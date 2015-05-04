# all flags used by the c compiler
AM_CFLAGS=-Wall -std=c99
# libraries common to all executables
LDADD=libmath.la
# linker flags common to all executables?
AM_LDFLAGS=-static


# define all libraries and their implementation files
noinst_LTLIBRARIES=libmath.la
libmath_la_SOURCES=math.c

# define all executables
bin_PROGRAMS=testmath
testmath_SOURCES=testmath.c
# libs to link testmath with, if it were different than common:
# testmath_LDADD=libsomelib.la ${LDADD} -lexternallib
