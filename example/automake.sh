#!/bin/sh
#
# This is a simple script that generates an automake file fragment to be
# included in the automake template. The fragment contains the list of
# example programs to build.
#
# Author: Anders Lövgren
# Date:   2009-03-27

programs=$(ls *.cpp | sed s%'\.cpp'%''%g | tr '\n' ' ')

# Make programs depend on library:
echo "$programs : \$(LIBFOA)"

# The list of programs to build:
echo "noinst_PROGRAMS = $programs"

# Each program has a single source file:
for p in $programs; do
  echo "${p}_SOURCES = $p.cpp"
done
