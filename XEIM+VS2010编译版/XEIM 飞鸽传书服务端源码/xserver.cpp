/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#include "stdafx.h"
#include "resource.h"
#include "xserver.h"
#include "process.h"
#include "xsvrDlg.h"
#include "xsvr.h"
#include "../xmsg/xtype.h"
#include "../xmsg/xdef.h"


#define XEIM_FreeAndNULL(p) {GlobalFree(p);p = NULL;}

// �������߳�����
DWORD xserver::m_dwThreads = 0;
// �߳̾��
HANDLE *xserver::m_phThread = NULL;
// �����¼
CString xserver::m_strLastError = "";

xserver::xserver()
{
}

void xserver::run(HWND hWnd)
{
	// ��ʼ��
	InitServer();

	_beginthread(lisn_proc, 4096, hWnd);
}

// ���ӹ����߳�
void xserver::lisn_proc(void* hWnd)
{
	SOCKADDR_IN InternetAddr;
	SOCKET Listen;
	SOCKET Accept;
	HANDLE CompletionPort;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	int i;
	DWORD RecvBytes;
	DWORD Flags;
	DWORD ThreadID;

	// Setup an I/O completion port.
	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		AfxMessageBox("CreateIoCompletionFailed with error %d\n", GetLastError());
		return;
	}
	
	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor.
	for (i=0; i<(int)m_dwThreads; i++)
	{
		// Create a server worker thread and pass the completion port to the thread.
		if ((m_phThread[i] = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort, 0, &ThreadID)) == NULL)
		{
			m_strLastError.Format("CreateThread failed with error %d\n", GetLastError());
			return;
		}
	}

	// Create a listening socket.
	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		m_strLastError.Format("WSASocket failed with error %d\n", WSAGetLastError());
		return;
	}

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_port = htons(PORT);
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		m_strLastError.Format("bind failed with error %d\n", WSAGetLastError());
		// ��ʱ������������ֱ���˳���
		exit(0);
		return;
	}

	// Prepare socket for listening.
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		m_strLastError.Format("listen failed with error %d\n", WSAGetLastError());
		// ��ʱ������������ֱ���˳���
		exit(0);
		return;
	}

	// Accept connections and assign to the completion port.

	while(TRUE)
	{
		if (SOCKET_ERROR == (Accept = WSAAccept(Listen, NULL, NULL, NULL, 0)))
		{
			CString strError;
			strError.Format("WSAAccept failed with error %d\n", WSAGetLastError());
			AfxMessageBox(strError);
			return;
		}

		// Create a socket information structure to associate with the socket
		PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HEANDLE_DATA));
		if (NULL == PerHandleData)
		{
			CString strError;
			strError.Format("GlobalAlloc failed with error %d\n", GetLastError());
			AfxMessageBox(strError);
			return;
		}

		// Associate the accepted socket with the original completion port.
		/*AfxMessageBox("Socket number %d connected\n", Accept);*/
		::PostMessage((HWND)hWnd, XM_CONNECTED, NULL, Accept);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//KeepAliveʵ�� 
		TCP_KEEPALIVE2 inKeepAlive;//�������
		memset(&inKeepAlive, 0, sizeof(TCP_KEEPALIVE2));  
		unsigned long ulInLen = sizeof(TCP_KEEPALIVE2);  
		TCP_KEEPALIVE2 outKeepAlive;//������� 
		memset(&outKeepAlive, 0, sizeof(TCP_KEEPALIVE2)); 
		unsigned long ulOutLen = sizeof(TCP_KEEPALIVE2);  
		unsigned long ulBytesReturn = 0;  

		//����socket��keep aliveΪ5�룬���ҷ��ʹ���Ϊ3��   
		inKeepAlive.onoff = 1;  
		inKeepAlive.keepaliveinterval = 5000; //����KeepAlive̽����ʱ���� 
		inKeepAlive.keepalivetime = 5000; //��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ�� 

		if (WSAIoctl((unsigned int)Accept,
		  SIO_KEEPALIVE_VALS,
		  (LPVOID)&inKeepAlive, ulInLen,
		  (LPVOID)&outKeepAlive, ulOutLen,
		  &ulBytesReturn, NULL, NULL)
		  == SOCKET_ERROR)
		{          
			CString strError;
			strError.Format("WSAIoctl failed. error code %d", GetLastError());
			AfxMessageBox(strError);
			return;
		}

		PerHandleData->Sock = Accept;
		if (NULL == CreateIoCompletionPort((HANDLE)Accept, CompletionPort, (DWORD)PerHandleData, 0))
		{
			CString strError;
			strError.Format("CreateIoCompletionPort failed with error %d\n", GetLastError());
			AfxMessageBox(strError);
			return;
		}

		// Create per I/O socket information structure to associate with the
		// WSARecv call below.
		PerIoData = (LPPER_IO_OPERATION_DATA )GlobalAlloc(GPTR, sizeof(PER_IO_OPERATION_DATA));
		if (PerIoData == NULL)
		{
			CString strError;
			strError.Format("GlobalAlloc failed with error %d\n", GetLastError());
			AfxMessageBox(strError);
			return;
		}

		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		PerIoData->hWnd = (HWND)hWnd;
		PerIoData->send = 1;

		Flags = 0;

		if (SOCKET_ERROR == WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags, &(PerIoData->Overlapped), NULL))
		{
			if (ERROR_IO_PENDING != WSAGetLastError())
			{
				CString strError;
				strError.Format("WSARecv failed with error %d\n", WSAGetLastError());
				AfxMessageBox(strError);
				return;
			}
		}
	}

}

