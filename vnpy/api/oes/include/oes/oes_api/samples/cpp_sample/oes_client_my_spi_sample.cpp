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
OesClientMySpi::OnBusinessReject(const OesRptMsgHeadT *pRptMsgHead,
        const OesOrdRejectT *pOrderReject) {
    fprintf(stdout, ">>> 收到委托业务拒绝回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "客户委托流水号[%d], 证券账户[%s], 证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 委托类型[%" __SPK_FMT_HH__ "u], " \
            "买卖类型[%" __SPK_FMT_HH__ "u], 委托数量[%d], 委托价格[%d], " \
            "原始委托的客户订单编号[%" __SPK_FMT_LL__ "d], 错误码[%d]\n",
            pRptMsgHead->execType, pOrderReject->clEnvId, pOrderReject->clSeqNo,
            pOrderReject->invAcctId, pOrderReject->securityId,
            pOrderReject->mktId, pOrderReject->ordType,
            pOrderReject->bsType, pOrderReject->ordQty,
            pOrderReject->ordPrice, pOrderReject->origClOrdId,
            pRptMsgHead->ordRejReason);
}


/* 委托已收回报 */
void
OesClientMySpi::OnOrderInsert(const OesRptMsgHeadT *pRptMsgHead,
        const OesOrdCnfmT *pOrderInsert) {
    fprintf(stdout, ">>> 收到委托已收回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], " \
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
            pRptMsgHead->execType, pOrderInsert->clEnvId, pOrderInsert->clSeqNo,
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
OesClientMySpi::OnOrderReport(const OesRptMsgHeadT *pRptMsgHead,
        const OesOrdCnfmT *pOrderReport) {
    fprintf(stdout, ">>> 收到委托回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], " \
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
            pRptMsgHead->execType, pOrderReport->clEnvId, pOrderReport->clSeqNo,
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
OesClientMySpi::OnTradeReport(const OesRptMsgHeadT *pRptMsgHead,
        const OesTrdCnfmT *pTradeReport) {
    fprintf(stdout, ">>> 收到成交回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], " \
            "成交编号[%" __SPK_FMT_LL__ "d], 会员内部编号[%" __SPK_FMT_LL__ "d], " \
            "委托客户端环境号[%" __SPK_FMT_HH__ "d], 客户委托流水号[%d], " \
            "证券账户[%s], 证券代码[%s], 市场代码[%" __SPK_FMT_HH__ "u], " \
            "买卖方向[%" __SPK_FMT_HH__ "u], 委托买卖类型[%" __SPK_FMT_HH__ "u], "
            "成交日期[%d], 成交时间[%d], 成交数量[%d], 成交价格[%d], " \
            "成交金额[%" __SPK_FMT_LL__ "d], 债券利息[%" __SPK_FMT_LL__ "d], "
            "交易费用[%" __SPK_FMT_LL__ "d], 累计成交数量[%d], " \
            "累计成交金额[%" __SPK_FMT_LL__ "d], 累计债券利息[%" __SPK_FMT_LL__ "d], " \
            "累计交易费用[%" __SPK_FMT_LL__ "d], PBU代码[%d]\n",
            pRptMsgHead->execType, pTradeReport->exchTrdNum, pTradeReport->clOrdId,
            pTradeReport->clEnvId, pTradeReport->clSeqNo,
            pTradeReport->invAcctId, pTradeReport->securityId,
            pTradeReport->mktId, pTradeReport->trdSide,
            pTradeReport->ordBuySellType, pTradeReport->trdDate,
            pTradeReport->trdTime, pTradeReport->trdQty,
            pTradeReport->trdPrice, pTradeReport->trdAmt,
            pTradeReport->trdInterest, pTradeReport->trdFee,
            pTradeReport->cumQty, pTradeReport->cumAmt,
            pTradeReport->cumInterest, pTradeReport->cumFee,
            pTradeReport->pbuId);
}


/* 资金变动回报 */
void
OesClientMySpi::OnCashAssetVariation(const OesCashAssetReportT *pCashAssetRpt) {
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
            "未对冲实时保证金金额[%" __SPK_FMT_LL__ "d], " \
            "已对冲实时保证金金额[%" __SPK_FMT_LL__ "d], " \
            "当前余额[%" __SPK_FMT_LL__ "d], " \
            "当前可用余额[%" __SPK_FMT_LL__ "d], " \
            "当前可取余额[%" __SPK_FMT_LL__ "d]\n",
            pCashAssetRpt->cashAcctId, pCashAssetRpt->custId,
            pCashAssetRpt->currType, pCashAssetRpt->cashType,
            pCashAssetRpt->cashAcctStatus, pCashAssetRpt->beginningBal,
            pCashAssetRpt->beginningAvailableBal,
            pCashAssetRpt->beginningDrawableBal,
            pCashAssetRpt->disableBal, pCashAssetRpt->totalDepositAmt,
            pCashAssetRpt->totalWithdrawAmt, pCashAssetRpt->withdrawFrzAmt,
            pCashAssetRpt->totalSellAmt, pCashAssetRpt->totalBuyAmt,
            pCashAssetRpt->buyFrzAmt, pCashAssetRpt->totalFeeAmt,
            pCashAssetRpt->feeFrzAmt, pCashAssetRpt->marginAmt,
            pCashAssetRpt->marginFrzAmt,
            pCashAssetRpt->optionExt.totalMarketMargin,
            pCashAssetRpt->optionExt.totalNetMargin,
            pCashAssetRpt->currentTotalBal,
            pCashAssetRpt->currentAvailableBal,
            pCashAssetRpt->currentDrawableBal);
}


/* 股票持仓变动回报 */
void
OesClientMySpi::OnStockHoldingVariation(const OesStkHoldingReportT *pStkHoldingRpt) {
    fprintf(stdout, ">>> 收到股票持仓变动回报: " \
            "证券账户[%s], 产品代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "日初持仓[%" __SPK_FMT_LL__ "d], " \
            "日初可用持仓[%" __SPK_FMT_LL__ "d], " \
            "当日可减持额度[%" __SPK_FMT_LL__ "d], " \
            "日中累计买入持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计卖出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前卖出冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "手动冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换获得持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换付出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前转换付出冻结持仓[%" __SPK_FMT_LL__ "d], " \
            "日初锁定持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计锁定持仓[%" __SPK_FMT_LL__ "d], " \
            "日中累计解锁持仓[%" __SPK_FMT_LL__ "d], " \
            "日初总持仓成本[%" __SPK_FMT_LL__ "d], " \
            "当日累计买入金额[%" __SPK_FMT_LL__ "d], " \
            "当日累计卖出金额[%" __SPK_FMT_LL__ "d], " \
            "当日累计买入费用[%" __SPK_FMT_LL__ "d], " \
            "当日累计卖出费用[%" __SPK_FMT_LL__ "d], " \
            "持仓成本价[%" __SPK_FMT_LL__ "d], " \
            "当前总持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可卖持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可转换付出持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定持仓[%" __SPK_FMT_LL__ "d]\n",
            pStkHoldingRpt->invAcctId, pStkHoldingRpt->securityId,
            pStkHoldingRpt->mktId, pStkHoldingRpt->originalHld,
            pStkHoldingRpt->originalAvlHld, pStkHoldingRpt->maxReduceQuota,
            pStkHoldingRpt->totalBuyHld,pStkHoldingRpt->totalSellHld,
            pStkHoldingRpt->sellFrzHld, pStkHoldingRpt->manualFrzHld,
            pStkHoldingRpt->totalTrsfInHld, pStkHoldingRpt->totalTrsfOutHld,
            pStkHoldingRpt->trsfOutFrzHld, pStkHoldingRpt->originalLockHld,
            pStkHoldingRpt->totalLockHld, pStkHoldingRpt->totalUnlockHld,
            pStkHoldingRpt->originalCostAmt, pStkHoldingRpt->totalBuyAmt,
            pStkHoldingRpt->totalSellAmt, pStkHoldingRpt->totalBuyFee,
            pStkHoldingRpt->totalSellFee, pStkHoldingRpt->costPrice,
            pStkHoldingRpt->sumHld, pStkHoldingRpt->sellAvlHld,
            pStkHoldingRpt->trsfOutAvlHld, pStkHoldingRpt->lockAvlHld);
}


/* 期权持仓变动通知 (适用于期权业务) */
void
OesClientMySpi::OnOptionHoldingVariation(const OesOptHoldingReportT *pOptHoldingRpt) {
    fprintf(stdout, ">>> 收到期权持仓变动回报: " \
            "证券账户[%s], 产品代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "持仓类型[%" __SPK_FMT_HH__ "u], " \
            "产品类型[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], " \
            "证券子类型[%" __SPK_FMT_HH__ "u], " \
            "合约类型[%" __SPK_FMT_HH__ "u], " \
            "套保标志[%" __SPK_FMT_HH__ "u], " \
            "日初总持仓张数[%" __SPK_FMT_LL__ "d], " \
            "日初可用持仓[%" __SPK_FMT_LL__ "d], " \
            "日初总持仓成本[%" __SPK_FMT_LL__ "d], " \
            "日初总占用金额[%" __SPK_FMT_LL__ "d], " \
            "日中累计开仓张数[%" __SPK_FMT_LL__ "d], " \
            "开仓委托未成交张数[%" __SPK_FMT_LL__ "d], " \
            "日中累计平仓张数[%" __SPK_FMT_LL__ "d], " \
            "平仓在途冻结张数[%" __SPK_FMT_LL__ "d], " \
            "手动冻结张数[%" __SPK_FMT_LL__ "d], " \
            "日中累计获得权利金[%" __SPK_FMT_LL__ "d], " \
            "日中累计付出权利金[%" __SPK_FMT_LL__ "d], " \
            "日中累计开仓费用[%" __SPK_FMT_LL__ "d], " \
            "日中累计平仓费用[%" __SPK_FMT_LL__ "d], " \
            "权利仓行权冻结张数[%" __SPK_FMT_LL__ "d], " \
            "义务仓持仓保证金[%" __SPK_FMT_LL__ "d], " \
            "可平仓张数[%" __SPK_FMT_LL__ "d], " \
            "可行权张数[%" __SPK_FMT_LL__ "d], " \
            "总持仓张数[%" __SPK_FMT_LL__ "d], " \
            "持仓成本价[%" __SPK_FMT_LL__ "d], " \
            "持仓均价[%" __SPK_FMT_LL__ "d], " \
            "可备兑标的券数量[%" __SPK_FMT_LL__ "d], " \
            "当前可用的权利仓限额[%d], " \
            "当前可用的总持仓限额[%d], " \
            "当前可用的单日买入开仓限额[%d]\n",
            pOptHoldingRpt->invAcctId, pOptHoldingRpt->securityId,
            pOptHoldingRpt->mktId, pOptHoldingRpt->positionType,
            pOptHoldingRpt->productType, pOptHoldingRpt->securityType,
            pOptHoldingRpt->subSecurityType, pOptHoldingRpt->contractType,
            pOptHoldingRpt->hedgeFlag, pOptHoldingRpt->originalQty,
            pOptHoldingRpt->originalAvlQty, pOptHoldingRpt->originalCostAmt,
            pOptHoldingRpt->originalCarryingAmt,
            pOptHoldingRpt->totalOpenQty, pOptHoldingRpt->uncomeQty,
            pOptHoldingRpt->totalCloseQty, pOptHoldingRpt->closeFrzQty,
            pOptHoldingRpt->manualFrzQty, pOptHoldingRpt->totalInPremium,
            pOptHoldingRpt->totalOutPremium, pOptHoldingRpt->totalOpenFee,
            pOptHoldingRpt->totalCloseFee, pOptHoldingRpt->exerciseFrzQty,
            pOptHoldingRpt->positionMargin, pOptHoldingRpt->closeAvlQty,
            pOptHoldingRpt->exerciseAvlQty, pOptHoldingRpt->sumQty,
            pOptHoldingRpt->costPrice, pOptHoldingRpt->carryingAvgPrice,
            pOptHoldingRpt->coveredAvlUnderlyingQty,
            pOptHoldingRpt->availableLongPositionLimit,
            pOptHoldingRpt->availableTotalPositionLimit,
            pOptHoldingRpt->availableDailyBuyOpenLimit);
}


/* 期权标的持仓变动通知 (适用于期权业务) */
void
OesClientMySpi::OnOptionUnderlyingHoldingVariation(
        const OesOptUnderlyingHoldingReportT *pUnderlyingHoldingRpt) {
    fprintf(stdout, ">>> 收到期权标的持仓变动回报: " \
            "证券账户[%s], " \
            "标的证券代码[%s], " \
            "市场代码(衍生品市场)[%" __SPK_FMT_HH__ "u], " \
            "标的市场代码[%" __SPK_FMT_HH__ "u], " \
            "标的证券类型[%" __SPK_FMT_HH__ "u], " \
            "标的证券子类型[%" __SPK_FMT_HH__ "u], " \
            "日初标的证券的总持仓数量 [%" __SPK_FMT_LL__ "d], "  \
            "日初标的证券的可用持仓数量[%" __SPK_FMT_LL__ "d], " \
            "日初备兑仓实际占用的标的证券数量[%" __SPK_FMT_LL__ "d], " \
            "日初备兑仓应占用的标的证券数量[%" __SPK_FMT_LL__ "d], " \
            "当前备兑仓实际占用的标的证券数量[%" __SPK_FMT_LL__ "d], " \
            "当前备兑仓占用标的证券的缺口数量[%" __SPK_FMT_LL__ "d], " \
            "当前可用于备兑开仓的标的持仓数量[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定的标的持仓数量[%" __SPK_FMT_LL__ "d], " \
            "总持仓数量[%" __SPK_FMT_LL__ "d], " \
            "当日最大可减持额度[%" __SPK_FMT_LL__ "d]\n",
            pUnderlyingHoldingRpt->invAcctId,
            pUnderlyingHoldingRpt->underlyingSecurityId,
            pUnderlyingHoldingRpt->mktId,
            pUnderlyingHoldingRpt->underlyingMktId,
            pUnderlyingHoldingRpt->underlyingSecurityType,
            pUnderlyingHoldingRpt->underlyingSubSecurityType,
            pUnderlyingHoldingRpt->originalHld,
            pUnderlyingHoldingRpt->originalAvlHld,
            pUnderlyingHoldingRpt->originalCoveredQty,
            pUnderlyingHoldingRpt->initialCoveredQty,
            pUnderlyingHoldingRpt->coveredQty,
            pUnderlyingHoldingRpt->coveredGapQty,
            pUnderlyingHoldingRpt->coveredAvlQty,
            pUnderlyingHoldingRpt->lockAvlQty,
            pUnderlyingHoldingRpt->sumHld,
            pUnderlyingHoldingRpt->maxReduceQuota);
}


/* 期权结算单确认回报 (适用于期权业务) */
void
OesClientMySpi::OnSettlementConfirmedRpt(const OesRptMsgHeadT *pRptMsgHead,
        const OesOptSettlementConfirmReportT *pCnfmSettlementRpt) {
    fprintf(stdout, ">>> 收到结算单确认回报: " \
            "客户代码[%s], " \
            "客户端编号[%" __SPK_FMT_SHORT__ "d], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "发生日期[%d], " \
            "发生时间[%d], " \
            "失败原因[%d]\n",
            pCnfmSettlementRpt->custId,
            pCnfmSettlementRpt->clientId,
            pCnfmSettlementRpt->clEnvId,
            pCnfmSettlementRpt->transDate,
            pCnfmSettlementRpt->transTime,
            pCnfmSettlementRpt->rejReason);
}


/* 出入金委托拒绝回报 */
void
OesClientMySpi::OnFundTrsfReject(const OesRptMsgHeadT *pRptMsgHead,
        const OesFundTrsfRejectT *pFundTrsfReject) {
    fprintf(stdout, ">>> 收到出入金委托拒绝回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], 错误码[%d], 错误信息[%s], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "出入金流水号[%d], 资金账户[%s], " \
            "是否仅调拨[%" __SPK_FMT_HH__ "u], " \
            "出入金方向[%" __SPK_FMT_HH__ "u], " \
            "出入金金额[%" __SPK_FMT_LL__ "d]\n",
            pRptMsgHead->execType, pFundTrsfReject->rejReason,
            pFundTrsfReject->errorInfo, pFundTrsfReject->clEnvId,
            pFundTrsfReject->clSeqNo, pFundTrsfReject->cashAcctId,
            pFundTrsfReject->isAllotOnly, pFundTrsfReject->direct,
            pFundTrsfReject->occurAmt);
}


/* 出入金委托执行回报 */
void
OesClientMySpi::OnFundTrsfReport(const OesRptMsgHeadT *pRptMsgHead,
        const OesFundTrsfReportT *pFundTrsfReport) {
    fprintf(stdout, ">>> 收到出入金委托执行回报: " \
            "执行类型[%" __SPK_FMT_HH__ "u], 错误原因[%d], " \
            "主柜错误码[%d], 错误信息[%s], " \
            "客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "出入金流水号[%d], 出入金编号[%d], 资金账户[%s], " \
            "是否仅调拨[%" __SPK_FMT_HH__ "u], " \
            "出入金方向[%" __SPK_FMT_HH__ "u], " \
            "出入金金额[%" __SPK_FMT_LL__ "d], " \
            "出入金状态[%d], 接收日期[%08d], " \
            "接收时间[%09d], 上报时间[%09d], 完成时间[%09d]\n",
            pRptMsgHead->execType, pFundTrsfReport->rejReason,
            pFundTrsfReport->counterErrCode, pFundTrsfReport->errorInfo,
            pFundTrsfReport->clEnvId, pFundTrsfReport->clSeqNo,
            pFundTrsfReport->fundTrsfId, pFundTrsfReport->cashAcctId,
            pFundTrsfReport->isAllotOnly, pFundTrsfReport->direct,
            pFundTrsfReport->occurAmt, pFundTrsfReport->trsfStatus,
            pFundTrsfReport->operDate, pFundTrsfReport->operTime,
            pFundTrsfReport->dclrTime, pFundTrsfReport->doneTime);
}


/* 市场状态信息 */
void
OesClientMySpi::OnMarketState(const OesMarketStateItemT *pMarketStateItem) {
    fprintf(stdout, ">>> 收到市场状态信息: " \
            "交易所代码[%" __SPK_FMT_HH__ "u], " \
            "交易平台类型[%" __SPK_FMT_HH__ "u], " \
            "市场类型[%" __SPK_FMT_HH__ "u], " \
            "市场状态[%" __SPK_FMT_HH__ "u]\n",
            pMarketStateItem->exchId, pMarketStateItem->platformId,
            pMarketStateItem->mktId, pMarketStateItem->mktState);
}


/* 通知消息回报 */
void
OesClientMySpi::OnNotifyReport(const OesNotifyInfoReportT *pNotifyInfoRpt) {
    fprintf(stdout, ">>> 收到通知消息回报: " \
            "通知消息序号[%d], " \
            "通知消息等级[%" __SPK_FMT_HH__ "u], " \
            "通知消息范围[%" __SPK_FMT_HH__ "u], " \
            "通知来源分类[%" __SPK_FMT_HH__ "u], " \
            "通知消息类型[%" __SPK_FMT_HH__ "u], " \
            "通知发出时间[%9d], " \
            "客户代码[%s], " \
            "通知内容[%s]\n",
            pNotifyInfoRpt->notifySeqNo,
            pNotifyInfoRpt->notifyLevel,
            pNotifyInfoRpt->notifyScope,
            pNotifyInfoRpt->notifySource,
            pNotifyInfoRpt->notifyType,
            pNotifyInfoRpt->tranTime,
            pNotifyInfoRpt->custId,
            pNotifyInfoRpt->content);
}


/* 回报同步响应 */
void
OesClientMySpi::OnReportSynchronizationRsp(
        const OesReportSynchronizationRspT *pReportSynchronization) {
    fprintf(stdout, ">>> 收到回报同步响应: " \
            "服务端最后已发送或已忽略的回报数据的回报编号[%" __SPK_FMT_LL__ "d], " \
            "订阅的客户端环境号[%" __SPK_FMT_HH__ "d], " \
            "已订阅的回报消息种类[%d]\n",
            pReportSynchronization->lastRptSeqNum,
            pReportSynchronization->subscribeEnvId,
            pReportSynchronization->subscribeRptTypes);
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
            "当前费用冻结[%" __SPK_FMT_LL__ "d], 日初持仓保证金[%" __SPK_FMT_LL__ "d], " \
            "行权累计待交收冻结[%" __SPK_FMT_LL__ "d], 当前维持保证金[%" __SPK_FMT_LL__ "d], " \
            "当前保证金冻结[%" __SPK_FMT_LL__ "d], 未对冲实时价格保证金[%" __SPK_FMT_LL__ "d], " \
            "已对冲实时价格保证金[%" __SPK_FMT_LL__ "d], 待追加保证金[%" __SPK_FMT_LL__ "d], " \
            "当前余额[%" __SPK_FMT_LL__ "d], 当前可用[%" __SPK_FMT_LL__ "d], " \
            "当前可取[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pCashAsset->cashAcctId, pCashAsset->custId, pCashAsset->currType,
            pCashAsset->cashType, pCashAsset->beginningBal,
            pCashAsset->beginningAvailableBal, pCashAsset->beginningDrawableBal,
            pCashAsset->disableBal, pCashAsset->totalDepositAmt,
            pCashAsset->totalWithdrawAmt, pCashAsset->withdrawFrzAmt,
            pCashAsset->totalSellAmt, pCashAsset->totalBuyAmt,
            pCashAsset->buyFrzAmt, pCashAsset->totalFeeAmt,
            pCashAsset->feeFrzAmt, pCashAsset->optionExt.initialMargin,
            pCashAsset->optionExt.totalExerciseFrzAmt,
            pCashAsset->marginAmt, pCashAsset->marginFrzAmt,
            pCashAsset->optionExt.totalMarketMargin,
            pCashAsset->optionExt.totalNetMargin,
            pCashAsset->optionExt.pendingSupplMargin,
            pCashAsset->currentTotalBal, pCashAsset->currentAvailableBal,
            pCashAsset->currentDrawableBal);
}


/* 查询到持仓信息回调 */
void
OesClientMySpi::OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到股票持仓信息: index[%d], isEnd[%c], " \
            "证券账户[%s], 市场代码[%" __SPK_FMT_HH__ "u], 产品代码[%s], " \
            "日初持仓[%" __SPK_FMT_LL__ "d], " \
            "日初可用持仓[%" __SPK_FMT_LL__ "d], " \
            "当日可减持额度[%" __SPK_FMT_LL__ "d], " \
            "日中累计买入[%" __SPK_FMT_LL__ "d], " \
            "日中累计卖出[%" __SPK_FMT_LL__ "d], " \
            "当前卖出冻结[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换获得[%" __SPK_FMT_LL__ "d], " \
            "日中累计转换付出[%" __SPK_FMT_LL__ "d], " \
            "当前转换付出冻结[%" __SPK_FMT_LL__ "d], " \
            "日初锁定[%" __SPK_FMT_LL__ "d], " \
            "累计锁定[%" __SPK_FMT_LL__ "d], " \
            "累计解锁[%" __SPK_FMT_LL__ "d], " \
            "当前总持仓[%" __SPK_FMT_LL__ "d], " \
            "当前可卖[%" __SPK_FMT_LL__ "d], " \
            "当前可转换付出[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pStkHolding->invAcctId, pStkHolding->mktId, pStkHolding->securityId,
            pStkHolding->originalHld, pStkHolding->originalAvlHld,
            pStkHolding->maxReduceQuota, pStkHolding->totalBuyHld,
            pStkHolding->totalSellHld, pStkHolding->sellFrzHld,
            pStkHolding->totalTrsfInHld, pStkHolding->totalTrsfOutHld,
            pStkHolding->trsfOutFrzHld, pStkHolding->originalLockHld,
            pStkHolding->totalLockHld, pStkHolding->totalUnlockHld,
            pStkHolding->sumHld, pStkHolding->sellAvlHld,
            pStkHolding->trsfOutAvlHld, pStkHolding->lockAvlHld);
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
            "主板权益[%d], 科创板权益[%d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pInvAcct->invAcctId, pInvAcct->mktId,
            pInvAcct->custId, pInvAcct->status,
            pInvAcct->subscriptionQuota, pInvAcct->kcSubscriptionQuota);
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
            "交易所代码[%" __SPK_FMT_HH__ "u], " \
            "交易平台类型[%" __SPK_FMT_HH__ "u], " \
            "市场类型[%" __SPK_FMT_HH__ "u], " \
            "市场状态[%" __SPK_FMT_HH__ "u]\n", \
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pMarketState->exchId, pMarketState->platformId,
            pMarketState->mktId, pMarketState->mktState);
}


