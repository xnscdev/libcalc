AM_CPPFLAGS = -I$(top_builddir)
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit -Wno-switch	\
	$(GMP_CFLAGS) $(MPFR_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)	\
	$(PANGOCAIRO_CFLAGS)

pkgincludedir = $(includedir)/libcalc
pkgconfigdir = $(libdir)/pkgconfig

lib_LTLIBRARIES = libcalc.la
libcalc_la_SOURCES =		\
	calc-exponent.c		\
	calc-expr.c		\
	calc-fraction.c		\
	calc-number.c		\
	calc-number-add.c	\
	calc-number-cmp.c	\
	calc-number-div.c	\
	calc-number-mul.c	\
	calc-number-sub.c	\
	calc-number-trans.c	\
	calc-sum.c		\
	calc-term.c		\
	calc-variable.c
libcalc_la_LIBADD = $(GMP_LIBS) $(MPFR_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS) \
	$(PANGOCAIRO_LIBS)

pkginclude_HEADERS =	\
	calc-exponent.h	\
	calc-expr.h	\
	calc-fraction.h	\
	calc-number.h	\
	calc-sum.h	\
	calc-term.h	\
	calc-variable.h	\
	libcalc.h

pkgconfig_DATA = libcalc.pc

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libcalc_la_SOURCES) $(pkginclude_HEADERS)

Calc-1.0.gir: libcalc.la
Calc_1_0_gir_INCLUDES = GObject-2.0
Calc_1_0_gir_CFLAGS = $(INCLUDES)					\
	$(GMP_CFLAGS) $(MPFR_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)	\
	$(PANGOCAIRO_CFLAGS)
Calc_1_0_gir_LIBS = libcalc.la
Calc_1_0_gir_FILES = $(introspection_sources)
Calc_1_0_gir_NAMESPACE = Calc
Calc_1_0_gir_VERSION = $(VERSION)
INTROSPECTION_GIRS += Calc-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
endif
