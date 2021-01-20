/*************************************************************************
 * number-cast.c -- This file is part of libcalc.                        *
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

#include <stdio.h>
#include <stdlib.h>
#include "libcalc.h"

#define TEST_TYPE CALC_NUMBER_TYPE_FLOATING
#define TEST_VALUE 256

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  calc_number_cast (NULL, TEST_TYPE);
  calc_number_cast (a, TEST_TYPE);
  if (a->type != TEST_TYPE)
    {
      fprintf (stderr, "bad type after cast\n");
      exit (1);
    }
  if (mpfr_cmp_d (a->floating, TEST_VALUE) != 0)
    {
      mpfr_out_str (stderr, 10, 4, a->floating, MPFR_RNDD);
      fprintf (stderr, " != %d\n", TEST_VALUE);
      exit (2);
    }
  return 0;
}
