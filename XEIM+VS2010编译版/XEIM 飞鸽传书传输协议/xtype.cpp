/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#include "StdAfx.h"
#include "xtype.h"
#include "xdef.h"

//*******************************************************************************************
// XEIM ͨѶ��Ϣ�ṹ
//*******************************************************************************************
XMSG::XMSG()
{
	m_nDataLength = 0;
	m_szData = NULL;
	m_szBuffer = NULL;
	m_nMessage = XEIMMESSAGE;
}

// �����ݰ���ԭ�� XMSG
XMSG::XMSG(const char* szBuffer, int nBufferLength)
{
	m_nDataLength = 0;
	m_szData = NULL;
	m_szBuffer = NULL;
	m_nMessage = XEIMMESSAGE;

	int nIdx = 0;
	// ȷ���û���������Ϣ������
	try
	{
		memcpy((char*)&m_nMessage, szBuffer, sizeof(m_nMessage));
		if (XEIMMESSAGE == (m_nMessage & XEIMMESSAGE))
		{
		//	AfxMessageBox("This data is not a XEIM XMSG data. XMSG::XMSG");
		//	return;
			nIdx = sizeof(m_nMessage);
			memcpy((char*)&m_nDataLength, szBuffer+nIdx, sizeof(m_nDataLength));
			nIdx += sizeof(m_nDataLength);
			m_szData = new char[m_nDataLength];
			memcpy(m_szData, szBuffer+nIdx, m_nDataLength);
		}
	}
	catch(...)
	{
	//	AfxMessageBox("Error in the XMSG.");
		printf("");
	}
}

// XMSG ��װ������
char *XMSG::GetData()
{
	return m_szData;
}

// װ������
void XMSG::SetData(const char* szData, int nDataLength)
{
	m_nDataLength = nDataLength;
	m_szData = new char[nDataLength];
	memcpy(m_szData, szData, nDataLength);
}

// XMSG ��װ�����ݳ���
int XMSG::GetDataLenght()
{
	return m_nDataLength;
}

// XMSG �������ݰ�
char *XMSG::GetBuffer()
{
	int nIdx = 0;
	m_szBuffer = new char[GetBufferLength()];
	memcpy(m_szBuffer, (char*)&m_nMessage, sizeof(m_nMessage));
	nIdx = sizeof(m_nMessage);
	memcpy(m_szBuffer+nIdx, (char*)&m_nDataLength, sizeof(m_nDataLength));
	nIdx += sizeof(m_nDataLength);
	memcpy(m_szBuffer+nIdx, m_szData, m_nDataLength);

	return m_szBuffer;
}

// XMSG �������ݳ���
int XMSG::GetBufferLength()
{
	int nLen = sizeof(m_nMessage);
	nLen += sizeof(m_nDataLength);
	nLen += m_nDataLength;

	return nLen;
}

XMSG::~XMSG()
{
	if (m_szData)
	{
		delete m_szData;
		m_szData = NULL;
	}
	if (m_szBuffer)
	{
		delete m_szBuffer;
		m_szData = NULL;
	}
}
//*******************************************************************************************
// End XEIM ͨѶ��Ϣ�ṹ
//*******************************************************************************************





//*******************************************************************************************
// XEIM �ʺ���ϸ��Ϣ ͨѶ��Ϣ�ṹ
//*******************************************************************************************
XUserDetail::XUserDetail()
{
	// ����Ψһ��ʶ
	m_nDataID = 0x111cfff;

	ZeroMemory((char*)m_szUID, sizeof(m_szUID));
	ZeroMemory((char*)m_szUNickName, sizeof(m_szUNickName));
	ZeroMemory((char*)m_szUPassword, sizeof(m_szUPassword));
	ZeroMemory((char*)m_szUGroup, sizeof(m_szUGroup));
	m_nUStatus = STATUS_OFFLINE;
}

XUserDetail::XUserDetail(const XUserDetail &xUserDetail)
{
	// ����Ψһ��ʶ
	m_nDataID = xUserDetail.m_nDataID;

	strcpy(m_szUPassword, xUserDetail.m_szUPassword);
	strcpy(m_szUID, xUserDetail.m_szUID);
	strcpy(m_szUNickName, xUserDetail.m_szUNickName);
	strcpy(m_szUGroup, xUserDetail.m_szUGroup);

	m_nUStatus = xUserDetail.m_nUStatus;
}

BOOL XUserDetail::IsDataType()
{
	// ����Ψһ��ʾ
	return 	m_nDataID == 0x111cfff;
}

void XUserDetail::SetUID(const char *szUID)
{
	strcpy(m_szUID, szUID);
}

