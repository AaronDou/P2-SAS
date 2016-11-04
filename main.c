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



int main(){

//    benchmark(); //benchmark for Paillier cryptosystem

    
    // Initialization
    clock_t tic, toc; //timer
    srand(time(NULL)); // used for generating random numbers
        
    mpz_init_set_ui(TEN, 10);
    mpz_init_set_ui(ONE, 1);
    mpz_init_set_ui(ZERO, 0);
    mpz_init(Z);
    mpz_setbit(Z,K-1);
    mpz_sub_ui(Z,Z,1);
    
    
    
    FILE *public_key = fopen("./pub2048", "r");
    paillier_public_key pub; // use &pub in main file
    get_pub_Keys(&pub, public_key);  
    fclose(public_key);

    
    /**************************************************/ 
    //       PUs submit operation data to SAS         //
    /**************************************************/ 
    mpz_t *N_enc;
    N_enc=aggregation(&pub);
    
    //debug
    if (debug == true){
        int l, h, f;
        mpz_t temp;
        mpz_init(temp);

        FILE *private_key = fopen("./priv2048", "r");
        paillier_private_key priv;
        paillier_private_init(&priv);
        paillier_private_in_str(&priv, private_key);
        fclose(private_key);
        
        printf("\n\n******     Debugging mode: print entries of N **********\n\n");
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){                   
                    paillier_decrypt(temp, *(N_enc + offset(l,h,f)), &priv);           
                    gmp_printf("%Zd\n", temp);
                }
            }
        }
    }


    /**************************************************/ 
    //  SUs send spectrum access request to SAS       //
    /**************************************************/ 
    int i;
    for(i=0; i<SU_NUM; i++){
        mpz_t * R_enc;
        R_enc=gen_req(&pub);

        //debug
        if (debug == true){
            int l, h, f;
            mpz_t temp;
            mpz_init(temp);
            FILE *private_key = fopen("./priv2048", "r");
            paillier_private_key priv;
            paillier_private_init(&priv);
            paillier_private_in_str(&priv, private_key);
            fclose(private_key);

            printf("\n\n******     Debugging mode: print entries of R **********\n\n");
            for(l = 0; l < L; l++){               
                for(h = 0; h < H; h++){
                    for(f = 0; f < F; f++){                   
                        paillier_decrypt(temp, *(R_enc + offset(l,h,f)), &priv);           
                        gmp_printf("%Zd\n", temp);
                    }
                }
            }
        }

        SAS_processing(N_enc, R_enc, &pub);
    }

    
    
    
//    tic = clock();
//    toc = clock();
//    printf ("SAS update N takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC); 
   
    return 0;
}