/* 查询到期权产品信息回调 */
void
OesClientMySpi::OnQueryOption(const OesOptionItemT *pOption,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到期权产品信息: index[%d], isEnd[%c], " \
            "证券代码[%s], 合约交易代码[%s], 合约名称[%s], 标的证券[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], 产品类型[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], 证券子类型[%" __SPK_FMT_HH__ "u], " \
            "合约类型[%" __SPK_FMT_HH__ "u], 行权方式[%" __SPK_FMT_HH__ "u], " \
            "交割方式[%" __SPK_FMT_HH__ "u], 当日回转[%" __SPK_FMT_HH__ "u], " \
            "限制开仓[%" __SPK_FMT_HH__ "u], 连续停牌[%" __SPK_FMT_HH__ "u], " \
            "临时停牌[%" __SPK_FMT_HH__ "u], 合约单位[%d], 期权行权价[%d], " \
            "交割日期[%08d], 交割月份[%08d], 上市日期[%08d], 最后交易日[%08d], " \
            "行权起始日[%08d], 行权结束日[%08d], 持仓量[%" __SPK_FMT_LL__ "d], " \
            "前收盘价[%d], 前结算价[%d], 标的前收[%d], 报价单位[%d], 涨停价[%d], " \
            "跌停价[%d], 买单位[%d], 限价买上限[%d], 限价买下限[%d], 市价买上限[%d], " \
            "市价买下限[%d], 卖单位[%d], 限价卖上限[%d], 限价卖下限[%d], " \
            "市价卖上限[%d], 市价卖下限[%d], 卖开保证金[%" __SPK_FMT_LL__ "d], " \
            "保证金参数一[%d](万分比), 保证金参数二[%d](万分比), " \
            "保证金上浮比例[%d](万分比), 合约状态[%c%c%c%c%c%c%c%c]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N', pOption->securityId,
            pOption->contractId, pOption->securityName,
            pOption->underlyingSecurityId, pOption->mktId, pOption->productType,
            pOption->securityType, pOption->subSecurityType,
            pOption->contractType, pOption->exerciseType, pOption->deliveryType,
            pOption->isDayTrading, pOption->limitOpenFlag, pOption->suspFlag,
            pOption->temporarySuspFlag, pOption->contractUnit,
            pOption->exercisePrice, pOption->deliveryDate,
            pOption->deliveryMonth, pOption->listDate, pOption->lastTradeDay,
            pOption->exerciseBeginDate, pOption->exerciseEndDate,
            pOption->contractPosition, pOption->prevClosePrice,
            pOption->prevSettlPrice, pOption->underlyingClosePrice,
            pOption->priceTick, pOption->upperLimitPrice,
            pOption->lowerLimitPrice, pOption->buyQtyUnit,
            pOption->lmtBuyMaxQty, pOption->lmtBuyMinQty, pOption->mktBuyMaxQty,
            pOption->mktBuyMinQty, pOption->sellQtyUnit, pOption->lmtSellMaxQty,
            pOption->lmtSellMinQty, pOption->mktSellMaxQty,
            pOption->mktSellMinQty, pOption->sellMargin,
            pOption->marginRatioParam1, pOption->marginRatioParam2,
            pOption->increasedMarginRatio, pOption->securityStatusFlag[0],
            pOption->securityStatusFlag[1], pOption->securityStatusFlag[2],
            pOption->securityStatusFlag[3], pOption->securityStatusFlag[4],
            pOption->securityStatusFlag[5], pOption->securityStatusFlag[6],
            pOption->securityStatusFlag[7]);
}


