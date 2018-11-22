// SSCARDCtrl.cpp : CSSCARDCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "SSCARD.h"
#include "SSCARDCtrl.h"
#include "SSCARDPropPage.h"
#include "afxdialogex.h"

#include <vector>
#include <string>
#include "log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSSCARDCtrl, COleControl)

#include ".\\lib\\GWI_CardRead_Adapt.h"
#pragma  comment(lib, ".\\lib\\GWI_CardRead_Adapt.lib")

#include ".\\lib\\GWI_SAM_Adapt.h"
#pragma  comment(lib, ".\\lib\\GWI_SAM_Adapt.lib")

#include ".\\lib\\GWI_SSSE_SC.h"
#pragma  comment(lib, ".\\lib\\GWI_SSSE_SC.lib")

bool bIsRunCardReadOpen = false;
char strL[LEN_1024];
char log_msg[LEN_1024];
_ReturnMap returnMap[] = {
	{-1,		"卡类型不对",0xFF,0x00},
	{-2,		"无卡",0x00,0x00},
	{-3,		"有卡未上电",0xFF,0x20},
	{-4,		"卡无应答",0xFF,0x21},
	{-5,		"加载动态库错",0x00,0x00},
	{-11,		"读卡器连接错",0xFF,0x11},
	{-12,		"未建立连接",0xFF,0x10},
	{-13,		"（动态库）不支持该命令",0x00,0x00},
	{-14,		"（发给动态库的）命令参数错",0xFF,0x50},
	{-15,		"信息校验和出错",0x00,0x00},
	{-20,		"卡识别码格式错",0x00,0x00},
	{-21,		"内部认证失败（用户卡不合法)",0xFF,0x40},
	{-22,		"传入数据与卡内不符",0x00,0x00},
	{-23,		"传入数据不合法",0xFF,0x01},
	{-24,		"PSAM卡密钥级别不够",0x00,0x00},
	{-25,		"内部认证与加密机不一致失败",0xFF,0x41},
	{-31,		"用户取消密码输入",0x00,0x00},
	{-32,		"密码输入操作超时",0x00,0x00},
	{-33,		"输入密码长度错",0x00,0x00},
	{-34,		"两次输入密码不一致",0x00,0x00},
	{-35,		"初始密码不能交易",0x00,0x00},
	{-36,		"不能改为初始密码",0x00,0x00},
	{-41,		"运算数据含非法字符",0x00,0x00},
	{-42,		"运算数据长度错",0x00,0x00},
	{-51,		"PIN校验失败，剩余次数N次（根据卡返回信息）",0x63,0xC0},
	{-52,		"PIN锁定",0x00,0x00},
	{-2201,		"无PSAM卡",0xFF,0x30},
	{-2202,		"PSAM卡算法不支持（即PSAM卡内没有SSF33算法或SM4算法）",0x00,0x00},
	{-2203,		"PSAM卡内没有RKSSSE密钥（3.0卡读个人基本信息需要RKSSSE密钥外部认证）",0x00,0x00},
	{-2204,		"不需要加密机认证",0x00,0x00},
	{-25536,	"外部认证失败，剩余可尝试次数2、1、0次",0x00,0x00},
	{-25537,	" 外部认证失败，剩余可尝试次数2、1、0次",0x00,0x00},
	{25538,		"外部认证失败，剩余可尝试次数2、1、0次",0x00,0x00},
	{-26368,	"Lc/Le不正确",0x6C,0x00},
	{-26369,	"P1、 P2 与 Lc 不一致",0x67,0x00},
	{-26370,	"参数 P1、 P2 不正确",0x6A,0x86},
	{-26371,	"CLA 错",0x6E,0x00},
	{-26881,	"命令不接受（无效状态）",0x69,0x86},
	{-27009,	"命令与文件结构不相符、当前文件非所需文件",0x69,0x81},
	{-27010,	"不满足安全条件",0x69,0x82},
	{-27011,	"密钥锁定（算法锁定）鉴别方法锁定",0x69,0x83},
	{-27012,	"引用数据无效、随机数无效",0x69,0x84},
	{-27013,	"不满足使用条件、应用被锁定、应用未选择、余额上溢",0x93,0x03},
	{-27016,	"安全报文数据项不正确、MAC不正确",0x69,0x88},
	{-27264,	"数据域参数不正确",0x6A,0x80},
	{-27265,	"不支持该功能、卡中无MF、卡被锁定、应用锁定",0x6A,0x81},
	{-27266,	"未找到文件、文件标识相重、SFI不正确",0x6A,0x82},
	{-27267,	"未找到记录",0x6A,0x83},
	{-27272,	"未找到引用数据、未找到密钥",0x6A,0x88},
	{-37634,	"MAC无效",0x00,0x00},
	{-37635,	"应用已被永久锁定、卡片锁定",0x93,0x03},
	{-37891,	"PSAM卡不支持消费交易",0x00,0x00},
	{-37894,	"所需MAC（或/和TAC）不可用",0x00,0x00},
	{-999,		"未知错误",0x00,0x00}
};

static int iReturnMap_Len = sizeof(returnMap)/sizeof(returnMap[0]);

