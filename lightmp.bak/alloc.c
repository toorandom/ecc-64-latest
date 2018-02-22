#include "lightmp.h"
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
bint_alloc (const long digits, unsigned char sign)
{
/*
 * printf("%d\n",digits);
 * */
  bint *n;
  n = xcalloc (1, sizeof (struct bint_t));
  n->sign = sign;
  n->digits = xcalloc (digits + 1, sizeof (unsigned char));
  n->len = digits;
  bint_normalize (n);
  return n;
}

	      /* free  of bints */
void
bint_free (bint * n)
{
  free (n->digits);
  free (n);
}
