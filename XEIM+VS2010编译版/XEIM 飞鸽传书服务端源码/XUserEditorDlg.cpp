/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// XUserEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xsvr.h"
#include "XUserEditorDlg.h"
#include "xsvrDlg.h"
#include "../xmsg/xtype.h"
#include <string>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXUserEditorDlg dialog


CXUserEditorDlg::CXUserEditorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CXUserEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXUserEditorDlg)
	m_strUID = _T("");
	m_strPassword = _T("");
	m_strNickName = _T("");
	m_strGroup = _T("");
	m_bModify = FALSE;
	m_strUMobile = _T("");
	//}}AFX_DATA_INIT
}


void CXUserEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXUserEditorDlg)
	DDX_Control(pDX, IDC_TREE1, m_treeUserList);
	DDX_Text(pDX, IDC_EDIT1, m_strUID);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
	DDX_Text(pDX, IDC_EDIT3, m_strNickName);
	DDX_Text(pDX, IDC_EDIT4, m_strGroup);
	DDX_Text(pDX, IDC_EDIT_CELL, m_strUMobile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXUserEditorDlg, CDialog)
//{{AFX_MSG_MAP(CXUserEditorDlg)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_CHECK_INVERSE, OnCheckInverse)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CXUserEditorDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXUserEditorDlg message handlers

void CXUserEditorDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	CXsvrDlg *pDlg = (CXsvrDlg*)AfxGetMainWnd();
	
	if (! m_bModify)
	{
		if (m_strUID.IsEmpty())
		{
			GetDlgItem(IDC_EDIT1)->SetFocus();
			AfxMessageBox("�û�ID������д");
			return;
		}
		
		if (pDlg->XUserExisted((LPCTSTR)m_strUID))
		{
			GetDlgItem(IDC_EDIT1)->SetFocus();
			AfxMessageBox("�û�ID�Ѵ��ڣ����������롣");
			return;
		}
		
		if (m_strPassword.IsEmpty())
		{
			GetDlgItem(IDC_EDIT2)->SetFocus();
			AfxMessageBox("�û����������д");
			return;
		}
		
		if (m_strNickName.IsEmpty())
		{
			m_strNickName = m_strUID;
		}

		if (m_strGroup.IsEmpty())
		{
			m_strGroup = "����";
		}

		XUserDetail xUser;
		xUser.SetUID((LPCTSTR)m_strUID);
		xUser.SetUNickName((LPCTSTR)m_strNickName);
		xUser.SetUPassword((LPCTSTR)m_strPassword);
		xUser.SetUGroup((LPCTSTR)m_strGroup);

		// ���ظ���������
		pDlg->XUserAddNew(xUser, m_strUMobile);
	}
	else
	{
		XUserDetail xUser;
		xUser.SetUID((LPCTSTR)m_strUID);
		xUser.SetUNickName((LPCTSTR)m_strNickName);
		xUser.SetUPassword((LPCTSTR)m_strPassword);
		xUser.SetUGroup((LPCTSTR)m_strGroup);
		
		// ���ظ���������
		pDlg->XUserUpdate(xUser, m_strUMobile);
	}
	
	map<string, HTREEITEM>::iterator iGroup;
	for (iGroup = m_mapGroup.begin();
	iGroup != m_mapGroup.end(); iGroup ++)
	{
		CheckForChanging(iGroup->second);
	}
	
	string str;
	if (m_listContact.size() != 0)
	{
		int nSize = m_listContact.size();
		for (int i=0; i<nSize; i++)
		{
			str = m_listContact.front();
			m_listContact.pop_front();
			DeleteContact(str.c_str());
		}
	}
	
	m_listContact.clear();
	m_mapGroup.clear();
	CDialog::OnOK();
}

void CXUserEditorDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CXUserEditorDlg::SetData(XUserDetail &uDetail)
{
	m_strGroup = uDetail.GetUGroup();
	m_strNickName = uDetail.GetUNickName();
	m_strPassword = uDetail.GetUPassword();
	m_strUID = uDetail.GetUID();
	
	m_bModify = TRUE;
	
	return TRUE;
}

