// EditDeviceParaTabDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditDeviceParaTabDlg.h"
#include "afxdialogex.h"


// CEditDeviceParaTabDlg �Ի���

IMPLEMENT_DYNAMIC(CEditDeviceParaTabDlg, CDialog)

CEditDeviceParaTabDlg::CEditDeviceParaTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDeviceParaTabDlg::IDD, pParent)
{

}

CEditDeviceParaTabDlg::~CEditDeviceParaTabDlg()
{
}

void CEditDeviceParaTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LI1_EDITDEVICEPARA_TABDLG, m_list1);
	DDX_Control(pDX, IDC_ED1_EDITDEVICEPARA_TABDLG, m_NameEdit);
	DDX_Control(pDX, IDC_ED2_EDITDEVICEPARA_TABDLG, m_ControlAddrEdit);
	DDX_Control(pDX, IDC_ED3_EDITDEVICEPARA_TABDLG, m_StateAddrEdit);
	DDX_Control(pDX, IDC_ED4_EDITDEVICEPARA_TABDLG, m_DescriptionEdit);
	DDX_Control(pDX, IDC_CO1_EDITDEVICEPARA_TABDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO2_EDITDEVICEPARA_TABDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_CO3_EDITDEVICEPARA_TABDLG, m_DeviceComoboBox);
	DDX_Control(pDX, IDC_CO4_EDITDEVICEPARA_TABDLG, m_PlcComboBox);
}


BEGIN_MESSAGE_MAP(CEditDeviceParaTabDlg, CDialog)
	ON_BN_CLICKED(IDC_BT1_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnBnClickedAddItem)
	ON_BN_CLICKED(IDC_BT2_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnBnClickedClearEdit)
	ON_BN_CLICKED(IDC_BT3_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnBnClickedClearAll)
	ON_CBN_SELCHANGE(IDC_CO1_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnCbnSelchangeLine)
	ON_CBN_SELCHANGE(IDC_CO2_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnCbnSelchangeModule)
	ON_NOTIFY(NM_RCLICK, IDC_LI1_EDITDEVICEPARA_TABDLG, &CEditDeviceParaTabDlg::OnNMRClickLi1EditdeviceparaTabdlg)
END_MESSAGE_MAP()


// CEditDeviceParaTabDlg ��Ϣ�������

//���//
void CEditDeviceParaTabDlg::OnBnClickedAddItem()
{
	CDevicePara tempDevicePara;
	m_LineComboBox.GetWindowText(tempDevicePara.m_strProductionLineName);
	m_ModuleComboBox.GetWindowText(tempDevicePara.m_strProcessModuleName);
	m_DeviceComoboBox.GetWindowText(tempDevicePara.m_strDeviceName);

	m_PlcComboBox.GetWindowText(tempDevicePara.m_strPlcName);
	
	m_NameEdit.GetWindowText(tempDevicePara.m_strParaName);
	m_ControlAddrEdit.GetWindowText(tempDevicePara.m_strControlAddrIndex);
	m_StateAddrEdit.GetWindowText(tempDevicePara.m_strStateAddrIndex);
	m_DescriptionEdit.GetWindowText(tempDevicePara.m_strDescription);

	if (m_ParaCheckUtil.DeviceParaCheck(tempDevicePara) == 0) //�������ļ��ͨ��
	{
		m_pDataProvider->AddDeviceParaToDatabase(tempDevicePara);
	}
	
	ListOnPaint();
}

//��ձ༭��//
void CEditDeviceParaTabDlg::OnBnClickedClearEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_NameEdit.SetWindowText(_T(""));
	m_ControlAddrEdit.SetWindowText(_T(""));
	m_StateAddrEdit.SetWindowText(_T(""));
	m_DescriptionEdit.SetWindowText(_T(""));
}

//�������//
void CEditDeviceParaTabDlg::OnBnClickedClearAll()
{
	int nResult = MessageBox(_T("�ò�����ɾ�����е��豸�������Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
	if (nResult == IDYES)
	{
		m_pDataProvider->m_vectDevicePara.clear();
		m_pDataProvider->DeleteDbTable(CDataProvider::tbDevicePara);
		OnBnClickedClearEdit();
		ListOnPaint();
	}

}


BOOL CEditDeviceParaTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	MyOnPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int CEditDeviceParaTabDlg::MyOnPaint()
{
	ListOnPaint(); //�����б��//

	LineComboxPaint();
	CString LineName,ModuleName;
	//m_LineComboBox.GetLBText(0,LineName);
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);

	//m_ModuleComboBox.GetLBText(0,ModuleName);
	m_ModuleComboBox.GetWindowText(ModuleName);
	DeviceComboxPaint(LineName,ModuleName);

	PlcComboxPaint();
	
	return 0;
}

int CEditDeviceParaTabDlg::LineComboxPaint()
{
	m_LineComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProductionLine.size(); i++)
	{
		m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[i].m_strLineName);
		m_LineComboBox.SetCurSel(0);
	}
	
	return 0;

}
int CEditDeviceParaTabDlg::ModuleComboxPaint(CString LineName)
{
	m_ModuleComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size();i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName==LineName)
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
			m_ModuleComboBox.SetCurSel(0);
		}
	}
	
	return 0;
}

