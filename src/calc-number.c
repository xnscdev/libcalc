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
calc_number_class_init (CalcNumberClass *klass)
{
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

CalcNumber *
calc_number_new_q (mpq_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpq_init (self->rational);
  mpq_set (self->rational, value);
  self->type = CALC_NUMBER_TYPE_RATIONAL;
  return self;
}

CalcNumber *
calc_number_new_z (mpz_t value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

CalcNumber *
calc_number_new_ui (unsigned long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_ui (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}

CalcNumber *
calc_number_new_si (signed long value)
{
  CalcNumber *self = g_object_new (CALC_TYPE_NUMBER, NULL);
  mpz_init_set_si (self->integer, value);
  self->type = CALC_NUMBER_TYPE_INTEGER;
  return self;
}
