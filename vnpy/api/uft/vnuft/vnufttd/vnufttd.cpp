// vnuftmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnufttd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
void TdApi::OnFrontConnected()
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nResult)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nResult;
    this->task_queue.push(task);
};

void TdApi::OnRspAuthenticate(CHSRspAuthenticateField *pRspAuthenticate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPAUTHENTICATE;
    if (pRspAuthenticate)
    {
        CHSRspAuthenticateField *task_data = new CHSRspAuthenticateField();
        *task_data = *pRspAuthenticate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CHSRspUserLoginField *task_data = new CHSRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERPASSWORDUPDATE;
    if (pRspUserPasswordUpdate)
    {
        CHSRspUserPasswordUpdateField *task_data = new CHSRspUserPasswordUpdateField();
        *task_data = *pRspUserPasswordUpdate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERRORORDERINSERT;
    if (pRspOrderInsert)
    {
        CHSRspOrderInsertField *task_data = new CHSRspOrderInsertField();
        *task_data = *pRspOrderInsert;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPORDERACTION;
    if (pRspOrderAction)
    {
        CHSRspOrderActionField *task_data = new CHSRspOrderActionField();
        *task_data = *pRspOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROREXERCISEORDERINSERT;
    if (pRspExerciseOrderInsert)
    {
        CHSRspExerciseOrderInsertField *task_data = new CHSRspExerciseOrderInsertField();
        *task_data = *pRspExerciseOrderInsert;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPEXERCISEORDERACTION;
    if (pRspExerciseOrderAction)
    {
        CHSRspExerciseOrderActionField *task_data = new CHSRspExerciseOrderActionField();
        *task_data = *pRspExerciseOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspErrorLockInsert(CHSRspLockInsertField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERRORLOCKINSERT;
    if (pRspExerciseOrderAction)
    {
        CHSRspLockInsertField *task_data = new CHSRspLockInsertField();
        *task_data = *pRspExerciseOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPFORQUOTEINSERT;
    if (pRspForQuoteInsert)
    {
        CHSRspForQuoteInsertField *task_data = new CHSRspForQuoteInsertField();
        *task_data = *pRspForQuoteInsert;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERRORCOMBACTIONINSERT;
    if (pRspCombActionInsert)
    {
        CHSRspCombActionInsertField *task_data = new CHSRspCombActionInsertField();
        *task_data = *pRspCombActionInsert;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYMAXORDERVOLUME;
    if (pRspQueryMaxOrderVolume)
    {
        CHSRspQueryMaxOrderVolumeField *task_data = new CHSRspQueryMaxOrderVolumeField();
        *task_data = *pRspQueryMaxOrderVolume;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYLOCKVOLUME;
    if (pRspQueryLockVolume)
    {
        CHSRspQueryLockVolumeField *task_data = new CHSRspQueryLockVolumeField();
        *task_data = *pRspQueryLockVolume;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYEXERCISEVOLUME;
    if (pRspQueryExerciseVolume)
    {
        CHSRspQueryExerciseVolumeField *task_data = new CHSRspQueryExerciseVolumeField();
        *task_data = *pRspQueryExerciseVolume;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPOSITION;
    if (pRspQryPosition)
    {
        CHSRspQryPositionField *task_data = new CHSRspQryPositionField();
        *task_data = *pRspQryPosition;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRADINGACCOUNT;
    if (pRspQryTradingAccount)
    {
        CHSRspQryTradingAccountField *task_data = new CHSRspQryTradingAccountField();
        *task_data = *pRspQryTradingAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYORDER;
    if (pRspQryOrder)
    {
        CHSOrderField *task_data = new CHSOrderField();
        *task_data = *pRspQryOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRADE;
    if (pRspQryTrade)
    {
        CHSTradeField *task_data = new CHSTradeField();
        *task_data = *pRspQryTrade;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXERCISE;
    if (pRspQryExercise)
    {
        CHSExerciseField *task_data = new CHSExerciseField();
        *task_data = *pRspQryExercise;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYLOCK;
    if (pRspQryLock)
    {
        CHSLockField *task_data = new CHSLockField();
        *task_data = *pRspQryLock;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCOMBACTION;
    if (pRspQryCombAction)
    {
        CHSCombActionField *task_data = new CHSCombActionField();
        *task_data = *pRspQryCombAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPOSITIONCOMBINEDETAIL;
    if (pRspQryPositionCombineDetail)
    {
        CHSRspQryPositionCombineDetailField *task_data = new CHSRspQryPositionCombineDetailField();
        *task_data = *pRspQryPositionCombineDetail;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINSTRUMENT;
    if (pRspQryInstrument)
    {
        CHSRspQryInstrumentField *task_data = new CHSRspQryInstrumentField();
        *task_data = *pRspQryInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCOVEREDSHORT;
    if (pRspQryCoveredShort)
    {
        CHSRspQryCoveredShortField *task_data = new CHSRspQryCoveredShortField();
        *task_data = *pRspQryCoveredShort;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXERCISEASSIGN;
    if (pRspQryExerciseAssign)
    {
        CHSRspQryExerciseAssignField *task_data = new CHSRspQryExerciseAssignField();
        *task_data = *pRspQryExerciseAssign;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPTRANSFER;
    if (pRspTransfer)
    {
        CHSRspTransferField *task_data = new CHSRspTransferField();
        *task_data = *pRspTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRANSFER;
    if (pRspQryTransfer)
    {
        CHSRspQryTransferField *task_data = new CHSRspQryTransferField();
        *task_data = *pRspQryTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYBANKBALANCE;
    if (pRspQueryBankBalance)
    {
        CHSRspQueryBankBalanceField *task_data = new CHSRspQueryBankBalanceField();
        *task_data = *pRspQueryBankBalance;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYBANKACCOUNT;
    if (pRspQueryBankAccount)
    {
        CHSRspQueryBankAccountField *task_data = new CHSRspQueryBankAccountField();
        *task_data = *pRspQueryBankAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYBILLCONTENT;
    if (pRspQueryBillContent)
    {
        CHSRspQueryBillContentField *task_data = new CHSRspQueryBillContentField();
        *task_data = *pRspQueryBillContent;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPBILLCONFIRM;
    if (pRspBillConfirm)
    {
        CHSRspBillConfirmField *task_data = new CHSRspBillConfirmField();
        *task_data = *pRspBillConfirm;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYMARGIN;
    if (pRspQryMargin)
    {
        CHSRspQryMarginField *task_data = new CHSRspQryMarginField();
        *task_data = *pRspQryMargin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCOMMISSION;
    if (pRspQryCommission)
    {
        CHSRspQryCommissionField *task_data = new CHSRspQryCommissionField();
        *task_data = *pRspQryCommission;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPOSITIONDETAIL;
    if (pRspQryPositionDetail)
    {
        CHSRspQryPositionDetailField *task_data = new CHSRspQryPositionDetailField();
        *task_data = *pRspQryPositionDetail;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXCHANGERATE;
    if (pRspQryExchangeRate)
    {
        CHSRspQryExchangeRateField *task_data = new CHSRspQryExchangeRateField();
        *task_data = *pRspQryExchangeRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSYSCONFIG;
    if (pRspQrySysConfig)
    {
        CHSRspQrySysConfigField *task_data = new CHSRspQrySysConfigField();
        *task_data = *pRspQrySysConfig;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYDEPTHMARKETDATA;
    if (pRspQryDepthMarketData)
    {
        CHSDepthMarketDataField *task_data = new CHSDepthMarketDataField();
        *task_data = *pRspQryDepthMarketData;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CHSRspInfoField *task_error = new CHSRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CHSTradeField *pRtnTrade)
{
    Task task = Task();
    task.task_name = ONRTNTRADE;
    if (pRtnTrade)
    {
        CHSTradeField *task_data = new CHSTradeField();
        *task_data = *pRtnTrade;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CHSOrderField *pRtnOrder)
{
    Task task = Task();
    task.task_name = ONRTNORDER;
    if (pRtnOrder)
    {
        CHSOrderField *task_data = new CHSOrderField();
        *task_data = *pRtnOrder;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnExercise(CHSExerciseField *pRtnExercise)
{
    Task task = Task();
    task.task_name = ONRTNEXERCISE;
    if (pRtnExercise)
    {
        CHSExerciseField *task_data = new CHSExerciseField();
        *task_data = *pRtnExercise;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnCombAction(CHSCombActionField *pRtnCombAction)
{
    Task task = Task();
    task.task_name = ONRTNCOMBACTION;
    if (pRtnCombAction)
    {
        CHSCombActionField *task_data = new CHSCombActionField();
        *task_data = *pRtnCombAction;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnLock(CHSLockField *pRtnLock)
{
    Task task = Task();
    task.task_name = ONRTNLOCK;
    if (pRtnLock)
    {
        CHSLockField *task_data = new CHSLockField();
        *task_data = *pRtnLock;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};




///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TdApi::processTask()
{
    try
    {
        while (this->active)
        {
            Task task = this->task_queue.pop();

            switch (task.task_name)
            {
            case ONFRONTCONNECTED:
            {
                this->processFrontConnected(&task);
                break;
            }

            case ONFRONTDISCONNECTED:
            {
                this->processFrontDisconnected(&task);
                break;
            }

            case ONRSPAUTHENTICATE:
            {
                this->processRspAuthenticate(&task);
                break;
            }

            case ONRSPUSERLOGIN:
            {
                this->processRspUserLogin(&task);
                break;
            }

            case ONRSPUSERPASSWORDUPDATE:
            {
                this->processRspUserPasswordUpdate(&task);
                break;
            }

            case ONRSPERRORORDERINSERT:
            {
                this->processRspErrorOrderInsert(&task);
                break;
            }

            case ONRSPORDERACTION:
            {
                this->processRspOrderAction(&task);
                break;
            }

            case ONRSPERROREXERCISEORDERINSERT:
            {
                this->processRspErrorExerciseOrderInsert(&task);
                break;
            }

            case ONRSPEXERCISEORDERACTION:
            {
                this->processRspExerciseOrderAction(&task);
                break;
            }

            case ONRSPERRORLOCKINSERT:
            {
                this->processRspErrorLockInsert(&task);
                break;
            }

            case ONRSPFORQUOTEINSERT:
            {
                this->processRspForQuoteInsert(&task);
                break;
            }

            case ONRSPERRORCOMBACTIONINSERT:
            {
                this->processRspErrorCombActionInsert(&task);
                break;
            }

            case ONRSPQUERYMAXORDERVOLUME:
            {
                this->processRspQueryMaxOrderVolume(&task);
                break;
            }

            case ONRSPQUERYLOCKVOLUME:
            {
                this->processRspQueryLockVolume(&task);
                break;
            }

            case ONRSPQUERYEXERCISEVOLUME:
            {
                this->processRspQueryExerciseVolume(&task);
                break;
            }

            case ONRSPQRYPOSITION:
            {
                this->processRspQryPosition(&task);
                break;
            }

            case ONRSPQRYTRADINGACCOUNT:
            {
                this->processRspQryTradingAccount(&task);
                break;
            }

            case ONRSPQRYORDER:
            {
                this->processRspQryOrder(&task);
                break;
            }

            case ONRSPQRYTRADE:
            {
                this->processRspQryTrade(&task);
                break;
            }

            case ONRSPQRYEXERCISE:
            {
                this->processRspQryExercise(&task);
                break;
            }

            case ONRSPQRYLOCK:
            {
                this->processRspQryLock(&task);
                break;
            }

            case ONRSPQRYCOMBACTION:
            {
                this->processRspQryCombAction(&task);
                break;
            }

            case ONRSPQRYPOSITIONCOMBINEDETAIL:
            {
                this->processRspQryPositionCombineDetail(&task);
                break;
            }

            case ONRSPQRYINSTRUMENT:
            {
                this->processRspQryInstrument(&task);
                break;
            }

            case ONRSPQRYCOVEREDSHORT:
            {
                this->processRspQryCoveredShort(&task);
                break;
            }

            case ONRSPQRYEXERCISEASSIGN:
            {
                this->processRspQryExerciseAssign(&task);
                break;
            }

            case ONRSPTRANSFER:
            {
                this->processRspTransfer(&task);
                break;
            }

            case ONRSPQRYTRANSFER:
            {
                this->processRspQryTransfer(&task);
                break;
            }

            case ONRSPQUERYBANKBALANCE:
            {
                this->processRspQueryBankBalance(&task);
                break;
            }

            case ONRSPQUERYBANKACCOUNT:
            {
                this->processRspQueryBankAccount(&task);
                break;
            }

            case ONRSPQUERYBILLCONTENT:
            {
                this->processRspQueryBillContent(&task);
                break;
            }

            case ONRSPBILLCONFIRM:
            {
                this->processRspBillConfirm(&task);
                break;
            }

            case ONRSPQRYMARGIN:
            {
                this->processRspQryMargin(&task);
                break;
            }

            case ONRSPQRYCOMMISSION:
            {
                this->processRspQryCommission(&task);
                break;
            }

            case ONRSPQRYPOSITIONDETAIL:
            {
                this->processRspQryPositionDetail(&task);
                break;
            }

            case ONRSPQRYEXCHANGERATE:
            {
                this->processRspQryExchangeRate(&task);
                break;
            }

            case ONRSPQRYSYSCONFIG:
            {
                this->processRspQrySysConfig(&task);
                break;
            }

            case ONRSPQRYDEPTHMARKETDATA:
            {
                this->processRspQryDepthMarketData(&task);
                break;
            }

            case ONRTNTRADE:
            {
                this->processRtnTrade(&task);
                break;
            }

            case ONRTNORDER:
            {
                this->processRtnOrder(&task);
                break;
            }

            case ONRTNEXERCISE:
            {
                this->processRtnExercise(&task);
                break;
            }

            case ONRTNCOMBACTION:
            {
                this->processRtnCombAction(&task);
                break;
            }

            case ONRTNLOCK:
            {
                this->processRtnLock(&task);
                break;
            }

            };
        }
    }
    catch (const TerminatedError&)
    {
    }
};

void TdApi::processFrontConnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(task->task_id);
};

void TdApi::processRspAuthenticate(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspAuthenticateField *task_data = (CHSRspAuthenticateField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["AppID"] = toUtf(task_data->AppID);
        data["AuthCode"] = toUtf(task_data->AuthCode);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspAuthenticate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspUserLoginField *task_data = (CHSRspUserLoginField*)task->task_data;
        data["BranchID"] = task_data->BranchID;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["UserName"] = toUtf(task_data->UserName);
        data["TradingDay"] = task_data->TradingDay;
        data["PreTradingDay"] = task_data->PreTradingDay;
        data["BillConfirmFlag"] = task_data->BillConfirmFlag;
        data["SessionID"] = task_data->SessionID;
        data["UserApplicationType"] = task_data->UserApplicationType;
        data["UserApplicationInfo"] = toUtf(task_data->UserApplicationInfo);
        data["RiskLevel"] = toUtf(task_data->RiskLevel);
        data["LastMacAddress"] = toUtf(task_data->LastMacAddress);
        data["LastIPAddress"] = toUtf(task_data->LastIPAddress);
        data["LastLoginTime"] = task_data->LastLoginTime;
        data["CZCETime"] = task_data->CZCETime;
        data["DCETime"] = task_data->DCETime;
        data["SHFETime"] = task_data->SHFETime;
        data["CFFEXTime"] = task_data->CFFEXTime;
        data["INETime"] = task_data->INETime;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserPasswordUpdate(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspUserPasswordUpdateField *task_data = (CHSRspUserPasswordUpdateField*)task->task_data;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorOrderInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspOrderInsertField *task_data = (CHSRspOrderInsertField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderPrice"] = task_data->OrderPrice;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["OrderCommand"] = toUtf(task_data->OrderCommand);
        data["InsertTime"] = task_data->InsertTime;
        data["MinVolume"] = task_data->MinVolume;
        data["SpringPrice"] = task_data->SpringPrice;
        data["SwapOrderFlag"] = task_data->SwapOrderFlag;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspErrorOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspOrderActionField *task_data = (CHSRspOrderActionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertTime"] = task_data->InsertTime;
        data["OrderActionRef"] = toUtf(task_data->OrderActionRef);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorExerciseOrderInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspExerciseOrderInsertField *task_data = (CHSRspExerciseOrderInsertField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["SessionID"] = task_data->SessionID;
        data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
        data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["OrderVolume"] = task_data->OrderVolume;
        data["ExerciseType"] = task_data->ExerciseType;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertTime"] = task_data->InsertTime;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspErrorExerciseOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExerciseOrderAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspExerciseOrderActionField *task_data = (CHSRspExerciseOrderActionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
        data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
        data["SessionID"] = task_data->SessionID;
        data["OrderStatus"] = task_data->OrderStatus;
        data["ExecOrderActionRef"] = toUtf(task_data->ExecOrderActionRef);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspExerciseOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorLockInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspLockInsertField *task_data = (CHSRspLockInsertField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["LockType"] = task_data->LockType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["UnderlyingAccountID"] = toUtf(task_data->UnderlyingAccountID);
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertTime"] = task_data->InsertTime;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspErrorLockInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspForQuoteInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspForQuoteInsertField *task_data = (CHSRspForQuoteInsertField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["OrderStatus"] = task_data->OrderStatus;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspForQuoteInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorCombActionInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspCombActionInsertField *task_data = (CHSRspCombActionInsertField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
        data["CombPositionID"] = toUtf(task_data->CombPositionID);
        data["CombDirection"] = task_data->CombDirection;
        data["OrderVolume"] = task_data->OrderVolume;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertTime"] = task_data->InsertTime;
        data["Direction"] = task_data->Direction;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspErrorCombActionInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryMaxOrderVolumeField *task_data = (CHSRspQueryMaxOrderVolumeField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["MaxOrderVolume"] = task_data->MaxOrderVolume;
        data["MaxOrderVolumeUnit"] = task_data->MaxOrderVolumeUnit;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["OrderCommand"] = toUtf(task_data->OrderCommand);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderPrice"] = task_data->OrderPrice;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryMaxOrderVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryLockVolume(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryLockVolumeField *task_data = (CHSRspQueryLockVolumeField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["LockType"] = task_data->LockType;
        data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryLockVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryExerciseVolume(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryExerciseVolumeField *task_data = (CHSRspQueryExerciseVolumeField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["MaxOrderVolumeUnit"] = task_data->MaxOrderVolumeUnit;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryExerciseVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPosition(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryPositionField *task_data = (CHSRspQryPositionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["HedgeType"] = task_data->HedgeType;
        data["YdPositionVolume"] = task_data->YdPositionVolume;
        data["PositionVolume"] = task_data->PositionVolume;
        data["TodayPositionVolume"] = task_data->TodayPositionVolume;
        data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
        data["TodayAvailablePositionVolume"] = task_data->TodayAvailablePositionVolume;
        data["PositionMargin"] = task_data->PositionMargin;
        data["Premium"] = task_data->Premium;
        data["Commission"] = task_data->Commission;
        data["OpenFrozenVolume"] = task_data->OpenFrozenVolume;
        data["CloseFrozenVolume"] = task_data->CloseFrozenVolume;
        data["CombVolume"] = task_data->CombVolume;
        data["ExerciseFrozenVolume"] = task_data->ExerciseFrozenVolume;
        data["FrozenMargin"] = task_data->FrozenMargin;
        data["ExerciseFrozenMargin"] = task_data->ExerciseFrozenMargin;
        data["FrozenPremium"] = task_data->FrozenPremium;
        data["FrozenCommission"] = task_data->FrozenCommission;
        data["OpenVolume"] = task_data->OpenVolume;
        data["CloseVolume"] = task_data->CloseVolume;
        data["OpenBalance"] = task_data->OpenBalance;
        data["CloseBalance"] = task_data->CloseBalance;
        data["OpenCost"] = task_data->OpenCost;
        data["PositionCost"] = task_data->PositionCost;
        data["PositionProfit"] = task_data->PositionProfit;
        data["CloseProfit"] = task_data->CloseProfit;
        data["OptionsMarketValue"] = task_data->OptionsMarketValue;
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTradingAccount(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryTradingAccountField *task_data = (CHSRspQryTradingAccountField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["YdBalance"] = task_data->YdBalance;
        data["YdPositionMargin"] = task_data->YdPositionMargin;
        data["YdFundEquity"] = task_data->YdFundEquity;
        data["FundEquity"] = task_data->FundEquity;
        data["OptionsMarketValue"] = task_data->OptionsMarketValue;
        data["Equity"] = task_data->Equity;
        data["AvailableBalance"] = task_data->AvailableBalance;
        data["WithdrawBalance"] = task_data->WithdrawBalance;
        data["Margin"] = task_data->Margin;
        data["FrozenMargin"] = task_data->FrozenMargin;
        data["ExerciseFrozenMargin"] = task_data->ExerciseFrozenMargin;
        data["RiskDegree"] = task_data->RiskDegree;
        data["Premium"] = task_data->Premium;
        data["FrozenPremium"] = task_data->FrozenPremium;
        data["Commission"] = task_data->Commission;
        data["FrozenCommission"] = task_data->FrozenCommission;
        data["CloseProfit"] = task_data->CloseProfit;
        data["PositionProfit"] = task_data->PositionProfit;
        data["CloseProfitByDate"] = task_data->CloseProfitByDate;
        data["PositionProfitByDate"] = task_data->PositionProfitByDate;
        data["Deposit"] = task_data->Deposit;
        data["Withdraw"] = task_data->Withdraw;
        data["FundMortgage"] = task_data->FundMortgage;
        data["WarrantMortgage"] = task_data->WarrantMortgage;
        data["FrozenBalance"] = task_data->FrozenBalance;
        data["UnFrozenBalance"] = task_data->UnFrozenBalance;
        data["CurrencyID"] = task_data->CurrencyID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryTradingAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSOrderField *task_data = (CHSOrderField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderPrice"] = task_data->OrderPrice;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradeVolume"] = task_data->TradeVolume;
        data["CancelVolume"] = task_data->CancelVolume;
        data["TradePrice"] = task_data->TradePrice;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ReportTime"] = task_data->ReportTime;
        data["OrderCommand"] = toUtf(task_data->OrderCommand);
        data["MinVolume"] = task_data->MinVolume;
        data["SpringPrice"] = task_data->SpringPrice;
        data["SwapOrderFlag"] = task_data->SwapOrderFlag;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSTradeField *task_data = (CHSTradeField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["TradeID"] = toUtf(task_data->TradeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["TradeVolume"] = task_data->TradeVolume;
        data["TradePrice"] = task_data->TradePrice;
        data["TradingDay"] = task_data->TradingDay;
        data["TradeTime"] = task_data->TradeTime;
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExercise(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSExerciseField *task_data = (CHSExerciseField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
        data["SessionID"] = task_data->SessionID;
        data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["HedgeType"] = task_data->HedgeType;
        data["ExerciseType"] = task_data->ExerciseType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["OrderSource"] = task_data->OrderSource;
        data["CloseFlag"] = task_data->CloseFlag;
        data["OffsetFlag"] = task_data->OffsetFlag;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryExercise(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryLock(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSLockField *task_data = (CHSLockField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["LockType"] = task_data->LockType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryLock(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCombAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSCombActionField *task_data = (CHSCombActionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
        data["CombPositionID"] = toUtf(task_data->CombPositionID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
        data["Direction"] = task_data->Direction;
        data["CombDirection"] = task_data->CombDirection;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryCombAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPositionCombineDetail(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryPositionCombineDetailField *task_data = (CHSRspQryPositionCombineDetailField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["CombPositionID"] = toUtf(task_data->CombPositionID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
        data["HedgeType"] = task_data->HedgeType;
        data["Direction"] = task_data->Direction;
        data["YdPositionVolume"] = task_data->YdPositionVolume;
        data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
        data["TotalCombVolume"] = task_data->TotalCombVolume;
        data["TotalSplitVolume"] = task_data->TotalSplitVolume;
        data["PositionMargin"] = task_data->PositionMargin;
        data["OpenDate"] = task_data->OpenDate;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryPositionCombineDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrument(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryInstrumentField *task_data = (CHSRspQryInstrumentField*)task->task_data;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["InstrumentName"] = toUtf(task_data->InstrumentName);
        data["InstrumentEngName"] = toUtf(task_data->InstrumentEngName);
        data["ProductID"] = toUtf(task_data->ProductID);
        data["ProductType"] = task_data->ProductType;
        data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
        data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
        data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
        data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
        data["VolumeMultiple"] = task_data->VolumeMultiple;
        data["PriceTick"] = task_data->PriceTick;
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["ExercisePrice"] = task_data->ExercisePrice;
        data["OptionsType"] = task_data->OptionsType;
        data["TradingFlag"] = task_data->TradingFlag;
        data["MarketDate"] = task_data->MarketDate;
        data["ExpireDate"] = task_data->ExpireDate;
        data["BeginExerciseDate"] = task_data->BeginExerciseDate;
        data["EndExerciseDate"] = task_data->EndExerciseDate;
        data["BeginDeliveryDate"] = task_data->BeginDeliveryDate;
        data["EndDeliveryDate"] = task_data->EndDeliveryDate;
        data["CurrencyID"] = task_data->CurrencyID;
        data["CombType"] = task_data->CombType;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCoveredShort(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryCoveredShortField *task_data = (CHSRspQryCoveredShortField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["CoveredLockVolume"] = task_data->CoveredLockVolume;
        data["CoveredShortVolume"] = task_data->CoveredShortVolume;
        data["CoveredEstimateShortVolume"] = task_data->CoveredEstimateShortVolume;
        data["MsgContent"] = toUtf(task_data->MsgContent);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryCoveredShort(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExerciseAssign(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryExerciseAssignField *task_data = (CHSRspQryExerciseAssignField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["PositionType"] = task_data->PositionType;
        data["OptionsType"] = task_data->OptionsType;
        data["ExercisePrice"] = task_data->ExercisePrice;
        data["ExerciseVolume"] = task_data->ExerciseVolume;
        data["DeliveryVolume"] = task_data->DeliveryVolume;
        data["ExerciseFrozenBalance"] = task_data->ExerciseFrozenBalance;
        data["SettlementBalance"] = task_data->SettlementBalance;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryExerciseAssign(data, error, task->task_id, task->task_last);
};

void TdApi::processRspTransfer(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspTransferField *task_data = (CHSRspTransferField*)task->task_data;
        data["TransferSerialID"] = task_data->TransferSerialID;
        data["BankID"] = toUtf(task_data->BankID);
        data["TransferType"] = task_data->TransferType;
        data["OccurBalance"] = task_data->OccurBalance;
        data["CurrencyID"] = task_data->CurrencyID;
        data["TransferOccasion"] = toUtf(task_data->TransferOccasion);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspTransfer(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTransfer(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryTransferField *task_data = (CHSRspQryTransferField*)task->task_data;
        data["TransferSerialID"] = task_data->TransferSerialID;
        data["BankID"] = toUtf(task_data->BankID);
        data["BankName"] = toUtf(task_data->BankName);
        data["BusinessName"] = toUtf(task_data->BusinessName);
        data["OccurBalance"] = task_data->OccurBalance;
        data["PostBalance"] = task_data->PostBalance;
        data["TransferTime"] = task_data->TransferTime;
        data["TransferStatus"] = task_data->TransferStatus;
        data["TransferSource"] = task_data->TransferSource;
        data["Remarks"] = toUtf(task_data->Remarks);
        data["CurrencyID"] = task_data->CurrencyID;
        data["OrderSourceDate"] = task_data->OrderSourceDate;
        data["TradingDay"] = task_data->TradingDay;
        data["TransferOccasion"] = toUtf(task_data->TransferOccasion);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryTransfer(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBankBalance(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryBankBalanceField *task_data = (CHSRspQueryBankBalanceField*)task->task_data;
        data["TransferSerialID"] = task_data->TransferSerialID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryBankBalance(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBankAccount(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryBankAccountField *task_data = (CHSRspQueryBankAccountField*)task->task_data;
        data["BankID"] = toUtf(task_data->BankID);
        data["BankName"] = toUtf(task_data->BankName);
        data["BankAccountID"] = toUtf(task_data->BankAccountID);
        data["CurrencyID"] = task_data->CurrencyID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryBankAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBillContent(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQueryBillContentField *task_data = (CHSRspQueryBillContentField*)task->task_data;
        data["BillContent"] = toUtf(task_data->BillContent);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQueryBillContent(data, error, task->task_id, task->task_last);
};

void TdApi::processRspBillConfirm(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspBillConfirmField *task_data = (CHSRspBillConfirmField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["BillConfirmStatus"] = task_data->BillConfirmStatus;
        data["ConfirmDate"] = task_data->ConfirmDate;
        data["ConfirmTime"] = task_data->ConfirmTime;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspBillConfirm(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryMargin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryMarginField *task_data = (CHSRspQryMarginField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["HedgeType"] = task_data->HedgeType;
        data["LongMarginRatio"] = task_data->LongMarginRatio;
        data["LongMargin"] = task_data->LongMargin;
        data["ShortMarginRatio"] = task_data->ShortMarginRatio;
        data["ShortMargin"] = task_data->ShortMargin;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryMargin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCommission(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryCommissionField *task_data = (CHSRspQryCommissionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["ProductType"] = task_data->ProductType;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["LongOpenCommissionRatio"] = task_data->LongOpenCommissionRatio;
        data["LongOpenCommission"] = task_data->LongOpenCommission;
        data["LongCloseCommissionRatio"] = task_data->LongCloseCommissionRatio;
        data["LongCloseCommission"] = task_data->LongCloseCommission;
        data["LongCloseTodayCommissionRatio"] = task_data->LongCloseTodayCommissionRatio;
        data["LongCloseTodayCommission"] = task_data->LongCloseTodayCommission;
        data["ShortOpenCommissionRatio"] = task_data->ShortOpenCommissionRatio;
        data["ShortOpenCommission"] = task_data->ShortOpenCommission;
        data["ShortCloseCommissionRatio"] = task_data->ShortCloseCommissionRatio;
        data["ShortCloseCommission"] = task_data->ShortCloseCommission;
        data["ShortCloseTodayCommissionRatio"] = task_data->ShortCloseTodayCommissionRatio;
        data["ShortCloseTodayCommission"] = task_data->ShortCloseTodayCommission;
        data["ExerciseCommissionRatio"] = task_data->ExerciseCommissionRatio;
        data["ExerciseCommission"] = task_data->ExerciseCommission;
        data["TradeValueRatio"] = task_data->TradeValueRatio;
        data["StockValue"] = task_data->StockValue;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryCommission(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPositionDetail(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryPositionDetailField *task_data = (CHSRspQryPositionDetailField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["TradeID"] = toUtf(task_data->TradeID);
        data["OpenDate"] = task_data->OpenDate;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["HedgeType"] = task_data->HedgeType;
        data["TradeVolume"] = task_data->TradeVolume;
        data["PositionPrice"] = task_data->PositionPrice;
        data["TodayCloseVolume"] = task_data->TodayCloseVolume;
        data["ArbitragePositionID"] = toUtf(task_data->ArbitragePositionID);
        data["LegID"] = task_data->LegID;
        data["TradeType"] = task_data->TradeType;
        data["PositionMargin"] = task_data->PositionMargin;
        data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryPositionDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExchangeRate(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQryExchangeRateField *task_data = (CHSRspQryExchangeRateField*)task->task_data;
        data["FromCurrencyID"] = task_data->FromCurrencyID;
        data["ToCurrencyID"] = task_data->ToCurrencyID;
        data["ExchangeRate"] = task_data->ExchangeRate;
        data["FromCurrencyUnit"] = task_data->FromCurrencyUnit;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryExchangeRate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQrySysConfig(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSRspQrySysConfigField *task_data = (CHSRspQrySysConfigField*)task->task_data;
        data["ConfigNo"] = task_data->ConfigNo;
        data["ConfigValue"] = toUtf(task_data->ConfigValue);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQrySysConfig(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryDepthMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSDepthMarketDataField *task_data = (CHSDepthMarketDataField*)task->task_data;
        data["TradingDay"] = task_data->TradingDay;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["LastPrice"] = task_data->LastPrice;
        data["PreSettlementPrice"] = task_data->PreSettlementPrice;
        data["PreClosePrice"] = task_data->PreClosePrice;
        data["OpenPrice"] = task_data->OpenPrice;
        data["HighestPrice"] = task_data->HighestPrice;
        data["LowestPrice"] = task_data->LowestPrice;
        data["TradeVolume"] = task_data->TradeVolume;
        data["TradeBalance"] = task_data->TradeBalance;
        data["OpenInterest"] = task_data->OpenInterest;
        data["ClosePrice"] = task_data->ClosePrice;
        data["SettlementPrice"] = task_data->SettlementPrice;
        data["UpperLimitPrice"] = task_data->UpperLimitPrice;
        data["LowerLimitPrice"] = task_data->LowerLimitPrice;
        data["PreDelta"] = task_data->PreDelta;
        data["CurrDelta"] = task_data->CurrDelta;
        data["UpdateTime"] = task_data->UpdateTime;
        data["BidPrice1"] = task_data->BidPrice1;
        data["BidVolume1"] = task_data->BidVolume1;
        data["AskPrice1"] = task_data->AskPrice1;
        data["AskVolume1"] = task_data->AskVolume1;
        data["BidPrice2"] = task_data->BidPrice2;
        data["BidVolume2"] = task_data->BidVolume2;
        data["AskPrice2"] = task_data->AskPrice2;
        data["AskVolume2"] = task_data->AskVolume2;
        data["BidPrice3"] = task_data->BidPrice3;
        data["BidVolume3"] = task_data->BidVolume3;
        data["AskPrice3"] = task_data->AskPrice3;
        data["AskVolume3"] = task_data->AskVolume3;
        data["BidPrice4"] = task_data->BidPrice4;
        data["BidVolume4"] = task_data->BidVolume4;
        data["AskPrice4"] = task_data->AskPrice4;
        data["AskVolume4"] = task_data->AskVolume4;
        data["BidPrice5"] = task_data->BidPrice5;
        data["BidVolume5"] = task_data->BidVolume5;
        data["AskPrice5"] = task_data->AskPrice5;
        data["AskVolume5"] = task_data->AskVolume5;
        data["AveragePrice"] = task_data->AveragePrice;
        data["PreOpenInterest"] = task_data->PreOpenInterest;
        data["InstrumentTradeStatus"] = task_data->InstrumentTradeStatus;
        data["OpenRestriction"] = toUtf(task_data->OpenRestriction);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryDepthMarketData(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnTrade(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSTradeField *task_data = (CHSTradeField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["TradeID"] = toUtf(task_data->TradeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["TradeVolume"] = task_data->TradeVolume;
        data["TradePrice"] = task_data->TradePrice;
        data["TradingDay"] = task_data->TradingDay;
        data["TradeTime"] = task_data->TradeTime;
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        delete task_data;
    }
    this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSOrderField *task_data = (CHSOrderField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
        data["SessionID"] = task_data->SessionID;
        data["OrderRef"] = toUtf(task_data->OrderRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderPrice"] = task_data->OrderPrice;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradeVolume"] = task_data->TradeVolume;
        data["CancelVolume"] = task_data->CancelVolume;
        data["TradePrice"] = task_data->TradePrice;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ReportTime"] = task_data->ReportTime;
        data["OrderCommand"] = toUtf(task_data->OrderCommand);
        data["MinVolume"] = task_data->MinVolume;
        data["SpringPrice"] = task_data->SpringPrice;
        data["SwapOrderFlag"] = task_data->SwapOrderFlag;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    this->onRtnOrder(data);
};

void TdApi::processRtnExercise(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSExerciseField *task_data = (CHSExerciseField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
        data["SessionID"] = task_data->SessionID;
        data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["HedgeType"] = task_data->HedgeType;
        data["ExerciseType"] = task_data->ExerciseType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["OrderSource"] = task_data->OrderSource;
        data["CloseFlag"] = task_data->CloseFlag;
        data["OffsetFlag"] = task_data->OffsetFlag;
        delete task_data;
    }
    this->onRtnExercise(data);
};

void TdApi::processRtnCombAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSCombActionField *task_data = (CHSCombActionField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
        data["CombPositionID"] = toUtf(task_data->CombPositionID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
        data["Direction"] = task_data->Direction;
        data["CombDirection"] = task_data->CombDirection;
        data["HedgeType"] = task_data->HedgeType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertDate"] = task_data->InsertDate;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    this->onRtnCombAction(data);
};

void TdApi::processRtnLock(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CHSLockField *task_data = (CHSLockField*)task->task_data;
        data["AccountID"] = toUtf(task_data->AccountID);
        data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["LockType"] = task_data->LockType;
        data["OrderVolume"] = task_data->OrderVolume;
        data["OrderStatus"] = task_data->OrderStatus;
        data["TradingDay"] = task_data->TradingDay;
        data["InsertTime"] = task_data->InsertTime;
        data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
        data["OrderSource"] = task_data->OrderSource;
        delete task_data;
    }
    this->onRtnLock(data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::newTradeApi(string pszFlowPath)
{
    this->api = NewTradeApi(pszFlowPath.c_str());
    this->api->RegisterSpi(this);
};

int TdApi::init(string pszLicFile, string pszSafeLevel, string pszPwd, string pszSslFile, string pszSslPwd)
{
    this->active = true;
    this->task_thread = thread(&TdApi::processTask, this);

    int i = this->api->Init((char*)pszLicFile.c_str(), (char*)pszSafeLevel.c_str(), (char*)pszPwd.c_str(), (char*)pszSslFile.c_str(), (char*)pszSslPwd.c_str());
    return i;
};

int TdApi::join()
{
    int i = this->api->Join();
    return i;
};

int TdApi::exit()
{
    this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();

    this->api->RegisterSpi(NULL);
    this->api->ReleaseApi();
    this->api = NULL;
    return 1;
};

int TdApi::rgisterSubModel(string pszSubModel)
{
    int i = this->api->RegisterSubModel((char*)pszSubModel.c_str());
    return i;
};

int TdApi::registerFront(string pszFrontAddress)
{
    int i = this->api->RegisterFront((char*)pszFrontAddress.c_str());
    return i;
};

int TdApi::registerFensServer(string pszFensAddress, string pszAccountID)
{
    int i = this->api->RegisterFensServer((char*)pszFensAddress.c_str(), (char*)pszAccountID.c_str());
    return i;
};

string TdApi::getApiErrorMsg(int nErrorCode)
{
    string error = toUtf(this->api->GetApiErrorMsg(nErrorCode));
    return error;
};

int TdApi::getTradingDate()
{
    int day = this->api->GetTradingDate();
    return day;
};

int TdApi::reqAuthenticate(const dict &req, int reqid)
{
    CHSReqAuthenticateField myreq = CHSReqAuthenticateField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "AccountID", myreq.AccountID);
    getString(req, "Password", myreq.Password);
    getString(req, "AppID", myreq.AppID);
    getString(req, "AuthCode", myreq.AuthCode);
    int i = this->api->ReqAuthenticate(&myreq, reqid);
    return i;
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
    CHSReqUserLoginField myreq = CHSReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "AccountID", myreq.AccountID);
    getString(req, "Password", myreq.Password);
    getChar(req, "UserApplicationType", &myreq.UserApplicationType);
    getString(req, "UserApplicationInfo", myreq.UserApplicationInfo);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "IPAddress", myreq.IPAddress);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int TdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
    CHSReqUserPasswordUpdateField myreq = CHSReqUserPasswordUpdateField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "PasswordType", &myreq.PasswordType);
    getString(req, "Password", myreq.Password);
    getString(req, "NewPassword", myreq.NewPassword);
    int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
    return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
    CHSReqOrderInsertField myreq = CHSReqOrderInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "OrderRef", myreq.OrderRef);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getChar(req, "Direction", &myreq.Direction);
    getChar(req, "OffsetFlag", &myreq.OffsetFlag);
    getChar(req, "HedgeType", &myreq.HedgeType);
    getDouble(req, "OrderPrice", &myreq.OrderPrice);
    getDouble(req, "OrderVolume", &myreq.OrderVolume);
    getString(req, "OrderCommand", myreq.OrderCommand);
    getDouble(req, "MinVolume", &myreq.MinVolume);
    getDouble(req, "SpringPrice", &myreq.SpringPrice);
    getChar(req, "SwapOrderFlag", &myreq.SwapOrderFlag);
    int i = this->api->ReqOrderInsert(&myreq, reqid);
    return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
    CHSReqOrderActionField myreq = CHSReqOrderActionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "OrderSysID", myreq.OrderSysID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getInt(req, "SessionID", &myreq.SessionID);
    getString(req, "OrderRef", myreq.OrderRef);
    getString(req, "OrderActionRef", myreq.OrderActionRef);
    int i = this->api->ReqOrderAction(&myreq, reqid);
    return i;
};

int TdApi::reqExerciseOrderInsert(const dict &req, int reqid)
{
    CHSReqExerciseOrderInsertField myreq = CHSReqExerciseOrderInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExerciseRef", myreq.ExerciseRef);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getDouble(req, "OrderVolume", &myreq.OrderVolume);
    getChar(req, "ExerciseType", &myreq.ExerciseType);
    getChar(req, "HedgeType", &myreq.HedgeType);
    int i = this->api->ReqExerciseOrderInsert(&myreq, reqid);
    return i;
};

int TdApi::reqExerciseOrderAction(const dict &req, int reqid)
{
    CHSReqExerciseOrderActionField myreq = CHSReqExerciseOrderActionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "ExerciseOrderSysID", myreq.ExerciseOrderSysID);
    getString(req, "ExerciseRef", myreq.ExerciseRef);
    getInt(req, "SessionID", &myreq.SessionID);
    getString(req, "ExecOrderActionRef", myreq.ExecOrderActionRef);
    int i = this->api->ReqExerciseOrderAction(&myreq, reqid);
    return i;
};

int TdApi::reqLockInsert(const dict &req, int reqid)
{
    CHSReqLockInsertField myreq = CHSReqLockInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
    getChar(req, "LockType", &myreq.LockType);
    getDouble(req, "OrderVolume", &myreq.OrderVolume);
    int i = this->api->ReqLockInsert(&myreq, reqid);
    return i;
};

int TdApi::reqForQuoteInsert(const dict &req, int reqid)
{
    CHSReqForQuoteInsertField myreq = CHSReqForQuoteInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqForQuoteInsert(&myreq, reqid);
    return i;
};

int TdApi::reqCombActionInsert(const dict &req, int reqid)
{
    CHSReqCombActionInsertField myreq = CHSReqCombActionInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "CombStrategyID", myreq.CombStrategyID);
    getString(req, "CombPositionID", myreq.CombPositionID);
    getChar(req, "CombDirection", &myreq.CombDirection);
    getDouble(req, "OrderVolume", &myreq.OrderVolume);
    getChar(req, "HedgeType", &myreq.HedgeType);
    getChar(req, "Direction", &myreq.Direction);
    int i = this->api->ReqCombActionInsert(&myreq, reqid);
    return i;
};

int TdApi::reqQueryMaxOrderVolume(const dict &req, int reqid)
{
    CHSReqQueryMaxOrderVolumeField myreq = CHSReqQueryMaxOrderVolumeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "OrderCommand", myreq.OrderCommand);
    getChar(req, "Direction", &myreq.Direction);
    getChar(req, "OffsetFlag", &myreq.OffsetFlag);
    getChar(req, "HedgeType", &myreq.HedgeType);
    getDouble(req, "OrderPrice", &myreq.OrderPrice);
    int i = this->api->ReqQueryMaxOrderVolume(&myreq, reqid);
    return i;
};

int TdApi::reqQueryLockVolume(const dict &req, int reqid)
{
    CHSReqQueryLockVolumeField myreq = CHSReqQueryLockVolumeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
    getChar(req, "LockType", &myreq.LockType);
    int i = this->api->ReqQueryLockVolume(&myreq, reqid);
    return i;
};

int TdApi::reqQueryExerciseVolume(const dict &req, int reqid)
{
    CHSReqQueryExerciseVolumeField myreq = CHSReqQueryExerciseVolumeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQueryExerciseVolume(&myreq, reqid);
    return i;
};

int TdApi::reqQryPosition(const dict &req, int reqid)
{
    CHSReqQryPositionField myreq = CHSReqQryPositionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryPosition(&myreq, reqid);
    return i;
};

int TdApi::reqQryTradingAccount(const dict &req, int reqid)
{
    CHSReqQryTradingAccountField myreq = CHSReqQryTradingAccountField();
    memset(&myreq, 0, sizeof(myreq));
    int i = this->api->ReqQryTradingAccount(&myreq, reqid);
    return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
    CHSReqQryOrderField myreq = CHSReqQryOrderField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "OrderSysID", myreq.OrderSysID);
    int i = this->api->ReqQryOrder(&myreq, reqid);
    return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
    CHSReqQryTradeField myreq = CHSReqQryTradeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryTrade(&myreq, reqid);
    return i;
};

int TdApi::reqQryExercise(const dict &req, int reqid)
{
    CHSReqQryExerciseField myreq = CHSReqQryExerciseField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "ExerciseOrderSysID", myreq.ExerciseOrderSysID);
    int i = this->api->ReqQryExercise(&myreq, reqid);
    return i;
};

int TdApi::reqQryLock(const dict &req, int reqid)
{
    CHSReqQryLockField myreq = CHSReqQryLockField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
    getString(req, "LockOrderSysID", myreq.LockOrderSysID);
    int i = this->api->ReqQryLock(&myreq, reqid);
    return i;
};

int TdApi::reqQryCombAction(const dict &req, int reqid)
{
    CHSReqQryCombActionField myreq = CHSReqQryCombActionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "CombOrderSysID", myreq.CombOrderSysID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryCombAction(&myreq, reqid);
    return i;
};

int TdApi::reqQryPositionCombineDetail(const dict &req, int reqid)
{
    CHSReqQryPositionCombineDetailField myreq = CHSReqQryPositionCombineDetailField();
    memset(&myreq, 0, sizeof(myreq));
    int i = this->api->ReqQryPositionCombineDetail(&myreq, reqid);
    return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
    CHSReqQryInstrumentField myreq = CHSReqQryInstrumentField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryInstrument(&myreq, reqid);
    return i;
};

int TdApi::reqQryCoveredShort(const dict &req, int reqid)
{
    CHSReqQryCoveredShortField myreq = CHSReqQryCoveredShortField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    int i = this->api->ReqQryCoveredShort(&myreq, reqid);
    return i;
};

int TdApi::reqQryExerciseAssign(const dict &req, int reqid)
{
    CHSReqQryExerciseAssignField myreq = CHSReqQryExerciseAssignField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getChar(req, "PositionType", &myreq.PositionType);
    int i = this->api->ReqQryExerciseAssign(&myreq, reqid);
    return i;
};

int TdApi::reqTransfer(const dict &req, int reqid)
{
    CHSReqTransferField myreq = CHSReqTransferField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BankID", myreq.BankID);
    getChar(req, "TransferType", &myreq.TransferType);
    getDouble(req, "OccurBalance", &myreq.OccurBalance);
    getString(req, "FundPassword", myreq.FundPassword);
    getString(req, "BankPassword", myreq.BankPassword);
    getChar(req, "CurrencyID", &myreq.CurrencyID);
    getString(req, "TransferOccasion", myreq.TransferOccasion);
    int i = this->api->ReqTransfer(&myreq, reqid);
    return i;
};

int TdApi::reqQryTransfer(const dict &req, int reqid)
{
    CHSReqQryTransferField myreq = CHSReqQryTransferField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BankID", myreq.BankID);
    getInt(req, "TransferSerialID", &myreq.TransferSerialID);
    int i = this->api->ReqQryTransfer(&myreq, reqid);
    return i;
};

int TdApi::reqQueryBankBalance(const dict &req, int reqid)
{
    CHSReqQueryBankBalanceField myreq = CHSReqQueryBankBalanceField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BankID", myreq.BankID);
    getString(req, "FundPassword", myreq.FundPassword);
    getString(req, "BankPassword", myreq.BankPassword);
    getChar(req, "CurrencyID", &myreq.CurrencyID);
    int i = this->api->ReqQueryBankBalance(&myreq, reqid);
    return i;
};

int TdApi::reqQueryBankAccount(const dict &req, int reqid)
{
    CHSReqQueryBankAccountField myreq = CHSReqQueryBankAccountField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BankID", myreq.BankID);
    getChar(req, "CurrencyID", &myreq.CurrencyID);
    int i = this->api->ReqQueryBankAccount(&myreq, reqid);
    return i;
};

int TdApi::reqQueryBillContent(const dict &req, int reqid)
{
    CHSReqQueryBillContentField myreq = CHSReqQueryBillContentField();
    memset(&myreq, 0, sizeof(myreq));
    getInt(req, "BeginDate", &myreq.BeginDate);
    getInt(req, "EndDate", &myreq.EndDate);
    int i = this->api->ReqQueryBillContent(&myreq, reqid);
    return i;
};

int TdApi::reqBillConfirm(const dict &req, int reqid)
{
    CHSReqBillConfirmField myreq = CHSReqBillConfirmField();
    memset(&myreq, 0, sizeof(myreq));
    int i = this->api->ReqBillConfirm(&myreq, reqid);
    return i;
};

int TdApi::reqQryMargin(const dict &req, int reqid)
{
    CHSReqQryMarginField myreq = CHSReqQryMarginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
    getChar(req, "HedgeType", &myreq.HedgeType);
    int i = this->api->ReqQryMargin(&myreq, reqid);
    return i;
};

int TdApi::reqQryCommission(const dict &req, int reqid)
{
    CHSReqQryCommissionField myreq = CHSReqQryCommissionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getChar(req, "ProductType", &myreq.ProductType);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
    int i = this->api->ReqQryCommission(&myreq, reqid);
    return i;
};

int TdApi::reqQryExchangeRate(const dict &req, int reqid)
{
    CHSReqQryExchangeRateField myreq = CHSReqQryExchangeRateField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "FromCurrencyID", &myreq.FromCurrencyID);
    getChar(req, "ToCurrencyID", &myreq.ToCurrencyID);
    int i = this->api->ReqQryExchangeRate(&myreq, reqid);
    return i;
};

int TdApi::reqQryPositionDetail(const dict &req, int reqid)
{
    CHSReqQryPositionDetailField myreq = CHSReqQryPositionDetailField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryPositionDetail(&myreq, reqid);
    return i;
};

int TdApi::reqQrySysConfig(const dict &req, int reqid)
{
    CHSReqQrySysConfigField myreq = CHSReqQrySysConfigField();
    memset(&myreq, 0, sizeof(myreq));
    int i = this->api->ReqQrySysConfig(&myreq, reqid);
    return i;
};

int TdApi::reqQryDepthMarketData(const dict &req, int reqid)
{
    CHSReqQryDepthMarketDataField myreq = CHSReqQryDepthMarketDataField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryDepthMarketData(&myreq, reqid);
    return i;
};



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;
    
    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onFrontConnected);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onFrontDisconnected(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onFrontDisconnected, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspAuthenticate, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspUserPasswordUpdate, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspErrorOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspErrorOrderInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspErrorExerciseOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspErrorExerciseOrderInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspExerciseOrderAction(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspExerciseOrderAction, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspErrorLockInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspErrorLockInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspForQuoteInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspErrorCombActionInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspErrorCombActionInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryMaxOrderVolume, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryLockVolume(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryLockVolume, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryExerciseVolume(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryExerciseVolume, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryPosition, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingAccount, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryExercise, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryLock(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryLock, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryCombAction, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionCombineDetail, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryInstrument, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCoveredShort(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryCoveredShort, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryExerciseAssign(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryExerciseAssign, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspTransfer(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspTransfer, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTransfer(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryTransfer, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryBankBalance(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryBankBalance, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryBankAccount(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryBankAccount, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQueryBillContent(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQueryBillContent, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspBillConfirm(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspBillConfirm, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryMargin(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryMargin, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCommission(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryCommission, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryPositionDetail(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionDetail, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryExchangeRate, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQrySysConfig(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQrySysConfig, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryDepthMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnTrade(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnTrade, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnOrder(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnExercise(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnExercise, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnCombAction(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnCombAction, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnLock(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnLock, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };




};


PYBIND11_MODULE(vnufttd, m)
{
    class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
    TdApi
        .def(init<>())
        .def("newTradeApi", &TdApi::newTradeApi)
        .def("init", &TdApi::init)
        .def("join", &TdApi::join)
        .def("exit", &TdApi::exit)
        .def("rgisterSubModel", &TdApi::rgisterSubModel)
        .def("registerFront", &TdApi::registerFront)
        .def("registerFensServer", &TdApi::registerFensServer)
        .def("getApiErrorMsg", &TdApi::getApiErrorMsg)
        .def("getTradingDate", &TdApi::getTradingDate)

        .def("reqAuthenticate", &TdApi::reqAuthenticate)
        .def("reqUserLogin", &TdApi::reqUserLogin)
        .def("reqUserPasswordUpdate", &TdApi::reqUserPasswordUpdate)
        .def("reqOrderInsert", &TdApi::reqOrderInsert)
        .def("reqOrderAction", &TdApi::reqOrderAction)
        .def("reqExerciseOrderInsert", &TdApi::reqExerciseOrderInsert)
        .def("reqExerciseOrderAction", &TdApi::reqExerciseOrderAction)
        .def("reqLockInsert", &TdApi::reqLockInsert)
        .def("reqForQuoteInsert", &TdApi::reqForQuoteInsert)
        .def("reqCombActionInsert", &TdApi::reqCombActionInsert)
        .def("reqQueryMaxOrderVolume", &TdApi::reqQueryMaxOrderVolume)
        .def("reqQueryLockVolume", &TdApi::reqQueryLockVolume)
        .def("reqQueryExerciseVolume", &TdApi::reqQueryExerciseVolume)
        .def("reqQryPosition", &TdApi::reqQryPosition)
        .def("reqQryTradingAccount", &TdApi::reqQryTradingAccount)
        .def("reqQryOrder", &TdApi::reqQryOrder)
        .def("reqQryTrade", &TdApi::reqQryTrade)
        .def("reqQryExercise", &TdApi::reqQryExercise)
        .def("reqQryLock", &TdApi::reqQryLock)
        .def("reqQryCombAction", &TdApi::reqQryCombAction)
        .def("reqQryPositionCombineDetail", &TdApi::reqQryPositionCombineDetail)
        .def("reqQryInstrument", &TdApi::reqQryInstrument)
        .def("reqQryCoveredShort", &TdApi::reqQryCoveredShort)
        .def("reqQryExerciseAssign", &TdApi::reqQryExerciseAssign)
        .def("reqTransfer", &TdApi::reqTransfer)
        .def("reqQryTransfer", &TdApi::reqQryTransfer)
        .def("reqQueryBankBalance", &TdApi::reqQueryBankBalance)
        .def("reqQueryBankAccount", &TdApi::reqQueryBankAccount)
        .def("reqQueryBillContent", &TdApi::reqQueryBillContent)
        .def("reqBillConfirm", &TdApi::reqBillConfirm)
        .def("reqQryMargin", &TdApi::reqQryMargin)
        .def("reqQryCommission", &TdApi::reqQryCommission)
        .def("reqQryExchangeRate", &TdApi::reqQryExchangeRate)
        .def("reqQryPositionDetail", &TdApi::reqQryPositionDetail)
        .def("reqQrySysConfig", &TdApi::reqQrySysConfig)
        .def("reqQryDepthMarketData", &TdApi::reqQryDepthMarketData)

        .def("onFrontConnected", &TdApi::onFrontConnected)
        .def("onFrontDisconnected", &TdApi::onFrontDisconnected)
        .def("onRspAuthenticate", &TdApi::onRspAuthenticate)
        .def("onRspUserLogin", &TdApi::onRspUserLogin)
        .def("onRspUserPasswordUpdate", &TdApi::onRspUserPasswordUpdate)
        .def("onRspErrorOrderInsert", &TdApi::onRspErrorOrderInsert)
        .def("onRspOrderAction", &TdApi::onRspOrderAction)
        .def("onRspErrorExerciseOrderInsert", &TdApi::onRspErrorExerciseOrderInsert)
        .def("onRspExerciseOrderAction", &TdApi::onRspExerciseOrderAction)
        .def("onRspErrorLockInsert", &TdApi::onRspErrorLockInsert)
        .def("onRspForQuoteInsert", &TdApi::onRspForQuoteInsert)
        .def("onRspErrorCombActionInsert", &TdApi::onRspErrorCombActionInsert)
        .def("onRspQueryMaxOrderVolume", &TdApi::onRspQueryMaxOrderVolume)
        .def("onRspQueryLockVolume", &TdApi::onRspQueryLockVolume)
        .def("onRspQueryExerciseVolume", &TdApi::onRspQueryExerciseVolume)
        .def("onRspQryPosition", &TdApi::onRspQryPosition)
        .def("onRspQryTradingAccount", &TdApi::onRspQryTradingAccount)
        .def("onRspQryOrder", &TdApi::onRspQryOrder)
        .def("onRspQryTrade", &TdApi::onRspQryTrade)
        .def("onRspQryExercise", &TdApi::onRspQryExercise)
        .def("onRspQryLock", &TdApi::onRspQryLock)
        .def("onRspQryCombAction", &TdApi::onRspQryCombAction)
        .def("onRspQryPositionCombineDetail", &TdApi::onRspQryPositionCombineDetail)
        .def("onRspQryInstrument", &TdApi::onRspQryInstrument)
        .def("onRspQryCoveredShort", &TdApi::onRspQryCoveredShort)
        .def("onRspQryExerciseAssign", &TdApi::onRspQryExerciseAssign)
        .def("onRspTransfer", &TdApi::onRspTransfer)
        .def("onRspQryTransfer", &TdApi::onRspQryTransfer)
        .def("onRspQueryBankBalance", &TdApi::onRspQueryBankBalance)
        .def("onRspQueryBankAccount", &TdApi::onRspQueryBankAccount)
        .def("onRspQueryBillContent", &TdApi::onRspQueryBillContent)
        .def("onRspBillConfirm", &TdApi::onRspBillConfirm)
        .def("onRspQryMargin", &TdApi::onRspQryMargin)
        .def("onRspQryCommission", &TdApi::onRspQryCommission)
        .def("onRspQryPositionDetail", &TdApi::onRspQryPositionDetail)
        .def("onRspQryExchangeRate", &TdApi::onRspQryExchangeRate)
        .def("onRspQrySysConfig", &TdApi::onRspQrySysConfig)
        .def("onRspQryDepthMarketData", &TdApi::onRspQryDepthMarketData)
        .def("onRtnTrade", &TdApi::onRtnTrade)
        .def("onRtnOrder", &TdApi::onRtnOrder)
        .def("onRtnExercise", &TdApi::onRtnExercise)
        .def("onRtnCombAction", &TdApi::onRtnCombAction)
        .def("onRtnLock", &TdApi::onRtnLock)
        ;

}
