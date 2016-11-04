/* 
 * File:   Parameters.h
 * Author: yanzhi
 *
 * Created on December 7, 2014, 5:45 PM
 */
#include "paillier.h"

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_H */

//#define L 650 // number of grids
//#define PU_NUM 350 // number of PUs
//#define F 5 // number of frequency channels
#define L 2 // number of grids
#define H 2 // antenna height levels
#define F 2 // number of frequency channels
#define PU_NUM 2 // number of PUs
#define SU_NUM 10

#define K 60
#define PSI 220
#define MAX_LENGTH_I_MAP_ROW 1000
#define MAX_LENGTH_I_MAP_COL 500
#define I_Line_length 52312098

#define MIN_SENSITIVITY 1000000
#define MAX_SENSITIVITY 100000000

mpz_t TEN;
mpz_t ONE;
mpz_t ZERO;
mpz_t Z;




#include <gmp.h>