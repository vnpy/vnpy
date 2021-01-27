/*
 * Copyright 2009-2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    data_buffer_define.h
 *
 * 可动态分配的数据缓存
 *
 * @version 1.0 2008/12/1
 * @since   2008/12/1
 */


#ifndef _SPK_DATA_BUFFER_DEFINE_H
#define _SPK_DATA_BUFFER_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 最小缓存大小 */
#define SPK_MIN_DATA_BUFFER_SIZE        (4 * 1024)
/** 最大缓存大小 */
#define SPK_MAX_DATA_BUFFER_SIZE        (32 * 1024 * 1024)
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * 支持动态内存分配的数据缓存定义
 */
typedef struct _SDataBuffer {
    int32               dataSize;                       /**< 有效数据长度 */
    int32               const bufSize;                  /**< 缓存区总大小 */
    char                * const buffer;                 /**< 缓存区指针 */
    void                *__ref;                         /**< 反向引用指针 */
} SDataBufferT;


/**
 * 支持动态内存分配的数据缓存的结构体别名 (为了消除某些情况下的编译警告)
 */
struct _SDataBufferVar {
    int32               dataSize;                       /**< 有效数据长度 */
    int32               bufSize;                        /**< 缓存区总大小 */
    char                *buffer;                        /**< 缓存区指针 */
    void                *__ref;                         /**< 反向引用指针 */
};


/* 结构体初始化值定义 */
#define NULLOBJ_SPK_DATA_BUFFER                         \
        0, 0, (char*) NULL, NULL
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_DATA_BUFFER_DEFINE_H */
