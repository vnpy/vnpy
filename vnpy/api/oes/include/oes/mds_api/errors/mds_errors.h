/*
 * Copyright 2020 the original author or authors.
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
 * @file    mds_errors.h
 *
 * 通信接口错误信息定义
 *
 * @version 0.15.6.13   2018/07/16
 *          - 新增错误码定义
 *              - 1031, 非法的加密类型 (MDSERR_ILLEGAL_ENCRYPT_TYPE)
 *              - 1033, 无可用节点 (MDSERR_NO_AVAILABLE_NODE)
 * @version 0.15.7.6    2018/10/16
 *          - 新增错误码定义
 *              - 1035, 非法的产品类型 (MDSERR_ILLEGAL_PRODUCT_TYPE)
 * @version 0.15.8_RC3  2019/01/14
 *          - 调整错误描述
 *              - 1007, 非服务开放时间 (MDSERR_NOT_TRADING_TIME)
 *              - 1022, 尚不支持或尚未开通此业务 (MDSERR_NOT_SUPPORT)
 * @version 0.15.9      2019/03/18
 *          - 新增错误码定义
 *              - 1029, 密码未改变（MDSERR_PASSWORD_UNCHANGED）
 *              - 1030, 非法的来源分类（MDSERR_ILLEGAL_SOURCE_TYPE）
 *              - 1032, 非法的客户端设备序列号 (MDSERR_ILLEGAL_DRIVER)
 *              - 1034, 密码强度不足（MDSERR_PASSWORD_WEAK_STRENGTH）
 *              - 1036, 未通过黑白名单检查 (MDSERR_WBLIST_CHECK_FAILURE)
 *              - 1037, 集群编号不匹配 (MDSERR_SET_NUM_MISMATCH)
 *              - 1038, 无此操作权限 (MDSERR_NO_PERM)
 * @version 0.16        2019/01/18
 *
 * @since   2016/1/3
 */


#ifndef _MDS_PROTOCOL_ERRORS_H
#define _MDS_PROTOCOL_ERRORS_H


#include    <sutil/net/spk_errmsg_base_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 通信接口错误定义表
 */
extern  SErrMsgT __SPK_DLL_IMPORT               __ERRS_mdsApiErrors[];
/* -------------------------           */


/*
 * 通用错误定义
 */
