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

#ifndef WORKER_RDMO_H_
#define WORKER_RDMO_H_

#include <doca_log.h>
#include <doca_error.h>

#include <doca_urom.h>

#include "urom_rdmo.h"

/*
 * RDMO client init task callback function, will be called once the send task is finished
 *
 * @result [in]: task status
 * @cookie [in]: user cookie
 * @addr [in]: Device UCP worker address
 * @addr_len [in]: address length
 */
typedef void (*urom_rdmo_client_init_finished)(doca_error_t result,
					       union doca_data cookie,
					       void *addr,
					       uint64_t addr_len);

/*
 * RDMO receive queue create task callback function, will be called once the send task is finished
 *
 * @result [in]: task status
 * @cookie [in]: user cookie
 * @rq_id [in]: RQ id
 */
typedef void (*urom_rdmo_rq_create_finished)(doca_error_t result, union doca_data cookie, uint64_t rq_id);

/*
 * RDMO receive queue destroy task callback function, will be called once the send task is finished
 *
 * @result [in]: task status
 * @cookie [in]: user cookie
 * @rq_id [in]: destroyed RQ id
 */
typedef void (*urom_rdmo_rq_destroy_finished)(doca_error_t result, union doca_data cookie, uint64_t rq_id);

/*
 * RDMO memory region register task callback function, will be called once the send task is finished
 *
 * @result [in]: task status
 * @cookie [in]: user cookie
 * @rkey [in]: memory remote key
 */
typedef void (*urom_rdmo_mr_register_finished)(doca_error_t result, union doca_data cookie, uint64_t rkey);

/*
 * RDMO memory region deregister task callback function, will be called once the send task is finished
 *
 * @result [in]: task status
 * @cookie [in]: user cookie
 * @rkey [in]: deregistered memory remote key
 */
typedef void (*urom_rdmo_mr_deregister_finished)(doca_error_t result, union doca_data cookie, uint64_t rkey);

/*
 * Create client init RDMO task
 *
 * @worker_ctx [in]: DOCA UROM worker context
 * @cookie [in]: user cookie
 * @id [in]: id is used to identify client in requests
 * @addr [in]: local UCP worker address
 * @addr_len [in]: worker address length
 * @cb [in]: program callback to call once the task is finished
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_task_client_init(struct doca_urom_worker *worker_ctx,
					union doca_data cookie,
					uint64_t id,
					void *addr,
					uint64_t addr_len,
					urom_rdmo_client_init_finished cb);

/*
 * Create RDMO receive queue task
 *
 * @worker_ctx [in]: DOCA UROM worker context
 * @cookie [in]: user cookie
 * @addr [in]: peer UCP worker address
 * @addr_len [in]: worker address length
 * @cb [in]: program callback to call once the task is finished
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_task_rq_create(struct doca_urom_worker *worker_ctx,
				      union doca_data cookie,
				      void *addr,
				      uint64_t addr_len,
				      urom_rdmo_rq_create_finished cb);

/*
 * Create receive queue destroy RDMO task
 *
 * @worker_ctx [in]: DOCA UROM worker context
 * @cookie [in]: user cookie
 * @rq_id [in]: receive queue id, program receives it from RQ create notification
 * @cb [in]: program callback to call once the task is finished
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_task_rq_destroy(struct doca_urom_worker *worker_ctx,
				       union doca_data cookie,
				       uint64_t rq_id,
				       urom_rdmo_rq_destroy_finished cb);

/*
 * Create memory region register RDMO task
 *
 * @worker_ctx [in]: DOCA UROM worker context
 * @cookie [in]: user cookie
 * @va [in]: Host virtual address
 * @len [in]: address length
 * @rkey [in]: packed memory remote key
 * @rkey_len [in]: remote key length
 * @memh [in]: packed memory handle
 * @memh_len [in]: memory handle length
 * @cb [in]: program callback to call once the task is finished
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_task_mr_register(struct doca_urom_worker *worker_ctx,
					union doca_data cookie,
					uint64_t va,
					uint64_t len,
					void *rkey,
					uint64_t rkey_len,
					void *memh,
					uint64_t memh_len,
					urom_rdmo_mr_register_finished cb);

/*
 * Create memory region deregister RDMO task
 *
 * @worker_ctx [in]: DOCA UROM worker context
 * @cookie [in]: user cookie
 * @rkey_id [in]: remote key id, program receives it from MR register notification
 * @cb [in]: program callback to call once the task is finished
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_task_mr_deregister(struct doca_urom_worker *worker_ctx,
					  union doca_data cookie,
					  uint64_t rkey_id,
					  urom_rdmo_mr_deregister_finished cb);

/*
 * This method inits RDMO plugin.
 *
 * @plugin_id [in]: UROM plugin ID
 * @version [in]: plugin version on DPU side
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t urom_rdmo_init(uint64_t plugin_id, uint64_t version);

#endif /* WORKER_RDMO_H_ */
