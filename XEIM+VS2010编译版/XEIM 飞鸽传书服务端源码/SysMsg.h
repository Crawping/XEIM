#pragma once
#include "afxwin.h"
#include <string>
using namespace std;

// CSysMsg �Ի���

class CSysMsg : public CDialog
{
	DECLARE_DYNAMIC(CSysMsg)

public:
	CSysMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysMsg();

// �Ի�������
	enum { IDD = IDD_DLG_SYSTEM_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_SysMsg;
	virtual BOOL OnInitDialog();

	string sMsg;
};
