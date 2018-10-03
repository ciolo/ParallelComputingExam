//
// Created by Alberto Ciolini on 26/09/2018.
//

#ifndef DESCPP_UTILS_H
#define DESCPP_UTILS_H

#include <string>

/**
 * Convert hexadecimal to binary text
 * @param text: text to convert
 * @return binary text
 */
std::string hex_to_bin(const std::string& text);

/**
 * Convert string to hexadecimal text
 * @param text: text to convert
 * @return hexadecimal 
 */
std::string string_to_hex(const std::string& text);

/**
 * Convert hexadecimal to string
 * @param text: text to convert
 * @return string
 */
std::string hex_to_string(const std::string& text);

#endif //DESCPP_UTILS_H
