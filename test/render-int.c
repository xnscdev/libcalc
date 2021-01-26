/*************************************************************************
 * render-int.c -- This file is part of libcalc.                         *
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

#include "libtest.h"

#define TEST_VALUE 12345L
#define TEST_SIZE 36

int
main (void)
{
  CalcNumber *a = calc_number_new_ui (TEST_VALUE);
  cairo_surface_t *surface =
    cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
  cairo_t *cr = cairo_create (surface);
  cairo_status_t status;

  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
  cairo_paint (cr);

  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_move_to (cr, 0.0, 0.0);
  calc_expr_render (CALC_EXPR (a), cr, TEST_SIZE);

  g_object_unref (a);
  cairo_destroy (cr);
  status = cairo_surface_write_to_png (surface, "render-int.png");
  cairo_surface_destroy (surface);
  assert (status == CAIRO_STATUS_SUCCESS);
  return 0;
}
