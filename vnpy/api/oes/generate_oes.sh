#!/usr/bin/env bash

python -m autocxxpy generate \
    vnoes \
    oes_api/oes_api.h \
    mds_api/mds_api.h \
    -I vnoes/include \
    -I vnoes/include/oes \
    --output-dir vnoes/generated_files \
    --copy-autocxxpy-includes vnoes/include \
    --pyi-output-dir .\
    --no-clear-pyi-output-dir \
    --no-callback-pattern ".*" \
    --enforce-version 0.4.1

#####################################
# of unsupported functions: 5
# OesApi_SendBatchOrdersReq (OesApiSessionInfoT * pOrdChannel,const OesOrdReqT *[] ppOrdPtrList,int32 ordCount)
# OesApi_WaitOnChannelGroup (OesApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,void * pCallbackParams,OesApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnTcpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnTcpChannelGroupCompressible (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnUdpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
#####################################