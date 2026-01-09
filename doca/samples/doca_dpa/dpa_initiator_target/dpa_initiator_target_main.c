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

#include "dpa_common.h"

DOCA_LOG_REGISTER(DPA_INITIATOR_TARGET::MAIN);

/**
 * @brief Sample's logic
 */
doca_error_t dpa_initiator_target(struct dpa_resources *resources);

/**
 * @brief Sample's main function
 *
 * @argc [in]: sample arguments length
 * @argv [in]: sample arguments
 * @return: EXIT_SUCCESS on success and EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{
	struct dpa_config cfg = {{0}};
	struct dpa_resources resources = {0};
	doca_error_t result = DOCA_SUCCESS;
	struct doca_log_backend *sdk_log = NULL;
	int exit_status = EXIT_FAILURE;

	strcpy(cfg.device_name, DEVICE_DEFAULT_NAME);

	result = doca_log_backend_create_standard();
	if (result != DOCA_SUCCESS)
		goto sample_exit;

	result = doca_log_backend_create_with_file_sdk(stderr, &sdk_log);
	if (result != DOCA_SUCCESS)
		goto sample_exit;
	result = doca_log_backend_set_sdk_level(sdk_log, DOCA_LOG_LEVEL_WARNING);
	if (result != DOCA_SUCCESS)
		goto sample_exit;

	DOCA_LOG_INFO("Starting the sample");

	result = doca_argp_init("dpa_initiator_target", &cfg);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to init ARGP resources: %s", doca_error_get_descr(result));
		goto sample_exit;
	}

	result = register_dpa_params();
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to register sample parameters: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}

	result = doca_argp_start(argc, argv);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to parse sample input: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}

	result = allocate_dpa_resources(&cfg, &resources);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to Allocate DPA Resources: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}

	result = dpa_initiator_target(&resources);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("dpa_initiator_target() encountered an error: %s", doca_error_get_descr(result));
		goto dpa_cleanup;
	}

	exit_status = EXIT_SUCCESS;

dpa_cleanup:
	result = destroy_dpa_resources(&resources);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to destroy DOCA DPA resources: %s", doca_error_get_descr(result));
		exit_status = EXIT_FAILURE;
	}

argp_cleanup:
	doca_argp_destroy();

sample_exit:
	if (exit_status == EXIT_SUCCESS)
		DOCA_LOG_INFO("Sample finished successfully");
	else
		DOCA_LOG_INFO("Sample finished with errors");
	return exit_status;
}
