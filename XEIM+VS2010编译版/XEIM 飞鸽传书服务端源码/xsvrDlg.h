/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// xsvrDlg.h : header file
//

#if !defined(AFX_XSVRDLG_H__BBBF4633_43E9_4615_BBCE_68DA3C0F4D80__INCLUDED_)
#define AFX_XSVRDLG_H__BBBF4633_43E9_4615_BBCE_68DA3C0F4D80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../xmsg/xtype.h"
#include "xserver.h"
#include "XTreeCtrl.h"
#include "SystemTray.h"
#include "XSplitDlg.h"
#include "XTaskDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXsvrDlg dialog
//class SerialThread;
class CXsvrApp;

class CXsvrDlg : public CDialog
{
// Construction
public:
	BOOL _UI_SetProductInfo();
	LPCTSTR _ERP_GetUIDByName(LPCTSTR lpszName);
	BOOL _ERP_SendMessageToUserByName(LPCTSTR szName, LPCTSTR szMessage);
	void _ERP_SendMessageToUserList(CString strUsers, CString strMessage);
	// ���ַ���ʱ��ת���� CTime ʱ��
	void _ERP_StringToCTime(IN CString str, OUT CTime &ctm);
	void _ERP_INIT();
	void _ERP_CheckDatabase();
	void XUser_SendStatus();
	void XUser_SendContact();
//	void XCheckSMSList();


	// SMS ���� ////////////////////////////////////////////////////////////
//	SerialThread* serialProcess;
	// SMS �߳��Ƿ�����
/*	BOOL m_bSMSActiveProccess;
	// COM1 �˿�����
	DWORD m_dwSMSStep;
	CString	m_monitorSend;
	CString m_strSMSCenter;
	CString m_strCOMX;
	list<string> m_listSMS;
	// ����״̬
	BOOL m_bSuccessed;*/
	// SMS ���� ////////////////////////////////////////////////////////////




	// ERP ���� //////////////////////////////////////////////////////////////////////////
	DWORD m_dw_ERP_MONTH;
	DWORD m_dw_ERP_CURRENT_NUMBER;
	// ERP ���� //////////////////////////////////////////////////////////////////////////
	


	// �û���ϵ���б����ʱ��
	BOOL m_bSendUserContact;
	list<SOCKET> m_listContactQuery;

	// �û�״̬��Ϣ
	list<XUserInfo> m_listUserStatus;
	BOOL m_bSendUserStatus;

	// �߳�ͬ��
	CXsvrApp *m_pApp;

	void GetUIDMobileNUM(LPCTSTR lpszUID, CString &strNum);
	DWORD SendDataToClient(SOCKET sock, char *buf, DWORD len);
	// ���� SOCKET ״̬
	BOOL ResetSockState(SOCKET sock, LPPER_IO_OPERATION_DATA PerIoData);
	// ��������Ϣ��ӵ���ʷ��¼��
	void XDBMsgOnLine(LPCTSTR lpszSendUID, LPCTSTR lpszRecvUID, LPCTSTR lpszMsgBody);
	// ��������Ϣ��ӵ���ʷ��¼��
	void XDBMsgOffLine(LPCTSTR lpszSendUID, LPCTSTR lpszRecvUID, LPCTSTR lpszMsgBody);
	// �Ѷ�����Ϣ��¼�����ݿ�
	void XDBMsgSMS(LPCTSTR lpszSendUID, LPCTSTR lpszRecvUID, LPCTSTR lpszMsgBody);

	// �û��ǳ� XEIM ������ݿ�Ĵ���
	void XDBUserLogout(LPCTSTR lpszUID);
	// �û���¼ XEIM ������ݿ�Ĵ���
	void XDBUserLogin(LPCTSTR lpszUID, LPCTSTR lpszVersion, LPCTSTR lpszIP);

	// ��ʼ����������ݿ���ж�ȡ
	void XDB_InitUserList();
	// ��ȡһ���û�����ϸ��Ϣ
	void XDB_ReadUserDetail(LPCTSTR lpszUID, XUserDetail &xDetail);

	void XCheckUserInfo();
	void AddErrorInfo(CString strErr);
	_ConnectionPtr m_pConn;					// ���ݿ�����
	list<XUserDetail> m_listUserDetail;		// �û���ϸ��Ϣ
	map<SOCKET, XUserInfo> m_mapUserInfos;	// �����û�ժҪ��Ϣ
	CImageList	m_ilUser;					// �����û� CTreeCtrl ͼ��

	BOOL XUserExisted(const char* szUID);
	void XUserAddNew(XUserDetail &detail, CString strMobile);
	void XUserUpdate(XUserDetail &detail, CString strMobile);
	BOOL XSendMsgToUser(const char* szUID, const char* szMSG);
	void XSendUserStatusToFriends(XUserInfo &xui);
	CXsvrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXsvrDlg)
	enum { IDD = IDD_XSVR_DIALOG };
	CEdit	m_errOut;
	CListCtrl	m_lcUserList;
	CXTreeCtrl	m_tcUserTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXsvrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	XSplitDlg	*m_pSplitDlg;				// ���ڲ��
	xserver m_xserver;						// �����������߳�
//	CXTaskDlg m_dlgTask;					// ���������

	HICON m_hIcon;
	HTREEITEM m_hRoot;						// �����û�

	CString m_strDatabase;					// ���ݿ�λ��

	CSystemTray m_sysTray;					//ϵͳ����

	// Generated message map functions
	//{{AFX_MSG(CXsvrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT XOnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XGetMsgOffLine(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XGetMsgHistory(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgHistoryData(WPARAM wParam, LPARAM lParam);
//	afx_msg void XOnNormalSMS(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnRecordSMS(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT _ERP_OnRecordProject(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT _ERP_OnGetProject(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT _ERP_OnGetSchedule(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XEIM_USER_Login(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgOnLine(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgOffLine(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgOffLineData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnLogoff(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnGetList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnNewFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGetDispInfo (NMHDR* pnmhdr, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnTrayRestore();
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuabout();
	afx_msg void OnMenuquit();
	afx_msg void OnMenuUser();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuTask();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMsgSystem();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSVRDLG_H__BBBF4633_43E9_4615_BBCE_68DA3C0F4D80__INCLUDED_)
