/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// DLG_ERP_MESSAGE.cpp : implementation file
//

#include "stdafx.h"
#include "client02.h"
#include "DLG_ERP_MESSAGE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLG_ERP_MESSAGE dialog


DLG_ERP_MESSAGE::DLG_ERP_MESSAGE(CWnd* pParent /*=NULL*/)
	: CDialog(DLG_ERP_MESSAGE::IDD, pParent)
{
	//{{AFX_DATA_INIT(DLG_ERP_MESSAGE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DLG_ERP_MESSAGE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DLG_ERP_MESSAGE)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DLG_ERP_MESSAGE, CDialog)
	//{{AFX_MSG_MAP(DLG_ERP_MESSAGE)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLG_ERP_MESSAGE message handlers

void DLG_ERP_MESSAGE::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void DLG_ERP_MESSAGE::SetMessage(CString strMsg)
{
	int nSize = m_vecMessage.size();
	CTime ctNow = CTime::GetCurrentTime();
	CString strMessage;
	// ��Ϣ ������ �� ����ʱ��
	strMessage.Format(_T("��[%d]�� - %s\r\n%s"), nSize+1, 
		ctNow.Format(_T("%H:%M:%S")),
		strMsg);

//	strMessage.Replace("#", "xxx");
	m_vecMessage.push_back((LPCTSTR)strMessage);
	// ��ʾ��Ϣ
	SetDlgItemText(IDC_EDIT1, strMessage);
	// ��ʾ��Ϣ����
	CString strSize;
	strSize.Format("����[%d]��ϵͳ��Ϣ��", nSize+1);
	SetDlgItemText(IDC_STATIC_SIZE, strSize);

	m_iPointer = m_vecMessage.end();
	m_iPointer --;

	// �����Ϣ��ֹһ��
	if (nSize > 0)
	{
		GetDlgItem(IDC_BACK)->EnableWindow();
	}
}

void DLG_ERP_MESSAGE::OnBack() 
{
	// TODO: Add your control notification handler code here
	// ��һ����¼
	m_iPointer --;

	string str = *m_iPointer;
	SetDlgItemText(IDC_EDIT1, str.c_str());
	
	if (! GetDlgItem(IDC_NEXT)->IsWindowEnabled())
	{
		GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
	}

	// ����ǵ�һ����¼
	if (m_iPointer == m_vecMessage.begin())
	{
		GetDlgItem(IDC_BACK)->EnableWindow(FALSE);
	}
}

void DLG_ERP_MESSAGE::OnNext() 
{
	// TODO: Add your control notification handler code here
	m_iPointer ++;

	string str = *m_iPointer;
	SetDlgItemText(IDC_EDIT1, str.c_str());
	if (! GetDlgItem(IDC_BACK)->IsWindowEnabled())
	{
		GetDlgItem(IDC_BACK)->EnableWindow(TRUE);
	}

	// ��������һ��
	m_iPointer ++;
	if (m_iPointer == m_vecMessage.end())
	{
		GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);

	}

	m_iPointer --;
}

BOOL DLG_ERP_MESSAGE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��һ����ť
	GetDlgItem(IDC_BACK)->EnableWindow(FALSE);
	// ��һ����ť
	GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);

	// ��ʼʱ�����κ���Ϣ��ʾ��������Ϣ
	SetDlgItemText(IDC_EDIT1, "- ������Ϣ");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
