/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#ifndef _TORA_TSTPDATATYPE_H
#define _TORA_TSTPDATATYPE_H

#include <limits.h>
#include <float.h>

#define INT_NULL_VAL INT_MAX

#define FLOAT_NULL_VAL DBL_MAX

#define CHAR_NULL_VAL 0

#define WORD_NULL_VAL SHRT_MAX

#ifdef WINDOWS
#define LONG_NULL_VAL _I64_MAX
#else
#define LONG_NULL_VAL  LLONG_MAX
#endif

#define POINT_NULL_VAL NULL

inline void set_null(int &v)
{
	v = INT_NULL_VAL;
}

inline bool is_null(int v)
{
	return v == INT_NULL_VAL;
}

inline void set_null(double &v)
{
	v = FLOAT_NULL_VAL;
}

inline bool is_null(double v)
{
	return v == FLOAT_NULL_VAL;
}

inline void set_null(char &v)
{
	v = CHAR_NULL_VAL;
}

inline bool is_null(char v)
{
	return v == CHAR_NULL_VAL;
}

inline void set_null(short &v)
{
	v = WORD_NULL_VAL;
}

inline bool is_null(short v)
{
	return v == WORD_NULL_VAL;
}

#ifdef WINDOWS
inline void set_null(__int64 &v)
#else
inline void set_null(long long &v)
#endif
{
	v = LONG_NULL_VAL;
}

#ifdef WINDOWS
inline bool is_null(__int64 v)
#else
inline bool is_null(long long v)
#endif
{
	return v == LONG_NULL_VAL;
}

inline void set_null(char *v)
{
	v[0] = '\0';
}

inline bool is_null(const char *v)
{
	const char *p=v;
	while (*p)
	{
		if (*p!=' ')
		{
			return false;
		}
		p++;
	}
	return true;
}

enum TORA_TE_RESUME_TYPE
{
	TORA_TERT_RESTART = 0,
	TORA_TERT_RESUME,
	TORA_TERT_QUICK
};


/////////////////////////////////////////////////////////////////////////
/// TTORATstpDateType是一个日期类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDateType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTimeType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMillisecType是一个时间（毫秒）类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpMillisecType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPriceType是一个价格类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPriceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRatioType是一个比率类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpRatioType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMoneyType是一个资金类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpMoneyType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeType是一个数量类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLargeVolumeType是一个大额数量类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpLargeVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBoolType是一个布尔型类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpBoolType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSequenceNoType是一个流水号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSequenceNoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSerialType是一个流水号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSerialType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCommFluxType是一个通讯流量类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpCommFluxType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRoleIDType是一个角色编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpRoleIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRoleDescriptionType是一个角色描述类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpRoleDescriptionType[161];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFunctionsType是一个功能权限集合类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpFunctionsType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDeviceIDType是一个设备标识类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDeviceIDType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDeviceSerialType是一个设备序列类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDeviceSerialType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExchangeIDType是一个交易所代码类型
/////////////////////////////////////////////////////////////////////////
///内部使用)
#define TORA_TSTP_EXD_SSE_FO 'h'
///内部使用)
#define TORA_TSTP_EXD_SZSE_FO 'z'
///通用(内部使用)
#define TORA_TSTP_EXD_COMM '0'
///上海交易所
#define TORA_TSTP_EXD_SSE '1'
///深圳交易所
#define TORA_TSTP_EXD_SZSE '2'
///香港交易所
#define TORA_TSTP_EXD_HK '3'

typedef char TTORATstpExchangeIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAuthModeType是一个认证方式类型
/////////////////////////////////////////////////////////////////////////
///密码
#define TORA_TSTP_AM_Password '0'
///指纹
#define TORA_TSTP_AM_FingerPrint '1'

typedef char TTORATstpAuthModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeMultipleType是一个合约数量乘数类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpVolumeMultipleType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIdCardNoType是一个证件编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIdCardNoType[51];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserIDType是一个交易用户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpUserIDType[16];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTradeIDType是一个成交编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTradeIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderSysIDType是一个系统报单编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderSysIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondOrderIDType是一个条件报单编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpCondOrderIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPasswordType是一个密码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpPasswordType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFrontIDType是一个前置编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpFrontIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSessionIDType是一个会话编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSessionIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProductInfoType是一个产品信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpProductInfoType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProtocolInfoType是一个协议信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpProtocolInfoType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpErrorIDType是一个错误代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpErrorIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpErrorMsgType是一个错误信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpErrorMsgType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPositionTypeType是一个持仓类型类型
/////////////////////////////////////////////////////////////////////////
///净持仓
#define TORA_TSTP_PT_Net '1'
///综合持仓
#define TORA_TSTP_PT_Gross '2'

typedef char TTORATstpPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParameterCharValType是一个参数文本值类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpParameterCharValType[101];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpNameType是一个名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpNameType[61];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpListingMarketType是一个挂牌市场类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpListingMarketType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProductIDType是一个证券品种代码类型
/////////////////////////////////////////////////////////////////////////
///通用(内部使用)
#define TORA_TSTP_PID_COMMON '0'
///上海股票
#define TORA_TSTP_PID_SHStock '1'
///上海配股配债
#define TORA_TSTP_PID_SHWarrant '2'
///上海基金
#define TORA_TSTP_PID_SHFund '3'
///上海债券
#define TORA_TSTP_PID_SHBond '4'
///上海标准券
#define TORA_TSTP_PID_SHStandard '5'
///上海质押式回购
#define TORA_TSTP_PID_SHRepurchase '6'
///深圳股票
#define TORA_TSTP_PID_SZStock '7'
///深圳配股配债
#define TORA_TSTP_PID_SZWarrant '8'
///深圳基金
#define TORA_TSTP_PID_SZFund '9'
///深圳债券
#define TORA_TSTP_PID_SZBond 'a'
///深圳标准券
#define TORA_TSTP_PID_SZStandard 'b'
///深圳质押式回购
#define TORA_TSTP_PID_SZRepurchase 'c'

