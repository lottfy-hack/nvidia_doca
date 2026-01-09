/*
 * Copyright (c) 2022 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
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

#include <doca_dpa_dev.h>
#include <doca_dpa_dev_devemu_pci.h>

/*
 * RPC function for raising MSI-X interrupt towards Host
 *
 * @msix [in]: The MSI-X DPA handle passed from DPU
 * @return: RPC function always succeed and returns 0
 */
__dpa_rpc__ uint64_t raise_msix_rpc(doca_dpa_dev_devemu_pci_msix_t msix)
{
	doca_dpa_dev_devemu_pci_msix_raise(msix);

	return 0;
}
