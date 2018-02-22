#include "lightmp.h"
/*
 * Function to help debugging process
 */
void
bint_debug_new (bint * x, char *name, char *f, int l)
{
  printf ("DEBUG: %s(%d):%s=", f, l, name);
  bint_print (x);
  return;
}

/* prints x */
void
bint_print (bint * x)
{
  int i;
  //printf("LEN = %d\n",x->len);
  if (x->sign == NEGATIVE)
    printf ("%c", x->sign);
  for (i = x->len - 1; i >= 0; --i)
      printf (sizeof(_long) == 4 ? "%08lX" : "%016lX" ,  x->digits[i]);
  printf ("\n");
  return;
}

