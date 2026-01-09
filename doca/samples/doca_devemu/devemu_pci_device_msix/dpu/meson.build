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

project('DOCA_SAMPLE', 'C', 'CPP',
	# Get version number from file.
	version: run_command(find_program('cat'),
		files('/opt/mellanox/doca/applications/VERSION'), check: true).stdout().strip(),
	license: 'Proprietary',
	default_options: ['buildtype=debug'],
	meson_version: '>= 0.61.2'
)

SAMPLE_NAME = 'devemu_pci_device_msix'
sample_program_name = SAMPLE_NAME + '_program'

# Comment this line to restore warnings of experimental DOCA features
add_project_arguments('-D DOCA_ALLOW_EXPERIMENTAL_API', language: ['c', 'cpp'])

sample_dependencies = []
# Required for all DOCA programs
sample_dependencies += dependency('doca-common')
# The DOCA library of the sample itself
sample_dependencies += dependency('doca-devemu')
# Utility DOCA library for executables
sample_dependencies += dependency('doca-argp')
# FlexIO definitions - Required by DPACC
sample_dependencies += dependency('libflexio')
# Required for running DPA
dependency_dpa = dependency('doca-dpa')
sample_dependencies += dependency_dpa

sample_srcs = [
	# The sample itself
	'host/' + SAMPLE_NAME + '_dpu_sample.c',
	# Main function for the sample's executable
	SAMPLE_NAME + '_dpu_main.c',
	# Common code for the DOCA library samples
	'../../devemu_pci_common.c',
	# Common code for all DOCA samples
	'../../../common.c',
]

sample_inc_dirs  = []
# Common DOCA library logic
sample_inc_dirs += include_directories('../..')
# Common DOCA logic (samples)
sample_inc_dirs += include_directories('../../..')
# Common DOCA logic
sample_inc_dirs += include_directories('../../../..')
# Common DOCA logic (applications)
sample_inc_dirs += include_directories('../../../../applications/common/')

# DPA compiler build script
dpacc_build_script_name = 'build_dpacc_samples.sh'
dpacc_build_script = meson.current_source_dir() + '/../../' + dpacc_build_script_name
# Sample device source code absolute path to be compiled by the DPACC
sample_device_src = meson.project_source_root() + '/device/' +  SAMPLE_NAME + '_dpu_kernels_dev.c'

dpa_lib_dir = dependency_dpa.get_variable(pkgconfig : 'libdir')
dpa_include_dir = dependency_dpa.get_variable(pkgconfig : 'includedir')

# Run DPA compiler
run_command(dpacc_build_script, meson.project_build_root(), dpa_lib_dir, dpa_include_dir, sample_device_src, SAMPLE_NAME,
	    sample_program_name, check: true)

# Dependencies
sample_device_build_dir = meson.project_build_root() + '/' + SAMPLE_NAME + '/dpu/device/build_dpacc'
dpa_program_lib = meson.get_compiler('c').find_library(sample_program_name, dirs : sample_device_build_dir,
							static: true)

sample_dependencies += dpa_program_lib

executable('doca_' + SAMPLE_NAME + '_dpu', sample_srcs,
	c_args : '-Wno-missing-braces',
	dependencies : sample_dependencies,
	include_directories: sample_inc_dirs,
	install: false)
