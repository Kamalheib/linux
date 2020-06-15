// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#include <linux/module.h>
#include <rdma/rdma_netlink.h>
#include <rdma/ib_verbs.h>

#include "rdmasim.h"


static __init int rdmasim_init_module(void)
{
	return 0;
}

static __exit void rdmasim_exit_module(void)
{
}

module_init(rdmasim_init_module);
module_exit(rdmasim_exit_module);

MODULE_ALIAS_RDMA_LINK("rdmasim");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Heib <kamalheib1@gmail.com>");
MODULE_DESCRIPTION("Software RDMA simulator driver");
