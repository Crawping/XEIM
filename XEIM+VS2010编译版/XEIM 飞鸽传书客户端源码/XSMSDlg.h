/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_XSMSDLG_H__755E310C_40CB_42E0_803A_E9998311F595__INCLUDED_)
#define AFX_XSMSDLG_H__755E310C_40CB_42E0_803A_E9998311F595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XSMSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXSMSDlg dialog

class CXSMSDlg : public CDialog
{
// Construction
public:

	LPSTR UnchangeCODE(LPCTSTR lpText);
	LPSTR ChangeCODE(LPCTSTR lpText);
	void SendSMS(SOCKET sock);
	CXSMSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXSMSDlg)
	enum { IDD = IDD_DIALOG5 };
	CString	m_strSMS;
	CString	m_strNUM;
	// ������ɫ
	CBrush m_brBk2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXSMSDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSMSDLG_H__755E310C_40CB_42E0_803A_E9998311F595__INCLUDED_)
