// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020-2021 Kamal Heib <kamalheib1@gmail.com>
 */

#ifndef _VERBS_H
#define _VERBS_H

int rdmasim_query_device(struct ib_device *device,
			 struct ib_device_attr *device_attr,
			 struct ib_udata *udata);

int rdmasim_get_port_immutable(struct ib_device *device, u32 port_num,
			       struct ib_port_immutable *immutable);

int rdmasim_query_port(struct ib_device *device, u32 port_num,
		       struct ib_port_attr *port_attr);

void rdmasim_dealloc_driver(struct ib_device *dev);

#endif
