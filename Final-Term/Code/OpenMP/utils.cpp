//
// Created by Alberto Ciolini on 26/09/2018.
//

#include <string>
#include <stdexcept>

using namespace std;


string hex_to_bin(const std::string& text) {
    string text_bin="";
    int l=text.length();
    for(int i=0;i<l;i++) {
        string st="";
        if(text[i]>='0'&& text[i]<='9') {
            int te=int(text[i])-48;
            while(te>0) {
                st+=char(te%2+48);
                te/=2;
            }
            while(st.length()!=4)
                st+='0';
            for(int j=3;j>=0;j--)
                text_bin+=st[j];
        } else {
            int te=text[i]-'A'+10;
            while(te>0) {
                st+=char(te%2+48);
                te/=2;
            }
            for(int j=3;j>=0;j--)
                text_bin+=st[j];
        }
    }
    return text_bin;
}

string string_to_hex(const std::string& text) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = text.length();
    string output;
    output.reserve(2*len);
    for (size_t i=0; i<len; ++i) {
        const unsigned char c = text[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }

    return output;
}

string hex_to_string(const std::string& text) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = text.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2) {
        char a = text[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = text[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}
