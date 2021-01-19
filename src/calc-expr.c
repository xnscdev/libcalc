/*************************************************************************
 * calc-expr.c -- This file is part of libcalc.                          *
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

#include "calc-expr.h"

G_DEFINE_ABSTRACT_TYPE (CalcExpr, calc_expr, G_TYPE_OBJECT)

static void
calc_expr_class_init (CalcExprClass *klass)
{
  klass->equivalent = NULL;
}

static void
calc_expr_init (CalcExpr *self)
{
}

/**
 * calc_expr_equivalent:
 * @self: the first expression
 * @other: the second expression
 *
 * Compares two expressions to determine if they are equivalent. Expressions
 * are equivalent if one can be rewritten as the other.
 *
 * Returns: %TRUE if both expressions are valid and equivalent, otherwise %FALSE
 **/

gboolean
calc_expr_equivalent (CalcExpr *self, CalcExpr *other)
{
  CalcExprClass *klass;
  g_return_val_if_fail (CALC_IS_EXPR (self), FALSE);
  g_return_val_if_fail (CALC_IS_EXPR (other), FALSE);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_val_if_fail (klass->equivalent != NULL, FALSE);
  return klass->equivalent (self, other);
}
