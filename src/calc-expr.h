/*************************************************************************
 * calc-expr.h -- This file is part of libcalc.                          *
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

#ifndef _CALC_EXPR_H
#define _CALC_EXPR_H

#include <pango/pangocairo.h>
#include <glib-object.h>
#include <stdio.h>

G_BEGIN_DECLS

#define CALC_TYPE_EXPR calc_expr_get_type ()
G_DECLARE_DERIVABLE_TYPE (CalcExpr, calc_expr, CALC, EXPR, GObject)

/**
 * CalcExprClass:
 * @render: renders an expression on a #cairo_t object
 * @get_dims: determines the graphical dimensions of an object
 * @print: prints an expression to a stdio stream
 * @equivalent: checks if two expressions are equivalent
 * @like_terms: checks if two expressions are like terms
 * @hash: computes a hash of an expression
 * @evaluate: evaluates an arithmetic expression
 *
 * Class type for mathematical expressions.
 **/

struct _CalcExprClass
{
  /*< private >*/
  GObjectClass parent;
  gpointer padding[9];

  /*< public >*/
  void (*render) (CalcExpr *self, cairo_t *cr, gsize size);
  void (*get_dims) (CalcExpr *self, cairo_t *cr, gint *width, gint *height,
		    gsize size);
  void (*print) (CalcExpr *self, FILE *stream);
  gboolean (*equivalent) (CalcExpr *self, CalcExpr *other);
  gboolean (*like_terms) (CalcExpr *self, CalcExpr *other);
  gulong (*hash) (CalcExpr *self);
  gboolean (*evaluate) (CalcExpr *self, CalcExpr *result);
};

void calc_expr_render (CalcExpr *self, cairo_t *cr, gsize size);
void calc_expr_get_dims (CalcExpr *self, cairo_t *cr, gint *width, gint *height,
			 gsize size);
void calc_expr_print (CalcExpr *self, FILE *stream);
gboolean calc_expr_equivalent (CalcExpr *self, CalcExpr *other);
gboolean calc_expr_like_terms (CalcExpr *self, CalcExpr *other);
gulong calc_expr_hash (CalcExpr *self);
gboolean calc_expr_evaluate (CalcExpr *self, CalcExpr *result);

G_END_DECLS

#endif