// �û��ǳ�
void XUserDetail::SetUNickName(const char *szUNickName)
{
	strcpy(m_szUNickName, szUNickName);
}

// �û�����
void XUserDetail::SetUPassword(const char *szUPassword)
{
	strcpy(m_szUPassword, szUPassword);
}

// �û�����Ϣ
void XUserDetail::SetUGroup(const char *szUGroup)
{
	strcpy(m_szUGroup, szUGroup);
}

void XUserDetail::OnLine()
{
	m_nUStatus = STATUS_ONLINE;
}

void XUserDetail::OffLine()
{
	m_nUStatus = STATUS_OFFLINE;
}

// �����û�ID
char *XUserDetail::GetUID()
{
	return (char*)m_szUID;
}

// �����û��ǳ�
char *XUserDetail::GetUNickName()
{
	return (char*)m_szUNickName;
}

// �����û�����
char *XUserDetail::GetUPassword()
{
	return (char*)m_szUPassword;
}

// �����û�����
char *XUserDetail::GetUGroup()
{
	return (char*)m_szUGroup;
}

// �����û�״̬
int	XUserDetail::GetUStatus()
{
	return m_nUStatus;
}

// �� XUserDetail ����ȡ XUserInfo
void XUserDetail::GetUserInfo(XUserInfo &uinfo)
{
	uinfo.SetUID(m_szUID);
	uinfo.SetUNickName(m_szUNickName);
	uinfo.SetUGroup(m_szUGroup);

	if (m_nDataID == 10)
		uinfo.SetNumberAndSex(TRUE, FALSE);
	else
		uinfo.SetNumberAndSex(FALSE, FALSE);

	if (m_nUStatus == STATUS_ONLINE)
		uinfo.OnLine();
	else
		uinfo.OffLine();

}

BOOL XUserDetail::operator == (const XUserDetail &xUserDetail)
{
	int ret = strcmp(strlwr(m_szUID), strlwr((char*)xUserDetail.m_szUID));
	if (ret != 0)
		return FALSE;
	ret = strcmp(m_szUPassword, xUserDetail.m_szUPassword);
	if (ret != 0)
		return FALSE;

	return TRUE;
}

BOOL XUserDetail::operator == (const char *szUID)
{
	int ret = strcmp(strlwr((char*)m_szUID), strlwr((char*)szUID));
	if (ret != 0)
		return FALSE;

	return TRUE;
}

XUserDetail::~XUserDetail()
{
}
//*******************************************************************************************
// End XEIM �ʺ���ϸ��Ϣ ͨѶ��Ϣ�ṹ
//*******************************************************************************************





//*******************************************************************************************
// XEIM �û���Ϣ
//*******************************************************************************************
void XUserInfo::SetUID(const char *szUID)
{
	strcpy(m_szUID, strlwr((LPSTR)szUID));
}

void XUserInfo::SetUNickName(const char *szUNickName)
{
	strcpy(m_szUNickName, szUNickName);
}
// �û�����Ϣ
void XUserInfo::SetUGroup(const char *szUGroup)
{
	strcpy(m_szUGroup, szUGroup);
}

void XUserInfo::OnLine()
{
	m_nUStatus = STATUS_ONLINE;
}

void XUserInfo::OffLine()
{
	m_nUStatus = STATUS_OFFLINE;
}

char *XUserInfo::GetUID()
{
	return (char*)m_szUID;
}

char *XUserInfo::GetUNickName()
{
	return (char*)m_szUNickName;
}

int	XUserInfo::GetUStatus()
{
	return m_nUStatus;
}

// �����û�����
char *XUserInfo::GetUGroup()
{
	return (char*)m_szUGroup;
}

XUserInfo::XUserInfo()
{
	ZeroMemory((char*)m_szUID, sizeof(m_szUID));
	ZeroMemory((char*)m_szUNickName, sizeof(m_szUNickName));
	m_nUStatus = STATUS_OFFLINE;
}

BOOL XUserInfo::operator == (const XUserInfo &xUserInfo)
{
	int ret = strcmp(strlwr((char*)m_szUID), strlwr((char*)xUserInfo.m_szUID));
	if (ret != 0)
		return FALSE;

	return TRUE;
}

XUserInfo::~XUserInfo()
{
}
//*******************************************************************************************
// End XEIM �û���Ϣ
//*******************************************************************************************



