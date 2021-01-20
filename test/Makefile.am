AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GMP_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

check_PROGRAMS =	\
	number-init-i	\
	number-init-z
TESTS = $(check_PROGRAMS)

number_init_i_SOURCES = number-init-i.c
number_init_i_LDADD = $(top_builddir)/src/libcalc.la

number_init_z_SOURCES = number-init-z.c
number_init_z_LDADD = $(top_builddir)/src/libcalc.la
