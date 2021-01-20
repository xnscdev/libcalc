AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GMP_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

check_PROGRAMS =	\
	number-cast	\
	number-init
TESTS = $(check_PROGRAMS)

number_cast_SOURCES = number-cast.c
number_cast_LDADD = $(top_builddir)/src/libcalc.la

number_init_SOURCES = number-init.c
number_init_LDADD = $(top_builddir)/src/libcalc.la
