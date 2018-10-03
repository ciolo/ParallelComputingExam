//
// Created by alessandro on 29/09/18.
//

#ifndef CUDA_DES_DES_H
#define CUDA_DES_DES_H


#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <sys/time.h>

#include "des.h"
#include "utils.h"

using namespace std;

static int IP[] = {
        58,50,42,34,26,18,10, 2,
        60,52,44,36,28,20,12, 4,
        62,54,46,38,30,22,14, 6,
        64,56,48,40,32,24,16, 8,
        57,49,41,33,25,17, 9, 1,
        59,51,43,35,27,19,11, 3,
        61,53,45,37,29,21,13, 5,
        63,55,47,39,31,23,15, 7,
};

static int FP[] = {
        40, 8,48,16,56,24,64,32,
        39, 7,47,15,55,23,63,31,
        38, 6,46,14,54,22,62,30,
        37, 5,45,13,53,21,61,29,
        36, 4,44,12,52,20,60,28,
        35, 3,43,11,51,19,59,27,
        34, 2,42,10,50,18,58,26,
        33, 1,41, 9,49,17,57,25,
};

static int PC1[] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4,
};

static int PC2[] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32,
};

static int P[32]={
        16, 7, 20,21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
};

static int S[8][4][16] = {
        {
                14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
        },
        {
                15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
        },


        {
                10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
        },
        {
                7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
        },
        {
                2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
        },
        {
                12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
        },
        {
                4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
        },
        {
                13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
        }
};

static int E[] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9,10,11,12,13,
        12,13,14,15,16,17,
        16,17,18,19,20,21,
        20,21,22,23,24,25,
        24,25,26,27,28,29,
        28,29,30,31,32, 1,
};


/**
 * Generate key to encrypt and decrypt
 * @param key_str: key in string format
 * @return sixteen key of 48 bit (Matrix)
 */
int** keygen(string key_str) {
    int key1[64];

    // Set the 64 bit key
    for(int i=0;i<64;i++)
        key1[i]=key_str[i]-'0';

    int keyl[28],keyr[28],nshift,temp1,temp2,pkey[56];
    int **key = new int*[16]; // Subkeys
    int i, j;
    // Key generation
    // The 64-bit key is permuted according to the PC-1 tabel
    // Only 56 bits of the original key appear in the permuted key.
    for(i=0;i<56;i++)
        pkey[i]=key1[PC1[i]-1];
    // Split key in left (C0) and right (D0) both of 28 bit dimension
    for(i=0;i<28;i++)
        keyl[i]=pkey[i];
    for(i=0;i<28;i++)
        keyr[i]=pkey[i+28];
    // round key generation:
    // with C0 (left_key) and D0 (right_key) defined, we now create sixteen blocks Cn and Dn, 1<=n<=16
    for(i=0;i<16;i++) {
        key[i] = new int[48];
        if(i==0||i==1||i==8||i==15)
            nshift=1;
        else
            nshift=2;
        while(nshift--) {
            temp1=keyl[0];
            temp2=keyr[0];
            for(j=0;j<27;j++) {
                keyl[j]=keyl[j+1];
                keyr[j]=keyr[j+1];
            }
            keyl[27]=temp1;
            keyr[27]=temp2;
        }
        // We now form the keys Kn, for 1<=n<=16,
        // by applying the following permutation table to each of the concatenated pairs CnDn.
        // Each pair has 56 bits, but PC-2 only uses 48 of these.
        for(j=0;j<24;j++)
            key[i][j]=keyl[PC2[j]-1];
        for(j=24;j<48;j++)
            key[i][j]=keyr[PC2[j]-1-28];
    }

    return key;
}


unsigned char* encrypt_c(unsigned char text[], int **key, unsigned char text_en[], int len)
{
    int sizeo = len* sizeof(char);
    unsigned char * l = (unsigned char*)malloc(sizeo/2);
    unsigned char * r = (unsigned char*)malloc(sizeo/2);
    unsigned char * rtem = (unsigned char*)malloc(sizeo/2);
    unsigned char * text_perm = (unsigned char*)malloc(sizeo);
    unsigned char * ep = (unsigned char*)malloc((sizeo*3)/4);
    unsigned char * xorout = (unsigned char*)malloc((sizeo*3)/4);
    unsigned char * sout = (unsigned char*)malloc((sizeo*3)/4);
    unsigned char * soutt = (unsigned char*)malloc(sizeo/16);
    unsigned char * pc = (unsigned char*)malloc(sizeo/2);
    int i,m,j,row,col,temp,round=16, count2=0, count3=0, count4=0, count5=0;

    for(m=0;m<64;m++){
	    text_perm[m] = text[IP[m]-1];
    }

    for(m=0; m<len/2; m++)
    {
        l[m] = text_perm[m];
        r[m] = text_perm[m+(len/2)];
    }

    while(round--) {
        for (m = 0; m < len / 2; m++) {
            rtem[m] = r[m];
        }
        count2 = 0;
        count4 = 0;
        //the expansion P box

        for(i = 0; i < 48; i++){
            ep[i] = r[E[i]-1];
        }
        //Key xor with output of expansion p box
        for (i = 0; i < 48; i++) {
            xorout[count2] = (unsigned char) (((int(ep[i]) - 48) ^ key[16 - round - 1][i]) + 48);
            count2++;
        }
        //sbox compression 48bit to 32 bit
        for (i = 0; i < 48; i += 6) {
            row = (int(xorout[i + 5]) - 48) + (int(xorout[i]) - 48) * 2;
            col = (int(xorout[i + 1]) - 48) * 8 + (int(xorout[i + 2]) - 48) * 4 + (int(xorout[i + 3]) - 48) * 2 +
                  (int(xorout[i + 4]) - 48);
            temp = S[i / 6][row][col];
            count3 = 0;
            while (temp > 0) {
                soutt[count3] = (unsigned char) (temp % 2 + 48);
                count3++;
                temp /= 2;
            }
            while (count3 < 4) {
                soutt[count3] = 48;
                count3++;
            }
            for (j = count3 - 1; j >= 0; j--) {
                sout[count4] = soutt[j];
                count4++;
            }
        }

        //straight pbox that is permutation of the sbox output
        for (i = 0; i < 32; i++)
        {
            pc[i] = sout[P[i] - 1];
        }
        count5 = 0;
        for (i = 0; i < 32; i++)
        {
            r[count5] = (unsigned char) (((int(pc[i]) - 48) ^ (int(l[i]) - 48)) + 48);
            count5++;
        }
        for (m = 0; m < (len/2); m++)
        {
            l[m] = rtem[m];
        }

    }

    for(m=0; m<len/2; m++)
    {
        text_perm[m]=l[m];
        text_perm[m+len/2]=r[m];
    }
    for(m=0; m<64; m++){
        text_en[m] = text_perm[FP[m]-1];
    }

    return text_en;
}

#endif //CUDA_DES_DES_H
