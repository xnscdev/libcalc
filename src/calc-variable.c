/*************************************************************************
 * calc-variable.c -- This file is part of libcalc.                        *
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

#include "calc-variable.h"

G_DEFINE_TYPE (CalcVariable, calc_variable, CALC_TYPE_EXPR)

static void calc_variable_print (CalcExpr *expr, FILE *stream);
static gboolean calc_variable_equivalent (CalcExpr *self, CalcExpr *other);
static gboolean calc_variable_like_terms (CalcExpr *self, CalcExpr *other);
static gulong calc_variable_hash (CalcExpr *expr);

static void
calc_variable_dispose (GObject *obj)
{
  g_free (CALC_VARIABLE (obj)->text);
}

static void
calc_variable_class_init (CalcVariableClass *klass)
{
  G_OBJECT_CLASS (klass)->dispose = calc_variable_dispose;
  CALC_EXPR_CLASS (klass)->print = calc_variable_print;
  CALC_EXPR_CLASS (klass)->equivalent = calc_variable_equivalent;
  CALC_EXPR_CLASS (klass)->like_terms = calc_variable_like_terms;
  CALC_EXPR_CLASS (klass)->hash = calc_variable_hash;
}

static void
calc_variable_init (CalcVariable *self)
{
}

static void
calc_variable_print (CalcExpr *expr, FILE *stream)
{
  fprintf (stream, "%s", CALC_VARIABLE (expr)->text);
}

static gboolean
calc_variable_equivalent (CalcExpr *self, CalcExpr *other)
{
  g_return_val_if_fail (CALC_IS_VARIABLE (other), FALSE);
  return g_strcmp0 (CALC_VARIABLE (self)->text, CALC_VARIABLE (other)->text);
}

static gboolean
calc_variable_like_terms (CalcExpr *self, CalcExpr *other)
{
  /* Temporary */
  return calc_variable_equivalent (self, other);
}

static gulong
calc_variable_hash (CalcExpr *expr)
{
  /* djb2 algorithm */
  gulong hash = 5831;
  gchar *ptr = CALC_VARIABLE (expr)->text;
  while (*ptr != '\0')
    {
      hash = (hash << 5) + hash + *ptr;
      ptr++;
    }
  return hash;
}

/**
 * calc_variable_new:
 * @text: the name of the variable
 *
 * Creates a new variable object named @text. The object may be used to
 * represent the variable in other expressions.
 *
 * Returns: the newly constructed instance, or %NULL if @text is %NULL
 **/

CalcVariable *
calc_variable_new (const gchar *text)
{
  CalcVariable *self;
  g_return_val_if_fail (text != NULL, NULL);
  self = g_object_new (CALC_TYPE_VARIABLE, NULL);
  self->text = g_strdup (text);
  return self;
}

void
calc_variable_set_value (const gchar *name, CalcExpr *value)
{
}

CalcExpr *
calc_variable_get_value (const gchar *name)
{
}
