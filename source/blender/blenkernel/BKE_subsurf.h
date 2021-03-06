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

/* struct DerivedMesh is used directly */
#include "BKE_DerivedMesh.h"

/* Thread sync primitives used directly. */
#include "BLI_threads.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CCGEdge;
struct CCGElem;
struct CCGFace;
struct CCGVert;
struct DMFlagMat;
struct DerivedMesh;
struct EdgeHash;
struct MPoly;
struct Mesh;
struct MeshElemMap;
struct Object;
struct PBVH;
struct SubsurfModifierData;

/**************************** External *****************************/

typedef enum {
  SUBSURF_USE_RENDER_PARAMS = 1,
  SUBSURF_IS_FINAL_CALC = 2,
  SUBSURF_FOR_EDIT_MODE = 4,
  SUBSURF_IN_EDIT_MODE = 8,
  SUBSURF_ALLOC_PAINT_MASK = 16,
  SUBSURF_USE_GPU_BACKEND = 32,
  SUBSURF_IGNORE_SIMPLIFY = 64,
} SubsurfFlags;

struct DerivedMesh *subsurf_make_derived_from_derived(struct DerivedMesh *dm,
                                                      struct SubsurfModifierData *smd,
                                                      const struct Scene *scene,
                                                      float (*vertCos)[3],
                                                      SubsurfFlags flags);

void subsurf_calculate_limit_positions(struct Mesh *me, float (*r_positions)[3]);

/**
 * Get grid-size from 'level', level must be greater than zero.
 */
int BKE_ccg_gridsize(int level);

/**
 * X/Y grid coordinates at 'low_level' can be multiplied by the result
 * of this function to convert to grid coordinates at 'high_level'.
 */
int BKE_ccg_factor(int low_level, int high_level);

/**
 * Translate #GridHidden into the #ME_HIDE flag for MVerts. Assumes
 * vertices are in the order output by #ccgDM_copyFinalVertArray.
 */
void subsurf_copy_grid_hidden(struct DerivedMesh *dm,
                              const struct MPoly *mpoly,
                              struct MVert *mvert,
                              const struct MDisps *mdisps);

/**
 * Translate #GridPaintMask into vertex paint masks. Assumes vertices
 * are in the order output by #ccgDM_copyFinalVertArray.
 */
void subsurf_copy_grid_paint_mask(struct DerivedMesh *dm,
                                  const struct MPoly *mpoly,
                                  float *paint_mask,
                                  const struct GridPaintMask *grid_paint_mask);

bool subsurf_has_edges(struct DerivedMesh *dm);
bool subsurf_has_faces(struct DerivedMesh *dm);

typedef enum MultiresModifiedFlags {
  /* indicates the grids have been sculpted on, so MDisps
   * have to be updated */
  MULTIRES_COORDS_MODIFIED = 1,
  /* indicates elements have been hidden or unhidden */
  MULTIRES_HIDDEN_MODIFIED = 2,
} MultiresModifiedFlags;

/**************************** Internal *****************************/

typedef struct CCGDerivedMesh {
  DerivedMesh dm;

  struct CCGSubSurf *ss;
  int freeSS;
  int drawInteriorEdges, useSubsurfUv;

  struct {
    int startVert;
    struct CCGVert *vert;
  } * vertMap;
  struct {
    int startVert;
    int startEdge;
    struct CCGEdge *edge;
  } * edgeMap;
  struct {
    int startVert;
    int startEdge;
    int startFace;
    struct CCGFace *face;
  } * faceMap;

  short *edgeFlags;
  struct DMFlagMat *faceFlags;

  int *reverseFaceMap;

  struct PBVH *pbvh;

  struct MeshElemMap *pmap;
  int *pmap_mem;

  struct CCGElem **gridData;
  int *gridOffset;
  struct CCGFace **gridFaces;
  struct DMFlagMat *gridFlagMats;
  unsigned int **gridHidden;
  /* Elements in arrays above. */
  unsigned int numGrid;

  struct {
    struct MultiresModifierData *mmd;
    int local_mmd;

    int lvl, totlvl;
    float (*orco)[3];

    struct Object *ob;
    MultiresModifiedFlags modified_flags;
  } multires;

  struct EdgeHash *ehash;

  ThreadMutex loops_cache_lock;
  ThreadRWMutex origindex_cache_rwlock;
} CCGDerivedMesh;

#ifdef __cplusplus
}
#endif
