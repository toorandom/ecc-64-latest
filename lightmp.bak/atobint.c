#include "lightmp.h"
/* Allocates a bint *x
 *  * using the number expressed in ascii from ascii_num
 *   */
bint *
atobint (char *ascii_num, bint * x)
{
  int i = 0, pf = 0, nf = 0, alen = strlen (ascii_num);
  switch (ascii_num[0])
    {
    case POSITIVE:
      pf = 1;
      break;
    case NEGATIVE:
      nf = 1;
      break;
    default:
      pf = 1;
    }

  /* Normaliza numeros, si estos comienzan con cero, los elimina */
  if (ascii_num[0 + nf] == '0')
    {

      while (ascii_num[i + nf] == '0')
	i++;

      ascii_num = ascii_num + i;

      if (nf)
	{
	  ascii_num = ascii_num + 1;
	}
      alen = alen - i - nf;
    }


  for (i = 0 + nf; i < alen; i++)
    {
      if (!isdigit (ascii_num[i]))
	{
	  fprintf (stdout, "%s (%c) is not a number\n", ascii_num,
		   ascii_num[i]);
	  exit (EXIT_FAILURE);
	}
    }
  for (i = alen - 1; i >= 0 + nf; i--)
    x->digits[alen - 1 - i] = ascii_num[i] - '0';
  x->sign = pf > 0 ? POSITIVE : NEGATIVE;
  x->len = alen;
  bint_normalize (x);
  return x;
}
