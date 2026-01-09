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

#ifndef DEVEMU_PCI_TYPE_CONFIG_H_
#define DEVEMU_PCI_TYPE_CONFIG_H_

#include <doca_devemu_pci_type.h>

#define PCI_TYPE_NAME "Sample PCI Type"

#define PCI_TYPE_DEVICE_ID 0x1021
#define PCI_TYPE_VENDOR_ID 0x15b3
#define PCI_TYPE_SUBSYSTEM_ID 0x0051
#define PCI_TYPE_SUBSYSTEM_VENDOR_ID 0x15b3
#define PCI_TYPE_REVISION_ID 0
#define PCI_TYPE_CLASS_CODE 0x020000

struct bar_memory_layout_config {
	uint8_t bar_id;				       /**< The BAR ID that this layout describes */
	uint16_t log_size;			       /**< The log size of the BAR */
	enum doca_devemu_pci_bar_mem_type memory_type; /**< The memory type of the BAR */
	uint8_t prefetchable;			       /**< Whether the BAR memory is prefetchable */
};

struct bar_region_config {
	uint8_t bar_id;		/**< The BAR ID that the region is part of */
	uint64_t start_address; /**< The start address of the region within the BAR */
	uint64_t size;		/**< The size of the region in bytes */
};

struct bar_db_region_config {
	struct bar_region_config region; /**< Holds common BAR region configuration */
	uint8_t log_db_size;		 /**< The log size of a single doorbell record */
	uint8_t log_db_stride_size;	 /**< The log stride size of a single doorbell record */
	bool with_data;			 /**< If true the doorbell will work by data. Otherwise by offset */
	uint16_t db_id_msbyte;		 /**< Relevant only when with_data is true */
	uint16_t db_id_lsbyte;		 /**< Relevant only when with_data is true */
};

/* Configure how many BARs exist, and what they look like */
#define PCI_TYPE_NUM_BAR_MEMORY_LAYOUT 2

static const struct bar_memory_layout_config layout_configs[PCI_TYPE_NUM_BAR_MEMORY_LAYOUT] = {
	[0] =
		{
			.bar_id = 0,
			.log_size = 0xe,
			.memory_type = DOCA_DEVEMU_PCI_BAR_MEM_TYPE_64_BIT,
			.prefetchable = 1,
		},
	[1] =
		{
			.bar_id = 1,
			.log_size = 0x0,
			.memory_type = DOCA_DEVEMU_PCI_BAR_MEM_TYPE_64_BIT,
			.prefetchable = 0,
		},
};

/* Configure how many MSI-X vectors there are, and where they are placed in the BAR */
#define PCI_TYPE_NUM_MSIX 4
#define PCI_TYPE_NUM_BAR_MSIX_TABLE_REGIONS 1
#define PCI_TYPE_NUM_BAR_MSIX_PBA_REGIONS 1

static const struct bar_region_config msix_table_configs[PCI_TYPE_NUM_BAR_MSIX_TABLE_REGIONS] = {
	[0] =
		{
			.bar_id = 0,
			.start_address = 0x1000,
			.size = 0x1000,
		},
};

static const struct bar_region_config msix_pba_configs[PCI_TYPE_NUM_BAR_MSIX_PBA_REGIONS] = {
	[0] =
		{
			.bar_id = 0,
			.start_address = 0x2000,
			.size = 0x1000,
		},
};

/* Configure number of doorbells and regions and how they operate */
#define PCI_TYPE_NUM_BAR_DB_REGIONS 1

static const struct bar_db_region_config db_configs[PCI_TYPE_NUM_BAR_DB_REGIONS] = {
	[0] =
		{
			.region.bar_id = 0,
			.region.start_address = 0x0,
			.region.size = 0x1000,
			.log_db_size = 0x2,
			.log_db_stride_size = 0x2,
			.with_data = false,
		},
};

/* Configure number of stateful regions and their ranges */
#define PCI_TYPE_NUM_BAR_STATEFUL_REGIONS 1
#define PCI_TYPE_MAX_STATEFUL_REGION_SIZE 2048

static const struct bar_region_config stateful_configs[PCI_TYPE_NUM_BAR_STATEFUL_REGIONS] = {
	[0] =
		{
			.bar_id = 0,
			.start_address = 0x3000,
			.size = 0x100,
		},
};

#endif // DEVEMU_PCI_TYPE_CONFIG_H_