/* 查询到期权持仓信息回调 */
void
OesClientMySpi::OnQueryOptHolding(const OesOptHoldingItemT *pHoldingItem,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到期权持仓信息: index[%d], isEnd[%c], " \
            "证券账户[%s], " \
            "合约代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "持仓类型[%" __SPK_FMT_HH__ "u], " \
            "产品类型[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], " \
            "证券子类型[%" __SPK_FMT_HH__ "u], " \
            "合约类型[%" __SPK_FMT_HH__ "u], " \
            "日初持仓张数[%" __SPK_FMT_LL__ "d], " \
            "日初可用持仓张数[%" __SPK_FMT_LL__ "d], " \
            "日初总持仓成本[%" __SPK_FMT_LL__ "d], " \
            "日中累计开仓张数[%" __SPK_FMT_LL__ "d], "  \
            "开仓未成交张数[%" __SPK_FMT_LL__ "d], "  \
            "日中累计平仓张数[%" __SPK_FMT_LL__ "d], " \
            "平仓在途冻结张数[%" __SPK_FMT_LL__ "d], " \
            "手动冻结张数[%" __SPK_FMT_LL__ "d], " \
            "日中累计获得权利金[%" __SPK_FMT_LL__ "d], " \
            "日中累计支出权利金[%" __SPK_FMT_LL__ "d], " \
            "日中累计开仓费用[%" __SPK_FMT_LL__ "d], " \
            "日中累计平仓费用[%" __SPK_FMT_LL__ "d], " \
            "权利仓行权冻结张数[%" __SPK_FMT_LL__ "d], " \
            "义务仓持仓保证金[%" __SPK_FMT_LL__ "d], " \
            "可平仓张数[%" __SPK_FMT_LL__ "d], " \
            "可行权张数[%" __SPK_FMT_LL__ "d], " \
            "总持仓张数[%" __SPK_FMT_LL__ "d], " \
            "持仓成本价[%" __SPK_FMT_LL__ "d], " \
            "可备兑标的券数量[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pHoldingItem->invAcctId,
            pHoldingItem->securityId,
            pHoldingItem->mktId,
            pHoldingItem->positionType,
            pHoldingItem->productType,
            pHoldingItem->securityType,
            pHoldingItem->subSecurityType,
            pHoldingItem->contractType,
            pHoldingItem->originalQty,
            pHoldingItem->originalAvlQty,
            pHoldingItem->originalCostAmt,
            pHoldingItem->totalOpenQty,
            pHoldingItem->uncomeQty,
            pHoldingItem->totalCloseQty,
            pHoldingItem->closeFrzQty,
            pHoldingItem->manualFrzQty,
            pHoldingItem->totalInPremium,
            pHoldingItem->totalOutPremium,
            pHoldingItem->totalOpenFee,
            pHoldingItem->totalCloseFee,
            pHoldingItem->exerciseFrzQty,
            pHoldingItem->positionMargin,
            pHoldingItem->closeAvlQty,
            pHoldingItem->exerciseAvlQty,
            pHoldingItem->sumQty,
            pHoldingItem->costPrice,
            pHoldingItem->coveredAvlUnderlyingQty);
}


