AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

pkgincludedir = $(includedir)/libcalc

lib_LTLIBRARIES = libcalc.la
libcalc_la_SOURCES =	\
	calc-expr.c	\
	calc-number.c
libcalc_la_LIBADD = $(GLIB_LIBS) $(GOBJECT_LIBS)

pkginclude_HEADERS =	\
	calc-expr.h	\
	calc-number.h
