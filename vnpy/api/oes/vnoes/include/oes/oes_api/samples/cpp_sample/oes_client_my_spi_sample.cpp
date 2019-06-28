/*
 * Copyright 2016 the original author or authors.
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
 * @file    oes_client_my_spi_sample.c
 *
 * OES API接口库的CPP风格客户端示例。客户需要实现自己的SPI定义
 *
 * @version 1.0 2017/08/24
 * @since   2017/08/24
 */


#include    <iostream>
#include    "oes_client_my_spi_sample.h"


/* 委托业务拒绝回报 */
void
OesClientMySpi::OnBusinessReject(int32 errorCode, const OesOrdRejectT *pOrderReject) {
    fprintf(stdout, ">>> 收到委托业务拒绝回报: " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "客户委托流水号[%d], 证券账户[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 委托类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 委托数量[%d], 委托价格[%d], " \
            "原始委托的客户订单编号[%" __SPK_FMT_LL__ "d], 错误码[%d]\n",
            pOrderReject->clEnvId, pOrderReject->clSeqNo,
            pOrderReject->invAcctId, pOrderReject->securityId,
            pOrderReject->mktId, pOrderReject->ordType,
            pOrderReject->bsType, pOrderReject->ordQty,
            pOrderReject->ordPrice, pOrderReject->origClOrdId, errorCode);
}


/* 委托已收回报 */
void
OesClientMySpi::OnOrderInsert(const OesOrdCnfmT *pOrderInsert) {
    fprintf(stdout, ">>> 收到委托已收回报: " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "会员内部编号[%" __SPK_FMT_LL__ "d], 证券账户[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 订单类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 委托状态[%" __SPK_FMT_HH__ "u], " \
            "委托日期[%d], 委托接收时间[%d], 委托确认时间[%d], " \
            "委托数量[%d], 委托价格[%d], 撤单数量[%d], 累计成交份数[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易佣金[%" __SPK_FMT_LL__ "d], 冻结交易金额[%" __SPK_FMT_LL__ "d], " \
            "冻结债券利息[%" __SPK_FMT_LL__ "d], 冻结交易佣金[%" __SPK_FMT_LL__ "d], " \
            "被撤内部委托编号[%" __SPK_FMT_LL__ "d], 拒绝原因[%d], 交易所错误码[%d]\n",
            pOrderInsert->clEnvId, pOrderInsert->clSeqNo,
            pOrderInsert->clOrdId, pOrderInsert->invAcctId,
            pOrderInsert->securityId, pOrderInsert->mktId,
            pOrderInsert->ordType, pOrderInsert->bsType,
            pOrderInsert->ordStatus, pOrderInsert->ordDate,
            pOrderInsert->ordTime, pOrderInsert->ordCnfmTime,
            pOrderInsert->ordQty, pOrderInsert->ordPrice,
            pOrderInsert->canceledQty, pOrderInsert->cumQty,
            pOrderInsert->cumAmt, pOrderInsert->cumInterest,
            pOrderInsert->cumFee, pOrderInsert->frzAmt,
            pOrderInsert->frzInterest, pOrderInsert->frzFee,
            pOrderInsert->origClOrdId, pOrderInsert->ordRejReason,
            pOrderInsert->exchErrCode);
}


