#include <string>
#include <iostream>
#include <sys/time.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime_api.h>

#include "des.h"
#include "utils.h"

using namespace std;


__device__ int ip_cuda[] = {
        58,50,42,34,26,18,10, 2,
        60,52,44,36,28,20,12, 4,
        62,54,46,38,30,22,14, 6,
        64,56,48,40,32,24,16, 8,
        57,49,41,33,25,17, 9, 1,
        59,51,43,35,27,19,11, 3,
        61,53,45,37,29,21,13, 5,
        63,55,47,39,31,23,15, 7,
};

__device__ int fp_cuda[64] = {
        40, 8,48,16,56,24,64,32,
        39, 7,47,15,55,23,63,31,
        38, 6,46,14,54,22,62,30,
        37, 5,45,13,53,21,61,29,
        36, 4,44,12,52,20,60,28,
        35, 3,43,11,51,19,59,27,
        34, 2,42,10,50,18,58,26,
        33, 1,41, 9,49,17,57,25,
};


__device__ int per_cuda[32]={
        16, 7, 20,21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
};

__device__ int s_cuda[8][4][16] = {
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

__device__ int e_cuda[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9,10,11,12,13,
        12,13,14,15,16,17,
        16,17,18,19,20,21,
        20,21,22,23,24,25,
        24,25,26,27,28,29,
        28,29,30,31,32, 1,
};

__device__ unsigned int n_symbols =10;

__device__ unsigned char* hex_to_bin_c(const unsigned char p[], int l, unsigned char ap[], unsigned char *st) //hexadecimal to binary
{
    unsigned int Idx = blockIdx.x;
    int inc = 0;
    for(int i=0;i<l;i++)
    {
        int count = 0;
        if(p[Idx*16+i]>=48 && p[Idx*16+i]<=57)
        {
            int te=int(p[Idx*16+i])-48;
            while(te>0)
            {
                st[Idx*4+count]=(unsigned char)(te%2+48);
                te/=2;
                count++;
            }
            while(count!=4)
            {
                st[Idx*4+count] = '0';
                count++;
            }
            for(int j=3;j>=0;j--)
            {
                ap[Idx*64+inc]=st[Idx*4+j];
                inc ++;
            }
        }
        else
        {
            int te=p[i]-'A'+10;
            while(te>0)
            {
                st[Idx*4+count]=(unsigned char)(te%2+48);
                te/=2;
                count++;
            }
            for(int j=3;j>=0;j--)
            {
                ap[Idx*64+inc] = st[Idx*4+j];
                inc++;
            }
        }
    }
    return ap;
}

__device__ unsigned char *string_to_hex_c(const unsigned char input[], int len, unsigned char output[])
{
    unsigned int Idx = blockIdx.x;
    static const char* const lut = "0123456789ABCDEF";
    int count = 0;
    for (int i=0; i<len; ++i) {
        const unsigned char c = input[Idx*8+i];
        output[Idx*16+count] = (lut[c >> 4]);
        count++;
        output[Idx*16+count] = (lut[c & 15]);
        count++;
    }
    return output;
}


__device__ unsigned char* encrypt_cuda(unsigned char *text, int *key, unsigned char *text_en, int len, unsigned char *l,
                                       unsigned char *r, unsigned char *rtem, unsigned char * ep, unsigned char *xorout,
                                       unsigned char *sout, unsigned char *soutt, unsigned char *pc, unsigned char *text_perm)
{
    unsigned int Idx = blockIdx.x;
    int i,m, j,row,col,temp,round=16, count2=0, count3=0, count4=0, count5=0;


    for(m=0;m<64;m++){
        text_perm[Idx*64+m] = text[Idx*64+ip_cuda[m]-1];
    }

    for(m=0; m<len/2; m++)
    {
        l[Idx*32+m] = text_perm[Idx*64+m];
        r[Idx*32+m] = text_perm[Idx*64+m+(len/2)];
    }

    while(round--) {
        for (m = 0; m < len / 2; m++) {
            rtem[Idx*32+m] = r[Idx*32+m];
        }
        count2 = 0;
        count4 = 0;

        //the expansion P box
        for(i = 0; i < 48; i++){
            ep[Idx*48+i] = r[Idx*32+e_cuda[i]-1];
        }
        //Key xor with output of expansion p box
        for (i = 0; i < 48; i++) {
            xorout[Idx*48+count2] = (unsigned char) (((int(ep[Idx*64+i]) - 48) ^ key[(48*(16-round-1)+i)] + 48));
            count2++;
        }
        //sbox compression 48bit to 32 bit
        for (i = 0; i < 48; i += 6) {
            row = (int(xorout[Idx*48+i + 5]) - 48) + (int(xorout[Idx*48+i]) - 48) * 2;
            col = (int(xorout[Idx*48+i + 1]) - 48) * 8 + (int(xorout[Idx*48+i + 2]) - 48) * 4 + (int(xorout[Idx*48+i + 3]) - 48) * 2 +
                  (int(xorout[Idx*48+i + 4]) - 48);
            temp = s_cuda[i / 6][row][col];
            count3 = 0;
            while (temp > 0) {
                soutt[Idx*4+count3] = (unsigned char) (temp % 2 + 48);
                count3++;
                temp /= 2;
            }
            while (count3 < 4) {
                soutt[Idx*4+count3] = 48;
                count3++;
            }
            for (j = count3 - 1; j >= 0; j--) {
                sout[Idx*48 + count4] = soutt[Idx*4+j];
                count4++;
            }
        }

        //straight pbox that is permutation of the sbox output
        for (i = 0; i < 32; i++)
        {
            pc[Idx*32+i] = sout[Idx*48 + per_cuda[i] - 1];
        }
        //r="";
        count5 = 0;
        for (i = 0; i < 32; i++)
        {
            r[Idx*32+count5] = (unsigned char) (((int(pc[Idx*32+i]) - 48) ^ (int(l[Idx*32+i]) - 48)) + 48);
            count5++;
        }
        for (m = 0; m < (len/2); m++)
        {
            l[Idx*(len/2)+m] = rtem[Idx*(len/2)+m];
        }

    }

    for(m=0; m<len/2; m++)
    {
        text_perm[Idx*(len)+m]=l[Idx*(len/2)+m];
        text_perm[Idx*(len)+m+len/2]=r[Idx*(len/2)+m];
    }

    for(m=0; m<64; m++){
        text_en[Idx*64+m] = text_perm[Idx*64+fp_cuda[m]-1];
    }

    return text_en;
}


__device__ void generateCombination(unsigned int *v, unsigned int k, int i)
{
    unsigned int Idx = blockIdx.x;
    unsigned int n = n_symbols;
    unsigned int div;
    for (int j=0; j<(k-1);j++){
        div = n;
        for (int m=2; m<=(k-1)-j; m++ ){
            div = div * n;
        }
        v[Idx*(k)+j] = i / div;
        i = i % div;
    }
    v[Idx*(k)+k-1] = i % n;
    return;
}

__global__ void brute_force_cuda(unsigned char encrypted_text_c[], unsigned int len, int* key, int threads,
        unsigned char *attack_psw, unsigned char *attack_h, unsigned char *attack_b, unsigned int* test,
        unsigned char *first_part, unsigned char *second_part, unsigned char *swap_part,
        unsigned char * ep, unsigned char *xorout, unsigned char *sout, unsigned char *soutt, unsigned char *pc,
                                 unsigned char *st, unsigned char *text_perm)
{
    unsigned int Idx = blockIdx.x;

    bool compare = false;
    unsigned int l = len;
    unsigned int n = n_symbols;

    unsigned int size = n;
    for (int k = 2; k <= l; k++) {
        size = size * n;
    }

    unsigned int size_per_thread = size / threads;
    unsigned int start = Idx*size_per_thread;
    unsigned int finish = start + size_per_thread;

    if(Idx >= threads){return;}
    if(Idx == threads)
    {
        finish = size;
    }

    for(int i=start; i<finish; i++)
    {
        generateCombination(test, l, i);

        //Convert test to char  array
        for (int j =0; j<l; j++)
        {
            attack_psw[Idx*l+j] = (unsigned char)test[Idx*l+j] + '0';
        }


        attack_h = string_to_hex_c(attack_psw, l, attack_h);
        attack_b = hex_to_bin_c(attack_h, l*2, attack_b, st);
        attack_b = encrypt_cuda(attack_b, key, attack_b, l*8, first_part, second_part, swap_part, ep, xorout, sout, soutt, pc, text_perm);

        for(int m=0; m < l*8; m++)
        {
            if(attack_b[Idx*(l*8)+m] != encrypted_text_c[m])
            {
                break;
            }
            if( m == (l*8)-1)
            {
                compare = true;
            }
        }
        if (compare)
        {
            printf("From thread %d \n", blockIdx.x);
            for(int m=0; m < 64; m++){
                printf("%d", attack_b[Idx*64+m] -'0');
            }
            printf("\n");
            asm("trap;");
            compare = false;
        }
    }
    printf("Any match found");
    return;
}


int main(){
    // Initialization parameters
    int threads = 0;
	unsigned int len = 8;
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

    pre3:;
    cout << "Set number of threads (0: set one thread):\n";
    cin >> n_threads;
    for(int i = 0; i < n_threads.length(); i++) {
        if(!isdigit(n_threads[i], loc)) {
            cout << "Number of threads must be integer!\n";
            goto pre3;
        }
    }
    if(atoi(n_threads.c_str()) != 0)
        threads = atoi(n_threads.c_str());

    if(threads == 0)
    	threads = 1;

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
    // Generation of the key
    text_bin = hex_to_bin(text_hex);
    key_bin = hex_to_bin(key_hex);

    int **key;
    key = keygen(key_bin);

    // from 2D to 1D
    unsigned  int height = 16;
    unsigned int width = 48;
    int *key_1D = new int [height*width];
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++)
            key_1D[width * h + w] = key[h][w];
    }

    cout << "Crypting...\n" << endl;

    unsigned char text_bin_c[text_bin.length()];
    for(int i=0; i < text_bin.length(); i++)
    {
        text_bin_c[i] = (unsigned char)text_bin[i];
    }

    unsigned int l = len * sizeof(unsigned char);
    unsigned char * encrypted_b_c = (unsigned char*)malloc(l*8);
    unsigned char *encrypted_binary_text_c = encrypt_c(text_bin_c, key, encrypted_b_c,64);
    cout << "Encrypted text: " << encrypted_binary_text_c << endl;

    // Start time
    struct timeval start, end;
    gettimeofday(&start, NULL);


    // Necessary to brute force cuda function
    unsigned char * compare_text;
    unsigned char * attack_psw;
    unsigned char * attack_h;
    unsigned char * attack_b;
    unsigned int * test;

    //Necessary to hex to bin function
    unsigned char * st;

    // Necessary to encrypt cuda function
    unsigned char * first_part;
    unsigned char * second_part;
    unsigned char * swap_part;
    unsigned char * ep;
    unsigned char * xorout;
    unsigned char * sout;
    unsigned char * soutt;
    unsigned char * pc;
    unsigned char * text_perm;

    cudaMalloc(&compare_text, l*8);
    cudaMemcpy(compare_text, encrypted_binary_text_c, l*8, cudaMemcpyHostToDevice);
    cudaMalloc(&attack_psw, l*threads);
    cudaMalloc(&attack_h, l*2*threads);
    cudaMalloc(&attack_b, l*8*threads);
    cudaMalloc(&test, l*threads);

    cudaMalloc(&st, l*threads/2);

    cudaMalloc(&first_part, l*4*threads);
    cudaMalloc(&second_part, l*4*threads);
    cudaMalloc(&swap_part, l*4*threads);
    cudaMalloc(&ep, l*8*threads);
    cudaMalloc(&xorout, l*6*threads);
    cudaMalloc(&sout, l*6*threads);
    cudaMalloc(&soutt, l*threads/2);
    cudaMalloc(&pc, l*4*threads);
    cudaMalloc(&text_perm, l*8*threads);

    unsigned int size_key= width*height* sizeof(int);
    int * p_key_1D;
    cudaMalloc(&p_key_1D, size_key);
    cudaMemcpy(p_key_1D, key_1D, size_key, cudaMemcpyHostToDevice);

    cout<<"Searching text...\n"<<endl;

    // call to kernel
    brute_force_cuda<<<threads,1>>>(compare_text, len, p_key_1D, threads, attack_psw, attack_h, attack_b, test,
            first_part, second_part, swap_part, ep, xorout, sout, soutt, pc, st, text_perm);

    cudaThreadSynchronize();

    // End time
    gettimeofday(&end, NULL);
    double time_tot = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    cout<<"Total time: "<< time_tot <<endl;

    // Free GPU space
    cudaFree(compare_text);
    cudaFree(attack_psw);
    cudaFree(attack_h);
    cudaFree(attack_b);
    cudaFree(test);

    cudaFree(first_part);
    cudaFree(second_part);
    cudaFree(swap_part);
    cudaFree(ep);
    cudaFree(xorout);
    cudaFree(sout);
    cudaFree(soutt);
    cudaFree(pc);
    cudaFree(text_perm);

    return 0;
}
