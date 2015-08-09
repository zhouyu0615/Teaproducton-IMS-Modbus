// AllUserManageDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "AllUserManageDlg.h"
#include "afxdialogex.h"

// CAllUserManageDlg �Ի���

IMPLEMENT_DYNAMIC(CAllUserManageDlg, CDialog)

CAllUserManageDlg::CAllUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAllUserManageDlg::IDD, pParent)
{
	m_pDataProvider = CDataProvider::getInstance();
	m_pDataProvider->ReadLoginUserFormDatabase();
	

}

CAllUserManageDlg::~CAllUserManageDlg()
{
}

void CAllUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LI1_ALLUSERMANAGEDLG, m_list_UserInfo);
	DDX_Control(pDX, IDC_ED1_USERNAME, m_edUserName);
	DDX_Control(pDX, IDC_ED2_PASSWORD, m_edPassword);
}

BEGIN_MESSAGE_MAP(CAllUserManageDlg, CDialog)
	ON_BN_CLICKED(IDC_BT1_ADDUSER, &CAllUserManageDlg::OnBnClickedBt1Adduser)
	ON_BN_CLICKED(IDC_BT2_CLEARALL, &CAllUserManageDlg::OnBnClickedBt2Clearall)
	ON_NOTIFY(NM_RCLICK, IDC_LI1_ALLUSERMANAGEDLG, &CAllUserManageDlg::OnNMRClickLi1Allusermanagedlg)
END_MESSAGE_MAP()

// CAllUserManageDlg ��Ϣ�������

void CAllUserManageDlg::OnBnClickedBt1Adduser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������///
	CLoginUser tempLoginUser;		//�����û�����///

	// ��ȡ�༭���е������û���������///
	GetDlgItem(IDC_ED1_USERNAME)->GetWindowText(tempLoginUser.m_strLoginName);
	GetDlgItem(IDC_ED2_PASSWORD)->GetWindowText(tempLoginUser.m_strLoginPassWd);

	if (tempLoginUser.m_strLoginName==_T("Super"))
	{
		AfxMessageBox(_T("���û�������ʹ�ã�"));
		return;
	}
	
	//�ж��û����Ƿ�Ϊ�գ�Ϊ������ʾ��ϢΪ��///
	if (tempLoginUser.m_strLoginName.IsEmpty())
    {
		AfxMessageBox(_T("�û���Ϊ��,�������û���!"));
		return;
    }
	else if (tempLoginUser.m_strLoginPassWd.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ�գ�����������!"));
		return;
	}
	else
	{
		m_pDataProvider->ReadUserFromDatabase();
		
		for (int i = 0; i < m_pDataProvider->m_vectLoginUser.size();i++)
		{
			if (tempLoginUser.m_strLoginName == m_pDataProvider->m_vectLoginUser[i].m_strLoginName)
			{
				AfxMessageBox(_T("���û����ѱ�ʹ�ã�����������!"));
				return;
			}	
		}
	}
	tempLoginUser.m_PermissionLevel = 0;						//����ԱȨ��Ϊ0������Ա��superȨ��Ϊ1  ///
	m_pDataProvider->AddLoginUserToDatabase(tempLoginUser);		//����һ���û�///
	AfxMessageBox(_T("��ӳɹ�!"));
	m_edUserName.SetWindowText(_T(""));
	m_edPassword.SetWindowText(_T(""));
	
	MyOnPint();													//ÿ�޸�һ��ˢ��һ���б��///
}

