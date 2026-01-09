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

if not flag_enable_grpc_support
	warning('Skipping compilation of DOCA Application - @0@ - Missing gRPC support.'.format(APP_NAME))
	subdir_done()
endif

grpc_cpp_args = base_cpp_args
subdir('grpc')

app_dependencies += dependency_psp_gateway_grpc
app_dependencies += grpc_dependencies

app_srcs = files([
	'psp_gw_flows.cpp',
	'psp_gw_params.cpp',
	'psp_gw_svc_impl.cpp',
	'psp_gw_pkt_rss.cpp',
	'psp_gw_utils.cpp',
	common_dir_path + '/dpdk_utils.c',
	samples_dir_path + '/common.c',
])

vanilla_app_srcs = [
	APP_NAME + '.cpp',
]

executable(DOCA_PREFIX + APP_NAME,
	app_srcs + vanilla_app_srcs,
	override_options: ['cpp_std=c++17'],
	c_args : base_c_args,
	cpp_args: base_cpp_args + grpc_cpp_args,
	dependencies : app_dependencies,
	include_directories : app_inc_dirs,
	install: install_apps)
