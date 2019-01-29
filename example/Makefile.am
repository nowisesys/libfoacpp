## Process this file with automake to produce Makefile.in

## Static link libfoa++:
LIBFOA = $(top_srcdir)/src/.libs/libfoa++.a
## Dynamic link libfoa++:
# LIBFOA = $(top_srcdir)/src/libfoa++.la

AM_CPPFLAGS = -I$(top_srcdir)/src
AM_LDFLAGS  = $(LIBFOA)

## Include automake dependencies for this makefile template:
include Makefile.dep