/* 委托确认回报 */
void
OesClientMySpi::OnOrderReport(int32 errorCode, const OesOrdCnfmT *pOrderReport) {
    fprintf(stdout, ">>> 收到委托回报: " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "会员内部编号[%" __SPK_FMT_LL__ "d], 证券账户[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 订单类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 委托状态[%" __SPK_FMT_HH__ "u], " \
            "委托日期[%d], 委托接收时间[%d], 委托确认时间[%d], "
            "委托数量[%d], 委托价格[%d], 撤单数量[%d], 累计成交份数[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易佣金[%" __SPK_FMT_LL__ "d], 冻结交易金额[%" __SPK_FMT_LL__ "d], " \
            "冻结债券利息[%" __SPK_FMT_LL__ "d], 冻结交易佣金[%" __SPK_FMT_LL__ "d], " \
            "被撤内部委托编号[%" __SPK_FMT_LL__ "d], 拒绝原因[%d], 交易所错误码[%d]\n",
            pOrderReport->clEnvId, pOrderReport->clSeqNo,
            pOrderReport->clOrdId, pOrderReport->invAcctId,
            pOrderReport->securityId, pOrderReport->mktId,
            pOrderReport->ordType, pOrderReport->bsType,
            pOrderReport->ordStatus, pOrderReport->ordDate,
            pOrderReport->ordTime, pOrderReport->ordCnfmTime,
            pOrderReport->ordQty, pOrderReport->ordPrice,
            pOrderReport->canceledQty, pOrderReport->cumQty,
            pOrderReport->cumAmt, pOrderReport->cumInterest,
            pOrderReport->cumFee, pOrderReport->frzAmt,
            pOrderReport->frzInterest, pOrderReport->frzFee,
            pOrderReport->origClOrdId, pOrderReport->ordRejReason,
            pOrderReport->exchErrCode);
}


