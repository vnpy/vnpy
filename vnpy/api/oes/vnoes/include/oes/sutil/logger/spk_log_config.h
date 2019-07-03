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
 * @file    spk_log_config.h
 *
 * 日志配置文件解析处理头文件(非线程安全)
 *
 * @version $Id$
 * @since   2005.10.31
 */


#ifndef _SPK_LOG_CONFIG_H
#define _SPK_LOG_CONFIG_H


#include    <sutil/types.h>
#include    <sutil/logger/spk_log_type.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_mode.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定义
 */
/** 最大的日志配置数量 */
#define     SLOGCFG_MAX_CONFIG_COUNT            (32)
/** 最大的日志记录器数量 */
#define     SLOGCFG_MAX_APPENDER_NUMBER         (16)
/* -------------------------           */


/*
 * 日志默认配置定义
 */
#define     SLOGCFG_DEFAULT_MIN_LOG_LEVEL       SLOG_LEVEL_TRACE
#define     SLOGCFG_DEFAULT_MAX_LOG_LEVEL       SLOG_LEVEL_FATAL
#define     SLOGCFG_DEFAULT_MAX_FILE_LENGTH     (300)
#define     SLOGCFG_DEFAULT_MAX_BACKUP_COUNT    (3)
#define     SLOGCFG_MAX_BACKUP_COUNT            (1000)
#define     SLOGCFG_DEFAULT_ASYNC_QUEUE_SIZE    (1000)
#define     SLOGCFG_DEFAULT_ASYNC_SHM_ID        (0)
#define     SLOGCFG_MAX_SECTION_LENGTH          (64)
/* -------------------------           */


/*
 * 配置文件常量定义
 */
/** 默认的日志根配置区段 */
#define     SLOGCFG_KEY_DEFAULT_ROOT_SECTION    "log"

/** 默认的日志根配置 */
#define     SLOGCFG_KEY_DEFAULT_ROOT_CATEGORY   "log.root_category"

/** 多值域的域分隔符 */
#define     SLOGCFG_MULTI_VALUE_DELIMITER       ","
/* -------------------------           */


/*
 * 结构体定义
 */

/**
 * 日志配置信息结构
 */
typedef struct _SLogCfgItem {
    /** 日志配置区段名称 */
    char                logSection[SLOGCFG_MAX_SECTION_LENGTH];

    /** 日志模式 */
    char                logMode[SLOG_MAX_MODE_NAME];
    /** 日志登记的起始级别 */
    char                minLogLevel[SLOG_MAX_LEVEL_NAME];
    /** 日志登记的最高级别 */
    char                maxLogLevel[SLOG_MAX_LEVEL_NAME];
    /** 日志文件名称 */
    char                logFile[SPK_MAX_PATH_LEN];

    /**
     * 日志文件最大长度
     * - 日志文件最大长度允许配置为0, 表示无最大长度限制
     * - 如果配置值小于 2048 则以兆为单位计算, 否则以字节为单位计算, 最大文件长度为2GB
     */
    int32               maxFileLength;
    /** 日志文件最大备份数 */
    int32               maxBackupCount;

    /** 异步日志的消息队列大小 */
    int32               asyncQueueSize;
    /** 异步日志的共享内存ID (0 表示使用默认值) */
    int32               asyncQueueShmId;
} SLogCfgItemT;


/* 结构体初始化值定义 */
#define NULLOBJ_LOG_CFG_ITEM                    \
        {0}, {0}, {0}, {0}, {0}, \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * 日志配置区段
 */
typedef struct _SLogCfgSectionInfo {
    /** 日志配置的区段名称 */
    char        section[SLOGCFG_MAX_SECTION_LENGTH];
} SLogCfgSectionInfoT;
/* -------------------------           */


/*
 * 函数声明
 */

/*
 * 尝试加载所有的日志配置区段
 */
int32   SLogCfg_LoadAllConfig(
                const char *pConfigFile,
                SLogCfgItemT *pOutLogConfigList,
                int32 maxLogConfigCount);

/*
 * 解析日志配置信息, 读取相关的日志分类列表，并加载所有的日志配置区段
 */
int32   SLogCfg_LoadAllConfigAndCategoryList(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pRootCategoryField,
                SLogCfgItemT *pOutLogConfigList,
                int32 *pLogConfigCount,
                SLogCfgSectionInfoT *pOutLogSectionList,
                int32 *pLogSectionCount,
                const SLogLevelT **ppOutAllowableMinLogLevel);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_CONFIG_H */
