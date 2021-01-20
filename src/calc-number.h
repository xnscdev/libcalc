/*************************************************************************
 * calc-number.h -- This file is part of libcalc.                        *
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

#ifndef _CALC_NUMBER_H
#define _CALC_NUMBER_H

#include <mpfr.h>
#include "calc-expr.h"

G_BEGIN_DECLS

/**
 * CalcNumberType:
 * @CALC_NUMBER_TYPE_INTEGER: an integer
 * @CALC_NUMBER_TYPE_RATIONAL: a rational number
 * @CALC_NUMBER_TYPE_FLOATING: an arbitrary floating-point real number
 *
 * Contains the types of values used for a #CalcNumber instance.
 **/

typedef enum
{
  CALC_NUMBER_TYPE_INTEGER = 1,
  CALC_NUMBER_TYPE_RATIONAL,
  CALC_NUMBER_TYPE_FLOATING
} CalcNumberType;

#define CALC_TYPE_NUMBER calc_number_get_type ()
G_DECLARE_FINAL_TYPE (CalcNumber, calc_number, CALC, NUMBER, CalcExpr)

struct _CalcNumberClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcNumber:
 * @value: the internal value of the number
 *
 * Represents a real rational number.
 **/

struct _CalcNumber
{
  /*< private >*/
  CalcExpr parent;
  mpz_t integer;
  mpq_t rational;
  mpfr_t floating;
  CalcNumberType type;
};

CalcNumber *calc_number_new_q (mpq_t value);
CalcNumber *calc_number_new_z (mpz_t value);
CalcNumber *calc_number_new_ui (unsigned long value);
CalcNumber *calc_number_new_si (signed long value);

G_END_DECLS

#endif
