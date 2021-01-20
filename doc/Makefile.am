DOC_MODULE = libcalc
DOC_MAIN_SGML_FILE = $(DOC_MODULE)-docs.xml
DOC_SOURCE_DIR = $(top_srcdir)/src

SCAN_OPTIONS =
SCANGOBJ_OPTIONS =
MKDB_OPTIONS = --xml-mode --output-format=xml
MKHTML_OPTIONS =
FIXXREF_OPTIONS =

HFILE_GLOB = $(top_srcdir)/src/calc-*.h
CFILE_GLOB = $(top_srcdir)/src/calc-*.c
EXTRA_HFILES =
IGNORE_HFILES = libcalc.h
HTML_IMAGES =

content_files =
expand_content_files =

GTKDOC_CFLAGS = -I$(top_srcdir)/src
GTKDOC_LIBS = $(top_builddir)/src/libcalc.la

include $(top_srcdir)/gtk-doc.make

-include $(top_srcdir)/git.mk
