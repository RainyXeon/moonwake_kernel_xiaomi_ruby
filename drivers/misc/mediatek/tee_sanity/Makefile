# SPDX-License-Identifier: GPL-2.0

obj-$(CONFIG_MTK_TEE_SANITY) += tee_sanity.o

CFLAGS_tee_sanity.o := -I$(src)
ccflags-y += -I$(srctree)/drivers/misc/mediatek/tee_sanity
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include

# timesync to get boot time
ccflags-y += -I$(srctree)/drivers/misc/mediatek/timer/timesync
