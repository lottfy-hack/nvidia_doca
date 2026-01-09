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

#ifndef FLOW_ENCRYPT_H_
#define FLOW_ENCRYPT_H_

#include <rte_hash.h>

#include "flow_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Add encryption entry to the encrypt pipes:
 * - 5 tuple rule in the TCP / UDP pipe with specific set meta data value (shared obj ID)
 * - specific meta data match on encryption pipe (shared obj ID) with shared object ID in actions
 *
 * @rule [in]: rule to insert for encryption
 * @rule_id [in]: rule id for shared obj ID
 * @ports [in]: array of ports
 * @app_cfg [in]: application configuration struct
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t add_encrypt_entry(struct encrypt_rule *rule,
			       int rule_id,
			       struct ipsec_security_gw_ports_map **ports,
			       struct ipsec_security_gw_config *app_cfg);

/*
 * Add encryption entries to the encrypt pipes:
 * - 5 tuple rule in the TCP / UDP pipe with specific set meta data value (shared obj ID)
 * - specific meta data match on encryption pipe (shared obj ID) with shared object ID in actions
 *
 * @app_cfg [in]: application configuration struct
 * @ports [in]: ports map
 * @queue_id [in]: queue id
 * @nb_rules [in]: number of encryption rules
 * @rule_offset [in]: offset of the rule in the rules array
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t add_encrypt_entries(struct ipsec_security_gw_config *app_cfg,
				 struct ipsec_security_gw_ports_map *ports[],
				 uint16_t queue_id,
				 int nb_rules,
				 int rule_offset);

/*
 * Create encrypt pipe and entries according to the parsed rules
 *
 * @ports [in]: array of struct ipsec_security_gw_ports_map
 * @app_cfg [in]: application configuration structure
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t ipsec_security_gw_insert_encrypt_rules(struct ipsec_security_gw_ports_map *ports[],
						    struct ipsec_security_gw_config *app_cfg);

/*
 * Create encrypt egress pipes
 *
 * @ports [in]: array of struct ipsec_security_gw_ports_map
 * @app_cfg [in]: application configuration structure
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t ipsec_security_gw_create_encrypt_egress(struct ipsec_security_gw_ports_map *ports[],
						     struct ipsec_security_gw_config *app_cfg);

/*
 * Handling the new received packet - print packet source IP and send them to tx queues of second port
 *
 * @packet [in]: packet to parse
 * @ctx [in]: core context struct
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t handle_unsecured_packets_received(struct rte_mbuf **packet, struct ipsec_security_gw_core_ctx *ctx);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FLOW_ENCRYPT_H_ */
