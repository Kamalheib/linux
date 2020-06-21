// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020 Kamal Heib <kamalheib1@gmail.com>
 */

#ifndef _VERBS_H
#define _VERBS_H


int rdmasim_get_port_immutable(struct ib_device *device, u8 port_num,
			       struct ib_port_immutable *immutable);

#endif
