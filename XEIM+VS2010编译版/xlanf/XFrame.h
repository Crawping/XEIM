#if !defined(AFX_XFRAME_H__E0145AE1_0CCE_4BCC_B0A7_7A0B57C6F7CA__INCLUDED_)
#define AFX_XFRAME_H__E0145AE1_0CCE_4BCC_B0A7_7A0B57C6F7CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XFrame.h : header file
//
#include "xdlldef.h"

#pragma warning(disable:4786)
#include <list>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CXFrame dialog

// �ļ��Ի��򼰶Ի�������
typedef struct
{
	CDialog *pDlg;
	BOOL	bSend;

} FILEDIALOG;


class CXFrame : public CDialog
{
// Construction
public:
	// �����ļ��������
	void NoFile();
	// һ���ļ�������ϣ����ͻ���ܣ�
	void FileOK(DWORD dwID);

	// ����һ���ļ�
	void SendFile(LPXFILEINFO pFileInfo);

	// ����һ���ļ�
	void RecvFile(LPXFILEINFO pFileInfo);

	// �ļ�����Ի������ 6 ��
	FILEDIALOG	m_dlg[6];

	// �����ߴ��ھ��
	HWND		m_hParent;

	// ��������
	DWORD		m_dwFileTotal;
	// �Ի�������������С�� 6
	DWORD		m_dwDlgTotal;

	list<XFILEINFO*> m_recvfile;
	list<XFILEINFO*> m_sendfile;

	CXFrame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXFrame)
	enum { IDD = IDD_FRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXFrame)
	afx_msg LRESULT OnFileRecvEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnDestRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCancelFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefuseFile(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFRAME_H__E0145AE1_0CCE_4BCC_B0A7_7A0B57C6F7CA__INCLUDED_)
