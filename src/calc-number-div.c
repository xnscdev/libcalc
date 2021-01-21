/*************************************************************************
 * calc-number-div.c -- This file is part of libcalc.                    *
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
 * calc_number_div:
 * @result: the pointer to store the result of the division
 * @a: the dividend
 * @b: the divisor
 *
 * Divides @a by @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a or @b are invalid
 * numbers, no action is performed.
 **/

void
calc_number_div (CalcNumber **result, CalcNumber *a, CalcNumber *b)
{
  CalcNumberType type;
  CalcNumber *ca;
  CalcNumber *cb;
  mpz_t temp;

  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));
  g_return_if_fail (CALC_IS_NUMBER (b));

  type = _calc_number_get_final_type (a->type, b->type);
  ca = calc_number_new (a);
  cb = calc_number_new (b);
  calc_number_cast (ca, type);
  calc_number_cast (cb, type);

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = type;
  switch (type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init (temp);
      mpz_mod (temp, ca->integer, cb->integer);
      if (mpz_cmp_ui (temp, 0) == 0)
	{
	  mpz_init ((*result)->integer);
	  mpz_tdiv_q ((*result)->integer, ca->integer, cb->integer);
	}
      else
	{
	  mpq_t qa;
	  mpq_t qb;
	  (*result)->type = CALC_NUMBER_TYPE_RATIONAL;
	  mpq_inits (qa, qb, NULL);
	  mpq_set_z (qa, ca->integer);
	  mpq_set_z (qb, cb->integer);
	  mpq_div ((*result)->rational, qa, qb);
	  mpq_clears (qa, qb, NULL);
	}
      mpz_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_div ((*result)->rational, ca->rational, cb->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_div ((*result)->floating, ca->floating, cb->floating, MPFR_RNDN);
      break;
    }

  g_object_unref (ca);
  g_object_unref (cb);
}

/**
 * calc_number_div_z:
 * @result: the pointer to store the result of the division
 * @a: the dividend
 * @b: the divisor
 *
 * Divides @a by @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is an invalid number,
 * no action is performed.
 **/

void
calc_number_div_z (CalcNumber **result, CalcNumber *a, mpz_t b)
{
}
