/*************************************************************************
 * number-sign.c -- This file is part of libcalc.                        *
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

DEFINE_TEST (z_abs)
{
  CalcNumber *a = calc_number_new_si (-TEST_VALUE);
  CalcNumber *b = NULL;
  calc_number_abs (&b, a);
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (a);
  a = calc_number_new_ui (TEST_VALUE);
  calc_number_abs (&b, a);
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
}

DEFINE_TEST (f_abs)
{
  CalcNumber *a = calc_number_new_d (-TEST_VALUE);
  CalcNumber *b = NULL;
  calc_number_abs (&b, a);
  assert_num_equals_d (b, TEST_VALUE);
  g_object_unref (a);
  a = calc_number_new_d (TEST_VALUE);
  calc_number_abs (&b, a);
  assert_num_equals_d (b, TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
}

DEFINE_TEST (z_neg)
{
  CalcNumber *a = calc_number_new_si (-TEST_VALUE);
  CalcNumber *b = NULL;
  calc_number_neg (&b, a);
  assert_num_equals_ui (b, TEST_VALUE);
  g_object_unref (a);
  a = calc_number_new_ui (TEST_VALUE);
  calc_number_neg (&b, a);
  assert_num_equals_si (b, -TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
}

DEFINE_TEST (f_neg)
{
  CalcNumber *a = calc_number_new_d (-TEST_VALUE);
  CalcNumber *b = NULL;
  calc_number_neg (&b, a);
  assert_num_equals_d (b, TEST_VALUE);
  g_object_unref (a);
  a = calc_number_new_d (TEST_VALUE);
  calc_number_neg (&b, a);
  assert_num_equals_d (b, -TEST_VALUE);
  g_object_unref (a);
  g_object_unref (b);
}

int
main (void)
{
  RUN_TEST (z_abs);
  RUN_TEST (f_abs);
  RUN_TEST (z_neg);
  RUN_TEST (f_neg);
  return 0;
}
