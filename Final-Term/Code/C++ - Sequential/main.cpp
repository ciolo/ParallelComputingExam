//
// Created by Alberto Ciolini on 20/09/2018.
//

#include <string>
#include <iostream>
#include <stdlib.h>

#include "des.h"
#include "utils.h"


using namespace std;


int main() {
    string text, text_hex, text_bin, key_hex, key_bin;
    pre:;
    std::cout << "Enter the 8 characters password (only numbers)\n";
    cin >> text;
    if(text.length()!=8)
    {
        cout<<"enter all the character\n";
        goto pre;
    }

    text_hex = string_to_hex(text);

    for(int i=0;i<16;i++)
    {
        if((text_hex[i]>='0'&& text_hex[i]<='9')||(text_hex[i]>='A'&& text_hex[i]<='F'))
            ;
        else
        {
            cout<<"Not a valid hexadecimal string\n";
            goto pre;
        }
    }

    key_hex = "AABB09182736CCDD";
    if(key_hex.length()!=16)
    {
        cout<<"enter all the key bits (in hexadecimal)\n";
        return 0;
    }
    for(int i=0;i<16;i++)
    {
        if((key_hex[i]>='0'&& key_hex[i]<='9')||(key_hex[i]>='A'&& key_hex[i]<='F'))
            ;
        else
        {
            cout<<"Not a valid hexadecimal key string\n";
            return 0;
        }
    }

    //Input is completed
    text_bin = hex_to_bin(text_hex);
    key_bin = hex_to_bin(key_hex);

    int **key;
    key = keygen(key_bin);

    cout << "Crypting...\n" << endl;
    string encrypted_binary_text = encrypt(text_bin, key);
    cout << "Encrypted text: " << encrypted_binary_text << endl;
    brute_force(encrypted_binary_text, text.length(), key);
    /*string decrypted_text = decrypt(encrypted_binary_text, key);
    cout << "Decrypted password is: " << hex_to_string(decrypted_text) << endl;*/

    return 0;

}