/* 成交回报 */
void
OesClientMySpi::OnTradeReport(const OesTrdCnfmT *pTradeReport) {
    fprintf(stdout, ">>> 收到成交回报: " \
            "成交编号[%" __SPK_FMT_LL__ "d], 会员内部编号[%" __SPK_FMT_LL__ "d], " \
            "委托客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "证券账户[%s], 证券代码[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "买卖方向[%" __SPK_FMT_HH__ "u], 委托买卖类型[%" __SPK_FMT_HH__ "u], "
            "成交日期[%d], 成交时间[%d], 成交数量[%d], 成交价格[%d], " \
            "成交金额[%" __SPK_FMT_LL__ "d], 累计成交数量[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易费用[%" __SPK_FMT_LL__ "d], PBU代码[%d]\n",
            pTradeReport->exchTrdNum, pTradeReport->clOrdId,
            pTradeReport->clEnvId, pTradeReport->clSeqNo,
            pTradeReport->invAcctId, pTradeReport->securityId,
            pTradeReport->mktId, pTradeReport->trdSide,
            pTradeReport->ordBuySellType, pTradeReport->trdDate,
            pTradeReport->trdTime, pTradeReport->trdQty, pTradeReport->trdPrice,
            pTradeReport->trdAmt, pTradeReport->cumQty, pTradeReport->cumAmt,
            pTradeReport->cumInterest, pTradeReport->cumFee,
            pTradeReport->pbuId);
}


/* 资金变动回报 */
void
OesClientMySpi::OnCashAssetVariation(const OesCashAssetItemT *pCashAssetItem) {
    fprintf(stdout, ">>> 收到资金变动回报: " \
            "资金账户代码[%s], 客户代码[%s], " \
            "币种[%" __SPK_FMT_HH__ "u], " \
            "资金类型[%" __SPK_FMT_HH__ "u], " \
            "资金账户状态[%" __SPK_FMT_HH__ "u], " \
            "期初余额[%" __SPK_FMT_LL__ "d], " \
            "期初可用余额[%" __SPK_FMT_LL__ "d], " \
            "期初可取余额[%" __SPK_FMT_LL__ "d], " \
            "不可用余额[%" __SPK_FMT_LL__ "d], " \
            "累计存入金额[%" __SPK_FMT_LL__ "d], " \
            "累计提取金额[%" __SPK_FMT_LL__ "d], " \
            "当前提取冻结金额[%" __SPK_FMT_LL__ "d], " \
            "累计卖金额[%" __SPK_FMT_LL__ "d], " \
            "累计买金额[%" __SPK_FMT_LL__ "d], " \
            "当前买冻结金额[%" __SPK_FMT_LL__ "d], " \
            "累计费用金额[%" __SPK_FMT_LL__ "d], " \
            "当前费用冻结金额[%" __SPK_FMT_LL__ "d], " \
            "当前维持保证金金额[%" __SPK_FMT_LL__ "d], " \
            "当前保证金冻结金额[%" __SPK_FMT_LL__ "d], " \
            "当前余额[%" __SPK_FMT_LL__ "d], " \
            "当前可用余额[%" __SPK_FMT_LL__ "d], " \
            "当前可取余额[%" __SPK_FMT_LL__ "d]\n",
            pCashAssetItem->cashAcctId, pCashAssetItem->custId,
            pCashAssetItem->currType, pCashAssetItem->cashType,
            pCashAssetItem->cashAcctStatus, pCashAssetItem->beginningBal,
            pCashAssetItem->beginningAvailableBal,
            pCashAssetItem->beginningDrawableBal,
            pCashAssetItem->disableBal, pCashAssetItem->totalDepositAmt,
            pCashAssetItem->totalWithdrawAmt, pCashAssetItem->withdrawFrzAmt,
            pCashAssetItem->totalSellAmt, pCashAssetItem->totalBuyAmt,
            pCashAssetItem->buyFrzAmt, pCashAssetItem->totalFeeAmt,
            pCashAssetItem->feeFrzAmt, pCashAssetItem->marginAmt,
            pCashAssetItem->marginFrzAmt, pCashAssetItem->currentTotalBal,
            pCashAssetItem->currentAvailableBal,
            pCashAssetItem->currentDrawableBal);
}


/* 持仓变动回报 */
void
OesClientMySpi::OnStockHoldingVariation(const OesStkHoldingItemT *pStkHoldingItem) {
    fprintf(stdout, ">>> 收到持仓变动回报: " \
            "证券账户[%s], 产品代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "日初持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计买入持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计卖出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前卖出冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "手动冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换获得持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换付出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前转换付出冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "当前已锁定持仓[%" __SPK_FMT_LL__ "d], " \
            "当前锁定冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "当前解锁定冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "当前备兑冻结的现货持仓[%" __SPK_FMT_LL__ "d], " \
            "当前已备兑使用的现货持仓[%" __SPK_FMT_LL__ "d], " \
            "日初总持仓成本[%" __SPK_FMT_LL__ "d], " \
            "当日累计买入金额[%" __SPK_FMT_LL__ "d], " \
            "当日累计卖出金额[%" __SPK_FMT_LL__ "d], " \
            "当日累计买入费用[%" __SPK_FMT_LL__ "d], " \
            "当日累计卖出费用[%" __SPK_FMT_LL__ "d], " \
            "持仓成本价[%" __SPK_FMT_LL__ "d], " \
            "当前总持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可卖持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可转换付出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可备兑/解锁持仓[%" __SPK_FMT_LL__ "d]\n",
            pStkHoldingItem->invAcctId, pStkHoldingItem->securityId,
            pStkHoldingItem->mktId, pStkHoldingItem->originalHld,
            pStkHoldingItem->totalBuyHld, pStkHoldingItem->totalSellHld,
            pStkHoldingItem->sellFrzHld, pStkHoldingItem->manualFrzHld,
            pStkHoldingItem->totalTrsfInHld, pStkHoldingItem->totalTrsfOutHld,
            pStkHoldingItem->trsfOutFrzHld, pStkHoldingItem->lockHld,
            pStkHoldingItem->lockFrzHld, pStkHoldingItem->unlockFrzHld,
            pStkHoldingItem->coveredFrzHld, pStkHoldingItem->coveredHld,
            pStkHoldingItem->originalCostAmt, pStkHoldingItem->totalBuyAmt,
            pStkHoldingItem->totalSellAmt, pStkHoldingItem->totalBuyFee,
            pStkHoldingItem->totalSellFee, pStkHoldingItem->costPrice,
            pStkHoldingItem->sumHld, pStkHoldingItem->sellAvlHld,
            pStkHoldingItem->trsfOutAvlHld, pStkHoldingItem->lockAvlHld,
            pStkHoldingItem->coveredAvlHld);
}


/* 出入金委托拒绝回报 */
void
OesClientMySpi::OnFundTrsfReject(int32 errorCode,
        const OesFundTrsfRejectT *pFundTrsfReject) {
    fprintf(stdout, ">>> 收到出入金委托拒绝回报: " \
            "错误码[%d], 错误信息[%s], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "出入金流水号[%d], 资金账户[%s], " \
            "是否仅调拨[%" __SPK_FMT_HH__ "u], " \
            "出入金方向[%" __SPK_FMT_HH__ "u], " \
            "出入金金额[%" __SPK_FMT_LL__ "d]\n",
            pFundTrsfReject->rejReason,pFundTrsfReject->errorInfo,
            pFundTrsfReject->clEnvId, pFundTrsfReject->clSeqNo,
            pFundTrsfReject->cashAcctId, pFundTrsfReject->isAllotOnly,
            pFundTrsfReject->direct, pFundTrsfReject->occurAmt);
}


/* 出入金委托执行回报 */
void
OesClientMySpi::OnFundTrsfReport(int32 errorCode,
        const OesFundTrsfReportT *pFundTrsfReport) {
    fprintf(stdout, ">>> 收到出入金委托执行回报: " \
            "错误原因[%d], 主柜错误码[%d], 错误信息[%s], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "出入金流水号[%d], 出入金编号[%d], 资金账户[%s], " \
            "是否仅调拨[%" __SPK_FMT_HH__ "u], " \
            "出入金方向[%" __SPK_FMT_HH__ "u], " \
            "出入金金额[%" __SPK_FMT_LL__ "d], " \
            "出入金状态[%d], 接收日期[%08d], " \
            "接收时间[%09d], 上报时间[%09d], 完成时间[%09d]\n",
            pFundTrsfReport->rejReason, pFundTrsfReport->counterErrCode,
            pFundTrsfReport->errorInfo, pFundTrsfReport->clEnvId,
            pFundTrsfReport->clSeqNo, pFundTrsfReport->fundTrsfId,
            pFundTrsfReport->cashAcctId, pFundTrsfReport->isAllotOnly,
            pFundTrsfReport->direct, pFundTrsfReport->occurAmt,
            pFundTrsfReport->trsfStatus, pFundTrsfReport->operDate,
            pFundTrsfReport->operTime, pFundTrsfReport->dclrTime,
            pFundTrsfReport->doneTime);
}


/* 市场状态信息 */
void
OesClientMySpi::OnMarketState(const OesMarketStateItemT *pMarketStateItem) {
    fprintf(stdout, ">>> 收到市场状态信息: " \
            "交易所代码[%hhu], 交易平台类型[%hhu], 市场类型[%hhu], "
            "市场状态[%hhu]\n",
            pMarketStateItem->exchId, pMarketStateItem->platformId,
            pMarketStateItem->mktId, pMarketStateItem->mktState);
}


/* 查询到委托信息回调 */
void
OesClientMySpi::OnQueryOrder(const OesOrdItemT *pOrder,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到委托信息: index[%d], isEnd[%c], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "会员内部编号[%" __SPK_FMT_LL__ "d], 证券账户[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 订单类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 委托状态[%" __SPK_FMT_HH__ "u], " \
            "委托日期[%d], 委托接收时间[%d], 委托确认时间[%d], " \
            "委托数量[%d], 委托价格[%d], 撤单数量[%d], 累计成交份数[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易佣金[%" __SPK_FMT_LL__ "d], 冻结交易金额[%" __SPK_FMT_LL__ "d], " \
            "冻结债券利息[%" __SPK_FMT_LL__ "d], 冻结交易佣金[%" __SPK_FMT_LL__ "d], " \
            "被撤内部委托编号[%" __SPK_FMT_LL__ "d], 拒绝原因[%d], " \
            "交易所错误码[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pOrder->clEnvId, pOrder->clSeqNo, pOrder->clOrdId,
            pOrder->invAcctId, pOrder->securityId, pOrder->mktId,
            pOrder->ordType, pOrder->bsType, pOrder->ordStatus,
            pOrder->ordDate, pOrder->ordTime, pOrder->ordCnfmTime,
            pOrder->ordQty, pOrder->ordPrice, pOrder->canceledQty,
            pOrder->cumQty, pOrder->cumAmt, pOrder->cumInterest,
            pOrder->cumFee, pOrder->frzAmt, pOrder->frzInterest,
            pOrder->frzFee, pOrder->origClOrdId, pOrder->ordRejReason,
            pOrder->exchErrCode);
}


