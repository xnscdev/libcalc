/*************************************************************************
 * calc-fraction.c -- This file is part of libcalc.                      *
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

#include "calc-number.h"
#include "calc-fraction.h"

G_DEFINE_TYPE (CalcFraction, calc_fraction, CALC_TYPE_EXPR)

static void calc_fraction_print (CalcExpr *expr, FILE *stream);
static gboolean calc_fraction_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_fraction_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_fraction_hash (CalcExpr *expr);
static gboolean calc_fraction_evaluate (CalcExpr *expr, CalcExpr *result);

static void
calc_fraction_class_init (CalcFractionClass *klass)
{
  CalcExprClass *exprclass = CALC_EXPR_CLASS (klass);
  exprclass->print = calc_fraction_print;
  exprclass->equivalent = calc_fraction_equivalent;
  exprclass->like_terms = calc_fraction_like_terms;
  exprclass->hash = calc_fraction_hash;
  exprclass->evaluate = calc_fraction_evaluate;
}

static void
calc_fraction_init (CalcFraction *self)
{
}

static void
calc_fraction_print (CalcExpr *expr, FILE *stream)
{
  CalcFraction *self = CALC_FRACTION (expr);
  calc_expr_print (self->num, stream);
  fputc ('/', stream);
  calc_expr_print (self->denom, stream);
}

static gboolean
calc_fraction_equivalent (CalcExpr *self, CalcExpr *other)
{
  /* TODO Common factors in numerator and denominator */
  g_return_val_if_fail (CALC_IS_FRACTION (other), FALSE);
  return calc_expr_equivalent (CALC_FRACTION (self)->num,
			       CALC_FRACTION (other)->num)
    && calc_expr_equivalent (CALC_FRACTION (self)->denom,
			     CALC_FRACTION (other)->denom);
}

static gboolean
calc_fraction_like_terms (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_FRACTION (other), FALSE);
  return calc_expr_equivalent (CALC_FRACTION (self)->denom,
			       CALC_FRACTION (other)->denom);
}

static gulong
calc_fraction_hash (CalcExpr *expr)
{
  CalcFraction *self = CALC_FRACTION (expr);
  return calc_expr_hash (self->num) + calc_expr_hash (self->denom);
}

static gboolean
calc_fraction_evaluate (CalcExpr *expr, CalcExpr *result)
{
  CalcNumber *num_result;
  CalcNumber *denom_result;
  CalcNumber *nresult;
  CalcFraction *self = CALC_FRACTION (expr);

  g_return_val_if_fail (CALC_IS_NUMBER (result), FALSE);
  num_result = calc_number_new (NULL);
  denom_result = calc_number_new (NULL);
  nresult = CALC_NUMBER (result);

  if (!calc_expr_evaluate (self->num, CALC_EXPR (num_result)))
    goto err_exit;
  if (!calc_expr_evaluate (self->denom, CALC_EXPR (denom_result)))
    goto err_exit;
  calc_number_div (&nresult, num_result, denom_result);

  g_object_unref (num_result);
  g_object_unref (denom_result);
  return TRUE;

 err_exit:
  g_object_unref (num_result);
  g_object_unref (denom_result);
  return FALSE;
}

/**
 * calc_fraction_new:
 * @num: the numerator
 * @denom: the denominator
 *
 * Creates a new fraction object with a numerator of @num and a denominator
 * of @denom. @num and @denom should not be freed until the created instance
 * is no longer in use.
 *
 * Returns: the newly constructed instance, or %NULL if @num or @denom are
 * invalid expressions
 **/

CalcFraction *
calc_fraction_new (CalcExpr *num, CalcExpr *denom)
{
  CalcFraction *self;
  g_return_val_if_fail (CALC_IS_EXPR (num), NULL);
  g_return_val_if_fail (CALC_IS_EXPR (denom), NULL);
  self = g_object_new (CALC_TYPE_FRACTION, NULL);
  self->num = num;
  self->denom = denom;
  return self;
}

/**
 * calc_fraction_set_num:
 * @self: the fraction
 * @num: the new numerator
 *
 * Changes the numerator of @self to @num. If @self is an invalid fraction
 * or @num is an invalid expression, no action is performed. @num should not
 * be freed until @self is no longer in use.
 **/

void
calc_fraction_set_num (CalcFraction *self, CalcExpr *num)
{
  g_return_if_fail (CALC_IS_FRACTION (self));
  g_return_if_fail (CALC_IS_EXPR (num));
  self->num = num;
}

/**
 * calc_fraction_get_num:
 * @self: the fraction
 *
 * Gets the numerator of @self, which may be modified but should not be freed.
 *
 * Returns: the numerator of @self, or %NULL if @self is an invalid fraction
 **/

CalcExpr *
calc_fraction_get_num (CalcFraction *self)
{
  g_return_val_if_fail (CALC_IS_FRACTION (self), NULL);
  return self->num;
}

/**
 * calc_fraction_set_denom:
 * @self: the fraction
 * @denom: the new denominator
 *
 * Changes the denominator of @self to @denom. If @self is an invalid fraction
 * or @denom is an invalid expression, no action is performed. @denom should not
 * be freed until @self is no longer in use.
 **/

void
calc_fraction_set_denom (CalcFraction *self, CalcExpr *denom)
{
  g_return_if_fail (CALC_IS_FRACTION (self));
  g_return_if_fail (CALC_IS_EXPR (denom));
  self->denom = denom;
}

/**
 * calc_fraction_get_denom:
 * @self: the fraction
 *
 * Gets the denominator of @self, which may be modified but should not be freed.
 *
 * Returns: the denominator of @self, or %NULL if @self is an invalid fraction
 **/

CalcExpr *
calc_fraction_get_denom (CalcFraction *self)
{
  g_return_val_if_fail (CALC_IS_FRACTION (self), NULL);
  return self->denom;
}
