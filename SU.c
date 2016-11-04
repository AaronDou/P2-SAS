/* 
 * File:   main.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include <stdbool.h>

mpz_t * gen_req(paillier_public_key *pub){
    
    int h, l, f;
    srand(time(NULL));
    
    mpz_t *R = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));   
    mpz_t *R_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));    
    initialize_mpz_array(R, 0);  
    initialize_mpz_array(R_enc, 0);  
      
    int pos = get_pos();
    int tx_power = get_tx_power();
    printf("\nSU operation position: %d, transmit power: %d\n", pos, tx_power);
    
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
    return 1000;
}

mpz_t * generate_U(bool availability, mpz_t *F_enc, paillier_public_key *pub){
    mpz_t *U_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    
    int h, l, f;
    if (availability == true){
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    mpz_init(*(U_enc+offset(l,h,f)));
                    paillier_encrypt(*(U_enc+offset(l,h,f)), ZERO, pub);
                    paillier_homomorphic_add(*(U_enc+offset(l,h,f)), *(U_enc+offset(l,h,f)), *(F_enc+offset(l,h,f)), pub); // to calculate time cost
                }
            }
        }
    }
    else{
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    mpz_init(*(U_enc+offset(l,h,f)));
                    paillier_encrypt(*(U_enc+offset(l,h,f)), ZERO, pub);
                }
            }
        }
    }
    return U_enc;
}