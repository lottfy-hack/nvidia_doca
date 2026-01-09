/*
 * Copyright (c) 2023-2024 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
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

#include <stdlib.h>
#include <string.h>

#include <doca_argp.h>
#include <doca_error.h>
#include <doca_dev.h>
#include <doca_log.h>

#include <devemu_pci_common.h>

DOCA_LOG_REGISTER(DPU_DEVEMU_PCI_DEVICE_HOTPLUG::MAIN);

/* Sample's Logic */
doca_error_t devemu_pci_device_hotplug(const char *pci_address, const char *unplug_vuid);

/* Configuration struct */
struct devemu_pci_cfg {
	char pci_address[DOCA_DEVINFO_PCI_ADDR_SIZE]; /* device PCI address */
	char vuid[DOCA_DEVINFO_REP_VUID_SIZE];	      /* VUID of emulated device to unplug */
};

/*
 * ARGP Callback - Handle PCI device address parameter
 *
 * @param [in]: Input parameter
 * @config [in/out]: Program configuration context
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
static doca_error_t pci_callback(void *param, void *config)
{
	struct devemu_pci_cfg *conf = (struct devemu_pci_cfg *)config;
	const char *addr = (char *)param;

	return parse_pci_address(addr, conf->pci_address);
}

/*
 * ARGP Callback - Handle VUID parameter
 *
 * @param [in]: Input parameter
 * @config [in/out]: Program configuration context
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
static doca_error_t vuid_callback(void *param, void *config)
{
	struct devemu_pci_cfg *conf = (struct devemu_pci_cfg *)config;
	const char *vuid = (char *)param;

	return parse_vuid(vuid, conf->vuid);
}

/*
 * Register the command line parameters for the sample
 *
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
static doca_error_t register_devemu_pci_params(void)
{
	doca_error_t result;

	result = register_pci_address_param(pci_callback);
	if (result != DOCA_SUCCESS)
		return result;

	result = register_vuid_param(
		"DOCA Devemu emulated device VUID. If provided then the given device will be hotunplugged",
		vuid_callback);
	if (result != DOCA_SUCCESS)
		return result;

	return DOCA_SUCCESS;
}

/*
 * Sample main function
 *
 * @argc [in]: command line arguments size
 * @argv [in]: array of command line arguments
 * @return: EXIT_SUCCESS on success and EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{
	struct devemu_pci_cfg devemu_pci_cfg;
	char *vuid = NULL;
	doca_error_t result;
	struct doca_log_backend *sdk_log;
	int exit_status = EXIT_FAILURE;

	/* Set the default configuration values (Example values) */
	strcpy(devemu_pci_cfg.pci_address, "0000:03:00.0");
	strcpy(devemu_pci_cfg.vuid, "");

	/* Register a logger backend */
	result = doca_log_backend_create_standard();
	if (result != DOCA_SUCCESS)
		goto sample_exit;

	/* Register a logger backend for internal SDK errors and warnings */
	result = doca_log_backend_create_with_file_sdk(stderr, &sdk_log);
	if (result != DOCA_SUCCESS)
		goto sample_exit;
	result = doca_log_backend_set_sdk_level(sdk_log, DOCA_LOG_LEVEL_WARNING);
	if (result != DOCA_SUCCESS)
		goto sample_exit;

	DOCA_LOG_INFO("Starting the sample");

	result = doca_argp_init("doca_devemu_pci_device_hotplug", &devemu_pci_cfg);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to init ARGP resources: %s", doca_error_get_descr(result));
		goto sample_exit;
	}
	result = register_devemu_pci_params();
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to register sample command line parameters: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}
	result = doca_argp_start(argc, argv);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("Failed to parse sample input: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}

#ifdef DOCA_ARCH_DPU

	if (*devemu_pci_cfg.vuid != 0)
		vuid = devemu_pci_cfg.vuid;

	result = devemu_pci_device_hotplug(devemu_pci_cfg.pci_address, vuid);
	if (result != DOCA_SUCCESS) {
		DOCA_LOG_ERR("devemu_pci_device_hotplug() encountered an error: %s", doca_error_get_descr(result));
		goto argp_cleanup;
	}

	exit_status = EXIT_SUCCESS;

#else // DOCA_ARCH_DPU

	(void)vuid;
	DOCA_LOG_ERR("Hotplug PCI Emulated Device can run only on the DPU");
	exit_status = EXIT_FAILURE;

#endif // DOCA_ARCH_DPU

argp_cleanup:
	doca_argp_destroy();

sample_exit:
	if (exit_status == EXIT_SUCCESS)
		DOCA_LOG_INFO("Sample finished successfully");
	else
		DOCA_LOG_INFO("Sample finished with errors");
	return exit_status;
}
