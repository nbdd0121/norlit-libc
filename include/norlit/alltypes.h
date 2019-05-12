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
typedef __WINT_TYPE__ wint_t;
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
typedef __builtin_va_list va_list;
#endif

#ifdef __need_size_t
#undef __need_size_t
typedef __SIZE_TYPE__ size_t;
#endif

#ifdef __need_ssize_t
#undef __need_ssize_t
typedef __INTPTR_TYPE__ ssize_t;
#endif

#ifdef __need_wchar_t
#undef __need_wchar_t
typedef __WCHAR_TYPE__ wchar_t;
#endif

#ifdef __need_ptrdiff_t
#undef __need_ptrdiff_t
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif

#ifdef __need_blkcnt_t
#undef __need_blkcnt_t
typedef long blkcnt_t;
#endif

#ifdef __need_blksize_t
#undef __need_blksize_t
typedef long blksize_t;
#endif

#ifdef __need_dev_t
#undef __need_dev_t
typedef int dev_t;
#endif

#ifdef __need_ino_t
#undef __need_ino_t
typedef int ino_t;
#endif

#ifdef __need_mode_t
#undef __need_mode_t
typedef int mode_t;
#endif

#ifdef __need_nlink_t
#undef __need_nlink_t
typedef int nlink_t;
#endif

#ifdef __need_uid_t
#undef __need_uid_t
typedef int uid_t;
#endif

#ifdef __need_gid_t
#undef __need_gid_t
typedef int gid_t;
#endif

#ifdef __need_off_t
#undef __need_off_t
typedef __INT64_TYPE__ off_t;
#endif

#include <norlit/header/end.h>