/* 查询期权标的持仓信息回调 */
void
OesClientMySpi::OnQueryOptUnderlyingHolding(
        const OesOptUnderlyingHoldingItemT *pUnderlyingHld,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 期权标的持仓信息: index[%d], isEnd[%c], " \
            "证券账户[%s], " \
            "标的证券代码[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "标的市场代码[%" __SPK_FMT_HH__ "u], " \
            "标的证券类型[%" __SPK_FMT_HH__ "u], " \
            "标的证券子类型[%" __SPK_FMT_HH__ "u], " \
            "日初标的证券的总持仓数量[%" __SPK_FMT_LL__ "d], " \
            "日初标的证券的可用持仓数量[%" __SPK_FMT_LL__ "d], " \
            "日初备兑仓实际占用的标的证券数量[%" __SPK_FMT_LL__ "d], " \
            "日初备兑仓应占用的标的证券数量[%" __SPK_FMT_LL__ "d], "  \
            "当前备兑仓实际占用的标的证券数量[%" __SPK_FMT_LL__ "d], "  \
            "当前备兑仓占用标的证券的缺口数量[%" __SPK_FMT_LL__ "d], " \
            "当前可用于备兑开仓的标的持仓数量[%" __SPK_FMT_LL__ "d], " \
            "当前可锁定的标的持仓数量[%" __SPK_FMT_LL__ "d], " \
            "标的证券总持仓数量[%" __SPK_FMT_LL__ "d], " \
            "标的证券当日最大可减持额度[%" __SPK_FMT_LL__ "d]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pUnderlyingHld->invAcctId,
            pUnderlyingHld->underlyingSecurityId,
            pUnderlyingHld->mktId,
            pUnderlyingHld->underlyingMktId,
            pUnderlyingHld->underlyingSecurityType,
            pUnderlyingHld->underlyingSubSecurityType,
            pUnderlyingHld->originalHld,
            pUnderlyingHld->originalAvlHld,
            pUnderlyingHld->originalCoveredQty,
            pUnderlyingHld->initialCoveredQty,
            pUnderlyingHld->coveredQty,
            pUnderlyingHld->coveredGapQty,
            pUnderlyingHld->coveredAvlQty,
            pUnderlyingHld->lockAvlQty,
            pUnderlyingHld->sumHld,
            pUnderlyingHld->maxReduceQuota);
}


