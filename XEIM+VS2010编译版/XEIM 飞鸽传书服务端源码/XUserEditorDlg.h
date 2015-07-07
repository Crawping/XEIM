/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_XUSEREDITORDLG_H__72C94680_4F7E_4618_9063_04CE85F893EB__INCLUDED_)
#define AFX_XUSEREDITORDLG_H__72C94680_4F7E_4618_9063_04CE85F893EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XUserEditorDlg.h : header file
//
#include "../xmsg/xtype.h"
/////////////////////////////////////////////////////////////////////////////
// CXUserEditorDlg dialog

class CXUserEditorDlg : public CDialog
{
// Construction
public:
	void SetMobile(LPCTSTR szMobile);
	void InverseAll();
	void UncheckAll();
	void DeleteContact(LPCTSTR szUID);
	void CheckForChanging(HTREEITEM hParent);
	void AddNewContact(LPCTSTR szUID);
	void GetUserContact();
	void SetParentCheck(HTREEITEM hItem);
	void SetParentCheck2(HTREEITEM hItem);
	void SetItemCheck(HTREEITEM hParent, BOOL bCheck);
	// ���в�������
	map<string, HTREEITEM> m_mapGroup;
	BOOL SetData(XUserDetail &uDetail);
	// �û�����ϵ�� ��UID��ʽ���ڣ�UID Ϊ Ψһ�ı�ʶ��
	list<string> m_listContact;
	CXUserEditorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXUserEditorDlg)
	enum { IDD = IDD_USER_EDITOR };
	CTreeCtrl	m_treeUserList;
	CString	m_strUID;		// 1
	CString	m_strPassword;	// 2
	CString	m_strNickName;	// 3
	CString	m_strGroup;		// 4
	BOOL m_bModify;					// �޸Ļ���ӵĿ���
	CString	m_strUMobile;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXUserEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXUserEditorDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAll();
	afx_msg void OnCheckInverse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XUSEREDITORDLG_H__72C94680_4F7E_4618_9063_04CE85F893EB__INCLUDED_)
