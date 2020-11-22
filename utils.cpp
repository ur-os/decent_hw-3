//
// Created by ur0s on 11/23/20.
//

#include "utils.h"

std::string string_to_hex(const std::string& in) {
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for(auto i : in)
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(i));

    return "0x" + ss.str();
}

std::string hex_to_string(std::string& in) {
    std::string output;
    in = in.substr(2);

    if ((in.length() % 2) != 0)
        throw std::runtime_error("String is not valid length ...");

    size_t cnt = in.length() / 2;

    for (size_t i = 0; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;

        output.push_back(static_cast<unsigned char>(s));
    }

    return output;
}

int parameter_processing(const std::string& mode) {
    if(mode == "split")
        return SPLIT;
    if(mode == "recover")
        return RECOVER;

    return WRONG_ARGUMENTS;
}