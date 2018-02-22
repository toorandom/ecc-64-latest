/*
Algebraic group structure for the binary operation on elliptic curve
+ and scalar multiplication 
by
Eduardo Ruiz Duarte
beck@math.co.ro

*/
#include  "lecc.h"


bint *p, *b, *base_x, *base_y, *p_minus_1_by_2, *p_plus_1_by_4;

void
lecc_initialize_parameters (void)
{
  p = bint_alloc (sizeof (P) + 1, POSITIVE);
  b = bint_alloc (sizeof (B) + 1, POSITIVE);
  base_x = bint_alloc (sizeof (BX) + 1, POSITIVE);
  base_y = bint_alloc (sizeof (BY) + 1, POSITIVE);
  p_plus_1_by_4 = bint_alloc (sizeof (P_PLUS_1_BY_4) + 1, POSITIVE);
  p_minus_1_by_2 = bint_alloc (sizeof (P_MINUS_1_BY_2), POSITIVE);
  p = atobint (P, p);
  b = atobint (B, b);
  base_x = atobint (BX, base_x);
  base_y = atobint (BY, base_y);
  p_minus_1_by_2 = atobint (P_MINUS_1_BY_2, p_minus_1_by_2);
  p_plus_1_by_4 = atobint (P_PLUS_1_BY_4, p_plus_1_by_4);
  return;
}

void
lecc_free_parameters (void)
{
  bint_free (p);
  bint_free (b);
  bint_free (base_x);
  bint_free (base_y);
  bint_free (p_minus_1_by_2);
  bint_free (p_plus_1_by_4);
  return;
}

void
lecc_point_copy (point_t * dst, point_t * src)
{
  dst->infinity = src->infinity;
  bint_copy (dst->x, src->x);
  bint_copy (dst->y, src->y);
  return;
}

void
lecc_point_clean (point_t * a)
{
  bint_clean (a->x);
  bint_clean (a->y);
  a->x->len = 1;
  a->y->len = 1;
  a->infinity = 1;
}

void
lecc_point_scalar_mul (bint * k, point_t * a, point_t * dst)
{
  point_t *u, *tp, *a2;
  bint *t1, *t2, *t3, *t4, *two;
  char *kbin;
  int kbin_len, i;
  if (a->infinity == 1)
    {
      lecc_point_clean (dst);
      dst->infinity = 1;
      return;
    }
  kbin = calloc (k->len * 10, sizeof (char));
  kbin_len = bint_2_binary (k, kbin);
  tp = lecc_point_alloc ();
  a2 = lecc_point_alloc ();
  t1 = bint_alloc (p->len * 2, POSITIVE);
  t2 = bint_alloc (p->len * 2, POSITIVE);
  t3 = bint_alloc (p->len * 2, POSITIVE);
  t4 = bint_alloc (p->len * 2, POSITIVE);
  two = bint_alloc (32, POSITIVE);
  two->len = 1;
  two->digits[0] = 2;

  lecc_point_clean (a2);
  a2->infinity = 1;
  for (i = 0; i < kbin_len; i++)
    {
      lecc_point_double (a2, tp);
      lecc_point_clean (a2);
      lecc_point_copy (a2, tp);
      lecc_point_clean (tp);
      if (kbin[i])
	{
	  lecc_point_add (a, a2, tp);
	  lecc_point_clean (a2);
	  lecc_point_copy (a2, tp);
	}

    }

  lecc_point_copy (dst, a2);
  bint_free (two);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (t4);
  bint_free (tp->x);
  bint_free (tp->y);
  free (kbin);
  free (tp);
  dst->infinity = 0;
  return;

}

void
lecc_point_to_message (point_t * a, bint * ret)
{
  char kascii[8];
  bint *kint, *t;
  memset (&kascii, 0, sizeof (kascii));
  snprintf ((char *) &kascii, sizeof (kascii), "%d", K);
  kint = bint_alloc (8, POSITIVE);
  t = bint_alloc (8, POSITIVE);
  kint = atobint (kascii, kint);
  ret = bint_div (a->x, kint, ret, t);
 /* t must be freed in the calling function */
 /* bint_free (t); */
  bint_free (kint);
  return;
}


