/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// XLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client02.h"
#include "XLoginDlg.h"
#include "client02Dlg.h"
#include "process.h"
#include "SetDlg.h"
#include "../xmsg/xtype.h"
#include "../xmsg/xdef.h"
#include "xfun.h"
#include "INI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXLoginDlg dialog

CXLoginDlg::CXLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXLoginDlg)
	m_bRemember = FALSE;
	m_bAuto = FALSE;
	//}}AFX_DATA_INIT
}


void CXLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXLoginDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bRemember);
	DDX_Check(pDX, IDC_CHECK2, m_bAuto);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CXLoginDlg)
	ON_BN_CLICKED(IDC_SETTING, OnSetting)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_WM_DESTROY()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXLoginDlg message handlers

void CXLoginDlg::OnSetting() 
{
	// TODO: Add your control notification handler code here
	CSetDlg dlg(this);
	if (IDOK == dlg.DoModal())
	{
		// ����û������ļ�
		char szFileName[_MAX_PATH];
		GetProgramDirectory(szFileName);
		strcat_s(szFileName, MAX_PATH*sizeof(char),"info.ini");

		CIniReader iniReader(szFileName);
		if (iniReader.sectionExists("xeim_server_info"))
		{
		//	m_strSvr = iniReader.getKeyValue("server_addr", "xeim_server_info");
			iniReader.setKey(((CClient02Dlg*)AfxGetMainWnd())->m_strSvr, "server_addr", "xeim_server_info");
		}
		else
		{
			iniReader.setKey("", "server_addr", "xeim_server_info");
		}
	}
}

void CXLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	ShowWindow(SW_HIDE);
	CString user;
	CString pass;
	GetDlgItemText(IDC_EDIT1, user);
	GetDlgItemText(IDC_EDIT2, pass);


	if (((CClient02Dlg*)AfxGetMainWnd())->Init())
	{
		SOCKET m_sock = ((CClient02Dlg*)AfxGetMainWnd())->m_sock;
		XMSG message;
		XUserDetail xLogin;
	//	xAcc.SetAccount((LPCTSTR)user, (LPCTSTR)pass);
		xLogin.SetUID((LPCTSTR)user);
		xLogin.SetUPassword((LPCTSTR)pass);
		xLogin.SetUNickName("");
		xLogin.OnLine();

		message.m_nMessage = XEIMMSG_LOGIN;
		message.SetData((char*)&xLogin, sizeof(xLogin));
	//	message.SetBuf((char*)&xAcc, sizeof(XMSG_UserINFO));

		int ret = ::send(m_sock, (LPCTSTR)message.GetBuffer(), message.GetBufferLength(), 0);
		if (SOCKET_ERROR == ret || 0 == ret)
		{
			AfxMessageBox("���Ͳ��ɹ���");
			return;
		}
		// ����¼��Ҫ����ϵͳ�����ļ�
		UpdateIniFile((LPCTSTR)user, (LPCTSTR)pass);

		((CClient02Dlg*)AfxGetMainWnd())->m_strUID = user;
		((CClient02Dlg*)AfxGetMainWnd())->m_strUPSW = pass;

		CDialog::OnOK();
		return;
	}
	else
	{
		CString strError;
		strError.Format("%s", ((CClient02Dlg*)AfxGetMainWnd())->m_strLastError);
		::MessageBox(GetSafeHwnd(), strError, "��¼ʧ��", MB_OK | MB_ICONERROR);
		ShowWindow(SW_SHOW);
		return;
	}

	CDialog::OnCancel();
}

BOOL CXLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

