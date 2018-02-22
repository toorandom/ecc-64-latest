#include "lightmp.h"
bint *
bint_inverse (bint * a, bint * m, bint * inv)
{
  bint *x, *y, *g, *t, *a_backup;
  int swap = 0;
  x = bint_alloc (a->len + m->len, POSITIVE);
  y = bint_alloc (a->len + m->len, POSITIVE);
  g = bint_alloc (a->len + m->len, POSITIVE);
  g = bint_egcd (a, m, x, y, g);
  swap = 1;
  a_backup = bint_alloc (a->len + m->len, POSITIVE);
  bint_normalize (a);
  bint_copy (a_backup, a);
  t = bint_alloc (a->len + m->len, POSITIVE);
  t = bint_mod (a, m, t);
  bint_copy (a, t);
  bint_free (t);

  /* Lets check if the inverse exists , gcd must be 1 (linear combination of a a
nd m   ax+my = 1)
   * if the inverse doesnt exists the return value is a zero in bint format
   */
  bint_dec (g);
  if (!bint_is_zero (g))
    {
      printf ("NO INVERSE for x=");
      bint_print (a);
      inv->len = 1;
      inv->digits[0] = 0;
      return inv;
    }
/* Here the inverse is x but this might be a negative value, lets calculate the
modulus
 * now im proud to announce my negative modulus partitioner implementation
 */
  bint_clean (inv);
  inv = bint_mod (x, m, inv);
  bint_free (x);
  bint_free (y);
  bint_free (g);
  if (swap)
    {
      bint_copy (a, a_backup);
      bint_free (a_backup);
    }
  return inv;
}

