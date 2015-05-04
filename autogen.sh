#!/bin/sh

# Generates build files
#
# Defaults for Autotools may be overrided by setting the environment variable
# for that program. $LIBTOOLIZE, $ACLOCAL, $AUTOHEADER, $AUTOMAKE, and $AUTOCONF
# may each be set in the parent environment to use their contents rather than
# the defaults.

LIBTOOLIZE_NAMES="$LIBTOOLIZE libtoolize glibtoolize"
ACLOCAL_NAMES="$ACLOCAL aclocal"
AUTOHEADER_NAMES="$AUTOHEADER autoheader"
AUTOMAKE_NAMES="$AUTOMAKE automake"
AUTOCONF_NAMES="$AUTOCONF autoconf"

export status
export working_program

# quick func for getting maximum of two numbers
num_max ()
{
	if test "$1" -gt "$2"
	then
		echo "$1"
	else
		echo "$2"
	fi
}

check_program ()
{
	working_program=
	for attempt in "$@"
	do
		(${attempt} --version) < /dev/null > /dev/null 2>&1
		status="$?"
		if test "$status" = 0
		then
			working_program="$attempt"
			break
		fi
	done
	if test -z "$working_program"
	then
		echo
		echo "Error: could not find a valid program in ("$@")"
	fi
}

run_program ()
{
	echo
	echo "Running $@"
	$@ || { echo; echo "Error: $1 failed."; exit 1; }
}

if test "x$1" = "x-f" -o "x$1" = "x--force"
then
	force=1
fi

terminate="0"

# tr is used inside of configure.ac to pick up the version number
check_program tr
terminate=$(num_max $status $terminate)
if test "$terminate" = 1
then
	if test "x$force" = "x1"
	then
		echo
		echo -n "Could not find tr on this system; program versioning "
		echo "cannot be automated."
		echo -n "Replace the second argument to AC_INIT in "
		echo "configure.ac with the"
		echo -n "number in the file VERSION and execute this script "
		echo "with either -f or --force"
		echo "to retry."
	else
		terminate=0
	fi
fi

check_program $LIBTOOLIZE_NAMES
LIBTOOLIZE="$working_program"
terminate=$(num_max $status $terminate)
check_program $ACLOCAL_NAMES
ACLOCAL="$working_program"
terminate=$(num_max $status $terminate)
check_program $AUTOHEADER_NAMES
AUTOHEADER="$working_program"
terminate=$(num_max $status $terminate)
check_program $AUTOMAKE_NAMES
AUTOMAKE="$working_program"
terminate=$(num_max $status $terminate)
check_program $AUTOCONF_NAMES
AUTOCONF="$working_program"
terminate=$(num_max $status $terminate)

if test "$terminate" != 0
then
	echo
	echo "Program check failed."
	exit 1
fi

# Otherwise, we tested the environment and have our programs. Time to generate:

git log --date=short --format=format:"%ad %an%n%n	* %s%n" > ChangeLog
# git log uses newline as separator between entries, so the last one will not
# have a newline
echo >> ChangeLog
run_program $LIBTOOLIZE --force --copy
run_program $ACLOCAL
run_program $AUTOHEADER
run_program $AUTOMAKE --add-missing --copy
run_program $AUTOCONF 

