/*
 * Free wrapper that detects double free's writing in the address that allocates the pointee that points to the data.
 * Use sfree(pointer); 
 * when trying to free void *pointer 
 *
 * beck@math.co.ro
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define sfree(x) xfree(&x,(char *)__FUNCTION__)
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

/* Testing double free... , use valgrind to check that theres no leak's */
int
main (void)
{
  void *k;
  int i = 0;
  while (i++ != 1000)
    {
      k = malloc (100);
      memset (k, 0x41, 100);
      printf ("primer free\n");
      sfree (k);
      printf ("Segundo free\n");
      sfree (k);
    }
  return 0;
}
