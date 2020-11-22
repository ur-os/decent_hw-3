//
// Created by ur0s on 11/23/20.
//

#ifndef DECENT_HW_3_UTILS_H
#define DECENT_HW_3_UTILS_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <cstdint>

const int SPLIT = 29345236;
const int RECOVER = 321345657;
const int WRONG_ARGUMENTS = 47135678;

std::string string_to_hex(const std::string&);
std::string hex_to_string(std::string&);
int parameter_processing(const std::string&);

#endif //DECENT_HW_3_UTILS_H
