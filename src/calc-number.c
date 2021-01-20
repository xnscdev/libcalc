/*************************************************************************
 * calc-number.c -- This file is part of libcalc.                        *
 * Copyright (C) 2020 XNSC                                               *
 *                                                                       *
 * libcalc is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * libcalc is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program. If not, see <https://www.gnu.org/licenses/>. *
 *************************************************************************/

#include <stdio.h> /* mpfr_fprintf() */
#include "calc-number.h"

G_DEFINE_TYPE (CalcNumber, calc_number, CALC_TYPE_EXPR)

static void calc_number_print (CalcExpr *expr, FILE *stream);
static gboolean calc_number_equivalent (CalcExpr *self, CalcExpr *other);

static void
calc_number_dispose (GObject *obj)
{
  CalcNumber *self = CALC_NUMBER (obj);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_clear (self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_clear (self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_clear (self->floating);
      break;
    }
}

static void
calc_number_class_init (CalcNumberClass *klass)
{
  G_OBJECT_CLASS (klass)->dispose = calc_number_dispose;
  CALC_EXPR_CLASS (klass)->print = calc_number_print;
  CALC_EXPR_CLASS (klass)->equivalent = calc_number_equivalent;
}

static void
calc_number_init (CalcNumber *self)
{
}

static void
calc_number_print (CalcExpr *expr, FILE *stream)
{
  CalcNumber *self = CALC_NUMBER (expr);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_out_str (stream, 10, self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_out_str (stream, 10, self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      /* TODO Customizable precision printing */
      mpfr_fprintf (stream, "%.8RNf", self->floating);
      break;
    }
}

static gboolean
calc_number_equivalent (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_NUMBER (other), FALSE);
  return calc_number_cmp (CALC_NUMBER (self), CALC_NUMBER (other)) == 0;
}

static CalcNumberType
calc_number_get_final_type (CalcNumberType a, CalcNumberType b)
{
  return a > b ? a : b;
}

/**
 * calc_number_new:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber by copying the data of @value. If @value
 * is %NULL, the new instance is initialized to an integer value of zero.
 *
 * Returns: the newly constructed instance, or %NULL if @value is not a
 * valid #CalcNumber and not %NULL
 **/

CalcNumber *
calc_number_new (CalcNumber *value)
{
  CalcNumber *self;
  g_return_val_if_fail (value == NULL || CALC_IS_NUMBER (value), NULL);
  self = g_object_new (CALC_TYPE_NUMBER, NULL);
  if (value == NULL)
    {
      self->type = CALC_NUMBER_TYPE_INTEGER;
      mpz_init (self->integer);
    }
  else
    {
      self->type = value->type;
      switch (self->type)
	{
	case CALC_NUMBER_TYPE_INTEGER:
	  mpz_init_set (self->integer, value->integer);
	  break;
	case CALC_NUMBER_TYPE_RATIONAL:
	  mpq_init (self->rational);
	  mpq_set (self->rational, value->rational);
	  break;
	case CALC_NUMBER_TYPE_FLOATING:
	  mpfr_init_set (self->floating, value->floating, MPFR_RNDN);
	  break;
	}
    }
  return self;
}

/**
 * calc_number_new_f:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP floating-point
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_FLOATING.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_f (mpf_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set_f (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_fr:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MPFR
 * floating-point number @value. The number will have a type set to
 * %CALC_NUMBER_TYPE_FLOATING.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_fr (mpfr_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_q:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP rational
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_RATIONAL.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_q (mpq_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpq_init (self->rational);
  mpq_set (self->rational, value);
  self->type = CALC_NUMBER_TYPE_RATIONAL;
  return self;
}

/**
 * calc_number_new_z:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_z (mpz_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

/**
 * calc_number_new_d:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the 64-bit floating-point
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_FLOATING.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_d (double value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set_d (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_ui:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the unsigned integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_ui (unsigned long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_ui (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

/**
 * calc_number_new_si:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the signed integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 *
 * Returns: the newly constructed instance
 **/

CalcNumber *
calc_number_new_si (signed long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_si (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

/**
 * calc_number_add:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a or @b are invalid
 * numbers, no action is performed.
 **/

void
calc_number_add (CalcNumber **result, CalcNumber *a, CalcNumber *b)
{
  CalcNumberType type;
  CalcNumber *ca;
  CalcNumber *cb;

  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));
  g_return_if_fail (CALC_IS_NUMBER (b));

  type = calc_number_get_final_type (a->type, b->type);
  ca = calc_number_new (a);
  cb = calc_number_new (b);
  calc_number_cast (ca, type);
  calc_number_cast (cb, type);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    calc_number_dispose (G_OBJECT (result));
  switch (type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init ((*result)->integer);
      mpz_add ((*result)->integer, ca->integer, cb->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_add ((*result)->rational, ca->rational, cb->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add ((*result)->floating, ca->floating, cb->floating, MPFR_RNDN);
      break;
    }
  (*result)->type = type;

  g_object_unref (ca);
  g_object_unref (cb);
}

/**
 * calc_number_add_z:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_z (CalcNumber **result, CalcNumber *a, mpz_t b)
{
  mpq_t temp;
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));
  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    calc_number_dispose (G_OBJECT (result));
  (*result)->type = a->type;
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init ((*result)->integer);
      mpz_add ((*result)->integer, a->integer, b);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_init (temp);
      mpq_set_z (temp, b);
      mpq_add ((*result)->rational, a->rational, temp);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_z ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_q:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_q (CalcNumber **result, CalcNumber *a, mpq_t b)
{
  mpq_t temp;
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));
  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    calc_number_dispose (G_OBJECT (result));
  (*result)->type = a->type;
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      (*result)->type = CALC_NUMBER_TYPE_RATIONAL;
      mpq_init ((*result)->rational);
      mpq_init (temp);
      mpq_set_z (temp, a->integer);
      mpq_add ((*result)->rational, temp, b);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_add ((*result)->rational, a->rational, b);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_q ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_f:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_f (CalcNumber **result, CalcNumber *a, mpf_t b)
{
  mpfr_t temp;
  mpfr_init_set_f (temp, b, MPFR_RNDN);
  calc_number_add_fr (result, a, temp);
  mpfr_clear (temp);
}

/**
 * calc_number_add_fr:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_fr (CalcNumber **result, CalcNumber *a, mpfr_t b)
{
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));
  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    calc_number_dispose (G_OBJECT (result));
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z ((*result)->floating, a->integer, MPFR_RNDN);
      mpfr_add ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q ((*result)->floating, a->rational, MPFR_RNDN);
      mpfr_add ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_cmp:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a and @b are invalid numbers
 **/

gint
calc_number_cmp (CalcNumber *a, CalcNumber *b)
{
  CalcNumberType type;
  CalcNumber *ca;
  CalcNumber *cb;
  gint result;

  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  g_return_val_if_fail (CALC_IS_NUMBER (b), 0);

  type = calc_number_get_final_type (a->type, b->type);
  ca = calc_number_new (a);
  cb = calc_number_new (b);
  calc_number_cast (ca, type);
  calc_number_cast (cb, type);

  switch (type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      result = mpz_cmp (ca->integer, cb->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      result = mpq_cmp (ca->rational, cb->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      result = mpfr_cmp (ca->floating, cb->floating);
      break;
    default:
      return 0;
    }

  g_object_unref (ca);
  g_object_unref (cb);
  return result;
}

/**
 * calc_number_cmp_z:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_z (CalcNumber *a, mpz_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_z (a->rational, b);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_z (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_q:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_q (CalcNumber *a, mpq_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpq_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp (a->rational, b);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_q (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_f:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_f (CalcNumber *a, mpf_t b)
{
  mpq_t temp;
  gint result;
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpf_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init (temp);
      mpq_set_f (temp, b);
      result = mpq_cmp (a->rational, temp);
      mpq_clear (temp);
      return result;
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_f (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_fr:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_fr (CalcNumber *a, mpfr_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpfr_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      return -mpfr_cmp_q (b, a->rational);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_d:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_d (CalcNumber *a, double b)
{
  mpfr_t temp;
  gint result;
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_d (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init (temp);
      mpfr_set_q (temp, a->rational, MPFR_RNDN);
      result = mpfr_cmp_d (temp, b);
      mpfr_clear (temp);
      return result;
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_d (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_ui:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_ui (CalcNumber *a, unsigned long b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_ui (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_ui (a->rational, b, 1);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_ui (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_si:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_si (CalcNumber *a, signed long b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_si (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_si (a->rational, b, 1);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_si (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cast:
 * @self: the number to cast
 * @type: the type to cast to
 *
 * Changes the type of @self to @type and sets its value to a representation
 * of the original value with the new type. If @self is not a valid expression
 * or @type is not a valid type or is a type that cannot be cast to without
 * losing precision, no action is performed.
 **/

void
calc_number_cast (CalcNumber *self, CalcNumberType type)
{
  g_return_if_fail (CALC_IS_NUMBER (self));
  if (self->type == type)
    return;
  g_return_if_fail (type > self->type && type < N_CALC_NUMBER_TYPE);
  switch (type)
    {
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init (self->rational);
      mpq_set_z (self->rational, self->integer);
      mpz_clear (self->integer);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init (self->floating);
      if (self->type == CALC_NUMBER_TYPE_RATIONAL)
	{
	  mpfr_set_q (self->floating, self->rational, MPFR_RNDN);
	  mpq_clear (self->rational);
	}
      else
	{
	  mpfr_set_z (self->floating, self->integer, MPFR_RNDD);
	  mpz_clear (self->integer);
	}
      break;
    default:
      break;
    }
  self->type = type;
}
