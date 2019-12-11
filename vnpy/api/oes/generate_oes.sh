#!/usr/bin/env bash

c2py generate \
    vnoes \
    oes_api/oes_api.h \
    mds_api/mds_api.h \
    -I vnoes/include \
    -I vnoes/include/oes \
    --output-dir vnoes/generated_files \
    --copy-c2py-includes vnoes/include \
    --pyi-output-dir .\
    --no-clear-pyi-output-dir \
    --no-callback-pattern ".*" \
    --ignore-pattern ".*(spk_struct|STimeval).*" \
    --enforce-version 0.5.4

#####################################
## of unsupported functions: 5
#OesApi_SendBatchOrdersReq (OesApiSessionInfoT * pOrdChannel,const OesOrdReqT *[] ppOrdPtrList,int32 ordCount)
#OesApi_WaitOnChannelGroup (OesApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,void * pCallbackParams,OesApiSessionInfoT ** ppFailed)
#MdsApi_WaitOnTcpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
#MdsApi_WaitOnTcpChannelGroupCompressible (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
#MdsApi_WaitOnUdpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
## of ignore: 17
#_spk_struct_timespec::tv_sec
#_spk_struct_timespec::tv_nsec
#_spk_struct_timespec
#_spk_struct_timezone::tz_minuteswest
#_spk_struct_timezone::tz_dsttime
#_spk_struct_timezone
#_spk_struct_iovec::iov_base
#_spk_struct_iovec::iov_len
#_spk_struct_iovec
#_spk_struct_timeval32::tv_sec
#_spk_struct_timeval32::tv_usec
#_spk_struct_timeval32
#_spk_struct_timeval64::tv_sec
#_spk_struct_timeval64::tv_usec
#_spk_struct_timeval64
#STimeval32T
#STimeval64T
