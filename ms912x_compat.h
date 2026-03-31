/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef MS912X_COMPAT_H
#define MS912X_COMPAT_H

#include <linux/string.h>
#include <linux/types.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 18, 0)
#include <linux/dma-buf.h>

#ifdef DMA_BUF_MAP_INIT_OFFSET
#define iosys_map dma_buf_map
#define IOSYS_MAP_INIT_OFFSET DMA_BUF_MAP_INIT_OFFSET
#define iosys_map_memcpy_from dma_buf_map_memcpy_from
#define iosys_map_incr dma_buf_map_incr
#else
struct iosys_map {
	void *vaddr;
};

static inline struct iosys_map
IOSYS_MAP_INIT_OFFSET(const struct iosys_map *src, size_t offset)
{
	struct iosys_map map = {
		.vaddr = (u8 *)src->vaddr + offset,
	};

	return map;
}

static inline void iosys_map_memcpy_from(void *dst,
					 const struct iosys_map *src,
					 size_t offset, size_t len)
{
	memcpy(dst, (u8 *)src->vaddr + offset, len);
}

static inline void iosys_map_incr(struct iosys_map *map, size_t offset)
{
	map->vaddr = (u8 *)map->vaddr + offset;
}
#endif
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0)
#define ms912x_drm_gem_fb_create_with_dirty drm_gem_fb_create
#else
#define ms912x_drm_gem_fb_create_with_dirty drm_gem_fb_create_with_dirty
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 18, 0)
static inline int ms912x_drm_gem_fb_begin_cpu_access(struct drm_framebuffer *fb,
						      enum dma_data_direction dir)
{
	return 0;
}

static inline void ms912x_drm_gem_fb_end_cpu_access(struct drm_framebuffer *fb,
						     enum dma_data_direction dir)
{
}
#else
#define ms912x_drm_gem_fb_begin_cpu_access drm_gem_fb_begin_cpu_access
#define ms912x_drm_gem_fb_end_cpu_access drm_gem_fb_end_cpu_access
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 19, 0)
#define ms912x_drm_fbdev_setup drm_fbdev_generic_setup
#else
#define ms912x_drm_fbdev_setup drm_fbdev_ttm_setup
#endif

#endif
