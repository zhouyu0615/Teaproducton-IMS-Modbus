// InitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include  "Resource.h"


// CInitDlg �Ի���

IMPLEMENT_DYNAMIC(CInitDlg, CDialog)

CInitDlg::CInitDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInitDlg::IDD, pParent)
{
	m_InitTag = OWER_EDIT_TAG;
	m_pDataProvider->InitDataProvider();
}

CInitDlg::~CInitDlg()
{
}

void CInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED1_INITDLG, m_EditText1);
	DDX_Control(pDX, IDC_ED2_INITDLG, m_EditText2);
	DDX_Control(pDX, IDC_ED3_INITDLG, m_EditText3);
	DDX_Control(pDX, IDC_ED4_INITDLG, m_EditText4);
	DDX_Control(pDX, IDC_ED5_INITDLG, m_EditText5);
	DDX_Control(pDX, IDC_ED6_INITDLG, m_EditText6);
	DDX_Control(pDX, IDC_ST_ADDCONTENT_INITDLG, m_GroupBox);
	DDX_Control(pDX, IDC_LI_INITDLG, m_list_init);
	DDX_Control(pDX, IDC_CO_LINE_INITDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO_MODULE_INITDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_ST1_INITDLG, m_StaticText1);
	DDX_Control(pDX, IDC_ST2_INITDLG, m_StaticText2);
	DDX_Control(pDX, IDC_ST3_INITDLG, m_StaticText3);
	DDX_Control(pDX, IDC_ST4_INITDLG, m_StaticText4);
	DDX_Control(pDX, IDC_ST5_INITDLG, m_StaticText5);
	DDX_Control(pDX, IDC_ST6_INITDLG, m_StaticText6);
}


BEGIN_MESSAGE_MAP(CInitDlg, CDialog)
	ON_BN_CLICKED(IDC_BT_PLCPARA_INITDLG, &CInitDlg::OnBnClickedBtPlcparaInitdlg)
	ON_BN_CLICKED(IDC_BT_OWNER_INITDLG, &CInitDlg::OnBnClickedBtOwnerInitdlg)
	ON_BN_CLICKED(IDC_BT_LINE_INITDLG, &CInitDlg::OnBnClickedBtLineInitdlg)
	ON_BN_CLICKED(IDC_BT_MODULE_INITDLG, &CInitDlg::OnBnClickedBtModuleInitdlg)
	ON_BN_CLICKED(IDC_BT_DEVICE_INITDLG, &CInitDlg::OnBnClickedBtDeviceInitdlg)
	ON_BN_CLICKED(IDC_BT_PLC_INITDLG, &CInitDlg::OnBnClickedBtPlcInitdlg)
	ON_BN_CLICKED(IDC_BT_VEDIO_INITDLG, &CInitDlg::OnBnClickedBtVedioInitdlg)
	ON_BN_CLICKED(IDC_ADD_INITDLG, &CInitDlg::OnBnClickedAddInitdlg)
	ON_BN_CLICKED(IDC_BT_GOBACK_INITDLG, &CInitDlg::OnBnClickedBtGobackInitdlg)
	ON_WM_PAINT()
	ON_WM_ACTIVATE()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CO_LINE_INITDLG, &CInitDlg::OnCbnSelchangeCoLineInitdlg)
	ON_NOTIFY(NM_RCLICK, IDC_LI_INITDLG, &CInitDlg::OnNMRClickLiInitdlg)
END_MESSAGE_MAP()


// CInitDlg ��Ϣ�������

//��PLC��������ť��Ӧ����//
void CInitDlg::OnBnClickedBtPlcparaInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_EditPlcParaDlg.DoModal();
}


void CInitDlg::OnBnClickedBtOwnerInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_InitTag != OWER_EDIT_TAG)
	{
		ClearEditCtrl();
	}
	m_InitTag = OWER_EDIT_TAG;
	MyOnPaint();

}


void CInitDlg::OnBnClickedBtLineInitdlg()
{
	if (m_pDataProvider->m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_InitTag != PRODUCTION_LINE_EDIT_TAG)
	{
		ClearEditCtrl();
	}
	m_InitTag = PRODUCTION_LINE_EDIT_TAG;
	MyOnPaint();

}


void CInitDlg::OnBnClickedBtModuleInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pDataProvider->m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_pDataProvider->m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (m_InitTag != MODULE_EDIT_TAG)
	{
		ClearEditCtrl();
	}
	m_InitTag = MODULE_EDIT_TAG;
	MyOnPaint();

}


void CInitDlg::OnBnClickedBtDeviceInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pDataProvider->m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ���������ߣ����ȴ�����"));
		return;
	}
	if (m_pDataProvider->m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (m_pDataProvider->m_vectProcessModule.empty())
	{
		AfxMessageBox(_T("������ӹ���ģ�飡"));
		return;
	}
	if (m_InitTag != DEVICE_EDIT_TAG)
	{
		ClearEditCtrl();
	}
	m_InitTag = DEVICE_EDIT_TAG;
	MyOnPaint();

}


void CInitDlg::OnBnClickedBtPlcInitdlg()
{
	if (m_pDataProvider->m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_pDataProvider->m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (m_InitTag != PLC_EDIT_TAG)
	{
		this->ClearEditCtrl();
	}
	m_InitTag = PLC_EDIT_TAG;
	MyOnPaint();
}


void CInitDlg::OnBnClickedBtVedioInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	if (m_pDataProvider->m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ���������ߣ�������������ߣ�"));
		return;
	}
	if (m_pDataProvider->m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}


	m_InitTag = VIDEO_EDIT_TAG;
	MyOnPaint();
}


void CInitDlg::OnBnClickedAddInitdlg()
{
	CString text1, text2, text3, text4, text5, text6;
	CUserClass tempUser;
	CProductionLineClass tempProLine;
	CProcessModuleClass tempProModule;
	CDeviceClass tempDevice;
	CPlcClass tempPlc;
	CVideoClass tempVideo;


	m_EditText1.GetWindowText(text1);
	m_EditText2.GetWindowText(text2);
	m_EditText3.GetWindowText(text3);
	m_EditText4.GetWindowText(text4);
	m_EditText5.GetWindowText(text5);
	m_EditText6.GetWindowText(text6);

	switch (m_InitTag){
	case OWER_EDIT_TAG:
		if (!m_pDataProvider->m_vectUser.empty())            //�ж��Ƿ�����ӹ��û�
		{
			AfxMessageBox(_T("�Ƿ��������û��Ѵ�����"));
			return;
		}

		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

		tempUser.m_strUserName = text1;
		tempUser.m_strUserPasswd = text2;
		tempUser.m_strUserCode = text3;
		tempUser.m_strNote = text4;

		m_pDataProvider->AddUserToDatabase(tempUser);

		break;
	case PRODUCTION_LINE_EDIT_TAG:
		if (!m_pDataProvider->m_vectProductionLine.empty())                 //���������������Ƿ��Ѿ�����//
			for (int q = 0; q < m_pDataProvider->m_vectProductionLine.size(); q++)
				if (text1 == m_pDataProvider->m_vectProductionLine[q].m_strLineName)
				{
					AfxMessageBox(_T("�Ƿ��������������������Ѵ��ڣ�"));
					return;
				}

		if (text1.IsEmpty() || text2.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

		tempProLine.m_strLineName = text1;
		tempProLine.m_strCapacity = text2;
		tempProLine.m_strDescription = text3;
		 
		m_pDataProvider->AddProLineToDatabase(tempProLine);


		break;
	case MODULE_EDIT_TAG:

		m_LineComboBox.GetWindowText(text1); //text1���������ߣ�text2ģ������

		if (text1.IsEmpty() || text2.IsEmpty())                   //�ж���¼�빤��ģ����Ϣ�Ƿ���ȫ//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

		//�����������¹���ģ�������Ƿ��Ѿ�����//
		for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
			if (text2 == m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName)
			{
				if (text1 == m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName)
				{
					AfxMessageBox(_T("�Ƿ����������������µ�ͬ������ģ���Ѵ��ڣ�"));
					return;
				}

			}


		tempProModule.m_strProductionLineName = text1;
		tempProModule.m_strProcessModuleName = text2;
		tempProModule.m_strDescription = text3;

		m_pDataProvider->AddProModuleToDatabase(tempProModule);
		break;
	case DEVICE_EDIT_TAG:

		m_LineComboBox.GetWindowText(text1);
		m_ModuleComboBox.GetWindowText(text2);

		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

		tempDevice.m_strProductionLineName = text1;
		tempDevice.m_strProcessModuleName = text2;
		tempDevice.m_strDeviceName = text3;
		tempDevice.m_strDeviceType = text4;


		m_pDataProvider->AddDeviceToDatabase(tempDevice);

		break;
	case PLC_EDIT_TAG:

		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty()
			|| text4.IsEmpty() || text5.IsEmpty() || text6.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

		tempPlc.m_strPlcName = text1;
		tempPlc.m_strIPAddr = text2;
		tempPlc.m_ReadStartAddr = _ttoi(text3);
		tempPlc.m_ReadLength = _ttoi(text4);
		tempPlc.m_WriteStartAddr = _ttoi(text5);
		tempPlc.m_WriteLength = _ttoi(text6);


		//����ӵ���Ϣ¼�뵽����//

		m_pDataProvider->AddPlcToDatabase(tempPlc);
		break;

	case VIDEO_EDIT_TAG:

		m_LineComboBox.GetWindowText(text1);
		m_ModuleComboBox.GetWindowText(text2);

		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		tempVideo.m_strProductionLineName = text1;
		tempVideo.m_strProcessModuleName = text2;
		tempVideo.m_strVideoName = text3;
		tempVideo.m_strIPAddr = text4;

		tempVideo.m_port = _ttoi(text5);

		//����ӵ���Ϣ¼�뵽����//


		m_pDataProvider->AddVideoToDatabase(tempVideo);
		break;

	default:
		break;
	}
	ClearEditCtrl();

	ListOnPaint();

}



void CInitDlg::OnBnClickedBtGobackInitdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


int CInitDlg::LineComboboxOnPaint()
{
	//����Ѿ��������������Ϣ����û����д������������//
	if (!m_pDataProvider->m_vectProductionLine.empty())  {
		m_LineComboBox.ResetContent();
		for (int k = 0; k < m_pDataProvider->m_vectProductionLine.size(); k++)
		{
			m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[k].m_strLineName);
			
		}
	}
	m_LineComboBox.SetCurSel(0);
	return 0;
}