/* 查询期权限仓额度信息回调 */
void
OesClientMySpi::OnQueryOptPositionLimit(
        const OesOptPositionLimitItemT *pPositionLimitItem,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 期权限仓额度信息: index[%d], isEnd[%c], " \
              "证券账户[%s], " \
              "标的证券代码[%s], " \
              "市场代码[%" __SPK_FMT_HH__ "u], " \
              "标的市场代码[%" __SPK_FMT_HH__ "u], " \
              "标的证券类型[%" __SPK_FMT_HH__ "u], " \
              "标的证券子类型[%" __SPK_FMT_HH__ "u], " \
              "总持仓限额[%d]," \
              "权利仓限额[%d]," \
              "单日买入开仓限额[%d]," \
              "日初权利仓持仓数量[%d]," \
              "日初义务仓持仓数量[%d]," \
              "日初备兑义务仓持仓数量[%d]," \
              "未占用的总持仓限额[%d]," \
              "未占用的权利仓限额[%d]," \
              "未占用的单日买入开仓限额[%d]\n",
              pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
              pPositionLimitItem->invAcctId,
              pPositionLimitItem->underlyingSecurityId,
              pPositionLimitItem->mktId,
              pPositionLimitItem->underlyingMktId,
              pPositionLimitItem->underlyingSecurityType,
              pPositionLimitItem->underlyingSubSecurityType,
              pPositionLimitItem->totalPositionLimit,
              pPositionLimitItem->longPositionLimit,
              pPositionLimitItem->dailyBuyOpenLimit,
              pPositionLimitItem->originalLongQty,
              pPositionLimitItem->originalShortQty,
              pPositionLimitItem->originalCoveredQty,
              pPositionLimitItem->availableTotalPositionLimit,
              pPositionLimitItem->availableLongPositionLimit,
              pPositionLimitItem->availableDailyBuyOpenLimit);
}


