#include "StdAfx.h"
#include "xdlldef.h"


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
	memcpy((char*)&m_nMessage, szBuffer, sizeof(m_nMessage));
	if (XEIMMESSAGE != (m_nMessage & XEIMMESSAGE))
	{
		printf("This data is not a XEIM XMSG data. XMSG::XMSG");
		return;
	}
	nIdx = sizeof(m_nMessage);
	memcpy((char*)&m_nDataLength, szBuffer+nIdx, sizeof(m_nDataLength));
	nIdx += sizeof(m_nDataLength);
	m_szData = new char[m_nDataLength];
	memcpy(m_szData, szBuffer+nIdx, m_nDataLength);
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
	strcpy(m_szUID, szid);
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


