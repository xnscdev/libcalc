/*************************************************************************
 * eval-num.c -- This file is part of libcalc.                           *
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

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  CalcNumber *b = calc_number_new (NULL);
  assert (calc_expr_evaluate (CALC_EXPR (a), CALC_EXPR (b)));
  assert_num_type_equals (b, CALC_NUMBER_TYPE_INTEGER);
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
  return 0;
}
