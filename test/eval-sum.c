/*************************************************************************
 * eval-sum.c -- This file is part of libcalc.                           *
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

#define TEST_VALUE 64
#define TEST_VARIABLE "x"

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  CalcSum *b = calc_sum_new (CALC_EXPR (a));
  CalcVariable *c = calc_variable_new (TEST_VARIABLE);
  CalcNumber *d = calc_number_new (NULL);
  calc_variable_set_value (TEST_VARIABLE, CALC_EXPR (a));
  calc_sum_add_term (b, CALC_EXPR (c));
  if (!calc_expr_evaluate (CALC_EXPR (b), CALC_EXPR (d)))
    abort ();
  assert_num_equals_ui (d, TEST_VALUE * 2);
  calc_variable_set_value (TEST_VARIABLE, NULL);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  return 0;
}
