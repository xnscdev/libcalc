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

#include <glib-object.h>
#include <stdio.h>

G_BEGIN_DECLS

#define CALC_TYPE_EXPR calc_expr_get_type ()
G_DECLARE_DERIVABLE_TYPE (CalcExpr, calc_expr, CALC, EXPR, GObject)

/**
 * CalcExprClass:
 * @print: prints an expression to a stdio stream
 * @equivalent: checks if two expressions are equivalent
 *
 * Class type for mathematical expressions.
 **/

struct _CalcExprClass
{
  /*< private >*/
  GObjectClass parent;
  gpointer padding[14];

  /*< public >*/
  void (*print) (CalcExpr *, FILE *);
  gboolean (*equivalent) (CalcExpr *, CalcExpr *);
};

void calc_expr_print (CalcExpr *self, FILE *stream);
gboolean calc_expr_equivalent (CalcExpr *self, CalcExpr *other);

G_END_DECLS

#endif
