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


int main(){

//    benchmark(); //benchmark for Paillier cryptosystem
    
    // Initialization
    clock_t tic, toc; //timer
    srand(time(NULL)); // used for generating random numbers
        
    mpz_init_set_ui(TEN, 10);
    mpz_init_set_ui(ONE, 1);
    mpz_init_set_ui(ZERO, 0);
    
    
    FILE *public_key = fopen("./pub2048", "r");
    paillier_public_key pub; // use &pub in main file
    get_pub_Keys(&pub, public_key);  
    fclose(public_key);
//    gmp_printf("%Zd\n",pub.n);
//    printf("%d\n",pub.len);
    
    /**************************************************/ 
    //                     PU                          //
    /**************************************************/ 
    mpz_t *N_enc;
    N_enc=aggregation(&pub);
    
    //testing
//    int l, h, f;
//    mpz_t temp;
//    mpz_init(temp);
//    
//    FILE *private_key = fopen("./priv2048", "r");
//    paillier_private_key priv;
//    paillier_private_init(&priv);
//    paillier_private_in_str(&priv, private_key);
//    fclose(private_key);
//    
//    for(l = 0; l < L; l++){               
//        for(h = 0; h < H; h++){
//            for(f = 0; f < F; f++){                   
//                paillier_decrypt(temp, *(N_enc + offset(l,h,f)), &priv);           
//                gmp_printf("%Zd\n", temp);
//            }
//        }
//    }
    
    

    /**************************************************/ 
    //                     SU                          //
    /**************************************************/ 
    mpz_t * R_enc;
    R_enc=gen_req(&pub);
    
    //testing
//    int l, h, f;
//    mpz_t temp;
//    mpz_init(temp);
//    
//    FILE *private_key = fopen("./priv2048", "r");
//    paillier_private_key priv;
//    paillier_private_init(&priv);
//    paillier_private_in_str(&priv, private_key);
//    fclose(private_key);
//    
//    for(l = 0; l < L; l++){               
//        for(h = 0; h < H; h++){
//            for(f = 0; f < F; f++){                   
//                paillier_decrypt(temp, *(R_enc + offset(l,h,f)), &priv);           
//                gmp_printf("%Zd\n", temp);
//            }
//        }
//    }
    
    
    /**************************************************/ 
    //                     SAS                         //
    /**************************************************/ 
    
    
    // ************* Preparing I ***********************//

    mpz_t *I = get_I();
    
//    FILE *fp1;
//    fp1 = fopen("I_MAP_100", "r");
////    fp = fopen("I_MAP_10000", "r");
//    read_I(I, fp1);
//    fclose(fp1);
 
//    mpz_t *Value = (mpz_t *) malloc(L * H_I * MAX_LENGTH_I_MAP_ROW *sizeof (mpz_t));
//    int *Idx = (int *)malloc(L * H_I * MAX_LENGTH_I_MAP_ROW * MAX_LENGTH_I_MAP_COL * sizeof(int));
//    optimize_I_array(Value, Idx, I);      
//    mpz_t *G_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));
//    cal_Interference_Budget_optimised_array(G_en, N_en, Value, Idx, R_en, &pub);
//    // LinkedList -- abandoned
////    struct Node ** I_optimized = (struct Node**) malloc(L * H_I * sizeof (struct Node*));
////    optimize_I_linkedlist(I_optimized, I);    
    

//    int *I_line = (int *)malloc(I_Line_length*sizeof(int));
//    FILE *fp;
//    fp = fopen("myfile.txt", "r");
//    read_I_line(I_line,fp);
//    fclose(fp);
      
    
    // *************Response***********************//
    mpz_t *G_enc;
    G_enc = cal_Interference_Budget(N_enc, I, R_enc, &pub);
    //testing
//    int l, h, f;
//    mpz_t temp;
//    mpz_init(temp);
//    
//    FILE *private_key = fopen("./priv2048", "r");
//    paillier_private_key priv;
//    paillier_private_init(&priv);
//    paillier_private_in_str(&priv, private_key);
//    fclose(private_key);
    
//    for(l = 0; l < L; l++){               
//        for(h = 0; h < H; h++){
//            for(f = 0; f < F; f++){                   
//                paillier_decrypt(temp, *(G_enc + offset(l,h,f)), &priv);           
//                gmp_printf("%Zd\n", temp);
//            }
//        }
//    }
    
    
    
    

//    mpz_t *F_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));    
//    mpz_t *G_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));       
//    tic = clock();
//    generate_F(F_en, I_line, R_en, &pub);
//    generate_G(G_en, N_en, F_en, &pub);
//    toc = clock();
//    printf ("SAS interference calculation (improved) takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);

    
    
    // ************* Obfuscation ***********************//
    mpz_t * epsilon=get_epsilon();
    
    //testing
    int l, h, f;
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
             for(f = 0; f < F; f++){                   
                gmp_printf("%Zd\n", *(epsilon + offset(l,h,f)));
            }
        }
    }
    
