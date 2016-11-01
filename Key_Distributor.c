/* 
 * File:   main.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"

//int Key_conversion(mpz_t *Y_en_su, const mpz_t *X, paillier_private_key *priv, paillier_public_key *pub){    
//    
//    int i,hi;
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){                        
//            mpz_init(*(Y_en_su + i*H + hi));           
//        }
//    }
//    
//    mpz_t temp, flag;
//    mpz_init(temp);
//    mpz_init(flag);
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){
//            paillier_decrypt(temp, *(X + i*H + hi), priv);            
//            size_t sz = mpz_sizeinbase (temp, 10);
//            if(sz <= DIFF_POS_NEG){
//                mpz_set_si(flag,1);
//            }
//            else{
//                mpz_set_si(flag,-1);
//            }
//            paillier_encrypt(*(Y_en_su + i*H + hi), flag, pub);
//        }
//    }
//    return 0;
//}