/* 查询到成交信息回调 */
void
OesClientMySpi::OnQueryTrade(const OesTrdItemT *pTrade,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到成交信息: index[%d], isEnd[%c], " \
            "成交编号[%" __SPK_FMT_LL__ "d], 会员内部编号[%" __SPK_FMT_LL__ "d], " \
            "委托客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "证券账户[%s], 证券代码[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "买卖方向[%" __SPK_FMT_HH__ "u], 委托买卖类型[%" __SPK_FMT_HH__ "u], " \
            "成交日期[%d], 成交时间[%d], 成交数量[%d], 成交价格[%d], " \
            "成交金额[%" __SPK_FMT_LL__ "d], 累计成交数量[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易费用[%" __SPK_FMT_LL__ "d], PBU代码[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pTrade->exchTrdNum, pTrade->clOrdId, pTrade->clEnvId,
            pTrade->clSeqNo, pTrade->invAcctId, pTrade->securityId,
            pTrade->mktId, pTrade->trdSide, pTrade->ordBuySellType,
            pTrade->trdDate, pTrade->trdTime, pTrade->trdQty, pTrade->trdPrice,
            pTrade->trdAmt, pTrade->cumQty, pTrade->cumAmt, pTrade->cumInterest,
            pTrade->cumFee, pTrade->pbuId);
}


/* 查询到资金信息回调 */
void
OesClientMySpi::OnQueryCashAsset(const OesCashAssetItemT *pCashAsset,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到资金信息: index[%d], isEnd[%c], " \
            "资金账户代码[%s], 客户代码[%s], 币种[%" __SPK_FMT_HH__ "u], " \
            "资金类型[%" __SPK_FMT_HH__ "u], 期初余额[%" __SPK_FMT_LL__ "d], " \
            "期初可用[%" __SPK_FMT_LL__ "d], 期初可取[%" __SPK_FMT_LL__ "d], " \
            "不可用[%" __SPK_FMT_LL__ "d], 累计存入[%" __SPK_FMT_LL__ "d], " \
            "累计提取[%" __SPK_FMT_LL__ "d], 当前提取冻结[%" __SPK_FMT_LL__ "d], " \
            "累计卖出[%" __SPK_FMT_LL__ "d], 累计买入[%" __SPK_FMT_LL__ "d], " \
            "当前买冻结[%" __SPK_FMT_LL__ "d], 累计费用[%" __SPK_FMT_LL__ "d], " \
            "当前费用冻结[%" __SPK_FMT_LL__ "d], 当前维持保证金[%" __SPK_FMT_LL__ "d], " \
            "当前保证金冻结[%" __SPK_FMT_LL__ "d], 当前余额[%" __SPK_FMT_LL__ "d], " \
            "当前可用[%" __SPK_FMT_LL__ "d], 当前可取[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pCashAsset->cashAcctId, pCashAsset->custId, pCashAsset->currType,
            pCashAsset->cashType, pCashAsset->beginningBal,
            pCashAsset->beginningAvailableBal, pCashAsset->beginningDrawableBal,
            pCashAsset->disableBal, pCashAsset->totalDepositAmt,
            pCashAsset->totalWithdrawAmt, pCashAsset->withdrawFrzAmt,
            pCashAsset->totalSellAmt, pCashAsset->totalBuyAmt,
            pCashAsset->buyFrzAmt, pCashAsset->totalFeeAmt,
            pCashAsset->feeFrzAmt, pCashAsset->marginAmt,
            pCashAsset->marginFrzAmt, pCashAsset->currentTotalBal,
            pCashAsset->currentAvailableBal, pCashAsset->currentDrawableBal);
}


/* 查询到持仓信息回调 */
void
OesClientMySpi::OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到股票持仓信息: index[%d], isEnd[%c], " \
            "证券账户[%s], 市场代码[%" __SPK_FMT_HH__ "u], 产品代码[%s], " \
            "日初持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计买入[%" __SPK_FMT_LL__ "d], " \
            "日中累计卖出[%" __SPK_FMT_LL__ "d], " \
            "当前卖出冻结[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换获得[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换付出[%" __SPK_FMT_LL__ "d], " \
            "当前转换付出冻结[%" __SPK_FMT_LL__ "d], " \
            "当前已锁定[%" __SPK_FMT_LL__ "d], " \
            "当前锁定冻结[%" __SPK_FMT_LL__ "d], " \
            "当前解锁定冻结[%" __SPK_FMT_LL__ "d], " \
            "当前备兑冻结[%" __SPK_FMT_LL__ "d], " \
            "当前已备兑使用[%" __SPK_FMT_LL__ "d], " \
            "当前可备兑/解锁[%" __SPK_FMT_LL__ "d], " \
            "当前总持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可卖[%" __SPK_FMT_LL__ "d], " \
            "当前可转换付出[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pStkHolding->invAcctId, pStkHolding->mktId, pStkHolding->securityId,
            pStkHolding->originalHld, pStkHolding->totalBuyHld,
            pStkHolding->totalSellHld, pStkHolding->sellFrzHld,
            pStkHolding->totalTrsfInHld, pStkHolding->totalTrsfOutHld,
            pStkHolding->trsfOutFrzHld, pStkHolding->lockHld,
            pStkHolding->lockFrzHld, pStkHolding->unlockFrzHld,
            pStkHolding->coveredFrzHld, pStkHolding->coveredHld,
            pStkHolding->coveredAvlHld, pStkHolding->sumHld,
            pStkHolding->sellAvlHld, pStkHolding->trsfOutAvlHld,
            pStkHolding->lockAvlHld);
}


/* 查询到配号、中签信息回调 */
void
OesClientMySpi::OnQueryLotWinning(const OesLotWinningItemT *pLotWinning,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到新股配号、中签信息: index[%d], isEnd[%c], " \
            "股东账户代码[%s], 证券代码[%s], 证券名称[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "记录类型[%" __SPK_FMT_HH__ "u], " \
            "失败原因[%" __SPK_FMT_HH__ "u], 配号、中签日期[%08d], " \
            "配号首个号码[%" __SPK_FMT_LL__ "d], 配号成功数量/中签股数[%d], " \
            "最终发行价[%d], 中签金额[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pLotWinning->invAcctId, pLotWinning->securityId,
            pLotWinning->securityName, pLotWinning->mktId, pLotWinning->lotType,
            pLotWinning->rejReason, pLotWinning->lotDate, pLotWinning->assignNum,
            pLotWinning->lotQty, pLotWinning->lotPrice, pLotWinning->lotAmt);
}


/* 查询到客户信息回调 */
void
OesClientMySpi::OnQueryCustInfo(const OesCustItemT *pCust,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到客户信息: index[%d], isEnd[%c], " \
            "客户ID[%s], 客户类型[%" __SPK_FMT_HH__ "u], " \
            "客户状态[%" __SPK_FMT_HH__ "u], 风险评级[%" __SPK_FMT_HH__ "u], " \
            "机构标志[%" __SPK_FMT_HH__ "u], 投资者分类[%c]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pCust->custId, pCust->custType, pCust->status,
            pCust->riskLevel, pCust->institutionFlag,
            pCust->investorClass == OES_INVESTOR_CLASS_NORMAL ?
                    '0' : pCust->investorClass + 'A' - 1);
}


/* 查询到股东账户信息回调 */
void
OesClientMySpi::OnQueryInvAcct(const OesInvAcctItemT *pInvAcct,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到证券账户信息: index[%d], isEnd[%c], " \
            "证券账户[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "客户代码[%s], 账户状态[%" __SPK_FMT_HH__ "u], " \
            "新股认购限额[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pInvAcct->invAcctId, pInvAcct->mktId,
            pInvAcct->custId, pInvAcct->status,
            pInvAcct->subscriptionQuota);
}


/* 查询到佣金信息回调 */
void
OesClientMySpi::OnQueryCommissionRate(
        const OesCommissionRateItemT *pCommissionRate,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到佣金信息: index[%d], isEnd[%c], " \
            "客户代码[%s], 证券代码[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], 证券子类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 币种[%" __SPK_FMT_HH__ "u], " \
            "费用标识[%" __SPK_FMT_HH__ "u], 计算模式 [%" __SPK_FMT_HH__ "u], " \
            "费率[%" __SPK_FMT_LL__ "d], 最低费用[%d], 最高费用[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pCommissionRate->custId, pCommissionRate->securityId,
            pCommissionRate->mktId, pCommissionRate->securityType,
            pCommissionRate->subSecurityType, pCommissionRate->bsType,
            pCommissionRate->currType, pCommissionRate->feeType,
            pCommissionRate->calcFeeMode, pCommissionRate->feeRate,
            pCommissionRate->minFee, pCommissionRate->maxFee);
}


/* 查询到出入金流水信息回调 */
void
OesClientMySpi::OnQueryFundTransferSerial(
        const OesFundTransferSerialItemT *pFundTrsf,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到出入金流水: index[%d], isEnd[%c], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "资金账户[%s], 方向[%s], 金额[%" __SPK_FMT_LL__ "d], " \
            "出入金状态[%" __SPK_FMT_HH__ "u], 错误原因[%d], 主柜错误码[%d], " \
            "错误信息[%s], 柜台委托编码[%d], 接收日期[%08d], " \
            "接收时间[%09d], 上报时间[%09d], 完成时间[%09d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pFundTrsf->clEnvId, pFundTrsf->clSeqNo,
            pFundTrsf->cashAcctId,
            pFundTrsf->direct == OES_FUND_TRSF_DIRECT_IN ? "Bank->Broker" : "Broker->Bank",
            pFundTrsf->occurAmt, pFundTrsf->trsfStatus, pFundTrsf->rejReason,
            pFundTrsf->counterErrCode, pFundTrsf->errorInfo,
            pFundTrsf->counterEntrustNo, pFundTrsf->operDate,
            pFundTrsf->operTime, pFundTrsf->dclrTime,
            pFundTrsf->doneTime);
}