typedef char TTORATstpProductIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityIDType是一个证券代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSecurityIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParValueType是一个面值类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpParValueType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPriceTickType是一个最小变动价位类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPriceTickType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTradingUnitType是一个交易单位类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpTradingUnitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityStatusType是一个证券状态类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSecurityStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAccountIDType是一个投资者资金帐号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpAccountIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInvestorIDType是一个投资者代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpInvestorIDType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAddressType是一个通讯地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpAddressType[101];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDepartmentIDType是一个部门代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDepartmentIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTerminalInfoType是一个终端信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTerminalInfoType[256];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpShareholderIDType是一个股东账户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpShareholderIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPbuIDType是一个交易单元代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpPbuIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIPAddressType是一个IP地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIPAddressType[16];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMacAddressType是一个Mac地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpMacAddressType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLangType是一个语言类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpLangType[17];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInterestType是一个利息类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpInterestType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderLocalIDType是一个本地报单编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderLocalIDType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPositionVolumeType是一个证券数量类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPositionVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBusinessUnitIDType是一个投资单元代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBusinessUnitIDType[17];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBusinessUnitNameType是一个投资单元名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBusinessUnitNameType[61];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeStampType是一个时间戳类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpTimeStampType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBigTimeStampType是一个长时间戳类型
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpBigTimeStampType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityNameType是一个证券名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSecurityNameType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExternalSerialType是一个外部流水号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpExternalSerialType[65];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderRefType是一个报单引用类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderRefType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRequestIDType是一个请求编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpRequestIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIntSerialType是一个整数流水号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpIntSerialType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInvestorNameType是一个投资者名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpInvestorNameType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserNameType是一个用户名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpUserNameType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLoginLimitType是一个登录限制类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpLoginLimitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCurrencyIDType是一个币种类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCurrencyIDType[4];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBankIDType是一个银行代码类型
/////////////////////////////////////////////////////////////////////////
///中国建设银行
#define TORA_TSTP_BKID_CCB '1'
///中国农业银行
#define TORA_TSTP_BKID_ABC '2'
///中国工商银行
#define TORA_TSTP_BKID_ICBC '3'
///中国银行
#define TORA_TSTP_BKID_BOC '4'
///中国招商银行
#define TORA_TSTP_BKID_CMB '5'
///中国交通银行
#define TORA_TSTP_BKID_BC '6'
///浦东发展银行
#define TORA_TSTP_BKID_SPDB '7'
///兴业银行
#define TORA_TSTP_BKID_CIB '8'
///中国光大银行
#define TORA_TSTP_BKID_CEB '9'
///广东发展银行
#define TORA_TSTP_BKID_GDB 'a'
///南京银行
#define TORA_TSTP_BKID_NJCB 'b'
///上海银行
#define TORA_TSTP_BKID_SHCB 'c'
///中信银行
#define TORA_TSTP_BKID_CITICB 'd'
///华夏银行
#define TORA_TSTP_BKID_HXB 'e'
///民生银行
#define TORA_TSTP_BKID_CMBC 'f'
///平安银行
#define TORA_TSTP_BKID_PACB 'g'
///宁波银行
#define TORA_TSTP_BKID_NBCB 'h'

typedef char TTORATstpBankIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBankAccountIDType是一个签约银行账号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBankAccountIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferReasonType是一个外围系统仓位调拨原因类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTransferReasonType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCombOffsetFlagType是一个组合开平标志类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCombOffsetFlagType[5];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCombHedgeFlagType是一个组合投机套保标志类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCombHedgeFlagType[5];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExchangeInstIDType是一个交易所合约代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpExchangeInstIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTelephoneType是一个联系电话类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTelephoneType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMobileType是一个手机类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpMobileType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTraderIDType是一个交易员代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTraderIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLongVolumeType是一个LongVolume类型
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpLongVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLongSequenceType是一个序号类型
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpLongSequenceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderUnitType是一个申报单位类型
/////////////////////////////////////////////////////////////////////////
///手
#define TORA_TSTP_OUT_Shou '0'
///股
#define TORA_TSTP_OUT_Gu '1'
///份
#define TORA_TSTP_OUT_Fen '2'
///张
#define TORA_TSTP_OUT_Zhang '3'

typedef char TTORATstpOrderUnitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIdCardTypeType是一个证件类型类型
/////////////////////////////////////////////////////////////////////////
///组织机构代码
#define TORA_TSTP_ICT_EID '0'
///中国公民身份证
#define TORA_TSTP_ICT_IDCard '1'
///军官证
#define TORA_TSTP_ICT_OfficerIDCard '2'
///警官证
#define TORA_TSTP_ICT_PoliceIDCard '3'
///士兵证
#define TORA_TSTP_ICT_SoldierIDCard '4'
///户口簿
#define TORA_TSTP_ICT_HouseholdRegister  '5'
///护照
#define TORA_TSTP_ICT_Passport '6'
///台胞证
#define TORA_TSTP_ICT_TaiwanCompatriotIDCard  '7'
///回乡证
#define TORA_TSTP_ICT_HomeComingCard '8'
///营业执照号
#define TORA_TSTP_ICT_LicenseNo '9'
///税务登记号/当地纳税ID
#define TORA_TSTP_ICT_TaxNo 'A'
///港澳居民来往内地通行证
#define TORA_TSTP_ICT_HMMainlandTravelPermit 'B'
///台湾居民来往大陆通行证
#define TORA_TSTP_ICT_TwMainlandTravelPermit 'C'
///驾照
#define TORA_TSTP_ICT_DrivingLicense 'D'
///当地社保ID
#define TORA_TSTP_ICT_SocialID 'F'
///当地身份证
#define TORA_TSTP_ICT_LocalID 'G'
///商业登记证
#define TORA_TSTP_ICT_BusinessRegistration 'H'
///港澳永久性居民身份证
#define TORA_TSTP_ICT_HKMCIDCard 'I'
///人行开户许可证
#define TORA_TSTP_ICT_AccountsPermits 'J'
///其他证件
#define TORA_TSTP_ICT_OtherCard 'x'

typedef char TTORATstpIdCardTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAccountTypeType是一个资金账户类型类型
/////////////////////////////////////////////////////////////////////////
///普通
#define TORA_TSTP_FAT_Normal '1'
///信用
#define TORA_TSTP_FAT_Credit '2'
///衍生品
#define TORA_TSTP_FAT_Derivatives '3'

typedef char TTORATstpAccountTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDirectionType是一个报单类别类型
/////////////////////////////////////////////////////////////////////////
///买入
#define TORA_TSTP_D_Buy '0'
///卖出
#define TORA_TSTP_D_Sell '1'
///ETF申购
#define TORA_TSTP_D_ETFPur '2'
///ETF赎回
#define TORA_TSTP_D_ETFRed '3'
///新股申购
#define TORA_TSTP_D_IPO '4'
///正回购
#define TORA_TSTP_D_Repurchase '5'
///逆回购
#define TORA_TSTP_D_ReverseRepur '6'
///开放式基金申购
#define TORA_TSTP_D_OeFundPur '8'
///开放式基金赎回
#define TORA_TSTP_D_OeFundRed '9'
///担保品划入
#define TORA_TSTP_D_CollateralIn 'a'
///担保品划出
#define TORA_TSTP_D_CollateralOut 'b'
///质押入库
#define TORA_TSTP_D_PledgeIn 'd'
///质押出库
#define TORA_TSTP_D_PledgeOut 'e'
///配股配债
#define TORA_TSTP_D_Rationed 'f'
///开放式基金拆分
#define TORA_TSTP_D_Split 'g'
///开放式基金合并
#define TORA_TSTP_D_Merge 'h'
///融资买入
#define TORA_TSTP_D_MarginBuy 'i'
///融券卖出
#define TORA_TSTP_D_ShortSell 'j'
///卖券还款
#define TORA_TSTP_D_SellRepayment 'k'
///买券还券
#define TORA_TSTP_D_BuyRepayment 'l'
///还券划转
#define TORA_TSTP_D_SecurityRepay 'm'
///余券划转
#define TORA_TSTP_D_RemainTransfer 'n'
///债转股
#define TORA_TSTP_D_BondConvertStock 't'
///债券回售
#define TORA_TSTP_D_BondPutback 'u'

