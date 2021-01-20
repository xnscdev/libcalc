AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit -Wno-switch \
	$(GMP_CFLAGS) $(MPFR_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

pkgincludedir = $(includedir)/libcalc

lib_LTLIBRARIES = libcalc.la
libcalc_la_SOURCES =	\
	calc-expr.c	\
	calc-number.c	\
	calc-variable.c
libcalc_la_LIBADD = $(GMP_LIBS) $(MPFR_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS)

pkginclude_HEADERS =	\
	calc-expr.h	\
	calc-number.h	\
	calc-variable.h	\
	libcalc.h
