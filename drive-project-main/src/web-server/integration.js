const net = require("net");

const EX2_HOST = process.env.EX2_HOST || "server"; //server is the docker-compose service name
const EX2_PORT = process.env.EX2_PORT || 12345; //port number for the ex2 server



// parse Ex2 response text into a structured object.
// Ex2 formats:
// - "201 Created\n"
// - "204 No Content\n"
// - "404 Not Found\n"
// - "400 Bad Request\n"
// - "200 Ok\n\n<BODY...>\n"
function parseEx2Response(message) {
    const newLine1 = message.indexOf("\n");
    let text;

    if (newLine1 === -1) {
        text = message;
    } else {
        text = message.substring(0, newLine1);
    }

    // Normalize any accidental CRLF / trailing whitespace.
    text = String(text).replace(/\r$/, "").trim();

    const map = {
        "200 Ok": 200,
        "201 Created": 201,
        "204 No Content": 204,
        "400 Bad Request": 400,
        "404 Not Found": 404,
    };

    let statusCode;

    if (text in map)
        statusCode = map[text];
    else
        statusCode = 500;

    //extract the body (relevant only for 200 responses, like GET, SEARCH)
    let body = null;
    const seperator = "\n\n";
    const sepIndex = message.indexOf(seperator);


    if (statusCode === 200 && sepIndex !== -1) { //only 200 responses have bodies
        body = message.substring(sepIndex + seperator.length).trim();
    }

    return { statusCode, statusLine: text, bodyText: body, raw: message };
}

function isCompleteEx2Response(buf) {
    const s = buf.toString();

    // must have at least first line
    const firstNl = s.indexOf("\n");
    if (firstNl === -1) return false;

    const statusLine = s.slice(0, firstNl).trim();

    // responses without body: just one line ending with \n
    if (statusLine !== "200 Ok") {
        return s.endsWith("\n");
    }

    // 200 Ok: must contain the separator \n\n and then end with \n
    return s.includes("\n\n") && s.endsWith("\n");
}


function sendToEx2Server(message) {
    return new Promise((resolve, reject) => {
        const client = new net.Socket();
        let buffer = "";

        client.setTimeout(3000, () => {
            client.destroy();
            reject(new Error("Ex2 timeout"));
        });

        client.connect(EX2_PORT, EX2_HOST, () => {
            client.write(message.endsWith("\n") ? message : message + "\n");
        });

        client.on("data", (chunk) => {
            buffer += chunk.toString();

            if (isCompleteEx2Response(buffer)) {
                // we have ONE full response; stop everything now
                const parsed = parseEx2Response(buffer);
                client.destroy();           // important: don't wait for server to close
                resolve(parsed);
            }
        });

        client.on("error", reject);
    });
}


module.exports = {
  sendToEx2Server,
  parseEx2Response,
};