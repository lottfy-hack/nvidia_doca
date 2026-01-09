/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
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

#ifndef ETH_RXQ_COMMON_H_
#define ETH_RXQ_COMMON_H_

#include <unistd.h>

#include <doca_flow.h>
#include <doca_dev.h>
#include <doca_error.h>

struct eth_rxq_flow_resources {
	struct doca_flow_port *df_port;		 /* DOCA flow port */
	struct doca_flow_pipe *root_pipe;	 /* DOCA flow root pipe*/
	struct doca_flow_pipe_entry *root_entry; /* DOCA flow root pipe entry*/
};

struct eth_rxq_flow_config {
	struct doca_dev *dev;	    /* DOCA device */
	uint16_t rxq_flow_queue_id; /* DOCA ETH RXQ's flow queue ID */
};

/*
 * Initializes DOCA flow for ETH RXQ sample
 *
 * @dev [in]: Doca device to use for doca_flow_port
 * @resources [in]: flow resources
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rxq_common_init_doca_flow(struct doca_dev *dev, struct eth_rxq_flow_resources *resources);

/*
 * Allocate DOCA flow resources for ETH RXQ sample
 *
 * @cfg [in]: Configuration parameters
 * @resources [out]: DOCA flow resources for ETH RXQ sample to allocate
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t allocate_eth_rxq_flow_resources(struct eth_rxq_flow_config *cfg, struct eth_rxq_flow_resources *resources);

/*
 * Destroy DOCA flow resources for ETH RXQ sample
 *
 * @resources [in]: DOCA flow resources for ETH RXQ sample to destroy
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t destroy_eth_rxq_flow_resources(struct eth_rxq_flow_resources *resources);

#endif /* ETH_RXQ_COMMON_H_ */
