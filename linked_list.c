#include<stdio.h>
#include<stdlib.h>
#include "paillier.h"
#include "linked_list.h"



 
struct Node* add_Node( mpz_t value, struct Node* Head ){

    struct Node *temp;
    temp=(struct Node *)malloc(sizeof(struct Node));
    mpz_init(temp->value);
    mpz_set(temp->value, value);
    temp->idx=NULL;    
    if (Head== NULL)
    {
        Head=temp;
        Head->next=NULL;
    }
    else
    {
        temp->next=Head;
        Head=temp;
    }
    return Head;
}
void add_node( int location, int height, struct Node* N){
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->location = location;
    temp->height = height;
    if (N->idx== NULL)
    {
        temp->next=NULL;
        N->idx=temp;        
    }
    else
    {
        temp->next=N->idx;
        N->idx=temp;
    }
}