BOOL CXUserEditorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (m_bModify)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		SetDlgItemText(IDOK, "�޸�(&M)");
	}
	
	m_treeUserList.ModifyStyle(0,TVS_CHECKBOXES);
	m_treeUserList.SetItemHeight(16);
	
	// ��ȡ�û�����ϵ��
	GetUserContact();
	
	CXsvrDlg *pDlg = (CXsvrDlg*)GetParent();
	// �û� CTreeCtrl ͼ��
	m_treeUserList.SetImageList(& pDlg->m_ilUser, TVSIL_NORMAL);

	list<XUserDetail>::iterator iDetail;
	map<string, HTREEITEM>::iterator iGroup;
	XUserInfo xui;
	HTREEITEM hGroup;
	HTREEITEM hItem;
	list<string>::iterator iContact;

	for (iDetail = pDlg->m_listUserDetail.begin();
	iDetail != pDlg->m_listUserDetail.end(); ++iDetail)
	{
		iDetail->GetUserInfo(xui);
		
		// �Ȼ�ȡ�����沿����Ϣ�����ھ��������������򱣴档
		iGroup = m_mapGroup.find(xui.GetUGroup());
		if (iGroup == m_mapGroup.end())	// ������
		{	
			hGroup = m_treeUserList.InsertItem(xui.GetUGroup(), 1, 1);
			m_mapGroup.insert(pair<string,HTREEITEM>(xui.GetUGroup(), hGroup));
		}
		else // �����Ѵ���
		{
			hGroup = iGroup->second;
		}
		// ����UI
		hItem = m_treeUserList.InsertItem(xui.GetUID(), 2, 2, hGroup);
		iContact = find(m_listContact.begin(), m_listContact.end(), xui.GetUID());
		
		if (iContact != m_listContact.end())
		{
			m_treeUserList.SetCheck(hItem);
			//	SetParentCheck(hItem);
		}
		
	}
	for (iGroup = m_mapGroup.begin(); iGroup != m_mapGroup.end(); ++iGroup)
	{
		HTREEITEM hChild = m_treeUserList.GetChildItem(iGroup->second);
		/*	CString strc;
		strc.Format("%s %d", iGroup->first.c_str(), hChild);
		AfxMessageBox(strc);
		*/
		//	m_treeUserList.Expand(iGroup->second, TVE_EXPAND);
		SetParentCheck(hChild);
	}
	
	//	CString strbb;
	//	strbb.Format("%d", m_mapGroup.size());
	//	AfxMessageBox(strbb);
	// �Ը��û��ĺ��ѽ��д�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CXUserEditorDlg::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pt;
	UINT flag;
	BOOL bRoot;
	
	HTREEITEM hItem;
	GetCursorPos(&pt);
	m_treeUserList.ScreenToClient(&pt);   
	
	hItem = m_treeUserList.HitTest(pt, &flag);
	
	if (hItem == NULL)
	{
		*pResult = 0;
		return;
	}
	
	CString itemText = m_treeUserList.GetItemText(hItem);
	
	// �ж�ѡ���Ƿ�Ϊ����
	map<string, HTREEITEM>::iterator iGroup;
	iGroup = m_mapGroup.find((LPCTSTR)itemText);
	if (iGroup != m_mapGroup.end())
	{
		if (iGroup->second == hItem)
		{
			bRoot = TRUE;
			//		AfxMessageBox("ROOT");
		}
		else
		{
			bRoot = FALSE;
		}
	}
	else
	{
		bRoot = FALSE;
	} // end �ж�ѡ���Ƿ�Ϊ����
	
	if (flag & TVHT_ONITEMSTATEICON)
	{
		//		AfxMessageBox("TVHT_ONITEMSTATEICON");
		if (bRoot)		// ROOT
		{
			if (! m_treeUserList.GetCheck(hItem))
			{
				SetItemCheck(hItem, TRUE);
			}
			else
			{
				SetItemCheck(hItem, FALSE);
			}
		}
		else						// CHILD
		{
			if (m_treeUserList.GetCheck(hItem))
			{
				//			AfxMessageBox("aaaaa");
				HTREEITEM hParent = m_treeUserList.GetParentItem(hItem);
				if (m_treeUserList.GetCheck(hParent))
					m_treeUserList.SetCheck(hParent, FALSE);
			}
			else
			{
				SetParentCheck2(hItem);
			}
		}
		// ֻ�е��û�ѡ�񷽿�ʱ������Ҫ���ô˺�����������벻��Ҫ��
		m_treeUserList.SelectItem(hItem);
	}
	else if (flag & (TVHT_ONITEMICON | TVHT_ONITEMLABEL))
	{
		if (bRoot)
		{
			if (m_treeUserList.GetCheck(hItem))
			{
				m_treeUserList.SetCheck(hItem, FALSE);
				
				SetItemCheck(hItem, FALSE);
			}
			else
			{
				m_treeUserList.SetCheck(hItem);
				
				SetItemCheck(hItem, TRUE);
			}
		}
		else
		{
			if (m_treeUserList.GetCheck(hItem))
			{
				HTREEITEM hParent = m_treeUserList.GetParentItem(hItem);
				if (hParent == NULL)
					return;
				if (m_treeUserList.GetCheck(hParent))
					m_treeUserList.SetCheck(hParent, FALSE);
				
				m_treeUserList.SetCheck(hItem, FALSE);
				//	AfxMessageBox(m_treeUserList.GetItemText(hParent));
			}
			else
			{
				m_treeUserList.SetCheck(hItem);
				SetParentCheck(hItem);
			}
		}
	}
	
	*pResult = 0;
}


