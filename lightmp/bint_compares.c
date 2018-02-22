#include "lightmp.h"
/*
 * Compares a and b
 * if a > b returns FIRST_GREATER   <-- the name of the macro is because "First
argument" was bigger
 * if a < b returns SECOND_GREATER
 * if a = b returns EQUAL
 */

int
bint_cmp (bint * a, bint * b)
{
  int i, negate = 0;
  bint_normalize (a);
  bint_normalize (b);
  if ((b->len <= 0) && (a->len <= 0))
    {
      return EQUAL;
    }
  if ((a->sign == NEGATIVE) && (b->sign == POSITIVE))
    return SECOND_GREATER;
  if ((a->sign == POSITIVE) && (b->sign == NEGATIVE))
    return FIRST_GREATER;


  if ((a->sign == NEGATIVE) && (b->sign == NEGATIVE))
    {
      negate = 1;
    }


  if (a->len > b->len)
    {
      if (negate)
	return SECOND_GREATER;
      return FIRST_GREATER;
    }
  else if (a->len < b->len)
    {
      if (negate)
	return FIRST_GREATER;
      return SECOND_GREATER;
    }
  i = a->len - 1;
  while (1)
    {
      if (a->digits[i] > b->digits[i])
	{
	  if (negate)
	    return SECOND_GREATER;
	  return FIRST_GREATER;
	}

      else if (a->digits[i] < b->digits[i])
	{
	  if (negate)
	    return FIRST_GREATER;
	  return SECOND_GREATER;
	}
      if (i == 0)
	break;
      i--;
    }
  return EQUAL;
}

/* return 1 if x is zero
 *  * else return 0
 *   */
int
bint_is_zero (bint * x)
{
  bint_normalize (x);
  if ((x->len == 1) && (x->digits[0] == 0))
    return 1;
  return 0;
}

	  /* returns 1 if x is of the form 2n
	   *  * else return 0
	   *   */
int
bint_is_even (bint * x)
{
  bint_normalize (x);
  if ((x->digits[0] % 2) == 0)
    return 1;
  return 0;
}
