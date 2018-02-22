/* We will use this curve y2 = x3 - 3x + B mod P of prime order R, this settings are recomended for ECC by NIST  */
#include "lightmp.h"
#ifndef _LECC_H
#define _LECC_H
/* This constant defines the probability of 1/2^k to fail when embedding a plaintext to a point in a curve */
#define K 100   
/* 256 bit prime modulus */
#define P "115792089210356248762697446949407573530086143415290314195533631308867097853951"  
/* Order */
#define R "115792089210356248762697446949407573529996955224135760342422259061068512044369"
/* The independent term B in the curve */
#define B "41058363725152142129326129780047268409114441015993725554835256314039467401291"
/* X coordinate of base point */
#define BX "48439561293906451759052585252797914202762949526041747995844080717082404635286"
/* Y coordinate of base point */
#define BY "36134250956749795798585127919587881956611106672985015071877198253568414405109"

/* (p-1)/2 needed for message conversion to point with Koblitz method */
#define P_MINUS_1_BY_2 "57896044605178124381348723474703786765043071707645157097766815654433548926975"
/* need to calculate the square root of a square modulo p */

#define P_PLUS_1_BY_4 "28948022302589062190674361737351893382521535853822578548883407827216774463488"
typedef struct point {
bint *x,*y;
int infinity;
} point_t;
void
lecc_point_double (const point_t * , point_t * );
void
lecc_point_add (const point_t *, const point_t *, point_t *);
void *
lecc_point_alloc (void);
void
lecc_point_print (point_t *, char *);
void
lecc_point_free (point_t * );

#endif
