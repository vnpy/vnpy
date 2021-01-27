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
 * @file    errmsg_base_define.h
 *
 * 基础通信接口错误信息定义
 *
 * @version 1.0 2008/7/16
 * @since   2004.12.23
 */


#ifndef _SPK_ERRMSG_BASE_DEFINE_H
#define _SPK_ERRMSG_BASE_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 错误信息的最大长度 */
#define SPK_MAX_ERRMSG_LEN                  (96)
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * 通信接口错误信息结构体定义
 */
typedef struct _SErrMsg {
    int16           __index;                /**< 序号, 为方便识别而设 */
    uint8           MODULE;                 /**< 模块代码 (取值范围: 0~99) */
    uint8           CODE;                   /**< 明细错误号 (取值范围: 0~99) */
    uint16          __errCode;              /**< 合并后的错误编号 (自动计算) */
    int16           __msgSize;              /**< 错误信息长度 (自动计算) */

    /** 错误信息 */
    char            MSG[SPK_MAX_ERRMSG_LEN];
} SErrMsgT;


/* 结构体初始化值定义 */
#define NULLOBJ_SPK_ERRMSG                  \
        0, 0, 0, 0, 0, \
        {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_ERRMSG_BASE_DEFINE_H */
