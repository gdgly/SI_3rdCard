/*********************************************************
copyright (c) 2018-2028, GWI
File name: GwiCardReadAdapt.js
Author: wsh  Version: V1.0.0.3 Date: 2018-07-10
Description: 实现JS对GWI_CardRead_AdaptEx.ocx的封装调用
History:
1.	Date: 2018-07-10
	Author: wsh
	Modification: 创建，银海变更需求从控件变成JS+AJAX调用
	
*********************************************************/
var _ocx;
function setOcx(ocx){
	_ocx = ocx;
}

function getOcx(){
	return _ocx;
}


function native2ascii(strNative) { 
     var output = ""; 
     for (var i=0; i<strNative.length; i++) { 
         var c = strNative.charAt(i); 
         var cc = strNative.charCodeAt(i); 
         if (cc > 0xff) 
           output += "\\u" + toHex(cc >>  8 ) + toHex(cc & 0xff); 
         else 
           output += c; 
     } 
     return output; 
} 

var hexChars = "0123456789ABCDEF"; 
function toHex(n) { 
     var nH = (n >> 4) & 0x0f; 
     var nL = n & 0x0f; 
     return hexChars.charAt(nH) + hexChars.charAt(nL); 
} 

function ascii2native(strAscii) { 
     var output = ""; 
     var posFrom = 0; 
     var posTo = strAscii.indexOf("\\u", posFrom); 
     while (posTo >= 0) { 
         output += strAscii.substring(posFrom, posTo); 
         output += toChar(strAscii.substr(posTo, 6)); 
         posFrom = posTo + 6; 
         posTo = strAscii.indexOf("\\u", posFrom); 
     } 
     output += strAscii.substr(posFrom); 
     return output; 
} 

function toChar(str) { 
     if (str.substr(0, 2) != "\\u") return str; 

     var code = 0; 
     for (var i=2; i<str.length; i++) { 
         var cc = str.charCodeAt(i); 
         if (cc >= 0x30 && cc <= 0x39) 
             cc = cc - 0x30; 
         else if (cc >= 0x41 && cc <= 0x5A) 
             cc = cc - 0x41 + 10; 
         else if (cc >= 0x61 && cc <= 0x7A) 
             cc = cc - 0x61 + 10; 

         code <<= 4; 
         code += cc; 
     } 

     if (code < 0xff) return str; 

     return String.fromCharCode(code); 
} 
/*测试桩
function f(){
	if(getOcx() == null){
		return false;
	}
	_ocx.test();
}
*/

function ocxInit(){
	return _ocx.ocx_Init();
}

/*********************************************************
Function: ocxPowerOnEX
Description: 实现进卡上电
Input:
	long(类型） iType（参数名） 上电的卡类型（参数作用） 1、2、3、4（参数取值范围） 1：接触 2：非接触 3：接触优先 4：非接触优先
	long(类型） lTimeout（参数名） 超时时间（参数作用） 秒为单位（参数取值范围） 1-255
Output:
    
Return: 
	string(类型） 上电返回值（返回值作用）
	‘’（值）  上电错误（值的意义）
	字符串    上电复位值
Others:
    @wsh
*********************************************************/
function ocxPowerOnEX(iType,lTimeout){
	return _ocx.ocx_PowerOn_EX(iType,lTimeout);
}

/*********************************************************
Function: ocxPowerOFFEX
Description: 实现进卡下电
Input:
Output:
    
Return: 
	long(类型） 下电返回值（返回值作用）
	0（值）     成功（值的意义）
	其它        失败
Others:
    @wsh
*********************************************************/
function ocxPowerOFFEX(){
	return _ocx.ocx_PowerOFF_EX();
}

/*********************************************************
Function: ocxPowerOnEX
Description: 实现进卡上电
Input:
	string(类型） szDataIn（参数名） 指令数据（参数作用） 字符串（参数取值范围） CN
	long(类型）   iLenIn（参数名）   指令数据长度（参数作用） >0（参数取值范围） <1024
Output:
    
Return: 
	string(类型） 指令返回值长度^返回指令^（返回值作用）
	0^^（值）  指令错误（值的意义）
	字符串    返回指令长度^返回指令^
Others:
    @wsh
*********************************************************/
function ocxChipIOEX(szDataIn, iLenIn){
	return _ocx.ocx_ChipIO_EX(szDataIn, iLenIn);
}

