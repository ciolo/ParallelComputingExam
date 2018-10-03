//
// Created by Alberto Ciolini on 20/09/2018.
//

#ifndef DESCPP_DES_H
#define DESCPP_DES_H

#include <string>

/**
 * Key generation
 * @param key_str: key to generate
 * @return 16 subkeys, each of which is 48-bits long
 */
int** keygen(std::string key_str);

/**
 * Encyrpt text
 * @param text: binary text
 * @param key: key to encrypt text
 * @return encrypted text
 */
std::string encrypt(std::string text, int **key);

/**
 * Decrypt text
 * @param text: encrypted text
 * @param key: key to decrypt text
 * @return decrypted text
 */
std::string decrypt(std::string text, int **key);

/**
 * Brute-force attack
 * @param text: encrypted text to find 
 * @param key: key to encrypt text
 * @return
 */
void brute_force(std::string encrypted_text, int text_lenght, int **key);

#endif //DESCPP_DES_H
