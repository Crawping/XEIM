/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_DLG_ERP_PROJECT_H__EDBCEE6F_19FE_4EC7_91E1_5308C43D562F__INCLUDED_)
#define AFX_DLG_ERP_PROJECT_H__EDBCEE6F_19FE_4EC7_91E1_5308C43D562F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLG_ERP_PROJECT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DLG_ERP_PROJECT dialog

class DLG_ERP_PROJECT : public CDialog
{
// Construction
public:
	void InitUI();
	void OnBtnWork();
	void ZoomOut();
	void ZoomIn();
	void AddProject(CString &strData);
	void AddSchedule(CString strData);
	// ��ȡָ����Ŀ��ŵ����й����б�
	BOOL GetScheduleFromSrv(CString strNumber);
	BOOL GetProjectFromSrv();
	BOOL EnsureDataComplete();

	// �������½�����Ŀ���͸���������¼
	BOOL SendProjectToSrv(CString &str);
	DLG_ERP_PROJECT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DLG_ERP_PROJECT)
	enum { IDD = IDD_PROJECT_NEW };
	CListCtrl	m_lcWorks;
	CListCtrl	m_lcAllProject;
	CString m_strNumber;
	COLORREF m_editBKColor;
	COLORREF m_textcolor;
	CBrush m_brBk2;
	BOOL m_bAddNew;
	DWORD m_dwMaxNumber;

	int m_hItemCurSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DLG_ERP_PROJECT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DLG_ERP_PROJECT)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnNewProject();
	afx_msg void OnBtnNewWork();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ERP_PROJECT_H__EDBCEE6F_19FE_4EC7_91E1_5308C43D562F__INCLUDED_)
