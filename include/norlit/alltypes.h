/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#include <norlit/header/start.h>

#ifdef __need_FILE
#undef __need_FILE
struct _FILE;
typedef struct _FILE FILE;
#endif

#ifdef __need_locale_t
#undef __need_locale_t
typedef void* locale_t;
#endif

#ifdef __need_mbstate_t
#undef __need_mbstate_t
typedef int mbstate_t;
#endif

#ifdef __need_wctype_t
#undef __need_wctype_t
typedef int wctype_t;
#endif

#ifdef __need_wint_t
#undef __need_wint_t
typedef int wint_t;
#endif

#ifdef __need_clock_t
#undef __need_clock_t
typedef __UINT64_TYPE__ clock_t;
#endif

#ifdef __need_time_t
#undef __need_time_t
typedef __UINT64_TYPE__ time_t;
#endif

#ifdef __need_clockid_t
#undef __need_clockid_t
typedef int clockid_t;
#endif

#ifdef __need_timer_t
#undef __need_timer_t
typedef int timer_t;
#endif

#ifdef __need_pid_t
#undef __need_pid_t
typedef int pid_t;
#endif

#ifdef __need_va_list
#undef __need_va_list
#include <stdarg.h>
#endif

#if defined(__need_size_t) || defined(__need_wchar_t)
#include <stddef.h>
#endif

#include <norlit/header/end.h>