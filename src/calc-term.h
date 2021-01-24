/*************************************************************************
 * calc-term.h -- This file is part of libcalc.                          *
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

#ifndef _CALC_TERM_H
#define _CALC_TERM_H

#include "calc-number.h"

G_BEGIN_DECLS

#define CALC_TYPE_TERM calc_term_get_type ()
G_DECLARE_FINAL_TYPE (CalcTerm, calc_term, CALC, TERM, CalcExpr)

struct _CalcTermClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcTerm:
 *
 * Represents the multiplication of a coefficient and zero or more factors.
 **/

struct _CalcTerm
{
  /*< private >*/
  CalcExpr parent;
  CalcNumber *coefficient;
  GPtrArray *factors;
};

CalcTerm *calc_term_new (CalcNumber *coefficient);
void calc_term_set_coefficient (CalcTerm *self, CalcNumber *coefficient);
CalcNumber *calc_term_get_coefficient (CalcTerm *self);
void calc_term_add_factor (CalcTerm *self, CalcExpr *factor);

G_END_DECLS

#endif
