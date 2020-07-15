// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#include <rdma/ib_verbs.h>
#include <net/addrconf.h>
#include <linux/types.h>

#include "rdmasim.h"

int rdmasim_get_port_immutable(struct ib_device *device, u8 port_num,
			       struct ib_port_immutable *immutable)
{
	return 0;
}


int rdmasim_query_device(struct ib_device *device,
			 struct ib_device_attr *device_attr,
			 struct ib_udata *udata)
{
	struct rdmasim_device *rdev = to_rdmasim_dev(device);

	device_attr->device_cap_flags = IB_DEVICE_ALLOW_USER_UNREG;
	addrconf_addr_eui48((unsigned char *)&device_attr->sys_image_guid,
			    rdev->netdev->dev_addr);
	return 0;
}

int rdmasim_query_port(struct ib_device *device, u8 port_num,
		       struct ib_port_attr *port_attr)
{
	return 0;
}

int rdmasim_query_gid(struct ib_device *device, u8 port_num,
		      int index, union ib_gid *gid)
{
	return 0;
}

void rdmasim_dealloc(struct ib_device *dev)
{
}
