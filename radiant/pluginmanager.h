/*
   Copyright (C) 1999-2007 id Software, Inc. and contributors.
   For a list of contributors, see the accompanying CONTRIBUTORS file.

   This file is part of GtkRadiant.

   GtkRadiant is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   GtkRadiant is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GtkRadiant; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _PLUGINMANAGER_H_
#define _PLUGINMANAGER_H_

#include "plugin.h"

// global interfaces we are using
extern _QERShadersTable g_ShadersTable;

// NOTE: it's actually a module manager, the name should change to ModuleManager..
class CPlugInManager
{
private:
GSList* m_PlugIns;
CPtrArray m_BrushHandles;
CPtrArray m_SelectedBrushHandles;
CPtrArray m_ActiveBrushHandles;

// v1.70
//! brushes of the current entity ( see m_SelectedBrushHandles and m_ActiveBrushHandles )
CPtrArray m_EntityBrushHandles;
//! allocated entities, not commited yet ( see m_BrushHandles )
CPtrArray m_EntityHandles;

//! tells in which array to look when given a patch index
enum EPatchesMode { EActivePatches, ESelectedPatches, EAllocatedPatches } PatchesMode;
//! patches handles (brush_t*)
CPtrArray m_PatchesHandles;
//! plugin-allocated patches, not commited yet (patchMesh_t*)
CPtrArray m_PluginPatches;

void InitForDir( const Str &dir ); ///< init for plguins/modules below this directory

public:
CPtrArray& GetActiveHandles() {return m_ActiveBrushHandles; };
CPtrArray& GetSelectedHandles() {return m_SelectedBrushHandles; };
CPtrArray& GetPluginPatches() {return m_PluginPatches; };
brush_t* FindBrushHandle( void *vp );
patchMesh_t* FindPatchHandle( int index );
int CreatePatchHandle();
int AllocateActivePatchHandles();
int AllocateSelectedPatchHandles();
void CommitPatchHandleToMap( int index, patchMesh_t *pMesh, char *texName );
void CommitPatchHandleToEntity( int index, patchMesh_t *pMesh, char *texName, void *vpEntity );
void ReleasePatchesHandles() { m_PatchesHandles.RemoveAll(); m_PluginPatches.RemoveAll(); }
void AddFaceToBrushHandle( void *vp, vec3_t v1, vec3_t v2, vec3_t v3 );
void CommitBrushHandleToMap( void *vp );
void DeleteBrushHandle( void* vp );
void* CreateBrushHandle();
void Dispatch( int n, const char *p );
void Cleanup();   ///< cleanup of data structures allocated for plugins, not a plugin reload
void Init();   ///< go through the path where we will find modules and plugins
void LoadImage( const char *name, unsigned char **pic, int *width, int *height );
void ImportMap( IDataStream *in, CPtrArray *ents, const char *type );
void ExportMap( CPtrArray *ents, IDataStream *out, const char *type );
void Shutdown();   ///< shutdown all the plugins/module subsystem
//CPlugInManager();
//virtual ~CPlugInManager();

/*!
   the texture manager front ends the single load
   addins (texture, model, map formats.. etc.)
 */
_QERTextureInfo* GetTextureInfo();
void LoadTexture( const char *pFilename );

void* GetSurfaceFlags();

// v1.70
CPtrArray& GetEntityBrushHandles() {return m_EntityBrushHandles; };
CPtrArray& GetEntityHandles() {return m_EntityHandles; };
//! the vpBrush needs to be in m_BrushHandles
void CommitBrushHandleToEntity( void* vpBrush, void* vpEntity );
//! the vpEntity needs to be in m_EntityHandles
void CommitEntityHandleToMap( void* vpEntity );

protected:
//! read the interfaces this plugin implements
void LoadFromPath( const char *path ); ///< load all modules/plugins in specified path
void RegisterInterfaces();
};



#endif // _PLUGINMANAGER_H_
