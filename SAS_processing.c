#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "paillier.h"
#include "Parameters.h"
#include <time.h>
#include "tools.h"
#include "declaritions.h"
#include <sys/time.h>
#include <stdbool.h>

int SAS_processing(mpz_t * N_enc, mpz_t * R_enc, paillier_public_key *pub){
    /**************************************************/ 
    //                     SAS                         //
    /**************************************************/ 
    if (debug == true){
        printf("\n\n******     Debugging mode: print entries of I **********\n\
               x axis is SU, y axis is PU\n\n");
    }
    mpz_t *I = get_I();
   
    
    // *************Response***********************//
    mpz_t *G_enc;
    mpz_t *F_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    
    G_enc = cal_Interference_Budget(N_enc, F_enc, I, R_enc, pub);
    //testing
    
    if (debug == true){
        printf("\n\n******     Debugging mode: print entries of F **********\n\n");
    
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);

        FILE *private_key = fopen("./priv2048", "r");
        paillier_private_key priv;
        paillier_private_init(&priv);
        paillier_private_in_str(&priv, private_key);
        fclose(private_key);

        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){                   
                    paillier_decrypt(temp, *(F_enc + offset(l,h,f)), &priv);           
                    gmp_printf("%Zd\n", temp);
                }
            }
        }
    }
    if (debug == true){
        printf("\n\n******     Debugging mode: print sign bit of entries of G **********\n\n");
    
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);

        FILE *private_key = fopen("./priv2048", "r");
        paillier_private_key priv;
        paillier_private_init(&priv);
        paillier_private_in_str(&priv, private_key);
        fclose(private_key);

        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){                   
                    paillier_decrypt(temp, *(G_enc + offset(l,h,f)), &priv);           
                    printf("%d\n", mpz_tstbit(temp, PSI+K-1));
                }
            }
        }
    }



    
    
    // ************* Obfuscation ***********************//
    int * epsilon=get_epsilon();// epsilon randomly draws values from {0,1}. if epsilon==0, flip sign of formula (14). 
    
    if (debug == true){
        printf("\n\n******     Debugging mode: print entries of epsilon **********\n\n");
        
        int l, h, f;
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                 for(f = 0; f < F; f++){                   
                    printf("%d\n", *(epsilon + offset(l,h,f)));
                }
            }
        }
    }
    
    
    mpz_t* X_enc;
    X_enc = obfuscate(epsilon, G_enc, pub);  
    
    if (debug == true){
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);

        FILE *private_key = fopen("./priv2048", "r");
        paillier_private_key priv;
        paillier_private_init(&priv);
        paillier_private_in_str(&priv, private_key);
        fclose(private_key);
        
        printf("\n\n******     Debugging mode: print sign bit of entries in X **********\n\n");
        
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    paillier_decrypt(temp, *(X_enc + offset(l,h,f)), &priv);  
//                    gmp_printf("%Zd\n", temp);
                    printf("%d\n", mpz_tstbit(temp, PSI+K-1));
                }
            }
        }
    }
    
    
      
    /**************************************************/ 
    //                 Key_converter                  //
    /**************************************************/ 
   
    FILE *su_public_key, *su_private_key;
    paillier_public_key su_pub;
    paillier_private_key su_priv;
    paillier_public_init(&su_pub);
    paillier_private_init(&su_priv);
    su_public_key = fopen("./su_pub2048", "r");
    su_private_key = fopen("./su_priv2048", "r");
    paillier_public_in_str(&su_pub, su_public_key);
    paillier_private_in_str(&su_priv, su_private_key);
    fclose(su_public_key);
    fclose(su_private_key);
    
    FILE *private_key = fopen("./priv2048", "r");
    paillier_private_key priv;
    paillier_private_init(&priv);
    paillier_private_in_str(&priv, private_key);
    fclose(private_key);    
    
    // Key Conversion
    
    mpz_t *Y_enc_su = Key_conversion(X_enc, &priv, &su_pub); // use su_pub afterwards
     //testing
    if (debug == true){
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);  
        printf("\n\n******     Debugging mode: print entries of Y **********\n\n");
        
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    paillier_decrypt(temp, *(Y_enc_su + offset(l,h,f)), &su_priv);           
                    gmp_printf("%Zd\n", temp);
                }
            }
        }
    }
    
        
    /**************************************************/ 
    //                     SAS                         //
    /**************************************************/ 
    
    // Calculate Q
    
    mpz_t *Q_enc_su = calc_Q(epsilon, Y_enc_su, &su_pub);        

    if (debug == true){
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);  
        printf("\n\n******     Debugging mode: print entries of Q **********\n\n");
        
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    paillier_decrypt(temp, *(Q_enc_su + offset(l,h,f)), &su_priv);           
                    gmp_printf("%Zd\n", temp);
                }
            }
        }
    }
    
    mpz_t *D_enc_su = calc_D(Q_enc_su, &su_pub);
    if (debug==true){
        
        printf("\n\n******     Debugging mode: print D **********\n\n");
        mpz_t temp;
        mpz_init(temp);
        paillier_decrypt(temp, *(D_enc_su), &su_priv);           
        gmp_printf("%Zd\n", temp);

    }
    /**************************************************/ 
    //                     SU                          //
    /**************************************************/ 
    
    mpz_t result;
    mpz_init(result);
    paillier_decrypt(result, D_enc_su, &su_priv); 
    bool availability=false;
    
    mpz_t verify;
    mpz_init_set_str(verify,\
                    "6f7df91d8f973a0619d525c319337741130b77b21f9667dc7d1d74853b644cbe\
                    5e6b0e84aacc2faee883d43affb811fc653b67c38203d4f206d1b838c4714b6b\
                    2cf17cd621303c21bac96090df3883e58784a0576e501c10cdefb12b6bf887e5\
                    48f6b07b09ae80d8416151d7dab7066d645e2eee57ac5f7af2a70ee0724c8e47",16);
    
    if (mpz_cmp(result, verify)==0){
        availability=true;
        printf("Spectrum is available to use.\n\n");
    }
    else{
        printf("Spectrum is unavailable to use.\n\n");
    }
    
 
    
    mpz_t *U_enc = generate_U(availability, F_enc, pub);

    /**************************************************/ 
    //                     SAS                          //
    /**************************************************/ 
    
    update_N(N_enc, U_enc, pub);

    
    if (debug==true){
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);  
        printf("\n\n******     Debugging mode: print entries of updated N **********\n\n");
    
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){                   
                    paillier_decrypt(temp, *(N_enc + offset(l,h,f)), &priv);           
                    gmp_printf("%Zd\n", temp);
                }
            }
        }
    }
}