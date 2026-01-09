#!/bin/bash

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

set -e

# This script uses the dpacc tool (located in /opt/mellanox/doca/tools/dpacc) to compile DPA kernels device code.
# This script takes 4 arguments:
# arg1: The project's build path (for the DPA Device build)
# arg2: Install directory for DOCA's device libraries
# arg3: Install directory for DOCA's include files
# arg4: Absolute paths of all DPA (kernel) device source code *files* (our code)
# arg5: The sample name
# arg6: The output DPACC sample program name

####################
## Configurations ##
####################

PROJECT_BUILD_DIR=$1
DOCA_LIB_DIR=$2
DOCA_INCLUDE_DIR=$3
DPA_KERNELS_DEVICE_SRC=$4
SAMPLE_NAME=$5
SAMPLE_PROGRAM_NAME=$6

# DOCA Configurations
DOCA_DPACC="/opt/mellanox/doca/tools/dpacc"

HOST_CC_FLAGS="-Wno-deprecated-declarations -Werror -Wall -Wextra"
DEVICE_CC_FLAGS="-Wno-deprecated-declarations -Werror -Wall -Wextra"

# DOCA DPA APP Configuration
# This variable name passed to DPACC with --app-name parameter and it's token must be idintical to the
# struct doca_dpa_app parameter passed to doca_dpa_set_app(), i.e.
# doca_error_t doca_dpa_set_app(..., struct doca_dpa_app *${DPA_APP_NAME});
DPA_APP_NAME="devemu_pci_sample_app"

##################
## Script Start ##
##################

# Build directory for the DPA device (kernel) code
SAMPLE_DEVICE_BUILD_DIR="${PROJECT_BUILD_DIR}/${SAMPLE_NAME}/dpu/device/build_dpacc"

rm -rf ${SAMPLE_DEVICE_BUILD_DIR}
mkdir -p ${SAMPLE_DEVICE_BUILD_DIR}

# Compile the DPA (kernel) device source code using the DPACC
$DOCA_DPACC $DPA_KERNELS_DEVICE_SRC \
	-o ${SAMPLE_DEVICE_BUILD_DIR}/${SAMPLE_PROGRAM_NAME}.a \
	-hostcc=gcc \
	-hostcc-options="${HOST_CC_FLAGS}" \
	--devicecc-options="${DEVICE_CC_FLAGS}" \
	--app-name="${DPA_APP_NAME}" \
	-device-libs="-L${DOCA_LIB_DIR} -ldoca_dpa_dev_comm" \
	-ldpa \
	-flto \
	-I${DOCA_INCLUDE_DIR}
