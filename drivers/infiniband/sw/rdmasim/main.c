// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020-2021 Kamal Heib <kamalheib1@gmail.com>
 */

#include <linux/module.h>
#include <rdma/rdma_netlink.h>
#include <rdma/ib_verbs.h>

#include "rdmasim.h"
#include "verbs.h"

static const struct ib_device_ops rdmasim_dev_ops = {
	.dealloc_driver = rdmasim_dealloc_driver,
	.query_device = rdmasim_query_device,
	.query_port = rdmasim_query_port,
	.get_port_immutable = rdmasim_get_port_immutable,
};

static struct rdmasim_device *rdmasim_create_device(struct net_device *netdev)
{
	struct rdmasim_device *rdev;
	struct ib_device *ibdev;

	rdev = ib_alloc_device(rdmasim_device, ibdev);
	if (!rdev)
		return NULL;

	rdev->netdev = netdev;

	ibdev = &rdev->ibdev;
	strlcpy(ibdev->node_desc, RDMASIM_NODE_DESC, sizeof(ibdev->node_desc));
	ibdev->node_type = RDMA_NODE_IB_CA;
	ibdev->phys_port_cnt = RDMASIM_MAX_PORT;
	ib_set_device_ops(ibdev, &rdmasim_dev_ops);

	return rdev;
}

static void rdmasim_destroy_device(struct rdmasim_device *rdev)
{
	struct ib_device *ibdev = &rdev->ibdev;

	ib_dealloc_device(ibdev);
}

static int rdmasim_register_device(struct rdmasim_device *rdev,
				   const char *ibdev_name)
{
	struct net_device *netdev = rdev->netdev;
	struct ib_device *ibdev = &rdev->ibdev;
	int ret;

	ret = ib_device_set_netdev(ibdev, netdev, 1);
	if (ret) {
		pr_err("rdmasim: Failed to set netdevice, error=%d\n", ret);
		return ret;
	}

	ret = ib_register_device(ibdev, ibdev_name, NULL);
	if (ret) {
		pr_err("rdmasim: Failed to register device, error=%d\n", ret);
		return ret;
	}

	return 0;
}

static int rdmasim_newlink(const char *ibdev_name, struct net_device *netdev)
{
	struct rdmasim_device *rdev;
	struct ib_device *ibdev;
	int ret;

	ibdev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_RDMASIM);
	if (ibdev) {
		ib_device_put(ibdev);
		return -EEXIST;
	}

	rdev = rdmasim_create_device(netdev);
	if (!rdev)
		return -ENOMEM;

	ret = rdmasim_register_device(rdev, ibdev_name);
	if (ret) {
		rdmasim_destroy_device(rdev);
		return ret;
	}

	return 0;
}

static struct rdma_link_ops rdmasim_link_ops = {
	.type = "rdmasim",
	.newlink = rdmasim_newlink,
};

static __init int rdmasim_init_module(void)
{
	pr_info("rdmasim: Driver loaded\n");
	rdma_link_register(&rdmasim_link_ops);
	return 0;
}

static __exit void rdmasim_exit_module(void)
{
	pr_info("rdmasim: Driver unloaded\n");
	rdma_link_unregister(&rdmasim_link_ops);
	ib_unregister_driver(RDMA_DRIVER_RDMASIM);
}

module_init(rdmasim_init_module);
module_exit(rdmasim_exit_module);

MODULE_ALIAS_RDMA_LINK("rdmasim");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Heib <kamalheib1@gmail.com>");
MODULE_DESCRIPTION("Software RDMA simulator driver");
