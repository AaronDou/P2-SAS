/* 
 * File:   SAS.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include "declaritions.h"
// All the variables are in ciphertext
// All the constants are in plaintext.


mpz_t * aggregation(paillier_public_key *pub){ // may extract the PU computation part to PU.c in the future
    
    mpz_t *N_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    initialize_mpz_array(N_enc, 0);
    mpz_t *T_i_enc;
    struct Pos_Value* pv=PU_data_generation_coordination();
    int pu_i, l, h, f;
    
    mpz_t Z;
    mpz_init(Z);
    mpz_setbit(Z,K-1);
    mpz_sub_ui(Z,Z,1);
                    
                    
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){                   
            paillier_encrypt(*(N_enc + offset(l,h,f)), Z, pub);
            }
        }
    }
    
    for (pu_i=0; pu_i<PU_NUM; pu_i++){
        T_i_enc=PU_i_update(pv+pu_i, pub);
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    paillier_homomorphic_add(*(N_enc + offset(l,h,f)), *(N_enc + offset(l,h,f)), *(T_i_enc+offset(l,h,f)), pub);
                }
            }
        }
    }
    return N_enc;
}




mpz_t * cal_Interference_Budget(const mpz_t *N_enc, mpz_t *F_enc, const mpz_t *I, const mpz_t *R_enc, paillier_public_key *pub){
    
    int l_s, h_s, f_s, l_i, h_i, f_i;
    mpz_t *G_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    
    mpz_t temp;
    mpz_init(temp);
    
    for(l_i = 0; l_i < L; l_i++){               
        for(h_i = 0; h_i < H; h_i++){
            for(f_i = 0; f_i < F; f_i++){  
                mpz_inits(*(G_enc+offset(l_i,h_i,f_i)), *(F_enc+offset(l_i,h_i,f_i)), NULL);
                paillier_encrypt(*(F_enc+offset(l_i,h_i,f_i)), ZERO, pub);
                
                for(l_s = 0; l_s < L; l_s++){               
                    for(h_s = 0; h_s < H; h_s++){
                        for(f_s = 0; f_s < F; f_s++){
                            paillier_homomorphic_multc(temp, *(R_enc+offset(l_s,h_s,f_s)), *(I+ l_i*L*H*H*F*F + h_i*L*H*F*F+ f_i*L*H*F + l_s*H*F +h_s*F + f_s), pub);   
                            paillier_homomorphic_add(*(F_enc+offset(l_i,h_i,f_i)), *(F_enc+offset(l_i,h_i,f_i)), temp, pub);
                        }   
                    }
                }
                
                paillier_homomorphic_sub(*(G_enc+offset(l_i,h_i,f_i)), *(N_enc+offset(l_i,h_i,f_i)), *(F_enc+offset(l_i,h_i,f_i)), pub);  
            }
        }
    }    
    return G_enc;
}

int * get_epsilon(){
    srand(time(NULL));
    int * epsilon= (int *)malloc(L*H*F*sizeof(int)); 
    int l, h, f;
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){        
                *(epsilon + offset(l,h,f))= rand()%2;
//                *(epsilon + offset(l,h,f))= 0;
            }
        }
    }
    return epsilon;
}

mpz_t * obfuscate(int *epsilon, const mpz_t *G_enc, paillier_public_key *pub){
    
    mpz_t *X_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));    
    mpz_t alpha, beta, beta_enc, tau, tau_enc, temp, temp_enc;
    mpz_inits(alpha, beta, beta_enc, tau, tau_enc, temp, temp_enc, NULL);
    
    int l, h, f;
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){
                mpz_init(*(X_enc + offset(l,h,f)));
                mpz_inits(alpha, beta, tau, NULL);// need to re-init
                while(mpz_cmp(alpha, beta) <= 0){
                    gen_pseudorandom(alpha, 216);
                    gen_pseudorandom(beta, 216);
                    gen_pseudorandom(tau, PSI);
                }
                mpz_mul_2exp(tau, tau, PSI+K);//left-shifting
//                gmp_printf("%Zd\n%Zd\n", alpha, beta);
//                printf("%d\n", mpz_tstbit(alpha, PSI-1));
                paillier_encrypt(beta_enc, beta, pub);
                paillier_encrypt(tau_enc, tau, pub);
                paillier_homomorphic_multc(*(X_enc + offset(l,h,f)), *(G_enc + offset(l,h,f)), alpha, pub);
                paillier_homomorphic_add(*(X_enc + offset(l,h,f)), *(X_enc + offset(l,h,f)), tau_enc, pub);
                paillier_homomorphic_sub(*(X_enc + offset(l,h,f)), *(X_enc + offset(l,h,f)), beta_enc, pub);
                if (*(epsilon + offset(l,h,f))==0){
                    mpz_setbit (temp, PSI+K-1);//different from paper, use homo.. addition instead of multi for sign obfuscation
                    paillier_encrypt(temp_enc, temp, pub);
                    paillier_homomorphic_add(*(X_enc + offset(l,h,f)), *(X_enc + offset(l,h,f)), temp_enc, pub);
                }
            }
        }
    }   
    return X_enc;
}

mpz_t * calc_Q(const int *epsilon, const mpz_t *Y_enc_su, paillier_public_key *su_pub){
    
    mpz_t *Q_enc_su = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    int l, h, f;
    mpz_t temp, mpz_epsilon;
    mpz_inits(temp, mpz_epsilon, NULL);
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){
                mpz_init(*(Q_enc_su + offset(l,h,f)));
                mpz_set_ui(mpz_epsilon, *(epsilon + offset(l,h,f)));
                paillier_encrypt(temp, mpz_epsilon, su_pub);
                paillier_homomorphic_sub(*(Q_enc_su + offset(l,h,f)), *(Y_enc_su + offset(l,h,f)) , temp, su_pub);
            }
        }
    }
    return Q_enc_su;
}

mpz_t * get_signature(){
    mpz_t* signature = (mpz_t *)malloc(sizeof(mpz_t));
    mpz_init(*signature);
    
    //2048-bit RSA signature can achieve approx. 112-bit security lvl.
    
    //can read from file
    
    //can build interface with RSA signature generation app. 
    
    
    mpz_set_str(*signature,\
"6f7df91d8f973a0619d525c319337741130b77b21f9667dc7d1d74853b644cbe\
5e6b0e84aacc2faee883d43affb811fc653b67c38203d4f206d1b838c4714b6b\
2cf17cd621303c21bac96090df3883e58784a0576e501c10cdefb12b6bf887e5\
48f6b07b09ae80d8416151d7dab7066d645e2eee57ac5f7af2a70ee0724c8e47",16);
    
    return signature;
}

mpz_t * calc_D(const mpz_t *Q_enc_su, paillier_public_key *su_pub){
    
    mpz_t *D_enc_su = (mpz_t *)malloc(sizeof(mpz_t));
    mpz_t sum;
    mpz_inits(*D_enc_su, sum, NULL);
    paillier_encrypt(sum, ZERO, su_pub);
    int l, h, f;
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){
                paillier_homomorphic_add(sum, sum, *(Q_enc_su + offset(l,h,f)), su_pub);
            }
        }
    }
    
    mpz_t sigma;
    mpz_init(sigma);
    gen_pseudorandom(sigma, 2048);//sigma is a 2048-bit long random number
    paillier_homomorphic_multc(sum, sum, sigma, su_pub);
    
    mpz_t* signature = get_signature();
    mpz_t signature_enc;
    mpz_init(signature_enc);
    paillier_encrypt(signature_enc, *signature, su_pub);
    
    paillier_homomorphic_add(*D_enc_su, sum, signature_enc, su_pub);
//    paillier_homomorphic_multc(*D_enc_su, sum, ZERO, su_pub);
    return D_enc_su;
}


int update_N(mpz_t *N_enc, mpz_t *U_enc, paillier_public_key *pub){
    int l, h, f;
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){
                paillier_homomorphic_sub(*(N_enc + offset(l,h,f)), *(N_enc + offset(l,h,f)), *(U_enc + offset(l,h,f)), pub);
            }
        }
    }
    return 0;
}