long getRetMsgBySw1Sw2(char sw1,char sw2,char* msg)
{
	int iret = -999;
	memset(msg,0x00,sizeof(msg));
	if (0x6E ==  sw1 || 0x6e == sw1)
	{
		strcpy(msg,"CLA错误");
		iret = -26371;
		return iret;
	}
	if (0x63 ==  sw1)
	{
		char cTemp[MAX_PATH] = {};
		sprintf(cTemp,"PIN校验失败，剩余次数%X次（根据卡返回信息）",sw2&0x0F);
		strcpy(msg,cTemp);
		iret = -51;
		return iret;
	}
	for (int i=0 ; i<iReturnMap_Len; i++)
	{
		if (sw1 == returnMap[i].sw1 && sw2 == returnMap[i].sw2)
		{
			strcpy(msg,returnMap[i].msg);
			iret = returnMap[i].ret;
			break;
		}
	}
	return iret;
}

_KLV getKLV(char* data)
{
	_KLV temp;

	if (strlen(data) < 4)
	{
		strcpy(temp.k,"");
		temp.l=0;
		strcpy(temp.v,"");
	}

	memcpy(temp.k,data,2);
	char csL[3] = {};
	memcpy(csL,data+2,2);
	temp.l = ((csL[0]-0x30)*16+(csL[1]-0x30))*2;//hex长度转换为DSP长度
	if (temp.l>=strlen(data)-4) //防止内存越界
	{
		temp.l = strlen(data)-4;
	}
	memcpy(temp.v,data+4,temp.l);
	return temp;
}

//-------------获取按ch分割的子字符串--------------------------
std::vector<std::string> split(char* pStr, char ch)
{
	std::vector<std::string> vec;
	if (nullptr == pStr)
		return vec;

	std::string strStr(pStr);
	int _off=0;
	std::string::size_type sizeType;
	while(true)
	{
		if (_off>=strStr.length())
			break;

		sizeType=strStr.find_first_of(ch,_off);
		if (sizeType<=0)
		{
			_off=sizeType+1;
			continue;
		}
		if (sizeType==std::string::npos)
		{
			vec.push_back(strStr.substr(_off,strStr.length() - _off));
			break;
		}
		vec.push_back(strStr.substr(_off,sizeType - _off));
		_off=sizeType+1;
	}
	return vec;
}
// 消息映射

BEGIN_MESSAGE_MAP(CSSCARDCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CSSCARDCtrl, COleControl)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReadCardBas", dispidiReadCardBas, iReadCardBas, VT_I4, VTS_I4)
	DISP_PROPERTY_NOTIFY_ID(CSSCARDCtrl, "pOutInfo", dispidpOutInfo, m_pOutInfo, OnpOutInfoChanged, VT_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReadCardBas_HSM_Step1", dispidiReadCardBas_HSM_Step1, iReadCardBas_HSM_Step1, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReadCardBas_HSM_Step2", dispidiReadCardBas_HSM_Step2, iReadCardBas_HSM_Step2, VT_I4, VTS_BSTR)
	
	DISP_FUNCTION_ID(CSSCARDCtrl, "ocxReadTrack", dispidocxReadTrack, ocxReadTrack, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CSSCARDCtrl, "ocxEjectCard", dispidocxEjectCard, ocxEjectCard, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CSSCARDCtrl, "ocxCloseDevice", dispidocxCloseDevice, ocxCloseDevice, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CSSCARDCtrl, "ocxOpenDevice", dispidocxOpenDevice, ocxOpenDevice, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iVerifyPIN", dispidiVerifyPIN, iVerifyPIN, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iChangePIN", dispidiChangePIN, iChangePIN, VT_I4, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReloadPIN", dispidiReloadPIN, iReloadPIN, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReloadPIN_HSM_Step1", dispidiReloadPIN_HSM_Step1, iReloadPIN_HSM_Step1, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReloadPIN_HSM_Step2", dispidiReloadPIN_HSM_Step2, iReloadPIN_HSM_Step2, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CSSCARDCtrl, "iReloadPIN_HSM_Step3", dispidiReloadPIN_HSM_Step3, iReloadPIN_HSM_Step3, VT_I4, VTS_BSTR)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CSSCARDCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CSSCARDCtrl, 1)
	PROPPAGEID(CSSCARDPropPage::guid)
END_PROPPAGEIDS(CSSCARDCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSSCARDCtrl, "SSCARD.SSCARDCtrl.1",
	0xb2167f16, 0xe8b0, 0x4d84, 0x80, 0x2e, 0x3c, 0x7f, 0x34, 0xaa, 0x28, 0x73)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CSSCARDCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DSSCARD = { 0x7E4FB4C8, 0xB4B, 0x4D7F, { 0xA4, 0x17, 0x7B, 0x7D, 0xEB, 0xDC, 0xF3, 0x91 } };
const IID IID_DSSCARDEvents = { 0x9F6CBFA1, 0x1839, 0x4733, { 0x89, 0x0, 0x11, 0x64, 0xA, 0xCC, 0x21, 0xDD } };


// 控件类型信息

static const DWORD _dwSSCARDOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSSCARDCtrl, IDS_SSCARD, _dwSSCARDOleMisc)



