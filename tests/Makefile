#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
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

ifneq (${RERUN_FAILED},)
RERUN_FAILED_COMMAND:=--rerun-failed --output-on-failure
endif

run_tests:
	@mkdir -p build
	@(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} ${VERBOSE_COMMAND} ${RERUN_FAILED_COMMAND})

run_tests_xml:
	@mkdir -p build
	(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} ${VERBOSE_COMMAND} -T Test --no-compress-output)
	cat build/Testing/*/Test.xml

list_tests:
	@mkdir -p build
	(cd build && cmake .. && ctest ${RANGE_COMMAND} ${REGEX_COMMAND} -N)
