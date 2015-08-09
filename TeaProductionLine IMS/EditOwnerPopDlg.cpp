// EditOwnerPopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditOwnerPopDlg.h"
#include "afxdialogex.h"


// CEditOwnerPopDlg �Ի���

IMPLEMENT_DYNAMIC(CEditOwnerPopDlg, CDialog)

CEditOwnerPopDlg::CEditOwnerPopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditOwnerPopDlg::IDD, pParent)
{

}

CEditOwnerPopDlg::~CEditOwnerPopDlg()
{
}

void CEditOwnerPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED1_EDITOWNER_POPDLG, m_editOwerName);

	DDX_Control(pDX, IDC_ED2_EDITOWNER_POPDLG, m_editOwerCode);
	DDX_Control(pDX, IDC_ED3_EDITOWNER_POPDLG, m_editOwerPasswd);
	DDX_Control(pDX, IDC_ED4_EDITOWNER_POPDLG, m_editDescription);
}


BEGIN_MESSAGE_MAP(CEditOwnerPopDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditOwnerPopDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditOwnerPopDlg ��Ϣ�������


void CEditOwnerPopDlg::OnBnClickedOk()
{
	CString name, code, passwd, description;
	m_editOwerName.GetWindowText(name);
	m_editOwerCode.GetWindowText(code);
	m_editOwerPasswd.GetWindowText(passwd);
	m_editDescription.GetWindowText(description);

	m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserName = name;
	m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserCode = code;
	m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserPasswd = passwd;
	m_pDataProvider->m_vectUser[m_nSelectedItem].m_strNote = description;

	int Id = m_pDataProvider->m_vectUser[m_nSelectedItem].m_UserId;
	m_pDataProvider->UpdateTableItem(CDataProvider::tbUser, Id);

	CDialog::OnOK();
}


BOOL CEditOwnerPopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editOwerName.SetWindowText(m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserName);
	m_editOwerCode.SetWindowText(m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserCode);
	m_editOwerPasswd.SetWindowText(m_pDataProvider->m_vectUser[m_nSelectedItem].m_strUserPasswd);
	m_editDescription.SetWindowText(m_pDataProvider->m_vectUser[m_nSelectedItem].m_strNote);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALS
	
}


void CEditOwnerPopDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