BOOL CAllUserManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
							// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	MyOnPint();				//�б����ʾ�û���Ϣ///
	return TRUE;		 // return TRUE unless you set the focus to a control
						// �쳣:  OCX ����ҳӦ���� FALSE
}
void CAllUserManageDlg::MyOnPint()
{
	CPaintDC dc(this); // device context for painting
	m_pDataProvider->ReadLoginUserFormDatabase();
						//�����б�ؼ����///
	CRect rect1;
	m_list_UserInfo.GetWindowRect(&rect1);
	m_list_UserInfo.SetExtendedStyle(m_list_UserInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	m_list_UserInfo.DeleteAllItems();		//������б����Ԫ��///
	CHeaderCtrl *pmyHeaderCtrl = m_list_UserInfo.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
	{
		m_list_UserInfo.DeleteColumn(i);
	}
	int temp = 0;
	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");
	//��ʼ���༭��///
	m_list_UserInfo.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_list_UserInfo.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 35 * 3, -1);
	m_list_UserInfo.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect1.Width() / 35 * 3, -1);
	m_list_UserInfo.InsertColumn(3, _T("����"), LVCFMT_CENTER, rect1.Width() / 35 * 3, -1);
	m_list_UserInfo.InsertColumn(4, _T("Ȩ��"), LVCFMT_CENTER, rect1.Width() / 35 * 3, -1);
	m_list_UserInfo.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect1.Width() / 35 * 8, -1);
	m_list_UserInfo.InsertColumn(6, _T("�ϴε�¼ʱ��"), LVCFMT_CENTER, rect1.Width() / 35 * 8, -1);
	m_list_UserInfo.InsertColumn(7, _T("����޸�ʱ��"), LVCFMT_CENTER, rect1.Width() / 35 * 8, -1);

	//��д������,���û���Ϣ��ʾ���б����///
	temp = m_pDataProvider->m_vectLoginUser.size();
	for (int i = 0; i < temp; i++)
	{
		litem.iItem = i;
		CString str;
		str.Format(_T("%d"), i + 1);
		m_list_UserInfo.InsertItem(&litem);
		m_list_UserInfo.SetItemText(i, 1, str);
		m_list_UserInfo.SetItemText(i, 2, (m_pDataProvider->m_vectLoginUser[i].m_strLoginName));
		m_list_UserInfo.SetItemText(i, 3, (m_pDataProvider->m_vectLoginUser[i].m_strLoginPassWd));
		m_list_UserInfo.SetItemText(i, 5, (m_pDataProvider->m_vectLoginUser[i].m_strCreatedDateTime));
		if (m_pDataProvider->m_vectLoginUser[i].m_strLastLoginInTime==_T("1970-01-01 08:00:00"))
		{
			m_list_UserInfo.SetItemText(i, 6, _T("��δ��¼"));
		}
		else
		    m_list_UserInfo.SetItemText(i, 6, (m_pDataProvider->m_vectLoginUser[i].m_strLastLoginInTime));
		m_list_UserInfo.SetItemText(i, 7, (m_pDataProvider->m_vectLoginUser[i].m_strLastUpdatedDateTime));
		if (m_pDataProvider->m_vectLoginUser[i].m_PermissionLevel==0)
		{
			m_list_UserInfo.SetItemText(i, 4, _T("����Ա"));
		}
		else if (m_pDataProvider->m_vectLoginUser[i].m_PermissionLevel == 1)
		{
			m_list_UserInfo.SetItemText(i, 4, _T("����Ա"));
		}
	}
}
//����Ա�һ��˵�ɾ�����޸ĵ���Ӧ����///
void CAllUserManageDlg::OnNMRClickLi1Allusermanagedlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	index = pNMItemActivate->iItem;  //�û��һ����б�//
	//CEditUserPopDlg.EditUserId= m_pDataProvider->m_vectLoginUser[index].m_Id;		//�б�����û�ID///
	if (index == -1)
	{
		return;
	}
	//�����Ӧ�˵���///
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_MENU_MANAGE);
	pSubMenu = menu.GetSubMenu(0);			//0��ʾ�Զ���Ĳ˵����ֻ��1��,0��ʾ��1��///
	CPoint cpoint;							//�洢���λ�õ���ʱ����//
	GetCursorPos(&cpoint);					//�õ���괦//
	//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	UINT  nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, cpoint.x, cpoint.y, GetParent());
	if (nItem1 == ID_DELETE)
	{
		int nResult;
		nResult = MessageBox(_T("�ò����޷��ָ����Ƿ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
		if (nResult == IDYES)
		{
			if (1 == m_pDataProvider->m_vectLoginUser[index].m_PermissionLevel)		//����ǰɾ�����û�IDΪ����Ա������ʾ����ɾ��///
			{
				AfxMessageBox(_T("�Բ���,������ɾ������Ա�û�!"));
				return;
			}
			m_pDataProvider->DeleteDbTableItem(m_pDataProvider->tbLoginUser, m_pDataProvider->m_vectLoginUser[index].m_Id);
			//��������ĵ�index��ɾ�����������¶����ݿ�///
			m_pDataProvider->m_vectLoginUser.erase(m_pDataProvider->m_vectLoginUser.begin()+index);		
			AfxMessageBox(_T("��ɾ��"));
			MyOnPint();
		}
	}
	if (nItem1 == ID_MODIFY)
	{
		//�����޸��û��Ľ���///
		CEditUserPopDlg dlgUserPop;
		dlgUserPop.EditUserId = m_pDataProvider->m_vectLoginUser[index].m_Id;	//�б��ѡ���û���ID///
		dlgUserPop.DoModal();
		MyOnPint();
	}
}

	//��ղ�������Ӧ����///
void CAllUserManageDlg::OnBnClickedBt2Clearall()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nResult;
	nResult = MessageBox(_T("�ò�����ɾ�����в���Ա�˺�,�������޷��ָ����Ƿ������"),
		_T("����"), MB_ICONEXCLAMATION | MB_YESNO);
	if (nResult == IDYES)
	{
		for (int i = m_pDataProvider->m_vectLoginUser.size()-1; i >=0; i--)
		{
			if (m_pDataProvider->m_vectLoginUser[i].m_PermissionLevel==0)
			{
				m_pDataProvider->DeleteDbTableItem(m_pDataProvider->tbLoginUser, m_pDataProvider->m_vectLoginUser[i].m_Id);
				//��������ĵ�i����¼���������forѭ�����������¶����ݿ�///
				m_pDataProvider->m_vectLoginUser.erase(m_pDataProvider->m_vectLoginUser.begin() + i);
			}
		}
		AfxMessageBox(_T("�����"));
		MyOnPint();
	}
}