/* 
 * File:   linked_list.h
 * Author: yanzhi
 *
 * Created on February 11, 2015, 5:20 PM
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

struct Node{
    mpz_t value;
    struct node *idx;
    struct Node *next;
};

struct node{
    int location;
    int height;
    struct node *next;
};