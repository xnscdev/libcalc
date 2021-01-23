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
