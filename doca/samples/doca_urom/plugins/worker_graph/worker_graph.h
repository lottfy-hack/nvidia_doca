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

#ifndef WORKER_GRAPH_H_
#define WORKER_GRAPH_H_

#include <ucp/api/ucp.h>
#include <ucs/datastruct/khash.h>
#include <ucs/datastruct/list.h>

#include <doca_error.h>
#include <doca_urom_plugin.h>

/* UROM graph worker interface */
struct urom_worker_graph_iface {
	struct urom_plugin_iface super; /* DOCA UROM worker plugin interface */
};

/* Graph UCP data structure */
struct urom_worker_graph_ucp_data {
	ucp_context_h ucp_context;     /* UCP context */
	ucp_worker_h ucp_worker;       /* UCP worker instance */
	ucp_address_t *worker_address; /* UCP worker address */
	size_t ucp_addrlen;	       /* UCP worker address length */
};

/* UROM worker graph context */
struct urom_worker_graph {
	struct urom_worker_graph_ucp_data ucp_data; /* Graph UCP data */
	ucs_list_link_t completed_reqs;		    /* Graph worker commands completion list */
};

/*
 * Get DOCA worker plugin interface for graph plugin, DOCA UROM worker will load the urom_plugin_get_iface symbol
 * to get the graph interface
 *
 * @iface [out]: Set DOCA UROM plugin interface for graph
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_plugin_get_iface(struct urom_plugin_iface *iface);

/*
 * Get graph plugin version, will be used to verify that the host and DPU plugin versions are compatible
 *
 * @version [out]: Set the graph worker plugin version
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_plugin_get_version(uint64_t *version);

#endif /* WORKER_GRAPH_H_ */