//**********************************************************************************
// ������Ϣ XXMSG_ONLINE
//**********************************************************************************
XMSG_ONLINE::XMSG_ONLINE()
{
	m_nDataLen = 0;
	buffer = NULL;
	memset((char*)m_szUID, 0, sizeof(m_szUID));
}
XMSG_ONLINE::XMSG_ONLINE(const char *buf)
{
	m_nDataLen = 0;
	buffer = NULL;
	memset((char*)m_szUID, 0, sizeof(m_szUID));

	int i=0;
	memcpy(m_szUID, buf, sizeof(m_szUID));
	i = sizeof(m_szUID);

	memcpy((char*)&m_nDataLen, buf+i, sizeof(m_nDataLen));
	i += sizeof(m_nDataLen);

	buffer = new char[m_nDataLen];
	memcpy(buffer, buf+i, m_nDataLen);
}

XMSG_ONLINE::XMSG_ONLINE(const char *szid, const char *data, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, data, len);
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	memcpy(m_szUID, szid, sizeof(m_szUID));
}

// ���� DATA
void XMSG_ONLINE::SetData(const char *szid, const char *szData, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, szData, len);
	strcpy(m_szUID, szid);
}

void XMSG_ONLINE::SetUID(const char *szid)
{
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	strcpy(m_szUID, szid);
}

// ��ȡ Data
char * XMSG_ONLINE::GetData()
{
	return buffer;
}

// �������û�ID
char * XMSG_ONLINE::GetUID()
{
	return (char*)m_szUID;
}

// ��ȡ������Ϣ���ݰ�
char *XMSG_ONLINE::GetBuffer()
{
	char *temp;
	int len = GetBufferLength();
	temp = new char[len];

	// �������
	memcpy(temp, m_szUID, sizeof(m_szUID));		// ID
	int i = sizeof(m_szUID);
	memcpy(temp+i, (char*)&m_nDataLen, sizeof(m_nDataLen));	// Data Length
	i += sizeof(m_nDataLen);
	memcpy(temp+i, buffer, m_nDataLen);					// Data

	delete buffer;
	buffer = temp;

	return temp;
}

// ��ȡ������Ϣ���ݰ�����
int XMSG_ONLINE::GetBufferLength()
{
	int total = sizeof(m_szUID)	// ID
			+ sizeof(m_nDataLen)	// Data Length
			+ m_nDataLen;			// Data

	return total;
}

XMSG_ONLINE::~XMSG_ONLINE()
{
	if (buffer)
	{
		delete buffer;
		buffer = NULL;
	}
}


//**********************************************************************************
// End ������Ϣ XXMSG_ONLINE
//**********************************************************************************




//**********************************************************************************
// ������Ϣ XMSG_OFFLINE
//**********************************************************************************
XMSG_OFFLINE::XMSG_OFFLINE()
{
	m_nDataLen = 0;
	buffer = NULL;
	memset((char*)m_szUID, 0, sizeof(m_szUID));
}

XMSG_OFFLINE::XMSG_OFFLINE(const char *buf)
{
	try
	{
		m_nDataLen = 0;
		buffer = NULL;
		memset((char*)m_szUID, 0, sizeof(m_szUID));

		int i=0;
		memcpy(m_szUID, buf, sizeof(m_szUID));
		i = sizeof(m_szUID);

		memcpy((char*)&m_nDataLen, buf+i, sizeof(m_nDataLen));
		i += sizeof(m_nDataLen);

		buffer = new char[m_nDataLen];
		memcpy(buffer, buf+i, m_nDataLen);
	}
	catch(...)
	{
		MessageBox(NULL, "XMSG_OFFLINE::XMSG_OFFLINE(const char *buf)", "catch(...)", MB_OK);
	}
}

XMSG_OFFLINE::XMSG_OFFLINE(const char *szid, const char *data, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, data, len);
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	strcpy(m_szUID, szid);
}

// ���� DATA
void XMSG_OFFLINE::SetData(const char *szid, const char *szData, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, szData, len);
	strcpy(m_szUID, szid);
}

void XMSG_OFFLINE::SetUID(const char *szid)
{
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	strcpy(m_szUID, szid);
}

// ��ȡ Data
char * XMSG_OFFLINE::GetData()
{
	return buffer;
}

// ���������ȡ Data
char * XMSG_OFFLINE::GetData(char *buf)
{
	int len = GetDataLength(buf);
	int offset = sizeof(m_szUID) + sizeof(m_nDataLen);
	buffer = buf+offset;
	return buffer;
}

// �������û�ID
char * XMSG_OFFLINE::GetUID()
{
	return (char*)m_szUID;
}

// �ӻ�������ȡUID
char * XMSG_OFFLINE::GetUID(char *buf)
{
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	memcpy(m_szUID, buf, sizeof(m_szUID));

	return (char*)m_szUID;
}

