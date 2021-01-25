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
  CalcExponent *d;
  CalcVariable *e;
  calc_term_add_factor (c, CALC_EXPR (b));
  assert (c->factors->len == 1);
  assert (CALC_IS_EXPONENT (c->factors->pdata[0]));
  d = CALC_EXPONENT (c->factors->pdata[0]);
  assert (CALC_IS_VARIABLE (calc_exponent_get_base (d)));
  e = CALC_VARIABLE (calc_exponent_get_base (d));
  assert (strcmp (calc_variable_get_name (e), "x") == 0);
  assert (CALC_IS_NUMBER (calc_exponent_get_power (d)));
  assert_num_equals_ui (CALC_NUMBER (calc_exponent_get_power (d)), 1);
  assert_num_equals_ui (calc_term_get_coefficient (c), TEST_VALUE_A);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
}

DEFINE_TEST (exp_match)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE_A);
  CalcNumber *b = calc_number_new_ui (TEST_VALUE_B);
  CalcVariable *c = calc_variable_new ("x");
  CalcExponent *d = calc_exponent_new (CALC_EXPR (c), CALC_EXPR (a));
  CalcExponent *e = calc_exponent_new (CALC_EXPR (c), CALC_EXPR (b));
  CalcTerm *f = calc_term_new (a);
  CalcExponent *g;
  CalcTerm *h;
  calc_term_add_factor (f, CALC_EXPR (d));
  calc_term_add_factor (f, CALC_EXPR (e));
  assert (f->factors->len == 1);
  assert (CALC_IS_EXPONENT (f->factors->pdata[0]));
  g = CALC_EXPONENT (f->factors->pdata[0]);
  assert (calc_expr_equivalent (g->base, CALC_EXPR (c)));
  assert (CALC_IS_SUM (g->power));
  assert (CALC_SUM (g->power)->terms->len == 1);
  assert (CALC_IS_TERM (CALC_SUM (g->power)->terms->pdata[0]));
  h = CALC_TERM (CALC_SUM (g->power)->terms->pdata[0]);
  assert (h->factors->len == 0);
  assert_num_equals_ui (h->coefficient, TEST_VALUE_A + TEST_VALUE_B);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  g_object_unref (d);
  g_object_unref (e);
  g_object_unref (f);
}

int
main (void)
{
  RUN_TEST (num);
  RUN_TEST (var);
  RUN_TEST (exp_match);
  return 0;
}
