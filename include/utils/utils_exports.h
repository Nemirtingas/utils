/* Copyright (C) Nemirtingas
 * This file is part of utils.
 *
 * utils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * utils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with utils.  If not, see <https://www.gnu.org/licenses/>
 */

#pragma once

#include "utils_osdetector.h"

#ifdef __cplusplus
    #define UTILS_EXPORT_C_API   extern "C"
    #define UTILS_EXPORT_CXX_API extern
#else
    #define UTILS_EXPORT_C_API   extern
    #define UTILS_EXPORT_CXX_API #error "No C++ export in C"
#endif

#if defined(UTILS_OS_WINDOWS)

    #define UTILS_EXPORT_API(mode) __declspec(mode)

    #define UTILS_LOCAL_API

#elif defined(UTILS_OS_LINUX) || defined(UTILS_OS_APPLE)

    #define UTILS_EXPORT_API(mode) __attribute__((visibility ("default")))

    //#define LOCAL_API __attribute__((visibility ("internal")))
    #define UTILS_LOCAL_API __attribute__((visibility ("hidden")))

#endif

#ifdef UTILS_EXPORT_LIBRARY
void UTILS_LOCAL_API shared_library_load(void* hmodule);
void UTILS_LOCAL_API shared_library_unload(void* hmodule);
#endif
