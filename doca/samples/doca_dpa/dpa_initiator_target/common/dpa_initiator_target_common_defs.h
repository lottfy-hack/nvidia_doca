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

#ifndef DPA_INITIATOR_TARGET_COMMON_DEFS_H_
#define DPA_INITIATOR_TARGET_COMMON_DEFS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Target RDMA #1 user data
 */
#define TARGET_RDMA1_USER_DATA (111)

/**
 * @brief Target RDMA #2 user data
 */
#define TARGET_RDMA2_USER_DATA (222)

/**
 * @brief DPA thread #1 device argument struct
 */
struct dpa_thread1_arg {
	uint64_t notification_comp_handle;
	uint64_t dpa_comp_handle;
	uint64_t target_rdma1_handle;
	uint64_t local_buf1_addr;
	uint32_t dpa_mmap1_handle;
	uint64_t target_rdma2_handle;
	uint64_t local_buf2_addr;
	uint32_t dpa_mmap2_handle;
	size_t length;
} __attribute__((__packed__, aligned(8)));

/**
 * @brief DPA thread #2 device argument struct
 */
struct dpa_thread2_arg {
	uint64_t sync_event_handle;
	uint64_t completion_count;
} __attribute__((__packed__, aligned(8)));

#ifdef __cplusplus
}
#endif

#endif /* DPA_INITIATOR_TARGET_COMMON_DEFS_H_ */