/*********************************************************
Function: ocxOpenEX
Description: 实现打开设备
Input:
Output:
    
Return: 
	long(类型） 打开返回值（返回值作用）
	1、2、3（值）     成功（值的意义）1插入式读卡器 2非接触读卡器 3插入式和非接触式
	其它        失败
Others:
    @wsh
*********************************************************/
function ocxOpenEX(){
	return _ocx.ocx_Open_EX();
}

/*********************************************************
Function: ocxCloseEx
Description: 实现关闭设备
Input:
Output:
    
Return: 
	long(类型） 打开返回值（返回值作用）
	1、2、3（值）     成功（值的意义）1插入式读卡器 2非接触读卡器 3插入式和非接触式
	其它        失败
Others:
    @wsh
*********************************************************/
function ocxCloseEx(){
	return _ocx.ocx_Close_EX();
}

/*********************************************************
Function: ocxResetDevice
Description: 实现复位设备
Input:
Output:
    
Return: 
	long(类型） 打开返回值（返回值作用）
	1、2、3（值）     成功（值的意义）1插入式读卡器 2非接触读卡器 3插入式和非接触式
	其它        失败
Others:
    @wsh
*********************************************************/
function ocxResetDevice(){
	return _ocx.ocx_ResetDevice();
}

/*********************************************************
Function: ocxReadCardTracks
Description: 实现读2,3磁道
Input:
	long(类型）   lTimeout（参数名）   超时时间（秒）（参数作用） >0（参数取值范围） <1024
Output:
    
Return: 
	string(类型） 二磁道^三磁道^（返回值作用）
	^^（值）  读磁失败（值的意义）
	字符串    二磁道^三磁道^
Others:
    @wsh
*********************************************************/
function ocxReadCardTracks(lTimeout){
	return _ocx.ocx_ReadCardTracks(lTimeout);
}

/*********************************************************
Function: ocxGetDeviceStatus
Description: 获取设备状态
Input:
Output:
    
Return: 
	string(类型） 插入式状态^非接触状态^（返回值作用）
	^^（值）  设备状态失败（值的意义）
	字符串    插入式状态^非接触状态^
	0 :通道无卡
	1 :卡在通道口
	2 :卡在通道中（不在上电位）
	3:卡在通道中，且已在上电位
	4 :夹卡 
	5 :通道状态未知
	-1：调用出错
Others:
    @wsh
*********************************************************/
function ocxGetDeviceStatus(){
	return _ocx.ocx_GetDeviceStatus();
}

/*********************************************************
Function: ocxGetMediaStatus
Description: 获取卡介质状态
Input:
Output:
    
Return: 
	string(类型） 插入式状态^非接触状态^（返回值作用）
	^^（值）  设备状态失败（值的意义）
	字符串    插入式状态^非接触状态^
	1 :卡在通道
	2 :卡状态未知
Others:
    @wsh
*********************************************************/
function ocxGetMediaStatus(){
	return _ocx.ocx_GetMediaStatus();
}

/*********************************************************
Function: ocxGetSN
Description: 获取读卡器SN
Input:
Output:
    
Return: 
	string(类型） 读卡器SN码（返回值作用）
	‘’（值）  SN码获取失败（值的意义）
	字符串    读卡器SN码
Others:
    @wsh
*********************************************************/
function ocxGetSN(){
	return _ocx.ocx_GetSN();
}
/*********************************************************
copyright (c) 2018-2028, GWI
File name: GwiSamAdapt.js
Author: wsh  Version: V1.0.0.3 Date: 2018-07-10
Description: 实现JS对psam卡座的封装调用
History:
1.	Date: 2018-07-10
	Author: wsh
	Modification: 创建，银海变更需求从控件变成JS+AJAX调用
	
*********************************************************/



/*********************************************************
Function: psamPowerOn
Description: 实现上电
Input:
	long(类型） iSlotNum（参数名） 上电的卡座号（参数作用） 1、2、3、4（参数取值范围） 
Output:
    
Return: 
	string(类型） 上电返回值（返回值作用）
	‘’（值）  上电错误（值的意义）
	字符串    上电复位值
Others:
    @wsh
*********************************************************/
function psamPowerOn(iSlotNum){
	return '';
}



/*********************************************************
copyright (c) 2018-2028, GWI
File name: GwiSsseScApi.js
Author: wsh  Version: V1.0.0.3 Date: 2018-07-12
Description: 四川省社保卡指令封装

1.	Date: 2018-07-12
	Author: wsh
	Modification: 创建，银海变更需求从控件变成JS+AJAX调用
	
*********************************************************/

