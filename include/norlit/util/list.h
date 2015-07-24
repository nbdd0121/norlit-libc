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

#ifndef _NORLIT_UTIL_LIST_H
#define _NORLIT_UTIL_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct str_list_t {
    struct str_list_t *prev;
    struct str_list_t *next;
} list_t;

static inline void list_empty(list_t *list) {
    list->prev = list->next = list;
}

#define container_of(list, str, name) ((str*)((size_t)list - offsetof(str, name)))

#define list_add list_addLast

static inline bool list_isEmpty(list_t *list) {
    return list->prev == list;
}

static inline void list_addFirst(list_t *list, list_t *inserted) {
    inserted->next = list->next;
    inserted->prev = list;
    list->next->prev = inserted;
    list->next = inserted;
}

static inline void list_addLast(list_t *list, list_t *inserted) {
    inserted->prev = list->prev;
    inserted->next = list;
    list->prev->next = inserted;
    list->prev = inserted;
}

static inline void list_remove(list_t *list) {
    list->prev->next = list->next;
    list->next->prev = list->prev;
}

#define list_forEach(list, var, str, name)\
    for (\
            list_t *__listHead = (list), *__listVar = __listHead->next, *__listNext = __listVar->next;\
            __listVar != __listHead && (var = container_of(__listVar, str, name));\
            __listVar = __listNext, __listNext = __listVar->next\
        )\

#define list_forEachInclusive(list, var, str, name)\
    for (\
            list_t *__listHead = (list), *__listVar = __listHead, *__listNext = __listVar->next;\
            __listNext && (var = container_of(__listVar, str, name));\
            __listVar = __listNext, __listNext = __listVar == __listHead ? NULL: __listVar->next\
        )\

#endif
