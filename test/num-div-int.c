/*************************************************************************
 * num-div-int.c -- This file is part of libcalc.                        *
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

#define TEST_DIVIDEND 6
#define TEST_DIVISOR 2
#define TEST_QUOTIENT 3

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_DIVIDEND);
  CalcNumber *b = calc_number_new_ui (TEST_DIVISOR);
  CalcNumber *c = NULL;
  calc_number_div (&c, a, b);
  g_object_unref (a);
  g_object_unref (b);
  assert (c != NULL);
  assert_num_type_equals (c, CALC_NUMBER_TYPE_INTEGER);
  assert_num_equals_ui (c, TEST_QUOTIENT);
  g_object_unref (c);
  return 0;
}
