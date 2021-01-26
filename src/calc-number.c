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

#define _LIBCALC_INTERNAL

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h> /* mpfr_fprintf() */
#include "calc-number.h"

G_DEFINE_TYPE (CalcNumber, calc_number, CALC_TYPE_EXPR)

static void calc_number_render (CalcExpr *expr, cairo_t *cr, gsize size);
static void calc_number_get_dims (CalcExpr *expr, cairo_t *cr, gint *width,
				  gint *height, gsize size);
static void calc_number_print (CalcExpr *expr, FILE *stream);
static gboolean calc_number_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_number_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_number_hash (CalcExpr *expr);
static gboolean calc_number_evaluate (CalcExpr *expr, CalcExpr *result);

static void
calc_number_dispose (GObject *obj)
{
  _calc_number_release (CALC_NUMBER (obj));
}

static void
calc_number_class_init (CalcNumberClass *klass)
{
  CalcExprClass *exprclass = CALC_EXPR_CLASS (klass);
  G_OBJECT_CLASS (klass)->dispose = calc_number_dispose;
  exprclass->render = calc_number_render;
  exprclass->get_dims = calc_number_get_dims;
  exprclass->print = calc_number_print;
  exprclass->equivalent = calc_number_equivalent;
  exprclass->like_terms = calc_number_like_terms;
  exprclass->hash = calc_number_hash;
  exprclass->evaluate = calc_number_evaluate;
  
}

static void
calc_number_init (CalcNumber *self)
{
}

static void
calc_number_render (CalcExpr *expr, cairo_t *cr, gsize size)
{
  CalcNumber *self = CALC_NUMBER (expr);
  gchar *text;
  PangoLayout *layout;

  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      gmp_asprintf (&text, "%Zd", self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      gmp_asprintf (&text, "%Qd", self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_asprintf (&text, "%.8RNf", self->floating);
      break;
    default:
      g_return_if_reached ();
    }

  layout = _calc_expr_layout_new (cr, _LIBCALC_REGULAR_FONT, size, text);
  pango_cairo_show_layout (cr, layout);
  free (text);
  g_object_unref (layout);
}

static void
calc_number_get_dims (CalcExpr *expr, cairo_t *cr, gint *width, gint *height,
		      gsize size)
{
  CalcNumber *self = CALC_NUMBER (expr);
  gchar *text;
  PangoLayout *layout;

  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      gmp_asprintf (&text, "%Zd", self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      gmp_asprintf (&text, "%Qd", self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_asprintf (&text, "%.8RNf", self->floating);
      break;
    default:
      g_return_if_reached ();
    }

  layout = _calc_expr_layout_new (cr, _LIBCALC_REGULAR_FONT, size, text);
  pango_layout_get_pixel_size (layout, width, height);
  free (text);
  g_object_unref (layout);
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

static gboolean
calc_number_like_terms (CalcExpr *self, CalcExpr *other)
{
  return CALC_IS_NUMBER (other);
}

static gulong
calc_number_hash (CalcExpr *expr)
{
  return 0; /* Hashes for constant numbers are meaningless */
}

static gboolean
calc_number_evaluate (CalcExpr *expr, CalcExpr *result)
{
  CalcNumber *self = CALC_NUMBER (expr);
  CalcNumber *ans;
  g_return_val_if_fail (CALC_IS_NUMBER (result), FALSE);
  ans = CALC_NUMBER (result);
  _calc_number_release (ans);
  ans->type = self->type;
  switch (ans->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init_set (ans->integer, self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init (ans->rational);
      mpq_set (ans->rational, self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init_set (ans->floating, self->floating, MPFR_RNDN);
      break;
    default:
      return FALSE;
    }
  return TRUE;
}

/**
 * calc_number_new:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber by copying the data of @value. If @value
 * is %NULL, the new instance is initialized to an integer value of zero.
 *
 * Returns: (transfer full): the newly constructed instance, or %NULL if @value
 * is not a valid #CalcNumber and not %NULL
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
      self->type = -1; /* Don't free anything */
      calc_number_copy (self, value);
    }
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
 * calc_number_copy:
 * @result: where to store the copied number
 * @self: the number to copy
 *
 * Copies the value of @self into @result. Any previous value of @result is
 * erased. If @result or @self are invalid numbers, no action is performed.
 **/

void
calc_number_copy (CalcNumber *result, CalcNumber *self)
{
  g_return_if_fail (CALC_IS_NUMBER (result));
  g_return_if_fail (CALC_IS_NUMBER (self));
  _calc_number_release (result);
  result->type = self->type;
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init_set (result->integer, self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init (result->rational);
      mpq_set (result->rational, self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init_set (result->floating, self->floating, MPFR_RNDN);
      break;
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

/**
 * calc_number_neg:
 * @result: the pointer to store the result
 * @self: the number
 *
 * Sets the value of @result to the additive inverse of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to
 * it. If @result is %NULL or @self is not a valid number, no action is
 * performed.
 **/

void
calc_number_neg (CalcNumber **result, CalcNumber *self)
{
  g_return_if_fail (result != NULL);
  g_return_if_fail (CALC_IS_NUMBER (self));

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = self->type;
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init ((*result)->integer);
      mpz_neg ((*result)->integer, self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_neg ((*result)->rational, self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_neg ((*result)->floating, self->floating, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_abs:
 * @result: the pointer to store the result
 * @self: the number
 *
 * Sets the value of @result to the absolute value of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to
 * it. If @result is %NULL or @self is not a valid number, no action is
 * performed.
 **/

void
calc_number_abs (CalcNumber **result, CalcNumber *self)
{
  g_return_if_fail (result != NULL);
  g_return_if_fail (CALC_IS_NUMBER (self));

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = self->type;
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init ((*result)->integer);
      mpz_abs ((*result)->integer, self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_abs ((*result)->rational, self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_abs ((*result)->floating, self->floating, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_sgn:
 * @self: the number
 *
 * Determines the sign of the number @self.
 *
 * Returns: positive if @self is positive, zero if @self is zero, or negative
 * if @self is negative or invalid
 **/

gint
calc_number_sgn (CalcNumber *self)
{
  g_return_val_if_fail (CALC_IS_NUMBER (self), -1);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_sgn (self->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_sgn (self->rational);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_sgn (self->floating);
    default:
      return -1;
    }
}

CalcNumberType
_calc_number_get_final_type (CalcNumberType a, CalcNumberType b)
{
  return a > b ? a : b;
}

void
_calc_number_release (CalcNumber *self)
{
  if (self->type == -1)
    return;
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
  self->type = -1;
}
