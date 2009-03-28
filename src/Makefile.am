EXTRA_DIST = libfoa++.pc libfoa++.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfoa++.pc

lib_LTLIBRARIES = libfoa++.la
libfoa___la_SOURCES = libfoa++.hpp internal.hpp encoder.cpp decoder.cpp \
		      libfoa++.cpp
libfoa___la_LDFLAGS = -version-info 1:0:1 -Wl,-x

noinst_HEADERS  = internal.hpp
include_HEADERS = libfoa++.hpp
