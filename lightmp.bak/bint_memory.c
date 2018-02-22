#include "lightmp.h"
/*
 *  Fix zeroes , if 000001 then 1
*/
void
bint_normalize (bint * x)
{
  int j = 0;
  if ((x->len == 1) && (x->digits[0] == 0))
    {
      x->sign = POSITIVE;
    }
  if (x->len <= 0)
    {
      x->len = 1;
      x->digits[0] = 0;
      x->sign = POSITIVE;
    }
  if (x->len > 1)
    while (x->digits[x->len - 1 - j] == 0)
      {
        j++;
      }
  x->len = x->len - j;
  return;
}

/*
 * Copy sign , digits and len from
 * src to dst
 * obviusly dst must have memory
 */

void
bint_copy (bint * dst, bint * src)
{
  bint_normalize (src);
  dst->len = src->len;
  dst->sign = src->sign;
  memset (dst->digits, 0, dst->len);
  memcpy (dst->digits, src->digits, src->len);
  bint_normalize (dst);
  return;
}

/*
 * Fills all with zeroes , but not the sign
 */
void
bint_clean (bint * x)
{
  if (x->len > 0)
    memset (x->digits, 0, x->len);
  x->len = 0;
  return;
}
