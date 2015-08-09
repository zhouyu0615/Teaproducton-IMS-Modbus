// EditStateParaTabDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditStateParaTabDlg.h"
#include "afxdialogex.h"


// CEditStateParaTabDlg �Ի���

IMPLEMENT_DYNAMIC(CEditStateParaTabDlg, CDialog)

CEditStateParaTabDlg::CEditStateParaTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditStateParaTabDlg::IDD, pParent)
{

}

CEditStateParaTabDlg::~CEditStateParaTabDlg()
{
}

void CEditStateParaTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_CO2_EDITSTATEPARA_TABDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO3_EDITSTATEPARA_TABDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_CO4_EDITSTATEPARA_TABDLG, m_PlcComboBox);
	DDX_Control(pDX, IDC_ED1_EDITSTATEPARA_TABDLG, m_NameEdit);
	DDX_Control(pDX, IDC_ED2_EDITSTATEPARA_TABDLG, m_AddrIndexEdit);
	DDX_Control(pDX, IDC_ED3_EDITSTATEPARA_TABDLG, m_NoteEdit);
}


BEGIN_MESSAGE_MAP(CEditStateParaTabDlg, CDialog)
	ON_BN_CLICKED(IDC_BT1_EDITSTATEPARA_TABDLG, &CEditStateParaTabDlg::OnBnClickedAddItem)
	ON_BN_CLICKED(IDC_BT2_EDITSTATEPARA_TABDLG, &CEditStateParaTabDlg::OnBnClickedClearEdit)
	ON_BN_CLICKED(IDC_BT3_EDITSTATEPARA_TABDLG, &CEditStateParaTabDlg::OnBnClickedClearAll)
	ON_CBN_SELCHANGE(IDC_CO2_EDITSTATEPARA_TABDLG, &CEditStateParaTabDlg::OnCbnSelchangeLine)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CEditStateParaTabDlg::OnNMRClickList1)
END_MESSAGE_MAP()


// CEditStateParaTabDlg ��Ϣ�������


void CEditStateParaTabDlg::OnBnClickedAddItem()
{
	CStatePara tempStatePara;
	m_LineComboBox.GetWindowText(tempStatePara.m_strProductionLineName);
	m_ModuleComboBox.GetWindowText(tempStatePara.m_strProcessModuleName);
	m_PlcComboBox.GetWindowText(tempStatePara.m_strPlcName);

	m_NameEdit.GetWindowText(tempStatePara.m_strParaName);
	m_AddrIndexEdit.GetWindowText(tempStatePara.m_strAddressIndex);
	m_NoteEdit.GetWindowText(tempStatePara.m_strDescription);

	if (!m_ParaCheckUtil.StateParaCheck(tempStatePara))
	{
		m_pDataProvider->AddStateParaToDatabase(tempStatePara);
	}

	ListOnPaint();

}


BOOL CEditStateParaTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��//

	MyOnPaint();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int CEditStateParaTabDlg::MyOnPaint()
{
	ListOnPaint();
	LineComboxPaint();
	CString LineName;
	//m_LineComboBox.GetLBText(0, LineName);
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);
	PlcComboxPaint();

	return 0;
}

void CEditStateParaTabDlg::OnBnClickedClearEdit()
{
	m_NameEdit.SetWindowText(_T(""));
	m_AddrIndexEdit.SetWindowText(_T(""));
	m_NoteEdit.SetWindowText(_T(""));
}


void CEditStateParaTabDlg::OnBnClickedClearAll()
{
	int nResult = MessageBox(_T("�ò�����ɾ�����е�״̬�������Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
	if (nResult == IDYES)
	{ 
		m_pDataProvider->m_vectStatePara.clear();
		m_pDataProvider->DeleteDbTable(CDataProvider::tbStatePara);
		ListOnPaint();
		OnBnClickedClearEdit();
	}

}


void CEditStateParaTabDlg::OnCbnSelchangeLine()
{
	CString LineName;
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);
}


int CEditStateParaTabDlg::LineComboxPaint()
{
	m_LineComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProductionLine.size(); i++)
	{
		m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[i].m_strLineName);
		m_LineComboBox.SetCurSel(0);
	}
	
	return 0;
}

int CEditStateParaTabDlg::ModuleComboxPaint(CString LineName)
{
	m_ModuleComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == LineName)
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
			m_ModuleComboBox.SetCurSel(0);
		}
	}
	
	return 0;
}

int CEditStateParaTabDlg::PlcComboxPaint()
{
	m_PlcComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectPlc.size(); i++)
	{
		m_PlcComboBox.AddString(m_pDataProvider->m_vectPlc[i].m_strPlcName);
		m_PlcComboBox.SetCurSel(0);
	}
	
	return 0;
}

int CEditStateParaTabDlg::ListOnPaint()
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
	m_list1.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 13, -1);
	m_list1.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	m_list1.InsertColumn(3, _T("����ģ��"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	m_list1.InsertColumn(4, _T("����PLC"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	m_list1.InsertColumn(5, _T("��������"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	m_list1.InsertColumn(6, _T("������ַ"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	m_list1.InsertColumn(7, _T("��ע"), LVCFMT_CENTER, rect1.Width() / 13 * 2, -1);
	//��д������//
	int length = m_pDataProvider->m_vectStatePara.size();
	for (int i = 0; i < length; i++)
	{
		litem.iItem = i;
		CString str;
		str.Format(_T("%d"), i + 1);
		m_list1.InsertItem(&litem);
		m_list1.SetItemText(i, 1, str);
		m_list1.SetItemText(i, 2, m_pDataProvider->m_vectStatePara[i].m_strProductionLineName);
		m_list1.SetItemText(i, 3, m_pDataProvider->m_vectStatePara[i].m_strProcessModuleName);
		m_list1.SetItemText(i, 4, m_pDataProvider->m_vectStatePara[i].m_strPlcName);
		m_list1.SetItemText(i, 5, m_pDataProvider->m_vectStatePara[i].m_strParaName);
		m_list1.SetItemText(i, 6, m_pDataProvider->m_vectStatePara[i].m_strAddressIndex);
		m_list1.SetItemText(i, 7, m_pDataProvider->m_vectStatePara[i].m_strDescription);
	}
	return 0;
}



void CEditStateParaTabDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
		m_StateParaPopDlg.m_nSelectedItem = m_nSelectedItem;
		m_StateParaPopDlg.DoModal();
		break;
	case ID_PARA_DELETE:
		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbFaultPara, m_pDataProvider->m_vectStatePara[m_nSelectedItem].m_Id);
		m_pDataProvider->m_vectStatePara.erase(m_pDataProvider->m_vectStatePara.begin() + m_nSelectedItem);
		break;
	default:
		break;
	}

	ListOnPaint();


}


void CEditStateParaTabDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
