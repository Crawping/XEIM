/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#ifndef XEIM_TYPE
#define	XEIM_TYPE

#include "xdef.h"
#include "winsock2.h"
class XUserInfo;

/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//*******************************************************************************************
// XEIM ͨѶ��Ϣ�ṹ
//*******************************************************************************************
class XMSG
{
public:
	int m_nMessage;		// ��Ϣ���Ͷ����� xdef.h ��
private:
	char *m_szData;		// ����������
	char *m_szBuffer;	// ��������
	int m_nDataLength;
public:
	BOOL IsMsgType();
	XMSG();
	XMSG(const char* szBuffer, int nBufferLength); // �����ݰ���ԭ�� XMSG

	char *GetData();		// XMSG ��װ������
	void SetData(const char* szData, int nDataLength); // װ������
	int GetDataLenght();	// XMSG ��װ�����ݳ���

	char *GetBuffer();		// XMSG �������ݰ�
	int GetBufferLength();	// XMSG �������ݳ���

	~XMSG();
};
//*******************************************************************************************
// End XEIM ͨѶ��Ϣ�ṹ
//*******************************************************************************************




/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//*******************************************************************************************
// XEIM �ʺ���ϸ��Ϣ ͨѶ��Ϣ�ṹ
//*******************************************************************************************
class XUserDetail
{
	char	m_szUID[32];
	char	m_szUNickName[32];
	char	m_szUPassword[32];
	char	m_szUGroup[32];
	int		m_nUStatus;

public:
	int		m_nDataID;
	BOOL IsDataType();
	XUserDetail();
	XUserDetail(const XUserDetail &xUserDetail);
	void GetUserInfo(XUserInfo &uinfo);
	void SetUID(const char *szUID);
	void SetUNickName(const char *szUNickName);
	void SetUPassword(const char *szUPassword);
	void SetUGroup(const char *szUGroup);
	void OnLine();
	void OffLine();

	char *GetUID();
	char *GetUNickName();
	char *GetUPassword();
	char *GetUGroup();
	int	GetUStatus();

	BOOL operator == (const XUserDetail &xUserDetail);
	BOOL operator == (const char *szUID);
	~XUserDetail();
};
//*******************************************************************************************
// End XEIM �ʺ���ϸ��Ϣ ͨѶ��Ϣ�ṹ
//*******************************************************************************************






/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//*******************************************************************************************
// XEIM �û���Ϣ
//*******************************************************************************************
class XUserInfo
{
	char	m_szUID[32];
	char	m_szUNickName[32];
	char	m_szUGroup[32];
	int		m_nUStatus;
public:
	BOOL UserHasMobile();
	void SetNumberAndSex(BOOL bNUM, BOOL bSex);
	void SetUID(const char *szUID);
	void SetUNickName(const char *szUNickName);
	void SetUGroup(const char *szUGroup); // �����û����ڵĲ�����
	void OnLine();
	void OffLine();

	char *GetUID();
	char *GetUNickName();
	char *GetUGroup();		// �õ��û����ڵĲ�����
	int	GetUStatus();

	BOOL operator == (const XUserInfo &xUserInfo);
	XUserInfo();
	~XUserInfo();
};
//*******************************************************************************************
// End XEIM �û���Ϣ
//*******************************************************************************************


/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//**********************************************************************************
// ������Ϣ XXMSG_ONLINE
//**********************************************************************************
class XMSG_ONLINE
{
public:
	XMSG_ONLINE();
	XMSG_ONLINE(const char *buf);

	// ����
	XMSG_ONLINE(const char *szid,
			const char *data,
			int len);

	// ���� DATA
	void SetData(const char *szid,
			const char *szData,
			int len);
	void SetUID(const char *szid);

	// ��ȡ Data
	char * GetData();
	// �������û�ID
	char * GetUID();

	// ��ȡ������Ϣ���ݰ�
	char *GetBuffer();
	// ��ȡ������Ϣ���ݰ�����
	int GetBufferLength();

