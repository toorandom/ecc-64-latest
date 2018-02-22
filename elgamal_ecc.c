/*
Elgamal routines using finite group on a elliptic curve
Eduardo Ruiz Duarte
beck@math.co.ro
*/
#include "lecc.h"
extern bint *base_x;
extern bint *base_y;
extern bint *p;
void
elgamal_genkeys_ecc (point_t * public, bint * priv)
{
  point_t *gen = lecc_point_alloc ();
  bint_copy (gen->x, base_x);
  bint_copy (gen->y, base_y);
  gen->infinity = 0;
  priv = bint_random (priv, p->len);
  if (bint_cmp (priv, p) == FIRST_GREATER)
    priv->len--;
  bint_normalize (priv);
  lecc_point_scalar_mul (priv, gen, public);
/*
  bint_free (gen->x);
  bint_free (gen->y);
*/
  lecc_point_free (gen);
  return;
}

void
elgamal_crypt_ecc (point_t * m, point_t * pub, point_t * c1, point_t * c2)
{
  bint *t = bint_alloc (p->len * p->len, POSITIVE);
  point_t *gen = lecc_point_alloc (), *tmp;
  bint_copy (gen->x, base_x);
  bint_copy (gen->y, base_y);
  gen->infinity = 0;
  t = bint_random (t, p->len);
  tmp = lecc_point_alloc ();
  lecc_point_scalar_mul (t, gen, c1);
  lecc_point_scalar_mul (t, pub, tmp);
  lecc_point_add (tmp, m, c2);
  lecc_point_free (tmp);
  lecc_point_free (gen);
  bint_free (t);
  return;
}

void
elgamal_decrypt (point_t * c1, point_t * c2, bint * priv, point_t * plain)
{
  point_t *tmp;
  bint *t1;
  tmp = lecc_point_alloc ();
  t1 = bint_alloc (p->len * 4, POSITIVE);
  bint_clean (t1);
  lecc_point_scalar_mul (priv, c1, tmp);
  tmp->y->sign = NEGATIVE;
  lecc_point_add (c2, tmp, plain);
  lecc_point_free (tmp);
  bint_free (t1);
  return;
}

int
main (void)
{
  point_t *pub, *plain_point, *c1, *c2, *out_point;
  bint *priv, *plain_number,*out_number;
  lecc_initialize_parameters ();
  priv = bint_alloc (p->len * 2, POSITIVE);
  plain_number = bint_alloc (p->len * 10, POSITIVE);
  out_number = bint_alloc (p->len * 10, POSITIVE);
  pub = lecc_point_alloc ();
  plain_point = lecc_point_alloc ();
  c1 = lecc_point_alloc ();
  c2 = lecc_point_alloc ();
  out_point = lecc_point_alloc ();
/*
  bint_free(priv);
  bint_free(plain_number);
  bint_free(out_number);
  lecc_point_free(plain_point);
  lecc_point_free(pub);
  lecc_point_free(c1);
  lecc_point_free(c2);
  lecc_point_free(out_point);
  lecc_free_parameters();
  */
/* We generate a random number to crypt of 128 bits len in digits in radix 10 is */
  
  plain_number = bint_random (plain_number, p->len/2);
  printf("------------------------\n");
  printf("Using this integer as plaintext\nplaintext=");
  bint_print(plain_number);
  printf("------------------------\n");
  printf("Converting integer to point in elliptic curve...\n");
  lecc_message_to_point (plain_number, plain_point);
  lecc_point_print (plain_point, "Plain point");
  printf("------------------------\n");
  printf("Generating public and private keys\n");
  elgamal_genkeys_ecc (pub, priv);
  lecc_point_print (pub,"Public key");
  printf("------------------------\n");
  printf("Ciphering Plain point..\n");
  elgamal_crypt_ecc (plain_point, pub, c1, c2);
  lecc_point_print(c1,"Ciphered message1");
  lecc_point_print(c2,"Ciphered message2");
  printf("------------------------\n");
  printf("Deciphering ciphered messages with private key:\n");
  printf("privkey=");
  bint_print(priv);
  elgamal_decrypt (c1, c2, priv, out_point);
  lecc_point_print(out_point, "Point decrypted");
  lecc_point_to_message(out_point,out_number);
  printf("------------------------\n");
  printf("Decrypted integer\nplaintext=");
  bint_print(out_number);
  bint_free(priv);
  bint_free(plain_number);
  bint_free(out_number);
  lecc_point_free(plain_point);
  lecc_point_free(pub);
  lecc_point_free(c1);
  lecc_point_free(c2);
  lecc_point_free(out_point);
  lecc_free_parameters ();
  return 0;
}