/* 查询期权限购额度信息回调 */
void
OesClientMySpi::OnQueryOptPurchaseLimit(
        const OesOptPurchaseLimitItemT *pPurchaseLimitItem,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 期权限购额度信息: index[%d], isEnd[%c], " \
              "客户代码[%s], " \
              "资金账号[%s], " \
              "股东账号[%s], " \
              "市场代码[%" __SPK_FMT_HH__ "u], " \
              "客户类别[%" __SPK_FMT_HH__ "u], " \
              "限购额度[%" __SPK_FMT_LL__ "d], " \
              "日初占用限购额度[%" __SPK_FMT_LL__ "d], " \
              "日中累计开仓额度[%" __SPK_FMT_LL__ "d], " \
              "当前挂单冻结额度[%" __SPK_FMT_LL__ "d], " \
              "日中累计平仓额度[%" __SPK_FMT_LL__ "d], " \
              "当前可用限购额度[%" __SPK_FMT_LL__ "d]\n",
              pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
              pPurchaseLimitItem->custId,
              pPurchaseLimitItem->cashAcctId,
              pPurchaseLimitItem->invAcctId,
              pPurchaseLimitItem->mktId,
              pPurchaseLimitItem->custType,
              pPurchaseLimitItem->purchaseLimit,
              pPurchaseLimitItem->originalUsedPurchaseAmt,
              pPurchaseLimitItem->totalOpenPurchaseAmt,
              pPurchaseLimitItem->frzPurchaseAmt,
              pPurchaseLimitItem->totalClosePurchaseAmt,
              pPurchaseLimitItem->availablePurchaseLimit);
}


