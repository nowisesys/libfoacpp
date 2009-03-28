## Process this file with automake to produce Makefile.in

## Static link libfoa++:
LIBFOA = $(top_srcdir)/src/.libs/libfoa++.a
## Dynamic link libfoa++:
# LIBFOA = $(top_srcdir)/src/libfoa++.la

INCLUDES = -I$(top_srcdir)/src
AM_LDFLAGS  = $(LIBFOA)

## Include makefile fragment in automake template:
include Makefile.def
