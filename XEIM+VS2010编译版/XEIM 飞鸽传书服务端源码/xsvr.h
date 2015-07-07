/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// xsvr.h : main header file for the XSVR application
//

#if !defined(AFX_XSVR_H__786C0284_9A06_4AE9_AEA4_04BF85466A65__INCLUDED_)
#define AFX_XSVR_H__786C0284_9A06_4AE9_AEA4_04BF85466A65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXsvrApp:
// See xsvr.cpp for the implementation of this class
//

class CXsvrApp : public CWinApp
{
public:
	void Unlock();
	void Lock();
	CXsvrApp();
	CRITICAL_SECTION g_cs;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXsvrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXsvrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSVR_H__786C0284_9A06_4AE9_AEA4_04BF85466A65__INCLUDED_)
