#include "lightmp.h"
/* Allocates a bint *x
 *  using the number expressed in ascii from ascii_num
 */
bint *
atobint (void *data_num, size_t bytes, char sign, bint * x)
{
  char pf = 0, nf = 0;
  int k, m, rsize;
  _ulong *temp = data_num;
  bint_clean (x);
  rsize = bytes / sizeof (_long);
  x->len = bytes % sizeof (_long) != 0 ? rsize + 1 : rsize;
  if ((rsize == 1) && (x->len == 1))
    memcpy (&x->digits[0], data_num, bytes);
  else
    {
      for (k = x->len - 1; k >= 0 + ((x->len % sizeof (_long)) > 0); k--)
	x->digits[k] = temp[x->len - 1 - k];

      if ((m = bytes % sizeof (_long)))
	memcpy (&x->digits[0], data_num + bytes - m, m);
    }

  x->sign = sign == NEGATIVE ? NEGATIVE : POSITIVE;
#if (BYTE_ORDER == __LITTLE_ENDIAN)
  int i;
  for (i = 0; i < x->len; i++)
#if (__WORDSIZE == 64)
    x->digits[i] = INVERT64 (x->digits[i]);
#endif
#if (__WORDSIZE == 32)
  x->digits[i] = INVERT32 (x->digits[i]);
#endif

#endif
  bint_normalize (x);
  return x;
}
