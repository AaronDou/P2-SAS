/* 
 * File:   main.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"

//int gen_req(mpz_t *R_en, paillier_public_key *pub){
//    
//    int i, hs;
//    srand(time(NULL));
//    mpz_t *R = (mpz_t *)malloc(L*H_S*sizeof(mpz_t));    
//    for(i = 0; i < L; i++){
//        for(hs = 0; hs < H_S; hs++){            
//            mpz_init_set_ui(*(R + i*H_S + hs), 0); 
//            mpz_init(*(R_en + i*H_S + hs));             
//        }
//    }
////    int pos = rand()%(L*H_S);
////    int tx_power = rand()%1000;     // unit: mWatt
//    int pos = 0;
//    int tx_power = 100000000;
//    printf("SU profile: %d %d %d\n", pos/H_S, pos%H_S, tx_power);
//    mpz_set_ui(*(R + pos), tx_power);    
//    for(i = 0; i < L; i++){
//        for(hs = 0; hs < H_S; hs++){  
//                paillier_encrypt(*(R_en + i*H_S + hs), *(R + i*H_S + hs), pub);           
//        }
//    }
//}
//int generate_U(mpz_t *U, int available, mpz_t *F_en, paillier_public_key *pub){
//    int i,hi;
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H_I; hi++){ 
//            mpz_init(*(U + i*H_I + hi)); 
//            paillier_encrypt(*(U + i*H_I + hi), ZERO, pub);   
//            paillier_homomorphic_add(*(U + i*H_I + hi), *(U + i*H_I + hi), *(F_en + i*H_I + hi), pub); // to calculate time cost
//        }
//    }      
//    
////    if (available == 0){
////        return 0;
////    }
////    else{
////        for(i = 0; i < L; i++){
////            for(hi = 0; hi < H_I; hi++){ 
////                paillier_homomorphic_add(*(U + i*H_I + hi), *(U + i*H_I + hi), *(F_en + i*H_I + hi), pub);
////            }
////        }  
////    }
//          
//}