/* Convert a message x to point Q */
void
lecc_message_to_point (bint * x, point_t * Q)
{
  int j;
  point_t ret;
  bint **xj, **sj, *J, *t, *t2, *t3, *t4;
  xj = calloc (K + 1, sizeof (bint) + 1);
  sj = calloc (K + 1, sizeof (bint) + 1);
  t = bint_alloc (x->len * 10, POSITIVE);
  t2 = bint_alloc (x->len * 10, POSITIVE);
  t3 = bint_alloc (x->len * 10, POSITIVE);
  t4 = bint_alloc (x->len * 10, POSITIVE);
  bint_clean (Q->x);
  bint_clean (Q->y);

  J = bint_alloc (32, POSITIVE);
  J->digits[0] = 0;
  J->len = 1;
  t = bint_mul_long (x, K, t);
  bint_normalize (t);
  for (j = 0; j < K; j++)
    {
      xj[j] = bint_alloc (x->len * 10, POSITIVE);
      bint_clean (xj[j]);
      bint_copy (xj[j], t);
      bint_inc (t);
    }
  for (j = 0; j < K; j++)
    {
      sj[j] = bint_alloc (xj[j]->len * 6, POSITIVE);
      t = bint_pow2long (xj[j], 3, t);
      t2 = bint_mul_long (xj[j], 3, t2);
      t3 = bint_sub (t, t2, t3);
      t4 = bint_add (t3, b, t4);
      bint_mod (t4, p, sj[j]);
      bint_normalize (sj[j]);
      bint_clean (t4);

      t4 = bint_mod_exp (sj[j], p_minus_1_by_2, p, t4);
      bint_dec (t4);
      if (bint_is_zero (t4))
	{
	  /* Calculate square root of sj[j] because now is a square mod p */
	  bint_clean (Q->y);
	  bint_mod_exp (sj[j], p_plus_1_by_4, p, Q->y);
	  bint_copy (Q->x, xj[j]);
	  break;
	}
      bint_clean (t);
    }
  
     for (j - 1; j >= 0; j--)
     bint_free (sj[j]);

     for (j = 0; j < K; j++)
     {
     bint_free (xj[j]);
     }


     bint_free (t);
     bint_free (t2);
     bint_free (t3);
     bint_free (t4);

     free (xj);
     free (sj);
   
  Q->infinity = 0;
  return;
}

int
points_are_equal (const point_t * a, const point_t * b)
{
  int x, y;
  x = bint_cmp (a->x, b->x);
  y = bint_cmp (a->y, b->y);
  if (x == y)
    {
      if (x == EQUAL)
	return 1;
    }
  return 0;
}

void
lecc_point_double (const point_t * a, point_t * r)
{
  bint *s, *t1, *t2, *t3, *t4, *t5;
  t1 = bint_alloc (a->x->len * 30, POSITIVE);
  t2 = bint_alloc (a->x->len * 30, POSITIVE);
  t3 = bint_alloc (a->x->len * 30, POSITIVE);
  s = bint_alloc (a->x->len * 30, POSITIVE);
  if (a->infinity)
    {
      r->infinity = 1;
      bint_clean (r->x);
      bint_clean (r->y);
      r->x->len = 1;
      r->y->len = 1;
      return;
    }

/* First we calculate the derivative in the point a */

/* This is t2 = 3*(a->x)^2 + A  (A=-3 so we just dec three times) */
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (s);
  bint_copy (t3, a->x);
  t1 = bint_mul (a->x, t3, t1);
  t2 = bint_mul_long (t1, 3, t2);
  bint_clean (t1);
  bint_clean (t3);

/* This is because (3x^2 + A)  and A = -3 */
  bint_dec (t2);
  bint_dec (t2);
  bint_dec (t2);


/* whis is t3 = 1/(2*a->y) */
  t1 = bint_mul_long (a->y, 2, t1);
  t3 = bint_inverse (t1, p, t3);
/* Now we calculate t2*t3 = s */
  s = bint_mul (t2, t3, s);
  bint_clean (t1);
  bint_mod (s, p, t1);
  bint_clean (s);
  bint_copy (s, t1);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);