// CSSCARDCtrl::CSSCARDCtrlFactory::UpdateRegistry -
// 添加或移除 CSSCARDCtrl 的系统注册表项

BOOL CSSCARDCtrl::CSSCARDCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SSCARD,
			IDB_SSCARD,
			afxRegApartmentThreading,
			_dwSSCARDOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CSSCARDCtrl::CSSCARDCtrl - 构造函数

CSSCARDCtrl::CSSCARDCtrl()
{
	
	InitializeIIDs(&IID_DSSCARD, &IID_DSSCARDEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CSSCARDCtrl::~CSSCARDCtrl - 析构函数

CSSCARDCtrl::~CSSCARDCtrl()
{
	// TODO: 在此清理控件的实例数据。
	//Close_EX();
}


// CSSCARDCtrl::OnDraw - 绘图函数

void CSSCARDCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CSSCARDCtrl::DoPropExchange - 持久性支持

void CSSCARDCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CSSCARDCtrl::OnResetState - 将控件重置为默认状态

void CSSCARDCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}

// CSSCARDCtrl 消息处理程序

LONG CSSCARDCtrl::iReadCardBas(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	sprintf(log_msg,"%d",iType);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	// TODO: 在此添加调度处理程序代码
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	if (!bIsRunCardReadOpen)
	{
		if(0!=Init())
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x10,msg);
			m_pOutInfo = msg;
			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x10,msg);
			LOG_DEBUG(log_msg);

			sprintf(log_msg,"iret[%d]",iret);
			LOG_INFO(log_msg);
			return iret;//参数错误
		}

		iret = Open_EX();
		sprintf(log_msg,"Open_EX -> iret[%d]",iret);
		LOG_DEBUG(log_msg);

		if (1!=iret && 2!=iret && 3!=iret)
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
			m_pOutInfo = msg;

			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
			LOG_DEBUG(log_msg);

			sprintf(log_msg,"iret[%d]",iret);
			LOG_INFO(log_msg);
			return iret;//参数错误
		}
		bIsRunCardReadOpen = true;
	}
	
	char pchData[MAX_PATH] = {};
	int iDataLen;
	char pchErrCode[MAX_PATH] = {};
	char pchError[MAX_PATH] = {};
	iret = psamPowerOn(2,pchData,&iDataLen,pchErrCode,pchError);
	if (0!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x30,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x30,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}
	//下面流程在迭代一 实现加密机中不做；迭代一只触发返回-2201就可以执行后续加密机操作流程
	/*
	（4）	选择社保卡社会保障系统环境，同时根据卡片返回的应答信息确定算法环境，根据算法环境标识选择PSAM卡相应算法密钥文件，具体方法详见10.1；
	（5）	若PSAM卡算法不支持（即PSAM卡内没有SSF33算法或SM4算法），返回错误代码“-2202”；若为3.0卡（要求详见10.2），但PSAM卡内没有RKSSSE密钥，返回错误代码“-2203”（具体参见附录A）；
	（6）	执行内部认证指令，验证卡片有效性；若为3.0卡，再执行RKSSSE密钥外部认证；其中密钥分散因子提取具体方法详见10.3；
	（7）	依次读取各项数据；读取“卡号”时只读前9位（详见10.4）；2.0卡或3.0卡需读出“姓名扩展”，与“姓名”拼接后返回完整姓名（详见10.2）；
	（8）	读取PSAM卡终端机编号和终端设备号；
	（9）	调用SSSE32.DLL动态库中的“关闭设备”函数关闭设备，释放端口；
	（10）	以上操作过程中出现异常时，均应先调用SSSE32.DLL动态库中的“关闭设备”函数关闭设备，释放端口，然后退出函数，返回错误代码和错误信息描述。
	*/
	sprintf(log_msg,"iret[%d]",0);
	LOG_INFO(log_msg);
	return 0;
}



void CSSCARDCtrl::OnpOutInfoChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
}

char csAtr[MAX_PATH] = {};
char EF05_01[MAX_PATH] = {};
char EF05_01_CityCode[7] = {};
char EF05_03[MAX_PATH] = {};
unsigned char EF05_03_Version[2] = {};
char EF05_07[MAX_PATH] = {};

