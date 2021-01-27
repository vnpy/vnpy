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
 * @file    spk_fixed_snprintf.h
 *
 * 支持以定长的方式输出的 snprintf 函数
 * add flags '!', to output with fixed field len
 *
 * @version 1.0 2016/11/20
 * @since   2008/01/22
 */


#ifndef _SPK_FIXED_SNPRINTF_H
#define _SPK_FIXED_SNPRINTF_H


#include    <sutil/types.h>
#include    <stdarg.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 函数原型
 */
int     SStr_Snprintf(char *str, size_t count, const char *fmt, ...);
int     SStr_VSnprintf(char *str, size_t count, const char *fmt, va_list args);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_FIXED_SNPRINTF_H */
