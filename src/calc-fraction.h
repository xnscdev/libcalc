/*************************************************************************
 * calc-fraction.h -- This file is part of libcalc.                      *
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

#ifndef _CALC_FRACTION_H
#define _CALC_FRACTION_H

#include <mpfr.h>
#include "calc-expr.h"

G_BEGIN_DECLS

#define CALC_TYPE_FRACTION calc_fraction_get_type ()
G_DECLARE_FINAL_TYPE (CalcFraction, calc_fraction, CALC, FRACTION, CalcExpr)

struct _CalcFractionClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcFraction:
 *
 * Represents a fraction with a numerator and denominator as expressions.
 **/

struct _CalcFraction
{
  /*< private >*/
  CalcExpr parent;
  CalcExpr *num;
  CalcExpr *denom;
};

CalcFraction *calc_fraction_new (CalcExpr *num, CalcExpr *denom);
void calc_fraction_set_num (CalcFraction *self, CalcExpr *num);
CalcExpr *calc_fraction_get_num (CalcFraction *self);
void calc_fraction_set_denom (CalcFraction *self, CalcExpr *denom);
CalcExpr *calc_fraction_get_denom (CalcFraction *self);

G_END_DECLS

#endif
