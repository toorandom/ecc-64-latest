#include "lightmp.h"
bint *
bint_random (bint * dst, int size)
{
  int fd = open (RAND_DEVICE, O_RDONLY);
  int i;
  bint *prime;
  char *p = PRIME;
  unsigned char *buf = calloc (size, sizeof (char));
  if (fd < 0)
    {
      perror ("fd");
      fprintf (stderr, "Could not open random device at %s\n", RAND_DEVICE);
      exit (EXIT_FAILURE);
    }
  read (fd, buf, size);
  dst->len = size;
  bint_clean (dst);
  for (i = 0; i < size; i++)
    dst->digits[i] = buf[i] % 10;
  free (buf);
  close (fd);
  dst->len = size + 1;
  bint_normalize (dst);
  prime = bint_alloc (sizeof (PRIME) + 1, POSITIVE);
  prime = atobint (p, prime);
  if (bint_cmp (dst, prime) == FIRST_GREATER)
    dst->len--;
  bint_free (prime);
  bint_normalize (dst);

  return dst;
}
