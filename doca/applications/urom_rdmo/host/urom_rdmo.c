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

#include <stdint.h>
#include <stdlib.h>

#include <doca_argp.h>

#include "urom_rdmo_core.h"

DOCA_LOG_REGISTER(UROM::RDMO);

/*
 * UROM RDMO application main function
 *
 * @argc [in]: command line arguments size
 * @argv [in]: array of command line arguments
 * @return: EXIT_SUCCESS on success and EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{
	doca_error_t result;
	struct rdmo_cfg rdmo_cfg = {0};
	struct doca_log_backend *sdk_log;
	int exit_status = EXIT_FAILURE;

	/* Register a logger backend */
	result = doca_log_backend_create_standard();
	if (result != DOCA_SUCCESS)
		goto app_exit;

	/* Register a logger backend for internal SDK errors and warnings */
	result = doca_log_backend_create_with_file_sdk(stderr, &sdk_log);
	if (result != DOCA_SUCCESS)
		goto app_exit;

	result = doca_log_backend_set_sdk_level(sdk_log, DOCA_LOG_LEVEL_WARNING);
	if (result != DOCA_SUCCESS)
		goto app_exit;

	result = doca_argp_init("doca_urom_rdmo", &rdmo_cfg.common);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to init ARGP resources: %s", doca_error_get_descr(result));
		goto app_exit;
	}

	result = register_urom_rdmo_params();
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to register RDMO parameters: %s", doca_error_get_descr(result));
		goto destroy_argp;
	}

	result = doca_argp_start(argc, argv);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to parse application input: %s", doca_error_get_descr(result));
		goto destroy_argp;
	}

	if (rdmo_cfg.mode == RDMO_MODE_SERVER)
		result = rdmo_server(rdmo_cfg.common.device_name);
	else if (rdmo_cfg.mode == RDMO_MODE_CLIENT)
		result = rdmo_client(rdmo_cfg.server_name);
	else
		result = DOCA_ERROR_BAD_STATE;

	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to start RDMO operations flow");
		goto destroy_argp;
	}

	exit_status = EXIT_SUCCESS;

destroy_argp:
	doca_argp_destroy();
app_exit:
	return exit_status;
}
