/*************************************************************************
 * calc-number-trans.c -- This file is part of libcalc.                  *
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
 * calc_number_log:
 * @result: the pointer to store the result
 * @self: the number
 *
 * Sets the value of @result to the natural logarithm of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to it.
 * If @result is %NULL or @self is an invalid number, no action is performed
 * and this function returns -1.
 *
 * Returns: zero if the calculation is exact, positive if the calculation is
 * slightly larger than the actual value, and negative if the calculation is
 * slightly smaller than the actual value or invalid arguments were given
 **/

gint
calc_number_log (CalcNumber **result, CalcNumber *self)
{
  gint ret;
  mpfr_t temp;
  g_return_val_if_fail (result != NULL, -1);
  g_return_val_if_fail (*result == NULL || CALC_IS_NUMBER (*result), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (self), -1);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  mpfr_init ((*result)->floating);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z (temp, self->integer, MPFR_RNDN);
      ret = mpfr_log ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q (temp, self->rational, MPFR_RNDN);
      ret = mpfr_log ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      ret = mpfr_log ((*result)->floating, self->floating, MPFR_RNDN);
      break;
    default:
      return -1;
    }
  return ret;
}

/**
 * calc_number_log2:
 * @result: the pointer to store the result
 * @self: the number
 *
 * Sets the value of @result to the binary logarithm of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to it.
 * If @result is %NULL or @self is an invalid number, no action is performed
 * and this function returns -1.
 *
 * Returns: zero if the calculation is exact, positive if the calculation is
 * slightly larger than the actual value, and negative if the calculation is
 * slightly smaller than the actual value or invalid arguments were given
 **/

gint
calc_number_log2 (CalcNumber **result, CalcNumber *self)
{
  gint ret;
  mpfr_t temp;
  g_return_val_if_fail (result != NULL, -1);
  g_return_val_if_fail (*result == NULL || CALC_IS_NUMBER (*result), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (self), -1);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  mpfr_init ((*result)->floating);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z (temp, self->integer, MPFR_RNDN);
      ret = mpfr_log2 ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q (temp, self->rational, MPFR_RNDN);
      ret = mpfr_log2 ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      ret = mpfr_log2 ((*result)->floating, self->floating, MPFR_RNDN);
      break;
    default:
      return -1;
    }
  return ret;
}

/**
 * calc_number_log10:
 * @result: the pointer to store the result
 * @self: the number
 *
 * Sets the value of @result to the decimal logarithm of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to it.
 * If @result is %NULL or @self is an invalid number, no action is performed
 * and this function returns -1.
 *
 * Returns: zero if the calculation is exact, positive if the calculation is
 * slightly larger than the actual value, and negative if the calculation is
 * slightly smaller than the actual value or invalid arguments were given
 **/

gint
calc_number_log10 (CalcNumber **result, CalcNumber *self)
{
  gint ret;
  mpfr_t temp;
  g_return_val_if_fail (result != NULL, -1);
  g_return_val_if_fail (*result == NULL || CALC_IS_NUMBER (*result), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (self), -1);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  mpfr_init ((*result)->floating);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z (temp, self->integer, MPFR_RNDN);
      ret = mpfr_log10 ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q (temp, self->rational, MPFR_RNDN);
      ret = mpfr_log10 ((*result)->floating, temp, MPFR_RNDN);
      mpfr_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      ret = mpfr_log10 ((*result)->floating, self->floating, MPFR_RNDN);
      break;
    default:
      return -1;
    }
  return ret;
}

/**
 * calc_number_logn:
 * @result: the pointer to store the result
 * @self: the number
 * @base: the base of the logarithm
 *
 * Sets the value of @result to the base-@base logarithm of @self. If @result
 * points to %NULL, a new #CalcNumber is allocated and @result will point to it.
 * If @result is %NULL, @base is zero or one, or @self is an invalid number,
 * no action is performed and this function returns -1.
 *
 * Returns: zero if the calculation succeeded
 **/

gint
calc_number_logn (CalcNumber **result, CalcNumber *self, unsigned long base)
{
  CalcNumber *a = NULL;
  CalcNumber *b = NULL;
  CalcNumber *fbase;
  g_return_val_if_fail (result != NULL, -1);
  g_return_val_if_fail (*result == NULL || CALC_IS_NUMBER (*result), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (self), -1);
  g_return_val_if_fail (base > 1, -1);

  fbase = calc_number_new_ui (base);
  calc_number_log2 (&a, self);
  calc_number_log2 (&b, fbase);
  g_object_unref (fbase);
  if (a == NULL || b == NULL)
    {
      g_object_unref (a);
      g_object_unref (b);
      return -1;
    }

  calc_number_div (result, a, b);
  g_object_unref (a);
  g_object_unref (b);
  return 0;
}

/**
 * calc_number_pow:
 * @result: the pointer to store the result of the exponentiation
 * @a: the base number
 * @b: the power to raise the base to
 *
 * Sets the value of @result to @a raised the @b power. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a or @b are invalid
 * numbers, no action is performed and the function returns -1.
 *
 * Returns: zero if the calculation is exact, positive if the calculation is
 * slightly larger than the actual value, and negative if the calculation is
 * slightly smaller than the actual value or invalid arguments were given
 **/

gint
calc_number_pow (CalcNumber **result, CalcNumber *a, CalcNumber *b)
{
  gint ret;
  CalcNumber *ca;
  CalcNumber *cb;

  g_return_val_if_fail (result != NULL, -1);
  g_return_val_if_fail (*result == NULL || CALC_IS_NUMBER (*result), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (a), -1);
  g_return_val_if_fail (CALC_IS_NUMBER (b), -1);

  ca = calc_number_new (a);
  cb = calc_number_new (b);
  calc_number_cast (ca, CALC_NUMBER_TYPE_FLOATING);
  calc_number_cast (cb, CALC_NUMBER_TYPE_FLOATING);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  ret = mpfr_pow ((*result)->floating, ca->floating, cb->floating, MPFR_RNDN);
  g_object_unref (ca);
  g_object_unref (cb);
  return ret;
}
