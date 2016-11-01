
/* 
 * File:   read_I.c
 * Author: yanzhi
 *
 * Created on January 5, 2014, 7:57 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include "Parameters.h"
#include "paillier.h"
#include <string.h>
#include <math.h>
#include "linked_list.h"

//int read_I(mpz_t *I, FILE *fp){
//    int i,hi,j,hs;
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H_I; hi++){           
//            for(j = 0; j < L; j++){
//                for(hs = 0; hs < H_S; hs++){                    
//                        mpz_init(*(I + offset(i, hi, j, hs)));                    
//                }
//            }
//        }
//    }
//    if (fp == NULL){
//        printf("Cannot open the file!");
//        exit(EXIT_FAILURE);
//    }
//    int Buff = 255;
//    char str[Buff];
//    char * token;
//    const char s[2]=" ";
//    char temp[5][20];
//    int num = 0;
//    while( fgets (str, Buff, fp)!=NULL ) {        
////        printf("%s\n",str);        
//        token = strtok(str, s);    
//        int i = 0;
//        while( token != NULL ) 
//        {
//            strcpy(temp[i], token);
////            printf( " %s\n", temp[i] );
//            token = strtok(NULL, s);
//            i++;
//        }       
////        printf("%f\n", atof(temp[5]));
//        double tx_power = atof(temp[4]);
////        printf("%f\n",tx_power);
//        int b;
//
//        if(tx_power==0){
//            b = pow(10, 8);
//        }
//        else{
//            double c =17+tx_power/10*(-1);
//            b = (int)ceil(pow(10, c));
//        }
//
//        
////        printf("%d %d %d %d %d\n", atoi(temp[0]), atoi(temp[1]),atoi(temp[2]),atoi(temp[3]), b);
////        printf("%f\n", tx_power);
//        mpz_set_ui(*(I + offset(atoi(temp[0]), atoi(temp[1]), atoi(temp[2]), atoi(temp[3]))), b);   
//        num++;
////        if(num%10000==0){
////            printf("%d\n", num);
////        }
//        
//        
//    }
//
////    for(i = 0; i < L; i++){
////        for(hi = 0; hi < H_I; hi++){           
////            for(j = 0; j < L; j++){
////                for(hs = 0; hs < H_S; hs++){    
////                    printf("%d %d %d %d \n", j ,i, hs, hi);
////                        gmp_printf("%Zx\n", I[i][hi][j][hs]);     
////                }
////            }
////        }
////    }
//    return 0;
//}
//
//int read_I_line(int *I, FILE *fp){
//    char buf[20];
//
//    if (!fp)
//        return 1;
//    int i=0;
//    while (fgets(buf,1000, fp)!=NULL){
//        *(I + i) = atoi(buf);     
////        printf("%s",buf);
////        printf("%d\n",*(I + i));
//        i++;
//    }
//    printf("%d\n", i);
//    return 0;
//}
//
//
//int optimize_I_linkedlist(struct Node ** I_optimized, mpz_t *I){
//    
//    
//    int i,hi,j,hs;
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H_I; hi++){  
////            printf("$  %d   %d \n", i, hi);
//            *(I_optimized + i*H_I + hi) = NULL;
//            for(j = 0; j < L; j++){
//                for(hs = 0; hs < H_S; hs++){
//                    
//                    if(mpz_cmp_ui(*(I + offset(i, hi, j, hs)), 0) != 0){
////                        gmp_printf("%Zx\n", *(I + offset(i, hi, j, hs)));
//                        struct Node *temp = *(I_optimized + i*H_I + hi);
//                        int y=0;
//                        while(temp != NULL){
////                            printf("%p\n", *(I_optimized+ i*H_I + hi));
//                            if(mpz_cmp(temp->value, *(I + offset(i, hi, j, hs)))==0){
////                                printf("  %d   %d \n", j, hs);
//                                add_node(j, hs, temp);
//                                y=1;
////                                temp = *(I_optimized + i*H_I + hi);
////                                gmp_printf("%Zx\n", temp->value);
//                            }
//                            temp = temp->next;
//                        }
//                        if(y==0){
////                            printf("%p\n", *(I_optimized+ i*H_I + hi));
//                            *(I_optimized + i*H_I + hi) = add_Node(*(I + offset(i, hi, j, hs)), *(I_optimized + i*H_I + hi));
//                            add_node(j, hs, *(I_optimized + i*H_I + hi));
////                            printf("  %d   %d \n", j, hs);
////                            gmp_printf("%Zx\n", *(I_optimized+ i*H_I + hi)->value);
////                            gmp_printf("%Zx\n", *(I_optimized + i*H_I + hi)->value);
//                            
//                        }
//                                                           
//                    }
//                }
//            }
//        }
//    }
//    
//}
//int optimize_I_array(mpz_t *Value, int * Idx,const mpz_t *I){
//    int i,hi,j,hs,k,p,h,e;
//    int Loc, LLoc;
//    mpz_t temp;
//    mpz_init(temp);
//    for(i = 0; i < L; i++){
//        for(hi = 0; hi < H_I; hi++){
////            printf("\n$  %d   %d \n", i, hi);
//            for(k = 0; k < MAX_LENGTH_I_MAP_ROW; k++){
//                mpz_init(*(Value + i * (H_I * MAX_LENGTH_I_MAP_ROW) + hi * (MAX_LENGTH_I_MAP_ROW) + k));
//            }
//            e=0;
//            Loc = i * (H_I * MAX_LENGTH_I_MAP_ROW*MAX_LENGTH_I_MAP_COL) + hi * (MAX_LENGTH_I_MAP_ROW*MAX_LENGTH_I_MAP_COL);
//            LLoc = i * (H_I * MAX_LENGTH_I_MAP_ROW) + hi * (MAX_LENGTH_I_MAP_ROW);
//            for(j = 0; j < L; j++){
//                for(hs = 0; hs < H_S; hs++){
//                    if(mpz_cmp_ui(*(I + offset(i, hi, j, hs)), 0) != 0){
//                        p = 0;
//                        for(k = 0; k < e; k++){
//                            mpz_set(temp, *(Value + LLoc + k));
//                            if(mpz_cmp(temp, *(I + offset(i, hi, j, hs)))==0){                                
//                                h = *(Idx + Loc + k*MAX_LENGTH_I_MAP_COL + 0);
////                                printf("# $$$");
//                                *(Idx + Loc + k*MAX_LENGTH_I_MAP_COL + h+1) = j*H_S + hs;
//                                *(Idx + Loc + k*MAX_LENGTH_I_MAP_COL + 0)=h+1;
//                                
//                                p = 1;
//                                break;
//                                
//                            }
//                            
//                        }
//                        if(p == 0){
////                            printf("# %d \n", e);
////                            gmp_printf("%Zx\n", *(I + offset(i, hi, j, hs)));
//                            mpz_set(*(Value + LLoc + e),  *(I + offset(i, hi, j, hs)));
//                            *(Idx + Loc + e*MAX_LENGTH_I_MAP_COL + 1) = j*H_S + hs;
////                            gmp_printf("$%Zx\n", *(I + offset(i, hi, j, hs)));
////                            printf("# %d \n", j*H_S + hs);
//                            *(Idx + Loc + e*MAX_LENGTH_I_MAP_COL + 0)=1;
//                            e++;
//                                    
//                        }
//                    }
//                }
//            }
//        }   
//    }
//}