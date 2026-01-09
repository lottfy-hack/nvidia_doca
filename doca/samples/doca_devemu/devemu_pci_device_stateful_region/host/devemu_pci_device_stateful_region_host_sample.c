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

#include <errno.h>
#include <linux/vfio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

#include <common.h>
#include <doca_error.h>
#include <doca_log.h>

#include <devemu_pci_host_common.h>
#include <devemu_pci_type_config.h>

DOCA_LOG_REGISTER(DEVEMU_PCI_DEVICE_STATEFUL_REGION_HOST);

/*
 * Run DOCA Device Emulation Stateful Region Host sample
 *
 * @pci_address [in]: Emulated device PCI address
 * @vfio_group [in]: VFIO group ID
 * @region_index [in]: The index of the stateful region
 * @write_data [in]: The data to write to stateful region
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t devemu_pci_device_stateful_region_host(const char *pci_address,
						    int vfio_group,
						    int region_index,
						    const char *write_data)
{
	doca_error_t result;
	struct devemu_host_resources resources = {0};

	resources.container_fd = -1;
	resources.group_fd = -1;
	resources.device_fd = -1;

	if (PCI_TYPE_NUM_BAR_STATEFUL_REGIONS == 0) {
		DOCA_LOG_ERR(
			"No stateful region was configured for type. Please configure at least 1 stateful region to run this sample");
		return DOCA_ERROR_INVALID_VALUE;
	}

	const struct bar_region_config *stateful_config = &stateful_configs[region_index];
	size_t data_len = strnlen(write_data, PCI_TYPE_MAX_STATEFUL_REGION_SIZE);
	if (data_len > stateful_configs->size) {
		DOCA_LOG_ERR("Write data size of %zuB excceeds region size of %luB", data_len, stateful_configs->size);
		return DOCA_ERROR_INVALID_VALUE;
	}

	result = init_vfio_device(&resources, vfio_group, pci_address);
	if (result != DOCA_SUCCESS) {
		devemu_host_resources_cleanup(&resources);
		return result;
	}

	result = map_bar_region_memory(&resources, stateful_config, &resources.stateful_region);
	if (result != DOCA_SUCCESS) {
		devemu_host_resources_cleanup(&resources);
		return result;
	}

	struct bar_mapped_region *stateful_region = &resources.stateful_region;
	if (data_len == 0) {
		// Read data
		char *dump = hex_dump(stateful_region->mem, stateful_config->size);
		DOCA_LOG_INFO("Reading stateful region at bar %u start address %zu size %zuB:\n%s",
			      stateful_config->bar_id,
			      stateful_config->start_address,
			      stateful_configs->size,
			      dump);
		free(dump);
	} else {
		// Write data
		DOCA_LOG_INFO("Writing to stateful region at bar %u start address %zu size %zuB:\n",
			      stateful_config->bar_id,
			      stateful_config->start_address,
			      data_len);
		memcpy(stateful_region->mem, write_data, data_len);
	}

	return DOCA_SUCCESS;
}
