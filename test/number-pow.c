/*************************************************************************
 * number-pow.c -- This file is part of libcalc.                         *
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

DEFINE_TEST (test0)
{
  CalcNumber *a = calc_number_new_ui (3);
  CalcNumber *b = calc_number_new_ui (4);
  CalcNumber *c = NULL;
  calc_number_pow (&c, a, b);
  g_object_unref (a);
  g_object_unref (b);
  if (c == NULL)
    abort ();
  assert_num_equals_ui (c, 81);
  g_object_unref (c);
}

int
main (void)
{
  RUN_TEST (test0);
  return 0;
}
