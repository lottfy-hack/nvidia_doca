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

#ifndef FLOW_DECRYPT_H_
#define FLOW_DECRYPT_H_

#include "flow_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Add decryption entries to the decrypt pipe
 *
 * @app_cfg [in]: application configuration struct
 * @port [in]: port of the entries
 * @queue_id [in]: queue id to insert the entries
 * @nb_rules [in]: number of rules to insert
 * @rule_offset [in]: offset of the rules in the rules array
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t add_decrypt_entries(struct ipsec_security_gw_config *app_cfg,
				 struct ipsec_security_gw_ports_map *port,
				 uint16_t queue_id,
				 int nb_rules,
				 int rule_offset);

/*
 * Add decryption entry to the decrypt pipe
 *
 * @rule [in]: rule to insert for decryption
 * @rule_id [in]: rule id for crypto shared index
 * @port [in]: port of the entries
 * @app_cfg [in]: application configuration struct
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t add_decrypt_entry(struct decrypt_rule *rule,
			       int rule_id,
			       struct doca_flow_port *port,
			       struct ipsec_security_gw_config *app_cfg);

/*
 * Create decrypt pipe and entries according to the parsed rules
 *
 * @port [in]: secured network port pointer
 * @app_cfg [in]: application configuration structure
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t ipsec_security_gw_insert_decrypt_rules(struct ipsec_security_gw_ports_map *port,
						    struct ipsec_security_gw_config *app_cfg);

/*
 * Handling the new received packets - decap packet and send them to tx queues of second port
 *
 * @packet [in]: packet to process
 * @bad_syndrome_check [in]: true if need to check bad syndrome in packet meta
 * @ctx [in]: core context struct
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t handle_secured_packets_received(struct rte_mbuf **packet,
					     bool bad_syndrome_check,
					     struct ipsec_security_gw_core_ctx *ctx);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FLOW_DECRYPT_H_ */
