/*************************************************************************
 * calc-term.c -- This file is part of libcalc.                      *
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
  self->factors = g_ptr_array_new ();
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
  gint i;

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
  return FALSE; /* TODO Implement */
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