xserver::~xserver()
{
}


DWORD WINAPI xserver::ServerWorkerThread(LPVOID CompletionPortID)
{
	// XEIM DEBUG
	CWnd* pWnd = AfxGetApp()->GetMainWnd();
	CXsvrDlg *pDlg = (CXsvrDlg*)pWnd;

	DWORD tid = GetCurrentThreadId();

	// XEIM Debug
//	CString str;
//	str.Format("Thread #%d is running.", tid);
//	EnterCriticalSection(&xsrv_cs);
//	pDlg->AddErrorInfo(str);
//	LeaveCriticalSection(&xsrv_cs);

	while(TRUE)
	{
		HANDLE CompletionPort = (HANDLE)CompletionPortID;
		DWORD BytesTransferred;
		DWORD RecvBytes;
		DWORD Flags;
		LPPER_IO_OPERATION_DATA PerIoData;
		LPPER_HANDLE_DATA PerHandleData;

		HWND hWnd;
		SOCKET sock;
		if (0 == GetQueuedCompletionStatus(
										CompletionPort,
										&BytesTransferred,
										(LPDWORD)&PerHandleData,
										(LPOVERLAPPED*)&PerIoData,
										INFINITE))
		{
			hWnd = PerIoData->hWnd;
			sock = PerHandleData->Sock;

			XEIM_FreeAndNULL(PerHandleData);
			XEIM_FreeAndNULL(PerIoData);

			// ��ȡ�������
			int nLastError = WSAGetLastError();

			// ������
			switch (nLastError)
			{

			case ERROR_NETNAME_DELETED:
				{
					::PostMessage(hWnd, XM_LOGOFF, NULL, sock);
					XEIM_closesocket(tid, sock);

					// XEIM DEBUG
				/*	EnterCriticalSection(&xsrv_cs);
					pDlg->AddErrorInfo("ERROR_NETNAME_DELETED == WSAGetLastError()");
					LeaveCriticalSection(&xsrv_cs);*/
				}
				break;

			case ERROR_OPERATION_ABORTED:
				{
					::SendMessage(hWnd, XM_LOGOFF, NULL, sock);
					XEIM_closesocket(tid, sock);

					// XEIM DEBUG
					pDlg->AddErrorInfo("ERROR_OPERATION_ABORTED");
				}
				break;

			// �������ش���
			default:
				{
					CString strError;
					strError.Format("#%d GetQueuedCompletionStatus failed with error %d\n", tid, GetLastError());
					// XEIM DEBUG
					AfxMessageBox(strError);
					pDlg->AddErrorInfo(strError);
					return 0;
				}
			}

			// ��������
			continue;
		} // 0 == GetQueuedCompletionStatus

		hWnd = PerIoData->hWnd;
		sock = PerHandleData->Sock;

		// �ͻ��������˳����򣬻���ܵ� 0 �ֽڣ��������󣬽��д�����
		if (BytesTransferred == 0)
		{
			XEIM_FreeAndNULL(PerHandleData);
			XEIM_FreeAndNULL(PerIoData);

			::PostMessage(hWnd, XM_LOGOFF, NULL, sock);
			XEIM_closesocket(tid, sock);

			continue;
		} // End �������󣬽��д�����


		if (BytesTransferred > 1024*2)
		{
			XEIM_FreeAndNULL(PerHandleData);
			XEIM_FreeAndNULL(PerIoData);

			// XEIM DEBUG
			pDlg->AddErrorInfo("���ݰ�����BytesTransferred > 1024*2");

			::PostMessage(hWnd, XM_LOGOFF, NULL, sock);
			XEIM_closesocket(tid, sock);
			continue;
		}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
////////// ���������￪ʼ====================================================================
		// �յ����ݰ�
		// XEIM DEBUG

		if (PerIoData->send == 2)
		{
			// XEIM DEBUG
		//	CString str;
		//	str.Format("2. #%d %d bytes sent.", tid, BytesTransferred);
		//	EnterCriticalSection(&xsrv_cs);
		//	pDlg->AddErrorInfo(str);
		//	LeaveCriticalSection(&xsrv_cs);
			GlobalFree(PerIoData);
		}
		else if (PerIoData->send)
		{
			PerIoData->send = 0;

			XMSG msg(PerIoData->Buffer, BytesTransferred);

			// �򿪽���
			switch(msg.m_nMessage)
			{
			case XEIMMSG_GET_SCHEDULE:
				{
				//	pDlg->AddErrorInfo("XEIMMSG_GET_SCHEDULE");
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
					::PostMessage(hWnd, XM_GET_SCHEDULE, (WPARAM)PerIoData, sock);
				}
				break;
			case XEIMMSG_GET_PROJECT:
				{
				//	pDlg->AddErrorInfo("XEIMMSG_GET_PROJECT");
					::PostMessage(hWnd, XM_GET_PROJECT, (WPARAM)PerIoData, sock);
				}
				break;

			case XEIMMSG_NEW_PROJECT:
				{
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
				//	pDlg->AddErrorInfo("XEIMMSG_NEW_PROJECT");
					::PostMessage(hWnd, XM_RECORD_PROJECT, (WPARAM)PerIoData, sock);
				}
				break;
			
				// �ͻ���֪ͨ��������ʼ������ʷ��¼����
				case XEIMMSG_SENDHISTORYDATA:
				{
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
					::PostMessage(hWnd, XM_SENDHISTORYDATA, (WPARAM)PerIoData, sock);
				}
				break;
				// �ͻ���������Ϣ��ʷ��¼
				case XEIMMSG_GETHISTORYMSG:
				{
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
					::PostMessage(hWnd, XM_GETHISTORYDATA, (WPARAM)PerIoData, sock);
				}
				break;


				// �ͻ�������������Ϣ����
				case XEIMMSG_GETDATAOFFLINE:
				{
					::PostMessage(hWnd, XM_GETDATAOFFLINE, (WPARAM)PerIoData, sock);
				}
				break;
				// �ͻ��˶������ȡ������Ϣ
				case XEIMMSG_GETMSGOFFLINE:
				{
					// XEIM DEBUG
#ifdef XEIM_DEBUG
					pDlg->AddErrorInfo("�û�����������Ϣ��׼������...");
#endif
					::PostMessage(hWnd, XM_GETMSGOFFLINE, (WPARAM)PerIoData, sock);
				}
				break;
				// �û���¼��Ϣ /////////////////////////////////////////
				case XEIMMSG_LOGIN:
				{
					// XEIM DEBUG
				//	EnterCriticalSection(&xsrv_cs);
				//	pDlg->AddErrorInfo("Worker thread:XEIMMSG_LOGIN");

					XUserDetail *pXDetail = new XUserDetail;
					memcpy(pXDetail, msg.GetData(), msg.GetDataLenght());
					if (! pXDetail->IsDataType())
					{
						// XEIM DEBUG
						pDlg->AddErrorInfo("XEIMMSG_LOGIN �����������س���");
						break;
					}
					PerIoData->DataBuf.buf = (char*)pXDetail;
				//	PerIoData->DataBuf.len = sizeof(XUserDetail);
					::PostMessage(hWnd, XM_LOGIN, (WPARAM)PerIoData, sock);
				//	LeaveCriticalSection(&xsrv_cs);
				}
				break; // XEIMMSG_LOGIN



				// �û������ȡ�û��б� /////////////////////////////////////////
				case XEIMMSG_GETLIST:
				{
					// XEIM DEBUG
				//	EnterCriticalSection(&xsrv_cs);
				//	pDlg->AddErrorInfo("Worker thread:XEIMMSG_GETLIST");
				//	LeaveCriticalSection(&xsrv_cs);
				//	AfxMessageBox("XEIMMSG_GETLIST");
				//	Sleep(330);
					::SendMessage(hWnd, XM_GETLIST, (WPARAM)PerIoData, sock);
				}
				break; // XEIMMSG_GETLIST

 				// �û�������Ϣ /////////////////////////////////////////
				case XEIMMSG_MESSAGE:
				{
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
					::PostMessage(PerIoData->hWnd, XM_MESSAGE, (WPARAM)PerIoData, PerHandleData->Sock);
				}
				break; // XEIMMSG_MESSAGE

				// �û�����������Ϣ
				case XEIMMSG_MSGOFFLINE:
				{
					DWORD dwDataLen = msg.GetDataLenght();
					char *buf = new char[dwDataLen];
					memcpy(buf, msg.GetData(), dwDataLen);
					XMSG_OFFLINE ooo;
				//	pDlg->AddErrorInfo(ooo.GetUID(buf));
				//	CString str;
				//	str.Format("%d -- %s -- %s", ooo.GetDataLength(buf), ooo.GetUID(buf), ooo.GetData(buf));
				//	pDlg->AddErrorInfo(str);
				/*	char *sst = buf;
					CString strInfo;
					strInfo.Format("%d", dwDataLen);
					char bbb[1024];
					sprintf(bbb, "%d %d %d %d %d %d %d %d %d\n", sst[0], sst[1], sst[2], sst[3], sst[4], sst[5],  sst[6],  sst[7],  sst[8]);
					pDlg->AddErrorInfo(bbb);*/
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = dwDataLen;
				/*	XMSG_OFFLINEDATA occ(buf);
					pDlg->AddErrorInfo(occ.GetUID());*/
					::PostMessage(PerIoData->hWnd, XM_OFFLINEMESSAGE, (WPARAM)PerIoData, PerHandleData->Sock);
				}
				break; // XEIMMSG_OFFLINEMSG

				// �û������ļ� /////////////////////////////////////////
				case XEIMMSG_NEWFILE:
				{
					char *buf = new char[msg.GetDataLenght()];
					memcpy(buf, msg.GetData(), msg.GetDataLenght());
					PerIoData->DataBuf.buf = buf;
					PerIoData->DataBuf.len = msg.GetDataLenght();
					::PostMessage(PerIoData->hWnd, XM_NEWFILE, (WPARAM)PerIoData, PerHandleData->Sock);

//					::PostMessage(PerIoData->hWnd, XM_NEWFILE, (WPARAM)PerIoData, PerHandleData->Sock);
				}
				break; // XEIMMSG_NEWFILE:


				// �û��б������ /////////////////////////////////////////
				case XEIMMSG_LISTEND:
				{
					AfxMessageBox("User List end");
				}
				break; // XEIMMSG_LISTEND



				/////////////////////////////////////////
				case XEIMMSG_USERSTATUS:
				{
					GlobalFree(PerIoData);
				//	AfxMessageBox("XEIMMSG_USERSTATUS");
				}
				break; // XEIMMSG_USERSTATUS

				case XEIMMSG_USERLIST:
				{
					pDlg->AddErrorInfo("Worker thread:XEIMMSG_USERLIST");
					GlobalFree(PerIoData);
				}
				break;

				// ��Ϣ���ͳɹ� /////////////////////////////////////////
				case XEIMMSG_NEWMESSAGE:
					{
					//	AfxMessageBox("XEIMMSG_NEWMESSAGE");
					}
				break; // XEIMMSG_NEWMESSAGE

				case XEIMMSG_FILE:
					{
					}
				break; // XEIMMSG_FILE

				default:
				{
				//	AfxMessageBox("Default");
					char tmp[5];
					memcpy(tmp, PerIoData->Buffer, 4);
					tmp[4] = NULL;
					// ���� HTTP Э��� POST ����
					if (! strcmp(strupr(tmp),"POST"))
					{
					//	AfxMessageBox("adsf");
					//	::PostMessage(PerIoData->hWnd, XM_HTTPPOST, (WPARAM)PerIoData, PerHandleData->Sock);
					}
					else
					{
						Flags = 0;
						ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
						PerIoData->DataBuf.len = DATA_BUFSIZE;
						PerIoData->DataBuf.buf = PerIoData->Buffer;
						if (WSARecv(PerHandleData->Sock, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
							&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
						{
							if (WSAGetLastError() != ERROR_IO_PENDING)
							{
								printf("WSARecv() failed with error %d\n", WSAGetLastError());
								return 0;
							}
						}
						PerIoData->send = 1;
					}
				}
			}
		} // else if (PerIoData->send)
		else
		{
		//	AfxMessageBox("About to recv.");
			Flags = 0;
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
			PerIoData->DataBuf.len = DATA_BUFSIZE;
			PerIoData->DataBuf.buf = PerIoData->Buffer;
			if (WSARecv(PerHandleData->Sock, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
			PerIoData->send = 1;
		}

	} // while(TRUE)
	return -1;
}

BOOL xserver::IsHttpPost(LPCTSTR lpszBuffer)
{
	char tmp[5];
	memcpy(tmp, lpszBuffer, 4);
	tmp[4] = NULL;

	// ���� HTTP Э��� POST ����
	if (! strcmp(strupr(tmp),"POST"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
/*		Flags = 0;
		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		if (WSARecv(PerHandleData->Sock, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
			&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
				return 0;
			}
		}
		PerIoData->send = 1;*/
	}
}


BOOL xserver::InitServer()
{
	SYSTEM_INFO SystemInfo;
	WSADATA wsaData;
	DWORD ret;

	if ((ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		m_strLastError.Format("WSAStartup failed with error:%d", ret);
		return FALSE;
	}

	// ����Ҫ�������ٸ� IOCP �����߳�
	// Determine how many processors are on the system.
	GetSystemInfo(&SystemInfo);
	m_dwThreads = SystemInfo.dwNumberOfProcessors*2;
	m_phThread = new HANDLE[m_dwThreads];

	return TRUE;
}

// tid ��ǰ�̵߳� ID
// sock ִ�йرյ��׽���
void xserver::XEIM_closesocket(DWORD tid, SOCKET sock)
{
	// XEIM DEBUG
	CWnd* pWnd = AfxGetApp()->GetMainWnd();
	CXsvrDlg *pDlg = (CXsvrDlg*)pWnd;
	if (closesocket(sock) == SOCKET_ERROR)
	{
		CString str;
		str.Format("#%d closesocket failed with error %d",tid, WSAGetLastError());

		// XEIM DEBUG
		pDlg->AddErrorInfo(str);
	}
}
