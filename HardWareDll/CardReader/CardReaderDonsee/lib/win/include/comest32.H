#include "windows.h"
#ifndef COMEST32_H
#define COMEST32_H

#define ERROR_HEAD -11
#define ERROR_RECV -12
#define ERROR_XOR -13
#define ERROR_TAIL -14
#define ERROR_SEND -15
#define ERROR_PARAMENT -16
#define ERROR_HANDLE -17
#define ERROR_TIME -18
#define ERROR_LEN -19
#define OK_DLL	0

/*#define IFD_BadCommand -29	未找到该命令*/
#define IFD_TypeA_Find_Error -28	/*TYPE A寻卡错误*/
#define IFD_TypeA_MoreCard_Error -27	/*TYPE A检测到多张卡片*/
#define IFD_TypeA_Anticoll_Error -26	/*TYPE A防碰撞错误*/
#define IFD_TypeA_Select_Error -25	/*TYPE A选卡错误*/
#define IFD_TypeA_RATS_Error -24	/*TYPE A RATS错误*/
#define IFD_M1_Auth_Error -23	/*Mifare one Auth错误*/
#define IFD_TypeB_Find_Error -22	/*TYPE B寻卡错误*/
#define IFD_TypeB_attrib_Error -21	/*TYPE B attrib错误*/
#define IFD_SendAgain -40           /*如果返回此错误，需重发数据*/

/*状态码*/
#define IFD_OK	0					 /*执行成功*/
#define IFD_ICC_TypeError	-1		 /*卡片类型不对*/
#define IFD_ICC_NoExist	-2			 /*无卡*/
#define IFD_ICC_NoPower	-3			 /*有卡未上电*/
#define IFD_ICC_NoResponse	-4	     /*卡片无应答*/
#define IFD_ConnectError	-11	     /*读卡器连接错*/
#define IFD_UnConnected	-12	         /*未建立连接(没有执行打开设备函数)*/
#define IFD_BadCommand	-13	         /*(动态库)不支持该命令*/
#define IFD_ParameterError	-14	     /*(发给动态库的)命令参数错*/
#define IFD_CheckSumError	-15	     /*信息校验和出错*/

#define JR_OK 0     /*执行成功*/

#define IC_UnConnect -1001 /*设备通讯超时*/
#define IC_CardNoExist -1002 /*无卡*/
#define IC_CardLock -2001	/*卡片已锁定，请解锁*/
#define IC_CardInit -2002	/*卡片初始化失败*/
#define IC_CardGetCDOL1 -2003	/*卡片获取CDOL1失败*/
#define IC_CardARQC  -2004	/*卡片获取ARQC失败*/
#define IC_CardGetCDOL2 -2005	/*读取卡片CDOL2失败*/
#define IC_CardTC -2006	  /*卡片生成TC失败*/
#define IC_CardAAC -2007	/*卡片生成AAC失败*/

#define IC_CardIsAuthen -2010	/*卡片发卡行认证失败*/
#define IC_CardScript -2008	  /*卡片执行脚本失败*/
#define IC_CardList -2009	/*获取交易明细失败*/