int CEditDeviceParaTabDlg::DeviceComboxPaint(CString LineName, CString ModuleName)
{
	m_DeviceComoboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectDevice.size();i++)
	{
		if ((m_pDataProvider->m_vectDevice[i].m_strProductionLineName==LineName)
			&&(m_pDataProvider->m_vectDevice[i].m_strProcessModuleName==ModuleName))
		{
			m_DeviceComoboBox.AddString(m_pDataProvider->m_vectDevice[i].m_strDeviceName);
			m_DeviceComoboBox.SetCurSel(0);
		}
	}

	return 0;
}

int CEditDeviceParaTabDlg::PlcComboxPaint()
{
	m_PlcComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectPlc.size();i++)
	{
		m_PlcComboBox.AddString(m_pDataProvider->m_vectPlc[i].m_strPlcName);
		m_PlcComboBox.SetCurSel(0);
	}
	
	return 0;
}

int CEditDeviceParaTabDlg::ListOnPaint()
{

	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");
	//�����б�ؼ����//
	CRect rect1;
	m_list1.GetWindowRect(&rect1);
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//����б�//
	m_list1.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_list1.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_list1.DeleteColumn(i);

	m_list1.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_list1.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 17, -1);
	m_list1.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(3, _T("����ģ��"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(4, _T("�����豸"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(5, _T("����PLC"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(6, _T("��������"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(7, _T("�����źŵ�ַ"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(8, _T("�����źŵ�ַ"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(9, _T("��ע��"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	//��д������//
	int length = m_pDataProvider->m_vectDevicePara.size();
	for (int i = 0; i < length; i++)
	{
		litem.iItem = i;
		CString str;
		str.Format(_T("%d"), i + 1);
		m_list1.InsertItem(&litem);
		m_list1.SetItemText(i, 1, str);
		m_list1.SetItemText(i, 2, m_pDataProvider->m_vectDevicePara[i].m_strProductionLineName);
		m_list1.SetItemText(i, 3, m_pDataProvider->m_vectDevicePara[i].m_strProcessModuleName);
		m_list1.SetItemText(i, 4, m_pDataProvider->m_vectDevicePara[i].m_strDeviceName);
		m_list1.SetItemText(i, 5, m_pDataProvider->m_vectDevicePara[i].m_strPlcName);
		m_list1.SetItemText(i, 6, m_pDataProvider->m_vectDevicePara[i].m_strParaName);
		m_list1.SetItemText(i, 7, m_pDataProvider->m_vectDevicePara[i].m_strControlAddrIndex);
		m_list1.SetItemText(i, 8, m_pDataProvider->m_vectDevicePara[i].m_strStateAddrIndex);
		m_list1.SetItemText(i, 9, m_pDataProvider->m_vectDevicePara[i].m_strDescription);
	}
	return 0;
}


void CEditDeviceParaTabDlg::OnCbnSelchangeLine()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString LineName,ModuleName;
	m_LineComboBox.GetWindowText(LineName);
	
	ModuleComboxPaint(LineName);

	m_ModuleComboBox.GetWindowText(ModuleName);
	DeviceComboxPaint(LineName, ModuleName);
}


void CEditDeviceParaTabDlg::OnCbnSelchangeModule()
{
	CString LineName, ModuleName;
	m_LineComboBox.GetWindowText(LineName);
	m_ModuleComboBox.GetWindowText(ModuleName);
	
	DeviceComboxPaint(LineName, ModuleName);

}


void CEditDeviceParaTabDlg::OnNMRClickLi1EditdeviceparaTabdlg(NMHDR *pNMHDR, LRESULT *pResult)
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
	m_list1.SetItemState(m_nSelectedItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITPARADLG_POP_MENU1);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);//�õ���괦//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	
	switch (nItem1)
	{
	case ID_PARA_MODIFY:  //�Ҽ��˵����޸�//
		m_DeviceParaDlg.m_nSelectedItem = m_nSelectedItem;
		m_DeviceParaDlg.DoModal();
		break;
	case ID_PARA_DELETE:
		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbDevicePara, m_pDataProvider->m_vectDevicePara[m_nSelectedItem].m_Id);		
		m_pDataProvider->m_vectDevicePara.erase(m_pDataProvider->m_vectDevicePara.begin() + m_nSelectedItem);
		break;
	default:
		break;
	}

	ListOnPaint();

}




void CEditDeviceParaTabDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
