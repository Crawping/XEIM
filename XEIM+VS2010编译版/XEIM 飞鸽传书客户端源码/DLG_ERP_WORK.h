/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_DLG_ERP_WORK_H__9508D9CC_28D9_4762_AD1C_AFADC5E7D226__INCLUDED_)
#define AFX_DLG_ERP_WORK_H__9508D9CC_28D9_4762_AD1C_AFADC5E7D226__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLG_ERP_WORK.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DLG_ERP_WORK dialog

class DLG_ERP_WORK : public CDialog
{
// Construction
public:
	void AddSchedule(CString strData);
	BOOL GetScheduleFromSrv();
	DLG_ERP_WORK(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DLG_ERP_WORK)
	enum { IDD = IDD_WORK };
	CListCtrl	m_lcWorks;
	CString m_strNumber; // ��Ŀ���
	CString m_strProject; // ��Ŀ����
	CString m_strProDetail; // ��Ŀ����

	// �ı��򱳾���ɫ
	COLORREF m_editBKColor;
	COLORREF m_textcolor;
	// ������ɫ
	CBrush m_brBk2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DLG_ERP_WORK)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DLG_ERP_WORK)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ERP_WORK_H__9508D9CC_28D9_4762_AD1C_AFADC5E7D226__INCLUDED_)
