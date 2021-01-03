//
// Created by Ikmokhirio on 04.01.2021.
//

#ifndef SHA_1_UTILS_H
#define SHA_1_UTILS_H

#include <climits>
#include <cstdint>

class utils {
public:
    static uint32_t rol(uint32_t val, uint32_t pos); // Left Circular Shift
};


#endif //SHA_1_UTILS_H
