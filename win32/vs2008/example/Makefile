# Makefile for building libfoa++ examples using Visual Studio 2008.
#
# Author: Anders Lövgren
# Date:   2010-10-19

TARGET  = debug
LIBNAME = libfoa++

SRCLIB  = ..\..\..\src
SRCDIR  = ..\..\..\example
DESTDIR = .

!IF "$(TARGET)" == "debug"
VC9OPTS = /Od /Gm /EHsc /RTC1 /MDd /Fd"Debug\vc90.pdb" /ZI 
DEFINES = /D "_DEBUG" 
!ELSE
VC9OPTS	= /O2 /Oi /GL /FD /EHsc /MD /Gy /Fd"Release\vc90.pdb" /Zi 
DEFINES	= /D "NDEBUG"
!ENDIF

VC9OPTS		= $(VC9OPTS) /W3 /nologo /TP /errorReport:prompt

DEFINES		= $(DEFINES) /D "WIN32" /D "_CONSOLE" /D "HAVE_CONFIG_H=1" /D "_UNICODE" /D "UNICODE"
DEFINES		= $(DEFINES) /DLIBFOAPP_IMPORTS /D_WIN32_WINNT=0x400 /DSTDCALL=_stdcall

INCLUDES	= /I$(SRCDIR) /I$(SRCLIB) /I. /I..
CXXFLAGS	= $(DEFINES) $(VC9OPTS) $(INCLUDES)
LDFLAGS		= /link $(IMPORTLIB)

IMPORTLIB = ..\$(TARGET)\$(LIBNAME).lib
IMPORTDLL = ..\$(TARGET)\$(LIBNAME).dll

EXAMPLES  = decode_file_stream.exe decode_memory_buffer.exe decode_string_buffer.exe \
			decode_string_dynamic.exe encode_escape.exe encode_file_stream1.exe \
			encode_file_stream2.exe encode_object_array.exe encode_stdout_stream.exe \
			encode_string_stream.exe encode_write.exe set_memory_strategy.exe \
			set_option.exe decode_escape.exe decode_large_object.exe decode_realloc.exe

all : $(EXAMPLES)
	copy "$(IMPORTDLL)" $(DESTDIR)

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
	if exist *.pdb del /q *.pdb
	if exist *.ilk del /q *.ilk
	if exist *.exe.manifest del /q *.exe.manifest
distclean : clean
	if exist *.exe del /q *.exe
	if exist *.dll del /q *.dll
rebuild : distclean all