int CInitDlg::ListOnPaint()
{
	//�����б�ؼ����//
	CRect rect1;
	m_list_init.GetWindowRect(&rect1);
	m_list_init.SetExtendedStyle(m_list_init.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//����б�//
	m_list_init.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_list_init.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_list_init.DeleteColumn(i);

	if (!m_pDataProvider->m_vectUser.empty()
		&& !m_pDataProvider->m_vectProductionLine.empty()
		&& !m_pDataProvider->m_vectProcessModule.empty()) //����Ѿ�������û��������ߡ�ģ�飬��ʹ���������ͷ����ť����//
		GetDlgItem(IDC_BT_VEDIO_INITDLG)->EnableWindow(TRUE);

	int temp = 0;
	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	switch (m_InitTag){
	case OWER_EDIT_TAG:
		//��ʼ���༭��//
		m_GroupBox.SetWindowText(_T("���������"));
		m_StaticText1.SetWindowText(_T("�û�����"));
		m_StaticText2.SetWindowText(_T("��¼���룺"));
		m_StaticText3.SetWindowText(_T("�ͻ����룺"));
		m_StaticText4.SetWindowText(_T("��ע˵����"));

		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_SHOW);
		m_StaticText5.ShowWindow(SW_HIDE);
		m_StaticText6.ShowWindow(SW_HIDE);
		m_EditText1.ShowWindow(SW_SHOW);
		m_EditText2.ShowWindow(SW_SHOW);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_SHOW);
		m_EditText5.ShowWindow(SW_HIDE);
		m_EditText6.ShowWindow(SW_HIDE);
		m_LineComboBox.ShowWindow(SW_HIDE);
		m_ModuleComboBox.ShowWindow(SW_HIDE);
		//��ʼ���б���//
		//�б�༭//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 14, -1);
		m_list_init.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(3, _T("��¼����"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(4, _T("�ͻ�����"), LVCFMT_CENTER, rect1.Width() / 14 * 2, -1);
		m_list_init.InsertColumn(5, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 14 * 5, -1);
		//��д������//

		temp = m_pDataProvider->m_vectUser.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str);
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectUser[i].m_strUserName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectUser[i].m_strUserPasswd);
			m_list_init.SetItemText(i, 4, m_pDataProvider->m_vectUser[i].m_strUserCode);
			m_list_init.SetItemText(i, 5, m_pDataProvider->m_vectUser[i].m_strNote);
		}
		break;


	case PRODUCTION_LINE_EDIT_TAG:
		//��ʼ���༭��//

		m_GroupBox.SetWindowText(_T("���������"));
		m_StaticText1.SetWindowText(_T("����������"));
		m_StaticText2.SetWindowText(_T("���ܲ�����"));
		m_StaticText3.SetWindowText(_T("��ע˵����"));


		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_HIDE);
		m_StaticText5.ShowWindow(SW_HIDE);
		m_StaticText6.ShowWindow(SW_HIDE);
		m_EditText1.ShowWindow(SW_SHOW);
		m_EditText2.ShowWindow(SW_SHOW);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_HIDE);
		m_EditText5.ShowWindow(SW_HIDE);
		m_EditText6.ShowWindow(SW_HIDE);
		m_LineComboBox.ShowWindow(SW_HIDE);
		m_ModuleComboBox.ShowWindow(SW_HIDE);

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 10 * 4, -1);
		m_list_init.InsertColumn(3, _T("���ܲ���"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		//��д������//

		temp = m_pDataProvider->m_vectProductionLine.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str); //���
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectProductionLine[i].m_strLineName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectProductionLine[i].m_strCapacity);
			m_list_init.SetItemText(i, 4, m_pDataProvider->m_vectProductionLine[i].m_strDescription);
		}
		break;


	case MODULE_EDIT_TAG:
		//��ʼ���༭��//
		m_GroupBox.SetWindowText(_T("��ӹ���ģ��"));
		m_StaticText1.SetWindowText(_T("���������ߣ�"));
		m_StaticText2.SetWindowText(_T("����ģ�����ƣ�"));
		m_StaticText3.SetWindowText(_T("��ע˵����"));


		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_HIDE);
		m_StaticText5.ShowWindow(SW_HIDE);
		m_StaticText6.ShowWindow(SW_HIDE);

		m_EditText1.ShowWindow(SW_HIDE);
		m_EditText2.ShowWindow(SW_SHOW);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_HIDE);
		m_EditText5.ShowWindow(SW_HIDE);
		m_EditText6.ShowWindow(SW_HIDE);

		m_LineComboBox.ShowWindow(SW_SHOW);
		m_ModuleComboBox.ShowWindow(SW_HIDE);



		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(3, _T("����ģ������"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);

		//��д������//
		temp = m_pDataProvider->m_vectProcessModule.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str); //���
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
			m_list_init.SetItemText(i, 4, m_pDataProvider->m_vectProcessModule[i].m_strDescription);
		}
		break;


	case DEVICE_EDIT_TAG:
		//��ʼ���༭��//
		m_GroupBox.SetWindowText(_T("����豸"));
		m_StaticText1.SetWindowText(_T("���������ߣ�"));
		m_StaticText2.SetWindowText(_T("��������ģ�飺"));
		m_StaticText3.SetWindowText(_T("�豸���ƣ�"));
		m_StaticText4.SetWindowText(_T("�豸���ͣ�"));

		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_SHOW);
		m_StaticText5.ShowWindow(SW_HIDE);
		m_StaticText6.ShowWindow(SW_HIDE);

		m_EditText1.ShowWindow(SW_HIDE);
		m_EditText2.ShowWindow(SW_HIDE);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_SHOW);
		m_EditText5.ShowWindow(SW_HIDE);
		m_EditText6.ShowWindow(SW_HIDE);

		m_LineComboBox.ShowWindow(SW_SHOW);
		m_ModuleComboBox.ShowWindow(SW_SHOW);

		if (m_LineComboBox.GetCount() > 0)
		{
			if (m_ModuleComboBox.GetCount() > 0)    //���COMBO2�������ݣ������//
				m_ModuleComboBox.ResetContent();

			temp = m_LineComboBox.GetCurSel();
			CString str1;
			m_LineComboBox.GetLBText(temp, str1);//�õ�COMBO1��ǰѡ����Ŀ//
			for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
				if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
					m_ModuleComboBox.SetCurSel(0);
				}
		}
		m_ModuleComboBox.ShowWindow(SW_SHOW);


		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�༭��ͷ//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("�豸����"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("�豸����"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);



		//��д������//
		temp = m_pDataProvider->m_vectDevice.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str); //���
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectDevice[i].m_strProductionLineName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectDevice[i].m_strProcessModuleName);
			m_list_init.SetItemText(i, 4, m_pDataProvider->m_vectDevice[i].m_strDeviceName);
			m_list_init.SetItemText(i, 5, m_pDataProvider->m_vectDevice[i].m_strDeviceType);
		}
		break;

	case PLC_EDIT_TAG:
		//��ʼ���༭��//
		m_GroupBox.SetWindowText(_T("���PLC"));
		m_StaticText1.SetWindowText(_T("PLC����"));
		m_StaticText2.SetWindowText(_T("IP��ַ"));
		m_StaticText3.SetWindowText(_T("����ʼ��ַ"));
		m_StaticText4.SetWindowText(_T("�����ݳ���"));
		m_StaticText5.SetWindowText(_T("д��ʼ��ַ"));
		m_StaticText6.SetWindowText(_T("д���ݳ���"));

		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_SHOW);
		m_StaticText5.ShowWindow(SW_SHOW);
		m_StaticText6.ShowWindow(SW_SHOW);
		m_EditText1.ShowWindow(SW_SHOW);
		m_EditText2.ShowWindow(SW_SHOW);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_SHOW);
		m_EditText5.ShowWindow(SW_SHOW);
		m_EditText6.ShowWindow(SW_SHOW);

		m_LineComboBox.ShowWindow(SW_HIDE);
		m_ModuleComboBox.ShowWindow(SW_HIDE);



		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 15, -1);
		m_list_init.InsertColumn(2, _T("PLC����"), LVCFMT_CENTER, rect1.Width() / 15 * 3, -1);
		m_list_init.InsertColumn(3, _T("IP��ַ"), LVCFMT_CENTER, rect1.Width() / 15 * 3, -1);
		m_list_init.InsertColumn(4, _T("����ʼ��ַ��"), LVCFMT_CENTER, rect1.Width() / 15 * 2, -1);
		m_list_init.InsertColumn(5, _T("�����ݳ���"), LVCFMT_CENTER, rect1.Width() / 15 * 2, -1);
		m_list_init.InsertColumn(6, _T("д��ʼ��ַ"), LVCFMT_CENTER, rect1.Width() / 15 * 2, -1);
		m_list_init.InsertColumn(7, _T("д���ݳ���"), LVCFMT_CENTER, rect1.Width() / 15 * 2, -1);

		//��д������//
		temp = m_pDataProvider->m_vectPlc.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str); //���
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectPlc[i].m_strPlcName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectPlc[i].m_strIPAddr);

			str.Format(_T("%d"), m_pDataProvider->m_vectPlc[i].m_ReadStartAddr);
			m_list_init.SetItemText(i, 4, str);
			str.Format(_T("%d"), m_pDataProvider->m_vectPlc[i].m_ReadLength);
			m_list_init.SetItemText(i, 5, str);
			str.Format(_T("%d"), m_pDataProvider->m_vectPlc[i].m_WriteStartAddr);
			m_list_init.SetItemText(i, 6, str);
			str.Format(_T("%d"), m_pDataProvider->m_vectPlc[i].m_WriteLength);
			m_list_init.SetItemText(i, 7, str);
		}
		break;

	case VIDEO_EDIT_TAG:
		//��ʼ���༭��//
		m_GroupBox.SetWindowText(_T("�������ͷ"));
		m_StaticText1.SetWindowText(_T("���������ߣ�"));
		m_StaticText2.SetWindowText(_T("��������ģ�飺"));
		m_StaticText3.SetWindowText(_T("����ͷ���ƣ�"));
		m_StaticText4.SetWindowText(_T("IP��ַ��"));
		m_StaticText5.SetWindowText(_T("�˿ڣ�"));


		m_StaticText1.ShowWindow(SW_SHOW);
		m_StaticText2.ShowWindow(SW_SHOW);
		m_StaticText3.ShowWindow(SW_SHOW);
		m_StaticText4.ShowWindow(SW_SHOW);
		m_StaticText5.ShowWindow(SW_SHOW);
		m_StaticText6.ShowWindow(SW_HIDE);

		m_EditText1.ShowWindow(SW_HIDE);
		m_EditText2.ShowWindow(SW_HIDE);
		m_EditText3.ShowWindow(SW_SHOW);
		m_EditText4.ShowWindow(SW_SHOW);
		m_EditText5.ShowWindow(SW_SHOW);
		m_EditText6.ShowWindow(SW_HIDE);


		m_LineComboBox.ShowWindow(SW_SHOW);
		m_ModuleComboBox.ShowWindow(SW_SHOW);

		if (m_LineComboBox.GetCount() > 0)
		{
			if (m_ModuleComboBox.GetCount() > 0)    //���COMBO2�������ݣ������//
				m_ModuleComboBox.ResetContent();
			temp = m_LineComboBox.GetCurSel();
			CString str1;
			m_LineComboBox.GetLBText(temp, str1);//�õ�COMBO1��ǰѡ����Ŀ// 
			for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
				if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
					m_ModuleComboBox.SetCurSel(0);
				}
		}

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�༭��ͷ//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(4, _T("����ͷ����"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(5, _T("IP��ַ"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(6, _T("�˿�"), LVCFMT_CENTER, rect1.Width() / 10 * 1, -1);
		//��д������//
		temp = m_pDataProvider->m_vectVideo.size();

		for (int i = 0; i < temp; i++)
		{
			CString str, strPort;
			litem.iItem = i;
			str.Format(_T("%d"), i + 1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, str); //���
			m_list_init.SetItemText(i, 2, m_pDataProvider->m_vectVideo[i].m_strProductionLineName);
			m_list_init.SetItemText(i, 3, m_pDataProvider->m_vectVideo[i].m_strProcessModuleName);
			m_list_init.SetItemText(i, 4, m_pDataProvider->m_vectVideo[i].m_strVideoName);
			m_list_init.SetItemText(i, 5, m_pDataProvider->m_vectVideo[i].m_strIPAddr);

			strPort.Format(_T("%d"), m_pDataProvider->m_vectVideo[i].m_port);
			m_list_init.SetItemText(i, 6, strPort);
		}
		break;

	default:
		AfxMessageBox(_T("ϵͳ����"));
		CDialog::OnCancel();
		break;
	}

	return 0;
}

