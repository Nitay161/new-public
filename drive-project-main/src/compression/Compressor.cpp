#include "Compressor.h"
#include <stdexcept>

string compress(string text) {
    string compressed;
    char current = text[0];
    int count = 0;
    // Iterate over the string.
    for (int i = 0; i < text.size(); i++) {
        // Count the number of same chars.
        count++;
        // If this is the end or the next char is diffirent then the current...
        if (i == text.size() || text[i+1] != current) {
            // Compress.
            compressed += current;
            compressed += to_string(count);
            current = text[i+1];
            count = 0;
        }
    }
    return compressed;
}

string decompress(string text) {
    // Checking if the text's length is even (it should be even when it compressed by RLE)
    if (text.size() % 2 != 0) throw invalid_argument("The text is not in RLE format.");
    string decompressed;
    for (int i = 0; i < text.size(); i+=2) {
        char countS = text[i+1];
        // Checking if the expected char that should be a number is indeed a number.
        if (countS >= 48 && countS <= 57)
            decompressed.append(countS - '0', text[i]);
        else throw invalid_argument("The text is not in RLE format.");
    }
    return decompressed;
}