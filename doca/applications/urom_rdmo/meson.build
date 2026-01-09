
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

# Set application common variables
app_common_src = []
app_common_hdr = []
app_common_includes = []

# Enter common directory
subdir('common')

if is_dpu
        subdir('dpu')
else
        subdir('host')
endif