/*********************************************************
Function: doExchange
Description: 数据指令封装
Input:
	string(类型） inData（参数名） 输入指令（参数作用）ASCII （参数取值范围） 
	int(类型）    inDataLen（参数名） 输入指令长度（参数作用） （参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令长度，返回指令]（返回值作用） ASCII
	[0,]（值）  返回指令失败（值的意义）
	[4,905F]    返回指令长度4，返回指令9057
Others:
    @wsh
*********************************************************/
function doExchange(inData, inDataLen){
	var iret = ocxChipIOEX(inData,inDataLen);
	return iret.split('^');
}
/*********************************************************
Function: getRespSw1Sw2
Description: 得到指令最后2个字节保存到SW1 SW2
Input:
	string(类型） csData（参数名） 指令（参数作用）ASCII 转成 HEX（参数取值范围） 
Output:
    
Return: 
	[](类型） [指令最后第二字节，指令最后第一字节]（返回值作用） ASCII
	['00','00']（值）  指令不正确（值的意义）
	[90,00]    sw1:90  sw2:00
Others:
    @wsh
*********************************************************/
function getRespSw1Sw2(csData){
    var csDataLen = csData.length;
    if (csDataLen<4)
    {
    	return ['00','00'];
    }
    var sw1 = csData.substr(csDataLen-4,2);
    var sw2 = csData.substr(csDataLen-2,2);
    return [sw1,sw2];
}
/*********************************************************
Function: selectSsseYH
Description: 四川社保卡选择社保卡应用DF
Input:
	
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function selectSsseYH(){
	/* c++ 内部代码
	capdu[0] = 0x00;
	capdu[1] = 0xA4;
	capdu[2] = 0x04;
	capdu[3] = 0x00;
	capdu[4] = 0x0F;
	memcpy(capdu+5,"\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 15);
	*/
    var capdu = "";
    capdu += '00';
    capdu += 'A4';
    capdu += '04';
    capdu += '00';
    capdu += '0F';
    capdu += '7378312E73682EC9E7BBE1B1A3D5CF';

    var capduLen = 40;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}

/*********************************************************
Function: SelectFileSsseYH
Description: 四川社保卡选择社保卡目标文件EF
Input:
	string(类型） P1（参数名） 用文件标识符在当前 DF 下选择 EF （数据域=EF 的文件标识符）（参数作用）02（参数取值范围） 
	string(类型） Lc（参数名） ‘05’-‘10’（使用文件名或 AID 时）或‘02’（使用文件标识符时）或‘00’（参数作用）02（参数取值范围） 
	string(类型） inData（参数名） 文件标识符（参数作用）EF05 EF06...（参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function SelectFileSsseYH(P1, Lc, inData){
/* c++ 内部代码
	capdu[0] = 0x00;
	capdu[1] = 0xA4;
	capdu[2] = P1;
	capdu[3] = 0x00;
	HEX_2_DSP(&Lc,ucLc,1);
	capdu[4] = Lc;

	unsigned char ucLc[3] = {};

	int inDataLen = (ucLc[0]-0x30)*16+(ucLc[1]-0x30);
	memcpy(capdu+5,inData, inDataLen);
 */
    var capdu = "";
    capdu += '00';
    capdu += 'A4';
    capdu +=  P1;
    capdu += '00';
    capdu +=  Lc;
    capdu += inData;

    var capduLen = 14;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}

/*********************************************************
Function: GetChallengeSsseYH
Description: 四川社保卡获取随机数
Input:
	string(类型） Le（参数名） Le ‘04’或‘08’或‘10'随机数长度HEX（参数作用）08（参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function GetChallengeSsseYH(Le)
{
/*
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x84;
	capdu[2] = 0x00;
	capdu[3] = 0x00;
	capdu[4] = Le; 
	
	//执行apdu
	int inDataLen = 5;
	*/
	var capdu = "";
    capdu += '00';
    capdu += '84';
    capdu += '00';
    capdu += '00';
    capdu +=  Le;

    var capduLen = 10;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}

/*********************************************************
Function: InternalAuthenticationSsseYH
Description: 四川社保卡内部认证
Input:
	string(类型） Le（参数名） Le ‘04’或‘08’或‘10'随机数长度HEX（参数作用）08（参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function InternalAuthenticationSsseYH(Lc, inData)
{
	/*
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x88;
	capdu[2] = 0x00;
	capdu[3] = 0x00;
	capdu[4] = Lc; 

	//执行apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	*/
	var capdu = "";
    capdu += '00';
    capdu += '88';
    capdu += '00';
    capdu += '00';
    capdu +=  Lc;
    capdu +=  inData;
    var capduLen = inData.length + 10;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}

