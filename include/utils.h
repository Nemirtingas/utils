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

#if defined(WIN64) || defined(_WIN64) || defined(__MINGW64__)
    #define __WINDOWS_64__
    #define __64BITS__
#elif defined(WIN32) || defined(_WIN32) || defined(__MINGW32__)
    #define __WINDOWS_32__
    #define __32BITS__
#endif

#if defined(__WINDOWS_32__) || defined(__WINDOWS_64__)
    #define __WINDOWS__
#endif

#if defined(__linux__) || defined(linux)
    #if defined(__x86_64__)
        #define __LINUX_64__
        #define __64BITS__
    #else
        #define __LINUX_32__
        #define __32BITS__
    #endif
#endif

#if defined(__LINUX_32__) || defined(__LINUX_64__)
    #define __LINUX__
#endif

#if defined(__APPLE__)
    #if defined(__x86_64__)
        #define __APPLE_64__
        #define __64BITS__
    #else
        #define __APPLE_32__
        #define __32BITS__
    #endif
#endif

#ifdef __cplusplus
    #define EXPORT_C_API   extern "C"
#else
    #define EXPORT_C_API   extern
#endif
#define EXPORT_CXX_API extern

#if defined(__WINDOWS__)

    #define EXPORT_API(mode) __declspec(mode)
    #define EXPORT_STATIC_API

    #define LOCAL_API

#elif defined(__LINUX__) || defined(__APPLE__)// defined(__WINDOWS__)

    #define EXPORT_API(mode) __attribute__((visibility ("default")))
    #define EXPORT_STATIC_API EXPORT_API(static)

    //#define LOCAL_API __attribute__((visibility ("internal")))
    #define LOCAL_API __attribute__((visibility ("hidden")))

#endif // defined(__APPLE__)

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
