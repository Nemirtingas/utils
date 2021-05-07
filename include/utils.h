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

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "utils_osdetector"

#ifdef __cplusplus
    #define EXPORT_C_API   extern "C"
#else
    #define EXPORT_C_API   extern
#endif
#define EXPORT_CXX_API extern

#if defined(UTILS_OS_WINDOWS)

    #define EXPORT_API(mode) __declspec(mode)
    #define EXPORT_STATIC_API

    #define LOCAL_API

#elif defined(UTILS_OS_LINUX) || defined(UTILS_OS_APPLE)

    #define EXPORT_API(mode) __attribute__((visibility ("default")))
    #define EXPORT_STATIC_API EXPORT_API(static)

    //#define LOCAL_API __attribute__((visibility ("internal")))
    #define LOCAL_API __attribute__((visibility ("hidden")))

#endif

#include <cstdint>
#include <string>
#include <cstring>
#include <algorithm>
#include <mutex>
#include <iterator>

#include "switchstr"
#include "template_pack_size"
#include "constexpr_strlen"
#include "istring"
#include "string_trim"
#include "class_enum"
#include "endianness"
#include "scoped_lock"

#ifdef __EXPORT_SYMBOLS__
void LOCAL_API shared_library_load(void* hmodule);
void LOCAL_API shared_library_unload(void* hmodule);
#endif

#endif // UTILS_H_INCLUDED
