/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
#if !defined(AFX_XTREECTRL_H__9AE6058A_B921_4B74_9E6A_B6C6A0E45A90__INCLUDED_)
#define AFX_XTREECTRL_H__9AE6058A_B921_4B74_9E6A_B6C6A0E45A90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXTreeCtrl window

class CXTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CXTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTreeCtrl)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTREECTRL_H__9AE6058A_B921_4B74_9E6A_B6C6A0E45A90__INCLUDED_)
