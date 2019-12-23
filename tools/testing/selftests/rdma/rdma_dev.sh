#!/bin/bash
#
# SPDX-License-Identifier: GPL-2.0
# Author: Kamal Heib <kamalheib1@gmail.com>

rdma_lib=$(dirname $0)/rdma_lib.sh
source $rdma_lib

ALL_TESTS="test_node_type
	   test_node_desc
	   test_read_only
"

test_node_type()
{
	local not_found=1
	local dev=$RDMA_DEV
	local types=("1: CA" "2: switch" "3: router" "4: RNIC" "5: usNIC"
		     "6: usNIC UDP" "7: <unknown>")

	node_type="$(cat $INFINIBAND_SYSFS/$dev/node_type)"
	check_ret_val $? "$dev: Failed to read node_type"

	for nt in "${types[@]}"; do
		if [ "$nt" == "${node_type}" ]; then
			not_found=0
			break
		fi
	done

	check_ret_val $not_found "$dev: unexpected node_type=\"$node_type\""
	print_results "$dev: Test node_type"
}

test_node_desc()
{
	dev=$RDMA_DEV

	node_desc="$(cat $INFINIBAND_SYSFS/$dev/node_desc)"
	check_ret_val $? "$dev: Failed to read node_desc"

	echo "test $dev node_desc" > $INFINIBAND_SYSFS/$dev/node_desc
	check_ret_val $? "$dev: Write to node_desc failed"

	tested_node_desc="$(cat $INFINIBAND_SYSFS/$dev/node_desc)"
	check_ret_val $? "$dev: Failed to read node_desc"

	if [ "$tested_node_desc" -ne "test $dev node_desc" ]; then
		check_ret_val 1 "$dev: Un-expected node description"
	fi

	echo $node_desc > $INFINIBAND_SYSFS/$dev/node_desc
	check_ret_val $? "$dev: Restore node_desc failed"
	print_results "$dev: Test node_desc"
}

test_read_only_sysfs()
{
	local dev=$RDMA_DEV
	local sysfs=$1

	cat $INFINIBAND_SYSFS/$dev/$sysfs > /dev/null
	check_ret_val $? "$dev: Failed to read $sysfs"

	(echo 1 > $INFINIBAND_SYSFS/$dev/$sysfs) 2> /dev/null
	check_ret_val_fail $? "$dev: Write to $sysfs finsih successfuly (expected to fail!)"

	print_results "$dev: Test $sysfs"
}

test_read_only()
{
	local dev=$RDMA_DEV
	local sysfs_list=( "node_type" "node_guid" "sys_image_guid" "fw_ver" )

	for sysfs in "${sysfs_list[@]}"; do
		test_read_only_sysfs $sysfs
	done
}

check_and_skip $(id -u) "Need root privileges"

rdma_devices=( $(get_rdma_devices) )

test ${#rdma_devices[@]} -ne 0
check_and_skip $? "No RDMA devices available"

for rdma_dev in "${rdma_devices[@]}"; do
	RDMA_DEV=$rdma_dev
	run_tests
done

exit $EXIT_STATUS