void CInitDlg::MyOnPaint()
{
	LineComboboxOnPaint();
	ListOnPaint();
}

void CInitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

}




void CInitDlg::ClearEditCtrl()
{
	m_EditText1.Clear();
	m_EditText2.Clear();
	m_EditText3.Clear();
	m_EditText4.Clear();
	m_EditText5.Clear();
	m_EditText6.Clear();

	m_EditText1.SetWindowText(_T(""));
	m_EditText2.SetWindowText(_T(""));
	m_EditText3.SetWindowText(_T(""));
	m_EditText4.SetWindowText(_T(""));
	m_EditText5.SetWindowText(_T(""));
	m_EditText6.SetWindowText(_T(""));
}





void CInitDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO:  �ڴ˴������Ϣ����������

}


int CInitDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


BOOL CInitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	MyOnPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CInitDlg::OnCbnSelchangeCoLineInitdlg()
{
	if (m_ModuleComboBox.GetCount() > 0)    //���COMBO2�������ݣ������//
		m_ModuleComboBox.ResetContent();
	CString str1;
	m_LineComboBox.GetWindowText(str1); // �õ�COMBO1��ǰѡ����Ŀ//
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == str1)
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
			m_ModuleComboBox.SetCurSel(0);
		}

}


void CInitDlg::OnNMRClickLiInitdlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	m_nSelectedItem = -1;
	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nSelectedItem = lpNMItemActivate->iItem;
	}
	if (m_nSelectedItem == -1)
	{
		return;
	}
	m_list_init.SetItemState(m_nSelectedItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);//�õ���괦//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//

	switch (nItem1)
	{
	case ID_AA_MODIFY:  //�Ҽ��˵����޸�//
		ModifyListItem(); 
		break;
	case ID_AA_DELETE:
		DeleteListItem(m_nSelectedItem);
		break;
	case  ID_AA_MOVEUP:
		MoveUpItem();
		break;
	case ID_AA_MOVEDOWN:
		MoveDownItem();
		break;
	default:
		break;
	}
	MyOnPaint();
}


