/* 
 * File:   SAS.c
 * Author: yanzhi
 *
 * Created on December 2, 2014, 7:57 PM
 */

#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include "linked_list.h"
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




//int initialize_N(mpz_t *N_en, paillier_public_key *pub){
//    
//    int i, hi;
//    mpz_t *N = (mpz_t *)malloc(L*H*sizeof(mpz_t));
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){            
//            mpz_init_set(*(N + i*H_I + hi), EXTREMELY_LARGE_NUMBER);
//            mpz_init(*(N_en + i*H_I + hi));
//            paillier_encrypt(*(N_en + i*H + hi), *(N + i*H + hi), pub);
//        }
//    }
//}
//
//int update_PU(mpz_t *N_out, mpz_t *N_in, const mpz_t *M, paillier_public_key *pub){
//    
//    mpz_t large_number;
//    mpz_init(large_number);
//    
//    paillier_encrypt(large_number, EXTREMELY_LARGE_NUMBER, pub);
//    int i,hi;
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){
//            paillier_homomorphic_add(*(N_out + i*H + hi), *(N_in + i*H + hi), *(M + i*H + hi), pub);
//            paillier_homomorphic_sub(*(N_out + i*H + hi), *(N_out + i*H + hi), large_number, pub);
//        }
//    }    
//    return 0;
//}
//
//int cal_Interference_Budget(mpz_t *G, const mpz_t *N, const mpz_t *I, const mpz_t *R, paillier_public_key *pub){
//    
//    int i,hi,j,hs;
//    mpz_t temp;
//    mpz_init(temp);
//    mpz_t sum, zero;
//    mpz_init(sum);
//    mpz_init_set_si(zero, 0);
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){            
//            mpz_init(*(G + i*H_I + hi));   
//            paillier_encrypt(sum, zero, pub);
//            for(j = 0; j < L; j++){
//                for(hs = 0; hs < H; hs++){
//                        paillier_homomorphic_multc(temp, *(R + j*H + hs), *(I+offset(i, hi, j, hs)), pub);   
//                        paillier_homomorphic_add(sum, sum, temp, pub);                             
//                }
//            }
//            paillier_homomorphic_sub(*(G + i*H + hi), *(N + i*H + hi), sum, pub);         
////            mpz_t de;
////            mpz_init(de);
////            FILE *private_key = fopen("./priv2048", "r");
////            paillier_private_key priv;
////            paillier_private_init(&priv);
////            paillier_private_in_str(&priv, private_key);
////            fclose(private_key);
////            paillier_decrypt(de, G[i][hi], &priv);
////            gmp_printf("%Zx\n", de);
////            paillier_decrypt(de, N[i][hi], &priv);
////            gmp_printf("%Zx\n", de);
//        }
//    }  
//    return 0;
//}
//
//int cal_Interference_Budget_optimised_linkedlist(mpz_t *G, const mpz_t *N, const struct Node ** I_optimized, const mpz_t *R, paillier_public_key *pub){
//    
//    int i,hi,j,hs;
//    mpz_t temp;
//    mpz_init(temp);
//    
//    mpz_t multi;
//    mpz_init(multi);
//    
//    mpz_t sum;
//    mpz_init(sum);
//
//    
//    struct Node *head;
//    struct node *node;
//    
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){ 
//            printf("$  %d   %d \n", i, hi);
//            mpz_init(*(G + i*H_I + hi));   
//            paillier_encrypt(sum, ZERO, pub);
//            struct Node *head;
//            head = *(I_optimized + i*H_I + hi);
//            while(head != NULL){
////                gmp_printf("#  %Zx\n",multi);
//                mpz_set(multi, head->value);
//                node = head->idx;
//                paillier_encrypt(temp, ZERO, pub);
//                while(node != NULL){
//                    paillier_homomorphic_add(temp, temp, *(R + node->location *H_S + node->height), pub);
////                    printf("   %d   %d \n", node->location, node->height);
////                    gmp_printf("%Zx\n", *(R + node->location * H_S + node->height));
//                    node=node->next;
//                    
//                }
//                paillier_homomorphic_multc(temp, temp, multi, pub);
//                
//                paillier_homomorphic_add(sum, sum, temp, pub);  
//                head = head->next;
//            }
//               
//            paillier_homomorphic_sub(*(G + i*H + hi), *(N + i*H + hi), sum, pub);         
////            mpz_t de;
////            mpz_init(de);
////            FILE *private_key = fopen("./priv2048", "r");
////            paillier_private_key priv;
////            paillier_private_init(&priv);
////            paillier_private_in_str(&priv, private_key);
////            fclose(private_key);
////            paillier_decrypt(de, G[i][hi], &priv);
////            gmp_printf("%Zx\n", de);
////            paillier_decrypt(de, N[i][hi], &priv);
////            gmp_printf("%Zx\n", de);
//        }
//    }  
//    return 0;
//}
//
//int cal_Interference_Budget_optimised_array(mpz_t *G, const mpz_t *N, const mpz_t *Value, const int *Idx, const mpz_t *R, paillier_public_key *pub){
//    
//    int i,hi,j,hs,k,h;
//    int Loc;
//    int LLoc;
//    mpz_t temp;
//    mpz_init(temp);
//    
//    mpz_t multi;
//    mpz_init(multi);
//    
//    mpz_t sum;
//    mpz_init(sum);
//
//    mpz_t ZERO_en;
//    mpz_init(ZERO_en);
//    paillier_encrypt(ZERO_en, ZERO, pub);
//
//    
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){ 
////            printf("$  %d   %d \n", i, hi);
//            mpz_init(*(G + i*H_I + hi));   
//            mpz_set(sum, ZERO_en);
//            
//            LLoc = i * (H * MAX_LENGTH_I_MAP_ROW) + hi * (MAX_LENGTH_I_MAP_ROW) ;
//            Loc = i * (H * MAX_LENGTH_I_MAP_ROW*MAX_LENGTH_I_MAP_COL) + hi * (MAX_LENGTH_I_MAP_ROW*MAX_LENGTH_I_MAP_COL);
//            
//            k=0;
//            while(1){
//                mpz_set(multi, *(Value + LLoc + k));
//                if(mpz_cmp_ui(multi, 0)==0){
//                    break;
//                }
//                mpz_set(temp, ZERO_en);                
////                printf("# %d \n", *(Idx + Loc + 0));
//                for(h=1; h <= *(Idx + Loc + k*MAX_LENGTH_I_MAP_COL + 0); h++){
////                    printf("# %d \n", h);
//                    paillier_homomorphic_add(temp, temp, *(R + *(Idx + Loc + k*MAX_LENGTH_I_MAP_COL + h)), pub);
//                }
//                paillier_homomorphic_multc(temp, temp, multi, pub);
//                paillier_homomorphic_add(sum, sum, temp, pub);  
//                k++;
//            }
//            paillier_homomorphic_sub(*(G + i*H + hi), *(N + i*H + hi), sum, pub); 
//           
//        }
//    }  
//    return 0;
//}
//
//int generate_F(mpz_t *F, const int *I, const mpz_t *R, paillier_public_key *pub){
//    
//    int i,hi;
//    int k = 0;
//    int count = 0;
//    
//    
//    mpz_t ZERO_en;
//    mpz_init(ZERO_en);
//    paillier_encrypt(ZERO_en, ZERO, pub);
//    
//    mpz_t sum, temp;
//    mpz_init(sum);
//    mpz_init(temp);
//    mpz_set(sum, ZERO_en);
//    
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H; hi++){ 
//            mpz_init(*(F + i*H_I + hi));             
//        }
//    }  
//    
//    
//    while(k < I_Line_length-1){
//        if(*(I+k+1) == -1){
//            mpz_set(*(F + count), sum);
////            gmp_printf("%Zx\n", sum);
//            mpz_set(sum, ZERO_en);
//            count ++;
//            k++;
//        }
//        
//        mpz_t value;
//        mpz_init_set_ui(value, *(I+k+1));
//        k = k+2;
//        mpz_set(temp, ZERO_en);
//        while(*(I+k) != -1){           
//            paillier_homomorphic_add(temp, temp, *(R + *(I+k)), pub);
////            if(*(I+k)==0){
////                gmp_printf("%Zx\n", temp);
////                gmp_printf("%Zx\n", value);
////                printf("%d\n", k);
////            }
//            k++;
//        }        
//        paillier_homomorphic_multc(temp, temp, value, pub);                
//        paillier_homomorphic_add(sum, sum, temp, pub);
////        gmp_printf("%Zx\n", sum);
//    }
//    mpz_set(*(F + count), sum);
//}
//int generate_G(mpz_t *G_en, const mpz_t *N_en, mpz_t *F_en, paillier_public_key *pub){
////    int i,hi;
////    for(i = 0; i < L; i++){
////            for(hi = 0; hi < H_I; hi++){ 
////                mpz_init(*(G_en + i*H_I + hi)); 
////                paillier_homomorphic_sub(*(G_en + i*H_I + hi), *(N_en + i*H_I + hi), *(F_en + i*H_I + hi), pub);    
////            }
////    }            
//    return 0;
//}
//
//
//
//
//int obfuscate_Sign(mpz_t *X, mpz_t *gamma, const mpz_t *G, paillier_public_key *pub){
//    
////    int i, hi;
////    mpz_t alpha, beta, beta_en;
////    mpz_init(alpha);
////    mpz_init(beta);
////    mpz_init(beta_en);
////    int a;
////    
////    for(i = 0; i < L; i++){
////        for(hi = 0; hi < H_I; hi++){                        
////            mpz_init(*(X + i*H_I + hi));
////            mpz_init(*(gamma + i*H_I + hi));
////     
////            while(mpz_cmp(alpha, beta) <= 0){
////                gen_pseudorandom(alpha, RAND_LENGTH);        
////                gen_pseudorandom(beta, RAND_LENGTH);
////            }
////
////            paillier_encrypt(beta_en, beta, pub);
////
////            a = rand()%2*2-1;    
////            mpz_set_si(*(gamma + i*H_I + hi), a);
////
////            paillier_homomorphic_multc(*(X + i*H_I + hi), *(G + i*H_I + hi), alpha, pub);
////            paillier_homomorphic_sub(*(X + i*H_I + hi), *(X + i*H_I + hi), beta_en, pub);
////            paillier_homomorphic_multc(*(X + i*H_I + hi), *(X + i*H_I + hi), *(gamma + i*H_I + hi), pub);
////        }
////    }
//    
//    return 0;
//}
//
//int calc_Q(mpz_t Q, const mpz_t *gamma, const mpz_t *Y, paillier_public_key *pub){
//    
////    mpz_init(Q);
////    mpz_t temp, one_en;
////    mpz_init(temp);
////    mpz_init(one_en);
////    
////    paillier_encrypt(one_en, ONE, pub);
////    paillier_encrypt(Q, ZERO, pub);
////
////    int i,hi;
////       
//////    FILE * fout;
//////    fout = fopen("out_q","w");
//////    mpz_t test;
//////    mpz_init(test);
////    
////    
////    for(i = 0; i < L; i++){
////        for(hi = 0; hi < H_I; hi++){
////            paillier_homomorphic_multc(temp, *(Y + i*H_I + hi), *(gamma + i*H_I + hi), pub);
////            paillier_homomorphic_sub(temp, temp, one_en, pub);
////            
//////            paillier_decrypt(test, temp, priv);   
//////            gmp_fprintf (fout, "%Zx\n", test);
////           
////            paillier_homomorphic_add(Q, Q, temp, pub);
////        }
////    }
//    
////    fclose(fout);
//    
//    return 0;
//}
//
//int update_N(mpz_t *N_en, mpz_t *U, paillier_public_key *pub){
//    int i,hi;
//    for(i = 0; i < L; i++){
//            for(hi = 0; hi < H; hi++){                 
//                paillier_homomorphic_sub(*(N_en + i*H + hi), *(N_en + i*H + hi), *(U + i*H + hi), pub);
//            }
//    }
//}