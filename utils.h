//
// Created by Ikmokhirio on 04.01.2021.
//

#ifndef SHA_1_UTILS_H
#define SHA_1_UTILS_H

#include <climits>
#include <cstdint>
#include <string>
#include <fstream>
#include <streambuf>

class utils {
public:
    static uint32_t shiftLeft(uint32_t val, uint32_t pos); // Left Circular Shift

    static std::string readFileIntoString(const std::string &filepath);
};


#endif //SHA_1_UTILS_H
