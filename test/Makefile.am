AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GMP_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

check_PROGRAMS =	\
	number-add	\
	number-cast	\
	number-init
TESTS = $(check_PROGRAMS)

check_LIBRARIES = libtest.a
libtest_a_SOURCES =	\
	assert.c	\
	libtest.h	\
	num-type.c

number_add_SOURCES = number-add.c
number_add_LDADD = libtest.a $(top_builddir)/src/libcalc.la

number_cast_SOURCES = number-cast.c
number_cast_LDADD = libtest.a $(top_builddir)/src/libcalc.la

number_init_SOURCES = number-init.c
number_init_LDADD = libtest.a $(top_builddir)/src/libcalc.la
