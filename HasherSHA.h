//
// Created by Ikmokhirio on 04.01.2021.
//

#ifndef SHA_1_HASHERSHA_H
#define SHA_1_HASHERSHA_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

#include "utils.h"

class HasherSHA {
private:
    const unsigned DEFAULT_BLOCK_SIZE = 512; // 512 bits = 64 bytes
    const char FILLER = 0;

    std::string stringToHash;
    std::string hashedString;
    std::vector<std::vector<uint32_t>> blocks;

    void clearPreviousBlocks();

    std::string generateHash();

    std::string adjustMessagePadding();

    std::vector<uint32_t> processNextBlock(std::vector<uint32_t> block, std::vector<uint32_t> wordBuffer);

    void splitStringToBlocks();

public:

    explicit HasherSHA(const std::string& inputString = "");

    void hashString(const std::string &stringToHash = "");

    std::string getHashedString();

    friend std::ostream &operator<<(std::ostream &os, HasherSHA &hasher);

    friend std::istream &operator>>(std::istream &is, HasherSHA &hasher);
};


#endif //SHA_1_HASHERSHA_H
