/*************************************************************************
 * term-init.c -- This file is part of libcalc.                          *
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

#define TEST_VALUE 4

DEFINE_TEST (nofactors)
{
  CalcTerm *a = calc_term_new (calc_number_new_ui (TEST_VALUE));
  CalcNumber *b = calc_number_new (NULL);
  if (!calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (b)))
    abort ();
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (calc_term_get_coefficient (a));
  g_object_unref (a);
  g_object_unref (b);
}

DEFINE_TEST (var)
{
  CalcVariable *a = calc_variable_new ("x");
  CalcNumber *b = calc_number_new_ui (TEST_VALUE);
  CalcTerm *c = calc_term_new (b);
  CalcNumber *d = calc_number_new (NULL);
  calc_variable_set_value ("x", CALC_EXPR (b));
  calc_term_add_factor (c, CALC_EXPR (a));
  if (!calc_expr_evaluate (CALC_EXPR (c), CALC_EXPR (d)))
    abort ();
  assert_num_equals_ui (d, TEST_VALUE * TEST_VALUE);
  calc_variable_set_value ("x", NULL);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  g_object_unref (d);
}

int
main (void)
{
  RUN_TEST (nofactors);
  RUN_TEST (var);
  return 0;
}