char interAuth[17] = {};
LONG CSSCARDCtrl::iReadCardBas_HSM_Step1(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	sprintf(log_msg,"Enter.%d",iType);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	iret = ocxOpenDevice();//1为IDC 2：IC2 3：IDC与IC2打开成功
	if (1!=iret && 2!=iret && 3!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
		LOG_DEBUG(log_msg);
	}
		
	memset(csAtr,0x00,sizeof(csAtr));
	//银海 杨（传杰）老师需求改成6秒
	iret = PowerOn_EX(iType,6,csAtr);
	if (0!=iret)
	{
		ResetDevice();
		iret = getRetMsgBySw1Sw2(0xFF,0x20,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x20,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);

	//得到算法标识
	//9F0C03860103
	std::string rapdu(outData);

	char algorithm[3] = {};
	std::string::size_type pos = rapdu.find("9F0C038601");
	if (std::string::npos == pos)
	{
		strcpy(algorithm,"01");
	}
	else
	{
		strncpy(algorithm,(char*)rapdu.substr(pos+10,2).c_str(),2);
	}
	sprintf(log_msg,"algorithm[%s]",algorithm);
	LOG_DEBUG(log_msg);
	//EF05
	MEMSET_APDU
	unsigned char FILE_SSSE_YH[] = "\xEF\x05";
	iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	//EF05 01
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x01,0x00,0x12,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	_KLV klv = getKLV(outData);
	
	memset(EF05_01,0x00,sizeof(EF05_01));
	strcpy(EF05_01,klv.v);
	sprintf(log_msg,"EF05_01[%s]",EF05_01);
	LOG_DEBUG(log_msg);

	memset(EF05_01_CityCode,0x00,sizeof(EF05_01_CityCode));
	strncpy(EF05_01_CityCode,klv.v,6);
	sprintf(log_msg,"EF05_01_CityCode[%s]",EF05_01_CityCode);
	LOG_DEBUG(log_msg);
	//EF05 03
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x03,0x00,0x06,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	memset(EF05_03,0x00,sizeof(EF05_03));
	strcpy(EF05_03,klv.v);
	sprintf(log_msg,"EF05_03[%s]",EF05_03);
	LOG_DEBUG(log_msg);

	memset(EF05_03_Version,0x00,sizeof(EF05_03_Version));
	DSP_2_HEX((unsigned char*)EF05_03,EF05_03_Version,1);
	sprintf(log_msg,"EF05_03_Version[%s]",EF05_03_Version);
	LOG_DEBUG(log_msg);

	//EF05 07
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x07,0x00,0x0B,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	memset(EF05_07,0x00,sizeof(EF05_07));
	strcpy(EF05_07,klv.v);
	sprintf(log_msg,"EF05_07[%s]",EF05_07);
	LOG_DEBUG(log_msg);

	//SSSE
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"SELECT_SSSE_YH--outData[%s]",outData);
	LOG_DEBUG(log_msg);

	char interAuthSource[17] = {};
	char interAuthProcess[17] = {};
	char externalAuthSource[17] = {};
	char externalAuthProcess[17] = {};

	//内认证 原始数据
	if ('3' == (char)EF05_03_Version[0])
	{
		MEMSET_APDU
		iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);

		strncpy(interAuthSource,outData,16);
		sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--interAuthSource[%s]",interAuthSource);
		LOG_DEBUG(log_msg);

		//内认证 过程因子
		MEMSET_APDU
		iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);

		strncpy(interAuthProcess,outData,16);
		sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--interAuthProcess[%s]",interAuthProcess);
		LOG_DEBUG(log_msg);
		//内认证
		char interAuthData[36] = {};
		sprintf(interAuthData,"%s%s",interAuthProcess,interAuthSource);
		iret = INTERNAL_AUTHENTICATION_SSSE_YH(0x10,interAuthData,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);
		memset(interAuth,0x00,sizeof(interAuth));
		strncpy(interAuth,outData,16);
		sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--interAuth[%s]",interAuth);
		LOG_DEBUG(log_msg);

		//外部认证 原始数据
		MEMSET_APDU
		iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);
		strncpy(externalAuthSource,outData,16);
		sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--externalAuthSource[%s]",externalAuthSource);
		LOG_DEBUG(log_msg);

		//外部认证 过程因子
		MEMSET_APDU
		iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);
		strncpy(externalAuthProcess,outData,16);
		sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--externalAuthProcess[%s]",externalAuthProcess);
		LOG_DEBUG(log_msg);
	}
	
	//char terminalSN[MAX_PATH] = "DCKJ0100201706014606000000000000";//终端号
	char terminalSN[MAX_PATH] = {};
	iret = GetSN(terminalSN);
	sprintf(log_msg,"iret[%d];terminalSN[%s]",iret,terminalSN);
	LOG_DEBUG(log_msg);

	char pOut[MAX_PATH] = {};
	sprintf(pOut,"%s|%s|%s|%s|%s|%s|%s|%s|%s|",EF05_01_CityCode,csAtr,algorithm,EF05_01,interAuthProcess,interAuthSource,externalAuthProcess,externalAuthSource,terminalSN);
	sprintf(log_msg,"pOut[%s]",pOut);
	LOG_DEBUG(log_msg);
	m_pOutInfo = pOut;
	sprintf(log_msg,"iret[%d]",0);
	LOG_INFO(log_msg);
	return 0;
}

