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

#ifndef DPA_BASIC_INITIATOR_TARGET_COMMON_DEFS_H_
#define DPA_BASIC_INITIATOR_TARGET_COMMON_DEFS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DPA thread device argument struct
 */
struct dpa_thread_arg {
	uint64_t dpa_comp_handle;
	uint64_t local_buf_addr;
	uint64_t sync_event_handle;
} __attribute__((__packed__, aligned(8)));

#ifdef __cplusplus
}
#endif

#endif /* DPA_BASIC_INITIATOR_TARGET_COMMON_DEFS_H_ */
