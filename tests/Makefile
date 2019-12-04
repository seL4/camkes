#
# Copyright 2019, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#

ifneq (${REGEX},)
REGEX_COMMAND:=${REGEX:%=-R %} ${EXCLUDE_REGEX:%=-E %}
endif

ifneq (${VERBOSE},)
VERBOSE_COMMAND:=${VERBOSE}
endif

ifneq (${RANGE},)
RANGE_COMMAND:=${RANGE:%=-I %}
endif

run_tests:
	@mkdir -p build
	@(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} ${VERBOSE_COMMAND})

run_tests_xml:
	@mkdir -p build
	(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} ${VERBOSE_COMMAND} -T Test --no-compress-output)
	cat build/Testing/*/Test.xml

list_tests:
	@mkdir -p build
	(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} -N)
