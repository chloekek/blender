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
 * The Original Code is Copyright (C) 2010 Blender Foundation.
 * All rights reserved.
 */

#pragma once

/** \file
 * \ingroup bke
 * \brief Blender kernel freestyle line style functionality.
 */

#include "DNA_linestyle_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LS_MODIFIER_TYPE_COLOR 1
#define LS_MODIFIER_TYPE_ALPHA 2
#define LS_MODIFIER_TYPE_THICKNESS 3
#define LS_MODIFIER_TYPE_GEOMETRY 4

struct ColorBand;
struct Main;
struct ViewLayer;
struct bContext;

void BKE_linestyle_init(struct FreestyleLineStyle *linestyle);
FreestyleLineStyle *BKE_linestyle_new(struct Main *bmain, const char *name);

FreestyleLineStyle *BKE_linestyle_active_from_view_layer(struct ViewLayer *view_layer);

LineStyleModifier *BKE_linestyle_color_modifier_add(FreestyleLineStyle *linestyle,
                                                    const char *name,
                                                    int type);
LineStyleModifier *BKE_linestyle_alpha_modifier_add(FreestyleLineStyle *linestyle,
                                                    const char *name,
                                                    int type);
LineStyleModifier *BKE_linestyle_thickness_modifier_add(FreestyleLineStyle *linestyle,
                                                        const char *name,
                                                        int type);
LineStyleModifier *BKE_linestyle_geometry_modifier_add(FreestyleLineStyle *linestyle,
                                                       const char *name,
                                                       int type);

LineStyleModifier *BKE_linestyle_color_modifier_copy(FreestyleLineStyle *linestyle,
                                                     const LineStyleModifier *m,
                                                     const int flag);
LineStyleModifier *BKE_linestyle_alpha_modifier_copy(FreestyleLineStyle *linestyle,
                                                     const LineStyleModifier *m,
                                                     const int flag);
LineStyleModifier *BKE_linestyle_thickness_modifier_copy(FreestyleLineStyle *linestyle,
                                                         const LineStyleModifier *m,
                                                         const int flag);
LineStyleModifier *BKE_linestyle_geometry_modifier_copy(FreestyleLineStyle *linestyle,
                                                        const LineStyleModifier *m,
                                                        const int flag);

int BKE_linestyle_color_modifier_remove(FreestyleLineStyle *linestyle,
                                        LineStyleModifier *modifier);
int BKE_linestyle_alpha_modifier_remove(FreestyleLineStyle *linestyle,
                                        LineStyleModifier *modifier);
int BKE_linestyle_thickness_modifier_remove(FreestyleLineStyle *linestyle,
                                            LineStyleModifier *modifier);
int BKE_linestyle_geometry_modifier_remove(FreestyleLineStyle *linestyle,
                                           LineStyleModifier *modifier);

/**
 * Reinsert \a modifier in modifier list with an offset of \a direction.
 * \return if position of \a modifier has changed.
 */
bool BKE_linestyle_color_modifier_move(FreestyleLineStyle *linestyle,
                                       LineStyleModifier *modifier,
                                       int direction);
bool BKE_linestyle_alpha_modifier_move(FreestyleLineStyle *linestyle,
                                       LineStyleModifier *modifier,
                                       int direction);
bool BKE_linestyle_thickness_modifier_move(FreestyleLineStyle *linestyle,
                                           LineStyleModifier *modifier,
                                           int direction);
bool BKE_linestyle_geometry_modifier_move(FreestyleLineStyle *linestyle,
                                          LineStyleModifier *modifier,
                                          int direction);

void BKE_linestyle_modifier_list_color_ramps(FreestyleLineStyle *linestyle, ListBase *listbase);
char *BKE_linestyle_path_to_color_ramp(FreestyleLineStyle *linestyle,
                                       struct ColorBand *color_ramp);

bool BKE_linestyle_use_textures(FreestyleLineStyle *linestyle, const bool use_shading_nodes);

void BKE_linestyle_default_shader(const struct bContext *C, FreestyleLineStyle *linestyle);

#ifdef __cplusplus
}
#endif
