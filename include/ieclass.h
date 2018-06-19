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

/*! \file ieclass.h
    \brief entity files loader API
    this describes the APIs involved when loading entity description files
    (initially, .def and .fgd)
 */

#ifndef _IECLASS_H_
#define _IECLASS_H_

#define ECLASS_MAJOR "eclass"

typedef void ( *PFN_ECLASS_SCANFILE )( char *filename );
typedef const char*       ( *PFN_ECLASS_GETEXTENSION )();

struct _EClassTable
{
	int m_nSize;
	PFN_ECLASS_SCANFILE m_pfnScanFile;
	PFN_ECLASS_GETEXTENSION m_pfnGetExtension;
};

#define ECLASSMANAGER_MAJOR "eclassmanager"

typedef void ( *PFN_ECLASS_INSERTALPHABETIZED )( eclass_t *e );
typedef eclass_t** ( *PFN_GET_ECLASS_E )();
typedef void ( *PFN_SET_ECLASS_FOUND )( qboolean );
typedef qboolean ( *PFN_GET_PARSING_SINGLE )();
typedef eclass_t* ( *PFN_ECLASS_CREATE )( const char *name, float col1, float col2, float col3, const vec3_t *mins, const vec3_t *maxs, const char *comments );
typedef eclass_t* ( *PFN_ECLASS_FORNAME )( const char* name, qboolean has_brushes );

struct _EClassManagerTable
{
	int m_nSize;
	PFN_ECLASS_INSERTALPHABETIZED m_pfnEclass_InsertAlphabetized;
	PFN_GET_ECLASS_E m_pfnGet_Eclass_E;
	PFN_SET_ECLASS_FOUND m_pfnSet_Eclass_Found;
	PFN_GET_PARSING_SINGLE m_pfnGet_Parsing_Single;
	PFN_ECLASS_CREATE m_pfnEClass_Create;
	PFN_ECLASS_FORNAME m_pfnEclass_ForName;
};

#endif