/*********************************************************
Function: ReadRecordSsseYH
Description: 四川社保卡读域数据
Input:
	string(类型） P1（参数名） 记录号或记录标识符（参数作用）‘ 01’ -‘ FE’，‘ 00’表示当前记录（参数取值范围） 
	string(类型） P2（参数名） 引用控制参数（参数作用）（参数取值范围） 
	string(类型） Le（参数名） ‘00’ 或要读出的数据的长度（参数作用）（参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function ReadRecordSsseYH(P1,P2,Le)
{
	/*
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0xB2;
	capdu[2] = P1;
	capdu[3] = P2;
	capdu[4] = Le;
	//执行apdu
	int inDataLen = 5;
	*/
	var capdu = "";
    capdu += '00';
    capdu += 'B2';
    capdu +=  P1;
    capdu +=  P2;
    capdu +=  Le;
    var capduLen = 10;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}

/*********************************************************
Function: ExternalAuthenticationSsseYH
Description: 四川社保卡外部认证
Input:
	string(类型） P2（参数名） 密钥标识符（参数作用）OA（参数取值范围） 
	string(类型） Lc（参数名） 加密数据长度（参数作用）‘10’ ~ ‘11’（参数取值范围） 
	string(类型） inData （参数名） 外部认证数据（参数作用）ASCII（参数取值范围） 
Output:
    
Return: 
	[](类型） [返回指令SW1，返回指令SW2，返回指令]（返回值作用） ASCII
	[‘00’,‘00’,rapdu]（值）  返回指令失败（值的意义）
	[‘90’,‘90’，‘905F9000’]    返回指令SW1：90，返回指令SW2:90，返回指令：905F9000
Others:
    @wsh
*********************************************************/
function ExternalAuthenticationSsseYH(P2,Lc,inData)
{
	/*
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x82;
	capdu[2] = 0x00;
	capdu[3] = P2;
	capdu[4] = Lc;
	//执行apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	*/
	var capdu = "";
    capdu += '00';
    capdu += '82';
    capdu += '00';
    capdu +=  P2;
    capdu +=  Lc;
    capdu +=  inData;
    var capduLen = inData.length + 10;
    var rapdu = doExchange(capdu,capduLen);
    var sw1sw2 = getRespSw1Sw2(rapdu);
    return [sw1sw2[0],sw1sw2[1],rapdu];
}



/*********************************************************
copyright (c) 2018-2028, GWI
File name: GwiSsseScApi.js
Author: wsh  Version: V1.0.0.3 Date: 2018-07-12
Description: 四川省社保卡指令封装

1.	Date: 2018-07-12
	Author: wsh
	Modification: 创建，银海变更需求从控件变成JS+AJAX调用
	
*********************************************************/

