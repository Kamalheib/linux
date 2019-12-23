#!/bin/bash
#
# SPDX-License-Identifier: GPL-2.0
# Author: Kamal Heib <kamalheib1@gmail.com>

# Kselftest framework requirement - SKIP code is 4
ksft_skip=4

EXIT_STATUS=0
RET_MSG=""
RET=0

INFINIBAND_SYSFS="/sys/class/infiniband"

check_and_skip()
{
	local rc=$1
	local msg=$2

	if [ $rc -ne 0 ]; then
		echo "SKIP: $msg"
		exit $ksft_skip
	fi
}

check_ret_val()
{
	local rc=$1
	local msg=$2

	if [[ $RET -eq 0 && $rc -ne 0 ]]; then
		RET=$rc
		RET_MSG=$msg
	fi
}

check_ret_val_fail()
{
	local rc=$1
	local msg=$2

	if [[ $rc -eq 0 ]]; then
		RET=1
		RET_MSG=$msg
	fi
}

print_results()
{
	local test_name=$1

	if [[ $RET -ne 0 ]]; then
		EXIT_STATUS=1
		printf "TEST: %-60s [FAIL]\n" "$test_name"
		if [[ ! -z "$RET_MSG" ]]; then
			printf "\t%s\t\n" "$RET_MSG"
			RET_MSG=""
			RET=0
		fi
		return 1
	fi

	printf "TEST: %-60s [OK]\n" "$test_name"
	return 0
}

get_rdma_devices()
{
	echo `ls $INFINIBAND_SYSFS 2>/dev/null`
}

run_tests()
{
	local cur_test

	for cur_test in ${ALL_TESTS}; do
		$cur_test
	done
}
