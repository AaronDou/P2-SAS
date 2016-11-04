/* 
 * File:   benchmark.c
 * Author: Yanzhi (Aaron) Dou 
 * E-mail: yzdou@vt.edu
 * Description: To generate operation benchmark of Paillier cryptosystem. 
 * Created on December 2, 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "paillier.h"
#include "Parameters.h"
#include <time.h>
#include "tools.h"

int benchmark(){

    // initialization
    FILE *public_key, *private_key;
    paillier_public_key pub;
    paillier_private_key priv;
    paillier_public_init(&pub);
    paillier_private_init(&priv);
    clock_t tic, toc;
    int k = 300;  // number of operations
    int n = 2048; // security parameter
    
    
    unsigned long seed;
    gmp_randstate_t state;
    seed = time(NULL); // system time
    gmp_randinit_default(state);
    gmp_randseed_ui(state, seed);
    srand(time(NULL));
    
    mpz_t *a1 = malloc(k* sizeof(mpz_t)); // allocate space for k plaintext messages
    mpz_t *c1 = malloc(k* sizeof(mpz_t));
    mpz_t *a2 = malloc(k* sizeof(mpz_t));
    mpz_t *c2 = malloc(k* sizeof(mpz_t));
    mpz_t *c3 = malloc(k* sizeof(mpz_t));
    mpz_t *ran_20 = malloc(k* sizeof(mpz_t)); // allocate space for k 20-bit random numbers
    mpz_t *ran_112 = malloc(k* sizeof(mpz_t)); // allocate space for k 112-bit random numbers
    
    
    // read key pair from files
    public_key = fopen("./pub2048", "r");
    private_key = fopen("./priv2048", "r");
    paillier_public_in_str(&pub, public_key);
    paillier_private_in_str(&priv, private_key);
    
    // Encryption
    int i;
    for (i=0;i<k;i++){
        mpz_init(a1[i]);
        mpz_urandomb(a1[i],state,n); // assign random value in the range of 0 to 2^n-1
        mpz_init (c1[i]);
        
        mpz_init(a2[i]);
        mpz_urandomb(a2[i],state,n);
        mpz_init (c2[i]);

        mpz_init (c3[i]);
        mpz_init(ran_20[i]);
        mpz_urandomb(ran_20[i],state,20); 
        mpz_init(ran_112[i]);
        mpz_urandomb(ran_112[i],state,112);

//        gmp_printf("%Zd\n", ran_20[i]);
//        gmp_printf("%Zd\n", ran_120[i]);
    }
    
//    Encryption
    tic = clock();
    for(i = 0; i < k; i++){
//        printf("%d\n",i);
        paillier_encrypt(c1[i], a1[i], &pub);        
    }
    toc = clock();
    gmp_printf ("One encryption takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC/k*1000000);
    
    
    for(i = 0; i < k; i++){
//        printf("%d\n",i);
        paillier_encrypt(c2[i], a2[i], &pub);        
    }
    
  
    // Addition 
    tic = clock();

    for(i = 0; i<k; i++){
//        printf("%d\n",i);
        paillier_homomorphic_add(c3[i], c1[i], c2[i], &pub);
    }
    toc = clock();
    gmp_printf ("One addition takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC/k*1000000);
    
    
    // Multiplication 20 bit
    
    tic = clock();
    
    for(i = 0; i<k; i++){
//        printf("%d\n",i);
        paillier_homomorphic_multc(c3[i], c1[i], ran_20[i], &pub);
    }
    toc = clock();
    gmp_printf ("One scalar multiplication by 20-bit random value takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC /k*1000000);
    
    // Multiplication 120 bit
    
    tic = clock();
    
    for(i = 0; i<k; i++){
//        printf("%d\n",i);
        paillier_homomorphic_multc(c3[i], c1[i], ran_112[i], &pub);
    }
    toc = clock();
    gmp_printf ("One scalar multiplication by 112-bit random value takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC /k*1000000);
    
    // Subtraction
    
    tic = clock();
    
    for(i = 0; i<k; i++){
//        printf("%d\n",i);
        paillier_homomorphic_sub(c3[i], c1[i], c2[i], &pub);
    }
    toc = clock();
    gmp_printf ("One subtraction takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC /k*1000000);
    
    
    // Decrypt
    tic = clock();
    
    for(i = 0; i<k; i++){
//        printf("%d\n",i);
        paillier_decrypt(a1[i], c1[i], &priv);
    }
    toc = clock();
    gmp_printf ("One decryption takes  %f microseconds\n", (float)(toc-tic)/CLOCKS_PER_SEC /k*1000000);
    
}

