/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
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

#ifndef UROM_RDMO_CORE_H_
#define UROM_RDMO_CORE_H_

#include <doca_log.h>
#include <doca_error.h>
#include <limits.h>

#include <doca_urom.h>

#include "urom_common.h"

/* RDMO applications modes */
enum rdmo_mode {
	RDMO_MODE_UNKOWN, /* RDMO unkown mode */
	RDMO_MODE_SERVER, /* RDMO server mode */
	RDMO_MODE_CLIENT  /* RDMO client mode */
};

/* RDMO configuration structure */
struct rdmo_cfg {
	struct urom_common_cfg common;	 /* UROM common configuration file */
	enum rdmo_mode mode;		 /* Node running mode {server, client} */
	char server_name[HOST_NAME_MAX]; /* Server name */
};

/*
 * RDMO server main function
 *
 * @device_name [in]: UROM device name
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rdmo_server(char *device_name);

/*
 * RDMO client main function
 *
 * @server_name [in]: RDMO server name
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rdmo_client(char *server_name);

/*
 * Register RDMO application arguments
 *
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t register_urom_rdmo_params(void);

#endif /* UROM_RDMO_CORE_H_ */