/*############设备操作函数#################*/
#ifdef __cplusplus
extern "C" {
#endif

long WINAPI  EU_Reader_Open(int iPort,int t_baud); 
long WINAPI  EU_Reader_Close(long ReaderHandle);
long WINAPI  EU_PosBeep(long ReaderHandle, unsigned char time);/*蜂鸣*/
long WINAPI  EU_Reader_Libinfo(char* info,char * DllVersion);//获取动态库信息


long WINAPI EU_Reader_GetDeviceCSN(long ReaderHandle,unsigned char *data);//获取序列号
long WINAPI  EU_Reader_GetDeviceVersion(long ReaderHandle, unsigned char *VDate );/*获取版本信息*/
long WINAPI EU_Reader_GetKeybordVersion(long ReaderHandle, unsigned char *VDate);  //获取键盘版本号

/*############################# CPU卡操作 ###########################*/
long WINAPI  EU_Reader_pre_PowerOn(long ReaderHandle,unsigned char EU_slot_no,unsigned char* response);/*上电 冷 返回数据长度*/
long WINAPI  EU_Reader_hot_PowerOn(long ReaderHandle,unsigned char EU_slot_no,unsigned char* response);/*上电 热 返回数据长度*/
long WINAPI  EU_Reader_GetStatus(long ReaderHandle,unsigned char EU_slot_no);/*获取卡座状态*/
long WINAPI  EU_Reader_PowerOn(long ReaderHandle,unsigned char EU_slot_no,unsigned char* response);/*上电  返回数据长度 冷+热*/
long WINAPI  EU_Reader_PowerOff(long ReaderHandle,unsigned char EU_slot_no);/*下电*/
long WINAPI  EU_Reader_Application(long ReaderHandle,unsigned char EU_slot_no,long lenthofcommandapdu,unsigned char* commandapdu,unsigned char* responseapdu);  /*执行apdu命令  返回数据长度*/

long WINAPI EU_Reader_Zpre_PowerOn(long ReaderHandle,unsigned char EU_Slot_No,unsigned char* Response);//住建卡小卡


/*############ M1卡操作 #########################*/
long WINAPI PEU_Reader_Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord);/*认证密钥M1 带密钥参数*/

long WINAPI PEU_Reader_Authentication(long ReaderHandle,unsigned char Mode, unsigned char SecNr);/*认证密钥 M1 密钥keya mode=0 密钥keyb mode=1*/

long WINAPI PEU_Reader_Readval(long ReaderHandle,unsigned char Addr,unsigned long *value);	/*读值*/

long WINAPI PEU_Reader_Initval(long ReaderHandle,unsigned char Addr,unsigned long value);/*初始化值*/

long WINAPI PEU_Reader_Increment(long ReaderHandle,unsigned char Addr,unsigned long value);	/*增值*/

long WINAPI PEU_Reader_Decrement(long ReaderHandle,unsigned char Addr,unsigned long value);/*减值*/

long WINAPI PEU_Reader_Read(long ReaderHandle,unsigned char Addr,unsigned char *Data);	/*读取卡片M1*/

long WINAPI PEU_Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data);/*写入数据M1*/

long WINAPI PEU_Reader_WriteHEX(long ReaderHandle,unsigned char Addr,unsigned char *Data);/*写入数据M1*/

long WINAPI PEU_Reader_LoadKey(long ReaderHandle,unsigned char Mode,unsigned char SecNr,unsigned char *Key);/*装载密钥*/

long WINAPI PEU_Reader_GetUID(long ReaderHandle ,unsigned char * Data) ;//获取M1卡UID

/*############ 非接 CPU 卡操作函数 #################*/
 long WINAPI PEU_Reader_SetTypeA(long ReaderHandle);/*设置读typeA*/
 
 long WINAPI PEU_Reader_SetTypeB(long ReaderHandle);/*设置读typeA*/
 
 long WINAPI PEU_Reader_Select(long ReaderHandle,unsigned char cardtype);/*选择卡片，41为typea,M1 42为typeb,TypeB卡片需先上电后选卡*/
 
 long WINAPI PEU_Reader_Request(long ReaderHandle);/*typea M1请求卡片*/
 
 long WINAPI PEU_Reader_anticoll(long ReaderHandle,unsigned char *uid);/*防碰撞 typea M1卡片*/

long WINAPI PEU_Reader_PowerOnTypeA(long ReaderHandle,unsigned char* response);/*上电 返回数据长度 失败小于0*/

long WINAPI PEU_Reader_PowerOnTypeB(long ReaderHandle,unsigned char* response);/*上电 返回数据长度 失败小于0*/

long WINAPI PEU_Reader_Application(long ReaderHandle,long lenthofcommandapdu,unsigned char* commandapdu,unsigned char* responseapdu);  /*type a/b执行apdu命令 返回数据长度 失败小于0*/

