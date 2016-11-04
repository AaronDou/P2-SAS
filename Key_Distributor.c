/* 
 * File:   main.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"

mpz_t * Key_conversion(const mpz_t *X_enc, paillier_private_key *priv, paillier_public_key *su_pub){
    
    mpz_t *Y_enc_su = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));      
    mpz_t temp, ONE;
    mpz_inits(temp, ONE, NULL);
    mpz_set_ui(ONE, 1);
    
    int l, h, f;
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){
                mpz_init(*(Y_enc_su + offset(l,h,f)));
                paillier_decrypt(temp, *(X_enc + offset(l,h,f)), priv);
                if (mpz_tstbit(temp, PSI+K-1)){ // negative
                    paillier_encrypt(*(Y_enc_su + offset(l,h,f)), ZERO, su_pub);
                }
                else{
                    paillier_encrypt(*(Y_enc_su + offset(l,h,f)), ONE, su_pub);
                }              
            }
        }
    }
    return Y_enc_su;
}