/* 查询到行权指派消息回调 */
void
OesClientMySpi::OnQueryOptExerciseAssign(
        const OesOptExerciseAssignItemT *pExerAssignItem,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到行权指派消息: index[%d], isEnd[%c], " \
            "证券账户[%s], " \
            "期权合约代码[%s], " \
            "期权合约名称[%s], " \
            "市场代码[%" __SPK_FMT_HH__ "u], " \
            "持仓方向[%" __SPK_FMT_HH__ "u], " \
            "产品类型[%" __SPK_FMT_HH__ "u], " \
            "证券类型[%" __SPK_FMT_HH__ "u], " \
            "证券子类型[%" __SPK_FMT_HH__ "u], " \
            "合约类型[%" __SPK_FMT_HH__ "u], " \
            "交割方式[%" __SPK_FMT_HH__ "u], " \
            "行权价格[%d]," \
            "行权张数[%d], " \
            "标的证券收付数量[%" __SPK_FMT_LL__ "d], " \
            "行权开始日期[%d]," \
            "行权结束日期[%d]," \
            "清算日期[%d]," \
            "交收日期[%d]," \
            "清算金额[%" __SPK_FMT_LL__ "d], " \
            "清算费用[%" __SPK_FMT_LL__ "d], " \
            "收付金额[%" __SPK_FMT_LL__ "d], " \
            "标的证券代码[%s], " \
            "标的市场代码[%" __SPK_FMT_HH__ "u], " \
            "标的证券类型[%" __SPK_FMT_HH__ "u]\n",
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pExerAssignItem->invAcctId,
            pExerAssignItem->securityId,
            pExerAssignItem->securityName,
            pExerAssignItem->mktId,
            pExerAssignItem->positionType,
            pExerAssignItem->productType,
            pExerAssignItem->securityType,
            pExerAssignItem->subSecurityType,
            pExerAssignItem->contractType,
            pExerAssignItem->deliveryType,
            pExerAssignItem->exercisePrice,
            pExerAssignItem->exerciseQty,
            pExerAssignItem->deliveryQty,
            pExerAssignItem->exerciseBeginDate,
            pExerAssignItem->exerciseEndDate,
            pExerAssignItem->clearingDate,
            pExerAssignItem->deliveryDate,
            pExerAssignItem->clearingAmt,
            pExerAssignItem->clearingFee,
            pExerAssignItem->settlementAmt,
            pExerAssignItem->underlyingSecurityId,
            pExerAssignItem->underlyingMktId,
            pExerAssignItem->underlyingSecurityType);
}


