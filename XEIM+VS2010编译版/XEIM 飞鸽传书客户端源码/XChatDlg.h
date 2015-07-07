/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_XCHATDLG_H__AE4CB5E7_7329_4601_9744_E2E796F9884F__INCLUDED_)
#define AFX_XCHATDLG_H__AE4CB5E7_7329_4601_9744_E2E796F9884F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XChatDlg.h : header file
//
#include "xdlldef.h"
#include "SplitDlg.h"
#include "ViewHistoryDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXChatDlg dialog

class CXChatDlg : public CDialog
{
// Construction
public:
	void SendAllMsg();
	BOOL m_bMobile;
	CPoint m_ptOldXY;
	CPoint m_ptMin;
	void AdjustSize(CWnd *pWnd, int x, int y, int nStyle);
	void SendGroupMsg();
	void XNoHistoryMsg(LPCTSTR szUID);
	void XAddHistoryMsg(LPCTSTR szMessage, LPCTSTR szUID, LPCTSTR szTime);
	void XAddOffLineMsg(LPCTSTR szMessage, LPCTSTR lpszTime);
	// �����¼ģ��
	CViewHistoryDlg *m_pHistoryDlg;
	// ��ǰ�û���״̬
	DWORD m_dwStatus;
	void SetUserStatus(DWORD dwStatus);
	// ����������Ϣ
	void SendOffLineMsg();
	// ����������Ϣ
	void SendOnLineMsg();
	void FlashWindow();
	// ���ܵ��ļ�
	void XRecvFile(LPXFILEINFO pInfo);

	
	// ���ڶ���
	void Shake_Window();
	
	typedef HWND (*pSendFile)(HWND hParent, SOCKET sock, LPCTSTR szUID);
	typedef HWND (*pRecvFile)(HWND hParent, LPXFILEINFO pInfo);
	pSendFile SendFile;
	pRecvFile RecvFile;
	HINSTANCE hInst;
	HWND	m_hFrame;
	// ���ڲ��
	CSplitDlg *m_pSplit;
	// ���ֵ��˻���Ⱥ����Ϣ
	BOOL m_bGroup;

	CBrush m_whitebrush;
	COLORREF m_whitecolor,m_textcolor;

	void XAddMessage(const char *szMessage);
	CString m_strUser;
	CString m_strUID;
	SOCKET m_sock;
	CXChatDlg(CWnd* pParent = NULL);   // standard constructor
	~CXChatDlg();

// Dialog Data
	//{{AFX_DATA(CXChatDlg)
	enum { IDD = IDD_DIALOG2 };
	CRichEditCtrl	m_richMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXChatDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// ������ɫ
	CBrush m_brBk2;
	HICON m_hIcon;
	BOOL m_bPlaying;
	BOOL m_bFile;

	// Generated message map functions
	//{{AFX_MSG(CXChatDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSend();
	afx_msg void OnSendSMS();
	afx_msg void OnViewHistory();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSendFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnDestCanceled(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDestRefused(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XOnAllFileFinished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT XDoubleClickUserList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg LRESULT XOnAddFDlgSize(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShake_Window();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnMsgfilterRichedit2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnMsgfilterRichedit1(NMHDR *pNMHDR, LRESULT *pResult);

private:
	//�Ƿ���������ı�����
	BOOL  HasClipTextData();
	//��ǰ����һ������Ƿ�������������RichEdit��
	BOOL  m_bCurInputPos;
public:
	afx_msg void OnChatPaste();
	afx_msg void OnChatCopy();
	afx_msg void OnChatCut();
	CString GetClipTextData();
	BOOL SetClipTextData(CString sText);
	afx_msg void OnChatSelAll();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCHATDLG_H__AE4CB5E7_7329_4601_9744_E2E796F9884F__INCLUDED_)
