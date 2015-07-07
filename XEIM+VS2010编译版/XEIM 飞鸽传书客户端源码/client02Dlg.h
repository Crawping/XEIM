/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// client02Dlg.h : header file
//

#if !defined(AFX_CLIENT02DLG_H__30B9137D_CC8C_4377_9CF0_E0B7BD80A87C__INCLUDED_)
#define AFX_CLIENT02DLG_H__30B9137D_CC8C_4377_9CF0_E0B7BD80A87C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XChatDlg.h"
#include "XTreeCtrl.h"
#include "SystemTray.h"
#include "MyHyperLink.h"
#include "../XMSG/xtype.h"
#include "XPluginBar.h"	// Added by ClassView
#include "DLG_ERP_MESSAGE.h"
#include "DLG_ERP_SCHEDULE.h"
#include "DLG_ERP_PROJECT.h"
#include "DLG_ERP_WORK.h"
/////////////////////////////////////////////////////////////////////////////
// CClient02Dlg dialog


class CClient02Dlg : public CDialog
{
// Construction
public:
	void CheckForUpdate();
	CXPluginBar *m_pPluginBar;
	void ReConnect();
	BOOL SendSMS(LPCTSTR szRecv, LPCTSTR szSMS);
	void XCheckVersion();
	void XGetMsgOffLine();
	void AddDebugInfo(CString strInfo);
	LRESULT OnChildFire(WPARAM wparam,LPARAM lparam);
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	// ���紦��ص�����
	static void r(void* sock);
	static DLG_ERP_PROJECT* m_pDlg_ERP_Project;
	static DLG_ERP_SCHEDULE* m_pDlg_ERP_Schedule;
	static DLG_ERP_WORK* m_pDlg_ERP_Work;

	// ������ɫ
	CBrush m_brBk2;
	// �ı��򱳾���ɫ
	COLORREF m_editBKColor;
	COLORREF m_textcolor;

	void XSortUser(HTREEITEM hParent);
	BOOL Init();

	// ������ϵ�˵���Ϣ
	list<XUserInfo> m_listUserInfo;
	// ÿ���û���Ӧ����һ���Ի���
	map<HTREEITEM, CXChatDlg*> m_mapUserList;
	// ���в�������
	map<string, HTREEITEM> m_mapGroup;

	// �û�����
	CString m_strUPSW;
	// �û���
	CString m_strUID;
	// �û��ǳ�
	CString m_strUNickName;
	// �û���ϵ�绰
	CString m_strCellNUM;

	// ϵͳ��Ϣ�Ի���
	DLG_ERP_MESSAGE *m_erpDlg;

	// ���Ĵ�����ʾ
	CString m_strLastError;

	//ϵͳ����
	CSystemTray m_sysTray;
//	CStdioFile m_inifile;
	CString m_strSvr;
	SOCKET m_sock;
	HTREEITEM m_hRoot;

	typedef struct
	{
		HWND hWnd;
		SOCKET sock;
	}TDATA, *LPTDATA;

	CClient02Dlg(CWnd* pParent = NULL);	// standard constructor
	~CClient02Dlg();

// Dialog Data
	//{{AFX_DATA(CClient02Dlg)
	enum { IDD = IDD_CLIENT02_DIALOG };
	CXTreeCtrl	m_xtreeUser;
	CString	m_strDebug;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient02Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bLogedin;
	BOOL m_bNetWorkInit;
	DWORD m_dwOnLine;
	CXChatDlg *m_pGroupMsg;
	HICON m_hIcon;
	// �����û� treectrl ͼ��
	CImageList	m_ilUser;
	// [����] ��ť
	CMyHyperLink	m_staticSettings;
	CMyHyperLink	m_staticSendSMS;

	//[�˵�]��ť
	CMyHyperLink  m_staticMenu;

	// Generated message map functions
	//{{AFX_MSG(CClient02Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT XOnUserOK(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnUserBad(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnUserInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnDisconnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnUserList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnListEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnUserStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgRecvOffLine(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnTotalContact(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgHistory(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XMsgNoHistory(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnDblclkUserlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTrayRestore();
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRclickUserlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnMenuitemLogout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnQuit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	afx_msg void OnHelp();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT02DLG_H__30B9137D_CC8C_4377_9CF0_E0B7BD80A87C__INCLUDED_)
