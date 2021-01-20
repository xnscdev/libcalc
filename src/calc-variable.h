/*************************************************************************
 * calc-variable.h -- This file is part of libcalc.                        *
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

#ifndef _CALC_VARIABLE_H
#define _CALC_VARIABLE_H

#include <mpfr.h>
#include "calc-expr.h"

G_BEGIN_DECLS

#define CALC_TYPE_VARIABLE calc_variable_get_type ()
G_DECLARE_FINAL_TYPE (CalcVariable, calc_variable, CALC, VARIABLE, CalcExpr)

struct _CalcVariableClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcVariable:
 *
 * Represents a variable that may be set to a constant value.
 **/

struct _CalcVariable
{
  /*< private >*/
  CalcExpr parent;
  gchar *text;
};

CalcVariable *calc_variable_new (const gchar *text);
void calc_variable_set_value (const gchar *name, CalcExpr *value);
CalcExpr *calc_variable_get_value (const gchar *name);

G_END_DECLS

#endif
