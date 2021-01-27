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
 * @file    spk_strverscmp.h
 *
 * strverscmp函数的简化版本
 *
 * @version 1.0 2016/11/24
 * @since   2016/11/24
 */


#ifndef _SPK_STRVERSCMP_H
#define _SPK_STRVERSCMP_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * Compare S1 and S2 as strings holding indices/version numbers,
 * returning less than, equal to or greater than zero if S1 is less than,
 * equal to or greater than S2
 */
int32   SStr_Strverscmp(const char *s1, const char *s2);

/*
 * 将字符串类型的版本号转换为整数形式的版本号数值
 * - 版本号数值的格式为 10 位整型数值, 形如: 1AABBCCDD0, 其中:
 *   - 第一位固定为 1
 *   - AA 为主版本号
 *   - BB 为副版本号
 *   - CC 为发布号
 *   - DD 为构建号
 *   - 最后一位固定为 0
 */
int32   SStr_GetIntVersion(const char *pStr);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRVERSCMP_H */
