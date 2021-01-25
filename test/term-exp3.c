/*************************************************************************
 * term-exp3.c -- This file is part of libcalc.                          *
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
  CalcNumber *b = calc_number_new_ui (TEST_VALUE_B);
  CalcVariable *c = calc_variable_new (TEST_VARIABLE);
  CalcExponent *d = calc_exponent_new (CALC_EXPR (c), CALC_EXPR (a));
  CalcTerm *e = calc_term_new (b);
  CalcExponent *f;
  CalcTerm *g;
  calc_term_add_factor (e, CALC_EXPR (d));
  calc_term_add_factor (e, CALC_EXPR (c));
  assert (e->factors->len == 1);
  f = CALC_EXPONENT (e->factors->pdata[0]);
  assert (calc_expr_equivalent (f->base, CALC_EXPR (c)));
  assert (CALC_IS_SUM (f->power));
  assert (CALC_SUM (f->power)->terms->len == 1);
  assert (CALC_IS_TERM (CALC_SUM (f->power)->terms->pdata[0]));
  g = CALC_TERM (CALC_SUM (f->power)->terms->pdata[0]);
  assert (g->factors->len == 0);
  assert_num_equals_ui (g->coefficient, TEST_VALUE_A + 1);
  g_object_unref (a);
  g_object_unref (b);
  g_object_unref (c);
  g_object_unref (d);
  g_object_unref (e);
  return 0;
}
