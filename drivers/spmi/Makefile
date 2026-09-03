#
# Makefile for kernel SPMI framework.
#
obj-$(CONFIG_SPMI)	+= spmi.o

ccflags-y += -I$(srctree)/drivers/spmi

obj-$(CONFIG_SPMI_MSM_PMIC_ARB)	+= spmi-pmic-arb.o
obj-$(CONFIG_MTK_PMIF)	+= mtk-pmif.o mtk-dbg.o
