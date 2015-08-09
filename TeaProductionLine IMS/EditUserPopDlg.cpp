// EditUserPopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "AllUserManageDlg.h"
#include "EditUserPopDlg.h"
#include "afxdialogex.h"


// CEditUserPopDlg �Ի���


IMPLEMENT_DYNAMIC(CEditUserPopDlg, CDialog)

CEditUserPopDlg::CEditUserPopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditUserPopDlg::IDD, pParent)
	, EditUserId(0)
	, ManagerId(0)
{

}

CEditUserPopDlg::~CEditUserPopDlg()
{
}

void CEditUserPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditUserPopDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditUserPopDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CEditUserPopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ѡ���û���Ϣ�Զ���ʾ���޸���Ϣ�Ŀ���///
	for (int i = 0; i < m_pDataProvider->m_vectLoginUser.size(); i++)
	{
		if (EditUserId == m_pDataProvider->m_vectLoginUser[i].m_Id)
		{
			GetDlgItem(IDC_ED1_USERNAME)->SetWindowText(m_pDataProvider->m_vectLoginUser[i].m_strLoginName);		//��ȡ�û�������///
			GetDlgItem(IDC_ED2_PSAAWORD)->SetWindowText(m_pDataProvider->m_vectLoginUser[i].m_strLoginPassWd);		//��ȡ�û�������///
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// CEditUserPopDlg ��Ϣ�������

void CEditUserPopDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString NewUserName;
	CString NewUserPassWd;
	ManagerId = CLoginDlg::LoginUser_CurrentId;		//����ǰ�û�ID��������ԱID///
	GetDlgItem(IDC_ED1_USERNAME)->GetWindowText(NewUserName);		//��ȡ�û�������///
	GetDlgItem(IDC_ED2_PSAAWORD)->GetWindowText(NewUserPassWd);		//��ȡ�û�������///
	if (NewUserName.IsEmpty())
	{
		AfxMessageBox(_T("�û�������Ϊ��,����������!"));
		return;
	}
	if (NewUserPassWd.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ��,����������!"));
		return;
	}
	if (NewUserName==_T("Super"))
	{
		AfxMessageBox(_T("�Ƿ��û��������������룡"));
		return;
	}

	for (int i = 0; i < m_pDataProvider->m_vectLoginUser.size(); i++)			
	{
		//�жϳ����޸ĺ���û����������û��Ƿ�����///
		if ((NewUserName == m_pDataProvider->m_vectLoginUser[i].m_strLoginName)&&
			(EditUserId !=m_pDataProvider->m_vectLoginUser[i].m_Id))
		{
			AfxMessageBox(_T("���û����ѱ�ʹ��,����������!"));
			return;
		}
	}
	for (EditUserIndex = 0; EditUserIndex < m_pDataProvider->m_vectLoginUser.size(); EditUserIndex++)
	{
		if (EditUserId == m_pDataProvider->m_vectLoginUser[EditUserIndex].m_Id)
		{
			//�ж��û����������Ƿ��ԭ��һ��///
			if((NewUserName == m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginName)&&
				(NewUserPassWd == m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginPassWd))
			{
				AfxMessageBox(_T("�û���Ϣ�޸ĳɹ�!"));
				CDialog::OnOK();
				return;
			}
			if (EditUserId == ManagerId)	//��ѡ���û�IDΪ����Ա�Լ���ID///
			{
				int nResult;
				nResult = MessageBox(_T("�ò����޷��ָ����Ƿ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
				if (nResult == IDYES)
				{
					m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginName = NewUserName;
					m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginPassWd = NewUserPassWd;
					//��¼�޸�ʱ��///
					m_pDataProvider->m_vectLoginUser[EditUserIndex].m_LastUpdatedDateTime = CTime::GetCurrentTime();
					m_pDataProvider->UpdateTableItem(m_pDataProvider->tbLoginUser, EditUserId);		//�������ݿ�///
					AfxMessageBox(_T("�û���Ϣ�޸ĳɹ�!"));
					CDialog::OnOK();
				}
			}
			else
			{
				m_pDataProvider->m_vectLoginUser[EditUserIndex].m_IsAutoLogin = 0;
				m_pDataProvider->m_vectLoginUser[EditUserIndex].m_IsRememberPasswd = 0;
				m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginName = NewUserName;
				m_pDataProvider->m_vectLoginUser[EditUserIndex].m_strLoginPassWd = NewUserPassWd;
				//��¼�޸�ʱ��///
				m_pDataProvider->m_vectLoginUser[EditUserIndex].m_LastUpdatedDateTime = CTime::GetCurrentTime();
				m_pDataProvider->UpdateTableItem(m_pDataProvider->tbLoginUser, EditUserId);		//�������ݿ�///
				AfxMessageBox(_T("�û���Ϣ�޸ĳɹ�!"));
				CDialog::OnOK();
			}
		}
	}	
}



