/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#if defined(HAVE_CONFIG_H) && HAVE_CONFIG_H && defined(BUILDING_WITH_CMAKE)
#include "cmakeconfig.h"
#endif

#include <wtf/Platform.h>
#include <wtf/ExportMacros.h>

#if OS(WINDOWS)

#ifndef _WIN32_WINNT
#if defined(_M_X64) || defined(__x86_64__) 
#define _WIN32_WINNT 0x600
#else
#define _WIN32_WINNT 0x0502
#endif
#endif

#ifndef WINVER
#if defined(_M_X64) || defined(__x86_64__) 
#define WINVER 0x0600
#else
#define WINVER 0x0502
#endif
#endif

#if !COMPILER(MSVC7_OR_LOWER)
// We need to define this before the first #include of stdlib.h or it won't contain rand_s.
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif
#endif

#endif

#ifdef __cplusplus
#undef new
#undef delete
#include <wtf/FastMalloc.h>
#endif

#include <wtf/DisallowCType.h>

#if COMPILER(MSVC)
#define SKIP_STATIC_CONSTRUCTORS_ON_MSVC 1
#else
#define SKIP_STATIC_CONSTRUCTORS_ON_GCC 1
#endif
