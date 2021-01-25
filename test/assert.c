/*************************************************************************
 * assert.c -- This file is part of libcalc.                             *
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

#include <stdlib.h>
#include "libtest.h"

void
assert_num_equals_d (CalcNumber *num, double value)
{
  if (calc_number_cmp_d (num, value) != 0)
    {
      calc_expr_print (CALC_EXPR (num), stderr);
      fprintf (stderr, " != %.2f\n", value);
      abort ();
    }
}

void
assert_num_equals_ui (CalcNumber *num, unsigned long value)
{
  if (calc_number_cmp_ui (num, value) != 0)
    {
      calc_expr_print (CALC_EXPR (num), stderr);
      fprintf (stderr, " != %lu\n", value);
      abort ();
    }
}

void
assert_num_equals_si (CalcNumber *num, signed long value)
{
  if (calc_number_cmp_si (num, value) != 0)
    {
      calc_expr_print (CALC_EXPR (num), stderr);
      fprintf (stderr, " != %ld\n", value);
      abort ();
    }
}

void
assert_num_type_equals (CalcNumber *num, CalcNumberType type)
{
  if (num->type != type)
    {
      fprintf (stderr, "expected type %d but got %d\n", type, num->type);
      abort ();
    }
}