/* 查询到证券发行信息回调 */
void
OesClientMySpi::OnQueryIssue(const OesIssueItemT *pIssue,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到证券发行产品信息: index[%d], isEnd[%c], " \
            "证券代码[%s], 证券名称[%s], 正股代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], " \
            "证券子类型[%" __SPK_FMT_HH__ "u], " \
            "是否允许撤单[%" __SPK_FMT_HH__ "u], " \
            "是否允许重复认购[%" __SPK_FMT_HH__ "u], " \
            "发行起始时间[%d], 发行结束时间[%d], " \
            "发行总量[%" __SPK_FMT_LL__ "d], " \
            "份数单位[%d], 最大份数[%d], 最小份数[%d], " \
            "发行价格[%d], 价格上限[%d], 价格下限[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pIssue->securityId, pIssue->securityName,
            pIssue->underlyingSecurityId, pIssue->mktId, pIssue->securityType,
            pIssue->subSecurityType, pIssue->isCancelAble,
            pIssue->isReApplyAble, pIssue->startDate, pIssue->endDate,
            pIssue->issueQty, pIssue->qtyUnit, pIssue->ordMaxQty,
            pIssue->ordMinQty, pIssue->issuePrice, pIssue->ceilPrice,
            pIssue->floorPrice);
}


