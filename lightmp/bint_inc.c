#include "lightmp.h"
/*
 *  Calculates
 *  a=a+1
 *  a must have enough memory to handle a carry flag to the BASE
 *  in the most significative digit
 */
bint *
bint_inc (bint * a)
{
  int i, cf = 0;
  for (i = 0; i < a->len; i++)
    {
      a->digits[i] = (a->digits[i] + cf) + (i > 0 ? 0 : 1);
      if ((a->digits[i]) >= BASE)
        cf = 1;
      else
        cf = 0;
      a->digits[i] = a->digits[i] % BASE;
      if (i == a->len - 1)
        {
          a->len++;
          a->digits[a->len - 1] = cf;
          break;
        }
      if (!cf)
        break;
    }
  bint_normalize (a);
  return a;
}
