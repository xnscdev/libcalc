AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GMP_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

TESTS =	eval-exp	\
	eval-frac	\
	eval-num	\
	eval-sum	\
	eval-var	\
	number-add	\
	number-cast	\
	number-div	\
	number-init	\
	number-log	\
	number-mul	\
	number-pow	\
	number-sign	\
	number-sub	\
	term-factors	\
	term-init
check_PROGRAMS = $(TESTS)

check_LIBRARIES = libtest.a
libtest_a_SOURCES =	\
	assert.c	\
	libtest.h

LDADD = libtest.a $(top_builddir)/src/libcalc.la \
	$(GMP_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS)
