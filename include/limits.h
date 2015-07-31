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

#ifndef _NORLIT_LIBC_LIMITS_H
#define _NORLIT_LIBC_LIMITS_H

#define CHAR_BIT        __CHAR_BIT__
#define SCHAR_MIN       (~__SCHAR_MAX__)
#define SCHAR_MAX       __SCHAR_MAX__
#define UCHAR_MAX       (2U*SCHAR_MAX+1)

#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN        0
#define CHAR_MAX        UCHAR_MAX
#else
#define CHAR_MIN        SCHAR_MIN
#define CHAR_MAX        SCHAR_MAX
#endif

#define MB_LEN_MAX      6
#define SHRT_MIN        (~SHRT_MAX)
#define SHRT_MAX        __SHRT_MAX__
#define USHRT_MAX       (2U*SHRT_MAX+1)
#define INT_MIN         (~INT_MAX)
#define INT_MAX         __INT_MAX__
#define UINT_MAX        (2U*INT_MAX+1)
#define LONG_MIN        (~LONG_MAX)
#define LONG_MAX        __LONG_MAX__
#define ULONG_MAX       (2UL*LONG_MAX+1)
#define LLONG_MIN       (~LLONG_MAX)
#define LLONG_MAX       __LLONG_MAX__
#define ULLONG_MAX      (2ULL*LLONG_MAX+1)

#endif
