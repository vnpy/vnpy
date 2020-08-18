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
 * @file    spk_string_var.h
 *
 * 字符串变量处理, 用于替换字符串(如, 配置信息等)中的字符串变量
 * 以字符'@'起始的字符串变量被作为应用内部预定义变量处理
 * 以字符'$'起始的字符串变量被作为上下文环境变量和系统预定义变量处理（优先使用内部预定义变量）
 *
 * 支持如下样式的字符串变量:
 * - ${var}
 * - ${var=string}  Use string and assign string to var
 * - ${var:-string} Use var if set, otherwise use string
 * - ${var:=string} Use var if set, otherwise use string and assign string to var
 * - ${var:+string} Use string if var if set, otherwise use nothing
 * - ${var:!string} Use string if var if unset, otherwise use nothing
 *
 * 以及字符串变量的嵌套如:
 * - ${VAR:=${VAR2:+string_${VAR3:-string}_string}}
 *
 * @version 1.1 2015/04/10
 * @since   2012/01/05
 */


#ifndef _SPK_STRING_VAR_H
#define _SPK_STRING_VAR_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定义
 */
#define STRVAR_MAX_NAME_LENGTH      (128)       /**< 宏名称最大长度 */
#define STRVAR_PREFIX_MIXED         '$'
#define STRVAR_PREFIX_BUILDIN       '@'
#define STRVAR_LEFT_BOUND           '{'
#define STRVAR_RIGHT_BOUND          '}'
#define STRVAR_MIDDLE_BOUND         ':'
/* -------------------------           */


/*
 * 字符串变量取值函数原型定义
 */

/**
 * 字符串变量取值函数原型
 */
typedef const char* (*F_STRVAR_GETTER_T) (void);

/**
 * 可接受参数的宏取值函数原型
 */
typedef void (*F_STRVAR_SETTER_T) (const char *pValue);
/* -------------------------           */


/**
 * 预定义的字符串变量定义结构
 *
 */
typedef struct _SStrVar {
    /** 字符串变量名称 */
    char                name[STRVAR_MAX_NAME_LENGTH];

    /** 字符串变量取值函数 */
    F_STRVAR_GETTER_T   pValueGetter;

    /** 字符串变量设置函数 */
    F_STRVAR_SETTER_T   pValueSetter;
} SStrVarT;


/* 结构体初始化值定义 */
#define NULLOBJ_SSTR_VAR                \
        {0}, 0, 0
/* -------------------------           */


/*
 * 函数声明
 */

/* 通过变量名称返回字符串变量定义 */
const SStrVarT*
        SStr_GetVarItemByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName);

/* 通过变量名称返回字符串变量的值 */
const char*
        SStr_GetVarValueByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName,
                BOOL isSystemEnvAble);

/* 设置字符串变量的值 */
void    SStr_SetVarValueByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName,
                const char *pVarValue,
                BOOL isSystemEnvAble);

/* 替换所有的字符串变量 */
char*   SStr_ReplaceAllVar(
                char *pBuf,
                int32 maxStrlen,
                const char *pTarget);

/* 替换所有的字符串变量 */
char*   SStr_ReplaceAllVar2(
                char *pBuf,
                int32 maxStrlen,
                const char *pTarget,
                const SStrVarT *pVarItems,
                int32 varItemsNumber);

/* 替换所有的字符串变量 */
char*   SStr_ReplaceAllVar3(
                char *pBuf,
                int32 maxStrlen,
                const char *pTarget,
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                BOOL isSystemEnvAble);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRING_VAR_H */
