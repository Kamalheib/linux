// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020-2021 Kamal Heib <kamalheib1@gmail.com>
 */

#include <linux/module.h>
#include "rdmasim.h"

static __init int rdmasim_init_module(void)
{
	pr_info("rdmasim: Driver loaded\n");
	return 0;
}

static __exit void rdmasim_exit_module(void)
{
	pr_info("rdmasim: Driver unloaded\n");
}

module_init(rdmasim_init_module);
module_exit(rdmasim_exit_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Heib <kamalheib1@gmail.com>");
MODULE_DESCRIPTION("Software RDMA simulator driver");