int CInitDlg::ModifyListItem()
{
	switch (m_InitTag)
	{
	case OWER_EDIT_TAG:
		m_EditOwerPopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditOwerPopDlg.DoModal();
		break;
	case PRODUCTION_LINE_EDIT_TAG:
		m_EditLinePopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditLinePopDlg.DoModal();
		break;
	case MODULE_EDIT_TAG:
		m_EditModulePopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditModulePopDlg.DoModal();
		break;
	case DEVICE_EDIT_TAG:
		m_EditDevicePopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditDevicePopDlg.DoModal();
		break;
	case PLC_EDIT_TAG:
		m_EditPlcPopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditPlcPopDlg.DoModal();
		break;
	case VIDEO_EDIT_TAG:
		m_EditVideoPopDlg.m_nSelectedItem = m_nSelectedItem;
		m_EditVideoPopDlg.DoModal();
		break;
	default:
		break;
	}

	return 0;
}

int CInitDlg::MoveUpItem()
{
	switch (m_InitTag)
	{
	case OWER_EDIT_TAG:

		break;
	case PRODUCTION_LINE_EDIT_TAG:
		if (m_nSelectedItem >= 1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectProductionLine[m_nSelectedItem - 1], m_pDataProvider->m_vectProductionLine[m_nSelectedItem]);
			//�������ߵ�SortIndex����//
			std::swap(m_pDataProvider->m_vectProductionLine[m_nSelectedItem - 1].m_SortIndex, m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProductionLine, m_pDataProvider->m_vectProductionLine[m_nSelectedItem - 1].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProductionLine, m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_Id);
		}
		break;
	case MODULE_EDIT_TAG:
		if (m_nSelectedItem >= 1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectProcessModule[m_nSelectedItem - 1], m_pDataProvider->m_vectProcessModule[m_nSelectedItem]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectProcessModule[m_nSelectedItem - 1].m_SortIndex, m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProcessModule, m_pDataProvider->m_vectProcessModule[m_nSelectedItem - 1].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProcessModule, m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_Id);
		}
		break;
	case DEVICE_EDIT_TAG:
		if (m_nSelectedItem >= 1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectDevice[m_nSelectedItem - 1], m_pDataProvider->m_vectDevice[m_nSelectedItem]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectDevice[m_nSelectedItem - 1].m_SortIndex, m_pDataProvider->m_vectDevice[m_nSelectedItem].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbDevice, m_pDataProvider->m_vectDevice[m_nSelectedItem - 1].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbDevice, m_pDataProvider->m_vectDevice[m_nSelectedItem].m_Id);
		}
		break;
	case PLC_EDIT_TAG:
		if (m_nSelectedItem >= 1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectPlc[m_nSelectedItem - 1], m_pDataProvider->m_vectPlc[m_nSelectedItem]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectPlc[m_nSelectedItem - 1].m_SortIndex, m_pDataProvider->m_vectPlc[m_nSelectedItem].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbPLc, m_pDataProvider->m_vectPlc[m_nSelectedItem - 1].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbPLc, m_pDataProvider->m_vectPlc[m_nSelectedItem].m_Id);
		}
		break;
	case VIDEO_EDIT_TAG:
		if (m_nSelectedItem >= 1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectVideo[m_nSelectedItem - 1], m_pDataProvider->m_vectVideo[m_nSelectedItem]);
			//SortIndex����//
			std::swap(m_pDataProvider->m_vectVideo[m_nSelectedItem - 1].m_SortIndex, m_pDataProvider->m_vectVideo[m_nSelectedItem].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbVideo, m_pDataProvider->m_vectVideo[m_nSelectedItem - 1].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbVideo, m_pDataProvider->m_vectVideo[m_nSelectedItem].m_Id);
		}
		break;
	default:
		break;
	}

	return 0;
}


