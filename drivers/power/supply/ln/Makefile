subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/typec/tcpc/inc
subdir-ccflags-y += -I$(srctree)/drivers/power/supply/mediatek/misc/
subdir-ccflags-y += -I$(srctree)/drivers/power/supply/mediatek/charger/

obj-y	+= ln8410.o
obj-y	+= ln8000.o

# Disable stack protector
CFLAGS_REMOVE_ln8000.o := -fstack-protector-strong
CFLAGS_REMOVE_ln8410.o := -fstack-protector-strong
CFLAGS_ln8000.o += -fno-stack-protector
CFLAGS_ln8410.o += -fno-stack-protector

# Disable address/pointer tagging related stuff
CFLAGS_ln8000.o += -fno-sanitize=kernel-address
CFLAGS_ln8410.o += -fno-sanitize=kernel-address

# Disable strict aliasing UB exposure
CFLAGS_ln8000.o += -fno-strict-aliasing
CFLAGS_ln8410.o += -fno-strict-aliasing

# Disable stack tagging
# CFLAGS_ln8000.o += -fno-stack-clash-protection
# CFLAGS_ln8410.o += -fno-stack-clash-protection

# Disable tree vectorize
CFLAGS_ln8000.o += -fno-tree-vectorize
CFLAGS_ln8410.o += -fno-tree-vectorize