/* 查询到证券信息回调 */
void
OesClientMySpi::OnQueryStock(const OesStockItemT *pStock,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到现货产品信息: index[%d], isEnd[%c], " \
            "证券代码[%s], 证券名称[%s], 基金代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 证券类型[%" __SPK_FMT_HH__ "u], " \
            "证券子类型[%" __SPK_FMT_HH__ "u], 证券级别[%" __SPK_FMT_HH__ "u], " \
            "风险等级[%" __SPK_FMT_HH__ "u], 停牌标志[%" __SPK_FMT_HH__ "u], " \
            "适当性管理[%" __SPK_FMT_HH__ "u], 当日回转[%" __SPK_FMT_HH__ "u], " \
            "价格单位[%d], 买份数单位[%d], 卖份数单位[%d], " \
            "昨日收盘价[%d], 债券利息[%" __SPK_FMT_LL__ "d], " \
            "涨停价[%d], 跌停价[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pStock->securityId, pStock->securityName, pStock->fundId,
            pStock->mktId, pStock->securityType, pStock->subSecurityType,
            pStock->securityLevel, pStock->securityRiskLevel, pStock->suspFlag,
            pStock->qualificationClass, pStock->isDayTrading,
            pStock->priceUnit, pStock->buyQtyUnit, pStock->sellQtyUnit,
            pStock->prevClose, pStock->bondInterest,
            pStock->priceLimit[OES_TRD_SESS_TYPE_T].ceilPrice,
            pStock->priceLimit[OES_TRD_SESS_TYPE_T].floorPrice);
}


