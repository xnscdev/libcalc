/*************************************************************************
 * eval-arith.c -- This file is part of libcalc.                         *
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

#define TEST_VALUE 64
#define TEST_VARIABLE "a"

DEFINE_TEST (sa_num)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  CalcNumber *b = calc_number_new (NULL);
  if (!calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (b)))
    abort ();
  assert_type_equals (b, CALC_NUMBER_TYPE_INTEGER);
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
}

DEFINE_TEST (sa_var)
{
  CalcVariable *a = calc_variable_new (TEST_VARIABLE);
  CalcNumber *b = calc_number_new_ui (TEST_VALUE);
  CalcNumber *c = calc_number_new (NULL);
  calc_variable_set_value (TEST_VARIABLE, CALC_EXPR (b));
  if (!calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (c)))
    abort ();
  assert_num_equals_ui (c, TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  calc_variable_set_value (TEST_VARIABLE, NULL);
}

DEFINE_TEST (sa_exp)
{
  CalcNumber *base = calc_number_new_ui (TEST_VALUE);
  CalcNumber *power = calc_number_new_ui (2);
  CalcExponent *a = calc_exponent_new (CALC_EXPR (base), CALC_EXPR (power));
  CalcNumber *b = calc_number_new (NULL);
  if (!calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (b)))
    abort ();
  assert_num_equals_ui (b, TEST_VALUE * TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (base);
  g_object_unref (power);
}

DEFINE_TEST (sa_frac)
{
  CalcNumber *num = calc_number_new_ui (TEST_VALUE);
  CalcNumber *denom = calc_number_new_ui (2);
  CalcFraction *a = calc_fraction_new (CALC_EXPR (num), CALC_EXPR (denom));
  CalcNumber *b = calc_number_new (NULL);
  if (!calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (b)))
    abort ();
  assert_num_equals_ui (b, TEST_VALUE / 2);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (num);
  g_object_unref (denom);
}

DEFINE_TEST (sa_sum)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  CalcSum *b = calc_sum_new (CALC_EXPR (a));
  CalcVariable *c = calc_variable_new ("x");
  CalcNumber *d = calc_number_new (NULL);
  calc_variable_set_value ("x", CALC_EXPR (a));
  calc_sum_add_term (b, CALC_EXPR (c));
  if (!calc_expr_evaluate (CALC_EXPR (b), CALC_EXPR (d)))
    abort ();
  assert_num_equals_ui (d, TEST_VALUE * 2);
  calc_variable_set_value ("x", NULL);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
}

int
main (void)
{
  RUN_TEST (sa_num);
  RUN_TEST (sa_var);
  RUN_TEST (sa_exp);
  RUN_TEST (sa_frac);
  RUN_TEST (sa_sum);
  return 0;
}
