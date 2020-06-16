// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#include <linux/module.h>
#include <rdma/rdma_netlink.h>
#include <rdma/ib_verbs.h>

#include "rdmasim.h"

static struct rdmasim_device *rdmasim_create_device(void)
{
	struct rdmasim_device *rdev;

	rdev = ib_alloc_device(rdmasim_device, ibdev);
	if(!rdev)
		return NULL;

	return rdev;
}

static int rdmasim_newlink(const char *ibdev_name, struct net_device *netdev)
{
	struct rdmasim_device *rdev;
	struct ib_device *ib_dev;

	ib_dev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_RDMASIM);
	if (ib_dev) {
		ib_device_put(ib_dev);
		return -EEXIST;
	}

	rdev = rdmasim_create_device();
	if (!rdev)
		return -ENOMEM;

	return 0;
}

static struct rdma_link_ops rdmasim_link_ops = {
	.type = "rdmasim",
	.newlink = rdmasim_newlink,
};

static __init int rdmasim_init_module(void)
{
	rdma_link_register(&rdmasim_link_ops);
	return 0;
}

static __exit void rdmasim_exit_module(void)
{
	rdma_link_unregister(&rdmasim_link_ops);
}

module_init(rdmasim_init_module);
module_exit(rdmasim_exit_module);

MODULE_ALIAS_RDMA_LINK("rdmasim");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Heib <kamalheib1@gmail.com>");
MODULE_DESCRIPTION("Software RDMA simulator driver");
