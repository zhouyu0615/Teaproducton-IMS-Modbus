// UserManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "UserManageDlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"

// CUserManageDlg �Ի���

IMPLEMENT_DYNAMIC(CUserManageDlg, CDialog)

CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManageDlg::IDD, pParent)
{

}

CUserManageDlg::~CUserManageDlg()
{
}

void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialog)
	ON_BN_CLICKED(IDC_BT_ALLUSER, &CUserManageDlg::OnBnClickedBtAlluser)
	ON_BN_CLICKED(IDC_BT_EDITPASSWORD, &CUserManageDlg::OnBnClickedBtEditpassword)
	ON_BN_CLICKED(IDC_BT_LOGOUT, &CUserManageDlg::OnBnClickedBtLogout)
END_MESSAGE_MAP()


// CUserManageDlg ��Ϣ�������

//�����û���ť��Ӧ����//
void CUserManageDlg::OnBnClickedBtAlluser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//if (CMainDlg::s_nUserRight == 1)
	if (CLoginDlg::LoginUser_CurrentPermissionLevel)			//  ///
	{
		ShowWindow(SW_HIDE); 
		m_AllUserManageDlg.DoModal();
		ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox(_T("��û��Ȩ�޽��иò�����"));
}

//�޸����밴ť��Ӧ����//
void CUserManageDlg::OnBnClickedBtEditpassword()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (CLoginDlg::LoginUser_CurrentId==-1)
		AfxMessageBox(_T("�����û���Ϣ�����޸�"));
	else
	{
		ShowWindow(SW_HIDE);
		m_EditPasswordDlg.DoModal();
		ShowWindow(SW_SHOW);
	}
}

//�л��û���ť//
void CUserManageDlg::OnBnClickedBtLogout()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
