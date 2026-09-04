#
# Copyright (C) 2019 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

ifeq ($(CONFIG_MACH_MT6893),y)
PWR_PLAT=mt6885
else ifeq ($(CONFIG_MACH_MT6877),y)
PWR_PLAT=mt6877
else
PWR_PLAT=$(MTK_PLATFORM)
endif


# ------------------------------------------------------------------------------
#  Initial flow
# ------------------------------------------------------------------------------
subdir-ccflags-y += -DINIT_MDLA_BY_SELF
#subdir-ccflags-y += -DBUILD_MODULE



# ------------------------------------------------------------------------------
# APUSYS ARCH : Legacy ARM version
# ------------------------------------------------------------------------------
subdir-ccflags-y += -DLEGACY_PROJ
ccflags-y += -I$(obj)/../../include/
ccflags-y += -I$(obj)/../../util/
ccflags-y += -I$(obj)/../../power/2.0/
ccflags-y += -I$(obj)/../../power/2.0/$(PWR_PLAT)/
ccflags-y += -I$(obj)/../../midware/1.1/



# ------------------------------------------------------------------------------
# APUSYS ARCH : uP version
# ------------------------------------------------------------------------------
#subdir-ccflags-y += -DRV_COMP
#
#ccflags-y += -I$(obj)/../util/
#ccflags-y += -I$(obj)/../power/3.0/
#ccflags-y += -I$(obj)/../power/3.0/$(PWR_PLAT)/
#
## Replace old apusys_device (Path : apusys/include -> apusys/mdla/dummy/)
#ccflags-y += -I$(obj)/dummy/



# ------------------------------------------------------------------------------
# GKI : MDLA only
# ------------------------------------------------------------------------------

mdla-dir := $(srctree)/drivers/misc/mediatek/apusys/mdla/new_arch
ccflags-y += -I$(mdla-dir)

obj-y += mdla.o

mdla-objs += $(shell cd $(mdla-dir) && find * -name "*.c" | sed 's/\.c/\.o/g')



# ------------------------------------------------------------------------------
# GKI : Copy following description to apusys/Makefile
# ------------------------------------------------------------------------------
#   src=$(srctree)/drivers/misc/mediatek/apusys
#   ccflags-y += -I$(src)/mdla/
#   apusys-objs += $(shell cd $(src) && find mdla -name "*.c" | sed 's/\.c/\.o/g')

