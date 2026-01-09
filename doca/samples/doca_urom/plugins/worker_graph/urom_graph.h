/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION &
 * AFFILIATES (the "Company") and all right, title, and interest in and to the
 * software product, including all associated intellectual property rights, are
 * and shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#ifndef UROM_GRAPH_H_
#define UROM_GRAPH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Graph command types */
enum urom_worker_graph_cmd_type {
	UROM_WORKER_CMD_GRAPH_LOOPBACK, /* Graph loopback command */
};

/* Graph loopback command structure */
struct urom_worker_graph_cmd_loopback {
	uint64_t data; /* Loopback data */
};

/* UROM Graph worker command structure */
struct urom_worker_graph_cmd {
	uint64_t type; /* Type of command as defined urom_worker_graph_cmd_loopback */
	union {
		struct urom_worker_graph_cmd_loopback loopback; /* Loopback command */
	};
};

/* Graph notification types */
enum urom_worker_graph_notify_type {
	UROM_WORKER_NOTIFY_GRAPH_LOOPBACK, /* Graph loopback notification */
};

/* Graph loopback notification structure */
struct urom_worker_graph_notify_loopback {
	uint64_t data; /* Loopback data */
};

/* UROM Graph worker notification structure */

struct urom_worker_notify_graph {
	uint64_t type; /* Notify type as defined by urom_worker_graph_notify_type */
	union {
		struct urom_worker_graph_notify_loopback loopback; /* Loopback notification */
	};
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
