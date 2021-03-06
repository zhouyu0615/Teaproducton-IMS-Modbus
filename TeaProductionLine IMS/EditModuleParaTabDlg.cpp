// EditModuleParaTabDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditModuleParaTabDlg.h"
#include "afxdialogex.h"


// CEditModuleParaTabDlg 对话框

IMPLEMENT_DYNAMIC(CEditModuleParaTabDlg, CDialog)

CEditModuleParaTabDlg::CEditModuleParaTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditModuleParaTabDlg::IDD, pParent)
{

}

CEditModuleParaTabDlg::~CEditModuleParaTabDlg()
{
}

void CEditModuleParaTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LI1_EDITMODULEPARA_TABDLG, m_list1);
	DDX_Control(pDX, IDC_CO2_EDITMODULEPARA_TABDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO3_EDITMODULEPARA_TABDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_CO4_EDITMODULEPARA_TABDLG, m_PlcComboBox);
	DDX_Control(pDX, IDC_ED4_EDITMODULEPARA_TABDLG, m_UnitEdit);
	DDX_Control(pDX, IDC_ED1_EDITMODULEPARA_TABDLG, m_NameEdit);
	DDX_Control(pDX, IDC_ED2_EDITMODULEPARA_TABDLG, m_AddrTypeEdit);
	DDX_Control(pDX, IDC_ED3_EDITMODULEPARA_TABDLG, m_ReadAddrIndexEdit);
	DDX_Control(pDX, IDC_CO1_EDITMODULEPARA_TABDLG, m_ValueTypeComboBox);
	DDX_Control(pDX, IDC_ED3_EDITMODULEPARA_TABDLG2, m_WriteAddrIndex);
}


BEGIN_MESSAGE_MAP(CEditModuleParaTabDlg, CDialog)
	ON_BN_CLICKED(IDC_BT1_EDITMODULEPARA_TABDLG, &CEditModuleParaTabDlg::OnBnClickedAddItem)
	ON_BN_CLICKED(IDC_BT2_EDITMODULEPARA_TABDLG, &CEditModuleParaTabDlg::OnBnClickedClearEdit)
	ON_BN_CLICKED(IDC_BT3_EDITMODULEPARA_TABDLG, &CEditModuleParaTabDlg::OnBnClickedClearAll)
	ON_CBN_SELCHANGE(IDC_CO2_EDITMODULEPARA_TABDLG, &CEditModuleParaTabDlg::OnCbnSelchangeCo2EditmoduleparaTabdlg)
	ON_NOTIFY(NM_RCLICK, IDC_LI1_EDITMODULEPARA_TABDLG, &CEditModuleParaTabDlg::OnNMRClickLi1EditmoduleparaTabdlg)
END_MESSAGE_MAP()


// CEditModuleParaTabDlg 消息处理程序


BOOL CEditModuleParaTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MyOnPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEditModuleParaTabDlg::OnBnClickedAddItem()
{
	CProcessPara tempProPara;
	m_LineComboBox.GetWindowText(tempProPara.m_strProductionLineName);
	m_ModuleComboBox.GetWindowText(tempProPara.m_strProcessModuleName);
	m_PlcComboBox.GetWindowText(tempProPara.m_strPlcName);
	m_UnitEdit.GetWindowText(tempProPara.m_strUnit);

	m_NameEdit.GetWindowText(tempProPara.m_strParaName);
	m_AddrTypeEdit.GetWindowText(tempProPara.m_strAddressType);
	m_ReadAddrIndexEdit.GetWindowText(tempProPara.m_strReadAddrIndex);
	m_WriteAddrIndex.GetWindowText(tempProPara.m_strWriteAddrIndex);

	tempProPara.m_ValueType=m_ValueTypeComboBox.GetCurSel();

	tempProPara.m_IsConfig = GetConfigState();
	tempProPara.m_IsVisible = GetVisibleState();
	
	if (!m_ParaCheckUtil.ProcessParaCheck(tempProPara))
	{
		m_pDataProvider->AddProcessParaToDatabase(tempProPara);
	}

	ListOnPaint();
}

void CEditModuleParaTabDlg::OnBnClickedClearEdit()
{
	m_NameEdit.SetWindowText(_T(""));
	m_UnitEdit.SetWindowText(_T(""));
	m_ReadAddrIndexEdit.SetWindowText(_T(""));
	m_WriteAddrIndex.SetWindowText(_T(""));
	m_AddrTypeEdit.SetWindowText(_T(""));
}


void CEditModuleParaTabDlg::OnBnClickedClearAll()
{
	// TODO:  在此添加控件通知处理程序代码
	int nResult = MessageBox(_T("该操作将删除所有的工艺参数，是否继续当前操作？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
	if (nResult == IDYES)
	{
		m_pDataProvider->m_vectProModulePara.clear();
		m_pDataProvider->DeleteDbTable(CDataProvider::tbProcessPara);		
		ListOnPaint();
	}
}



void CEditModuleParaTabDlg::OnCbnSelchangeCo2EditmoduleparaTabdlg()
{
	// TODO:  在此添加控件通知处理程序代码
	CString LineName;
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);
}


void CEditModuleParaTabDlg::OnNMRClickLi1EditmoduleparaTabdlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
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
	CPoint point1;        //存储鼠标位置的临时变量//
	GetCursorPos(&point1);//得到光标处//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//确保右键点击在哪菜单出现在哪，并返回所选的菜单项//

	switch (nItem1)
	{
	case ID_PARA_MODIFY:  //右键菜单：修改//
		m_ModuleParaPopDlg.m_nSelectedItem = m_nSelectedItem;
		m_ModuleParaPopDlg.DoModal();
		break;
	case ID_PARA_DELETE:
		m_pDataProvider->DeleteDbTableItem(CDataProvider::tbProcessPara, m_pDataProvider->m_vectProModulePara[m_nSelectedItem].m_Id);
		m_pDataProvider->m_vectProModulePara.erase(m_pDataProvider->m_vectProModulePara.begin() + m_nSelectedItem);
		break;
	default:
		break;
	}

	ListOnPaint();

}