	~XMSG_ONLINE();
private:
	// ���͵���Ϣ����
	int m_nDataLen;
	// ���͵���Ϣ
	char *buffer;
	// ��Ϣ������
	char	m_szUID[16];

};
//**********************************************************************************
// End ������Ϣ
//**********************************************************************************

/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//**********************************************************************************
// ������Ϣ XXMSG_OFFLINE
//**********************************************************************************
class XMSG_OFFLINE
{
public:
	XMSG_OFFLINE();
	XMSG_OFFLINE(const char *buf);

	// ����
	XMSG_OFFLINE(const char *szid,
			const char *data,
			int len);

	// ���� DATA
	void SetData(const char *szid,
			const char *szData,
			int len);
	void SetUID(const char *szid);

	// ��ȡ Data
	char * GetData();
	// ���������ȡ Data
	char * GetData(char *buf);
	// �������û�ID
	char * GetUID();
	// �ӻ�������ȡUID
	char * GetUID(char *buf);
	DWORD GetDataLength();
	// ��ȡ��Ϣ���ݵĳ���
	DWORD GetDataLength(char *buf);

	// ��ȡ������Ϣ���ݰ�
	char *GetBuffer();
	// ��ȡ������Ϣ���ݰ�����
	int GetBufferLength();

	~XMSG_OFFLINE();
private:
	// ���͵���Ϣ����
	int m_nDataLen;
	// ���͵���Ϣ
	char *buffer;
	// ��Ϣ������
	char	m_szUID[16];

};
//**********************************************************************************
// End ������Ϣ
//**********************************************************************************


/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//**********************************************************************************
// �����������ͻ��˵�������Ϣ XMSG_OFFLINEDATA
//**********************************************************************************
class XMSG_OFFLINEDATA
{
public:
	DWORD GetDataLen(const char *buf);
	// ����
	XMSG_OFFLINEDATA();
	XMSG_OFFLINEDATA(const char *buf);
	XMSG_OFFLINEDATA(const char *szid,const char *data,int len);


//	void SetData(const char *szid, const char *szdate, const char *buf, int len);
	void SetUID(const char *szid);
	void SetDate(const char *szdate);
	void SetData(const char *buf);


	char * GetData();// ��ȡ Data
	char * GetUID();// �������û�ID
	char * GetDate();// ������Ϣ�ķ�������
	char * GetBuffer();// ��ȡ������Ϣ���ݰ�
	int GetBufferLength();// ��ȡ������Ϣ���ݰ�����


	~XMSG_OFFLINEDATA();
private:

	int		m_nDataLen;		// ���͵���Ϣ����
	char	*buffer;		// ���͵���Ϣ
	char	m_szUID[50];	// ��Ϣ������
	char	m_szDate[28];	// ���߷�����Ϣ����
};
//**********************************************************************************
// End �����������ͻ��˵�������Ϣ XMSG_OFFLINEDATA
//**********************************************************************************

/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
typedef struct
{
	HWND hWnd;
	SOCKET sock;
}TDATA, *LPTDATA;

typedef struct {
	OVERLAPPED Overlapped;
	WSABUF		DataBuf;
	CHAR Buffer[DATA_BUFSIZE];
	DWORD send;
	DWORD DataSize;
	HWND	hWnd;
} PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

typedef struct {
	SOCKET Sock;
} PER_HEANDLE_DATA, *LPPER_HANDLE_DATA;


/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
//����ṹ���� 
typedef struct 
{
	u_long onoff;
	u_long keepalivetime;
	u_long keepaliveinterval;
}TCP_KEEPALIVE2;

class XMSG_SMS
{
public:
	DWORD m_dwIndex;
	XMSG_SMS();
	XMSG_SMS(const char *buf);
	~XMSG_SMS();
	void SetData(LPCTSTR szNUM, LPCTSTR buf, DWORD bufLen);
	char * GetData();
	char * GetNUM();
	char * GetBuffer();
	DWORD GetBufferLength();
private:

	char m_szNUM[12];
	DWORD m_dwBufLen;
	DWORD m_dwTotal;
	char *m_buf;
};

void GetProgramDirectory(char *buf);

#endif // XEIM_TYPE