typedef char TTORATstpDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBrokerageTypeType是一个佣金类型类型
/////////////////////////////////////////////////////////////////////////
///毛佣金
#define TORA_TSTP_BT_Gross '0'
///净佣金
#define TORA_TSTP_BT_Net '1'

typedef char TTORATstpBrokerageTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserTypeType是一个用户类型类型
/////////////////////////////////////////////////////////////////////////
///经纪公司用户
#define TORA_TSTP_UTYPE_BrokerUser '0'
///超级用户
#define TORA_TSTP_UTYPE_SuperUser '1'
///投资者用户
#define TORA_TSTP_UTYPE_Investor '2'

typedef char TTORATstpUserTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpContingentConditionType是一个触发条件类型
/////////////////////////////////////////////////////////////////////////
///成交触发
#define TORA_TSTP_CC_TradeTouch '0'
///撤单触发
#define TORA_TSTP_CC_CancelTouch '1'
///时间触发
#define TORA_TSTP_CC_TimeTouch '2'
///交易时段触发
#define TORA_TSTP_CC_SegmentTouch '3'
///最新价大于等于条件价
#define TORA_TSTP_CC_LastPriceGreaterThanStopPrice '4'
///最新价小于等于条件价
#define TORA_TSTP_CC_LastPriceLesserThanStopPrice '5'
///卖一价大于等于条件价
#define TORA_TSTP_CC_AskPriceGreaterEqualStopPrice '6'
///卖一价小于等于条件价
#define TORA_TSTP_CC_AskPriceLesserEqualStopPrice '7'
///买一价大于等于条件价
#define TORA_TSTP_CC_BidPriceGreaterEqualStopPrice '8'
///买一价小于等于条件价
#define TORA_TSTP_CC_BidPriceLesserEqualStopPrice '9'

typedef char TTORATstpContingentConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpETFCurrenceReplaceStatusType是一个ETF现金替代标志类型
/////////////////////////////////////////////////////////////////////////
///禁止现金替代
#define TORA_TSTP_ETFCTSTAT_Forbidden '0'
///可以现金替代
#define TORA_TSTP_ETFCTSTAT_Allow '1'
///必须现金替代
#define TORA_TSTP_ETFCTSTAT_Force '2'
///跨市退补现金替代
#define TORA_TSTP_ETFCTSTAT_CBAllow '3'
///跨市必须现金替代
#define TORA_TSTP_ETFCTSTAT_CBForce '4'

typedef char TTORATstpETFCurrenceReplaceStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperateSourceType是一个操作来源类型
/////////////////////////////////////////////////////////////////////////
///实时上场
#define TORA_TSTP_OPRTSRC_DBCommand '0'
///API调用
#define TORA_TSTP_OPRTSRC_SyncAPI '1'

typedef char TTORATstpOperateSourceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperwayType是一个委托方式类型
/////////////////////////////////////////////////////////////////////////
///电话委托
#define TORA_TSTP_OPERW_Telephone '0'
///柜台委托
#define TORA_TSTP_OPERW_OTC '1'
///移动客户端委托
#define TORA_TSTP_OPERW_MobileClient '2'
///PC客户端委托
#define TORA_TSTP_OPERW_PCClient '3'
///TY委托
#define TORA_TSTP_OPERW_TY '4'

typedef char TTORATstpOperwayType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperwaysType是一个委托方式合集类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOperwaysType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderPriceTypeType是一个报单价格条件类型
/////////////////////////////////////////////////////////////////////////
///任意价
#define TORA_TSTP_OPT_AnyPrice '1'
///限价
#define TORA_TSTP_OPT_LimitPrice '2'
///最优价
#define TORA_TSTP_OPT_BestPrice '3'
///最新价
#define TORA_TSTP_OPT_LastPrice '4'
///卖一价
#define TORA_TSTP_OPT_AskPrice1 '5'
///买一价
#define TORA_TSTP_OPT_BidPrice1 '6'
///相关价
#define TORA_TSTP_OPT_Relative '7'
///五档价
#define TORA_TSTP_OPT_FiveLevelPrice 'G'
///本方最优
#define TORA_TSTP_OPT_HomeBestPrice 'a'

typedef char TTORATstpOrderPriceTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderVolumeTypeType是一个报单数量类型类型
/////////////////////////////////////////////////////////////////////////
///自定义数量
#define TORA_TSTP_OVT_CustomVol '1'
///相关数量
#define TORA_TSTP_OVT_RelativeVol '2'

typedef char TTORATstpOrderVolumeTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeConditionType是一个有效期类型类型
/////////////////////////////////////////////////////////////////////////
///立即完成，否则撤销
#define TORA_TSTP_TC_IOC '1'
///本节有效
#define TORA_TSTP_TC_GFS '2'
///当日有效
#define TORA_TSTP_TC_GFD '3'
///指定日期前有效
#define TORA_TSTP_TC_GTD '4'
///撤销前有效
#define TORA_TSTP_TC_GTC '5'
///集合竞价有效
#define TORA_TSTP_TC_GFA '6'

typedef char TTORATstpTimeConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeConditionType是一个成交量类型类型
/////////////////////////////////////////////////////////////////////////
///任何数量
#define TORA_TSTP_VC_AV '1'
///最小数量
#define TORA_TSTP_VC_MV '2'
///全部数量
#define TORA_TSTP_VC_CV '3'

typedef char TTORATstpVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpForceCloseReasonType是一个强平原因类型
/////////////////////////////////////////////////////////////////////////
///非强平
#define TORA_TSTP_FCC_NotForceClose '0'
///资金不足
#define TORA_TSTP_FCC_LackDeposit '1'
///客户超仓
#define TORA_TSTP_FCC_ClientOverPositionLimit '2'
///会员超仓
#define TORA_TSTP_FCC_MemberOverPositionLimit '3'
///持仓非整数倍
#define TORA_TSTP_FCC_NotMultiple '4'
///违规
#define TORA_TSTP_FCC_Violation '5'
///其它
#define TORA_TSTP_FCC_Other '6'