LONG CSSCARDCtrl::iReadCardBas_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	sprintf(log_msg,"Enter.pKey[%s]",pKey);
	LOG_INFO(log_msg);
	int iret;
	char msg[LEN_1024];
	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	if ('3'  == (char)EF05_03_Version[0])
	{
		// TODO: 在此添加调度处理程序代码
		if (strlen(pKey) < 64)
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x01,msg);
			m_pOutInfo = msg;
			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x01,msg);
			LOG_DEBUG(log_msg);
			return iret;//参数错误
		}

		std::string strInparam(pKey);
		if(0 != strncmp(interAuth,strInparam.substr(0,16).c_str(),16))
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x41,msg);
			m_pOutInfo = msg;
			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x41,msg);
			LOG_DEBUG(log_msg);
			return iret;//参数错误
		}

		char externAuthData[33] = {};
		strncpy(externAuthData,strInparam.substr(33,32).c_str(),32);
		iret = EXTERNAL_AUTHENTICATION_SSSE_YH(0x0A,0x10,externAuthData,outData,outDataLen,errorCode,errorMsg);
		VALIAD_RET(iret);
		VALIAD_SW1_SW2(errorCode);
	}

	//EF05
	MEMSET_APDU
	unsigned char FILE_SSSE_YH[] = "\xEF\x05";
	iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"SELECT_FILE_SSSE_YH - EF05[%s]",outData);
	LOG_DEBUG(log_msg);
	//EF05 - 05
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x05,0x00,0x06,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	_KLV klv = getKLV(outData);
	char EF05_05[9] = {};
	memset(EF05_05,0x00,sizeof(EF05_05));
	strncpy(EF05_05,klv.v,8);
	sprintf(log_msg,"EF05_05[%s]",EF05_05);
	LOG_DEBUG(log_msg);
	//EF05 - 06
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x06,0x00,0x06,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	char EF05_06[9] = {};
	memset(EF05_06,0x00,sizeof(EF05_06));
	strncpy(EF05_06,klv.v,8);
	sprintf(log_msg,"EF05_06[%s]",EF05_06);
	LOG_DEBUG(log_msg);
	//EF06
	MEMSET_APDU
	unsigned char FILE_SSSE_YH_EF06[] = "\xEF\x06";
	iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH_EF06,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"SELECT_FILE_SSSE_YH - EF06[%s]",outData);
	LOG_DEBUG(log_msg);
	//EF06-08
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x08,0x00,0x14,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	char EF06_08[37] = {};
	memset(EF06_08,0x00,sizeof(0));
	strncpy(EF06_08,klv.v,36);
	sprintf(log_msg,"EF06_08[%s]",EF06_08);
	LOG_DEBUG(log_msg);
	//EF06-09
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x09,0x00,0x20,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	char EF06_09[61] = {};
	memset(EF06_09,0x00,sizeof(0));
	strncpy(EF06_09,klv.v,60);
	sprintf(log_msg,"EF06_09[%s]",EF06_09);
	LOG_DEBUG(log_msg);
	//EF06-4E
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x4E,0x00,0x16,outData,outDataLen,errorCode,errorMsg);
	//VALIAD_RET(iret);//二代社保卡可能没有记录 就屏蔽检查
	//VALIAD_SW1_SW2(errorCode);
	char EF06_4E[41] = {};
	if (outData!=nullptr && strlen(outData) > 0)
	{
		klv = getKLV(outData);
		memset(EF06_4E,0x00,sizeof(0));
		strncpy(EF06_4E,klv.v,40);
		sprintf(log_msg,"EF06_4E[%s]",EF06_4E);
		LOG_DEBUG(log_msg);
	}
	

	char pout[LEN_1024] = {};
	char ucEF06_08[19] = {};
	DSP_2_HEX((unsigned char*)EF06_08,(unsigned char*)ucEF06_08,18);
	sprintf(log_msg,"ucEF06_08[%s]",ucEF06_08);
	LOG_DEBUG(log_msg);

	char ucEF05_07[10] = {};
	DSP_2_HEX((unsigned char*)EF05_07,(unsigned char*)ucEF05_07,9);
	sprintf(log_msg,"ucEF05_07[%s]",ucEF05_07);
	LOG_DEBUG(log_msg);

	char ucEF06_09[31] = {};
	DSP_2_HEX((unsigned char*)EF06_09,(unsigned char*)ucEF06_09,30);
	sprintf(log_msg,"ucEF06_09[%s]",ucEF06_09);
	LOG_DEBUG(log_msg);

	char ucEF06_4E[21] = {0};
	DSP_2_HEX((unsigned char*)EF06_4E,(unsigned char*)ucEF06_4E,20);
	sprintf(log_msg,"ucEF06_4E[%s]",ucEF06_4E);
	LOG_DEBUG(log_msg);

	char ucName[MAX_PATH] = {};
	sprintf(ucName,"%s%s",ucEF06_09,ucEF06_4E);
	sprintf(log_msg,"ucName[%s]",ucName);
	LOG_DEBUG(log_msg);

	char ucEF05_03[5] = {};
	DSP_2_HEX((unsigned char*)EF05_03,(unsigned char*)ucEF05_03,4);
	sprintf(log_msg,"ucEF05_03[%s]",ucEF05_03);
	LOG_DEBUG(log_msg);

	char terminalMark[13] = "000000000000";
	sprintf(log_msg,"terminalMark[%s]",terminalMark);
	LOG_DEBUG(log_msg);

	char terminalDeviceNo[MAX_PATH] = {};
	sprintf(log_msg,"terminalDeviceNo[%s]",terminalDeviceNo);
	LOG_DEBUG(log_msg);

	sprintf(pout,"%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|",EF05_01_CityCode,ucEF06_08,ucEF05_07,EF05_01,ucName,csAtr,ucEF05_03,EF05_05,EF05_06,terminalMark,terminalDeviceNo);
	sprintf(log_msg,"pout[%s]",pout);
	LOG_DEBUG(log_msg);

	m_pOutInfo = pout;
	sprintf(log_msg,"iret[%d]",0);
	LOG_INFO(log_msg);

	PowerOFF_EX();
	return 0;
}

