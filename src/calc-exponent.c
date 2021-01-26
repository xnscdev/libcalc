/*************************************************************************
 * calc-exponent.c -- This file is part of libcalc.                      *
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

#include "calc-number.h"
#include "calc-exponent.h"

G_DEFINE_TYPE (CalcExponent, calc_exponent, CALC_TYPE_EXPR)

static void calc_exponent_print (CalcExpr *expr, FILE *stream);
static gboolean calc_exponent_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_exponent_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_exponent_hash (CalcExpr *expr);
static gboolean calc_exponent_evaluate (CalcExpr *expr, CalcExpr *result);

static void
calc_exponent_class_init (CalcExponentClass *klass)
{
  CalcExprClass *exprclass = CALC_EXPR_CLASS (klass);
  exprclass->print = calc_exponent_print;
  exprclass->equivalent = calc_exponent_equivalent;
  exprclass->like_terms = calc_exponent_like_terms;
  exprclass->hash = calc_exponent_hash;
  exprclass->evaluate = calc_exponent_evaluate;
}

static void
calc_exponent_init (CalcExponent *self)
{
}

static void
calc_exponent_print (CalcExpr *expr, FILE *stream)
{
  CalcExponent *self = CALC_EXPONENT (expr);
  fputc ('(', stream);
  calc_expr_print (self->base, stream);
  fprintf (stream, ")^(");
  calc_expr_print (self->power, stream);
  fputc (')', stream);
}

static gboolean
calc_exponent_equivalent (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_EXPONENT (other), FALSE);
  return calc_expr_equivalent (CALC_EXPONENT (self)->base,
			       CALC_EXPONENT (other)->base)
    && calc_expr_equivalent (CALC_EXPONENT (self)->power,
			     CALC_EXPONENT (other)->power);
}

static gboolean
calc_exponent_like_terms (CalcExpr *self, CalcExpr *other)
{
  return calc_exponent_equivalent (self, other);
}

static gulong
calc_exponent_hash (CalcExpr *expr)
{
  CalcExponent *self = CALC_EXPONENT (expr);
  return calc_expr_hash (self->base) + calc_expr_hash (self->power);
}

static gboolean
calc_exponent_evaluate (CalcExpr *expr, CalcExpr *result)
{
  CalcNumber *base_result;
  CalcNumber *power_result;
  CalcNumber *nresult;
  CalcExponent *self = CALC_EXPONENT (expr);

  g_return_val_if_fail (CALC_IS_NUMBER (result), FALSE);
  base_result = calc_number_new (NULL);
  power_result = calc_number_new (NULL);
  nresult = CALC_NUMBER (result);

  if (!calc_expr_evaluate (self->base, CALC_EXPR (base_result)))
    goto err_exit;
  if (!calc_expr_evaluate (self->power, CALC_EXPR (power_result)))
    goto err_exit;
  calc_number_pow (&nresult, base_result, power_result);

  g_object_unref (base_result);
  g_object_unref (power_result);
  return TRUE;

 err_exit:
  g_object_unref (base_result);
  g_object_unref (power_result);
  return FALSE;
}

/**
 * calc_exponent_new:
 * @base: the base of the exponent
 * @power: the power to raise the base to
 *
 * Creates a new exponent object with a base of @base and a power of @power.
 * @base and @power should not be freed until the created instance is no longer
 * in use.
 *
 * Returns: the newly constructed instance, or %NULL if @base or @power are
 * invalid expressions
 **/

CalcExponent *
calc_exponent_new (CalcExpr *base, CalcExpr *power)
{
  CalcExponent *self;
  g_return_val_if_fail (CALC_IS_EXPR (base), NULL);
  g_return_val_if_fail (CALC_IS_EXPR (power), NULL);
  self = g_object_new (CALC_TYPE_EXPONENT, NULL);
  self->base = base;
  self->power = power;
  return self;
}

/**
 * calc_exponent_set_base:
 * @self: the exponent
 * @base: the new base
 *
 * Changes the base of @self to @base. @base should not be freed until @self
 * is no longer in use, but the previous base value of @self may be freed after
 * calling this function. If @self is an invalid exponent or @base is an
 * invalid expression, no action is performed.
 **/

void
calc_exponent_set_base (CalcExponent *self, CalcExpr *base)
{
  g_return_if_fail (CALC_IS_EXPONENT (self));
  g_return_if_fail (CALC_IS_EXPR (base));
  self->base = base;
}

/**
 * calc_exponent_get_base:
 * @self: the exponent
 *
 * Gets the base of @self, which may be modified but not freed.
 *
 * Returns: (transfer none): the base of @self, or %NULL if @self is an
 * invalid exponent
 **/

CalcExpr *
calc_exponent_get_base (CalcExponent *self)
{
  g_return_val_if_fail (CALC_IS_EXPONENT (self), NULL);
  return self->base;
}

/**
 * calc_exponent_set_power:
 * @self: the exponent
 * @power: the new power
 *
 * Changes the power of @self to @power. @power should not be freed until @self
 * is no longer in use, but the previous power of @self may be freed after
 * calling this function. If @self is an invalid exponent or @power is an
 * invalid expression, no action is performed.
 **/

void
calc_exponent_set_power (CalcExponent *self, CalcExpr *power)
{
  g_return_if_fail (CALC_IS_EXPONENT (self));
  g_return_if_fail (CALC_IS_EXPR (power));
  self->power = power;
}

/**
 * calc_exponent_get_power:
 * @self: the exponent
 *
 * Gets the power of @self, which may be modified but not freed.
 *
 * Returns: (transfer none): the power of @self, or %NULL if @self is an
 * invalid exponent
 **/

CalcExpr *
calc_exponent_get_power (CalcExponent *self)
{
  g_return_val_if_fail (CALC_IS_EXPONENT (self), NULL);
  return self->power;
}
