/*************************************************************************
 * calc-number.c -- This file is part of libcalc.                        *
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

#include "calc-number.h"

G_DEFINE_TYPE (CalcNumber, calc_number, CALC_TYPE_EXPR)

static gboolean calc_number_equivalent (CalcExpr *self, CalcExpr *other);

static void
calc_number_dispose (GObject *obj)
{
  CalcNumber *self = CALC_NUMBER (obj);
  switch (self->type)
    {
    case CALC_NUMBER_TYPE_INTEGER:
      mpz_clear (self->integer);
      break;
    case CALC_NUMBER_TYPE_RATIONAL:
      mpq_clear (self->rational);
      break;
    case CALC_NUMBER_TYPE_FLOATING:
      mpfr_clear (self->floating);
      break;
    }
}

static void
calc_number_class_init (CalcNumberClass *klass)
{
  G_OBJECT_CLASS (klass)->dispose = calc_number_dispose;
  CALC_EXPR_CLASS (klass)->equivalent = calc_number_equivalent;
}

static void
calc_number_init (CalcNumber *self)
{
}

static gboolean
calc_number_equivalent (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_NUMBER (other), FALSE);
  return FALSE; /* TODO Implement comparisons */
}

/**
 * calc_number_new_f:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP floating-point
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_FLOATING.
 **/

CalcNumber *
calc_number_new_f (mpf_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set_f (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_fr:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MPFR
 * floating-point number @value. The number will have a type set to
 * %CALC_NUMBER_TYPE_FLOATING.
 **/

CalcNumber *
calc_number_new_fr (mpfr_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_q:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP rational
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_RATIONAL.
 **/

CalcNumber *
calc_number_new_q (mpq_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpq_init (self->rational);
  mpq_set (self->rational, value);
  self->type = CALC_NUMBER_TYPE_RATIONAL;
  return self;
}

/**
 * calc_number_new_z:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the GNU MP integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 **/

CalcNumber *
calc_number_new_z (mpz_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

/**
 * calc_number_new_d:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the 64-bit floating-point
 * number @value. The number will have a type set to %CALC_NUMBER_TYPE_FLOATING.
 **/

CalcNumber *
calc_number_new_d (double value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpfr_init_set_d (self->floating, value, MPFR_RNDN);
  self->type = CALC_NUMBER_TYPE_FLOATING;
  return self;
}

/**
 * calc_number_new_ui:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the unsigned integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 **/

CalcNumber *
calc_number_new_ui (unsigned long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_ui (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

/**
 * calc_number_new_si:
 * @value: the value to initialize to
 *
 * Constructs a new #CalcNumber and initializes it to the signed integer
 * @value. The number will have a type set to %CALC_NUMBER_TYPE_INTEGER.
 **/

CalcNumber *
calc_number_new_si (signed long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_si (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}