typedef char TTORATstpForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFileOrderTypeType是一个文件报单类别类型
/////////////////////////////////////////////////////////////////////////
///复核
#define TORA_TSTP_EOT_Review '0'
///撤单
#define TORA_TSTP_EOT_Cancel '1'
///限价单
#define TORA_TSTP_EOT_Limit '2'
///最优五档即时成交剩余撤销
#define TORA_TSTP_EOT_FRC '3'
///最优五档即时成交剩余转限价
#define TORA_TSTP_EOT_FRL '4'
///对手方最优
#define TORA_TSTP_EOT_BP '5'
///本方最优
#define TORA_TSTP_EOT_HP '6'
///立即成交剩余撤销
#define TORA_TSTP_EOT_FAK '7'
///全额成交或撤销
#define TORA_TSTP_EOT_FOK '8'

typedef char TTORATstpFileOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferDirectionType是一个转移方向类型
/////////////////////////////////////////////////////////////////////////
///蓝补
#define TORA_TSTP_TRNSD_In '0'
///红冲
#define TORA_TSTP_TRNSD_Out '1'
///调入
#define TORA_TSTP_TRNSD_MoveIn '2'
///调出
#define TORA_TSTP_TRNSD_MoveOut '3'
///冻结
#define TORA_TSTP_TRNSD_Freeze '4'
///解冻
#define TORA_TSTP_TRNSD_UnFreeze '5'
///证券转银行
#define TORA_TSTP_TRNSD_StockToBank '6'
///银行转证券
#define TORA_TSTP_TRNSD_BankToStock '7'

typedef char TTORATstpTransferDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCollateralDirectionType是一个担保品划入方向类型
/////////////////////////////////////////////////////////////////////////
///担保品划入
#define TORA_TSTP_CLTD_CollateralIn '6'
///担保品划出
#define TORA_TSTP_CLTD_CollateralOut '7'

typedef char TTORATstpCollateralDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferStatusType是一个转移状态类型
/////////////////////////////////////////////////////////////////////////
///Transfer正在处理
#define TORA_TSTP_TRANST_TranferHandling '0'
///Transfer成功
#define TORA_TSTP_TRANST_TransferSuccess '1'
///Transfer失败
#define TORA_TSTP_TRANST_TransferFail '2'
///Repeal正在处理
#define TORA_TSTP_TRANST_RepealHandling '3'
///Repeal成功
#define TORA_TSTP_TRANST_RepealSuccess '4'
///Repeal失败
#define TORA_TSTP_TRANST_RepealFail '5'
///外部系统已接收
#define TORA_TSTP_TRANST_ExternalAccepted '6'

typedef char TTORATstpTransferStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferPositionTypeType是一个转移持仓类型类型
/////////////////////////////////////////////////////////////////////////
///任意仓
#define TORA_TSTP_TPT_ALL '0'
///昨仓
#define TORA_TSTP_TPT_History '1'
///今买卖仓
#define TORA_TSTP_TPT_TodayBS '2'
///今申赎仓
#define TORA_TSTP_TPT_TodayPR '3'

typedef char TTORATstpTransferPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSystemNameType是一个系统名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSystemNameType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRelativeCondParamType是一个相关条件参数类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpRelativeCondParamType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderStatusType是一个报单状态类型
/////////////////////////////////////////////////////////////////////////
///全部成交
#define TORA_TSTP_OST_AllTraded '0'
///部分成交还在队列中
#define TORA_TSTP_OST_PartTradedQueueing '1'
///部分成交不在队列中
#define TORA_TSTP_OST_PartTradedNotQueueing '2'
///未成交还在队列中
#define TORA_TSTP_OST_NoTradeQueueing '3'
///未成交不在队列中
#define TORA_TSTP_OST_NoTradeNotQueueing '4'
///撤单
#define TORA_TSTP_OST_Canceled '5'
///未知
#define TORA_TSTP_OST_Unknown 'a'
///尚未触发
#define TORA_TSTP_OST_NotTouched 'b'
///已触发
#define TORA_TSTP_OST_Touched 'c'
///预埋
#define TORA_TSTP_OST_Cached 'd'

typedef char TTORATstpOrderStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondOrderStatusType是一个条件单状态类型
/////////////////////////////////////////////////////////////////////////
///初始
#define TORA_TSTP_COST_Initial '#'
///未触发
#define TORA_TSTP_COST_NotTouched '0'
///已触发
#define TORA_TSTP_COST_Touched '1'
///已结束
#define TORA_TSTP_COST_Finished '2'
///已撤销
#define TORA_TSTP_COST_Cancel '3'
///触发失败
#define TORA_TSTP_COST_Failed '4'

typedef char TTORATstpCondOrderStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderSubmitStatusType是一个报单提交状态类型
/////////////////////////////////////////////////////////////////////////
///未提交
#define TORA_TSTP_OSS_UnSubmit '#'
///已经提交
#define TORA_TSTP_OSS_InsertSubmitted '0'
///撤单已经提交
#define TORA_TSTP_OSS_CancelSubmitted '1'
///修改已经提交
#define TORA_TSTP_OSS_ModifySubmitted '2'
///已经接受
#define TORA_TSTP_OSS_Accepted '3'
///报单已经被拒绝
#define TORA_TSTP_OSS_InsertRejected '4'
///撤单已经被拒绝
#define TORA_TSTP_OSS_CancelRejected '5'
///改单已经被拒绝
#define TORA_TSTP_OSS_ModifyRejected '6'

typedef char TTORATstpOrderSubmitStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderTypeType是一个报单类型类型
/////////////////////////////////////////////////////////////////////////
///正常
#define TORA_TSTP_ORDT_Normal '0'
///报价衍生
#define TORA_TSTP_ORDT_DeriveFromQuote '1'
///组合衍生
#define TORA_TSTP_ORDT_DeriveFromCombination '2'
///组合报单
#define TORA_TSTP_ORDT_Combination '3'
///条件单
#define TORA_TSTP_ORDT_ConditionalOrder '4'
///互换单
#define TORA_TSTP_ORDT_Swap '5'

typedef char TTORATstpOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOffsetFlagType是一个开平标志类型
/////////////////////////////////////////////////////////////////////////
///开仓
#define TORA_TSTP_OF_Open '0'
///平仓
#define TORA_TSTP_OF_Close '1'
///强平
#define TORA_TSTP_OF_ForceClose '2'
///平今
#define TORA_TSTP_OF_CloseToday '3'
///平昨
#define TORA_TSTP_OF_CloseYesterday '4'
///强减
#define TORA_TSTP_OF_ForceOff '5'
///本地强平
#define TORA_TSTP_OF_LocalForceClose '6'

