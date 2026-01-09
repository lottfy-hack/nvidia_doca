#
# Copyright (c) 2023-2024 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of NVIDIA CORPORATION &
# AFFILIATES (the "Company") and all right, title, and interest in and to the
# software product, including all associated intellectual property rights, are
# and shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

project('urom_sandbox_worker_plugin',
	'C', 'CPP',
	license: 'Proprietary',
	default_options: ['buildtype=debug'],
	meson_version: '>= 0.61.2'
)

PLUGIN_NAME = 'worker_sandbox'
lib_prefix = ''
# Comment this line to restore warnings of experimental DOCA features
add_project_arguments('-D DOCA_ALLOW_EXPERIMENTAL_API', language: ['c', 'cpp'])

languages = ['c', 'cpp']

plugin_dependencies = []
# Required for all DOCA programs
plugin_dependencies += dependency('doca-common')
# The DOCA library of the sample itself
plugin_dependencies += dependency('doca-urom')
# Required DOCA Driver
plugin_dependencies += dependency('ucx')

plugin_srcs = [
	PLUGIN_NAME + '.c',
]

plugin_inc_dirs  = []

sandbox_plugin = shared_library(PLUGIN_NAME, plugin_srcs,
	name_prefix: lib_prefix,
	dependencies : plugin_dependencies,
	install: false)
