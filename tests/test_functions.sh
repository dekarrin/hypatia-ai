#!/bin/sh

bindir="$srcdir/src/"
script_file="$(basename "$0" .sh)"

export FEATURE_TEST=1

# tests program execution
test_memory_output ()
{
	dir="mem"
	output_file="tests/${script_file}_output.txt"
	check_file="tests/check/$dir/${script_file}.txt"
	if test ! -f "$check_file"
	then
		echo "Error: missing test file '$check_file'"
		return 2
	fi
	"$@" > "$output_file" 2>&1
	status=0
	used_output_file="tests/valgrind_${script_file}_output.txt"
	used_check_file="tests/check/$dir/valgrind_${script_file}.txt"
	clear_valgrind_cruft "$output_file" > "$used_output_file"
	clear_valgrind_cruft "$check_file" > "$used_check_file"
	if test "x$(diff "$used_output_file" "$used_check_file")" != x
	then
		status=1
	fi
	rm "$used_output_file"
	rm "$used_check_file"
	rm "$output_file"
	return $status
}

test_feature_output ()
{
	dir="feature"
	output_file="tests/${script_file}_output.txt"
	check_file="tests/check/$dir/${script_file}.txt"
	if test ! -f "$check_file"
	then
		echo "Error: missing test file '$check_file'"
		return 2
	fi
	"$@" > "$output_file" 2>&1
	status=0
	used_output_file="$output_file"
	used_check_file="$check_file"
	if test "x$(diff "$used_output_file" "$used_check_file")" != x
	then
		status=1
	fi
	rm "$used_output_file"
	return $status
}

# clears away valgrind-specific lines that would cause errors with different
# versions of valgrind, different invocations, etc.
clear_valgrind_cruft()
{
	sed 	-e '/^==[0-9]\+== Memcheck/d' \
		-e '/^==[0-9]\+== Copyright/d' \
		-e '/^==[0-9]\+== Using Valgrind-/d' \
		-e '/^==[0-9]\+== Command/d' \
		-e '/^==[0-9]\+== /s/[0-9,]\+ [Bb]ytes//g' \
		-e '/^==[0-9]\+==   total heap usage:/d' \
		-e '/^==[0-9]\+== ERROR SUMMARY/s/[0-9,]\+//g' \
		-e 's/^==[0-9]\+==/==PID==/' \
		"$1"
}