//    obfuscate(X_en, gamma, G_en, &pub);  
//    printf ("SAS interference calculation (rest) takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
    
 
    
    
      
    /**************************************************/ 
    //                 Key_converter                  //
    /**************************************************/ 
//   
//    FILE *su_public_key, *su_private_key;
//    paillier_public_key su_pub;
//    paillier_private_key su_priv;
//    paillier_public_init(&su_pub);
//    paillier_private_init(&su_priv);
//    su_public_key = fopen("./su_pub2048", "r");
//    su_private_key = fopen("./su_priv2048", "r");
//    paillier_public_in_str(&su_pub, su_public_key);
//    paillier_private_in_str(&su_priv, su_private_key);
//    fclose(su_public_key);
//    fclose(su_private_key);
//    
//    FILE *private_key = fopen("./priv2048", "r");
//    paillier_private_key priv;
//    paillier_private_init(&priv);
//    paillier_private_in_str(&priv, private_key);
//    fclose(private_key);
//    
//   
//    
//    
//    
////    FILE * fout1;
////    fout1 = fopen("out1","w");
////    mpz_t test1;
////    mpz_init(test1);
////    for (i=0;i<L;i++){
////        for(j=0;j<H_I;j++){
////            paillier_decrypt(test1, *(G_en1 + i*H_I + j), &priv);   
////            gmp_fprintf (fout1, "%Zx\n", test1);
////        } 
////    }
////    fclose(fout1);
////    
////    FILE * fout;
////    fout = fopen("out","w");
////    mpz_t test;
////    mpz_init(test);
////
////    for (i=0;i<L;i++){
////        for(j=0;j<H_I;j++){
////            paillier_decrypt(test, *(G_en + i*H_I + j), &priv);   
////            gmp_fprintf (fout, "%Zx\n", test);
////        }
////    }
////    fclose(fout);
//    
//    
//      
//    
//    
//    // Key Conversion
//    
//    mpz_t *Y_en_su = (mpz_t *)malloc(L*H_I*sizeof(mpz_t));      
//    tic = clock();
//    Key_conversion(Y_en_su, X_en, &priv, &su_pub); // use su_pub afterwards
//    toc = clock();
//    printf ("Key conversion takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    /**************************************************/ 
//    //                     SAS                         //
//    /**************************************************/ 
//    
//    // Calculate Q
//    
//    mpz_t Q_en_su;
//    mpz_init(Q_en_su);
//    tic = clock();
//    calc_Q(Q_en_su, gamma, Y_en_su, &su_pub);        
//    toc = clock();
//    printf ("SAS license response takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    /**************************************************/ 
//    //                     SU                          //
//    /**************************************************/ 
//    
//    mpz_t temp;
//    mpz_init(temp);
//    tic = clock();
//    paillier_decrypt(temp, Q_en_su, &su_priv); 
//    toc = clock();
//    int available = 0;
//    if(mpz_cmp_ui(temp, 0) == 0){    
//        available = 1;        
//    }
//    gmp_printf("%Zx\n\n", temp);
//    printf("%d\n", available);
//    
//    printf ("SU decryption takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    mpz_t *U = (mpz_t *)malloc(L*H_I*sizeof(mpz_t));    
//    tic = clock();
//    generate_U(U, available, F_en, &pub);
//    toc = clock();
//    printf ("SU generate U takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    /**************************************************/ 
//    //                     SAS                          //
//    /**************************************************/ 
//    tic = clock();
//    update_N(N_en, U, &pub);
//    toc = clock();
//    printf ("SAS update N takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC); 
   
    return 0;
}

