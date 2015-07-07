/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#ifndef XEIM_DEF
#define XEIM_DEF

/////////////////////////////////////////////////////////
// msg ��ʶ����淶
// XEIMMSG + 0x01 ��ʼ
/////////////////////////////////////////////////////////
#define	XEIMMESSAGE					0xef000000
#define XEIMMSG_LOGIN				XEIMMESSAGE + 0x01
#define	XEIMMSG_MESSAGE				XEIMMESSAGE + 0x02
#define	XEIMMSG_USEROK				XEIMMESSAGE + 0x03
#define	XEIMMSG_USERBAD				XEIMMESSAGE + 0x04
#define	XEIMMSG_GETLIST				XEIMMESSAGE + 0x05
#define XEIMMSG_USERINFO			XEIMMESSAGE + 0x06
#define XEIMMSG_LISTEND				XEIMMESSAGE + 0x07
#define XEIMMSG_USERLIST			XEIMMESSAGE + 0x08
#define XEIMMSG_USERSTATUS			XEIMMESSAGE + 0x09
#define	XEIMMSG_NEWMESSAGE			XEIMMESSAGE + 0x0a	// ���յ�������Ϣ
#define XEIMMSG_HTTPPOST			XEIMMESSAGE + 0x0b	// ���յ�HTTP��Ϣ
#define	XEIMMSG_NEWFILE				XEIMMESSAGE + 0x0c	// ���յ��ļ���Ϣ
#define	XEIMMSG_FILE				XEIMMESSAGE + 0x0d	// �ͻ��˽��յ��ļ�

// �ͻ��˷���������Ϣ
#define XEIMMSG_MSGOFFLINE				XEIMMESSAGE + 0x0e
// �ͻ��˶������ȡ������Ϣ
#define XEIMMSG_GETMSGOFFLINE			XEIMMESSAGE + 0x0f
// �ͻ��������ȡ������Ϣ����
#define XEIMMSG_GETDATAOFFLINE			XEIMMESSAGE + 0x10

// ���Ͷ���
#define XEIMMSG_SMS						XEIMMESSAGE + 0x11

// �ͻ����������������ʷ��¼
#define XEIMMSG_GETHISTORYMSG			XEIMMESSAGE + 0x12
// ������֪ͨ�ͻ��˿�ʼ������ʷ��¼
#define XEIMMSG_RECVHISTORYDATA			XEIMMESSAGE + 0x13
// �ͻ���֪ͨ��������ʼ������ʷ��¼����
#define XEIMMSG_SENDHISTORYDATA			XEIMMESSAGE + 0x15
// ��������ʼ��ͻ��˷�����ʷ��¼����
#define XEIMMSG_HISTORYDATA				XEIMMESSAGE + 0x16


// �ͻ������������ѯ���°汾
#define XEIMMSG_CHECK_VERSION			XEIMMESSAGE + 0x17
// �������������°�Ÿ��ͻ���
#define XEIMMSG_VERSION					XEIMMESSAGE + 0x18


// �ͻ��˷�����ͨ����
#define XEIMMSG_NORMAL_SMS				XEIMMESSAGE + 0x21

// �ͻ��˷��͵Ķ��ż�¼
#define XEIMMSG_SMS_RECORD				XEIMMESSAGE + 0x22

// �ͻ���ͨ�������ύ����
#define	XEIMMSG_APP_SMS					XEIMMESSAGE + 0x23

// �ͻ����½���Ŀ
#define XEIMMSG_NEW_PROJECT				XEIMMESSAGE + 0x24
// �ͻ��������ȡ��Ŀ
#define XEIMMSG_GET_PROJECT				XEIMMESSAGE + 0x25
// ���������͵���Ŀ
#define XEIMMSG_PROJECT					XEIMMESSAGE + 0x26
// �ͻ��������ȡ�����б�
#define XEIMMSG_GET_SCHEDULE			XEIMMESSAGE + 0x27
// ���������͵Ĺ���
#define XEIMMSG_SCHEDULE				XEIMMESSAGE + 0x28

//////////////////////////////////////////////////////////////////////////
// ϵͳ��Ϣ
//////////////////////////////////////////////////////////////////////////


#define XM_USER				WM_USER + 0x65

#define	XM_LOGIN			XM_USER + 0x01
#define	XM_LOGOFF			XM_USER + 0x02
#define XM_MESSAGE			XM_USER + 0x03
#define	XM_CONNECTED		XM_USER + 0x04
#define	XM_GETLIST			XM_USER + 0x05
#define XM_HTTPPOST			XM_USER + 0x06
// �ļ���Ϣ����
#define XM_NEWFILE			XM_USER + 0x07

// ˫��User List TreeCtrlʱ���͵���Ϣ
#define	XM_EMDBLCLICKTREE	WM_USER + 0x08
// �����û������������Ϣ
#define XM_GETMSGOFFLINE	WM_USER + 0x09
// ������Ϣ
#define XM_OFFLINEMESSAGE	XM_USER + 0x10
// ������Ϣ����
#define XM_GETDATAOFFLINE	XM_USER + 0x11

// ����
#define XM_SMS				XM_USER + 0x12

// �ͻ���������Ϣ��ʷ��¼
#define XM_GETHISTORYDATA	XM_USER + 0x13

// �ͻ���֪ͨ��������ʼ������ʷ��Ϣ����
#define XM_SENDHISTORYDATA	XM_USER + 0x15

// �ͻ��˷�����ͨ����
#define XM_NORMAL_SMS		XM_USER + 0x16

// ��¼�ͻ��˵Ķ���
#define XM_RECORD_SMS		XM_USER + 0x18

// ��¼�ͻ�����Ŀ
#define XM_RECORD_PROJECT	XM_USER + 0x19

// ��ȡ�����Ϳͻ�����Ŀ
#define XM_GET_PROJECT		XM_USER + 0x20

// ��ȡ�����Ϳͻ��˹���
#define XM_GET_SCHEDULE		XM_USER + 0x21

// XEIM ��ʱͨѶϵͳ���õ� TCP ͨѶ�˿�
#define PORT			8188

#define DATA_BUFSIZE	1024 * 2


#define	STATUS_ONLINE						1
#define	STATUS_OFFLINE						2


#define SIO_KEEPALIVE_VALS   _WSAIOW(IOC_VENDOR,4) 

#endif // XEIM_DEF