/*############################ 4428卡操作 ###############################*/

long WINAPI EU_Reader_ChangeSlot(long ReaderHandle,unsigned char EU_slot_no);/*切换大卡2大卡2副卡座*/

long WINAPI EU_Reader_4428_Change(long ReaderHandle,unsigned char *newkey);/*修改密钥*/

long WINAPI EU_Reader_4428_ReadProtect(long ReaderHandle,long offset,int long,unsigned char *data); /*4428卡读保护数据*/

long WINAPI EU_Reader_4428_PowerOff(long ReaderHandle); /*4428卡下电*/

long WINAPI EU_Reader_4428_PowerOn(long ReaderHandle,unsigned char *data); /*4428卡上电*/

long WINAPI EU_Reader_4428_Read(long ReaderHandle,long offset,int len,unsigned char *data); /*4428卡读数据*/

long WINAPI EU_Reader_4428_ReadCount(long ReaderHandle); /*读取4428卡密钥剩余认证次数*/

long WINAPI EU_Reader_4428_Verify(long ReaderHandle,unsigned char *key); /*4428卡认证密钥*/

long WINAPI EU_Reader_4428_Write(long ReaderHandle,long offset,long len,unsigned char *data); /*4428卡写数据 */

long WINAPI EU_Reader_4428_WriteProtect(long ReaderHandle,long offset,long len,unsigned char *data); /*4428卡写保护数据 */

/*############################ 4442卡操作 ###############################*/
long WINAPI EU_Reader_4442_PowerOn(long ReaderHandle,unsigned char *data); //4442卡上电

long WINAPI EU_Reader_4442_PowerOff(long ReaderHandle); //4442卡下电