var retmsgJson = 
	'[{"ret":"-1","msg":		"卡类型不对","sw1":"FF","sw2":"00"},\
	{"ret":"-2","msg":		"无卡","sw1":"00","sw2":"00"},\
	{"ret":"-3","msg":		"有卡未上电","sw1":"FF","sw2":"20"},\
	{"ret":"-4","msg":		"卡无应答","sw1":"FF","sw2":"21"},\
	{"ret":"-5","msg":	"加载动态库错","sw1":"00","sw2":"00"},\
	{"ret":"-11","msg":		"读卡器连接错","sw1":"FF","sw2":"11"},\
	{"ret":"-12","msg":		"未建立连接","sw1":"FF","sw2":"10"},\
	{"ret":"-13","msg":		"（动态库）不支持该命令","sw1":"00","sw2":"00"},\
	{"ret":"-14","msg":		"（发给动态库的）命令参数错","sw1":"00","sw2":"00"},\
	{"ret":"-15","msg":		"信息校验和出错","sw1":"00","sw2":"00"},\
	{"ret":"-20","msg":		"卡识别码格式错","sw1":"00","sw2":"00"},\
	{"ret":"-21","msg":		"内部认证失败（用户卡不合法)","sw1":"FF","sw2":"40"},\
	{"ret":"-22","msg":		"传入数据与卡内不符","sw1":"00","sw2":"00"},\
	{"ret":"-23","msg":		"传入数据不合法","sw1":"FF","sw2":"01"},\
	{"ret":"-24","msg":		"PSAM卡密钥级别不够","sw1":"00","sw2":"00"},\
	{"ret":"-25","msg":		"内部认证与加密机不一致失败","sw1":"FF","sw2":"41"},\
	{"ret":"-31","msg":		"用户取消密码输入","sw1":"00","sw2":"00"},\
	{"ret":"-32","msg":		"密码输入操作超时","sw1":"00","sw2":"00"},\
	{"ret":"-33","msg":		"输入密码长度错","sw1":"00","sw2":"00"},\
	{"ret":"-34","msg":		"两次输入密码不一致","sw1":"00","sw2":"00"},\
	{"ret":"-35","msg":		"初始密码不能交易","sw1":"00","sw2":"00"},\
	{"ret":"-36","msg":		"不能改为初始密码","sw1":"00","sw2":"00"},\
	{"ret":"-41","msg":		"运算数据含非法字符","sw1":"00","sw2":"00"},\
	{"ret":"-42","msg":		"运算数据长度错","sw1":"00","sw2":"00"},\
	{"ret":"-51","msg":		"PIN校验失败，剩余次数N次（根据卡返回信息）","sw1":"00","sw2":"00"},\
	{"ret":"-52","msg":		"PIN锁定","sw1":"00","sw2":"00"},\
	{"ret":"-2201","msg":		"无PSAM卡","sw1":"FF","sw2":"30"},\
	{"ret":"-2202","msg":		"PSAM卡算法不支持（即PSAM卡内没有SSF33算法或SM4算法）","sw1":"00","sw2":"00"},\
	{"ret":"-2203","msg":		"PSAM卡内没有RKSSSE密钥（3.0卡读个人基本信息需要RKSSSE密钥外部认证）","sw1":"00","sw2":"00"},\
	{"ret":"-2204","msg":		"不需要加密机认证","sw1":"00","sw2":"00"},\
	{"ret":"-25536","msg":	"外部认证失败，剩余可尝试次数2、1、0次","sw1":"00","sw2":"00"},\
	{"ret":"-25537","msg":	" 外部认证失败，剩余可尝试次数2、1、0次","sw1":"00","sw2":"00"},\
	{"ret":"-25538","msg":		"外部认证失败，剩余可尝试次数2、1、0次","sw1":"00","sw2":"00"},\
	{"ret":"-26368","msg":	"Lc/Le不正确","sw1":"6C","sw2":"00"},\
	{"ret":"-26369","msg":	"P1、 P2 与 Lc 不一致","sw1":"67","sw2":"00"},\
	{"ret":"-26370","msg":	"参数 P1、 P2 不正确","sw1":"6A","sw2":"86"},\
	{"ret":"-26371","msg":	"CLA 错","sw1":"6E","sw2":"00"},\
	{"ret":"-26881","msg":	"命令不接受（无效状态）","sw1":"69","sw2":"86"},\
	{"ret":"-27009","msg":	"命令与文件结构不相符、当前文件非所需文件","sw1":"69","sw2":"81"},\
	{"ret":"-27010","msg":	"不满足安全条件","sw1":"69","sw2":"82"},\
	{"ret":"-27011","msg":	"密钥锁定（算法锁定）鉴别方法锁定","sw1":"00","sw2":"00"},\
	{"ret":"-27012","msg":	"引用数据无效、随机数无效","sw1":"00","sw2":"00"},\
	{"ret":"-27013","msg":	"不满足使用条件、应用被锁定、应用未选择、余额上溢","sw1":"00","sw2":"00"},\
	{"ret":"-27016","msg":	"安全报文数据项不正确、MAC不正确","sw1":"00","sw2":"00"},\
	{"ret":"-27264","msg":	"数据域参数不正确","sw1":"00","sw2":"00"},\
	{"ret":"-27265","msg":	"不支持该功能、卡中无MF、卡被锁定、应用锁定","sw1":"6A","sw2":"81"},\
	{"ret":"-27266","msg":	"未找到文件、文件标识相重、SFI不正确","sw1":"6A","sw2":"82"},\
	{"ret":"-27267","msg":	"未找到记录","sw1":"6A","sw2":"83"},\
	{"ret":"-27272","msg":	"未找到引用数据、未找到密钥","sw1":"6A","sw2":"88"},\
	{"ret":"-37634","msg":	"MAC无效","sw1":"00","sw2":"00"},\
	{"ret":"-37635","msg":	"应用已被永久锁定、卡片锁定","sw1":"93","sw2":"03"},\
	{"ret":"-37891","msg":	"PSAM卡不支持消费交易","sw1":"00","sw2":"00"},\
	{"ret":"-37894","msg":	"所需MAC（或/和TAC）不可用","sw1":"00,","sw2":"00"},\
	{"ret":"-999","msg":	"未知错误","sw1":"00","sw2":"00"}\
 ]';

