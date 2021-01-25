/*************************************************************************
 * calc-sum.h -- This file is part of libcalc.                           *
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

#ifndef _CALC_SUM_H
#define _CALC_SUM_H

#include "calc-number.h"

G_BEGIN_DECLS

#define CALC_TYPE_SUM calc_sum_get_type ()
G_DECLARE_FINAL_TYPE (CalcSum, calc_sum, CALC, SUM, CalcExpr)

struct _CalcSumClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcSum:
 *
 * Represents the addition of one or more terms (not necessarily instances of
 * #CalcTerm).
 **/

struct _CalcSum
{
  /*< private >*/
  CalcExpr parent;
  GPtrArray *terms;
};

CalcSum *calc_sum_new (CalcExpr *term);
void calc_sum_add_term (CalcSum *self, CalcExpr *term);

G_END_DECLS

#endif
