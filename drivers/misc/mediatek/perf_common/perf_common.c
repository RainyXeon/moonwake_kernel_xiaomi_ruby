// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2019 MediaTek Inc.
 */

#include <linux/spinlock.h>
#include <linux/time.h>
#include <linux/mutex.h>
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <mt-plat/perf_common.h>
#include <perf_tracker.h>
#include <linux/cpu.h>
#include <linux/topology.h>
#ifdef CONFIG_MTK_CORE_CTL
#include <mt-plat/core_ctl.h>
#endif

static u64 checked_timestamp;
static bool long_trace_check_flag;
static DEFINE_SPINLOCK(check_lock);
static int perf_common_init;
#define PERF_DEFAULT_INTERVAL_MS 64
static unsigned int perf_poll_interval_ms = PERF_DEFAULT_INTERVAL_MS;
static bool perf_force_enable;
static DEFINE_MUTEX(perf_cfg_mutex);
#ifdef CONFIG_MTK_PERF_TRACKER
int cluster_nr = -1;
#endif

static inline u64 perf_get_interval_ns(void)
{
	unsigned int interval = READ_ONCE(perf_poll_interval_ms);

	if (!interval)
		return 0;

	return (u64)interval * NSEC_PER_MSEC;
}

static bool perf_should_sample(void)
{
	if (READ_ONCE(perf_force_enable))
		return true;

#ifdef CONFIG_MTK_PERF_TRACKER
	return perf_tracker_is_enabled();
#else
	return false;
#endif
}

static inline bool perf_do_check(u64 wallclock)
{
	bool do_check = false;
	unsigned long flags;
	u64 interval = perf_get_interval_ns();

	if (!interval)
		return false;

	/* check interval */
	spin_lock_irqsave(&check_lock, flags);
	if ((s64)(wallclock - checked_timestamp)
		>= (s64)interval) {
		checked_timestamp = wallclock;
		long_trace_check_flag = !long_trace_check_flag;
		do_check = true;
	}
	spin_unlock_irqrestore(&check_lock, flags);

	return do_check;
}

#ifdef CONFIG_MTK_PERF_TRACKER
bool hit_long_check(void)
{
	bool do_check = false;
	unsigned long flags;

	spin_lock_irqsave(&check_lock, flags);
	if (long_trace_check_flag)
		do_check = true;
	spin_unlock_irqrestore(&check_lock, flags);
	return do_check;
}
#endif

void perf_common(u64 wallclock)
{
	long mm_available = -1, mm_free = -1;

	if (!perf_should_sample())
		return;

	if (!perf_do_check(wallclock))
		return;

#ifdef CONFIG_MTK_CORE_CTL
	/* run core_ctl at the same cadence as the perf sampler */
	if (hit_long_check())
		core_ctl_tick(wallclock);
#endif

	if (unlikely(!perf_common_init))
		return;

	perf_tracker(wallclock, mm_available, mm_free);
}

static ssize_t show_perf_force_enable(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%u\n",
			(unsigned int)READ_ONCE(perf_force_enable));
}

static ssize_t store_perf_force_enable(struct kobject *kobj,
		struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	unsigned int val;

	if (kstrtouint(buf, 0, &val))
		return -EINVAL;

	mutex_lock(&perf_cfg_mutex);
	perf_force_enable = !!val;
	mutex_unlock(&perf_cfg_mutex);

	return count;
}

static ssize_t show_perf_interval_ms(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%u\n",
			READ_ONCE(perf_poll_interval_ms));
}

static ssize_t store_perf_interval_ms(struct kobject *kobj,
		struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	unsigned int val;

	if (kstrtouint(buf, 0, &val))
		return -EINVAL;

	if (val != 0 && val < 16)
		val = 16;

	mutex_lock(&perf_cfg_mutex);
	perf_poll_interval_ms = val;
	mutex_unlock(&perf_cfg_mutex);

	return count;
}

static struct kobj_attribute perf_force_enable_attr =
__ATTR(force_enable, 0600,
	show_perf_force_enable, store_perf_force_enable);

static struct kobj_attribute perf_interval_attr =
__ATTR(interval_ms, 0644,
	show_perf_interval_ms, store_perf_interval_ms);

static struct attribute *perf_attrs[] = {
#ifdef CONFIG_MTK_PERF_TRACKER
	&perf_tracker_enable_attr.attr,
#endif
	&perf_force_enable_attr.attr,
	&perf_interval_attr.attr,
	NULL,
};

static struct attribute_group perf_attr_group = {
	.attrs = perf_attrs,
};

static int init_perf_common(void)
{
	int ret = 0;
	struct kobject *kobj = NULL;

	perf_common_init = 1;
#ifdef CONFIG_MTK_PERF_TRACKER
	cluster_nr = arch_nr_clusters();

	if (unlikely(cluster_nr <= 0 || cluster_nr > 3))
		cluster_nr = 3;
#endif

	kobj = kobject_create_and_add("perf", &cpu_subsys.dev_root->kobj);

	if (kobj) {
		ret = sysfs_create_group(kobj, &perf_attr_group);
		if (ret)
			kobject_put(kobj);
		else
			kobject_uevent(kobj, KOBJ_ADD);
	}

	return 0;
}
late_initcall_sync(init_perf_common);