DWORD XMSG_OFFLINE::GetDataLength()
{
	return m_nDataLen;
}

// ��ȡ��Ϣ���ݵĳ���
DWORD XMSG_OFFLINE::GetDataLength(char *buf)
{
	try
	{
		memcpy((char*)&m_nDataLen, buf+sizeof(m_szUID), sizeof(m_nDataLen));
	}
	catch(...)
	{
		MessageBox(NULL, "XMSG_OFFLINE::GetDataLength", "catch(...)", MB_OK);
	}

	return m_nDataLen;
}

// ��ȡ������Ϣ���ݰ�
char *XMSG_OFFLINE::GetBuffer()
{
	char *temp;
	int len = GetBufferLength();
	temp = new char[len];

	// �������
	memcpy(temp, m_szUID, sizeof(m_szUID));		// ID
	int i = sizeof(m_szUID);
	memcpy(temp+i, (char*)&m_nDataLen, sizeof(m_nDataLen));	// Data Length
	i += sizeof(m_nDataLen);
	memcpy(temp+i, buffer, m_nDataLen);					// Data

	delete buffer;
	buffer = temp;

	return temp;
}

// ��ȡ������Ϣ���ݰ�����
int XMSG_OFFLINE::GetBufferLength()
{
	int total = sizeof(m_szUID)	// ID
			+ sizeof(m_nDataLen)	// Data Length
			+ m_nDataLen;			// Data

	return total;
}

XMSG_OFFLINE::~XMSG_OFFLINE()
{
	if (buffer)
	{
		delete buffer;
		buffer = NULL;
	}
}

BOOL XMSG::IsMsgType()
{
	return (XEIMMESSAGE == (m_nMessage & XEIMMESSAGE));
}

//**********************************************************************************
// End ������Ϣ XMSG_OFFLINE
//**********************************************************************************




//**********************************************************************************
// ������Ϣ XMSG_OFFLINEDATA
//**********************************************************************************
XMSG_OFFLINEDATA::XMSG_OFFLINEDATA()
{
	m_nDataLen = 0;
	buffer = NULL;
	memset((char*)m_szUID, 0, sizeof(m_szUID));
}

XMSG_OFFLINEDATA::XMSG_OFFLINEDATA(const char *buf)
{
	m_nDataLen = 0;
	buffer = NULL;
	memset((char*)m_szDate, 0, sizeof(m_szDate));
	memset((char*)m_szUID, 0, sizeof(m_szUID));

	int i=0;
	memcpy(m_szUID, buf, sizeof(m_szUID));
	i = sizeof(m_szUID);

	memcpy(m_szDate, buf+i, sizeof(m_szDate));
	i += sizeof(m_szDate);

	memcpy((char*)&m_nDataLen, buf+i, sizeof(m_nDataLen));
	i += sizeof(m_nDataLen);

	buffer = new char[m_nDataLen];
	ZeroMemory(buffer, m_nDataLen);

	memcpy(buffer, buf+i, m_nDataLen);
}

XMSG_OFFLINEDATA::XMSG_OFFLINEDATA(const char *szid, const char *data, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, data, len);
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	memcpy(m_szUID, szid, sizeof(m_szUID));
}

// ���� DATA
/*void XMSG_OFFLINEDATA::SetData(const char *szid, const char *szdate, const char *buf, int len)
{
	m_nDataLen = len;
	buffer = new char[len];
	memcpy(buffer, buf, len);
	strcpy(m_szUID, szid);
	strcpy(m_szDate, szdate);
}*/

void XMSG_OFFLINEDATA::SetData(const char *buf)
{
	m_nDataLen = strlen(buf)+1;
	buffer = new char[m_nDataLen];
	memcpy(buffer, buf, m_nDataLen);
}

void XMSG_OFFLINEDATA::SetUID(const char *szid)
{
	memset((char*)m_szUID, 0, sizeof(m_szUID));
	memcpy(m_szUID, szid, sizeof(m_szUID));
}

void XMSG_OFFLINEDATA::SetDate(const char *szdate)
{
	memset((char*)m_szDate, 0, sizeof(m_szDate));
	strcpy(m_szDate, szdate);
}

// ��ȡ Data
char * XMSG_OFFLINEDATA::GetData()
{
	return buffer;
}

// �������û�ID
char * XMSG_OFFLINEDATA::GetUID()
{
	return (char*)m_szUID;
}

// ������Ϣ�ķ�������
char * XMSG_OFFLINEDATA::GetDate()
{
	return (char*)m_szDate;
}

