/*
Elgamal routines using a finite group Zp
by 
Eduardo Ruiz Duarte
beck@math.co.ro
*/
#include "lightmp.h"
#include "elgamal.h"
void
elgamal_genkeys (bint * public, bint * priv)
{
  char *prime_ascii = PRIME;
  char *gen_ascii = GEN;
  bint *prime, *gen, *priv_bak;
  prime = bint_alloc (sizeof (PRIME) * 2, POSITIVE);
  priv_bak = bint_alloc (sizeof (PRIME) * 2, POSITIVE);
  gen = bint_alloc (32, POSITIVE);
  bint_clean (prime);
  bint_clean (gen);
  prime = atobint (prime_ascii, prime);
  gen = atobint (gen_ascii, gen);
  fprintf (stderr, "Generating public and private keys..\n");
  priv = bint_random (priv, sizeof (PRIME));
  if (bint_cmp (priv, prime) == FIRST_GREATER)
    priv->len--;
  bint_copy (priv_bak, priv);
  bint_normalize (priv);
  bint_normalize (gen);
  bint_normalize (prime);
  public = bint_mod_exp (gen, priv, prime, public);
  bint_copy (priv, priv_bak);
  bint_free (prime);
  bint_free (gen);
  bint_free (priv_bak);
  bint_normalize (public);
  return;
}

void
elgamal_crypt (bint * m, bint * pub, bint * c1, bint * c2)
{
  char *gen = GEN;
  char *prime = PRIME;
  bint *y = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  bint *g = bint_alloc (32, POSITIVE);
  bint *p = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  bint *t = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  bint *t2 = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  g = atobint (gen, g);
  p = atobint (prime, p);
  y = bint_random (y, sizeof (PRIME));
  fprintf (stderr, "Phase 1/2 of elgamal encryption\n");
/*
  bint_debug(g,"g");
  bint_debug(y,"y");
  bint_debug(p,"p");
*/
  c1 = bint_mod_exp (g, y, p, c1);
/*
  bint_debug(c1,"g^y mod p");
*/
  fprintf (stderr, "Phase 2/2 of elgamal encryption\n");
/*
 bint_debug(pub,"pub");
 bint_debug(y,"y");
  bint_debug(p,"p");
*/
  t = bint_mod_exp (pub, y, p, t);
/*
  bint_debug(t,"pub^y mod p");
  bint_debug(t,"t");
  bint_debug(m,"m");
*/
  t2 = bint_mul (t, m, t2);
/*
  bint_debug(t2,"t*m");
*/
  c2 = bint_mod (t2, p, c2);
/*
  bint_debug(c2,"t*m");
*/
  bint_free (y);
  bint_free (g);
  bint_free (p);
  bint_free (t);
  bint_free (t2);
  return;
}

void
elgamal_decrypt (bint * c1, bint * c2, bint * priv, bint * plain)
{
  char *gen = GEN;
  char *prime = PRIME;
  bint *y, *g, *p, *t, *t2;
  g = bint_alloc (32, POSITIVE);
  p = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  t = bint_alloc (sizeof (PRIME) * sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  t2 = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  y = bint_alloc (sizeof (PRIME) * sizeof (PRIME), POSITIVE);
  g = atobint (gen, g);
  p = atobint (prime, p);
  fprintf (stderr, "Phase 1/4 of elgamal decryption\n");
/*
  bint_debug(c1,"c1");
  bint_debug(priv,"priv");
  bint_debug(p,"p");
*/
  t = bint_mod_exp (c1, priv, p, t);
/*
  bint_debug(t,"c1^priv mod p");
*/
  fprintf (stderr, "Phase 2/4 of elgamal decryption\n");
  bint_clean (t2);
  t2 = bint_inverse (t, p, t2);
/*
  bint_debug(t2,"(c1^priv)^-1 mod p");
*/
  bint_clean (t);
  fprintf (stderr, "Phase 3/4 of elgamal decryption\n");
/*
  bint_debug(c2,"c2");
  bint_debug(t2,"t2");
*/
  bint_clean (t);
  bint_free (t);
  t = bint_alloc (t2->len + c2->len + sizeof (PRIME), POSITIVE);
  t = bint_mul (t2, c2, t);
/*
  bint_debug(t2,"t2 after mul");
  bint_debug(c2,"c2 after mul");
  bint_debug(t,"c2*(c1^priv)^-1");
*/
  fprintf (stderr, "Phase 4/4 of elgamal decryption\n");
/*
  bint_debug(p,"p");
*/
  bint_clean (plain);
  plain = bint_mod (t, p, plain);
/*
  bint_debug(plain,"(c1^priv)^-1 % p");
*/
  bint_free (y);
  bint_free (g);
  bint_free (p);
  bint_free (t);
  bint_free (t2);
  return;
}
