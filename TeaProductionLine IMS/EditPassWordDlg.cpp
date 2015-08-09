// EditPassWordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditPassWordDlg.h"
#include "afxdialogex.h"
#include "DataProvider.h"
// CEditPassWordDlg �Ի���


IMPLEMENT_DYNAMIC(CEditPassWordDlg, CDialog)

CEditPassWordDlg::CEditPassWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPassWordDlg::IDD, pParent)
{
}

CEditPassWordDlg::~CEditPassWordDlg()
{
}

void CEditPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
									
	
}



BEGIN_MESSAGE_MAP(CEditPassWordDlg, CDialog)
	ON_BN_CLICKED(IDC_BT1_SAVE_EDITPASSWORDDLG, &CEditPassWordDlg::OnBnClickedBt1SaveEditpassworddlg)
END_MESSAGE_MAP()

BOOL CEditPassWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_pDataProvider->ReadLoginUserFormDatabase();		//�����ݿ����ȡ����///
	CurrentId = CLoginDlg::LoginUser_CurrentId;			//����ǰ��¼�û���ID����CurrentId///

	for (UserNumber = 0; UserNumber < m_pDataProvider->m_vectLoginUser.size(); UserNumber++)
	{
		if (m_pDataProvider->m_vectLoginUser[UserNumber].m_Id == CurrentId)
		{
			GetDlgItem(IDC_ED1_USERNAME_EDITPASSWORDDLG)->SetWindowText(m_pDataProvider->m_vectLoginUser[UserNumber].m_strLoginName);
			break;
		}
	}
	return TRUE;
	// return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

	// CEditPassWordDlg ��Ϣ�������
void CEditPassWordDlg::OnBnClickedBt1SaveEditpassworddlg()
{

	CLoginUser tempLoginUser;				//�����û�����///
	CString NewPassWord1;					//������///
	CString NewPassWord;					//�ٴ������������///
	(GetDlgItem(IDC_ED2_OLDPASSWORD))->GetWindowText(tempLoginUser.m_strLoginPassWd);
	(GetDlgItem(IDC_ED3_NEWPASSWORD1))->GetWindowText(NewPassWord1);
	(GetDlgItem(IDC_ED4_NEWPASSWORD))->GetWindowText(NewPassWord);
	if(tempLoginUser.m_strLoginPassWd.IsEmpty())
	{
		AfxMessageBox(_T("�������벻��Ϊ��,����������!"));
		return;
	}
	if (tempLoginUser.m_strLoginPassWd == m_pDataProvider->m_vectLoginUser[UserNumber].m_strLoginPassWd)
	{
		if (NewPassWord.IsEmpty()||NewPassWord1.IsEmpty())
		{
			AfxMessageBox(_T("�����벻��Ϊ��,����������!"));
			return;
		}
		if (NewPassWord1 == NewPassWord)
		{
			if (NewPassWord == m_pDataProvider->m_vectLoginUser[UserNumber].m_strLoginPassWd)
			{
				AfxMessageBox(_T("�����޸ĳɹ�!���μ�����������!"));
				CDialog::OnCancel();
			}
			else
			{
				
				m_pDataProvider->m_vectLoginUser[UserNumber].m_strLoginPassWd = NewPassWord;						//��¼�޸�����///
				m_pDataProvider->m_vectLoginUser[UserNumber].m_LastUpdatedDateTime = CTime::GetCurrentTime();			//��¼�޸�ʱ��///
				m_pDataProvider->UpdateTableItem(m_pDataProvider->tbLoginUser, m_pDataProvider->m_vectLoginUser[UserNumber].m_Id);	//�������ݿ�///
				AfxMessageBox(_T("�����޸ĳɹ�!���μ�����������!"));
				CDialog::OnCancel();
			}
		}
		else
		{
			AfxMessageBox(_T("��������������벻һ��!����������!"));
			return;
		}
	}
	else
	{
		AfxMessageBox(_T("�����벻��ȷ!����������!"));
		return;
	}
}



