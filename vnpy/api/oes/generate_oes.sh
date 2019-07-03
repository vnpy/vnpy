#!/usr/bin/env bash

script_autocxxpy_version="autocxxpy 0.4.0"
autocxxpy_version=`python -m autocxxpy version`
if [[ $autocxxpy_version != $script_autocxxpy_version ]]; then
    echo "autocxxpy version not match!"
    echo "current: " $autocxxpy_version
    echo "script: " $script_autocxxpy_version
    echo "to continue, change version of autocxxpy or modify this script."
    exit 1
fi
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
    --no-callback-pattern ".*"

#####################################
# of unsupported functions: 5
# OesApi_SendBatchOrdersReq (OesApiSessionInfoT * pOrdChannel,const OesOrdReqT *[] ppOrdPtrList,int32 ordCount)
# OesApi_WaitOnChannelGroup (OesApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,void * pCallbackParams,OesApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnTcpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnTcpChannelGroupCompressible (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
# MdsApi_WaitOnUdpChannelGroup (MdsApiChannelGroupT * pChannelGroup,int32 timeoutMs,F_MDSAPI_ONMSG_T pOnMsgCallback,void * pCallbackParams,MdsApiSessionInfoT ** ppFailed)
#####################################