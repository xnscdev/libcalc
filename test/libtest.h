/*************************************************************************
 * libtest.h -- This file is part of libcalc.                            *
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

#ifndef _LIBTEST_H
#define _LIBTEST_H

#include <libcalc.h>

#define DEFINE_TEST(name) void name (void)
#define RUN_TEST(name) name ()

void assert_num_equals_d (CalcNumber *num, double value);
void assert_num_equals_ui (CalcNumber *num, unsigned long value);
void assert_type_equals (CalcNumber *num, CalcNumberType type);

#endif
