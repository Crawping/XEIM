/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#ifndef XSVR_H
#define	XSVR_H

#include "../xmsg/xdef.h"
#include "winsock2.h"


#pragma comment(lib, "ws2_32")

class xserver
{
public:

	static CString m_strLastError;
	BOOL InitServer();

	// ר�����ڹر��׽���
	static void XEIM_closesocket(DWORD tid, SOCKET sock);

	static BOOL IsHttpPost(LPCTSTR lpszBuffer);
	// �����߳�
	void run(HWND hWnd);

	xserver();
	~xserver();
private:

	// �������߳�����
	static DWORD m_dwThreads;
	// �߳̾��
	static HANDLE *m_phThread;
	// ���ݴ����߳�
//	static void recv_proc(void* tdata);
	static DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);
	// ���ӹ����߳�
	static void lisn_proc(void* tdata);
};
#endif // XSVR_H
