AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = -std=gnu99 -Wall -pedantic -Werror=implicit			\
	$(GMP_CFLAGS) $(MPFR_CFLAGS) $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)	\
	$(PANGOCAIRO_CFLAGS)

TESTS =	eval-exp	\
	eval-frac	\
	eval-num	\
	eval-sum	\
	eval-var	\
	num-add-n	\
	num-add-q	\
	num-add-ui	\
	num-add-si	\
	num-cast	\
	num-div-int	\
	num-div-nogcd	\
	num-div-dec	\
	num-log2	\
	num-log10	\
	num-log7	\
	num-mul-n	\
	num-mul-q	\
	num-mul-ui	\
	num-mul-si	\
	num-pow		\
	num-abs-z	\
	num-abs-f	\
	num-neg-z	\
	num-neg-f	\
	num-sub-n	\
	num-sub-q	\
	num-sub-ui	\
	num-sub-si	\
	term-num	\
	term-var	\
	term-exp2	\
	term-exp3
check_PROGRAMS = $(TESTS)

check_LIBRARIES = libtest.a
libtest_a_SOURCES =	\
	assert.c	\
	libtest.h

LDADD = libtest.a $(top_builddir)/src/libcalc.la		\
	$(GMP_LIBS) $(MPFR_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS)	\
	$(PANGOCAIRO_LIBS)
