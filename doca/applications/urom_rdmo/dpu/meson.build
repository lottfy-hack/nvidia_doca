#
# Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of NVIDIA CORPORATION &
# AFFILIATES (the "Company") and all right, title, and interest in and to the
# software product, including all associated intellectual property rights, are
# and shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

PLUGIN_NAME = 'worker_rdmo'
lib_prefix = ''

app_srcs += files([
	'worker_rdmo.c',
	'worker_rdmo_ops.c',
])

rdmo_plugin = shared_library(PLUGIN_NAME, app_srcs + app_common_src,
	name_prefix: lib_prefix,
	dependencies : app_dependencies,
	include_directories: app_inc_dirs + app_common_includes,
	install: install_apps)
