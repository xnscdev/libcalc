/*************************************************************************
 * calc-term.c -- This file is part of libcalc.                          *
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

#include "calc-exponent.h"
#include "calc-sum.h"
#include "calc-term.h"

G_DEFINE_TYPE (CalcTerm, calc_term, CALC_TYPE_EXPR)

static void calc_term_print (CalcExpr *expr, FILE *stream);
static gboolean calc_term_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_term_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_term_hash (CalcExpr *expr);
static gboolean calc_term_evaluate (CalcExpr *expr, CalcExpr *result);

static void
calc_term_dispose (GObject *obj)
{
  CalcTerm *self = CALC_TERM (obj);
  g_ptr_array_unref (self->factors);
}

static void
calc_term_factor_dispose (gpointer data)
{
  CalcExponent *self;
  g_return_if_fail (CALC_IS_EXPONENT (data));
  self = CALC_EXPONENT (data);
  g_object_unref (self->power);
  g_object_unref (self);
}

static void
calc_term_class_init (CalcTermClass *klass)
{
  CalcExprClass *exprclass = CALC_EXPR_CLASS (klass);
  G_OBJECT_CLASS (klass)->dispose = calc_term_dispose;
  exprclass->print = calc_term_print;
  exprclass->equivalent = calc_term_equivalent;
  exprclass->like_terms = calc_term_like_terms;
  exprclass->hash = calc_term_hash;
  exprclass->evaluate = calc_term_evaluate;
}

static void
calc_term_init (CalcTerm *self)
{
  self->factors = g_ptr_array_new_with_free_func (calc_term_factor_dispose);
}

static void
calc_term_factor_print (gpointer data, gpointer user_data)
{
  FILE *stream = (FILE *) user_data;
  CalcExpr *factor = CALC_EXPR (data);
  fputc ('(', stream);
  calc_expr_print (factor, stream);
  fputc (')', stream);
}

static void
calc_term_factor_hash (gpointer data, gpointer user_data)
{
  *((gulong *) user_data) += calc_expr_hash (CALC_EXPR (data));
}

static gint
calc_term_factor_compare (gconstpointer a, gconstpointer b)
{
  gulong ha = calc_expr_hash (*((CalcExpr **) a));
  gulong hb = calc_expr_hash (*((CalcExpr **) b));
  if (ha > hb)
    return 1;
  if (ha < hb)
    return -1;
  return 0;
}

static void
calc_term_print (CalcExpr *expr, FILE *stream)
{
  CalcTerm *self = CALC_TERM (expr);
  calc_expr_print (CALC_EXPR (self->coefficient), stream);
  g_ptr_array_foreach (self->factors, calc_term_factor_print, stream);
}

static gboolean
calc_term_equivalent (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_TERM (other), FALSE);
  return calc_expr_equivalent (CALC_EXPR (CALC_TERM (self)->coefficient),
			       CALC_EXPR (CALC_TERM (other)->coefficient))
    && calc_term_like_terms (self, other);
}

static gboolean
calc_term_like_terms (CalcExpr *self, CalcExpr *other)
{
  CalcTerm *term = CALC_TERM (self);
  CalcTerm *other_term;
  guint i;

  g_return_val_if_fail (CALC_IS_TERM (other), FALSE);
  other_term = CALC_TERM (other);
  if (term->factors->len != other_term->factors->len)
    return FALSE;

  g_ptr_array_sort (term->factors, calc_term_factor_compare);
  g_ptr_array_sort (other_term->factors, calc_term_factor_compare);
  for (i = 0; i < term->factors->len; i++)
    {
      if (!calc_expr_equivalent (CALC_EXPR (term->factors->pdata[i]),
				 CALC_EXPR (other_term->factors->pdata[i])))
	return FALSE;
    }
  return TRUE;
}

static gulong
calc_term_hash (CalcExpr *expr)
{
  CalcTerm *self = CALC_TERM (expr);
  gulong hash;
  g_ptr_array_foreach (self->factors, calc_term_factor_hash, &hash);
  return hash;
}

static gboolean
calc_term_evaluate (CalcExpr *expr, CalcExpr *result)
{
  CalcTerm *self = CALC_TERM (expr);
  CalcNumber *total = NULL;
  guint i;

  g_return_val_if_fail (CALC_IS_NUMBER (result), FALSE);
  /* Terms without factors behave as numbers */
  if (self->factors->len == 0)
    return calc_expr_evaluate (CALC_EXPR (self->coefficient), result);

  total = calc_number_new (self->coefficient);
  for (i = 0; i < self->factors->len; i++)
    {
      CalcNumber *ans = calc_number_new (NULL);
      CalcNumber *temp;
      if (!calc_expr_evaluate (self->factors->pdata[i], CALC_EXPR (ans)))
	{
	  g_object_unref (ans);
	  g_object_unref (total);
	  return FALSE;
	}
      temp = calc_number_new (total);
      calc_number_mul (&total, temp, ans);
      g_object_unref (ans);
      g_object_unref (temp);
    }

  calc_expr_evaluate (CALC_EXPR (total), result);
  g_object_unref (total);
  return TRUE;
}

