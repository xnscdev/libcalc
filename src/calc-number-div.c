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
	  mpq_inits ((*result)->rational, qa, qb, NULL);
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
  mpz_t temp;
  mpq_t rb;
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = a->type;
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init (temp);
      mpz_mod (temp, a->integer, b);
      if (mpz_cmp_ui (temp, 0) == 0)
	{
	  mpz_init ((*result)->integer);
	  mpz_tdiv_q ((*result)->integer, a->integer, b);
	}
      else
	{
	  mpq_t qa;
	  mpq_t qb;
	  (*result)->type = CALC_NUMBER_TYPE_RATIONAL;
	  mpq_inits ((*result)->rational, qa, qb, NULL);
	  mpq_set_z (qa, a->integer);
	  mpq_set_z (qb, b);
	  mpq_div ((*result)->rational, qa, qb);
	  mpq_clears (qa, qb, NULL);
	}
      mpz_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_init (rb);
      mpq_set_z (rb, b);
      mpq_div ((*result)->rational, a->rational, rb);
      mpq_clear (rb);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_div_z ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_div_q:
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
calc_number_div_q (CalcNumber **result, CalcNumber *a, mpq_t b)
{
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = a->type;
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      (*result)->type = CALC_NUMBER_TYPE_RATIONAL;
      mpq_init ((*result)->rational);
      mpq_set_z ((*result)->rational, a->integer);
      mpq_div ((*result)->rational, (*result)->rational, b);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_div ((*result)->rational, a->rational, b);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_div_q ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_div_f:
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
calc_number_div_f (CalcNumber **result, CalcNumber *a, mpf_t b)
{
  mpfr_t temp;
  mpfr_init_set_f (temp, b, MPFR_RNDN);
  calc_number_div_fr (result, a, temp);
  mpfr_clear (temp);
}

/**
 * calc_number_div_fr:
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
calc_number_div_fr (CalcNumber **result, CalcNumber *a, mpfr_t b)
{
  g_return_if_fail (result != NULL);
  g_return_if_fail (*result == NULL || CALC_IS_NUMBER (*result));
  g_return_if_fail (CALC_IS_NUMBER (a));

  if (*result == NULL)
    {
      *result = calc_number_new (NULL);
      mpz_clear ((*result)->integer);
    }
  else
    _calc_number_release (*result);
  (*result)->type = CALC_NUMBER_TYPE_FLOATING;
  mpfr_init ((*result)->floating);
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_set_z ((*result)->floating, a->integer, MPFR_RNDN);
      mpfr_div ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_set_q ((*result)->floating, a->rational, MPFR_RNDN);
      mpfr_div ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_div ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}