/* 查询到ETF产品信息回调 */
void
OesClientMySpi::OnQueryEtf(const OesEtfItemT *pEtf,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到ETF申赎产品信息: index[%d], isEnd[%c], " \
            "基金代码[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "申购赎回单位[%d], 最大现金替代比例[%d], " \
            "前一日最小申赎单位净值[%" __SPK_FMT_LL__ "d], " \
            "前一日现金差额[%" __SPK_FMT_LL__ "d], " \
            "成分证券数目[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pEtf->fundId, pEtf->securityId, pEtf->mktId, pEtf->creRdmUnit,
            pEtf->maxCashRatio, pEtf->navPerCU, pEtf->cashCmpoent,
            pEtf->componentCnt);
}


/* 查询到ETF成分股信息回调 */
void
OesClientMySpi::OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到ETF成分股信息: index[%d], isEnd[%c], " \
            "成分证券代码[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "现金替代标识[%d], 昨日收盘价[%d], 成分证券数量[%d], " \
            "溢价比例[%d], 申购替代金额[%" __SPK_FMT_LL__ "d], " \
            "赎回替代金额[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pEtfComponent->securityId, pEtfComponent->mktId,
            pEtfComponent->subFlag, pEtfComponent->prevClose,
            pEtfComponent->qty, pEtfComponent->premiumRate,
            pEtfComponent->creationSubCash, pEtfComponent->redemptionCashSub);
}


/* 查询到市场状态信息回调 */
void
OesClientMySpi::OnQueryMarketState(const OesMarketStateItemT *pMarketState,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到市场状态信息: index[%d], isEnd[%c], " \
            "交易所代码[%hhu], 交易平台类型[%hhu], 市场类型[%hhu], " \
            "市场状态[%hhu]\n", \
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pMarketState->exchId, pMarketState->platformId,
            pMarketState->mktId, pMarketState->mktState);
}


OesClientMySpi::OesClientMySpi(int32 something) {
    this->something = something;
}


OesClientMySpi::~OesClientMySpi() {
    /* do nothing */
}
