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

#!/usr/bin/python3

import argparse
import re
import os
import subprocess

parser = argparse.ArgumentParser(description='Bind PCI device to VFIO Driver.')
parser.add_argument('pci_address', metavar='P', type=str, help='PCI address of device to bind. Format: XXXX:XX:XX.X')

args = parser.parse_args()

pci_address = args.pci_address
pattern = re.compile('^([A-Fa-f0-9]){4}:([A-Fa-f0-9]){2}:([A-Fa-f0-9]){2}.([A-Fa-f0-9])')
if not pattern.match(pci_address):
	print("Bad PCI format, expected format: XXXX:XX:XX.X")
	quit()

pci_device_sys_path = os.path.join('/sys/bus/pci/devices/', pci_address)
if not os.path.isdir(pci_device_sys_path):
	print("PCI device does not exist")
	quit()

os.system('modprobe vfio-pci')

unbind_path = os.path.join(pci_device_sys_path, 'driver/unbind')
if os.path.isfile(unbind_path):
	with open(unbind_path, 'w') as unbind_file:
		unbind_file.write(pci_address)


lspci = subprocess.run(['lspci', '-ns', pci_address], stdout=subprocess.PIPE, text=True)
lspci_out = str(lspci.stdout)
(vid, did) = lspci_out.replace('\n', '').split(' ')[2].split(':')

try:
	with open('/sys/bus/pci/drivers/vfio-pci/remove_id', 'w') as remove_id_file:
		remove_id_file.write(f'{vid} {did}')
except:
	# ID does not exist
	pass

with open('/sys/bus/pci/drivers/vfio-pci/new_id', 'w') as new_id_file:
	new_id_file.write(f'{vid} {did}')

iommu_group_link_path = os.path.join(pci_device_sys_path, 'iommu_group')
readlink = subprocess.run(['readlink', iommu_group_link_path], stdout=subprocess.PIPE, text=True)
readlink_out = str(readlink.stdout)
iommu_group_id = readlink_out.split('/')[-1].replace('\n', '')

print(f'PCI Address = {pci_address}')
print(f'VFIO Group ID = {iommu_group_id}')
