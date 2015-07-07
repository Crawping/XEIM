// SysMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "xsvr.h"
#include "SysMsg.h"


// CSysMsg �Ի���

IMPLEMENT_DYNAMIC(CSysMsg, CDialog)

CSysMsg::CSysMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysMsg::IDD, pParent)
{

}

CSysMsg::~CSysMsg()
{
}

void CSysMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SYSMSG, m_SysMsg);
}


BEGIN_MESSAGE_MAP(CSysMsg, CDialog)
	ON_BN_CLICKED(IDOK, &CSysMsg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSysMsg ��Ϣ�������

void CSysMsg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sText;
	GetDlgItemText(IDC_EDIT_SYSMSG, sText);
	sMsg = (LPCTSTR)sText;

	OnOK();
}

BOOL CSysMsg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SysMsg.SetWindowText(_T("�ڴ˱༭ϵͳ��Ϣ!"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