int CInitDlg::MoveDownItem()
{
	switch (m_InitTag)
	{
	case OWER_EDIT_TAG:
		break;
	case PRODUCTION_LINE_EDIT_TAG:
		if (m_nSelectedItem<m_pDataProvider->m_vectProductionLine.size()-1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectProductionLine[m_nSelectedItem], m_pDataProvider->m_vectProductionLine[m_nSelectedItem+1]);
			//�������ߵ�SortIndex����//
			std::swap(m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_SortIndex, m_pDataProvider->m_vectProductionLine[m_nSelectedItem+1].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProductionLine, m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProductionLine, m_pDataProvider->m_vectProductionLine[m_nSelectedItem+1].m_Id);

		}

	case MODULE_EDIT_TAG:
		if (m_nSelectedItem<m_pDataProvider->m_vectProcessModule.size()-1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectProcessModule[m_nSelectedItem], m_pDataProvider->m_vectProcessModule[m_nSelectedItem+1]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_SortIndex, m_pDataProvider->m_vectProcessModule[m_nSelectedItem+1].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProcessModule, m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbProcessModule, m_pDataProvider->m_vectProcessModule[m_nSelectedItem+1].m_Id);
		}
		break;
	case DEVICE_EDIT_TAG:
		if (m_nSelectedItem <m_pDataProvider->m_vectDevice.size()-1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectDevice[m_nSelectedItem], m_pDataProvider->m_vectDevice[m_nSelectedItem+1]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectDevice[m_nSelectedItem].m_SortIndex, m_pDataProvider->m_vectDevice[m_nSelectedItem+1].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbDevice, m_pDataProvider->m_vectDevice[m_nSelectedItem].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbDevice, m_pDataProvider->m_vectDevice[m_nSelectedItem+1].m_Id);
		}
		break;
	case PLC_EDIT_TAG:
		if (m_nSelectedItem <m_pDataProvider->m_vectPlc.size()-1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectPlc[m_nSelectedItem], m_pDataProvider->m_vectPlc[m_nSelectedItem+1]);
			//��SortIndex����//
			std::swap(m_pDataProvider->m_vectPlc[m_nSelectedItem].m_SortIndex, m_pDataProvider->m_vectPlc[m_nSelectedItem+1].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbPLc, m_pDataProvider->m_vectPlc[m_nSelectedItem].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbPLc, m_pDataProvider->m_vectPlc[m_nSelectedItem+1].m_Id);
		}
		break;
	case VIDEO_EDIT_TAG:
		if (m_nSelectedItem <m_pDataProvider->m_vectVideo.size()-1)
		{
			//�������е���һ��Ԫ�ؽ��н���//
			std::swap(m_pDataProvider->m_vectVideo[m_nSelectedItem], m_pDataProvider->m_vectVideo[m_nSelectedItem+1]);
			//SortIndex����//
			std::swap(m_pDataProvider->m_vectVideo[m_nSelectedItem].m_SortIndex, m_pDataProvider->m_vectVideo[m_nSelectedItem+1].m_SortIndex);

			//�ѸĶ��������ݿ�//
			m_pDataProvider->UpdateTableItem(CDataProvider::tbVideo, m_pDataProvider->m_vectVideo[m_nSelectedItem].m_Id);
			m_pDataProvider->UpdateTableItem(CDataProvider::tbVideo, m_pDataProvider->m_vectVideo[m_nSelectedItem+1].m_Id);
		}
		break;
	default:
		break;
	}


	return 0;
}



