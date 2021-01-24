AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit \
	$(GMP_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

TESTS =	eval-arith	\
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
	libtest.h	\
	num-type.c

DEP_LIBS = $(GMP_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS)

eval_arith_SOURCES = eval-arith.c
eval_arith_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_add_SOURCES = number-add.c
number_add_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_cast_SOURCES = number-cast.c
number_cast_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_div_SOURCES = number-div.c
number_div_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_init_SOURCES = number-init.c
number_init_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_log_SOURCES = number-log.c
number_log_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_mul_SOURCES = number-mul.c
number_mul_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_pow_SOURCES = number-pow.c
number_pow_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_sign_SOURCES = number-sign.c
number_sign_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

number_sub_SOURCES = number-sub.c
number_sub_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

term_factors_SOURCES = term-factors.c
term_factors_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)

term_init_SOURCES = term-init.c
term_init_LDADD = libtest.a $(top_builddir)/src/libcalc.la $(DEP_LIBS)
