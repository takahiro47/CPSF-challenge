//
//  main.c
//  [20111208] cpsf_sosu2_kai
//  CPSF 素数のアルゴリズム
//
//  Created by 土屋 貴裕 on 11/12/09.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/* macros */


/* prototypes */
unsigned int *alloc_prime_tab(unsigned int n);
void make_prime_tab(unsigned int n, unsigned int ip[]);
void print_primes(unsigned int n, unsigned int ip[]);
unsigned int count_primes(unsigned int n, unsigned int ip[]);

/* variables */


/* main */
#ifdef DEBUG
int main (int argc, const char * argv[]) {
    unsigned int n, *ip;
    
    printf("検索範囲の上限を入力(MAX:65535) -->\n");
    scanf("%d", &n);
    ip = alloc_prime_tab(n);
    
    make_prime_tab(n, ip);
    print_primes(n, ip);
    printf ("%d Primes found.\n", count_primes(n, ip));
    
    free(ip);
}
#endif


/* --------------------------------
 検索する数のメモリを確保する関数
 input  >> unsigned int n: 素数をサーチする数字の上限
 return >> unsigned int ip: 確保したメモリ番地？
 --------------------------------- */
unsigned int *alloc_prime_tab(unsigned int n) {
    unsigned int nh, j, ibit, *ip;
    
    nh = n >> 1;
    ibit = 0;
    for (j = 8 * sizeof(unsigned int); j > 1; j >>= 1) ibit++;
    ip = (unsigned int *) malloc(((nh >> ibit) + 1) << (ibit - 3));
    return ip;
}


/*  */
void make_prime_tab(unsigned int n, unsigned int ip[]) {
    unsigned int nh, j, k, ibit, imask;
    
    nh = n >> 1;
    ibit = 0;
    for (j = 8 * sizeof(unsigned int); j > 1; j >>= 1) ibit++;
    imask = ~((-1) << ibit);
    for (j = 0; j <= (nh >> ibit); j++) ip[j] = 0;
    
    for (k = 1; k <= nh / 3; k++) {
        if ((~ip[k >> ibit]) & (1 << (k & imask))) {
            for (j = k + (k + k + 1); j < nh; j += k + k + 1) {
                ip[j >> ibit] |= 1 << (j & imask);
            }
        }
    }
}


/* */
void print_primes(unsigned int n, unsigned int ip[]) {
    unsigned int nh, j, ibit, imask;
    
    nh = n >> 1;
    ibit = 0;
    for (j = 8 * sizeof(unsigned int); j > 1; j >>= 1) ibit++;
    imask = ~((-1) << ibit);
    
    if (n > 2) {
        printf ("%d\n", 2);
    }
    for (j = 1; j < nh; j++) {
        if ((~ip[j >> ibit]) & (1 << (j & imask))) {
            printf ("%d\n", j + j + 1);
        }
    }
}


/* */
unsigned int count_primes(unsigned int n, unsigned int ip[]) {
    unsigned int nh, j, k, ibit, imask;
    
    nh = n >> 1;
    ibit = 0;
    for (j = 8 * sizeof(unsigned int); j > 1; j >>= 1) ibit++;
    imask = ~((-1) << ibit);
    
    k = 0;
    if (n > 2) {
        k++;
    }
    for (j = 1; j < nh; j++) {
        if ((~ip[j >> ibit]) & (1 << (j & imask))) {
            k++;
        }
    }
    return k;
}