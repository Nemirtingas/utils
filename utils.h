/* Copyright (C) 2019 Nemirtingas
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

#if defined(__WINDOWS__)

    #ifdef __EXPORT_SYMBOLS__
        #define EXPORT_API extern "C" __declspec(dllexport)
    #else
        #define EXPORT_API extern "C" __declspec(dllimport)
    #endif

    #define LOCAL_API

#elif defined(__LINUX__)// defined(__WINDOWS__)

    #ifdef __EXPORT_SYMBOLS__
        #define EXPORT_API extern "C" __attribute__((visibility ("default")))
    #else
        #define EXPORT_API extern "C" __attribute__((visibility ("default")))
    #endif

    #define LOCAL_API __attribute__((visibility ("internal")))
    //#define LOCAL_API __attribute__((visibility ("hidden")))

#elif defined(__APPLE__)// defined(__LINUX__)

    #define LOCAL_API
    #define EXPORT_API

#endif // defined(__APPLE__)

#include <cstdint>

#define SINGLETON(x) \
private:\
    x();\
    x( x const& ) = delete;\
    x( x && ) = delete;\
    x& operator=( x const& ) = delete;\
    x& operator=( x && ) = delete;\
public:\
    static x& Inst()

#include <string>

// switch case on a string
#ifdef __32BITS__
constexpr uint32_t _hash(const char *input)
{
  return (*input ? static_cast<uint32_t>(*input) + 33 * _hash(input + 1) : 5381);
}

inline uint32_t _hash(const std::string &input)
{
  return _hash(input.c_str());
}
#else
constexpr uint64_t _hash(const char* input)
{
    return (*input ? static_cast<uint64_t>(*input) + 33 * _hash(input + 1) : 5381);
}

inline uint64_t _hash(const std::string& input)
{
    return _hash(input.c_str());
}
#endif

#define switchstr(x) switch( _hash(x) )
#define casestr(x) case _hash(x)

// Sum of all parameter pack sizeof
template <typename... Ts>
constexpr int size_of = 0;

template <typename T, typename... Ts>
constexpr int size_of<T, Ts...> = sizeof(T) + size_of<Ts...>;

template<size_t N>
constexpr size_t static_strlen(const char(&)[N])
{
    return N-1;
}
//

// Case insensible string
struct ichar_traits : public std::char_traits<char>
{
    static bool eq(char c1, char c2) { return tolower(c1) == tolower(c2); }
    static bool ne(char c1, char c2) { return tolower(c1) != tolower(c2); }
    static bool lt(char c1, char c2) { return tolower(c1) <  tolower(c2); }
    static int compare(const char* s1, const char* s2, size_t n)
    {
        while( n-- != 0 )
        {
            if( tolower(*s1) < tolower(*s2) ) return -1;
            if( tolower(*s1) > tolower(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a)
    {
        while( n-- > 0 && tolower(*s) != tolower(a) )
        {
            ++s;
        }
        return s;
    }
};

typedef std::basic_string<char, ichar_traits> istring;

LOCAL_API std::string& ltrim(std::string& str);
LOCAL_API std::string& rtrim(std::string& str);
LOCAL_API std::string& trim(std::string& str);
LOCAL_API std::string& to_lower(std::string& str);
LOCAL_API std::string& to_upper(std::string& str);

#ifdef __EXPORT_SYMBOLS__
void LOCAL_API shared_library_load(void* hmodule);
void LOCAL_API shared_library_unload(void* hmodule);
#endif

#endif // UTILS_H_INCLUDED