long WINAPI EU_Reader_4442_Read(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡读数据

long WINAPI EU_Reader_4442_Write(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡写数据 

long WINAPI EU_Reader_4442_Verify(long ReaderHandle, unsigned char *key); //4442卡认证密钥

long WINAPI EU_Reader_4442_Change(long ReaderHandle,unsigned char *newkey); //4442卡修改密钥

long WINAPI EU_Reader_4442_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡读保护数据

long WINAPI EU_Reader_4442_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡写保护数据

long WINAPI EU_Reader_4442_ReadCount(long ReaderHandle); //读取4442卡密钥剩余认证次数 返回次数0~3次

/*############################ 磁条卡操作 ###############################*/
long WINAPI Rcard(long ReaderHandle,unsigned char ctime,int track,unsigned char *rlen,unsigned char *getdata);//读磁条卡

/*############################ 身份证操作 ###############################*/

long WINAPI PEU_Reader_ID_Request(long ReaderHandle);//身份证寻卡

long WINAPI PEU_Reader_ID_Select(long ReaderHandle);//身份证选卡

long WINAPI PEU_Reader_ReadIDCard(long ReaderHandle, char * pErrMsg);


int WINAPI GetName(char* pName);
int WINAPI GetSex(char* pSex);
int WINAPI GetNation(char* pNation);
int WINAPI GetBirth(char* pBirth);
int WINAPI GetAddress(char* pAddress);
int WINAPI GetCertNo(char* pCertNo);
int WINAPI GetDepartemt(char* pDepartemt);
int WINAPI GetEffectDate(char* pEffectDate);
int WINAPI GetExpireDate(char* pExpireDate);

int WINAPI GetTXZHM(char* pTXZHM);
int WINAPI GetTXZQFCS(char* pTXZQFCS);

int WINAPI GetB64FileData(char* pB64FileData);
int WINAPI GetBmpFileData(char* pBmpFileData);
int WINAPI GetBmpFile(char* pBmpfilepath);

int	WINAPI IsFingerExist();
int	WINAPI GetFingerprint(unsigned char* fpInfo);

int	WINAPI GetCardType();
int WINAPI GetEnName(char* pEnName);
int WINAPI GetNationalityCode(char* pNationalityCode);
int WINAPI GetCardVersion(char* pCardVersion);
int WINAPI GetAuthorCode(char* pAuthorCode);
int WINAPI GetCardTypeFlag(char* pCardTypeFlag);

long WINAPI PEU_Reader_ID_ReadUID(long ReaderHandle, char *UID);//获取身份证UID

long WINAPI PEU_Reader_ID_Read(long ReaderHandle,unsigned char *data); /*读取身份证 */

long WINAPI PEU_Reader_ID_Read_Fp(long ReaderHandle,unsigned char *data);/*读取身份证 添加读取指纹信息*/

long WINAPI PEU_Reader_ID_Fgprint(long ReaderHandle,unsigned char *data);//读取身份证指纹信息


//如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
long WINAPI PEU_Reader_ReadIDMsg(long ReaderHandle, const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg);

//添加读取指纹信息 如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
long WINAPI PEU_Reader_ReadIDMsg_Fp(long ReaderHandle,const char* pBmpFile, char *pFpData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg);

long WINAPI PEU_Reader_ReadIDInfo(long ReaderHandle, char* pBmpFileData,char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire, char * pErrMsg);
long WINAPI PEU_Reader_ReadIDInfo_Fp(long ReaderHandle, char* pBmpFileData, unsigned char *pFing,char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire, char * pErrMsg);

long WINAPI PEU_Reader_ReadIDPhotoInfo(long ReaderHandle, char* pBmpFileData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData,  char *pExpire,char * pErrMsg);
long WINAPI PEU_Reader_ReadIDPhotoInfo_Fp(long ReaderHandle, char* pBmpFileData, unsigned char* pFpData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData,  char *pExpire,char * pErrMsg);

long WINAPI PEU_Reader_ID_ReadWGR(long ReaderHandle, const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg);
//////////////////

long WINAPI PEU_Reader_SICARD(long ReaderHandle, char* SBKH, char *XM, char *XB, char *MZ, char *CSRQ, char *SHBZHM, char *FKRQ, char *KYXQ,char* ErrMsg);

long WINAPI StrToHex(unsigned char *strIn, int inLen, unsigned char *strOut);//将字符命令流转为16进制流

long WINAPI HexToStr(unsigned char *strIn,int inLen,unsigned char *strOut);//将16进制命令流转为字符流

long WINAPI PEU_Reader_GetVN(long ReaderHandle ,unsigned char * Data) ;//获取版本信息

/*############################ 键盘操作 ###############################*/

long WINAPI EU_DispInfo(long ReaderHandle,unsigned char row,unsigned char list,char *data); //显示信息

long WINAPI EU_DispSound(long ReaderHandle,unsigned char type,unsigned char nMode); //声音提示信息 type(1~14) nMode==0内置键盘语音，nMode==1外置键盘语音
/*
	1、请插卡 2、请刷卡 3、读卡错误 4、请输入密码  5、密码错误  6、操作成功 7、操作超时 8、操作失败 9、请取回卡 10、请重新输入密码 11、请再次输入密码 12、请输入新密码 13、请输入旧密码 14、请确认新密码
*/


long WINAPI EU_GetInputPass(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char stop,unsigned char * cpass);//获取密码，带超时 start==0用内置键盘，start==1用外置键盘

//long WINAPI EU_GetInputPassID(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char stop,unsigned char * cardID,unsigned char * cpass);//获取密码，带超时,带ID

long WINAPI EU_PassCheck(long ReaderHandle,unsigned char *rlen,unsigned char * cpass);

long WINAPI EU_PassGet(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cpass);
//long WINAPI EU_PassGet(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cpass);


/*############ 15693 卡操作函数#################*/

long WINAPI PEU_Reader_Inventory(long ReaderHandle,unsigned char* GetData);//此命令通过防冲突用于得到读卡区域内所有卡片的序列号

long WINAPI PEU_Reader_15693_Read(long ReaderHandle,unsigned char blk_add,unsigned char* Response_APDU);//用来读取1个扇区的值

long WINAPI PEU_Reader_15693_Write(long ReaderHandle,unsigned char blk_add,unsigned char* data,
									unsigned char* Response_APDU);//对一个块进行写操作（每次只能写一个块）

long WINAPI PEU_Reader_API(long ReaderHandle,unsigned char* data,unsigned char* Response_APDU);//Data[0]	0代表写API,1代表锁API

long WINAPI PEU_Reader_DSFID(long ReaderHandle,unsigned char* data,unsigned char* Response_APDU);//Data[0]	0代表写DSFID,1代表锁DSFID

long WINAPI PEU_Reader_LockDataBlock(long ReaderHandle,unsigned char blk_add,unsigned char* Response_APDU);//用于锁定块内容。注意：此过程不可逆（不能解锁）块锁定后内容不能在修改。

long WINAPI PEU_Reader_SystemInfor(long ReaderHandle,unsigned char *Response_APDU);//用于得到卡的详细信息


//############################# AT88SC 1604 Card ##############################################################

long WINAPI EU_Reader_1604_PowerOn(long ReaderHandle,unsigned char *data);    //1604卡上电
long WINAPI EU_Reader_1604_PowerOff(long ReaderHandle);					   //1604卡下电

long WINAPI EU_Reader_1604_Read(long ReaderHandle,int offset,int len,unsigned char *data);  //1604卡读数据
long WINAPI EU_Reader_1604_Write(long ReaderHandle,int offset,int len,unsigned char *data); //1604卡写数据
long WINAPI EU_Reader_1604_BrushCard(long ReaderHandle,int offset,int len);                 //1604擦卡

long WINAPI EU_Reader_1604_Verify(long ReaderHandle,int zone,unsigned char *key);           //1604密码认证 zone=0为主密码 1为1区密码 2为2区密码 3为3区密码
long WINAPI EU_Reader_1604_VerifyBrush(long ReaderHandle,int zone,unsigned char *key);      //1604擦卡密码认证
long WINAPI EU_Reader_1604_Change(long ReaderHandle,int zone,unsigned char *newkey);        //1604修改密码
long WINAPI EU_Reader_1604_ChangeBrushKey(long ReaderHandle,int zone,unsigned char *databuff);//修改擦卡密码 熔断后无效

long WINAPI EU_Reader_1604_ClearRead(long ReaderHandle,int zone);        //应用区读属性清0     　　必须用户密码核对正确后方可读卡
long WINAPI EU_Reader_1604_ClearWrite(long ReaderHandle,int zone);       //应用区写属性清0       个人化后 任何情况下都不可写

long WINAPI EU_Reader_1604_Imitate(long ReaderHandle,int mode);   //模拟熔断  mode==1为模拟  mode==0为取消模拟
long WINAPI EU_Reader_1604_PassCount(long ReaderHandle,int zone); //密码错误计数器
long WINAPI EU_Reader_1604_BrushPassCount(long ReaderHandle,int zone);     //擦卡密码错误计时器  共8次 
long WINAPI EU_Reader_1604_Personal(long ReaderHandle);           //熔断操作  个人化操作  调用后无法取消

//读取功能表
long WINAPI EU_Reader_ContatctInfo(long ReaderHandle,char *VDate); 
long WINAPI EU_Reader_NoContatctInfo(long ReaderHandle,char *VDate);

long WINAPI EU_Reader_SetBaud(long ReaderHandle,unsigned char* Baud);

long WINAPI EU_Reader_UCCardType(long ReaderHandle);//获取非接卡类型

long WINAPI PEU_Reader_CardInfo(long ReaderHandle,
	unsigned char * ICCardSN , 
	unsigned char * ICCardIndate,
	unsigned char *MsgInfo,
	unsigned char * MsgInfoLen,
	int t_IntMode);
unsigned char*	WINAPI	str2hex(unsigned char* Src, int len, unsigned char* Des);
char*			WINAPI	hex2str(unsigned char* Src, int len, char* Des);


#ifdef __cplusplus
}
#endif
#endif

