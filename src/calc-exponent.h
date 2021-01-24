/*************************************************************************
 * calc-exponent.h -- This file is part of libcalc.                      *
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

#ifndef _CALC_EXPONENT_H
#define _CALC_EXPONENT_H

#include "calc-expr.h"

G_BEGIN_DECLS

#define CALC_TYPE_EXPONENT calc_exponent_get_type ()
G_DECLARE_FINAL_TYPE (CalcExponent, calc_exponent, CALC, EXPONENT, CalcExpr)

struct _CalcExponentClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcExponent:
 *
 * Represents a base expression raised to a power expression.
 **/

struct _CalcExponent
{
  /*< private >*/
  CalcExpr parent;
  CalcExpr *base;
  CalcExpr *power;
};

CalcExponent *calc_exponent_new (CalcExpr *base, CalcExpr *power);
void calc_exponent_set_base (CalcExponent *self, CalcExpr *base);
CalcExpr *calc_exponent_get_base (CalcExponent *self);
void calc_exponent_set_power (CalcExponent *self, CalcExpr *power);
CalcExpr *calc_exponent_get_power (CalcExponent *self);

G_END_DECLS

#endif
