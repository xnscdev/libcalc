/*************************************************************************
 * calc-number.h -- This file is part of libcalc.                        *
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

#ifndef _CALC_NUMBER_H
#define _CALC_NUMBER_H

#include <mpfr.h>
#include "calc-expr.h"

G_BEGIN_DECLS

/**
 * CalcNumberType:
 * @CALC_NUMBER_TYPE_INTEGER: an integer
 * @CALC_NUMBER_TYPE_RATIONAL: a rational number
 * @CALC_NUMBER_TYPE_FLOATING: an arbitrary floating-point real number
 *
 * Contains the types of values used for a #CalcNumber instance.
 **/

typedef enum
{
  /*< public >*/
  CALC_NUMBER_TYPE_INTEGER = 1,
  CALC_NUMBER_TYPE_RATIONAL,
  CALC_NUMBER_TYPE_FLOATING,

  /*< private >*/
  N_CALC_NUMBER_TYPE
} CalcNumberType;

#define CALC_TYPE_NUMBER calc_number_get_type ()
G_DECLARE_FINAL_TYPE (CalcNumber, calc_number, CALC, NUMBER, CalcExpr)

struct _CalcNumberClass
{
  /*< private >*/
  CalcExprClass parent;
};

/**
 * CalcNumber:
 *
 * Represents a real rational number.
 **/

struct _CalcNumber
{
  /*< private >*/
  CalcExpr parent;
  mpz_t integer;
  mpq_t rational;
  mpfr_t floating;
  CalcNumberType type;
};

CalcNumber *calc_number_new (CalcNumber *value);
CalcNumber *calc_number_new_z (mpz_t value);
CalcNumber *calc_number_new_q (mpq_t value);
CalcNumber *calc_number_new_f (mpf_t value);
CalcNumber *calc_number_new_fr (mpfr_t value);
CalcNumber *calc_number_new_d (double value);
CalcNumber *calc_number_new_ui (unsigned long value);
CalcNumber *calc_number_new_si (signed long value);

void calc_number_add (CalcNumber **result, CalcNumber *a, CalcNumber *b);
void calc_number_add_z (CalcNumber **result, CalcNumber *a, mpz_t b);
void calc_number_add_q (CalcNumber **result, CalcNumber *a, mpq_t b);
void calc_number_add_f (CalcNumber **result, CalcNumber *a, mpf_t b);
void calc_number_add_fr (CalcNumber **result, CalcNumber *a, mpfr_t b);
void calc_number_add_d (CalcNumber **result, CalcNumber *a, double b);
void calc_number_add_ui (CalcNumber **result, CalcNumber *a, unsigned long b);
void calc_number_add_si (CalcNumber **result, CalcNumber *a, signed long b);

void calc_number_div (CalcNumber **result, CalcNumber *a, CalcNumber *b);
void calc_number_div_z (CalcNumber **result, CalcNumber *a, mpz_t b);
void calc_number_div_q (CalcNumber **result, CalcNumber *a, mpq_t b);
void calc_number_div_f (CalcNumber **result, CalcNumber *a, mpf_t b);
void calc_number_div_fr (CalcNumber **result, CalcNumber *a, mpfr_t b);
void calc_number_div_d (CalcNumber **result, CalcNumber *a, double b);
void calc_number_div_ui (CalcNumber **result, CalcNumber *a, unsigned long b);
void calc_number_div_si (CalcNumber **result, CalcNumber *a, signed long b);

void calc_number_mul (CalcNumber **result, CalcNumber *a, CalcNumber *b);
void calc_number_mul_z (CalcNumber **result, CalcNumber *a, mpz_t b);
void calc_number_mul_q (CalcNumber **result, CalcNumber *a, mpq_t b);
void calc_number_mul_f (CalcNumber **result, CalcNumber *a, mpf_t b);
void calc_number_mul_fr (CalcNumber **result, CalcNumber *a, mpfr_t b);
void calc_number_mul_d (CalcNumber **result, CalcNumber *a, double b);
void calc_number_mul_ui (CalcNumber **result, CalcNumber *a, unsigned long b);
void calc_number_mul_si (CalcNumber **result, CalcNumber *a, signed long b);

void calc_number_sub (CalcNumber **result, CalcNumber *a, CalcNumber *b);
void calc_number_sub_z (CalcNumber **result, CalcNumber *a, mpz_t b);
void calc_number_sub_q (CalcNumber **result, CalcNumber *a, mpq_t b);
void calc_number_sub_f (CalcNumber **result, CalcNumber *a, mpf_t b);
void calc_number_sub_fr (CalcNumber **result, CalcNumber *a, mpfr_t b);
void calc_number_sub_d (CalcNumber **result, CalcNumber *a, double b);
void calc_number_sub_ui (CalcNumber **result, CalcNumber *a, unsigned long b);
void calc_number_sub_si (CalcNumber **result, CalcNumber *a, signed long b);

gint calc_number_cmp (CalcNumber *a, CalcNumber *b);
gint calc_number_cmp_z (CalcNumber *a, mpz_t b);
gint calc_number_cmp_q (CalcNumber *a, mpq_t b);
gint calc_number_cmp_f (CalcNumber *a, mpf_t b);
gint calc_number_cmp_fr (CalcNumber *a, mpfr_t b);
gint calc_number_cmp_d (CalcNumber *a, double b);
gint calc_number_cmp_ui (CalcNumber *a, unsigned long b);
gint calc_number_cmp_si (CalcNumber *a, signed long b);

void calc_number_cast (CalcNumber *self, CalcNumberType type);
void calc_number_neg (CalcNumber **result, CalcNumber *self);
void calc_number_abs (CalcNumber **result, CalcNumber *self);

gint calc_number_log (CalcNumber **result, CalcNumber *self);
gint calc_number_log2 (CalcNumber **result, CalcNumber *self);
gint calc_number_log10 (CalcNumber **result, CalcNumber *self);
gint calc_number_logn (CalcNumber **result, CalcNumber *self,
		       unsigned long base);
gint calc_number_pow (CalcNumber **result, CalcNumber *a, CalcNumber *b);

#ifdef _LIBCALC_INTERNAL

/*< private >*/
CalcNumberType _calc_number_get_final_type (CalcNumberType a, CalcNumberType b);
void _calc_number_release (CalcNumber *self);

#endif

G_END_DECLS

#endif