var retmagJsonArray = eval('(' + retmsgJson + ')');
function getRetMsg(sw1,sw2){
	for (var i = retmagJsonArray.length - 1; i >= 0; i--) {
		if (sw1 === '6E') {
			retrun ['-26371','CLA 错'];
		}

		if (retmagJsonArray[i].sw1 === sw1 && retmagJsonArray[i].sw2 === sw2){
			return [retmagJsonArray[i].ret,retmagJsonArray[i].msg];
		} 
	}
	return ['-999',"未知错误"];
}

/*********************************************************
Function: iReadCardBas
Description: 银海久远 读基本信息
Input:
	int(类型） iType（参数名） 操作卡的类型，（参数作用）定义如下：1-接触式操作卡；2-非接触式操作卡；3-自动寻卡，接触式操作卡优先；4-自动寻卡，非接触式操作卡优先（参数取值范围） 
	
Output:
    
Return: 
	[](类型） [返回值，读出数据或返回错误信息]（返回值作用） 
	[‘0’,pOutInfo]（值）  数据成功（值的意义）
	[‘-1’,‘卡类型不对’]    返回值：-1，读出数据或返回错误信息：卡类型不对
Others:
    @wsh
*********************************************************/
function iReadCardBas(iType){
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType){
		return getRetMsg('FF','00');
	}

	var psamATR = psamPowerOn(2);
	if (psamATR == null || psamATR == '') {
		return getRetMsg('FF','30');
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
 	return [0,psamATR];
}



function openDevice(){
	if (0 == isOpen) {
		if (0!=ocxInit()){
			return getRetMsg('FF','10');
		}

		var iOpen = ocxOpenEX();
		if (1!=iOpen && 2!=iOpen && 3!=iOpen){
			return getRetMsg('FF','11');
		}
		isOpen = 1;
		return [0,""];
	}
}

function getKLV(data) {
	//data 0-1是域名 2-3是长度 后面是长度位数据HEX
	if (data[1].length < 4) {
		return ['','',''];
	}
	var k = data[1].substr(0,2);
	var l = data[1].substr(2,2);

	var lLen = parseInt(l,16)*2;
    var v = data[1].substr(4,lLen);
    return [k,l,v];
}

function dsp2hex(dsp,len) {
	var hex = '';
	for (var i = 0; i < len; i+=2) {
		hex += String.fromCharCode(parseInt(dsp.substr(i,2),16));
	}
	return hex;
}

var isOpen = 0;
var csAtr = '';
var algorithm = '01';
var EF05_01 = '';
var EF05_01_CityCode = '';
var EF05_03 = '';
var EF05_03_Version = '';
var EF05_07 = '';
var interAuth = '';

