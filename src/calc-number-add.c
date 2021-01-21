/*************************************************************************
 * calc-number-add.c -- This file is part of libcalc.                    *
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
 * calc_number_add:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a or @b are invalid
 * numbers, no action is performed.
 **/

void
calc_number_add (CalcNumber **result, CalcNumber *a, CalcNumber *b)
{
  CalcNumberType type;
  CalcNumber *ca;
  CalcNumber *cb;

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
  switch (type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_init ((*result)->integer);
      mpz_add ((*result)->integer, ca->integer, cb->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_add ((*result)->rational, ca->rational, cb->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add ((*result)->floating, ca->floating, cb->floating, MPFR_RNDN);
      break;
    }
  (*result)->type = type;

  g_object_unref (ca);
  g_object_unref (cb);
}

/**
 * calc_number_add_z:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_z (CalcNumber **result, CalcNumber *a, mpz_t b)
{
  mpq_t temp;
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
      mpz_init ((*result)->integer);
      mpz_add ((*result)->integer, a->integer, b);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_init (temp);
      mpq_set_z (temp, b);
      mpq_add ((*result)->rational, a->rational, temp);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_z ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_q:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_q (CalcNumber **result, CalcNumber *a, mpq_t b)
{
  mpq_t temp;
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
      mpq_init (temp);
      mpq_set_z (temp, a->integer);
      mpq_add ((*result)->rational, temp, b);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_add ((*result)->rational, a->rational, b);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_q ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_f:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_f (CalcNumber **result, CalcNumber *a, mpf_t b)
{
  mpfr_t temp;
  mpfr_init_set_f (temp, b, MPFR_RNDN);
  calc_number_add_fr (result, a, temp);
  mpfr_clear (temp);
}

/**
 * calc_number_add_fr:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_fr (CalcNumber **result, CalcNumber *a, mpfr_t b)
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
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z ((*result)->floating, a->integer, MPFR_RNDN);
      mpfr_add ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q ((*result)->floating, a->rational, MPFR_RNDN);
      mpfr_add ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_d:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_d (CalcNumber **result, CalcNumber *a, double b)
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
  switch (a->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpfr_init_set_z ((*result)->floating, a->integer, MPFR_RNDN);
      mpfr_add_d ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpfr_init_set_q ((*result)->floating, a->rational, MPFR_RNDN);
      mpfr_add_d ((*result)->floating, (*result)->floating, b, MPFR_RNDN);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_d ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_ui:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_ui (CalcNumber **result, CalcNumber *a, unsigned long b)
{
  mpq_t temp;
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
      mpz_init ((*result)->integer);
      mpz_add_ui ((*result)->integer, a->integer, b);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_init (temp);
      mpq_set_ui (temp, b, 1);
      mpq_add ((*result)->rational, a->rational, temp);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_ui ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}

/**
 * calc_number_add_si:
 * @result: the pointer to store the result of the addition
 * @a: the first addend
 * @b: the second addend
 *
 * Adds @a and @b and stores the result in @result. Any previous value in
 * @result will be erased. The type of @result is dependent on the types of
 * @a and @b. If @result points to %NULL, a new #CalcNumber is allocated and
 * @result will point to it. If @result is %NULL or @a is invalid, no action
 * is performed.
 **/

void
calc_number_add_si (CalcNumber **result, CalcNumber *a, signed long b)
{
  mpq_t temp;
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
      mpz_init ((*result)->integer);
      if (b >= 0)
	mpz_add_ui ((*result)->integer, a->integer, b);
      else
	mpz_sub_ui ((*result)->integer, a->integer, -b);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_init ((*result)->rational);
      mpq_init (temp);
      mpq_set_si (temp, b, 1);
      mpq_add ((*result)->rational, a->rational, temp);
      mpq_clear (temp);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_init ((*result)->floating);
      mpfr_add_si ((*result)->floating, a->floating, b, MPFR_RNDN);
      break;
    }
}
