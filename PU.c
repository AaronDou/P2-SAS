#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include <time.h>
#include "declaritions.h"




mpz_t * PU_i_update(struct Pos_Value *pv, paillier_public_key *pub){
  
    int l, h, f;
    mpz_t *T_i = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    mpz_t *T_i_encrypted = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){               
                if (offset(l,h,f)==pv->pos){
                    mpz_t temp, W, V, WplusZ, Z; 
                    mpz_inits(temp, W, V, WplusZ, Z, NULL);
                    
                    mpz_setbit (temp, PSI+K); //set 60+220=280th bit to the right as 1
                    mpz_set_ui(V, pv->value);
                    mpz_add(WplusZ, temp, V);
//                    gmp_printf("%Zd\n%Zd\n%Zd",V,temp,WplusZ);
                    mpz_setbit(Z,K-1);
                    mpz_sub_ui(Z,Z,1);
                    mpz_sub(W,WplusZ,Z);
                    mpz_init_set(*(T_i+offset(l,h,f)), W);
//                    gmp_printf("%Zd\n%Zd\n%Zd",WplusZ,Z,W);
                    mpz_clears(temp, W, V, WplusZ, Z, NULL);
                }
                else{
                    mpz_init_set_ui(*(T_i+offset(l,h,f)), 0);
                }
                mpz_init(*(T_i_encrypted+offset(l,h,f)));
//                gmp_printf("%Zd\n", *(T_i+offset(l,h,f)));
                paillier_encrypt(*(T_i_encrypted+offset(l,h,f)), *(T_i+offset(l,h,f)), pub);
            }
        }
    }
//    print_mpz_array(T_i);
    return T_i_encrypted;
}

struct Pos_Value* PU_data_generation_coordination(){//randomized data
    
    struct Pos_Value* pv = (struct Pos_Value *) malloc(sizeof(struct Pos_Value)*PU_NUM);
    srand(time(NULL));
    
    int *value=generate_random_array_no_reps(F*H*L, 0, PU_NUM);     
    int pu_i;
    for( pu_i=0; pu_i<PU_NUM; pu_i++ ){
        (*(pv + pu_i)).pos = *(value+pu_i);
//        printf("%d\n",*(value+pu_i));
        (*(pv + pu_i)).value = rand()%(MAX_SENSITIVITY-MIN_SENSITIVITY)+MIN_SENSITIVITY;
    }
    return pv;
}