/**
 * calc_term_new:
 * @coefficient: the coefficient of the term
 *
 * Creates a new term object with no factors and a coefficient set to
 * @coefficient.
 *
 * Returns: the newly constructed instance, or %NULL if @coefficient is an
 * invalid number
 **/

CalcTerm *
calc_term_new (CalcNumber *coefficient)
{
  CalcTerm *self;
  g_return_val_if_fail (CALC_IS_NUMBER (coefficient), NULL);
  self = g_object_new (CALC_TYPE_TERM, NULL);
  self->coefficient = coefficient;
  return self;
}

/**
 * calc_term_set_coefficient:
 * @self: the term
 * @coefficient: the new coefficient
 *
 * Changes the coefficient of @self to @coefficient. @coefficient should not
 * be freed until @self is no longer in use, but the previous coefficient of
 * @self may be freed after calling this function. If @self or @coefficient
 * are invalid, no action is performed.
 **/

void
calc_term_set_coefficient (CalcTerm *self, CalcNumber *coefficient)
{
  g_return_if_fail (CALC_IS_TERM (self));
  g_return_if_fail (CALC_IS_NUMBER (coefficient));
  self->coefficient = coefficient;
}

/**
 * calc_term_get_coefficient:
 * @self: the term
 *
 * Gets the coefficient of @self.
 *
 * Returns: (transfer none): the coefficient of @self, which may be modified
 * but not freed
 **/

CalcNumber *
calc_term_get_coefficient (CalcTerm *self)
{
  g_return_val_if_fail (CALC_IS_TERM (self), NULL);
  return self->coefficient;
}

/**
 * calc_term_add_factor:
 * @self: the term
 * @factor: the factor to add
 *
 * Adds the expression @factor as a factor of @self. @factor should not
 * be freed until @self is no longer in use. If @self or @factor are invalid,
 * no action is performed.
 *
 * Depending on the type of @factor, this function performs different actions.
 * If @factor is an instance of #CalcNumber, its value will be multiplied to
 * the coefficient of @self. If @factor is an exponent and there is another
 * factor of @self with the same base, the power of @factor is added to the
 * power of the other factor. For all other valid expressions, an instance
 * of #CalcExponent is appended to the list of factors of @self with a base of
 * @factor and a power of 1.
 **/

void
calc_term_add_factor (CalcTerm *self, CalcExpr *factor)
{
  guint i;
  g_return_if_fail (CALC_IS_TERM (self));
  g_return_if_fail (CALC_IS_EXPR (factor));

  if (CALC_IS_NUMBER (factor))
    {
      CalcNumber *temp = calc_number_new (self->coefficient);
      calc_number_mul (&self->coefficient, temp, CALC_NUMBER (factor));
      return;
    }

  for (i = 0; i < self->factors->len; i++)
    {
      CalcExpr *expr = self->factors->pdata[i];
      if (calc_expr_equivalent (factor, expr))
	{
	  if (CALC_IS_EXPONENT (expr))
	    {
	      CalcExponent *efactor = CALC_EXPONENT (factor);
	      CalcSum *sum = calc_sum_new (efactor->power);
	      CalcExponent *temp;
	      calc_sum_add_term (sum, CALC_EXPONENT (expr)->power);
	      temp = calc_exponent_new (efactor->base, CALC_EXPR (sum));
	      g_ptr_array_add (self->factors, temp);
	    }
	  else
	    {
	      CalcExponent *temp =
		calc_exponent_new (expr, CALC_EXPR (calc_number_new_ui (2)));
	      g_ptr_array_add (self->factors, temp);
	    }
	  return;
	}
    }

  if (CALC_IS_EXPONENT (factor))
    {
      /* Will be unref-ed on disposal */
      g_object_ref (CALC_EXPONENT (factor)->power);
      g_ptr_array_add (self->factors, factor);
    }
  else
    g_ptr_array_add (self->factors,
		     calc_exponent_new (factor,
					CALC_EXPR (calc_number_new_ui (1))));
}
