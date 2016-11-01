#include <stdlib.h>
#include <time.h>
#include "Parameters.h"

int generate_ran(int percent){
    
    int r = rand()%100;
    if(r <= percent){
        return 1;
    }
    else
        return 0;
    
}

int offset( int l, int h, int f) { return l*H*F + h*F + f;}

int initialize_mpz_array(mpz_t *mpz_array, int value){
    int l=0;
    int h=0;
    int f=0;
    for(l=0; l<L; l++){
        for(h=0; h<H; h++){
            for(f=0; f<F; f++){
                mpz_init_set_ui(*(mpz_array + offset(l,h,f)), value);
            }
        }
    }
}

void print_mpz_array(mpz_t *mpz_array){
    int l=0;
    int h=0;
    int f=0;
    for(l=0; l<L; l++){
        for(h=0; h<H; h++){
            for(f=0; f<F; f++){
                gmp_printf("%Zx\n", *(mpz_array + offset(l,h,f)));
            }
        }
    }
}



int* generate_random_array_no_reps(int MAX, int MIN, int AMOUNT){     
    int *value = (int *)malloc(sizeof(int)*AMOUNT); //array to store the random numbers in

    srand(time(NULL)); //always seed your RNG before using it

    //generate random numbers:
    int i;
    for (i=0;i<AMOUNT;i++)
    {
        int check; //variable to check or number is already used
        int n; //variable to store the number in
        do
        {
        n=rand()%(MAX-MIN)+MIN;
        //check or number is already used:
        check=1;
        int j;
        for ( j=0;j<i;j++)
            if (n == value[j]) //if number is already used
            {
                check=0; //set check to false
                break; //no need to check the other elements of value[]
            }
        } while (!check); //loop until new, unique number is found
        value[i]=n; //store the generated number in the array
    }

    //print the array
//    for( i=0; i<AMOUNT; i++ )
//        printf("%d\n",value[i]);
    return value;
}