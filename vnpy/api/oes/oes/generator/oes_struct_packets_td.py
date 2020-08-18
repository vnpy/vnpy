OesReportSynchronizationReqT = {
    "lastRptSeqNum": "int64",
    "subscribeEnvId": "int8",
    "__filler": "uint8",
    "subscribeRptTypes": "int32",
}
OesReportSynchronizationRspT = {
    "lastRptSeqNum": "int64",
    "subscribeEnvId": "int8",
    "__filler": "uint8",
    "subscribeRptTypes": "int32",
}
OesTestRequestReqT = {
    "testReqId": "string",
    "sendTime": "string",
    "__filler": "string",
}
OesTestRequestRspT = {
    "testReqId": "string",
    "origSendTime": "string",
    "__filler1": "string",
    "respTime": "string",
    "__filler2": "string",
    "__recvTime": "STimeval32T",
    "__collectedTime": "STimeval32T",
    "__pushingTime": "STimeval32T",
}
OesChangePasswordReqT = {
    "encryptMethod": "int32",
    "__filler": "int32",
    "username": "string",
}
OesChangePasswordRspT = {
    "encryptMethod": "int32",
    "__filler": "int32",
    "username": "string",
}
OesBatchOrdersHeadT = {
    "itemCount": "int32",
    "__filler": "int32",
}
OesBatchOrdersReqT = {
    "batchHead": "dict",
    "items": "dict",
}
OesOptSettlementConfirmReqT = {
    "custId": "string",
}
OesRptMsgHeadT = {
}
OesRptMsgT = {
}
