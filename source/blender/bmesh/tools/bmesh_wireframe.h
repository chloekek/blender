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
 */

/** \file
 * \ingroup bmesh
 *
 * Wire Frame.
 */

#pragma once

/**
 * \param defgrp_index: Vertex group index, -1 for no vertex groups.
 *
 * \note All edge tags must be cleared.
 * \note Behavior matches MOD_solidify.c
 */
void BM_mesh_wireframe(BMesh *bm,
                       const float offset,
                       const float offset_fac,
                       const float offset_fac_vg,
                       const bool use_replace,
                       const bool use_boundary,
                       const bool use_even_offset,
                       const bool use_relative_offset,
                       const bool use_crease,
                       const float crease_weight,
                       const int defgrp_index,
                       const bool defgrp_invert,
                       const short mat_offset,
                       const short mat_max,
                       const bool use_tag);