typedef char TTORATstpOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpHedgeFlagType是一个投机套保标志类型
/////////////////////////////////////////////////////////////////////////
///投机
#define TORA_TSTP_HF_Speculation '1'
///套利
#define TORA_TSTP_HF_Arbitrage '2'
///套保
#define TORA_TSTP_HF_Hedge '3'
///备兑
#define TORA_TSTP_HF_Covered '4'

typedef char TTORATstpHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpActionFlagType是一个操作标志类型
/////////////////////////////////////////////////////////////////////////
///删除
#define TORA_TSTP_AF_Delete '0'
///修改
#define TORA_TSTP_AF_Modify '3'
///强制删除
#define TORA_TSTP_AF_ForceDelete '4'

typedef char TTORATstpActionFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderActionStatusType是一个报单操作状态类型
/////////////////////////////////////////////////////////////////////////
///已经提交
#define TORA_TSTP_OAS_Submitted 'a'
///已经接受
#define TORA_TSTP_OAS_Accepted 'b'
///已经被拒绝
#define TORA_TSTP_OAS_Rejected 'c'
///预埋未提交
#define TORA_TSTP_OAS_Cached 'e'

typedef char TTORATstpOrderActionStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpClientIDTypeType是一个交易编码类型类型
/////////////////////////////////////////////////////////////////////////
///未知
#define TORA_TSTP_CIDT_Unknown '0'
///投机
#define TORA_TSTP_CIDT_Speculation '1'
///套利
#define TORA_TSTP_CIDT_Arbitrage '2'
///套保
#define TORA_TSTP_CIDT_Hedge '3'
///普通
#define TORA_TSTP_CIDT_Normal 'a'
///信用
#define TORA_TSTP_CIDT_Credit 'b'
///衍生品
#define TORA_TSTP_CIDT_Derivatives 'c'

typedef char TTORATstpClientIDTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBizClassType是一个业务类别类型
/////////////////////////////////////////////////////////////////////////
///买入
#define TORA_TSTP_BC_Buy '0'
///卖出
#define TORA_TSTP_BC_Sell '1'
///ETF申购
#define TORA_TSTP_BC_ETFPur '2'
///ETF赎回
#define TORA_TSTP_BC_ETFRed '3'
///正回购
#define TORA_TSTP_BC_Repurchase '5'
///逆回购
#define TORA_TSTP_BC_ReverseRepur '6'
///配股配债
#define TORA_TSTP_BC_Rationed 'f'
///转托管
#define TORA_TSTP_BC_CustodyTransfer 'q'
///买入开仓
#define TORA_TSTP_BC_BuyOpen 'A'
///买入平仓
#define TORA_TSTP_BC_BuyClose 'B'
///卖出开仓
#define TORA_TSTP_BC_SellOpen 'C'
///卖出平仓
#define TORA_TSTP_BC_SellClose 'D'
///备兑开仓
#define TORA_TSTP_BC_CoveredOpen 'E'
///备兑平仓
#define TORA_TSTP_BC_CoveredClose 'F'
///行权
#define TORA_TSTP_BC_ExecOrder 'G'
///自动行权
#define TORA_TSTP_BC_AutoExecOrder 'H'

typedef char TTORATstpBizClassType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCreditPositionTypeType是一个头寸类型类型
/////////////////////////////////////////////////////////////////////////
///普通
#define TORA_TSTP_CPT_Normal '0'
///专项
#define TORA_TSTP_CPT_Special '1'

