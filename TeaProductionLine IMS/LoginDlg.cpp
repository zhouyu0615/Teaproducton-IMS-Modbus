// LoginDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "resource.h"
// CLoginDlg �Ի���
long  CLoginDlg::LoginUser_CurrentPermissionLevel ;		//������̬ȫ�ֱ������û�Ȩ�ޱ�־///
long  CLoginDlg::LoginUser_CurrentId;				   //������̬ȫ�ֱ������û�ID��־///
IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USERNAME, m_LoginUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_EditPasswd);
	DDX_Control(pDX, IDC_CHECK_PASSWD, CheckPassWd);
	DDX_Control(pDX, IDC_CHECK_AUTOLOGIN, CheckAutoLogin);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_USERNAME, &CLoginDlg::OnCbnSelchangeComboUsername)
	ON_CBN_SELCHANGE(IDC_COMBO_USERRIGHT, &CLoginDlg::OnCbnSelchangeComboUserright)
END_MESSAGE_MAP()

// CLoginDlg ��Ϣ�������
BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//	///��ʼ��Ȩ����Ͽ�
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("����Ա"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("����Ա"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->SetCurSel(0);		//Ĭ��Ϊ����Ա///
//	m_LoginDataProvider->ReadLoginUserFormDatabase();					//��ȡ���ݿ�///
	for (int i = 0; i < m_LoginDataProvider->m_vectLoginUser.size(); i++)
	{
		if (m_LoginDataProvider->m_vectLoginUser[i].m_PermissionLevel == 0)
		{
								  //������Ա�����Զ���ʾ�������б����///
			m_LoginUserName.AddString(m_LoginDataProvider->m_vectLoginUser[i].m_strLoginName);
		}
	}
	return TRUE;				 // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//ѡ���û�Ȩ�޹���Ա�Ͳ���Ա����Ӧ����///
void CLoginDlg::OnCbnSelchangeComboUserright()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString Super;
	GetDlgItem(IDC_COMBO_USERRIGHT)->GetWindowText(LoginUser_PermissionLevel);
	//m_LoginDataProvider->ReadLoginUserFormDatabase();
	m_LoginUserName.ResetContent();				//�Ƚ��������û������///
	if (LoginUser_PermissionLevel == _T("����Ա"))
	{
		for (int i = 0; i < m_LoginDataProvider->m_vectLoginUser.size();i++)
		{
			if (m_LoginDataProvider->m_vectLoginUser[i].m_PermissionLevel == 1)
			{
				m_LoginUserName.AddString(m_LoginDataProvider->m_vectLoginUser[i].m_strLoginName);
			}
		}
		m_LoginUserName.AddString(_T("Super"));
	}
	else
	{
		for (int i = 0; i < m_LoginDataProvider->m_vectLoginUser.size(); i++)
		{
			if (m_LoginDataProvider->m_vectLoginUser[i].m_PermissionLevel == 0)
			{
				m_LoginUserName.AddString(m_LoginDataProvider->m_vectLoginUser[i].m_strLoginName);
			}
		}
	}
	CheckAutoLogin.SetCheck(0);
	CheckPassWd.SetCheck(0);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T(""));
}

//�����༭������ѡ�в�ͬ��ס������û���ʱ����Ӧ������Ӧ����///
void CLoginDlg::OnCbnSelchangeComboUsername()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_COMBO_USERNAME)->GetWindowText(LoginUser.m_strLoginName);
	//m_LoginDataProvider->ReadLoginUserFormDatabase();
	for (int i = 0; i < m_LoginDataProvider->m_vectLoginUser.size(); i++)
	{
		//��ѡ���û���ס���룬���Զ���ʾ������///
		if (LoginUser.m_strLoginName == m_LoginDataProvider->m_vectLoginUser[i].m_strLoginName)
		{
			if (m_LoginDataProvider->m_vectLoginUser[i].m_IsRememberPasswd == 1)
			{
				GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_LoginDataProvider->m_vectLoginUser[i].m_strLoginPassWd);	//��ʾ����///
				CheckPassWd.SetCheck(TRUE);
			}
			else
			{
				GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T(""));
				CheckPassWd.SetCheck(0);
			}
			if (m_LoginDataProvider->m_vectLoginUser[i].m_IsAutoLogin)
				CheckAutoLogin.SetCheck(true);
			else
				CheckAutoLogin.SetCheck(0);
			break;
		}
	}
}

