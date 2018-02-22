#include "lightmp.h"
/*
 * Computes c such that c=a-b
 */
bint *
bint_sub (bint * a, bint * b, bint * c)
{
  int i,  swapped = 0;
  _ulong t = 0,cf=0,ccf=0;
  bint *temp;
  bint_normalize (a);
  bint_normalize (b);
  bint_clean(c);
  c->sign = POSITIVE;

  if ((a->sign == POSITIVE) && (b->sign == NEGATIVE))
    {
      b->sign = POSITIVE;
      c = bint_add (a, b, c);
      b->sign = NEGATIVE;
      bint_normalize (c);
      return c;
    }


  if ((a->sign == NEGATIVE) && (b->sign == POSITIVE))
    {
      a->sign = POSITIVE;
      c = bint_add (a, b, c);
      a->sign = NEGATIVE;
      c->sign = NEGATIVE;
      bint_normalize (c);
      return c;
    }
  if (bint_cmp (a, b) == SECOND_GREATER)
    {
      temp = a;
      a = b;
      b = temp;
      swapped = 1;
    }
  for (i = 0; i < b->len; i++)
    {
      t -= cf;
      cf = SUB_OVERFLOW(a->digits[i],b->digits[i]);
      t += a->digits[i] - b->digits[i];
      c->digits[i] = t & (_ulong)(-1UL);
      t = 0;
    }
t = 0;
  for (; i < a->len; i++)
    {
  //    t -= ccf;
      ccf=SUB_OVERFLOW(a->digits[i],cf);
      t += a->digits[i]-cf;
      c->digits[i] = t&(_ulong)(-1UL);
      t = 0;
      cf = ccf;
    }

  c->digits[i] = ccf;
  c->len = i + 2;
  
  /* Regresamos los punteros a la normalidad si estos fueron volteados pero con el
   *  resultado flagueado como negativo*/
  bint_normalize (c);
  if (swapped)
    {
      temp = a;
      a = b;
      b = temp;
      c->sign = NEGATIVE;
    }
  if (c->len < 1)
    {
      c->len = 1;
      c->digits[0] = 0;
    }
  bint_normalize (c);
  return c;
}
