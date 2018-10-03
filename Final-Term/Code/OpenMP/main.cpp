//
// Created by Alberto Ciolini on 20/09/2018.
//

#include <string>
#include <locale>
#include <iostream>
#include <stdlib.h>
#include <omp.h>

#include "des.h"
#include "utils.h"


using namespace std;


int main() {
    string text, text_hex, text_bin, key_hex, key_bin, n_threads;
    locale loc;

    pre:;
    std::cout << "Enter the 8 characters password (only number):\n";
    cin >> text;
    if(text.length()!=8) {
        cout<<"Enter all the characters\n";
        goto pre;
    }

    for(int i = 0; i < text.length(); i++) {
        if(!isdigit(text[i], loc)) {
            cout << "Password must contain only numbers!\n";
            goto pre;
        }
    }

    text_hex = string_to_hex(text);
    pre2:;
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

    int threads = omp_get_num_procs();;
    pre3:;
    cout << "Set number of threads (0: number of logical cores):\n";
    cin >> n_threads;
    for(int i = 0; i < n_threads.length(); i++) {
        if(!isdigit(n_threads[i], loc)) {
            cout << "Number of threads must be integer!\n";
            goto pre3;
        }
    }
    if(atoi(n_threads.c_str()) != 0)
        threads = atoi(n_threads.c_str());

    key_hex = "AABB09182736CCDD";
    if(key_hex.length()!=16)
    {
        cout<<"Enter all the key bits (in hexadecimal)\n";
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
    brute_force(encrypted_binary_text, text.length(), key, threads);
    /*string decrypted_text = decrypt(encrypted_binary_text, key);
    cout << "Decrypted password is: " << hex_to_string(decrypted_text) << endl;*/

    return 0;

}