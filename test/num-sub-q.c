/*************************************************************************
 * num-sub-q.c -- This file is part of libcalc.                          *
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

#define TEST_VALUE_A 1452863953L
#define TEST_VALUE_B 134217728L

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE_A);
  mpq_t b;
  CalcNumber *c = NULL;
  mpq_init (b);
  mpq_set_ui (b, TEST_VALUE_B, 1);
  calc_number_sub_q (&c, a, b);
  g_object_unref (a);
  mpq_clear (b);
  assert (c != NULL);
  assert_num_equals_ui (c, TEST_VALUE_A - TEST_VALUE_B);
  g_object_unref (c);
  return 0;
}