/*********************************************************
Function: iReadCardBas_HSM_Step1
Description: 银海久远 读基本信息 加密机第一步
Input:
	int(类型） iType（参数名） 操作卡的类型，（参数作用）定义如下：1-接触式操作卡；2-非接触式操作卡；3-自动寻卡，接触式操作卡优先；4-自动寻卡，非接触式操作卡优先（参数取值范围） 
	
Output:
    
Return: 
	[](类型） [返回值，读出数据或返回错误信息]（返回值作用） 
	[‘0’,pOutInfo]（值）  发给加密机的数据（值的意义）
	[‘-1’,‘卡类型不对’]    返回值：-1，读出数据或返回错误信息：卡类型不对
Others:
    @wsh
*********************************************************/
function iReadCardBas_HSM_Step1(iType){
	if (1!=iType && 2!=iType && 3!=iType && 4!=iType){
		return getRetMsg('FF','00');
	}

   var openDev = openDevice();
   if (0!=openDev[0]) {
   		return openDev;
   }
	
   csAtr = '';
   csAtr = ocxPowerOnEX(iType,6);
   if ('' == csAtr) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg('FF','20');
   }

   var retselectSsseYH = selectSsseYH();
   if ('90' != retselectSsseYH[0] && '00' != retselectSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retselectSsseYH[0],retselectSsseYH[1]);
   }

   var area9F0C_86 = '9F0C038601';
   
   if (-1 != retselectSsseYH[2].indexOf(area9F0C_86)){
   		algorithm = retselectSsseYH[2].substr(retselectSsseYH[2].indexOf(area9F0C_86)+ area9F0C_86.length,2);
   }

   var retSelectFileSsseYH = SelectFileSsseYH('02','02','EF05');
	if ('90' != retSelectFileSsseYH[0] && '00' != retSelectFileSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retSelectFileSsseYH[0],retSelectFileSsseYH[1]);
    }

    var retReadRecordSsseYH = ReadRecordSsseYH('01','00','12');
    if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
    }

    var klv = getKLV(retReadRecordSsseYH[2]);
    EF05_01 = '';
    EF05_01 = klv[2];

    EF05_01_CityCode = '';
    EF05_01_CityCode = EF05_01.substr(0,6);

    retReadRecordSsseYH = ReadRecordSsseYH('03','00','06');
    if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
    }
    
    klv = getKLV(retReadRecordSsseYH[2]);
    EF05_03 = '';
    EF05_03 = klv[2];

	EF05_03_Version = '';
    EF05_03_Version = String.fromCharCode(parseInt(EF05_03.substr(0,2),16));
    
    retReadRecordSsseYH = ReadRecordSsseYH('07','00','0B');
    if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
    }
    
    klv = getKLV(retReadRecordSsseYH[2]);
    EF05_07 = '';
    EF05_07 = klv[2];

	retselectSsseYH = selectSsseYH();
    if ('90' != retselectSsseYH[0] && '00' != retselectSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retselectSsseYH[0],retselectSsseYH[1]);
    }

	var interAuthSource = '';
	var interAuthProcess = '';
	var externalAuthSource = '';
	var externalAuthProcess = '';

	if ('3' == EF05_03_Version.substr(0,1)) {
		var retGetChallengeSsseYH = GetChallengeSsseYH('08');
		if ('90' != retGetChallengeSsseYH[0] && '00' != retGetChallengeSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retGetChallengeSsseYH[0],retGetChallengeSsseYH[1]);
   	    }
   	    interAuthSource = retGetChallengeSsseYH[2][1].substr(0,16);

   	    retGetChallengeSsseYH = GetChallengeSsseYH('08');
		if ('90' != retGetChallengeSsseYH[0] && '00' != retGetChallengeSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retGetChallengeSsseYH[0],retGetChallengeSsseYH[1]);
   	    }
   	    interAuthProcess = retGetChallengeSsseYH[2][1].substr(0,16);

   	    var interAuthData = '';
   	    interAuthData = interAuthProcess + interAuthSource;
   	    var retInternalAuthenticationSsseYH = InternalAuthenticationSsseYH('10',interAuthData);
		if ('90' != retInternalAuthenticationSsseYH[0] && '00' != retInternalAuthenticationSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retInternalAuthenticationSsseYH[0],retInternalAuthenticationSsseYH[1]);
   	    }

		interAuth = retInternalAuthenticationSsseYH[2][1].substr(0,16);

		retGetChallengeSsseYH = GetChallengeSsseYH('08');
		if ('90' != retGetChallengeSsseYH[0] && '00' != retGetChallengeSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retGetChallengeSsseYH[0],retGetChallengeSsseYH[1]);
   	    }
   	    externalAuthSource = retGetChallengeSsseYH[2][1].substr(0,16);

   	    retGetChallengeSsseYH = GetChallengeSsseYH('08');
		if ('90' != retGetChallengeSsseYH[0] && '00' != retGetChallengeSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retGetChallengeSsseYH[0],retGetChallengeSsseYH[1]);
   	    }
   	    externalAuthProcess = retGetChallengeSsseYH[2][1].substr(0,16);
	}

    var terminalSN = '';
    terminalSN = ocxGetSN();

    var pOut = '';
    pOut = EF05_01_CityCode + '|' + csAtr + '|' + algorithm + '|' + EF05_01 + '|' + interAuthProcess + '|' + interAuthSource +'|' + externalAuthProcess + '|' + externalAuthSource + '|' + terminalSN + '|';
    return ['0',pOut];
}

