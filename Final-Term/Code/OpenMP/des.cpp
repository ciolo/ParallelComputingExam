//
// Created by Alberto Ciolini on 24/09/2018.
//

#ifdef _NAMESPACE_CLEAN
#define keygen _keygen
#define encrypt _encrypt
#endif


#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <sys/time.h>

#include "des.h"
#include "utils.h"

#define N_SYMBOLS 10

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

#ifdef _NAMESPACE_CLEAN
#undef keygen
#pragma _HP_SECONDARY_DEF _keygen keygen
#define keygen _keygen
#endif

/**
 * Generate key to encrypt and decrypt
 * @param key_str: key in string format
 * @return sixteen  subkeys of 48 bit (Matrix)
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

#ifdef _NAMESPACE_CLEAN
#undef encrypt
#pragma _HP_SECONDARY_DEF _encrypt encrypt
#define encrypt _encrypt
#endif

/**
 * Des Encryption
 * @param text: text to encrypt
 * @param key: key to encrypt text
 * @return
 */
string encrypt(string text, int **key) {
    string l, r, rtem, text_iperm, text_fperm;
    int i,t,j,row,col,temp,round=16;

    // Initial Permutation
    text_iperm = "";
    for(i=0;i<64;i++)
        text_iperm += text[IP[i]-1];

    // Divide the message into a left half L0 of 32 bits, and a right half R0 of 32 bits.
    l=text_iperm.substr(0,32);
    r=text_iperm.substr(32,32);

    // Divide the message into a left half L0 of 32 bits, and a right half R0 of 32 bits.
    /*l = text.substr(0, 32);
    r = text.substr(32, 32);*/

    // We now proceed through 16 iterations, for 1<=n<=16, 
    // using a function f which operates on two blocks--a data block of 32 bits and a key Kn of 48 bits--to produce a block of 32 bits.
    while(round--) {
        rtem=r;
        t=1;
        string ep="", xorout="",sout="",soutt;

        //the expansion P box
        /*ep+=r[31];
        for(i=0;i<32;i++) {
            if((t+1)%6==0) {
                ep+=r[4*((t+1)/6)];
                t++;
            }
            if(t%6==0&&i!=0) {
                ep+=r[4*(t/6)-1];
                t++;
            }
            ep=ep+r[i];
            t++;
        }
        ep+=r[0];*/

        for(i = 0; i < 48; i++) {
            ep += r[E[i]-1];
        }

        //Next we XOR the output of expansion with the key Kn:
        for(i=0;i<48;i++)
            xorout+=char(((int(ep[i])-48)^key[16-round-1][i])+48);

        // We now have 48 bits, or eight groups of six bits. 
        // We use them as addresses in tables called "S boxes". 
        // Each group of six bits will give us an address in a different S box. 
        // Located at that address will be a 4 bit number. 
        // This 4 bit number will replace the original 6 bits. 
        // The net result is that the eight groups of 6 bits are 
        // transformed into eight groups of 4 bits (the 4-bit outputs from the S boxes) for 32 bits total.
        for(i=0;i<48;i+=6) {
            row=(int(xorout[i+5])-48)+(int(xorout[i])-48)*2;
            col= (int(xorout[i+1])-48)*8+(int(xorout[i+2])-48)*4+(int(xorout[i+3])-48)*2+(int(xorout[i+4])-48);
            temp=S[i/6][row][col];
            soutt="";
            while(temp>0) {
                soutt+=char(temp%2+48);
                temp/=2;
            }
            while(soutt.length()!=4)
                soutt+='0';
            for(j=soutt.length()-1;j>=0;j--)
                sout+=soutt[j];
        }

        // The final stage in the calculation of f is to do a 
        // permutation P, with table "per", of the S-box output to obtain the final value of f:
        // f = P(S1(B1)S2(B2)...S8(B8))
        char pc[32];
        for(i=0;i<32;i++)
            pc[i]=sout[P[i]-1];
        r="";
        for(i=0;i<32;i++)
            r+=char(((int(pc[i])-48)^(int(l[i])-48))+48);
        l=rtem;

        // Bin to Hex
        /*cout<<"Output after Round"<<16-round<<endl;
        string cip="";
        for(i=0;i<32;i+=4) {
            int te;
            te=(int(l[i])-48)*8+(int(l[i+1])-48)*4+(int(l[i+2])-48)*2+(int(l[i+3])-48);
            if(te<10)
                cip+=char(te+48);
            else
                cip+=char(te+55);
        }
        for(i=0;i<32;i+=4) {
            int te;
            te=(int(r[i])-48)*8+(int(r[i+1])-48)*4+(int(r[i+2])-48)*2+(int(r[i+3])-48);
            if(te<10)
                cip+=char(te+48);
            else
                cip+=char(te+55);
        }
        cout<<cip<<endl;*/
    }

    // Final Permutation
    string encrypted_text = r + l;
    text_fperm = "";
    for(i=0;i<64;i++)
        text_fperm += encrypted_text[FP[i]-1];

    return text_fperm;
    //return l + r;
}

/**
 * Desc Decryption
 * @param text: text to decrypt
 * @param key: key to decrypt text
 * @return
 */
