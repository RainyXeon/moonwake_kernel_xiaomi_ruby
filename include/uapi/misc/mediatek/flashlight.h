/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * MediaTek Flashlight UAPI
 *
 * This header is consumed by userspace (e.g. camera torch control) via
 * <misc/mediatek/flashlight.h>.
 */

#ifndef _UAPI_MISC_MEDIATEK_FLASHLIGHT_H
#define _UAPI_MISC_MEDIATEK_FLASHLIGHT_H

#include <linux/ioctl.h>
#include <linux/types.h>

/* flashlight arguments */
struct flashlight_user_arg {
	int type_id;
	int ct_id;
	int arg;
};

/* ioctl magic number */
#define FLASHLIGHT_MAGIC 'S'

/* ioctl protocol version 0. */
#define FLASHLIGHTIOC_T_ENABLE             _IOW(FLASHLIGHT_MAGIC, 5, int)
#define FLASHLIGHTIOC_T_LEVEL              _IOW(FLASHLIGHT_MAGIC, 10, int)
#define FLASHLIGHTIOC_T_FLASHTIME          _IOW(FLASHLIGHT_MAGIC, 15, int)
#define FLASHLIGHTIOC_T_STATE              _IOW(FLASHLIGHT_MAGIC, 20, int)
#define FLASHLIGHTIOC_G_FLASHTYPE          _IOR(FLASHLIGHT_MAGIC, 25, int)
#define FLASHLIGHTIOC_X_SET_DRIVER         _IOWR(FLASHLIGHT_MAGIC, 30, int)
#define FLASHLIGHTIOC_T_DELAY              _IOW(FLASHLIGHT_MAGIC, 35, int)

/* ioctl protocol version 1. */
#define FLASH_IOC_SET_TIME_OUT_TIME_MS     _IOR(FLASHLIGHT_MAGIC, 100, int)
#define FLASH_IOC_SET_STEP                 _IOR(FLASHLIGHT_MAGIC, 105, int)
#define FLASH_IOC_SET_DUTY                 _IOR(FLASHLIGHT_MAGIC, 110, int)
#define FLASH_IOC_SET_ONOFF                _IOR(FLASHLIGHT_MAGIC, 115, int)
#define FLASH_IOC_UNINIT                   _IOR(FLASHLIGHT_MAGIC, 120, int)

#define FLASH_IOC_PRE_ON                   _IOR(FLASHLIGHT_MAGIC, 125, int)
#define FLASH_IOC_GET_PRE_ON_TIME_MS       _IOR(FLASHLIGHT_MAGIC, 130, int)
#define FLASH_IOC_GET_PRE_ON_TIME_MS_DUTY  _IOR(FLASHLIGHT_MAGIC, 131, int)

#define FLASH_IOC_SET_REG_ADR              _IOR(FLASHLIGHT_MAGIC, 135, int)
#define FLASH_IOC_SET_REG_VAL              _IOR(FLASHLIGHT_MAGIC, 140, int)
#define FLASH_IOC_SET_REG                  _IOR(FLASHLIGHT_MAGIC, 145, int)
#define FLASH_IOC_GET_REG                  _IOR(FLASHLIGHT_MAGIC, 150, int)

#define FLASH_IOC_GET_MAIN_PART_ID         _IOR(FLASHLIGHT_MAGIC, 155, int)
#define FLASH_IOC_GET_SUB_PART_ID          _IOR(FLASHLIGHT_MAGIC, 160, int)
#define FLASH_IOC_GET_MAIN2_PART_ID        _IOR(FLASHLIGHT_MAGIC, 165, int)
#define FLASH_IOC_GET_PART_ID              _IOR(FLASHLIGHT_MAGIC, 166, int)

#define FLASH_IOC_HAS_LOW_POWER_DETECT     _IOR(FLASHLIGHT_MAGIC, 170, int)
#define FLASH_IOC_LOW_POWER_DETECT_START   _IOR(FLASHLIGHT_MAGIC, 175, int)
#define FLASH_IOC_LOW_POWER_DETECT_END     _IOR(FLASHLIGHT_MAGIC, 180, int)
#define FLASH_IOC_IS_LOW_POWER             _IOR(FLASHLIGHT_MAGIC, 182, int)

#define FLASH_IOC_GET_ERR                  _IOR(FLASHLIGHT_MAGIC, 185, int)
#define FLASH_IOC_GET_PROTOCOL_VERSION     _IOR(FLASHLIGHT_MAGIC, 190, int)

#define FLASH_IOC_IS_CHARGER_IN            _IOR(FLASHLIGHT_MAGIC, 195, int)
#define FLASH_IOC_IS_OTG_USE               _IOR(FLASHLIGHT_MAGIC, 200, int)
#define FLASH_IOC_GET_FLASH_DRIVER_NAME_ID _IOR(FLASHLIGHT_MAGIC, 205, int)

/* ioctl protocol version 2 */
#define FLASH_IOC_IS_CHARGER_READY         _IOR(FLASHLIGHT_MAGIC, 210, int)
#define FLASH_IOC_SET_SCENARIO             _IOWR(FLASHLIGHT_MAGIC, 215, int)
#define FLASH_IOC_IS_HARDWARE_READY        _IOR(FLASHLIGHT_MAGIC, 220, int)
#define FLASH_IOC_GET_DUTY_NUMBER          _IOWR(FLASHLIGHT_MAGIC, 225, int)
#define FLASH_IOC_GET_MAX_TORCH_DUTY       _IOWR(FLASHLIGHT_MAGIC, 230, int)
#define FLASH_IOC_GET_CURRENT_TORCH_DUTY   _IOR(FLASHLIGHT_MAGIC, 232, int)
#define FLASH_IOC_GET_DUTY_CURRENT         _IOWR(FLASHLIGHT_MAGIC, 235, int)
#define FLASH_IOC_GET_HW_TIMEOUT           _IOWR(FLASHLIGHT_MAGIC, 240, int)
#define FLASH_IOC_GET_HW_FAULT             _IOR(FLASHLIGHT_MAGIC, 250, int)
#define FLASH_IOC_GET_HW_FAULT2            _IOR(FLASHLIGHT_MAGIC, 251, int)

#endif /* _UAPI_MISC_MEDIATEK_FLASHLIGHT_H */