int CEditModuleParaTabDlg::MyOnPaint()
{
	ListOnPaint(); //绘制列表框//

	ShowConfigState(TRUE);
	ShowVisibleState(TRUE);

	ValTypeComboBoxInit();

	LineComboxPaint();
	CString LineName, ModuleName;
	//m_LineComboBox.GetLBText(0, LineName);
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);

	PlcComboxPaint();

	return 0;
}

int CEditModuleParaTabDlg::LineComboxPaint()
{
	m_LineComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProductionLine.size(); i++)
	{
		m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[i].m_strLineName);
		m_LineComboBox.SetCurSel(0);
	}
	
	return 0;
}

int CEditModuleParaTabDlg::ModuleComboxPaint(CString LineName)
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

int CEditModuleParaTabDlg::PlcComboxPaint()
{
	m_PlcComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectPlc.size(); i++)
	{
		m_PlcComboBox.AddString(m_pDataProvider->m_vectPlc[i].m_strPlcName);
		m_PlcComboBox.SetCurSel(0);
	}
	
	return 0;
}

int CEditModuleParaTabDlg::ValTypeComboBoxInit()
{
	m_ValueTypeComboBox.ResetContent();
	m_ValueTypeComboBox.AddString(_T("Bool"));
	m_ValueTypeComboBox.AddString(_T("Byte"));
	m_ValueTypeComboBox.AddString(_T("Short"));
	m_ValueTypeComboBox.AddString(_T("Long"));
	m_ValueTypeComboBox.AddString(_T("Float"));
	m_ValueTypeComboBox.AddString(_T("Double"));

	m_ValueTypeComboBox.SetCurSel(3);

	return 0;
}

int CEditModuleParaTabDlg::ListOnPaint()
{
	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");
	//设置列表控件风格//
	CRect rect1;
	m_list1.GetWindowRect(&rect1);
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//清空列表//
	m_list1.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_list1.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_list1.DeleteColumn(i);

	m_list1.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_list1.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 17, -1);
	m_list1.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(3, _T("所属模块"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(4, _T("所属PLC"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(5, _T("参数名称"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(6, _T("地址类型"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(7, _T("读地址"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(8, _T("写地址"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(9, _T("数据类型"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(10, _T("是否配方"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(11, _T("是否可见"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	m_list1.InsertColumn(12, _T("单位"), LVCFMT_CENTER, rect1.Width() / 17 * 2, -1);
	//填写表单内容//
	int length = m_pDataProvider->m_vectProModulePara.size();
	for (int i = 0; i < length; i++)
	{
		litem.iItem = i;
		CString str;
		str.Format(_T("%d"), i + 1);
		m_list1.InsertItem(&litem);
		m_list1.SetItemText(i, 1, str);
		m_list1.SetItemText(i, 2, m_pDataProvider->m_vectProModulePara[i].m_strProductionLineName);
		m_list1.SetItemText(i, 3, m_pDataProvider->m_vectProModulePara[i].m_strProcessModuleName);
		m_list1.SetItemText(i, 4, m_pDataProvider->m_vectProModulePara[i].m_strPlcName);
		m_list1.SetItemText(i, 5, m_pDataProvider->m_vectProModulePara[i].m_strParaName);
		m_list1.SetItemText(i, 6, m_pDataProvider->m_vectProModulePara[i].m_strAddressType);
		m_list1.SetItemText(i, 7, m_pDataProvider->m_vectProModulePara[i].m_strReadAddrIndex);
		m_list1.SetItemText(i, 8, m_pDataProvider->m_vectProModulePara[i].m_strWriteAddrIndex);
		m_list1.SetItemText(i, 9, m_pDataProvider->m_vectProModulePara[i].ConvertValTypeToString());
		m_list1.SetItemText(i, 10, m_pDataProvider->m_vectProModulePara[i].ConvertIsConfigToString());
		m_list1.SetItemText(i, 11, m_pDataProvider->m_vectProModulePara[i].ConvertIsVisibleToString());
		m_list1.SetItemText(i, 12, m_pDataProvider->m_vectProModulePara[i].m_strUnit);
	}
	return 0;
}

void CEditModuleParaTabDlg::ShowConfigState(BOOL IsConfig)
{
	if (IsConfig) //是
	{
		((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_TABDLG))->SetCheck(TRUE);//选上
		((CButton *)GetDlgItem(IDC_RA2_EDITMODULEPARA_TABDLG))->SetCheck(FALSE);// 不选上
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_TABDLG))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RA2_EDITMODULEPARA_TABDLG))->SetCheck(TRUE);
	}

}
void CEditModuleParaTabDlg::ShowVisibleState(BOOL IsVisible)
{
	if (IsVisible)
	{
		((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_TABDLG))->SetCheck(TRUE);//选上
		((CButton *)GetDlgItem(IDC_RA4_EDITMODULEPARA_TABDLG))->SetCheck(FALSE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_TABDLG))->SetCheck(FALSE);//选上
		((CButton *)GetDlgItem(IDC_RA4_EDITMODULEPARA_TABDLG))->SetCheck(TRUE);
	}

}

BOOL CEditModuleParaTabDlg::GetConfigState()
{
	if (((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_TABDLG))->GetCheck())
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CEditModuleParaTabDlg::GetVisibleState()
{
	if (((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_TABDLG))->GetCheck())
	{
		return TRUE;
	}
	return FALSE;
}



void CEditModuleParaTabDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}