//��¼��ť����Ϣ��Ӧ����///
void CLoginDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������_
	
	int UserNum ;										//         ///
	//m_LoginDataProvider->ReadUserFromDatabase();		//���������ȡ����///
	GetDlgItem(IDC_COMBO_USERNAME)->GetWindowText(LoginUser.m_strLoginName);
	GetDlgItem(IDC_COMBO_USERRIGHT)->GetWindowText(LoginUser_PermissionLevel);
	GetDlgItem(IDC_COMBO_USERNAME)->GetWindowText(LoginUser.m_strLoginName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(LoginUser.m_strLoginPassWd);
	if (CheckPassWd.GetCheck())
	{
		LoginUser.m_IsRememberPasswd = 1;
	}
	else
	{
		LoginUser.m_IsRememberPasswd = 0;
	}
	if (CheckAutoLogin.GetCheck())					//�ж��Ƿ�ѡ���Զ���¼///
	{
		LoginUser.m_IsAutoLogin = 1;
	}
	else
	{
		LoginUser.m_IsAutoLogin = 0;
	}
	if (LoginUser.m_strLoginName.IsEmpty())
	{
		AfxMessageBox(_T("�û�������Ϊ��, ����������!"));
		return;
	}
	if (LoginUser.m_strLoginPassWd.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ��, ����������!"));
		return;
	}
	//Super�û���¼//////////////////////////////////////////////////////////////////////////
	if (LoginUser.m_strLoginName  == _T("Super"))          //����ǳ����û�//
	{
		if (LoginUser.m_strLoginPassWd == _T("111111"))
		{
			LoginUser_CurrentPermissionLevel = 1;
			LoginUser_CurrentId = -1;
			CDialog::OnOK();
			return;
		}
		else
		{
			AfxMessageBox(_T("�û����벻��ȷ������������"));
			return;
		}
	}
	for ( UserNum = 0;UserNum < m_LoginDataProvider->m_vectLoginUser.size();UserNum++)
	{
		if (LoginUser.m_strLoginName == m_LoginDataProvider->m_vectLoginUser[UserNum].m_strLoginName)
		{
			if (LoginUser.m_strLoginPassWd == m_LoginDataProvider->m_vectLoginUser[UserNum].m_strLoginPassWd)
			{
				LoginUser_CurrentId = m_LoginDataProvider->m_vectLoginUser[UserNum].m_Id;		//��ס��ǰ��¼�û���ID///
				LoginUser_CurrentPermissionLevel = m_LoginDataProvider->m_vectLoginUser[UserNum].m_PermissionLevel;	//��ס�û�Ȩ��///			
				m_LoginDataProvider->m_vectLoginUser[UserNum].m_LastLoginInTime = CTime::GetCurrentTime();	//��ס�û���¼ʱ��///
				//���û��Զ���¼���ס���뷢���޸�,��������ݿ�///
				if ((m_LoginDataProvider->m_vectLoginUser[UserNum].m_IsAutoLogin != LoginUser.m_IsAutoLogin) ||
					(m_LoginDataProvider->m_vectLoginUser[UserNum].m_IsRememberPasswd != LoginUser.m_IsRememberPasswd))
				{
					m_LoginDataProvider->m_vectLoginUser[UserNum].m_IsAutoLogin = LoginUser.m_IsAutoLogin;	//��ס�Ƿ��Զ���¼///
					m_LoginDataProvider->m_vectLoginUser[UserNum].m_IsRememberPasswd = LoginUser.m_IsRememberPasswd;//��ס�Ƿ��ס����///
					m_LoginDataProvider->UpdateTableItem(m_LoginDataProvider->tbLoginUser, LoginUser_CurrentId); //�������ݿ�///
				}
                m_LoginDataProvider->UpdateUserLoginTime(LoginUser_CurrentId);				//�����û���¼ʱ��///
				if (LoginUser.m_IsAutoLogin == 1)										//�����û�ѡ���Զ���¼���������û����Զ���¼ȡ��///
				{
					for (int i = 0; i < m_LoginDataProvider->m_vectLoginUser.size(); i++)
					{
						if ((i != UserNum) && (m_LoginDataProvider->m_vectLoginUser[i].m_IsAutoLogin == 1))
						{
							m_LoginDataProvider->m_vectLoginUser[i].m_IsAutoLogin = 0;
							m_LoginDataProvider->UpdateTableItem(m_LoginDataProvider->tbLoginUser, m_LoginDataProvider->m_vectLoginUser[i].m_Id); //�������ݿ�///
						}
					}
				}
				
				CDialog::OnOK();
				return;
			}
			else
			{
				AfxMessageBox(_T("�û����벻��ȷ������������"));
				return;
			}
		}		
	}
}
//ȡ����ť����Ϣ��Ӧ����///
void CLoginDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
	CDialog::OnCancel();
	
}

