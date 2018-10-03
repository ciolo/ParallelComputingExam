//
// Created by alessandro on 29/09/18.
//

#ifndef CUDA_DES_UTILS_H
#define CUDA_DES_UTILS_H

#include <string>
#include <stdexcept>

using namespace std;

string hex_to_bin(std::string p) //hexadecimal to binary
{
    string ap="";
    int l=p.length();
    for(int i=0;i<l;i++)
    {
        string st="";
        if(p[i]>='0'&&p[i]<='9')
        {
            int te=int(p[i])-48;
            while(te>0)
            {
                st+=char(te%2+48);
                te/=2;
            }
            while(st.length()!=4)
                st+='0';
            for(int j=3;j>=0;j--)
                ap+=st[j];
        }
        else
        {
            int te=p[i]-'A'+10;
            while(te>0)
            {
                st+=char(te%2+48);
                te/=2;
            }
            for(int j=3;j>=0;j--)
                ap+=st[j];
        }
    }
    return ap;
}

string string_to_hex(const std::string& input) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    string output;
    output.reserve(2*len);
    for (size_t i=0; i<len; ++i) {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }

    return output;
}
#endif //CUDA_DES_UTILS_H
