/* 
 * File:   main.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"

mpz_t * gen_req(paillier_public_key *pub){
    
    int h, l, f;
    srand(time(NULL));
    
    mpz_t *R = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));   
    mpz_t *R_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));    
    initialize_mpz_array(R, 0);  
    initialize_mpz_array(R_enc, 0);  
      
    int pos = get_pos();
    int tx_power = get_tx_power();
    printf("SU profile: %d %d\n", pos, tx_power);
    
    mpz_set_ui(*(R + pos), tx_power); 
    
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){        
                paillier_encrypt(*(R_enc + offset(l,h,f)), *(R + offset(l,h,f)), pub);
                mpz_clear(*(R + offset(l,h,f)));
            }
        }
    }
    return R_enc;
}

int get_pos(){
//    srand(time(NULL));
//    int pos = rand()%(L*H*F);
//    return pos;
    return 0;
}

int get_tx_power(){
//    srand(time(NULL));  
//    int tx_power = rand()%1000;     // unit: mWatt
//    return tx_power;
    return 100000000;
}

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