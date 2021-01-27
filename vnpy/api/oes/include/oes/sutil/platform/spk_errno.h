/*
 * Copyright 2009-2018 the original author or authors.
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
 * @file    spk_errno.h
 *
 * 系统错误信息定义
 *
 * @version 1.0 2018/8/27
 * @since   2018/8/27
 */


#ifndef _SPK_ERRNO_H
#define _SPK_ERRNO_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函数声明
 * =================================================================== */

/*
 * 初始化系统错误列表信息
 */
BOOL    SpkErrno_InitErrorList(void);

/*
 * 返回错误码对应的错误信息
 *
 * @param   errCode      错误编码
 * @return  错误码对应的错误信息
 */
const char *
        SpkErrno_Strerror(int32 errCode);
/* -------------------------           */


#ifdef __cplusplus

}
#endif

#endif  /* _SPK_ERRNO_H */