/** 1001, 报文格式错误 */
#define MDSERR_MSG_FORMAT                       (&__ERRS_mdsApiErrors[0])
/** 1002, 当前主机不是主节点 */
#define MDSERR_NOT_LEADER                       (&__ERRS_mdsApiErrors[1])
/** 1003, 主存库操作失败 */
#define MDSERR_SDB_FAILURE                      (&__ERRS_mdsApiErrors[2])
/** 1004, 基础数据不匹配，无法更新数据 */
#define MDSERR_UPDATE_EPERM                     (&__ERRS_mdsApiErrors[3])
/** 1005, 功能尚不支持/协议版本不兼容 */
#define MDSERR_INCOMPATIBLE_PROTOCOL_VERSION    (&__ERRS_mdsApiErrors[4])
/** 1006, 数据不存在 */
#define MDSERR_NOT_FOUND                        (&__ERRS_mdsApiErrors[5])
/** 1007, 非服务开放时间 */
#define MDSERR_NOT_TRADING_TIME                 (&__ERRS_mdsApiErrors[6])
/** 1008, 非法的定位游标 */
#define MDSERR_ILLEGAL_POSITION                 (&__ERRS_mdsApiErrors[7])
/** 1009, 非法的客户端登录用户名称 */
#define MDSERR_ILLEGAL_CLIENT_NAME              (&__ERRS_mdsApiErrors[8])
/** 1010, 非法的证券代码 */
#define MDSERR_ILLEGAL_SECURITY_ID              (&__ERRS_mdsApiErrors[9])
/** 1011, 非法的客户代码 */
#define MDSERR_ILLEGAL_CUST_ID                  (&__ERRS_mdsApiErrors[10])
/** 1012, 非法的客户端类型 */
#define MDSERR_ILLEGAL_CLIENT_TYPE              (&__ERRS_mdsApiErrors[11])
/** 1013, 客户端已被禁用 */
#define MDSERR_CLIENT_DISABLED                  (&__ERRS_mdsApiErrors[12])
/** 1014, 客户端密码不正确 */
#define MDSERR_CLIENT_PASSWORD_INVALID          (&__ERRS_mdsApiErrors[13])
/** 1015, 客户端重复登录 */
#define MDSERR_CLIENT_REPEATED_LOGON            (&__ERRS_mdsApiErrors[14])
/** 1016, 客户端连接数量过多 */
#define MDSERR_CLIENT_CONNECTIONS_LIMIT         (&__ERRS_mdsApiErrors[15])
/** 1017, 客户端未经授权操作他人账户 */
#define MDSERR_CLIENT_NOT_AUTHORIZED            (&__ERRS_mdsApiErrors[16])
/** 1018, 数据超出修改范围 */
#define MDSERR_DATA_OUTOF_RANGE                 (&__ERRS_mdsApiErrors[17])
/** 1019, 非法的应用系统名称 */
#define MDSERR_ILLEGAL_APPNAME                  (&__ERRS_mdsApiErrors[18])
/** 1020, 请求条件有冲突 */
#define MDSERR_CONFLICT_REQ_CONDITION           (&__ERRS_mdsApiErrors[19])
/** 1021, 客户端IP/MAC地址格式错误 */
#define MDSERR_ILLEGAL_IP_MAC_FORMAT            (&__ERRS_mdsApiErrors[20])
/** 1022, 尚不支持或尚未开通此业务 */
#define MDSERR_NOT_SUPPORT                      (&__ERRS_mdsApiErrors[21])
/** 1026, 流量超出限制范围 */
#define MDSERR_TRAFFIC_CONTROL_OUTOF_RANGE      (&__ERRS_mdsApiErrors[25])
/** 1027, 禁止使用API登录 */
#define MDSERR_API_FORBIDDEN                    (&__ERRS_mdsApiErrors[26])
/** 1029, 密码未改变 */
#define MDSERR_PASSWORD_UNCHANGED               (&__ERRS_mdsApiErrors[28])
/** 1030, 非法的来源分类 */
#define MDSERR_ILLEGAL_SOURCE_TYPE              (&__ERRS_mdsApiErrors[29])
/** 1031, 非法的加密类型 */
#define MDSERR_ILLEGAL_ENCRYPT_TYPE             (&__ERRS_mdsApiErrors[30])
/** 1032, 非法的客户端设备序列号 */
#define MDSERR_ILLEGAL_DRIVER                   (&__ERRS_mdsApiErrors[31])
/** 1033, 无可用节点 */
#define MDSERR_NO_AVAILABLE_NODE                (&__ERRS_mdsApiErrors[32])
/** 1034, 密码强度不足 */
#define MDSERR_PASSWORD_WEAK_STRENGTH           (&__ERRS_mdsApiErrors[33])
/** 1035, 非法的产品类型 */
#define MDSERR_ILLEGAL_PRODUCT_TYPE             (&__ERRS_mdsApiErrors[34])
/** 1036, 未通过黑白名单检查 */
#define MDSERR_WBLIST_CHECK_FAILURE             (&__ERRS_mdsApiErrors[35])
/** 1037, 集群编号不匹配 */
#define MDSERR_SET_NUM_MISMATCH                 (&__ERRS_mdsApiErrors[36])
/** 1038, 无此操作权限 */
#define MDSERR_NO_PERM                          (&__ERRS_mdsApiErrors[37])
/* -------------------------           */


/*
 * MDS相关错误
 */
/** 1301, 行情订阅失败 */
#define MDSERR_SUBSCRIBE_FAILED                 (&__ERRS_mdsApiErrors[40])
/* -------------------------           */


#ifdef __cplusplus

}
#endif

#endif  /* _MDS_PROTOCOL_ERRORS_H */
