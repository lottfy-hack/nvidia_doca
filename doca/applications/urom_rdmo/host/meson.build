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

app_srcs += files([
        APP_NAME + '.c',
        APP_NAME + '_core.c',
        'worker_rdmo.c',
        '../' + samples_dir_path + '/common.c',
        '../' + samples_dir_path + '/doca_urom/urom_common.c'
])

urom_sample_inc_dir = include_directories('../' + samples_dir_path + '/doca_urom/')

executable(DOCA_PREFIX + APP_NAME, app_srcs + app_common_src,
        c_args : base_c_args,
        dependencies : app_dependencies,
        include_directories : app_inc_dirs + app_common_includes + urom_sample_inc_dir,
        install: install_apps)

