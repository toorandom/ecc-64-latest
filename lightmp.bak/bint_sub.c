#include "lightmp.h"
/*
 * Computes c such that c=a-b
 */
bint *
bint_sub (bint * a, bint * b, bint * c)
{
  int i, cf = 0, t, swapped = 0;
  bint *temp;
  bint_normalize (a);
  bint_normalize (b);
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
      t = a->digits[i] - (b->digits[i] + cf);
      if (t < 0)
	{
	  cf = 1;
	  t = BASE - abs (t);
	}
      else
	cf = 0;

      c->digits[i] = t % BASE;
    }
  for (; i < a->len; i++)
    {
      t = a->digits[i] - cf;
      if (t < 0)
	{
	  cf = 1;
	  t = BASE - abs (t);
	}
      else
	cf = 0;
      c->digits[i] = t;
    }

  c->digits[i] = cf;
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
