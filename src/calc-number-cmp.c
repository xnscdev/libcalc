/*************************************************************************
 * calc-number-cmp.c -- This file is part of libcalc.                    *
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

#define _LIBCALC_INTERNAL

#include "calc-number.h"

/**
 * calc_number_cmp:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a and @b are invalid numbers
 **/

gint
calc_number_cmp (CalcNumber *a, CalcNumber *b)
{
  CalcNumberType type;
  CalcNumber *ca;
  CalcNumber *cb;
  gint result;

  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  g_return_val_if_fail (CALC_IS_NUMBER (b), 0);

  type = _calc_number_get_final_type (a->type, b->type);
  ca = calc_number_new (a);
  cb = calc_number_new (b);
  calc_number_cast (ca, type);
  calc_number_cast (cb, type);

  switch (type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      result = mpz_cmp (ca->integer, cb->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      result = mpq_cmp (ca->rational, cb->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      result = mpfr_cmp (ca->floating, cb->floating);
      break;
    default:
      return 0;
    }

  g_object_unref (ca);
  g_object_unref (cb);
  return result;
}

/**
 * calc_number_cmp_z:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_z (CalcNumber *a, mpz_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_z (a->rational, b);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_z (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_q:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_q (CalcNumber *a, mpq_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpq_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp (a->rational, b);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_q (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_f:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_f (CalcNumber *a, mpf_t b)
{
  mpq_t temp;
  gint result;
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpf_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init (temp);
      mpq_set_f (temp, b);
      result = mpq_cmp (a->rational, temp);
      mpq_clear (temp);
      return result;
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_f (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_fr:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_fr (CalcNumber *a, mpfr_t b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return -mpfr_cmp_z (b, a->integer);
    case CALC_NUMBER_TYPE_RATIONAL:
      return -mpfr_cmp_q (b, a->rational);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_d:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_d (CalcNumber *a, double b)
{
  mpfr_t temp;
  gint result;
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_d (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init (temp);
      mpfr_set_q (temp, a->rational, MPFR_RNDN);
      result = mpfr_cmp_d (temp, b);
      mpfr_clear (temp);
      return result;
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_d (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_ui:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_ui (CalcNumber *a, unsigned long b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_ui (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_ui (a->rational, b, 1);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_ui (a->floating, b);
    default:
      return 0;
    }
}

/**
 * calc_number_cmp_si:
 * @a: the first number to compare
 * @b: the second number to compare
 *
 * Compares the values of @a and @b.
 *
 * Returns: a positive value if @a > @b, negative if @a < @b, and zero if
 * @a = @b or @a is an invalid number
 **/

gint
calc_number_cmp_si (CalcNumber *a, signed long b)
{
  g_return_val_if_fail (CALC_IS_NUMBER (a), 0);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      return mpz_cmp_si (a->integer, b);
    case CALC_NUMBER_TYPE_RATIONAL:
      return mpq_cmp_si (a->rational, b, 1);
    case CALC_NUMBER_TYPE_FLOATING:
      return mpfr_cmp_si (a->floating, b);
    default:
      return 0;
    }
}
