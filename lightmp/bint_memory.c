#include "lightmp.h"

void
xfree (void *ptr, char *parent_function)
{
  void **t = ptr;
  if (*t == NULL)
    {
      fprintf (stderr, "%s():NULL pointer!! called from %s() not freeing..\n\n",__FUNCTION__,parent_function);
      return;
    }
  free (*t);
  *t = 0;
  return;
}




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
        j++;
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
  bint_clean(dst);
  dst->len = src->len;
  dst->sign = src->sign;
  memcpy (dst->digits, src->digits, src->len*sizeof(_long));
  bint_normalize (dst);
  return;
}

/*
 * Fills all with zeroes , but not the sign
 */
void
bint_clean (bint * x)
{
  int i;
  if (x->len > 0)
  memset(x->digits,0,x->len);
  x->len = 0;
  return;
}



/* Malloc wrapper to check if memory is available */
void *
xcalloc (size_t n, int siz)
{
  bint *ptr;
  if ((ptr = calloc (n, siz)) == NULL)
    {
      perror ("calloc: Could not allocate memory\n");
      exit (EXIT_FAILURE);
    }
  return ptr;
}

/* malloc for bints */
void *
bint_alloc (size_t digits, size_t sign)
{
/*
 * printf("%d\n",digits);
 */
  bint *n;
  n = xcalloc (1, sizeof (struct bint_t));
  n->sign = sign;
  n->digits = xcalloc (digits + 1, sizeof (_long));
  n->len = digits;
  bint_normalize (n);
  return n;
}

              /* free  of bints */
void
bint_xfree (bint * n,char *function_name)
{
  xfree (&n->digits,function_name);
  xfree (&n,function_name);
}