/*********************************************************
Function: iReadCardBas_HSM_Step2
Description: 银海久远 读基本信息 加密机第二步
Input:
	string(类型） pKey（参数名） 加密机返回数据，（参数作用）三代卡：内部认证结果内部认证数据|外部认证过程因子外部认证数据； 其它卡：随意填（参数取值范围） 
	
Output:
    
Return: 
	[](类型） [返回值，读出数据或返回错误信息]（返回值作用） 
	[‘0’,pOutInfo]（值）  读出的社保卡基本信息各数据项，依次为：发卡地区行政区划代码（卡识别码前6位）、社会保障号码、卡号、卡识别码、姓名、卡复位信息（仅取历史字节）、规范版本、发卡日期、卡有效期、终端机编号、终端设备号。各数据项之间以“|”分割，且最后一个数据项以“|”结尾。（值的意义）
	[‘-1’,‘卡类型不对’]    返回值：-1，读出数据或返回错误信息：卡类型不对
Others:
    @wsh
*********************************************************/
function iReadCardBas_HSM_Step2(pKey){
	if ('3' == EF05_03_Version) {
		if (pKey.length < 64) {
			return getRetMsg('FF','01');
		}

		if (pKey.substr(0,16) != interAuth.substr(0,16)) {
			return getRetMsg('FF','41');
		}

		var externalAuthData = pKey.substr(33,32);
		var retExternalAuthenticationSsseYH = ExternalAuthenticationSsseYH('0A','10',externalAuthData);
		if ('90' != retExternalAuthenticationSsseYH[0] && '00' != retExternalAuthenticationSsseYH[1]) {
	   		ocxPowerOFFEX();//需退卡
	   		return getRetMsg(retExternalAuthenticationSsseYH[0],retExternalAuthenticationSsseYH[1]);
   	    }
	}

	var retSelectFileSsseYH = SelectFileSsseYH('02','02','EF05');
	if ('90' != retSelectFileSsseYH[0] && '00' != retSelectFileSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retSelectFileSsseYH[0],retSelectFileSsseYH[1]);
	}

	var retReadRecordSsseYH = ReadRecordSsseYH('05','00','06');
	if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
	}
	klv = getKLV(retReadRecordSsseYH[2][1]);
	var EF05_05 = '';
	EF05_05 = klv[2];

	retReadRecordSsseYH = ReadRecordSsseYH('06','00','06');
	if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
	}
	klv = getKLV(retReadRecordSsseYH[2][1]);
	var EF05_06 = '';
	EF05_06 = klv[2];

	retSelectFileSsseYH = SelectFileSsseYH('02','02','EF06');
	if ('90' != retSelectFileSsseYH[0] && '00' != retSelectFileSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retSelectFileSsseYH[0],retSelectFileSsseYH[1]);
	}

	retReadRecordSsseYH = ReadRecordSsseYH('08','00','14');
	if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
	}
	klv = getKLV(retReadRecordSsseYH[2][1]);
	var EF06_08 = '';
	EF06_08 = klv[2];

	retReadRecordSsseYH = ReadRecordSsseYH('09','00','20');
	if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
	}
	klv = getKLV(retReadRecordSsseYH[2][1]);
	var EF06_09 = '';
	EF06_09 = klv[2];

	retReadRecordSsseYH = ReadRecordSsseYH('4E','00','16');
	if ('90' != retReadRecordSsseYH[0] && '00' != retReadRecordSsseYH[1]) {
   		ocxPowerOFFEX();//需退卡
   		return getRetMsg(retReadRecordSsseYH[0],retReadRecordSsseYH[1]);
	}
	klv = getKLV(retReadRecordSsseYH[2][1]);
	var EF06_4E = '';
	EF06_4E = klv[2];

	var ucEF06_08 = dsp2hex(EF06_08,36);
	var ucEF05_07 = dsp2hex(EF05_07,18);
	var ucEF06_09 = dsp2hex(EF06_09,60);
	var ucEF06_4E = dsp2hex(EF06_4E,40);
	var ucEF05_03 = dsp2hex(EF05_03,8);

	var Name = EF06_09 + EF06_4E;
	var UTFName = ascii2native(Name);
	var terminalMark = "000000000000";
	var terminalDeviceNo = '';

    var pout = EF05_01_CityCode + '|' + ucEF06_08 + '|' + ucEF05_07 + '|' + EF05_01 + '|' + UTFName + '|' + csAtr + '|' + ucEF05_03 + '|' + EF05_05 + '|' + EF05_06 + '|' + terminalMark + '|' + terminalDeviceNo + '|';
    ocxPowerOFFEX();
    return ['0',pout];
} 