/* 查询到通知消息回调 */
void
OesClientMySpi::OnQueryNotifyInfo(const OesNotifyInfoItemT *pNotifyInfo,
        const OesQryCursorT *pCursor, int32 requestId) {
    fprintf(stdout, ">>> 查询到通知消息: index[%d], isEnd[%c], " \
            "通知消息序号[%d], " \
            "通知消息等级[%" __SPK_FMT_HH__ "u], " \
            "通知消息范围[%" __SPK_FMT_HH__ "u], " \
            "通知来源分类[%" __SPK_FMT_HH__ "u], " \
            "通知消息类型[%" __SPK_FMT_HH__ "u], " \
            "通知发出时间[%9d], 客户代码[%s], 通知内容[%s]\n", \
            pCursor->seqNo, pCursor->isEnd ? 'Y' : 'N',
            pNotifyInfo->notifySeqNo, pNotifyInfo->notifyLevel,
            pNotifyInfo->notifyScope, pNotifyInfo->notifySource,
            pNotifyInfo->notifyType, pNotifyInfo->tranTime,
            pNotifyInfo->custId, pNotifyInfo->content);
}


OesClientMySpi::OesClientMySpi(int32 something) {
    this->something = something;
}


OesClientMySpi::~OesClientMySpi() {
    /* do nothing */
}