//	SetDlgItemText(IDC_EDIT1, "aaa");
//	SetDlgItemText(IDC_EDIT2, "118899");
	m_brush.CreateSolidBrush(RGB(255,255,255));

	// ����û������ļ�
	char szFileName[_MAX_PATH];
	GetProgramDirectory(szFileName);
	strcat_s(szFileName, MAX_PATH*sizeof(char),"info.ini");

	CIniReader iniReader(szFileName);
	if (iniReader.sectionExists("xeim_user_info"))
	{
		// �ж��Ƿ񡮼�ס���롯
		CString value = iniReader.getKeyValue("remember_me", "xeim_user_info");
		int iValue = atoi((LPCTSTR)value);
		if (iValue == 1)
		{
			m_bRemember = TRUE;
		}
		// �ж��Ƿ��Զ���¼��
		value = iniReader.getKeyValue("autorun", "xeim_user_info");
		iValue = atoi((LPCTSTR)value);
		if (iValue == 1)
		{
			m_bAuto = TRUE;
		}
		// �Զ���ȡ�û���
		value = iniReader.getKeyValue("username", "xeim_user_info");
		SetDlgItemText(IDC_EDIT1, value);

		// ����Ǽ�ס���룬�Ͱ������ȡ����
		if (m_bRemember)
		{
			value = iniReader.getKeyValue("password", "xeim_user_info");
			SetDlgItemText(IDC_EDIT2, value);
		}
		else
		{
			m_bAuto = FALSE;
			GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		}

		UpdateData(FALSE);
	}
	else
	{
		iniReader.setKey("0", "remember_me", "xeim_user_info");
		iniReader.setKey("0", "autorun", "xeim_user_info");
		iniReader.setKey("", "username", "xeim_user_info");
		iniReader.setKey("", "password", "xeim_user_info");
	}

	// �����û���������
	if (m_bAuto)
		OnOK();

//	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CHECK2)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CXLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return m_brush;
}

// ���˼�ס����һ��
void CXLoginDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (! m_bRemember)
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		m_bAuto = FALSE;
		UpdateData();
	}
	else
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow();
	}
}

// �����Զ���¼һ��
void CXLoginDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CXLoginDlg::UpdateIniFile(LPCTSTR lpszUser, LPCTSTR lpszPass)
{
	// ����û������ļ�
	char szFileName[_MAX_PATH];
	GetProgramDirectory(szFileName);
	strcat_s(szFileName, MAX_PATH*sizeof(char),"info.ini");

	CIniReader iniReader(szFileName);
	if (m_bRemember)
	{
		iniReader.setKey("1", "remember_me", "xeim_user_info");
		iniReader.setKey(lpszPass, "password", "xeim_user_info");
	}
	else
	{
		iniReader.setKey("0", "remember_me", "xeim_user_info");
		iniReader.setKey("", "password", "xeim_user_info");
	}
	if (m_bAuto)
	{
		iniReader.setKey("1", "autorun", "xeim_user_info");
	}
	else
	{
		iniReader.setKey("0", "autorun", "xeim_user_info");
	}
	iniReader.setKey(lpszUser, "username", "xeim_user_info");
//	iniReader.setKey(lpszPass, "password", "xeim_user_info");
}

void CXLoginDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CXLoginDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDCtl)
	{
	case IDC_SETTING:
	case IDOK:
		{
			CDC dc;

			dc.Attach(lpDrawItemStruct->hDC);
			RECT rect;
			rect= lpDrawItemStruct->rcItem;
			
			dc.Draw3dRect(&rect,RGB(236, 243, 246),RGB(236, 243, 246));
		//	dc.Draw3dRect(&rect,RGB(255, 255, 255),RGB(255, 255, 255));
			dc.FillSolidRect(&rect,RGB(236, 243, 246));
		//	dc.FillSolidRect(&rect,RGB(255, 255, 255));
			UINT state=lpDrawItemStruct->itemState;

			if((state & ODS_SELECTED))
			{
				dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);

			}
			else
			{
				dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
			}

			dc.SetBkColor(RGB(236, 243, 246));
		//	dc.SetBkColor(RGB(255, 255, 255));
			//dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
			dc.SetTextColor(RGB(25, 79, 149));


			TCHAR buffer[MAX_PATH];
			ZeroMemory(buffer,MAX_PATH );
			::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH);
			dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			
			dc.Detach();
		}
		break;
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
