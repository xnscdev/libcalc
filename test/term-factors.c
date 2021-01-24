/*************************************************************************
 * term-factors.c -- This file is part of libcalc.                       *
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

#include <assert.h>
#include <stdlib.h>
#include "libtest.h"

#define TEST_VALUE_A 4
#define TEST_VALUE_B 2

DEFINE_TEST (num)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE_A);
  CalcNumber *b = calc_number_new_ui (TEST_VALUE_B);
  CalcTerm *c = calc_term_new (a);
  calc_term_add_factor (c, CALC_EXPR (b));
  assert (c->factors->len == 0);
  assert_num_equals_ui (calc_term_get_coefficient (c),
			TEST_VALUE_A * TEST_VALUE_B);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
}

DEFINE_TEST (var)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE_A);
  CalcVariable *b = calc_variable_new ("x");
  CalcTerm *c = calc_term_new (a);
  calc_term_add_factor (c, CALC_EXPR (b));
  assert (c->factors->len == 1);
  assert (CALC_IS_VARIABLE (c->factors->pdata[0]));
  assert (strcmp (calc_variable_get_name (CALC_VARIABLE (c->factors->pdata[0])),
		  "x") == 0);
  assert_num_equals_ui (calc_term_get_coefficient (c), TEST_VALUE_A);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
}

int
main (void)
{
  RUN_TEST (num);
  RUN_TEST (var);
  return 0;
}
