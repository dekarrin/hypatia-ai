# all flags used by the c compiler
AM_CFLAGS=-Wall -Werror -std=c99
# libraries common to all executables
#LDADD=libmath.la libactivation.la libneuron.la libutil.la libcombiner.la
# linker flags common to all executables?
AM_LDFLAGS=-static

# define all libraries and their implementation files
noinst_LTLIBRARIES=libvector.la libactivation.la libneuron.la libutil.la libcombiner.la
libvector_la_SOURCES=vector.c vector.h
libvector_la_LIBADD=-lm
libactivation_la_SOURCES=activation.c activation.h
libactivation_la_LIBADD=-lm
libneuron_la_SOURCES=neuron.c neuron.h
libneuron_la_LIBADD=libutil.la libcombiner.la libactivation.la libvector.la
libutil_la_SOURCES=util.c util.h
libcombiner_la_SOURCES=combiner.c combiner.h

# define all executables
bin_PROGRAMS=testvector testactivation testutil testcombiner testneuron
testvector_SOURCES=testvector.c
testvector_LDADD=libvector.la
testactivation_SOURCES=testactivation.c
testactivation_LDADD=libactivation.la
testutil_SOURCES=testutil.c
testutil_LDADD=libutil.la
testcombiner_SOURCES=testcombiner.c
testcombiner_LDADD=libvector.la libcombiner.la
testneuron_SOURCES=testneuron.c
testneuron_LDADD=libneuron.la
# libs to link testmath with, if it were different than common:
# testmath_LDADD=libsomelib.la ${LDADD} -lexternallib