BSTR CSSCARDCtrl::ocxReadTrack(LONG lTimeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult = "";
	int iret = -1;
	
	iret = ocxOpenDevice();
	if (1!=iret && 2!=iret && 3!=iret)
	{
		return strResult.AllocSysString();
	}

	char csTrack2[MAX_PATH] = {};
	char csTrack3[MAX_PATH] = {};
	ReadCardTracks(csTrack2,csTrack3,lTimeout);
	strResult.Append(csTrack2);
	strResult.Append("^");
	strResult.Append(csTrack3);
	strResult.Append("^");
	return strResult.AllocSysString();
}


LONG CSSCARDCtrl::ocxEjectCard(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return PowerOFF_EX();
}


ULONG CSSCARDCtrl::ocxCloseDevice(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bIsRunCardReadOpen = false;
	int iret = Close_EX();
	if (1==iret || 2==iret || 3==iret)
	{
		return 0;
	}
	return 1;
}


LONG CSSCARDCtrl::ocxOpenDevice(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int iret = -1;
	char msg[MAX_PATH] = {};
	if (!bIsRunCardReadOpen)
	{
		if(0!=Init())
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x10,msg);
			m_pOutInfo = msg;
			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x10,msg);
			LOG_DEBUG(log_msg);

			sprintf(log_msg,"iret[%d]",iret);
			LOG_INFO(log_msg);
			return iret;//参数错误
		}

		iret = Open_EX();
		sprintf(log_msg,"Open_EX -> iret[%d]",iret);
		LOG_DEBUG(log_msg);

		if (1!=iret && 2!=iret && 3!=iret)
		{
			iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
			m_pOutInfo = msg;

			sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
			LOG_DEBUG(log_msg);

			sprintf(log_msg,"iret[%d]",iret);
			LOG_INFO(log_msg);
			return iret;//参数错误
		}
		bIsRunCardReadOpen = true;
	}
	else
	{
		iret = 1;
	}
	return iret;
}

//验证输入密码
//LONG CSSCARDCtrl::iVerifyPIN(LONG iType)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	// TODO: 在此添加调度处理程序代码
//	sprintf(log_msg,"Enter.%d",iType);
//	LOG_INFO(log_msg);
//
//	char msg[MAX_PATH] = {};
//	int iret = -1;
//	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
//	{
//		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
//		m_pOutInfo = msg;
//
//		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
//		LOG_DEBUG(log_msg);
//
//		sprintf(log_msg,"iret[%d]",iret);
//		LOG_INFO(log_msg);
//		return iret;//参数错误
//	}
//
//	return 0;
//}


