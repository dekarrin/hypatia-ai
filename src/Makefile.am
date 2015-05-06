# all flags used by the c compiler
AM_CFLAGS=-Wall -std=c99
# libraries common to all executables
LDADD=libmath.la libactivation.la libneuron.la libutil.la libcombiner.la
# linker flags common to all executables?
AM_LDFLAGS=-static


# define all libraries and their implementation files
noinst_LTLIBRARIES=libmath.la libactivation.la libneuron.la libutil.la libcombiner.la
libmath_la_SOURCES=math.c math.h
libactivation_la_SOURCES=activation.c activation.h
libactivation_la_LIBADD=-lm
libneuron_la_SOURCES=neuron.c neuron.h
libutil_la_SOURCES=util.c util.h
libcombiner_la_SOURCES=combiner.c combiner.h

# define all executables
bin_PROGRAMS=testmath
testmath_SOURCES=testmath.c
# libs to link testmath with, if it were different than common:
# testmath_LDADD=libsomelib.la ${LDADD} -lexternallib
