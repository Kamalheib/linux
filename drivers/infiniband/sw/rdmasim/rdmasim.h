// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#ifndef _RDMASIM_H
#define _RDMASIM_H

#define RDMASIM_MAX_PORT 1
#define RDMASIM_NODE_DESC "Software RDMA suimlator"

struct rdmasim_device {
	struct ib_device ibdev;
	struct net_device *netdev;
};

static inline struct rdmasim_device *to_rdmasim_dev(struct ib_device *ibdev)
{
	return container_of(ibdev, struct rdmasim_device, ibdev);
}

#endif