typedef char TTORATstpCreditPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFunctionIDType是一个功能代码类型
/////////////////////////////////////////////////////////////////////////
///空
#define TORA_TSTP_FID_NAN ' '
///会话管理：强制登出
#define TORA_TSTP_FID_SessionManager '0'
///用户管理：强制用户退出(禁用)、激活、密码操作
#define TORA_TSTP_FID_UserManager '1'
///报单插入
#define TORA_TSTP_FID_OrderInsert '2'
///报单操作
#define TORA_TSTP_FID_OrderAction '3'
///权限调整
#define TORA_TSTP_FID_AdjustTradingRight '4'
///资金调拨
#define TORA_TSTP_FID_MoveFund '5'
///资金蓝补
#define TORA_TSTP_FID_AddFund '6'
///资金红冲
#define TORA_TSTP_FID_SubFund '7'
///强制冻结资金
#define TORA_TSTP_FID_ForceFreezeFund '8'
///强制解冻资金
#define TORA_TSTP_FID_ForceUnFreezeFund '9'
///仓位蓝补
#define TORA_TSTP_FID_AddPosition 'a'
///仓位红冲
#define TORA_TSTP_FID_SubPosition 'b'
///冲正资金
#define TORA_TSTP_FID_RepealFund 'c'
///冲正仓位
#define TORA_TSTP_FID_RepealPosition 'd'
///向外部系统划拨担保券
#define TORA_TSTP_FID_CollateralInJZ 'e'
///投资者费用调整
#define TORA_TSTP_FID_AdjustTradingFee 'f'
///调整特殊交易权限
#define TORA_TSTP_FID_AdjustSpecPrivilege 'g'
///调整股东关联关系
#define TORA_TSTP_FID_AdjustShareholderAssociation 'h'
///证券信息调整
#define TORA_TSTP_FID_AdjustSecurity 'i'
///持仓调拨
#define TORA_TSTP_FID_MovePosition 'j'
///股东参数调整
#define TORA_TSTP_FID_AdjustShareholderParam 'k'
///条件报单插入
#define TORA_TSTP_FID_CondOrderInsert 'l'
///条件报单操作
#define TORA_TSTP_FID_CondOrderAction 'm'
///查询条件单
#define TORA_TSTP_FID_QryCondOrder 'n'
///条件单参数维护
#define TORA_TSTP_FID_CondParamAdjust 'o'
///用户角色管理
#define TORA_TSTP_FID_UserRoleManage 'p'
///费率模板管理
#define TORA_TSTP_FID_TradingFeeTemplateManage 'q'
///交易权限模板管理
#define TORA_TSTP_FID_TradingRightTemplateManage 'r'
///股东账户证券代码系统权限管理
#define TORA_TSTP_FID_SecurityPriorAuthManage 's'
///持仓交易属性管理
#define TORA_TSTP_FID_PosiParamManage 't'
///报单编号前缀调整
#define TORA_TSTP_FID_OrderLocalSeqPrefixAdjust 'u'
///席位管理
#define TORA_TSTP_FID_TraderManage 'v'
///新股申购参数额度管理
#define TORA_TSTP_FID_IPOManage 'w'
///内部组件运行配置
#define TORA_TSTP_FID_AppRunManage 'x'
///市场状态管理
#define TORA_TSTP_FID_MarketStatusManage 'y'
///平台状态管理
#define TORA_TSTP_FID_PlatformStatusManage 'z'
///查询资金
#define TORA_TSTP_FID_QryTradingAccount 'A'
///查询持仓
#define TORA_TSTP_FID_QryPositon 'B'
///查询股东账户
#define TORA_TSTP_FID_QryShareholderAccount 'C'
///查询委托
#define TORA_TSTP_FID_QryOrder 'D'
///查询成交
#define TORA_TSTP_FID_QryTrade 'E'
///查询资金变动流水
#define TORA_TSTP_FID_QryFundSerial 'F'
///查询持仓变动流水
#define TORA_TSTP_FID_QryPositionSerial 'G'
///Dump资金
#define TORA_TSTP_FID_DumpTradingAccount 'H'
///Dump持仓
#define TORA_TSTP_FID_DumpPositon 'I'
///Dump股东账户
#define TORA_TSTP_FID_DumpShareholderAccount 'J'
///Dump委托
#define TORA_TSTP_FID_DumpOrder 'K'
///Dump成交
#define TORA_TSTP_FID_DumpTrade 'L'
///Dump资金变动流水
#define TORA_TSTP_FID_DumpFundSerial 'M'
///Dump持仓变动流水
#define TORA_TSTP_FID_DumpPositionSerial 'N'
///回传数据
#define TORA_TSTP_FID_UploadTradeData 'O'
///复核资金调整
#define TORA_TSTP_FID_ReviewFundAdjust 'P'
///复核仓位调整
#define TORA_TSTP_FID_ReviewPositionAdjust 'Q'
///记录操作日志
#define TORA_TSTP_FID_RecordOperateLog 'R'
///终端信息管理
#define TORA_TSTP_FID_TerminalInfoManage 'S'
///查询交易权限
#define TORA_TSTP_FID_QryTradingRight 'T'
///指定交易登记&撤销
#define TORA_TSTP_FID_DesignationRegistration 'U'
///深证转托管&撤销
#define TORA_TSTP_FID_CustodyTransfer 'V'
///强制删除报单
#define TORA_TSTP_FID_ForceDelete 'W'
///风控管理
#define TORA_TSTP_FID_RiskMgr 'X'
///复核用户登陆IP/MAC限制调整
#define TORA_TSTP_FID_ReviewUserIPLimitAdjust 'Y'
///用户登录IP/MAC限制调整
#define TORA_TSTP_FID_AdjustUserIPLimit 'Z'
///调整系统参数
#define TORA_TSTP_FID_AdjustSystemParam '@'
///部门信息管理
#define TORA_TSTP_FID_DepartmentInfoManage '#'
///新股配号中签信息管理
#define TORA_TSTP_FID_IPONumberMatchManage '$'
///客户信息管理
#define TORA_TSTP_FID_CustomerInfoManage '*'
///查询用户事件
#define TORA_TSTP_FID_QryTradeEvent '+'
///交易所回报序号维护
#define TORA_TSTP_FID_ExchRtnSeqManage '='
///银证转账
#define TORA_TSTP_FID_TransferFund '-'

typedef char TTORATstpFunctionIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityTypeType是一个证券类别类型
/////////////////////////////////////////////////////////////////////////
///通用(内部使用)
#define TORA_TSTP_STP_COMMON '0'
///上海A股
#define TORA_TSTP_STP_SHAShares 'a'
///上海单市场股票ETF
#define TORA_TSTP_STP_SHSingleMarketStockETF 'b'
///上海单市场实物债券ETF
#define TORA_TSTP_STP_SHSingleMarketBondETF 'c'
///上海黄金ETF
#define TORA_TSTP_STP_SHGoldETF 'd'
///上海货币ETF
#define TORA_TSTP_STP_SHTradableMonetaryFund 'e'
///上海国债、地方债
#define TORA_TSTP_STP_SHBondNation 'f'
///上海企业债
#define TORA_TSTP_STP_SHBondCorporation 'g'
///上海公司债
#define TORA_TSTP_STP_SHBondCompany 'h'
///上海可转债
#define TORA_TSTP_STP_SHBondConversion 'i'
///上海分离债
#define TORA_TSTP_STP_SHBondSeparation 'j'
///上海A股期权
#define TORA_TSTP_STP_SHASharesOption 'k'
///上海ETF期权
#define TORA_TSTP_STP_SHETFOption 'l'
///上海配股
#define TORA_TSTP_STP_SHAllotment 'm'
///上海配债
#define TORA_TSTP_STP_SHDistributeDebt 'n'
///上海标准券
#define TORA_TSTP_STP_SHStandard 'o'
///上海质押式回购
#define TORA_TSTP_STP_SHRepo 'p'
///上海封闭式基金
#define TORA_TSTP_STP_SHCEFund 'q'
///上海开放式基金
#define TORA_TSTP_STP_SHOEFund 'r'
///上海跨市场ETF
#define TORA_TSTP_STP_SHCrossMarketStockETF 's'
///上海跨境ETF
#define TORA_TSTP_STP_SHCrossBorderETF 't'
///上海分级母基金
#define TORA_TSTP_STP_SHMontherStructFund 'u'
///上海分级子基金
#define TORA_TSTP_STP_SHSubStructFund 'v'
///上海实时申赎货币基金
#define TORA_TSTP_STP_SHRealTimeMonetaryFund 'w'
///上海可交换债
#define TORA_TSTP_STP_SHExchangeableBond 'x'
///上海标准LOF基金
#define TORA_TSTP_STP_SHLOF 'A'
///深圳主板A股
#define TORA_TSTP_STP_SZMainAShares 'B'
///深圳中小企业板
#define TORA_TSTP_STP_SZSME 'C'
///深圳国债、地方债
#define TORA_TSTP_STP_SZBondNation 'D'
///深圳企业债
#define TORA_TSTP_STP_SZBondCorporation 'E'
///深圳公司债
#define TORA_TSTP_STP_SZBondCompany 'F'
///深圳可转债
#define TORA_TSTP_STP_SZBondConversion 'G'
///深圳分离债
#define TORA_TSTP_STP_SZBondSeparation 'H'
///深圳A股期权
#define TORA_TSTP_STP_SZASharesOption 'I'
///深圳ETF期权
#define TORA_TSTP_STP_SZETFOption 'J'
///深圳跨境ETF
#define TORA_TSTP_STP_SZCrossBorderETF 'K'
///深圳黄金ETF
#define TORA_TSTP_STP_SZGoldETF 'L'
///深圳现金债券ETF
#define TORA_TSTP_STP_SZCashBondETF 'M'
///深圳单市场股票ETF
#define TORA_TSTP_STP_SZSingleMarketStockETF 'N'
///深圳单市场实物债券ETF
#define TORA_TSTP_STP_SZSingleMarketBondETF 'O'
///深圳货币ETF
#define TORA_TSTP_STP_SZMonetaryFundETF 'P'
///深圳创业板
#define TORA_TSTP_STP_SZGEM 'Q'
///深圳配股
#define TORA_TSTP_STP_SZAllotment 'R'
///深圳配债
#define TORA_TSTP_STP_SZDistributeDebt 'S'
///深圳标准券
#define TORA_TSTP_STP_SZStandard 'T'
///深圳质押式回购
#define TORA_TSTP_STP_SZRepo 'U'
///深圳封闭式基金
#define TORA_TSTP_STP_SZCEFund 'V'
///深圳开放式基金
#define TORA_TSTP_STP_SZOEFund 'W'
///深圳跨境开放式基金
#define TORA_TSTP_STP_SZCrossBorderOEFund 'X'
///深圳跨市场市场股票ETF
#define TORA_TSTP_STP_SZCrossMarketStockETF 'Y'
///深圳标准LOF基金
#define TORA_TSTP_STP_SZLOF 'Z'
///深圳跨境LOF基金
#define TORA_TSTP_STP_SZCrossBorderLOF '1'
///深圳传统分级母基金
#define TORA_TSTP_STP_SZMontherStructFund '2'
///深圳传统分级子基金
#define TORA_TSTP_STP_SZSubStructFund '3'
///深圳跨境分级母基金
#define TORA_TSTP_STP_SZMontherCrossBorderStructFund '4'
///深圳跨境分级子基金
#define TORA_TSTP_STP_SZSubCrossBorderStructFund '5'
///深圳可交换债
#define TORA_TSTP_STP_SZExchangeableBond '6'
///深圳创业板可转债
#define TORA_TSTP_STP_SZGEMConversionBond '7'

