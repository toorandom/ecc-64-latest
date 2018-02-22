#include "lightmp.h"
/*
 * Computes
 * c = a*b
 * c must have at least a->len+b->len+1 memory allocated
 */
bint *
bint_mul (bint * a, bint * b, bint * c)
{
  int i, j;
  int *a_hdl, *b_hdl,*c_hdl;
  unsigned long long t,digit,cf=0;
  bint_clean (c);
  if (bint_is_zero (a) || bint_is_zero (b))
    {
      c->len = 1;
      c->digits[0] = 0;
      return c;
    }

#if (BYTE_ORDER == __LITTLE_ENDIAN) 
printf("Converting big endian\n");
 for(i = 0 ; i < a->len ; i++) 
 a->digits[i] = DOUBLE_WORD_INVERT(a->digits[i]);
 for(i = 0 ; i < b->len ; i++)
 b->digits[i] = DOUBLE_WORD_INVERT(b->digits[i]);
#endif
/*
  Lame reminder
         AA BB CC
            11 22
   ------------------        
      16 AC F1 18
   0B 56 78 8C
   ------------------
   0B 6D 25 7D 18
*/

  a_hdl = (int *)a->digits;
  b_hdl = (int *)b->digits;
  c_hdl = (int *)c->digits;

  for (i = 0; i < a->len*2; i++)
    for (j = 0; j < b->len*2; j++)
      {
        t = (unsigned long long)c_hdl[i + j] + (unsigned long long)a_hdl[i] * (unsigned long long)b_hdl[j] + (j < 1 ? 0 : cf);
        cf = (t & 0xFFFFFFFF00000000 >> 32);
        digit = t & 0xFFFFFFFF;
        c_hdl[i + j] = digit;
        c_hdl[i + (b->len*2)] = (j > (b->len*2) - 2 ) ? cf : 0;
      }
  c->len = a->len + b->len + 1;
  c->sign = (a->sign == b->sign) ? POSITIVE : NEGATIVE;
#if (BYTE_ORDER == __LITTLE_ENDIAN) 
 for(i = 0 ; i < a->len ; i++)
 a->digits[i] = DOUBLE_WORD_INVERT(a->digits[i]);
 for(i = 0 ; i < b->len ; i++)
 b->digits[i] = DOUBLE_WORD_INVERT(b->digits[i]);
 for(i = 0 ; i < c->len ; i++)
 c->digits[i] = DOUBLE_WORD_INVERT(c->digits[i]);
#endif


  bint_normalize (c);
  return c;
}

