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
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 */
#pragma once

/** \file
 * \ingroup bke
 */

#ifdef __cplusplus
extern "C" {
#endif

struct CurveCache;
struct Object;

/* ---------------------------------------------------- */
/* Curve Paths */

int BKE_anim_path_get_array_size(const struct CurveCache *curve_cache);
float BKE_anim_path_get_length(const struct CurveCache *curve_cache);

/**
 * This function populates the 'ob->runtime.curve_cache->anim_path_accum_length' data.
 * You should never have to call this manually as it should already have been called by
 * 'BKE_displist_make_curveTypes'. Do not call this manually unless you know what you are doing.
 */
void BKE_anim_path_calc_data(struct Object *ob);

/**
 * Calculate the deformation implied by the curve path at a given parametric position,
 * and returns whether this operation succeeded.
 *
 * \param ctime: Time is normalized range <0-1>.
 *
 * \return success.
 */
bool BKE_where_on_path(const struct Object *ob,
                       float ctime,
                       float r_vec[4],
                       float r_dir[3],
                       float r_quat[4],
                       float *r_radius,
                       float *r_weight);

#ifdef __cplusplus
}
#endif