typedef char TTORATstpSecurityTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpEndFlagType是一个结束标志类型
/////////////////////////////////////////////////////////////////////////
///待续
#define TORA_TSTP_EF_ToBeContinued '1'
///批结束
#define TORA_TSTP_EF_BatchEnd '2'
///全部完成
#define TORA_TSTP_EF_Completed '3'
///无数据
#define TORA_TSTP_EF_NOP '4'

typedef char TTORATstpEndFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMarketIDType是一个市场代码类型
/////////////////////////////////////////////////////////////////////////
///通用(内部使用)
#define TORA_TSTP_MKD_COMMON '0'
///上海A股
#define TORA_TSTP_MKD_SHA '1'
///深圳A股
#define TORA_TSTP_MKD_SZA '2'
///上海B股
#define TORA_TSTP_MKD_SHB '3'
///深圳B股
#define TORA_TSTP_MKD_SZB '4'
///深圳三版A股
#define TORA_TSTP_MKD_SZThreeA '5'
///深圳三版B股
#define TORA_TSTP_MKD_SZThreeB '6'
///境外市场
#define TORA_TSTP_MKD_Foreign '7'

typedef char TTORATstpMarketIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLogInAccountType是一个登录账户类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpLogInAccountType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLogInAccountTypeType是一个登录账户类型类型
/////////////////////////////////////////////////////////////////////////
///用户代码
#define TORA_TSTP_LACT_UserID '0'
///资金账号
#define TORA_TSTP_LACT_AccountID '1'
///上海A股
#define TORA_TSTP_LACT_SHAStock '2'
///深圳A股
#define TORA_TSTP_LACT_SZAStock '3'
///上海B股
#define TORA_TSTP_LACT_SHBStock '4'
///深圳B股
#define TORA_TSTP_LACT_SZBStock '5'
///三板A
#define TORA_TSTP_LACT_ThreeNewBoardA '6'
///三板B
#define TORA_TSTP_LACT_ThreeNewBoardB '7'
///港股
#define TORA_TSTP_LACT_HKStock '8'

typedef char TTORATstpLogInAccountTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMarketStatusType是一个市场状态类型
/////////////////////////////////////////////////////////////////////////
///未知
#define TORA_TSTP_MST_UnKnown '#'
///开盘前
#define TORA_TSTP_MST_BeforeTrading '0'
///连续交易
#define TORA_TSTP_MST_Continous '1'
///收盘
#define TORA_TSTP_MST_Closed '2'
///开盘集合竞价
#define TORA_TSTP_MST_OpenCallAuction '3'

typedef char TTORATstpMarketStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBigsInfoType是一个长字符串附加信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBigsInfoType[33];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpShortsInfoType是一个短字符串附加信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpShortsInfoType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIntInfoType是一个整形附加信息类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpIntInfoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFloatInfoType是一个浮点型附加信息类型
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpFloatInfoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpApiGroupIDType是一个Api工作组号类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpApiGroupIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpApiRunModeType是一个Api运行模式类型
/////////////////////////////////////////////////////////////////////////
///单一
#define TORA_TSTP_ARM_Single '0'
///集群
#define TORA_TSTP_ARM_Group '1'

typedef char TTORATstpApiRunModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDesignationTypeType是一个指定交易操作类型类型
/////////////////////////////////////////////////////////////////////////
///指定交易登记
#define TORA_TSTP_DT_Register '0'
///指定交易撤销登记
#define TORA_TSTP_DT_Cancel '1'

typedef char TTORATstpDesignationTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCustodyTransferTypeType是一个深证转托管类型类型
/////////////////////////////////////////////////////////////////////////
///深证转托管注册
#define TORA_TSTP_CT_Register '0'
///深证转托管撤单
#define TORA_TSTP_CT_Cancel '1'

typedef char TTORATstpCustodyTransferTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProperCtrlBusinessTypeType是一个适当性控制业务类别类型
/////////////////////////////////////////////////////////////////////////
///空值
#define TORA_TSTP_PCBT_None ' '
///其它
#define TORA_TSTP_PCBT_Other '0'
///上海退市整理
#define TORA_TSTP_PCBT_SHDelisting '1'
///风险警示
#define TORA_TSTP_PCBT_ST '2'
///创业板
#define TORA_TSTP_PCBT_GEM '3'
///分级基金
#define TORA_TSTP_PCBT_StructFund '4'
///债券
#define TORA_TSTP_PCBT_BondQualified '5'
///暂停上市债
#define TORA_TSTP_PCBT_SuspendBond '6'
///正回购
#define TORA_TSTP_PCBT_Repurchase '7'
///逆回购
#define TORA_TSTP_PCBT_ReverseRepur '8'
///深圳退市整理
#define TORA_TSTP_PCBT_SZDelisting '9'
///常规股票
#define TORA_TSTP_PCBT_Stock 'a'
///常规股票信用
#define TORA_TSTP_PCBT_CreditStock 'b'

typedef char TTORATstpProperCtrlBusinessTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProperCtrlPassFlagType是一个适当性控制通过标示类型
/////////////////////////////////////////////////////////////////////////
///空值
#define TORA_TSTP_PCPF_None ' '
///无条件通过
#define TORA_TSTP_PCPF_AnywayPass '0'
///匹配通过
#define TORA_TSTP_PCPF_MatchPass '1'
///有条件通过
#define TORA_TSTP_PCPF_SelectPass '2'
///专投豁免过
#define TORA_TSTP_PCPF_ProfInvestorPass '3'

typedef char TTORATstpProperCtrlPassFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCRiskLevelType是一个客户风险等级类型
/////////////////////////////////////////////////////////////////////////
///最低级别风险
#define TORA_TSTP_RLV_Lowest '0'
///保守型
#define TORA_TSTP_RLV_Conservative '1'
///谨慎型
#define TORA_TSTP_RLV_Cautious '2'
///稳健型
#define TORA_TSTP_RLV_Steady '3'
///积极型
#define TORA_TSTP_RLV_Positive '4'
///激进型
#define TORA_TSTP_RLV_Aggressive '5'

typedef char TTORATstpCRiskLevelType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProfInvestorTypeType是一个专业投资者类别类型
/////////////////////////////////////////////////////////////////////////
///非专业投资者
#define TORA_TSTP_PIT_NotProf '0'
///当然机构专业投资者
#define TORA_TSTP_PIT_OCInstiPro '1'
///法人或机构专业投资者
#define TORA_TSTP_PIT_InstiPro '2'
///自然人专业投资者
#define TORA_TSTP_PIT_PersonPro '3'
///认定法人或机构专业投资者
#define TORA_TSTP_PIT_ConfirmInstiPro '4'
///认定自然人专业投资者
#define TORA_TSTP_PIT_ConfirmPersonPro '5'

typedef char TTORATstpProfInvestorTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLOrderTypeType是一个订单类别类型
/////////////////////////////////////////////////////////////////////////
///市价
#define TORA_TSTP_LOT_Market '1'
///限价
#define TORA_TSTP_LOT_Limit '2'
///本方最优
#define TORA_TSTP_LOT_HomeBest '3'

typedef char TTORATstpLOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLSideType是一个委托方向类型
/////////////////////////////////////////////////////////////////////////
///买
#define TORA_TSTP_LSD_Buy '1'
///卖
#define TORA_TSTP_LSD_Sell '2'
///借入
#define TORA_TSTP_LSD_Borrow '3'
///借出
#define TORA_TSTP_LSD_Lend '4'

typedef char TTORATstpLSideType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExecTypeType是一个成交类别类型
/////////////////////////////////////////////////////////////////////////
///成交
#define TORA_TSTP_ECT_Fill '1'
///撤销
#define TORA_TSTP_ECT_Cancel '2'

typedef char TTORATstpExecTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondCheckType是一个委托条件检查类型
/////////////////////////////////////////////////////////////////////////
///不做任何检查
#define TORA_TSTP_CCT_None '0'
///自成交检查
#define TORA_TSTP_CCT_SelfDeal '1'

typedef char TTORATstpCondCheckType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpHDSerialType是一个硬盘序列号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpHDSerialType[33];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMDSubModeType是一个行情订阅模式类型
/////////////////////////////////////////////////////////////////////////
///TCP连接模式
#define TORA_TSTP_MST_TCP '0'
///UDP单播模式
#define TORA_TSTP_MST_UDP '1'
///UDP组播模式
#define TORA_TSTP_MST_MCAST '2'

typedef char TTORATstpMDSubModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMDSecurityStatType是一个行情证券状态类型
/////////////////////////////////////////////////////////////////////////
///开盘前
#define TORA_TSTP_MSST_PreOpen '0'
///集合竞价
#define TORA_TSTP_MSST_CallAuction '1'
///连续交易
#define TORA_TSTP_MSST_Continous '2'
///休市
#define TORA_TSTP_MSST_Pause '3'
///停牌
#define TORA_TSTP_MSST_Suspend '4'
///长期停牌
#define TORA_TSTP_MSST_LongSuspend '5'
///波动性中断
#define TORA_TSTP_MSST_UndulationInt '6'
///熔断可恢复
#define TORA_TSTP_MSST_CircuitBreak '7'
///熔断不可恢复
#define TORA_TSTP_MSST_CircuitBreakU '8'
///闭市
#define TORA_TSTP_MSST_Close '9'
///其它
#define TORA_TSTP_MSST_Other 'a'
///收盘集合竞价
#define TORA_TSTP_MSST_CloseCallAuction 'b'

typedef char TTORATstpMDSecurityStatType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCommitStatusType是一个文件委托提交状态类型
/////////////////////////////////////////////////////////////////////////
///初始
#define TORA_TSTP_FOCS_Init '0'
///已复核
#define TORA_TSTP_FOCS_Reviewed '1'
///处理失败
#define TORA_TSTP_FOCS_Failed '2'

typedef char TTORATstpCommitStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParamTypeType是一个股东参数类型类型
/////////////////////////////////////////////////////////////////////////
///最大买量限制
#define TORA_TSTP_SPT_MaxBuyLimit '0'
///最大卖量限制
#define TORA_TSTP_SPT_MaxSellLimit '1'
///买入大额申报限制比例
#define TORA_TSTP_SPT_LargeBuyLimitRatio '2'
///卖出大额申报限制比例
#define TORA_TSTP_SPT_LargeSelLimitRatio '3'
///风险警示买入上限
#define TORA_TSTP_SPT_RiskWarnBoardLimitVol '4'
///连续申报时间间隔
#define TORA_TSTP_SPT_SeriesDecInterval '5'
///连续申报单位时间委托笔数
#define TORA_TSTP_SPT_SeriesLimitPerUnit '6'
///影响收盘价波动比例
#define TORA_TSTP_SPT_ClosePriceScopeRatio '7'
///炒新控制最大上市时间
#define TORA_TSTP_SPT_OpenDateLimit '8'
///涨跌停板虚假申报占未成交比例
#define TORA_TSTP_SPT_LimitBoardShamRatio '9'
///撤单限制比例
#define TORA_TSTP_SPT_CancelOrderRatio 'a'

typedef char TTORATstpParamTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpContentType是一个消息正文类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpContentType[501];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpStatusMsgType是一个状态信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpStatusMsgType[93];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIPONumberIDType是一个新股申购配股号类型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIPONumberIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPageLocateType是一个页定位符类型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpPageLocateType;
#endif