LONG CSSCARDCtrl::iVerifyPIN(LONG iType, LPCTSTR pin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	sprintf(log_msg,"Enter.iType=%d;pin=%s",iType,pin);
	LOG_INFO(log_msg);
	
	char msg[MAX_PATH] = {};
	int iret = -1;
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
	
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);
	
		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	/* 20180725 杨传杰老师  验密是进卡之后的不需要添加 进卡 退卡
	iret = ocxOpenDevice();//1为IDC 2：IC2 3：IDC与IC2打开成功
	if (1!=iret && 2!=iret && 3!=iret)
	{
		return iret;
	}
	*/
	memset(csAtr,0x00,sizeof(csAtr));
	//银海 杨（传杰）老师需求改成6秒
	iret = PowerOn_EX(iType,6,csAtr);
	if (0!=iret)
	{
		//ResetDevice();
		iret = getRetMsgBySw1Sw2(0xFF,0x20,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x20,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}
	
	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET_NO_OFF(iret);
	VALIAD_SW1_SW2_NO_OFF(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);

	int iPinLen = strlen(pin);
	unsigned char Lc = 0x00;
	if (0 < iPinLen)
	{
		iPinLen /= 2;
		Lc = ((unsigned char)iPinLen - 0x30) & 0x0F;
	}
	iret = VERIFY_SSSE_YH(Lc,(char*)pin,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET_NO_OFF(iret);
	VALIAD_SW1_SW2_NO_OFF(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);
	/* 20180725 杨传杰老师  验密是进卡之后的不需要添加 进卡 退卡
	PowerOFF_EX();
	*/
	m_pOutInfo = "";
	sprintf(log_msg,"iret[%d]",iret);
	LOG_INFO(log_msg);
	return 0;
}


LONG CSSCARDCtrl::iChangePIN(LONG iType, LPCTSTR oldPin, LPCTSTR newPin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	sprintf(log_msg,"Enter.iType=%d;oldPin=%s;newPin=%s",iType,oldPin,newPin);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	/* 20180725 杨传杰老师  验密是进卡之后的不需要添加 进卡 退卡
	iret = ocxOpenDevice();//1为IDC 2：IC2 3：IDC与IC2打开成功
	if (1!=iret && 2!=iret && 3!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
		LOG_DEBUG(log_msg);
		return iret;
	}
	*/
	memset(csAtr,0x00,sizeof(csAtr));
	//银海 杨（传杰）老师需求改成6秒
	iret = PowerOn_EX(iType,6,csAtr);
	if (0!=iret)
	{
		//ResetDevice();
		iret = getRetMsgBySw1Sw2(0xFF,0x20,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x20,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET_NO_OFF(iret);
	VALIAD_SW1_SW2_NO_OFF(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);


	unsigned char Lc = 0x00;
	char cLc[2] = {0};
	int iLcLen = 1;
	char cIndata[MAX_PATH] = {0};
	if (strlen(oldPin) > 0)
	{
		iLcLen += strlen(oldPin) / 2;
	}

	if (strlen(newPin) > 0)
	{
		iLcLen += strlen(newPin) / 2;
	}

	sprintf(cLc,"%X",iLcLen);
	sprintf(cIndata,"%sFF%s",oldPin,newPin);
	Lc = (cLc[0] - 0x30) & 0xFF;

	iret = CHANGE_PIN_SSSE_YH(Lc,cIndata,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET_NO_OFF(iret);
	VALIAD_SW1_SW2_NO_OFF(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);
	/* 20180725 杨传杰老师  验密是进卡之后的不需要添加 进卡 退卡
	PowerOFF_EX();
	*/
	m_pOutInfo = "";
	sprintf(log_msg,"iret[%d]",iret);
	LOG_INFO(log_msg);
	return 0;
}


LONG CSSCARDCtrl::iReloadPIN(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	sprintf(log_msg,"%d",iType);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	// TODO: 在此添加调度处理程序代码
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	iret = ocxOpenDevice();//1为IDC 2：IC2 3：IDC与IC2打开成功
	if (1!=iret && 2!=iret && 3!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
		LOG_DEBUG(log_msg);
		return iret;
	}

	char pchData[MAX_PATH] = {};
	int iDataLen;
	char pchErrCode[MAX_PATH] = {};
	char pchError[MAX_PATH] = {};
	iret = psamPowerOn(2,pchData,&iDataLen,pchErrCode,pchError);
	if (0!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x30,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x30,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}
	//下面流程在迭代一 实现加密机中不做；迭代一只触发返回-2201就可以执行后续加密机操作流程
	/*
	（4）	选择社保卡社会保障系统环境，同时根据卡片返回的应答信息确定算法环境，根据算法环境标识选择PSAM卡相应算法密钥文件，具体方法详见10.1；
	（5）	读取社保卡的卡识别码、卡号，与输入参数pCardInfo一一核对，核对成功后进行下一步操作；核对不成功则报错退出；
	（6）	启动密码键盘，语音和显示同时依次提示持卡人“请输入新密码”、“请再次输入新密码”，分别获取密码键盘上持卡人输入的新PIN（有效长度为4-16位数字），判断两次输入的新密码是否一致，并以此新密码进行PIN重置操作；
	（7）	调用SSSE32.DLL中的“关闭设备”函数关闭设备，释放端口；
	（8）	以上操作过程中出现异常时，均应先调用SSSE32.DLL动态库中的“关闭设备”函数关闭设备，释放端口，然后退出函数，返回错误代码和错误信息描述。
	*/
	sprintf(log_msg,"iret[%d]",0);
	LOG_INFO(log_msg);
	return 0;
}


LONG CSSCARDCtrl::iReloadPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	sprintf(log_msg,"%d",iType);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	// TODO: 在此添加调度处理程序代码
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	iret = ocxOpenDevice();//1为IDC 2：IC2 3：IDC与IC2打开成功
	if (1!=iret && 2!=iret && 3!=iret)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x11,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x11,msg);
		LOG_DEBUG(log_msg);
		return iret;
	}

	memset(csAtr,0x00,sizeof(csAtr));
	//银海 杨（传杰）老师需求改成6秒
	iret = PowerOn_EX(iType,6,csAtr);
	if (0!=iret)
	{
		ResetDevice();
		iret = getRetMsgBySw1Sw2(0xFF,0x20,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x20,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}


	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);

	//得到算法标识
	//9F0C03860103
	std::string rapdu(outData);

	char algorithm[3] = {};
	std::string::size_type pos = rapdu.find("9F0C038601");
	if (std::string::npos == pos)
	{
		strcpy(algorithm,"01");
	}
	else
	{
		strncpy(algorithm,(char*)rapdu.substr(pos+9,2).c_str(),2);
	}
	sprintf(log_msg,"algorithm[%s]",algorithm);
	LOG_DEBUG(log_msg);
	//EF05
	MEMSET_APDU
	unsigned char FILE_SSSE_YH[] = "\xEF\x05";
	iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	//EF05 01
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x01,0x00,0x12,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	_KLV klv = getKLV(outData);

	memset(EF05_01,0x00,sizeof(EF05_01));
	strcpy(EF05_01,klv.v);
	sprintf(log_msg,"EF05_01[%s]",EF05_01);
	LOG_DEBUG(log_msg);

	//EF05 07
	MEMSET_APDU
	iret = READ_RECORD_SSSE_YH(0x07,0x00,0x0B,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	klv = getKLV(outData);
	memset(EF05_07,0x00,sizeof(EF05_07));
	strcpy(EF05_07,klv.v);
	sprintf(log_msg,"EF05_07[%s]",EF05_07);
	LOG_DEBUG(log_msg);

	char ucEF05_07[10] = {};
	DSP_2_HEX((unsigned char*)EF05_07,(unsigned char*)ucEF05_07,9);
	sprintf(log_msg,"ucEF05_07[%s]",ucEF05_07);
	LOG_DEBUG(log_msg);

	//卡识别码|卡号
	std::vector<std::string> vec = split((char*)pCardInfo,'|');
	if (vec.size() < 2 || 0!=strcmp(vec[0].c_str(),EF05_01) || 0!=strcmp(vec[1].c_str(),(char*)ucEF05_07));
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x50,msg);
		m_pOutInfo = msg;

		sprintf(log_msg,"与pCardInfo的卡识别码|卡号存在不匹配");
		LOG_DEBUG(log_msg);
		return iret;
	}

	char externalAuthSource[17] = {};
	char externalAuthProcess[17] = {};
	char pout[512] = {};

	//外部认证 原始数据
	MEMSET_APDU
	iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	strncpy(externalAuthSource,outData,16);
	sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--externalAuthSource[%s]",externalAuthSource);
	LOG_DEBUG(log_msg);

	//外部认证 过程因子
	MEMSET_APDU
	iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	strncpy(externalAuthProcess,outData,16);
	sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--externalAuthProcess[%s]",externalAuthProcess);
	LOG_DEBUG(log_msg);

	sprintf(pout,"%s|%s|%s|%s|",algorithm,"0090",externalAuthProcess,externalAuthSource);
	m_pOutInfo = pout;
	sprintf(log_msg,"iret[%d],pout[%s]",iret,pout);
	LOG_INFO(log_msg);

	return 0;
}