void CXUserEditorDlg::SetItemCheck(HTREEITEM hParent, BOOL bCheck)
{
	HTREEITEM hChild = m_treeUserList.GetChildItem(hParent);
	
	m_treeUserList.SetCheck(hChild, bCheck);
	
	while(hChild = m_treeUserList.GetNextSiblingItem(hChild))
	{
		m_treeUserList.SetCheck(hChild, bCheck);
	}
}


void CXUserEditorDlg::SetParentCheck(HTREEITEM hItem)
{
	HTREEITEM hParent;
	BOOL bCheckParent = FALSE;

	if (hItem != NULL)
	{
		hParent = m_treeUserList.GetParentItem(hItem);
		HTREEITEM hChild = m_treeUserList.GetChildItem(hParent);

		while (hChild)
		{
			if (! m_treeUserList.GetCheck(hChild))
				break;
			hChild = m_treeUserList.GetNextSiblingItem(hChild);
		}
		if (hChild == NULL)
		{
			m_treeUserList.SetCheck(hParent);
		}
	}
}

void CXUserEditorDlg::SetParentCheck2(HTREEITEM hItem)
{
	HTREEITEM hParent;
	int i=0;
	BOOL bCheckParent = FALSE;

	if (hItem != NULL)
	{
		hParent = m_treeUserList.GetParentItem(hItem);
		HTREEITEM hChild = m_treeUserList.GetChildItem(hParent);

		while (hChild)
		{
			if (hChild == hItem)
			{
				hChild = m_treeUserList.GetNextSiblingItem(hChild);
				continue;
			}
			if (! m_treeUserList.GetCheck(hChild))
				break;

			hChild = m_treeUserList.GetNextSiblingItem(hChild);
		}
		if (hChild == NULL)
		{
			m_treeUserList.SetCheck(hParent);
		}
	}
}

void CXUserEditorDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (TVE_EXPAND == pNMTreeView->action)
		m_treeUserList.SetItemImage(pNMTreeView->itemNew.hItem, 0, 0);
	else
		m_treeUserList.SetItemImage(pNMTreeView->itemNew.hItem, 1, 1);
	*pResult = 0;
}

