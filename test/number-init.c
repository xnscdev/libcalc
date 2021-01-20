/*************************************************************************
 * number-init.c -- This file is part of libcalc.                        *
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

#define TEST_VALUE 65535

DEFINE_TEST (ui)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  if (mpz_cmp_ui (a->integer, TEST_VALUE) != 0)
    {
      mpz_out_str (stderr, 10, a->integer);
      fprintf (stderr, " != %d\n", TEST_VALUE);
      exit (1);
    }
}

int
main (void)
{
  RUN_TEST (ui);
  return 0;
}