// ��ȡ������Ϣ���ݰ�
char *XMSG_OFFLINEDATA::GetBuffer()
{
	int len = GetBufferLength();
	char *temp;
	temp = new char[len];

	// �������
	memcpy(temp, m_szUID, sizeof(m_szUID));		// ID
	int i = sizeof(m_szUID);

	memcpy(temp+i, m_szDate, sizeof(m_szDate));	// Date ����
	i += sizeof(m_szDate);

	memcpy(temp+i, (char*)&m_nDataLen, sizeof(m_nDataLen));	// Data Length
	i += sizeof(m_nDataLen);

	memcpy(temp+i, buffer, m_nDataLen);					// Data

	delete buffer;
	buffer = temp;

	return buffer;
}

// ��ȡ������Ϣ���ݰ�����
int XMSG_OFFLINEDATA::GetBufferLength()
{
	int total = sizeof(m_szUID)		// ID
			+ sizeof(m_szDate)		// Date
			+ sizeof(m_nDataLen)	// Data Length
			+ m_nDataLen;			// Data

	return total;
}


DWORD XMSG_OFFLINEDATA::GetDataLen(const char *buf)
{
	int i=0;
	i = sizeof(m_szUID);
	i += sizeof(m_szDate);
	memcpy((char*)&m_nDataLen, buf+i, sizeof(m_nDataLen));
	i += sizeof(m_nDataLen);
	i += m_nDataLen;

	return i;
}

XMSG_OFFLINEDATA::~XMSG_OFFLINEDATA()
{
	if (buffer)
	{
		delete buffer;
		buffer = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

XMSG_SMS::XMSG_SMS()
{
	ZeroMemory((char*)m_szNUM, sizeof(m_szNUM));
	m_buf = NULL;
	m_dwBufLen = 0;
	m_dwIndex = 255;
	m_dwTotal = 0;
}

XMSG_SMS::XMSG_SMS(const char *buf)
{
	ZeroMemory((char*)m_szNUM, sizeof(m_szNUM));
	m_buf = NULL;
	m_dwBufLen = 0;
	m_dwIndex = 255;
	m_dwTotal = 0;

	DWORD idx = 0;
	memcpy((char*)&m_dwIndex, buf, sizeof(DWORD));
	idx += sizeof(DWORD);

	memcpy(m_szNUM, buf+idx, sizeof(m_szNUM));
	idx += sizeof(m_szNUM);

	memcpy((char*)&m_dwBufLen, buf+idx, sizeof(DWORD));
	idx += sizeof(DWORD);

	m_buf = new char [m_dwBufLen];
	memcpy(m_buf, buf+idx, m_dwBufLen);
}

XMSG_SMS::~XMSG_SMS()
{
	if (m_buf)
	{
		delete [] m_buf;
		m_buf = NULL;
	}
}

void XMSG_SMS::SetData(LPCTSTR szNUM, LPCTSTR buf, DWORD bufLen)
{
	memcpy(m_szNUM, szNUM, sizeof(m_szNUM));
	m_buf = new char[bufLen];
	m_dwBufLen = bufLen;
	strcpy(m_buf, buf);

	m_dwTotal = sizeof(m_szNUM);
	m_dwTotal += sizeof(DWORD)*2;
	m_dwTotal += m_dwBufLen;
}

char *XMSG_SMS::GetData()
{
	DWORD idx=0;

	char *tmp = new char [m_dwTotal];

	memcpy(tmp, (char*)&m_dwIndex, sizeof(DWORD));
	idx += sizeof(DWORD);

	memcpy(tmp+idx, m_szNUM, sizeof(m_szNUM));
	idx += sizeof(m_szNUM);

	memcpy(tmp+idx, (char*)&m_dwBufLen, sizeof(DWORD));
	idx += sizeof(DWORD);

	memcpy(tmp+idx, m_buf, m_dwBufLen);

	delete [] m_buf;
	m_buf = tmp;

	return tmp;
}

char * XMSG_SMS::GetBuffer()
{
	return m_buf;
}

DWORD XMSG_SMS::GetBufferLength()
{
	return m_dwTotal;
}

char * XMSG_SMS::GetNUM()
{
	return (char*)m_szNUM;
}
//////////////////////////////////////////////////////////////////////////

//**********************************************************************************
// End ������Ϣ XMSG_OFFLINEDATA
//**********************************************************************************


void XUserInfo::SetNumberAndSex(BOOL bNUM, BOOL bSex)
{
	char n1;
	char n2;
	n1 = (char)bNUM;
	n2 = (char)bSex;

	m_szUID[29] = n1;
	m_szUID[30] = n2;
}

BOOL XUserInfo::UserHasMobile()
{
	char n1 = (int)m_szUID[29];
	return n1==1;
}