// ��ȡ�û�������Ϣ
void CXUserEditorDlg::GetUserContact()
{
	// ����ܾ��
	CXsvrDlg *pDlg = (CXsvrDlg*)GetParent();
	// SQL ��ѯ
	char * szSQL = "SELECT * FROM x_contact where uid='%s'";
	char buf[512];
	sprintf(buf, szSQL, (LPCTSTR)m_strUID);
	
	// ADO ����ģ��
	_RecordsetPtr pRs;
	pRs.CreateInstance(__uuidof(Recordset));
	
	// ִ����Ӧ��������� Ϊ��ʱ���쳣
	try
	{
		pRs->Open(buf,
			pDlg->m_pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		
		// ������ݿ��ǿհ׵�
		if (! pRs->adoEOF)
		{
			// ��ȡ����ʾ���ݿ������Ϣ
			
			while (!pRs->adoEOF)
			{
				variant_t var;
				
				// ��ȡ�û��ǳ�
				var = pRs->GetCollect(_variant_t("xucontact"));
				if (var.vt != VT_NULL)
				{
					m_listContact.push_back((LPCTSTR)_bstr_t(var));
					//		AfxMessageBox((LPCTSTR)_bstr_t(var));
				}
				pRs->MoveNext();
			}
		}
		else
		{
			//			AfxMessageBox("��ϵ�����ݱ����κμ�¼��");
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	
	pRs->Close();
	pRs.Release();
} // end ��ȡ�û�������Ϣ


void CXUserEditorDlg::CheckForChanging(HTREEITEM hParent)
{
	HTREEITEM hChild = m_treeUserList.GetChildItem(hParent);
	list<string>::iterator iContact;
	
	string str = m_treeUserList.GetItemText(hChild);
	// �������
	if (m_treeUserList.GetCheck(hChild))
	{
		iContact = find(m_listContact.begin(), m_listContact.end(), str);
		// �ú����Ѵ���
		if (iContact != m_listContact.end())
		{
			// ��������ϵ���б���ɾ��
			m_listContact.erase(iContact);
		}
		else
		{
			AddNewContact(str.c_str());
		}
	}
	
	while(hChild = m_treeUserList.GetNextSiblingItem(hChild))
	{
		str = m_treeUserList.GetItemText(hChild);
		// �������
		if (m_treeUserList.GetCheck(hChild))
		{
			string str = m_treeUserList.GetItemText(hChild);
			iContact = find(m_listContact.begin(), m_listContact.end(), str);
			// �ú����Ѵ���
			if (iContact != m_listContact.end())
			{
				// ��������ϵ���б���ɾ��
				m_listContact.erase(iContact);
			}
			else
			{
				AddNewContact(str.c_str());
			}
		}
	}
}

// ����ϵ��ɾ��
void CXUserEditorDlg::DeleteContact(LPCTSTR szUID)
{
	char buf[256];
	
	// ����ܾ��
	CXsvrDlg *pDlg = (CXsvrDlg*)GetParent();
	// SQL ��ѯ
	sprintf(buf, "DELETE FROM x_contact WHERE xucontact='%s' AND uid='%s'", szUID, (LPCTSTR)m_strUID);

	try
	{
		_variant_t vAffected;
		pDlg->m_pConn->CursorLocation = adUseClient;
		pDlg->m_pConn->Execute(buf, &vAffected, adExecuteNoRecords);
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
	}
}

// ����µ���ϵ��
void CXUserEditorDlg::AddNewContact(LPCTSTR szUID)
{
	char buf[256];
	
	// ����ܾ��
	CXsvrDlg *pDlg = (CXsvrDlg*)GetParent();
	// SQL ��ѯ
	sprintf(buf, "INSERT INTO x_contact(uid,xucontact) VALUES('%s','%s')",
		(LPCTSTR)m_strUID, szUID);
	//	AfxMessageBox(buf);
	
	try
	{
		_variant_t vAffected;
		pDlg->m_pConn->CursorLocation = adUseClient;
		pDlg->m_pConn->Execute(buf, &vAffected, adExecuteNoRecords);
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
	}

	// �ж����Ƿ�Ҳ�ǶԷ��ĺ���
	sprintf(buf, "SELECT * FROM x_contact WHERE uid='%s' AND xucontact='%s'", szUID, (LPCTSTR)m_strUID);
	
	// ADO ����ģ��
	_RecordsetPtr pRs;
	pRs.CreateInstance(__uuidof(Recordset));
	
	try
	{
		pRs->Open(buf,
			pDlg->m_pConn.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
		
		// ������ݿ��ǿհ׵�
		if (pRs->adoEOF)
		{
			//	AfxMessageBox("aaaa");
			pRs->AddNew(); 
			pRs->Fields->GetItem("uid")->Value=_variant_t(szUID);
			pRs->Fields->GetItem("xucontact")->Value=_variant_t((LPCTSTR)m_strUID); 
			pRs->Update();
			// ��ȡ����ʾ���ݿ������Ϣ
			
			/*			while (!pRs->adoEOF)
			{
			variant_t var;
			
			  // ��ȡ�û��ǳ�
			  var = pRs->GetCollect(_variant_t("xucontact"));
			  if (var.vt != VT_NULL)
			  {
			  m_listContact.push_back((LPCTSTR)_bstr_t(var));
			  //		AfxMessageBox((LPCTSTR)_bstr_t(var));
			  }
			  pRs->MoveNext();
		}*/
		}
		else
		{
			//			AfxMessageBox("��ϵ�����ݱ����κμ�¼��");
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
	}
	pRs->Close();
	pRs.Release();
}

// ȫѡ
void CXUserEditorDlg::OnCheckAll() 
{
	// TODO: Add your control notification handler code here
	if (((CButton*)GetDlgItem(IDC_CHECK_ALL))->GetCheck())
	{
		UncheckAll();
		InverseAll();
	}
	else
	{
		UncheckAll();
	}
}

// ��ѡ
void CXUserEditorDlg::OnCheckInverse() 
{
	// TODO: Add your control notification handler code here
	if (((CButton*)GetDlgItem(IDC_CHECK_INVERSE))->GetCheck())
	{
		InverseAll();
	}
	else
	{
		InverseAll();
	}
}

void CXUserEditorDlg::UncheckAll()
{
	map<string, HTREEITEM>::iterator iGroup;
	for (iGroup = m_mapGroup.begin();
	iGroup != m_mapGroup.end(); iGroup ++)
	{
		if (m_treeUserList.GetCheck(iGroup->second))
		{
			m_treeUserList.SetCheck(iGroup->second, FALSE);
		}

		HTREEITEM hChild = m_treeUserList.GetChildItem(iGroup->second);

		string str = m_treeUserList.GetItemText(hChild);
		// �������
		if (m_treeUserList.GetCheck(hChild))
		{
			m_treeUserList.SetCheck(hChild, FALSE);
		}

		while(hChild = m_treeUserList.GetNextSiblingItem(hChild))
		{
			str = m_treeUserList.GetItemText(hChild);
			// �������
			if (m_treeUserList.GetCheck(hChild))
			{
				m_treeUserList.SetCheck(hChild, FALSE);
			}
		}
	}
}

void CXUserEditorDlg::InverseAll()
{
	BOOL bCheck;
	map<string, HTREEITEM>::iterator iGroup;
	map<string, HTREEITEM>::iterator _END;
	_END = m_mapGroup.end();

	for (iGroup = m_mapGroup.begin();
	iGroup != _END; iGroup ++)
	{
		bCheck = TRUE;
		HTREEITEM hChild = m_treeUserList.GetChildItem(iGroup->second);

		string str = m_treeUserList.GetItemText(hChild);
		// �������
		if (m_treeUserList.GetCheck(hChild))
		{
			bCheck = FALSE;
			m_treeUserList.SetCheck(hChild, FALSE);
		}
		else
		{
			m_treeUserList.SetCheck(hChild);
		}

		while(hChild = m_treeUserList.GetNextSiblingItem(hChild))
		{
			str = m_treeUserList.GetItemText(hChild);
			// �������
			if (m_treeUserList.GetCheck(hChild))
			{
				bCheck = FALSE;
				m_treeUserList.SetCheck(hChild, FALSE);
			}
			else
			{
				m_treeUserList.SetCheck(hChild);
			}
		}

		if (bCheck == FALSE)
		{
		//	AfxMessageBox(m_treeUserList.GetItemText(iGroup->second));
		}
		m_treeUserList.SetCheck(iGroup->second, bCheck);
	}
}

void CXUserEditorDlg::SetMobile(LPCTSTR szMobile)
{
	m_strUMobile = szMobile;
}

void CXUserEditorDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