/* Now we calculate the x coordinate of the resulting point */
  bint_copy (t3, s);
  t1 = bint_mul (s, t3, t1);
  t2 = bint_mul_long (a->x, 2, t2);
  r->x = bint_sub (t1, t2, r->x);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  t1 = bint_mod (r->x, p, t1);
  bint_clean (r->x);
  bint_copy (r->x, t1);
/* Now we calculate the y coordinate of the resulting point */
  bint_clean (t1);
  t1 = bint_sub (a->x, r->x, t1);
  t2 = bint_mul (s, t1, t2);
  bint_clean (t1);
  t3 = bint_mod (t2, p, t3);
  bint_clean (t2);
  bint_copy (t2, t3);

  r->y = bint_sub (t2, a->y, r->y);

  r->infinity = 0;

  bint_clean (t1);
  bint_clean (t2);

  t1 = bint_mod (r->x, p, t1);
  t2 = bint_mod (r->y, p, t2);

  bint_clean (r->x);
  bint_clean (r->y);

  bint_copy (r->x, t1);
  bint_copy (r->y, t2);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (s);

  return;

}

void
lecc_point_scalar_mul_long (long k, point_t * a, point_t * r)
{
  int i;
  point_t *t1, *a_acum;

  t1 = lecc_point_alloc ();
  a_acum = lecc_point_alloc ();

  lecc_point_clean (a_acum);
  lecc_point_clean (t1);

  for (i = 0; i < k; i++)
    {
      lecc_point_add (a, a_acum, t1);
      lecc_point_clean (a_acum);
      lecc_point_copy (a_acum, t1);
      lecc_point_clean (t1);
    }
  lecc_point_copy (r, a_acum);
  lecc_point_free (a_acum);
  lecc_point_free (t1);
  return;
}

