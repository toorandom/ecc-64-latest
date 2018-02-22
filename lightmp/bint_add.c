/* suma dos numerotes O(n) si n es el numero de digitos*/
/* lo mismo que en la resta
 * c debe de tener memoria lista para almacenar a+b
 */
#include "lightmp.h"
bint *
bint_add (bint * a, bint * b, bint * c)
{
  int i;
  _ulong cf = 0, t;
  bint_clean(c);
  if ((a->sign == NEGATIVE) && (b->sign == POSITIVE))
    {
      a->sign = POSITIVE;
      c = bint_sub (b, a, c);
      bint_normalize (c);
      b->sign = POSITIVE;
      a->sign = NEGATIVE;
      return c;
    }
  if ((a->sign == POSITIVE) && (b->sign == NEGATIVE))
    {
      b->sign = POSITIVE;
      c = bint_sub (a, b, c);
      bint_normalize (c);
      a->sign = POSITIVE;
      b->sign = NEGATIVE;
      return c;
    }
  if ((a->sign == NEGATIVE) && (b->sign == NEGATIVE))
    c->sign = NEGATIVE;


  /* sumamos lo que el minimo sumando le es posible con el otro sumando */
  for (i = 0; i < min (a->len, b->len); i++)
    {
      /* sumamos los dos digitos */
      t = a->digits[i] + b->digits[i] + cf;
      if(ADD_OVERFLOW(a->digits[i],b->digits[i])) 
      cf = 1;
      else
      cf = 0;
      /* sumamos el digito menos significativo(o digitos dependiendo la base) */
      c->digits[i] = t;
    }
      /* si t es mayor a la base (generalmente 10) quiere decir que necesitamos
aumentar el carry flag + 1 */
    
  /* si el primer sumando es mas grande , entonces incluimos su suma + carry fla
g */
  if (max (a->len, b->len) == a->len)
    for (; i < a->len; i++)
      {
        t = a->digits[i] + cf;
	if(ADD_OVERFLOW(a->digits[i],cf))
	cf = 1;
	else
	cf = 0;
        c->digits[i] = t;
      }
  /* si es el segundo sumando el mas grande entonces incluimos su suma + carry f
lag */
  else if (max (a->len, b->len) == b->len)
    for (; i < b->len; i++)
      {
        t = b->digits[i] + cf;
	if(ADD_OVERFLOW(b->digits[i],cf))
	cf = 1;
	else
	cf = 0;
        c->digits[i] = t;
      }
  c->digits[i] = cf;
  c->len = i + 1;
  bint_normalize (c);
  return c;
}