int CInitDlg::DeleteListItem(int nItem)
{
	int nResult;
	std::vector<CProductionLineClass>::iterator pProlineIter;
	std::vector<CProcessModuleClass>::iterator  pModuleIter;
	std::vector<CDeviceClass>::iterator        pDeviceIter;
	std::vector<CPlcClass>::iterator            pPlcIter;
	std::vector<CVideoClass>::iterator		pVideoIter;
	CString tempProLineName, tempModuleName;
	switch (m_InitTag)
	{
	case OWER_EDIT_TAG:
		nResult = MessageBox(_T("�ò�����ɾ���û��������������豸���Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
		if (nResult == IDYES)
		{
			m_pDataProvider->DeleteDbTable(CDataProvider::tbUser);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbProductionLine);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbProcessModule);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbDevice);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbPLc);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbVideo);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbProcessPara);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbStatePara);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbDevicePara);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbFaultPara);
			m_pDataProvider->DeleteDbTable(CDataProvider::tbFormula);

		}
		break;
	case PRODUCTION_LINE_EDIT_TAG:
		nResult = MessageBox(_T("�ò�����ɾ�������������й���ģ�飬�豸������ͷ���豸���Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
		if (nResult == IDYES)
		{
			//ɾ�����ݿ��е�������//
			m_pDataProvider->DeleteDbTableItem(CDataProvider::tbProductionLine,
				m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_Id);

			//ɾ�������������ߵĹ���ģ�飬�豸��PLC,����ͷ//
			tempProLineName = m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_strLineName;
			m_pDataProvider->DeleteModule(tempProLineName);
			m_pDataProvider->DeleteDevice(tempProLineName);
			m_pDataProvider->DeleteVideo(tempProLineName);

			//ɾ����ص��豸���������ղ��������ϲ���//
			m_pDataProvider->DeleteParaRelatedToLine(m_pDataProvider->m_vectProductionLine[m_nSelectedItem].m_Id); 
			

			//ɾ���������е�����
			pProlineIter = m_pDataProvider->m_vectProductionLine.begin();
			m_pDataProvider->m_vectProductionLine.erase(pProlineIter + m_nSelectedItem);
		}

		break;

	case MODULE_EDIT_TAG:
		nResult = MessageBox(_T("�ò�����ɾ���ù���ģ������������豸�����ݣ��Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
		if (nResult == IDYES)
		{
			//ɾ�����ݿ��е�����//
			m_pDataProvider->DeleteDbTableItem(CDataProvider::tbProcessModule,
				m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_Id);

			//ɾ�������������ߵĹ���ģ�飬�豸��PLC,����ͷ//
			tempProLineName = m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_strProductionLineName;
			tempModuleName = m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_strProcessModuleName;
			m_pDataProvider->DeleteDevice(tempProLineName, tempModuleName);
			m_pDataProvider->DeleteVideo(tempProLineName, tempModuleName);

			//ɾ����ģ����صĹ��ղ������豸���������ϲ�����״̬����//
			m_pDataProvider->DeleteParaRelatedToModule(m_pDataProvider->m_vectProcessModule[m_nSelectedItem].m_Id);

			//ɾ���������е�����//
			pModuleIter = m_pDataProvider->m_vectProcessModule.begin();
			m_pDataProvider->m_vectProcessModule.erase(pModuleIter + m_nSelectedItem);
		}

		break;
	case DEVICE_EDIT_TAG:
		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbDevice,
			m_pDataProvider->m_vectDevice[m_nSelectedItem].m_Id);

		m_pDataProvider->DeleteParaRelatedToDevice(m_pDataProvider->m_vectDevice[m_nSelectedItem].m_Id);

		pDeviceIter = m_pDataProvider->m_vectDevice.begin();
		m_pDataProvider->m_vectDevice.erase(pDeviceIter + m_nSelectedItem);


		break;
	case PLC_EDIT_TAG:
		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbPLc,
			m_pDataProvider->m_vectPlc[m_nSelectedItem].m_Id);

		m_pDataProvider->DeleteParaRelatedToPlc(m_pDataProvider->m_vectPlc[m_nSelectedItem].m_Id);

		pPlcIter = m_pDataProvider->m_vectPlc.begin();
		m_pDataProvider->m_vectPlc.erase(pPlcIter + m_nSelectedItem);

		break;
	case VIDEO_EDIT_TAG:

		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbVideo,
			m_pDataProvider->m_vectVideo[m_nSelectedItem].m_Id);

		pVideoIter = m_pDataProvider->m_vectVideo.begin();
		m_pDataProvider->m_vectVideo.erase(pVideoIter + m_nSelectedItem);

		break;
	default:
		break;
	}
	return 0;
}








void CInitDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
