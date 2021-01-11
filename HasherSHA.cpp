//
// Created by Ikmokhirio on 04.01.2021.
//

#include "HasherSHA.h"

void HasherSHA::hashString(const std::string &stringToHash) {
    if (!stringToHash.empty()) {
        this->stringToHash = stringToHash;
    }

    splitStringToBlocks();
    hashedString = generateHash();
}

void HasherSHA::splitStringToBlocks() {

    clearPreviousBlocks();

    unsigned amountOfIntsInBlock = DEFAULT_BLOCK_SIZE / (CHAR_BIT * sizeof(uint32_t));

    std::string input = adjustMessagePadding();

    unsigned amountOfBlocks = input.size() * sizeof(char) * CHAR_BIT / 512;

    int counter = 0;
    for (int i = 0; i < amountOfBlocks; i++) {
        std::vector<uint32_t> tmpVec;

        for (int j = 0; j < amountOfIntsInBlock; j++) {

            uint32_t value = 0;
            memcpy(&value, input.c_str() + (sizeof(uint32_t) * counter), sizeof(uint32_t));

            value = BYTE_SWAP(value); // Convert little endian to big endian
            tmpVec.push_back(value);

            counter++;
        }

        blocks.push_back(tmpVec);
    }
}

std::string HasherSHA::adjustMessagePadding() {
    std::string message = stringToHash;

    uint64_t len = message.size() * sizeof(char) * CHAR_BIT; // Length of message in bits

    message += (char) (1 << (CHAR_BIT - 1)); // Add 10000000 to the end of message

    while (message.size() * sizeof(char) * CHAR_BIT % DEFAULT_BLOCK_SIZE != 448) {
        message += FILLER;
    }

    for (int i = 0; i < sizeof(uint64_t); i++) {
        message += (char) (len >> (CHAR_BIT * (CHAR_BIT - (i + 1)))); // Add message length as big endian by bytes
    }


    while (message.size() * sizeof(char) * CHAR_BIT % DEFAULT_BLOCK_SIZE != 0) {
        message += FILLER;
    }

    return message;
}

std::string HasherSHA::generateHash() {
    std::vector<uint32_t> intermediateHashes;
    intermediateHashes.push_back(0x67452301);
    intermediateHashes.push_back(0xEFCDAB89);
    intermediateHashes.push_back(0x98BADCFE);
    intermediateHashes.push_back(0x10325476);
    intermediateHashes.push_back(0xC3D2E1F0);

    for (auto &block : blocks) {


        std::vector<uint32_t> wordBuffer = intermediateHashes;

        //Process one block
        wordBuffer = processNextBlock(block, wordBuffer);

        for (int i = 0; i < intermediateHashes.size(); i++) {
            intermediateHashes[i] += wordBuffer[i];
        }

    }

    std::stringstream ss;
    for (unsigned int intermediateHash : intermediateHashes) {
        ss << std::setfill('0') << std::setw(8) << std::hex << intermediateHash;
    }

    return ss.str();
}

std::vector<uint32_t> HasherSHA::processNextBlock(std::vector<uint32_t> block, std::vector<uint32_t> wordBuffer) {
    uint32_t f = 0;
    uint32_t k = 0;


    for (int t = 0; t < 80; t++) {

        if (t >= 16) {
            block.push_back(utils::shiftLeft(block[t - 3] ^ block[t - 8] ^ block[t - 14] ^ block[t - 16], 1));
        }

        if (t >= 0 && t <= 19) {
            f = ((wordBuffer[1] & wordBuffer[2]) | ((~wordBuffer[1]) & wordBuffer[3]));
            k = 0x5A827999;
        } else if (t >= 20 && t <= 39) {
            f = (wordBuffer[1] ^ wordBuffer[2] ^ wordBuffer[3]);
            k = 0x6ED9EBA1;
        } else if (t >= 40 && t <= 59) {
            f = ((wordBuffer[1] & wordBuffer[2]) | (wordBuffer[1] & wordBuffer[3]) | (wordBuffer[2] & wordBuffer[3]));
            k = 0x8F1BBCDC;
        } else if (t >= 60 && t <= 79) {
            f = (wordBuffer[1] ^ wordBuffer[2] ^ wordBuffer[3]);
            k = 0xCA62C1D6;
        } else {
            std::cerr << "ERROR" << std::endl;
        }

        uint32_t temp = utils::shiftLeft(wordBuffer[0], 5) + f + wordBuffer[4] + block[t] + k;

        wordBuffer[4] = wordBuffer[3];
        wordBuffer[3] = wordBuffer[2];
        wordBuffer[2] = utils::shiftLeft(wordBuffer[1], 30);
        wordBuffer[1] = wordBuffer[0];
        wordBuffer[0] = temp;

    }

    return wordBuffer;
}

std::ostream &operator<<(std::ostream &os, HasherSHA &hasher) {
    hasher.hashString();
    os << hasher.getHashedString();
    return os;
}

std::istream &operator>>(std::istream &is, HasherSHA &hasher) {
    std::string inputString;
    is >> inputString;
    hasher.stringToHash += inputString;
    return is;
}

std::string HasherSHA::getHashedString() {
    return hashedString;
}

void HasherSHA::clearPreviousBlocks() {
    std::vector<std::vector<uint32_t>> tmpBlocks;
    blocks.swap(tmpBlocks);
}

HasherSHA::HasherSHA(const std::string &inputString) {
    if (!inputString.empty()) {
        hashString(inputString);
    }
}
