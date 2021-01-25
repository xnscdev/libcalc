/*************************************************************************
 * num-log10.c -- This file is part of libcalc.                          *
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

#define TEST_VALUE 10000
#define TEST_RESULT 4

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  CalcNumber *b = NULL;
  calc_number_log10 (&b, a);
  g_object_unref (a);
  assert (b != NULL);
  assert_num_equals_ui (b, 4);
  g_object_unref (b);
  return 0;
}
