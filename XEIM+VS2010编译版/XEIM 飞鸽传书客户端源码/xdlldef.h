/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#include <WinSock2.h>

#define		WM_DEST_ACCEPT			WM_USER + 0x66
#define		WM_SEND_PROCESS			WM_USER + 0x68
#define		WM_SEND_NOTIFY			WM_USER + 0x69
#define		WM_SEND_CANCEL			WM_USER + 0xa2

#define		WM_DEST_CANCEL			WM_USER + 0xa1
#define		WM_RECV_FILE			WM_USER + 0x93
#define		WM_REFUSE_FILE			WM_USER + 0xb8


#define		WM_FILERECVEND			WM_USER + 0x64
#define		WM_FILESENDEND			WM_USER + 0x65
#define		WM_NEW_FILE				WM_USER + 0x68
#define		WM_RECV_CANCEL			WM_USER + 0xa3
#define		WM_FILE_FINISH			WM_USER + 0xa5	// �����ļ����������
//define		WM_REFUSE_FILE			WM_USER + 0xb8
// ֪ͨ�����ڵ�������
#define		XM_SENDFILEADD			WM_USER + 0x20
#define		XM_SENDFILEMIN			WM_USER + 0x21
// ֪ͨ�󶨳ɹ���󶨶˿�
#define		X_WM_TCP_FILE_BIND_OK	WM_USER + 0x22

// �ļ��������
#define		X_WM_TCP_FILE_COMPLETED	WM_USER + 0x23



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
#define	XEIMMSG_NEWMESSAGE			XEIMMESSAGE + 0x0a
#define XEIMMSG_HTTPPOST			XEIMMESSAGE + 0x0b

#define	XEIMMSG_NEWFILE				XEIMMESSAGE + 0x0c	// ���յ��ļ���Ϣ

// �ļ������̴߳��ݵĲ���
typedef struct
{
	// �����߳���Ϣ�Ĵ��ھ��
	HWND		hWnd;
	// Ҫ���͵��ļ���ַ
	char		szSendFileName[MAX_PATH];
	// ���շ���ʹ�õ� TCP �˿�
	int			nPort;

} XTCP_SendData, *LPXTCP_SendData;

// �ļ������̴߳��ݵ�����
typedef struct
{
	// �����߳���Ϣ�Ĵ��ھ��
	HWND	hWnd;
	// �����ļ��ĵ�ַ
	char	szSaveFileName[MAX_PATH];
	DWORD dwPort;

} XTCP_RecvData, *LPXTCP_RecvData;

// �ļ���Ϣ����Ϊ��������
typedef struct 
{
	char szFullName[MAX_PATH];
	char szShortName[MAX_PATH];
	char szExt[16];
	char szUID[32];
	char szUIP[128];
	SOCKET sock;
	DWORD dwPort;
	DWORD option;

} XFILEINFO, *LPXFILEINFO;

#define FILE_NEW			1		// �û��·��ʼ�
#define FILE_REFUSE			2		// �û��ܾ������ļ�
#define	FILE_CANCEL			3		// �û�ȡ������


// �ļ���Ϣ
typedef struct {
	// �ļ�����
	int		nFileLength;
	// �ļ���
	char	szFileName[MAX_PATH];

} XTCP_FileInfo, *LPXTCP_FileInfo;
