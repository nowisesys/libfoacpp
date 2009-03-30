#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([libfoa++], [1.0.2], [lespaul@algonet.se])
AM_INIT_AUTOMAKE([libfoa++], [1.0.2])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# We need _XOPEN_SOURCE=600 for isblank():
CXXFLAGS="$CXXFLAGS -D_XOPEN_SOURCE=600"

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memmove isblank])

# Check whether to build examples:
AC_MSG_CHECKING([whether to build examples])
AC_ARG_ENABLE([examples], 
  [AS_HELP_STRING([--enable-examples], 
    [Build libfoa example code [default=no]])],
  [build_examples=$enableval],
  [build_examples=no]
)
AC_MSG_RESULT($build_examples)
AM_CONDITIONAL(BUILD_EXAMPLES, test x${build_examples} == xyes)

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 doc/Makefile
                 example/Makefile
                 src/libfoa++.pc])
AC_OUTPUT
