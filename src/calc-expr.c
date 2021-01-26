/*************************************************************************
 * calc-expr.c -- This file is part of libcalc.                          *
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "calc-expr.h"

G_DEFINE_ABSTRACT_TYPE (CalcExpr, calc_expr, G_TYPE_OBJECT)

static void
calc_expr_class_init (CalcExprClass *klass)
{
  klass->render = NULL;
  klass->get_dims = NULL;
  klass->print = NULL;
  klass->equivalent = NULL;
  klass->like_terms = NULL;
  klass->hash = NULL;
}

static void
calc_expr_init (CalcExpr *self)
{
}

/**
 * calc_expr_render:
 * @self: the expression to render
 * @cr: the #cairo_t object to render the expression on
 * @size: the font size to use for text
 *
 * Renders a graphical representation of the expression on the #cairo_t object
 * @cr, using a font size of @size. If @self is an invalid expression, @cr is
 * %NULL, or @size is zero, no action is performed. The current point of @cr
 * will remain unchanged, so subsequent calls to this function will draw over
 * previously-rendered expressions.
 **/

void
calc_expr_render (CalcExpr *self, cairo_t *cr, gsize size)
{
  CalcExprClass *klass;
  g_return_if_fail (CALC_IS_EXPR (self));
  g_return_if_fail (cr != NULL);
  g_return_if_fail (size > 0);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_if_fail (klass->render != NULL);
  klass->render (self, cr, size);
}

/**
 * calc_expr_get_dims:
 * @self: the expression to get the dimensions of
 * @cr: the #cairo_t object to construct text layouts with
 * @width: the location to store the width, or %NULL to ignore width
 * @height: the location to store the height, or %NULL to ignore height
 * @size: the font size to consider
 *
 * Determines the dimensions of an expression if it were to be rendered on
 * @cr with a font size of @size, and stores the width and height in @width
 * and @height respectively. @width or @height may be %NULL to indicate that
 * the width or height should be ignored. No drawing is done on @cr by calling
 * this function, and the current point of @cr will remain unchanged.
 **/

void
calc_expr_get_dims (CalcExpr *self, cairo_t *cr, gint *width, gint *height,
		    gsize size)
{
  CalcExprClass *klass;
  g_return_if_fail (CALC_IS_EXPR (self));
  g_return_if_fail (cr != NULL);
  g_return_if_fail (size > 0);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_if_fail (klass->get_dims != NULL);
  klass->get_dims (self, cr, width, height, size);
}

/**
 * calc_expr_print:
 * @self: the expression to print
 * @stream: the stdio stream to print to
 *
 * Prints a textual representation of @self to the stdio stream @stream. If
 * @self is not a valid expression or @stream is %NULL, no action is performed.
 **/

void
calc_expr_print (CalcExpr *self, FILE *stream)
{
  CalcExprClass *klass;
  g_return_if_fail (CALC_IS_EXPR (self));
  g_return_if_fail (stream != NULL);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_if_fail (klass->print != NULL);
  klass->print (self, stream);
}

/**
 * calc_expr_equivalent:
 * @self: the first expression
 * @other: the second expression
 *
 * Compares two expressions to determine if they are equivalent. Expressions
 * are equivalent if one can be rewritten as the other.
 *
 * Returns: %TRUE if both expressions are valid and equivalent, otherwise %FALSE
 **/

gboolean
calc_expr_equivalent (CalcExpr *self, CalcExpr *other)
{
  CalcExprClass *klass;
  g_return_val_if_fail (CALC_IS_EXPR (self), FALSE);
  g_return_val_if_fail (CALC_IS_EXPR (other), FALSE);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_val_if_fail (klass->equivalent != NULL, FALSE);
  return klass->equivalent (self, other);
}

/**
 * calc_expr_like_terms:
 * @self: the first expression
 * @other: the second expression
 *
 * Compares two expressions to determine if they are like terms.
 *
 * Returns: %TRUE if both expressions are valid and like terms, otherwise %FALSE
 **/

gboolean
calc_expr_like_terms (CalcExpr *self, CalcExpr *other)
{
  CalcExprClass *klass;
  g_return_val_if_fail (CALC_IS_EXPR (self), FALSE);
  g_return_val_if_fail (CALC_IS_EXPR (other), FALSE);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_val_if_fail (klass->like_terms != NULL, FALSE);
  return klass->like_terms (self, other);
}

/**
 * calc_expr_hash:
 * @self: the expression
 *
 * Computes a hash of an expression, used internally for sorting purposes.
 * The hash returned by this function should only be used for sorting. Matching
 * hashes does not guarantee equivalent expressions, which should be tested
 * for using calc_expr_equivalent() instead.
 *
 * Returns: the hash of the expression
 **/

gulong
calc_expr_hash (CalcExpr *self)
{
  CalcExprClass *klass;
  g_return_val_if_fail (CALC_IS_EXPR (self), FALSE);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_val_if_fail (klass->hash != NULL, FALSE);
  return klass->hash (self);
}

/**
 * calc_expr_evaluate:
 * @self: the expression to evaluate
 * @result: where to store the result of the calculation
 *
 * Evaluates the arithmetic expression @self. All arithmetic will be performed,
 * and variables will be substituted. If variables are used in the expression,
 * they must be set to a value. The result of the calculation is stored in
 * @result, which should be an instance of #CalcNumber.
 *
 * Returns: %TRUE if the calculation succeeded
 **/

gboolean
calc_expr_evaluate (CalcExpr *self, CalcExpr *result)
{
  CalcExprClass *klass;
  g_return_val_if_fail (CALC_IS_EXPR (self), FALSE);
  klass = CALC_EXPR_GET_CLASS (self);
  g_return_val_if_fail (klass->evaluate != NULL, FALSE);
  return klass->evaluate (self, result);
}

PangoLayout *
_calc_expr_layout_new (cairo_t *cr, const gchar *face, gsize size,
		       const gchar *text)
{
  PangoLayout *layout;
  PangoFontDescription *font;
  gchar *buffer;

  g_return_val_if_fail (cr != NULL, NULL);
  g_return_val_if_fail (face != NULL, NULL);
  g_return_val_if_fail (text != NULL, NULL);

  layout = pango_cairo_create_layout (cr);
  pango_layout_set_text (layout, text, -1);

  asprintf (&buffer, "%s %zu", face, size);
  font = pango_font_description_from_string (buffer);
  free (buffer);

  pango_layout_set_font_description (layout, font);
  pango_font_description_free (font);
  return layout;
}
