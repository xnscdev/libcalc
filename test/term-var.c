/*************************************************************************
 * term-var.c -- This file is part of libcalc.                           *
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

#include "libtest.h"

#define TEST_VALUE_A 4
#define TEST_VALUE_B 2
#define TEST_VARIABLE "x"

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE_A);
  CalcVariable *b = calc_variable_new (TEST_VARIABLE);
  CalcTerm *c = calc_term_new (a);
  CalcExponent *d;
  CalcVariable *e;
  calc_term_add_factor (c, CALC_EXPR (b));
  assert (c->factors->len == 1);
  assert (CALC_IS_EXPONENT (c->factors->pdata[0]));
  d = CALC_EXPONENT (c->factors->pdata[0]);
  assert (CALC_IS_VARIABLE (calc_exponent_get_base (d)));
  e = CALC_VARIABLE (calc_exponent_get_base (d));
  assert (strcmp (calc_variable_get_name (e), TEST_VARIABLE) == 0);
  assert (CALC_IS_NUMBER (calc_exponent_get_power (d)));
  assert_num_equals_ui (CALC_NUMBER (calc_exponent_get_power (d)), 1);
  assert_num_equals_ui (calc_term_get_coefficient (c), TEST_VALUE_A);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  return 0;
}
