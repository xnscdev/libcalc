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

static GHashTable *calc_variable_values;

static gboolean
calc_variable_key_equal (gconstpointer a, gconstpointer b)
{
  return g_strcmp0 ((const gchar *) a, (const gchar *) b) == 0;
}

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

  calc_variable_values =
    g_hash_table_new_full (g_str_hash, calc_variable_key_equal, g_free, NULL);
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
  return g_str_hash (CALC_VARIABLE (expr)->text);
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

/**
 * calc_variable_set_value:
 * @name: the name of the variable
 * @value: the value to set the variable to
 *
 * Sets the value of the variable named @name to @value. Whenever the value
 * of the variable @name is requested, @value will be returned. If @value
 * is %NULL, any existing value of the variable is removed. If @value is not
 * %NULL and is not a valid expression, no action is performed.
 **/

void
calc_variable_set_value (const gchar *name, CalcExpr *value)
{
  g_return_if_fail (value == NULL || CALC_IS_EXPR (value));
  g_hash_table_insert (calc_variable_values, g_strdup (name), value);
}

/**
 * calc_variable_get_value:
 * @name: the name of the variable
 *
 * Gets the value of the variable named @name.
 *
 * Returns: the value of the variable, or %NULL if no variable named @name
 * was previously set to a value
 **/

CalcExpr *
calc_variable_get_value (const gchar *name)
{
  return g_hash_table_lookup (calc_variable_values, name);
}
