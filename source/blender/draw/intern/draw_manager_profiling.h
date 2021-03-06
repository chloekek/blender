/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Copyright 2016, Blender Foundation.
 */

/** \file
 * \ingroup draw
 */

#pragma once

struct rcti;

void DRW_stats_free(void);
void DRW_stats_begin(void);
void DRW_stats_reset(void);

/**
 * Use this to group the queries. It does NOT keep track
 * of the time, it only sum what the queries inside it.
 */
void DRW_stats_group_start(const char *name);
void DRW_stats_group_end(void);

/**
 * \note Only call this when no sub timer will be called.
 */
void DRW_stats_query_start(const char *name);
void DRW_stats_query_end(void);

void DRW_stats_draw(const rcti *rect);