string decrypt(string text, int** key) {
    string l, r, rtem, text_iperm, text_fperm;

    //DES decryption
    int i,t,j,row,col,temp,round=16;

    // Initial Permutation
    text_iperm = "";
    for(i=0;i<64;i++)
        text_iperm += text[IP[i]-1];

    l=text_iperm.substr(0,32);
    r=text_iperm.substr(32,32);

    /*l = text.substr(0, 32);
    r = text.substr(32, 32);*/

    string ltem;
    while(round--)
    {
        rtem=r;
        t=1;
        string ep="",xorout="",sout="",soutt;

        //the expansion P box
        /*ep+=l[31];
        for(i=0;i<32;i++)
        {
            if((t+1)%6==0)
            {
                ep+=l[4*((t+1)/6)];
                t++;
            }
            if(t%6==0&&i!=0)
            {
                ep+=l[4*(t/6)-1];
                t++;
            }
            ep=ep+l[i];
            t++;
        }
        ep+=l[0];*/

        for(i = 0; i < 48; i++) {
            ep += r[E[i]-1];
        }

        //Key xor with output of expansion p box
        for(i=0;i<48;i++)
            xorout+=char(((int(ep[i])-48)^key[round][i])+48);

        //sbox compression 48bit to 32 bit
        for(i=0;i<48;i+=6)
        {
            row=(int(xorout[i+5])-48)+(int(xorout[i])-48)*2;
            col= (int(xorout[i+1])-48)*8+(int(xorout[i+2])-48)*4+(int(xorout[i+3])-48)*2+(int(xorout[i+4])-48);
            temp=S[i/6][row][col];
            soutt="";
            while(temp>0)
            {
                soutt+=char(temp%2+48);
                temp/=2;
            }
            while(soutt.length()!=4)
                soutt+='0';
            for(j=soutt.length()-1;j>=0;j--)
                sout+=soutt[j];
        }

        //straight pbox that is permutation of the sbox output
        char pc[32];
        for(i=0;i<32;i++)
            pc[i]=sout[P[i]-1];
        r="";
        for(i=0;i<32;i++)
            r+=char(((int(pc[i])-48)^(int(l[i])-48))+48);
        l=rtem;

        /*
        cout<<"Decrypted Output after Round"<<16-round<<endl;
        string cip="";
        for(i=0;i<32;i+=4)
        {
            int te;
            te=(int(l[i])-48)*8+(int(l[i+1])-48)*4+(int(l[i+2])-48)*2+(int(l[i+3])-48);
            if(te<10)
                cip+=char(te+48);
            else
                cip+=char(te+55);
        }
        for(i=0;i<32;i+=4)
        {
            int te;
            te=(int(r[i])-48)*8+(int(r[i+1])-48)*4+(int(r[i+2])-48)*2+(int(r[i+3])-48);
            if(te<10)
                cip+=char(te+48);
            else
                cip+=char(te+55);
        }
        cout<<cip<<endl;*/

    }

    // Final Permutation
    string encrypted_text = r + l;
    text_fperm = "";
    for(i=0;i<64;i++)
        text_fperm += encrypted_text[FP[i]-1];

    l = text_fperm.substr(0, 32);
    r = text_fperm.substr(32, 32);

    // Bin to Hex
    string cip="";
    for(i=0;i<32;i+=4)
    {
        int te;
        te=(int(l[i])-48)*8+(int(l[i+1])-48)*4+(int(l[i+2])-48)*2+(int(l[i+3])-48);
        if(te<10)
            cip+=char(te+48);
        else
            cip+=char(te+55);
    }
    for(i=0;i<32;i+=4)
    {
        int te;
        te=(int(r[i])-48)*8+(int(r[i+1])-48)*4+(int(r[i+2])-48)*2+(int(r[i+3])-48);
        if(te<10)
            cip+=char(te+48);
        else
            cip+=char(te+55);
    }

    return cip;
}


void generateCombination(int v[], int k, int i){
    for (int j=0; j<(k-1);j++){
        v[j] = i / (int)(pow((double) N_SYMBOLS ,(double)((k-1)-j)));
        i = i % (int)(pow((double) N_SYMBOLS ,(double)((k-1)-j)));
    }
    v[k-1] = i % N_SYMBOLS;
}

void brute_force(string encrypted_text, int text_lenght, int **key, int threads) {
    int k = text_lenght;
    int n = N_SYMBOLS;
    long size = (long)pow((double)n,(double)k);

    cout<<"Searching text...\n"<<endl;

    /*struct timeval start, end;
    gettimeofday(&start, nullptr);*/
    double start_omp = omp_get_wtime();
    double time_tot;

    #pragma omp parallel num_threads(threads)
    {
        int test[k];
        char* comb = (char*)malloc(k);
        //char* attack_psw = (char*)malloc(text.length());
        string attack_psw;
        //char attack_salt[SALT_LENGTH];
        //char guess[16];
        string guess_text;

        unsigned num_iterations=0;
        #pragma omp for schedule(static)
        for(int i=0; i<size; i++) {

            generateCombination(test, k, i);

            //Convert test to char array
            for (int j =0; j<k; j++){
                sprintf(&(comb[j]), "%d", test[j]);
            }

            //strncpy(attack_psw,comb,text.length()); //copy only the password
            attack_psw = "";
            for(int j = 0; j < k; j++)
                attack_psw += comb[j];

            attack_psw = string_to_hex(attack_psw);
            attack_psw = hex_to_bin(attack_psw);
            guess_text = encrypt(attack_psw, key);

            if (!guess_text.compare(encrypted_text)) {
                /*gettimeofday(&end, nullptr);
                double time_tot = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;*/
                double end_omp = omp_get_wtime();
                time_tot = end_omp - start_omp;
                cout << "Text found: " << guess_text << endl;
                cout << "Thread: " << omp_get_thread_num() << endl;
                cout << "Total time openmp: "<< time_tot << endl;
                // Signal cancellation.
                #pragma omp cancel for
            }
            ++num_iterations;
            // Check for cancellations signalled by other threads:
            #pragma omp cancellation point for
        }

        free(comb);
        // All threads reach here eventually; sooner if the cancellation was signalled.
        printf("Thread %u: %u iterations completed\n", omp_get_thread_num(), num_iterations);
    }

    return;

}