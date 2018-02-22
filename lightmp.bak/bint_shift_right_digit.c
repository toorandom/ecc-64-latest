#include "lightmp.h"
/*
 * Right shift of digits (is like multiplying n * 10^d )
 *
 */
void
bint_shift_right_digit (bint * n, int d)
{
  int i;
  if ((n->len == 1) && (n->digits[0] == 0))
    return;

  for (i = n->len - 1; i >= 0; i--)
    n->digits[i + d] = n->digits[i];

  for (i = 0; i < d; i++)
    n->digits[i] = 0;

  n->len = n->len + d;
  bint_normalize (n);
}

