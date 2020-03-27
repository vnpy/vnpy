TapAPIApplicationInfo = {
    "AuthCode": "string",
    "KeyOperationLogPath": "string",
}

TapAPICommodity = {
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
}

TapAPIContract = {
    "Commodity": "dict",
    "ContractNo1": "string",
    "StrikePrice1": "string",
    "CallOrPutFlag1": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
}

TapAPIExchangeInfo = {
    "ExchangeNo": "string",
    "ExchangeName": "string",
}

TapAPIChangePasswordReq = {
    "OldPassword": "string",
    "NewPassword": "string",
}

