/*************************************************************************
 * calc-sum.c -- This file is part of libcalc.                           *
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

#include "calc-sum.h"

G_DEFINE_TYPE (CalcSum, calc_sum, CALC_TYPE_EXPR)

static void calc_sum_print (CalcExpr *expr, FILE *stream);
static gboolean calc_sum_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_sum_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_sum_hash (CalcExpr *expr);
static gboolean calc_sum_evaluate (CalcExpr *expr, CalcExpr *result);

static void
calc_sum_dispose (GObject *obj)
{
  CalcSum *self = CALC_SUM (obj);
  g_ptr_array_unref (self->terms);
}

static void
calc_sum_class_init (CalcSumClass *klass)
{
  CalcExprClass *exprclass = CALC_EXPR_CLASS (klass);
  G_OBJECT_CLASS (klass)->dispose = calc_sum_dispose;
  exprclass->print = calc_sum_print;
  exprclass->equivalent = calc_sum_equivalent;
  exprclass->like_terms = calc_sum_like_terms;
  exprclass->hash = calc_sum_hash;
  exprclass->evaluate = calc_sum_evaluate;
}

static void
calc_sum_init (CalcSum *self)
{
  self->terms = g_ptr_array_new ();
}

static void
calc_sum_term_hash (gpointer data, gpointer user_data)
{
  *((gulong *) user_data) += calc_expr_hash (CALC_EXPR (data));
}

static gint
calc_sum_term_compare (gconstpointer a, gconstpointer b)
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
calc_sum_print (CalcExpr *expr, FILE *stream)
{
  CalcSum *self = CALC_SUM (expr);
  guint i;
  for (i = 0; i < self->terms->len; i++)
    {
      if (i > 0)
	fputc ('+', stream);
      fputc ('(', stream);
      calc_expr_print (CALC_EXPR (self->terms->pdata[i]), stream);
      fputc (')', stream);
    }
}

static gboolean
calc_sum_equivalent (CalcExpr *self, CalcExpr *other)
{
  CalcSum *sum = CALC_SUM (self);
  CalcSum *other_sum;
  guint i;

  g_return_val_if_fail (CALC_IS_SUM (other), FALSE);
  other_sum = CALC_SUM (other);
  if (sum->terms->len != other_sum->terms->len)
    return FALSE;

  g_ptr_array_sort (sum->terms, calc_sum_term_compare);
  g_ptr_array_sort (other_sum->terms, calc_sum_term_compare);
  for (i = 0; i < sum->terms->len; i++)
    {
      if (!calc_expr_equivalent (CALC_EXPR (sum->terms->pdata[i]),
				 CALC_EXPR (other_sum->terms->pdata[i])))
	return FALSE;
    }
  return TRUE;
}

static gboolean
calc_sum_like_terms (CalcExpr *self, CalcExpr *other)
{
  return calc_sum_equivalent (self, other);
}

static gulong
calc_sum_hash (CalcExpr *expr)
{
  CalcSum *self = CALC_SUM (expr);
  gulong hash;
  g_ptr_array_foreach (self->terms, calc_sum_term_hash, &hash);
  return hash;
}

static gboolean
calc_sum_evaluate (CalcExpr *expr, CalcExpr *result)
{
  CalcSum *self = CALC_SUM (expr);
  CalcNumber *total = NULL;
  guint i;

  g_return_val_if_fail (CALC_IS_NUMBER (result), FALSE);
  for (i = 0; i < self->terms->len; i++)
    {
      CalcNumber *ans = calc_number_new (NULL);
      CalcNumber *temp;
      if (!calc_expr_evaluate (self->terms->pdata[i], CALC_EXPR (ans)))
	{
	  g_object_unref (ans);
	  g_object_unref (total);
	  return FALSE;
	}
      temp = calc_number_new (total);
      calc_number_add (&total, temp, ans);
      g_object_unref (ans);
      g_object_unref (temp);
    }

  calc_expr_evaluate (CALC_EXPR (total), result);
  g_object_unref (total);
  return TRUE;
}

/**
 * calc_sum_new:
 * @term: the initial term
 *
 * Creates a new sum object with a single term of @term. @term should not
 * be freed until the created instance is no longer in use.
 *
 * Returns: the newly constructed instance, or %NULL if @term is an invalid
 * expression
 **/

CalcSum *
calc_sum_new (CalcExpr *term)
{
  CalcSum *self;
  g_return_val_if_fail (CALC_IS_EXPR (term), NULL);
  self = g_object_new (CALC_TYPE_SUM, NULL);
  g_ptr_array_add (self->terms, term);
  return self;
}

/* TODO Adding terms to sum, combine like terms */
