subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/typec/tcpc/inc
subdir-ccflags-y += -I$(srctree)/drivers/power/supply/mediatek/misc/
subdir-ccflags-y += -I$(srctree)/drivers/power/supply/mediatek/charger/

obj-y += ln8410.o

CFLAGS_REMOVE_ln8410.o := -fstack-protector-strong
CFLAGS_ln8410.o += -fno-stack-protector
CFLAGS_ln8410.o += -fno-sanitize=kernel-address
CFLAGS_ln8410.o += -fno-strict-aliasing
CFLAGS_ln8410.o += -fno-stack-clash-protection
CFLAGS_ln8410.o += -fno-tree-vectorize