LONG CSSCARDCtrl::iReloadPIN_HSM_Step2(LPCTSTR pKey, LPCTSTR newPin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	sprintf(log_msg,"%s",pKey);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	// TODO: 在此添加调度处理程序代码
	if (0 == strlen(pKey))
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	
	char externAuthData[33] = {};
	strncpy(externAuthData,pKey,32);
	iret = EXTERNAL_AUTHENTICATION_SSSE_YH(0x06,0x10,externAuthData,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	
	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	sprintf(log_msg,"outData[%s]",outData);
	LOG_DEBUG(log_msg);

	//得到算法标识
	//9F0C03860103
	std::string rapdu(outData);

	char algorithm[3] = {};
	std::string::size_type pos = rapdu.find("9F0C038601");
	if (std::string::npos == pos)
	{
		strcpy(algorithm,"01");
	}
	else
	{
		strncpy(algorithm,(char*)rapdu.substr(pos+10,2).c_str(),2);
	}
	sprintf(log_msg,"algorithm[%s]",algorithm);
	LOG_DEBUG(log_msg);

	//外部认证 过程因子
	char AuthProcess[36] = {0};
	MEMSET_APDU
	iret = GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);
	strncpy(AuthProcess,outData,16);
	sprintf(log_msg,"GET_CHALLENGE_SSSE_YH--externalAuthProcess[%s]",AuthProcess);
	LOG_DEBUG(log_msg);

	char addr[16] = "0173";
	char apdu[16] = "8424000114";
	char pout[1024] = {0};
	//旧密码|新密码

	sprintf(pout,"%s|%s|%s|%s|%s|",algorithm,addr,AuthProcess,apdu,newPin);

	m_pOutInfo = pout;
	sprintf(log_msg,"iret[%d],pout[%s]",iret,pout);
	LOG_INFO(log_msg);
	return 0;
}



LONG CSSCARDCtrl::iReloadPIN_HSM_Step3(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	sprintf(log_msg,"%s",pKey);
	LOG_INFO(log_msg);

	char msg[MAX_PATH] = {};
	int iret = -1;
	// TODO: 在此添加调度处理程序代码
	if (strlen(pKey)<10)
	{
		iret = getRetMsgBySw1Sw2(0xFF,0x00,msg);
		m_pOutInfo = msg;
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x00,msg);
		LOG_DEBUG(log_msg);

		sprintf(log_msg,"iret[%d]",iret);
		LOG_INFO(log_msg);
		return iret;//参数错误
	}

	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	char cIndata[MAX_PATH] = {0};
	strcpy(cIndata,pKey);
	int iIndataLen = strlen(cIndata)/2;
	 unsigned char Lc = iIndataLen & 0xFF;
	iret = UNBLOCK_SSSE_YH(0x01,Lc,cIndata,outData,outDataLen,errorCode,errorMsg);
	VALIAD_RET(iret);
	VALIAD_SW1_SW2(errorCode);

	PowerOFF_EX();
	m_pOutInfo = "";
	sprintf(log_msg,"iret[%d]",0);
	LOG_INFO(log_msg);
	return 0;
}
