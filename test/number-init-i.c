/*************************************************************************
 * number-init-i.c -- This file is part of libcalc.                      *
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
#include "calc-number.h"

#define T0 65535

int
main (void)
{
  CalcNumber *t0 = calc_number_new_ui (T0);
  if (mpz_cmp_ui (t0->integer, T0) != 0)
    {
      g_object_unref (t0);
      exit (1);
    }
  g_object_unref (t0);
  return 0;
}
