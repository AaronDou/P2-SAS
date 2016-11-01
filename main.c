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
    
//    struct Pos_Value* pv=PU_data_generation_coordination();
//    mpz_t *T_i_encrypted;
//    T_i_encrypted=PU_i_update(pv, &pub);
//    print_mpz_array(T_i_encrypted);
    
//    int i;
//    for( i=0; i<PU_NUM; i++ )
//        printf("%i\n",(*(pv+i)).pos);
//    mpz_t test;
//    mpz_init(test);
//    mpz_set_ui(test,2);
//    int a=mpz_tstbit(test,0);
//    printf("%d\n",a);
//    mpz_setbit (test, 280);
//    gmp_printf("%Zx",test);
    //print_mpz_array(T_encrypted);
    
//    for (int pu_i = 0; pu_i < PU_NUM; pu_i++){
//        
//    }
//    Ti = PU_updates(&pub);
//    PU(T_encrypted, &pub); // Generate PU input data T
    
    
    
    
    
    
    
    
    
    /**************************************************/ 
    //                     SU                          //
    /**************************************************/ 
//    tic = clock();
//    mpz_t *R_en = (mpz_t *)malloc(L*H_S*sizeof(mpz_t));
//    gen_req(R_en, &pub);
//    toc = clock();
//    printf ("SU request generation takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    
//    
//    /**************************************************/ 
//    //                     SAS                         //
//    /**************************************************/ 
//    
//    
//    // *************Initialization***********************//
//    tic = clock();
//    mpz_t *N_en = (mpz_t *)malloc(L*H_I*sizeof(mpz_t));
//    initialize_N(N_en, &pub);
//    update_PU(N_en, N_en, T_encrypted, &pub);
//    int i,j;
//    
//
//    mpz_t *I = (mpz_t *)malloc(L*H_I*L*H_S*sizeof(mpz_t));   
//    FILE *fp1;
//    fp1 = fopen("I_MAP_100", "r");
////    fp = fopen("I_MAP_10000", "r");
//    read_I(I, fp1);
//    fclose(fp1);
// 
////    mpz_t *Value = (mpz_t *) malloc(L * H_I * MAX_LENGTH_I_MAP_ROW *sizeof (mpz_t));
////    int *Idx = (int *)malloc(L * H_I * MAX_LENGTH_I_MAP_ROW * MAX_LENGTH_I_MAP_COL * sizeof(int));
////    optimize_I_array(Value, Idx, I);      
////    mpz_t *G_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));
////    cal_Interference_Budget_optimised_array(G_en, N_en, Value, Idx, R_en, &pub);
////    // LinkedList -- abandoned
//////    struct Node ** I_optimized = (struct Node**) malloc(L * H_I * sizeof (struct Node*));
//////    optimize_I_linkedlist(I_optimized, I);    
//    
//
//    int *I_line = (int *)malloc(I_Line_length*sizeof(int));
//    FILE *fp;
//    fp = fopen("myfile.txt", "r");
//    read_I_line(I_line,fp);
//    fclose(fp);
//    
//    toc = clock();
//    printf ("SAS initialization takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    
//    
//    
//    // *************Response***********************//
//    mpz_t *G_en1 = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));
//    tic = clock();
//    cal_Interference_Budget(G_en1, N_en, I, R_en, &pub);
//    toc = clock();
//    printf ("SAS interference calculation (raw) takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//
//    mpz_t *F_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));    
//    mpz_t *G_en = (mpz_t *) malloc(L * H_I * sizeof (mpz_t));       
//    tic = clock();
//    generate_F(F_en, I_line, R_en, &pub);
//    generate_G(G_en, N_en, F_en, &pub);
//    toc = clock();
//    printf ("SAS interference calculation (improved) takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    
//    tic = clock();
//    mpz_t *X_en = (mpz_t *)malloc(L*H_I*sizeof(mpz_t));    
//    mpz_t *gamma = (mpz_t *)malloc(L*H_I*sizeof(mpz_t));     
//    obfuscate_Sign(X_en, gamma, G_en, &pub);  
//    toc = clock();
//    printf ("SAS interference calculation (rest) takes %f seconds\n", (float)(toc-tic)/CLOCKS_PER_SEC);
//    /**************************************************/ 
//    //                 Key_converter                  //
//    /**************************************************/ 
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

