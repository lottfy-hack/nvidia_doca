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

#ifndef WORKER_SANDBOX_H_
#define WORKER_SANDBOX_H_

#include <ucp/api/ucp.h>
#include <ucs/datastruct/khash.h>
#include <ucs/datastruct/list.h>

#include <doca_error.h>
#include <doca_urom_plugin.h>

/* UROM worker sandbox context */
struct urom_worker_sandbox;

/* UROM sandbox worker interface */
struct urom_worker_sandbox_iface {
	struct urom_plugin_iface super; /* DOCA UROM worker plugin interface */
};

/* Sandbox command request structure */
struct urom_worker_sandbox_request {
	ucs_list_link_t entry;			    /* UCX list entry */
	struct urom_worker_sandbox *sandbox_worker; /* Worker sandbox context */
	struct urom_worker_notif_desc *notif_desc;  /* Worker sandbox notification descriptor */
	int inline_data;			    /* If notification contains inline data */
};

/* Init endpoints UCX map */
KHASH_MAP_INIT_INT64(ep, ucp_ep_h);

/* Sandbox UCP data structure */
struct urom_worker_sandbox_ucp_data {
	ucp_context_h ucp_context;     /* UCP context */
	ucp_worker_h ucp_worker;       /* UCP worker instance */
	ucp_address_t *worker_address; /* UCP worker address */
	size_t ucp_addrlen;	       /* UCP worker address length */
	khash_t(ep) * eps;	       /* Worker endpoints map */
};

/* UROM worker sandbox context */
struct urom_worker_sandbox {
	struct urom_worker_sandbox_ucp_data ucp_data; /* Sandbox UCP data */
	ucs_list_link_t completed_reqs;		      /* Sandbox worker commands completion list */
};

/*
 * Get DOCA worker plugin interface for sandbox plugin, DOCA UROM worker will load the urom_plugin_get_iface symbol
 * to get the sandbox interface
 *
 * @iface [out]: Set DOCA UROM plugin interface for sandbox
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_plugin_get_iface(struct urom_plugin_iface *iface);

/*
 * Get sandbox plugin version, will be used to verify that the host and DPU plugin versions are compatible
 *
 * @version [out]: Set the sandbox worker plugin version
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_plugin_get_version(uint64_t *version);

#endif /* WORKER_SANDBOX_H_ */
