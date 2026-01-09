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

#include <doca_dpa_dev.h>
#include <doca_dpa_dev_rdma.h>
#include <doca_dpa_dev_buf.h>
#include "../common/dpa_basic_initiator_target_common_defs.h"

/**
 * @brief Kernel function for DPA thread
 *
 * This kernel is triggered when a completion is received on attached RDMA context.
 * This kernel is triggered once when it receives data on DPA buffer with value 10.
 * On completion, it gets and dumps completion info.
 * This kernel sets host completion sync event with the received data value to let host application
 * start destroying all resources and finishing the application
 *
 * @arg [in]: Kernel argument
 */
__dpa_global__ void thread_kernel(uint64_t arg)
{
	DOCA_DPA_DEV_LOG_INFO("%s: Hello from Thread\n", __func__);

	struct dpa_thread_arg *thread_arg = (struct dpa_thread_arg *)arg;

	DOCA_DPA_DEV_LOG_INFO("%s: Read completion info\n", __func__);
	doca_dpa_dev_completion_element_t comp_element;
	int found = doca_dpa_dev_get_completion(thread_arg->dpa_comp_handle, &comp_element);
	DOCA_DPA_DEV_LOG_INFO("%s: doca_dpa_dev_get_completion() returned %d\n", __func__, found);

	if (found) {
		DOCA_DPA_DEV_LOG_INFO("%s: doca_dpa_dev_get_completion_type() returned %d\n",
				      __func__,
				      doca_dpa_dev_get_completion_type(comp_element));
		DOCA_DPA_DEV_LOG_INFO("%s: doca_dpa_dev_get_completion_user_data() returned %u\n",
				      __func__,
				      doca_dpa_dev_get_completion_user_data(comp_element));

		DOCA_DPA_DEV_LOG_INFO("%s: Value of DPA received buffer is %lu\n",
				      __func__,
				      *((uint64_t *)(thread_arg->local_buf_addr)));
	}

	DOCA_DPA_DEV_LOG_INFO("%s: Set sync event to %lu\n", __func__, *((uint64_t *)(thread_arg->local_buf_addr)));
	doca_dpa_dev_sync_event_update_set(thread_arg->sync_event_handle, *((uint64_t *)(thread_arg->local_buf_addr)));

	DOCA_DPA_DEV_LOG_INFO("%s: Finish\n", __func__);
	doca_dpa_dev_thread_finish();
}

/**
 * @brief RPC function to post RDMA receive operation
 *
 * This RPC is used by target host application to post RDMA receive operation on DPA local buffer
 *
 * @rdma [in]: RDMA DPA handle
 * @local_buf_addr [in]: address of received buffer
 * @dpa_mmap_handle [in]: received DOCA Mmap handle
 * @length [in]: length of received buffer
 * @return: RPC function always succeed and returns 0
 */
__dpa_rpc__ uint64_t rdma_post_receive_rpc(doca_dpa_dev_rdma_t rdma,
					   doca_dpa_dev_uintptr_t local_buf_addr,
					   doca_dpa_dev_mmap_t dpa_mmap_handle,
					   size_t length)
{
	DOCA_DPA_DEV_LOG_INFO("%s: Post RDMA receive on DPA Mmap handle %u, address 0x%lx, length %lu\n",
			      __func__,
			      dpa_mmap_handle,
			      local_buf_addr,
			      length);
	doca_dpa_dev_rdma_post_receive(rdma, dpa_mmap_handle, local_buf_addr, length);

	return 0;
}

/**
 * @brief RPC function to post RDMA send operation
 *
 * This RPC is used by initiator host application to post RDMA send operation on host local buffer
 *
 * @rdma [in]: RDMA DPA handle
 * @local_buf_addr [in]: address of send buffer
 * @dpa_mmap_handle [in]: send DOCA Mmap handle
 * @length [in]: length of send buffer
 * @return: RPC function always succeed and returns 0
 */
__dpa_rpc__ uint64_t rdma_post_send_rpc(doca_dpa_dev_rdma_t rdma,
					uintptr_t local_buf_addr,
					doca_dpa_dev_mmap_t dpa_mmap_handle,
					size_t length)
{
	DOCA_DPA_DEV_LOG_INFO("%s: Post RDMA send on DPA Mmap handle %u, address 0x%lx, length %lu\n",
			      __func__,
			      dpa_mmap_handle,
			      local_buf_addr,
			      length);
	doca_dpa_dev_rdma_post_send(rdma, dpa_mmap_handle, local_buf_addr, length, 0);

	return 0;
}
