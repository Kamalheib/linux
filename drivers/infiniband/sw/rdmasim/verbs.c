// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#include <linux/types.h>

#include <rdma/ib_verbs.h>

int rdmasim_get_port_immutable(struct ib_device *device, u8 port_num,
			       struct ib_port_immutable *immutable)
{
	return 0;
}


int rdmasim_query_device(struct ib_device *device,
			 struct ib_device_attr *device_attr,
			 struct ib_udata *udata)
{
	return 0;
}

int rdmasim_query_port(struct ib_device *device, u8 port_num,
		       struct ib_port_attr *port_attr)
{
	return 0;
}
