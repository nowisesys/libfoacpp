# Makefile for building libfoa examples using Visual Studio 2003.
#
# Author: Anders L�vgren
# Date:   2009-03-28

TARGET  = release

SRCLIB  = ..\..\..\src
SRCDIR  = ..\..\..\example
DESTDIR = .

VC7OPTS   = /O2 /G5 /EHsc /TP
DEFINES   = /DWIN32 /DHAVE_CONFIG_H /DLIBFOAPP_IMPORTS /D_WIN32_WINNT=0x400 /DSTDCALL=_stdcall
INCLUDES  = /I$(SRCDIR) /I$(SRCLIB) /I. /I..
CXXFLAGS  = $(VC7OPTS) $(DEFINES) $(INCLUDES)
LDFLAGS   = /link $(IMPORTLIB)

IMPORTLIB = ..\libfoa++\$(TARGET)\libfoa++.lib

EXAMPLES  = encode_escape.exe encode_file_stream1.exe encode_file_stream2.exe \
	encode_object_array.exe encode_stdout_stream.exe encode_string_stream.exe \
	encode_write.exe set_option.exe

all : $(EXAMPLES)

encode_escape.exe : {$(SRCDIR)}encode_escape.cpp
encode_file_stream1.exe : {$(SRCDIR)}encode_file_stream1.cpp
encode_file_stream2.exe : {$(SRCDIR)}encode_file_stream2.cpp
encode_object_array.exe : {$(SRCDIR)}encode_object_array.cpp
encode_stdout_stream.exe : {$(SRCDIR)}encode_stdout_stream.cpp
encode_string_stream.exe : {$(SRCDIR)}encode_string_stream.cpp
encode_write.exe : {$(SRCDIR)}encode_write.cpp
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