#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>


#ifndef _LIGHTMP_
#define _LIGHTMP_
#define bint_debug(x,y) bint_debug_new(x,y,(char *)__FUNCTION__,__LINE__)
#define POSITIVE '+'
#define NEGATIVE '-'
#define BASE -1L
#define FIRST_GREATER 1
#define SECOND_GREATER 2
#define EQUAL 0
#define RAND_DEVICE "/dev/urandom"
#define MAX_MESSAGE_SIZE 8192

#define ADD_OVERFLOW(x,y) (-1L - y) < x ? 1 : 0
#define SUB_OVERFLOW(x,y) (max(x,y) == x ? 0 : 1)
#define DOUBLE_WORD_INVERT(vector) ((vector<<32) | (vector>>32))


#define INVERT64(vector)  \
((vector & 0x00000000000000FF) << 56) | \
((vector & 0x000000000000FF00) << 40) | \
((vector & 0x0000000000FF0000) << 24) | \
((vector & 0x00000000FF000000) << 8 ) | \
((vector & 0x000000FF00000000) >> 8 ) | \
((vector & 0x0000FF0000000000) >> 24) | \
((vector & 0x00FF000000000000) >> 40) | \
((vector & 0xFF00000000000000) >> 56)

#define INVERT32(vector)  \
((vector & 0x000000FF) << 24) | \
((vector & 0x0000FF00) << 8 ) | \
((vector & 0x00FF0000) >> 8 ) | \
((vector & 0xFF000000) >> 24)

typedef unsigned long _ulong;
typedef long _long;



typedef struct bint_t
{
  _long len;
  char sign;
  _ulong *digits;
} bint;

/* Prototypes */
/* Note that all functions that do arithmetic or calculates anything
 * requieres arguments with memory allocated with bint_alloc this is to evade memory leaks and giving the responsability to the user
 */
#define bint_free(x) bint_xfree(x,(char *)__FUNCTION__) 
#define sfree(x) xfree(&x,(char *)__FUNCTION__)

void xfree (void *, char *);				/* free wrapper */
void bint_xfree (bint * , char *);			/* Free a arg1 of bint type from function arg2 */
void bint_normalize (bint * );				/* Fix zeroes of arg1 , this converts 000001 to 1 for example */
void bint_copy (bint * , bint * );			/* Copy arg2 to arg1 */
void bint_clean (bint * );				/* Fill with zeroes arg1 */
void bint_debug_new (bint * , char *, char *, int );	/* This is internal use bint_debug() macro */
void bint_print (bint * );				/* Prints a arg1 in decimal format */
void bint_shift_right_digit (bint * , int );		/* Equivalent to multiply arg1*10^n where n is the second argument */
void *bint_alloc (size_t, size_t);		/* Allocates arg1 digits , second argument is POSITIVE or NEGATIVE return value is memory for bint */

int bint_is_zero (bint * );				/* True if arg1 is zero */
int bint_is_even (bint * );				/* True if arg is of the form 2n */
int bint_cmp (bint * , bint * );			/* Tests which arg1 or arg2 is greater, ret vals are FIRST_GREATER,SECOND_GREATER,EQUAL  */

bint *bint_sub (bint * , bint * , bint * );		/* arg1 - arg2 and allocates in arg3 */
bint *bint_add (bint * , bint * , bint * );		/* arg1 + arg2 and allocates in arg3 */
bint *bint_inc (bint * );				/* arg1 + 1 and allocates in same bint (careful when carry flag increments size) */
bint *bint_dec (bint * );				/* arg1 - 1 and allocates in same bint (fixes size of carry flag reduces size) */
bint *bint_mul (bint * , bint * , bint * );		/* arg1 * arg2 and allocates in arg3 */
bint *bint_pow2long (bint * , _ulong , bint * ); /* arg1 ** (long)arg2 and allocates in arg3 (careful with memory alloc here in arg3) */
bint *bint_mul_long (bint * , _ulong , bint * ); /* arg1 * (long)arg2 and allocates in arg3 */
bint *bint_egcd (bint * , bint * , bint * , bint * , bint * ); /* Calculates arg3 ,arg4, arg5 such that arg1*arg3 + arg2*arg4 = arg5 = gcd(arg1,arg2) */
bint *bint_gcd (bint * , bint * );			/* Calculates GCD of arg1 and arg2 (greatest common divisor) */
bint *bint_mod_exp (bint * , bint * , bint * , bint * );/* Calculates arg4 such that  arg1^arg2 = arg4 mod arg3 */
bint *bint_random (bint * , int);			/* Calculates arg1 as a random integer less than PRIME macro defined in elgamal.h with digits=arg2 */
bint *bint_mod (bint * , bint * , bint * );		/* Calculates arg3 such that arg1 = arg3 mod arg2 */
bint *bint_div (bint * , bint * , bint * , bint * );    /* Calculates arg3 and arg4 such that (arg2*arg3)+arg4 = arg1 with arg1 < arg2 */
bint *bint_inverse (bint * , bint *, bint * );		/* Calculates arg3 such that  arg1*arg3 = 1 modulo arg2 */
bint *atobint (void *,size_t,char, bint * );			/* Converts a string of digits "1234567890" to bint format to arg2 */
_ulong max(_ulong,_ulong);
#endif
