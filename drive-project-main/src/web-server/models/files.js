const { sendToEx2Server } = require("../integration");

let idCounter = 0
const files = []

const isExist = (id) => files.some(file => file.id === id);

const hasPermissions = (id, userId, perms) => {
    const file = files.find(file => file.id === id)
    return !(file.permissions[userId] == undefined || !(file.permissions[userId] & perms))
}

const isCreator = (id, userId) => {
    const file = files.find(file => file.id === id)
    return file.creator == userId
}

const isFolder = (id) => {
    const file = files.find(file => file.id === id)
    return (file.type == "folder")
}

const getAllFiles = (userId) => files.filter(file => file.permissions[userId] !== undefined);

const createFile = async (title, content, type, userId) => {
    /*
        Call the file server and provide (title, content) to create the file (or folder if type == "folder")!
    */
   let result;
    if (type == "file")
        result = await sendToEx2Server(`POST ${title} ${content}`);
    

    if (result.statusCode !== 201 && type == "file") { //error occurred
        throw { status: result.statusCode, message: result.statusLine };
    }

    const newFile = { id: ++idCounter, title, type, creator: userId, permissions: { [userId]: 7 } }
    files.push(newFile)

    return newFile
}

const getFile = async (id) => {
    const file = files.find(file => file.id === id)

    /*
        Call the file server with file.title and insert the text into str...

        NOTE: the file shouldnt have a content field in the files array, need to be changed
    */
    const result = await sendToEx2Server(`GET ${file.title}`);
    if (result.statusCode !== 200) { //error occurred
        throw { status: result.statusCode, message: result.statusLine };
    }

    return { ...file, content: result.bodyText }
}

const updateFile = async (id, title, content) => {
    const file = files.find(file => file.id === id);

    // Folders are local-only; renaming them should not call the external TCP server.
    if (file.type === "folder") {
        file.title = title;
        return;
    }

    // delete old entry in external server and recreate with new title/content
    const delRes = await sendToEx2Server(`DELETE ${file.title}`);
    if (delRes.statusCode !== 204) {
        throw { status: delRes.statusCode, message: delRes.statusLine };
    }

    const createRes = await sendToEx2Server(`POST ${title} ${content}`);
    if (createRes.statusCode !== 201) {
        throw { status: createRes.statusCode, message: createRes.statusLine };
    }

    // update local record
    file.title = title;
}

const deleteFile = async (id) => {
    const index = files.findIndex(file => file.id === id)

    const resultDel = await sendToEx2Server(`DELETE ${files[index].title}`);
    if (resultDel.statusCode !== 204) { //error occurred
        throw { status: resultDel.statusCode, message: resultDel.statusLine };
    }
    
    files.splice(index, 1) 
}

const getFilePermissions = (id) => {
    const file = files.find(file => file.id === id)

    return file.permissions
}

const createFilePermissions = (id, pid, perms) => {
    const file = files.find(file => file.id === id)

    file.permissions[pid] = perms;
}

const updateFilePermissions = (id, pid, perms) => {
    const file = files.find(file => file.id === id)

    file.permissions[pid] = perms;
}

const deleteFilePermissions = (id, pid) => {
    const file = files.find(file => file.id === id)

    delete file.permissions[pid];
}

const searchByQuery = async (query, userId) => {
    /*
        Call the search command in the file server with the query and set str as the output.
    */
    const result = await sendToEx2Server(`SEARCH ${query}`);
    if (result.statusCode !== 200) { //error occurred
        throw { status: result.statusCode, message: result.statusLine };
    }
    const names = result.bodyText.split(" ")

    // returning only the files/folders from the search that the user has read permissions.
    return files.filter(file => {
        const perm = file.permissions[userId];
        if (perm === undefined || (perm & 1) === 0) {
            return false
        }
        if (file.type === "file" && names.includes(file.title)) {
            return true
        }
        if (file.type === "folder" && file.title.includes(query)) {
            return true
        }
        return false;
    })

    /*
        Note: need to search also for folders within folder list
    */
}

module.exports = { 
    isExist,
    hasPermissions,
    isCreator,
    isFolder,
    getAllFiles,
    getFile,
    createFile,
    updateFile,
    deleteFile,
    getFilePermissions,
    createFilePermissions,
    updateFilePermissions,
    deleteFilePermissions,
    searchByQuery
}