void
lecc_point_add (const point_t * a, const point_t * b, point_t * r)
{
  bint *s, *t1, *t2, *t3, *t4, *t5, *t;
  int fsize = (a->x->len + b->x->len + p->len) * 3 + 1;
  bint_clean (r->x);
  bint_clean (r->y);
  r->infinity = 0;

  if (points_are_equal (a, b))
    {
      lecc_point_double (a, r);
      return;
    }

  if (a->infinity)
    {
      lecc_point_copy (r, (point_t *) b);
      return;
    }
  if (b->infinity)
    {
      lecc_point_copy (r, (point_t *) a);
      return;
    }


  t = bint_alloc (a->y->len + b->y->len, POSITIVE);

  if (bint_is_zero (bint_add (a->y, b->y, t)))
    {
      printf ("infinito!!!\n");
      bint_clean (r->x);
      bint_clean (r->y);
      bint_free (t);
      r->infinity = 1;
      return;
    }

  if (b->infinity)
    if (!b->infinity)
      {
	bint_copy (r->x, a->x);
	bint_copy (r->y, a->y);
	r->infinity = 0;
	return;
      }


  if (a->infinity)
    if (!b->infinity)
      {
	bint_copy (r->x, b->x);
	bint_copy (r->y, b->y);
	r->infinity = 0;
	return;
      }
  s = bint_alloc (fsize, POSITIVE);
  t1 = bint_alloc (fsize, POSITIVE);
  t2 = bint_alloc (fsize, POSITIVE);
  t3 = bint_alloc (fsize, POSITIVE);
  t4 = bint_alloc (fsize, POSITIVE);
  t5 = bint_alloc (fsize, POSITIVE);
/* We calculate the substractions for the slope */
  t1 = bint_sub (b->y, a->y, t1);
  t2 = bint_sub (b->x, a->x, t2);


/* here we t3=a->y-b->y and  t4 = a->x - b->x modulo p */
  t3 = bint_mod (t1, p, t3);
  t4 = bint_mod (t2, p, t4);


/* t5 has the inverse a->x - b->x */

  t5 = bint_inverse (t4, p, t5);
/*
   t5 = bint_inverse (t2, p, t5);   // quitar
*/

  bint_clean (t1);
  bint_clean (t2);
  t1 = bint_mul (t5, t3, t1);

/* here is the slope */
  bint_clean (s);
  s = bint_mod (t1, p, s);
  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (t4);
  bint_clean (t5);

/* We calculate to t1 = s^2 */
  bint_copy (t5, s);
  t1 = bint_mul (s, t5, t1);
  t2 = bint_mod (t1, p, t2);

  bint_clean (t1);
  bint_copy (t1, t2);
  bint_clean (t2);
  bint_clean (t5);

/* We calculate t2 = s^2 - a->x */
  t2 = bint_sub (t1, a->x, t2);

/* We calculate t1 = t2 - b->x  = (s^2 - a->x) - b->x */
  bint_clean (t1);
  t1 = bint_sub (t2, b->x, t1);
/* Here we have the x coordinate of the sum */

  r->x = bint_mod (t1, p, r->x);

  bint_clean (t1);
  bint_clean (t2);
  bint_clean (t3);
  bint_clean (t4);

/* Calculating t2 = a->x - r->x */
  t2 = bint_sub (a->x, r->x, t2);
  t3 = bint_mod (t2, p, t3);
  bint_clean (t2);
  bint_copy (t2, t3);
  bint_clean (t3);
/* We calculate t3 = s*(a->x - r->x) */
  t3 = bint_mul (s, t2, t3);

  t4 = bint_sub (t3, a->y, t4);

  r->y = bint_mod (t4, p, r->y);
   
     bint_free (s);
     bint_free (t1);
     bint_free (t2);
     bint_free (t3);
     bint_free (t4);
     bint_free (t5);
   
  return;

}

void *
lecc_point_alloc ()
{
  point_t *z;
  z = calloc (1, sizeof (struct point));
/* Don't ask */
  z->x = bint_alloc (p->len * 10, POSITIVE);
  z->y = bint_alloc (p->len * 10, POSITIVE);
  return z;
}

void
lecc_point_free (point_t * m)
{
  bint_free (m->x);
  bint_free (m->y);
  free (m);
  return;
}

void
lecc_point_print (point_t * m, char *name)
{
  if (name != NULL)
    printf ("\n");
  printf ("Point %s coordinates\n", name);
  printf ("x=");
  bint_print (m->x);
  printf ("y=");
  bint_print (m->y);
  return;
}

/*
int
main (int argc, char **argv)
{
  point_t *U, *V, *W, *Z;
  bint *r, *s, *t;
  int l1 = strlen (argv[1]) + 1;
  int l2 = strlen (argv[2]) + 1;
  r = bint_alloc (l1, POSITIVE);
  s = bint_alloc (l2, POSITIVE);
  r = atobint (argv[1], r);
  s = atobint (argv[2], s);
  lecc_initialize_parameters ();
  U = lecc_point_alloc ();
  V = lecc_point_alloc ();
  W = lecc_point_alloc ();
  Z = lecc_point_alloc ();
  lecc_message_to_point (r, U);
  lecc_point_scalar_mul_long (atoi(argv[2]), U, W);
  printf("K=%d\n",atoi(argv[2]));
  lecc_point_print (U, "U=Initial_Point");
  lecc_point_print (W, "V=Point U*k");
  lecc_point_scalar_mul(s,U,Z);
  bint_debug (s, "K");
  lecc_point_print (Z, "K*U exp");
  lecc_free_parameters ();
  return 0;
}
*/
