# Makefile for building libfoa examples using Visual Studio 2003.
#
# Author: Anders Lövgren
# Date:   2009-03-28

TARGET  = release
LIBNAME = libfoa++

SRCLIB  = ..\..\..\src
SRCDIR  = ..\..\..\example
DESTDIR = .

# Make sure to link with multi-threaded DLL (/MD). These options have to 
# match thoose in project libfoa++ (or nasty things will happen).
# 
# Debug version:
# VC7OPTS   = /O1 /G5 /EHsc /TP /MDd /GR
# Release version:
VC7OPTS   = /O2 /G5 /EHsc /TP /MD /GR

DEFINES   = /DWIN32 /DHAVE_CONFIG_H /DLIBFOAPP_IMPORTS /D_WIN32_WINNT=0x400 /DSTDCALL=_thiscall
INCLUDES  = /I$(SRCDIR) /I$(SRCLIB) /I. /I..
CXXFLAGS  = $(VC7OPTS) $(DEFINES) $(INCLUDES)
LDFLAGS   = /link $(IMPORTLIB)

IMPORTLIB = ..\$(LIBNAME)\$(TARGET)\$(LIBNAME).lib

EXAMPLES  = decode_file_stream.exe decode_memory_buffer.exe decode_string_buffer.exe \
			decode_string_dynamic.exe encode_escape.exe encode_file_stream1.exe \
			encode_file_stream2.exe encode_object_array.exe encode_stdout_stream.exe \
			encode_string_stream.exe encode_write.exe set_memory_strategy.exe \
			set_option.exe decode_escape.exe decode_large_object.exe decode_realloc.exe

all : $(EXAMPLES)

decode_escape.exe : {$(SRCDIR)}decode_escape.cpp
decode_large_object.exe : {$(SRCDIR)}decode_large_object.cpp
decode_realloc.exe : {$(SRCDIR)}decode_realloc.cpp
decode_memory_buffer.exe : {$(SRCDIR)}decode_memory_buffer.cpp
decode_string_buffer.exe : {$(SRCDIR)}decode_string_buffer.cpp
decode_string_dynamic.exe : {$(SRCDIR)}decode_string_dynamic.cpp
encode_escape.exe : {$(SRCDIR)}encode_escape.cpp
encode_file_stream1.exe : {$(SRCDIR)}encode_file_stream1.cpp
encode_file_stream2.exe : {$(SRCDIR)}encode_file_stream2.cpp
encode_object_array.exe : {$(SRCDIR)}encode_object_array.cpp
encode_stdout_stream.exe : {$(SRCDIR)}encode_stdout_stream.cpp
encode_string_stream.exe : {$(SRCDIR)}encode_string_stream.cpp
encode_write.exe : {$(SRCDIR)}encode_write.cpp
set_memory_strategy.exe : {$(SRCDIR)}set_memory_strategy.cpp
set_option.exe : {$(SRCDIR)}set_option.cpp

# Rule for building source files (we can't use builtin):
{$(SRCDIR)}.cpp{}.exe :
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS)

clean :
	if exist *.obj del /q *.obj
	if exist *.tds del /q *.tds
distclean : clean
	if exist *.exe del /q *.exe
rebuild : distclean all
