// EditModuleParaPopDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditModuleParaPopDlg.h"
#include "afxdialogex.h"


// CEditModuleParaPopDlg 对话框

IMPLEMENT_DYNAMIC(CEditModuleParaPopDlg, CDialog)

CEditModuleParaPopDlg::CEditModuleParaPopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditModuleParaPopDlg::IDD, pParent)
{

}

CEditModuleParaPopDlg::~CEditModuleParaPopDlg()
{
}

void CEditModuleParaPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CO2_EDITMODULEPARA_POPDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO3_EDITMODULEPARA_POPDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_CO4_EDITMODULEPARA_POPDLG, m_PlcComboBox);
	DDX_Control(pDX, IDC_ED4_EDITMODULEPARA_POPDLG, m_UnitEdit);
	DDX_Control(pDX, IDC_ED1_EDITMODULEPARA_POPDLG, m_NameEdit);
	DDX_Control(pDX, IDC_ED2_EDITMODULEPARA_POPDLG, m_AddrTypeEdit);
	DDX_Control(pDX, IDC_ED3_EDITMODULEPARA_POPDLG, m_ReadAddrIndexEdit);
	DDX_Control(pDX, IDC_ED3_EDITMODULEPARA_POPDLG2, m_WriteAddrIndexEdit);
	DDX_Control(pDX, IDC_CO1_EDITMODULEPARA_POPDLG, m_ValueTypeComboBox);
}


BEGIN_MESSAGE_MAP(CEditModuleParaPopDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditModuleParaPopDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CO2_EDITMODULEPARA_POPDLG, &CEditModuleParaPopDlg::OnCbnSelchangeLine)
END_MESSAGE_MAP()


// CEditModuleParaPopDlg 消息处理程序


void CEditModuleParaPopDlg::OnBnClickedOk()
{
	CProcessPara tempProcessPara = m_pDataProvider->m_vectProModulePara[m_nSelectedItem];
	m_LineComboBox.GetWindowText(tempProcessPara.m_strProductionLineName);
	m_ModuleComboBox.GetWindowText(tempProcessPara.m_strProcessModuleName);

	m_PlcComboBox.GetWindowText(tempProcessPara.m_strPlcName);

	m_UnitEdit.GetWindowText(tempProcessPara.m_strUnit);

	m_NameEdit.GetWindowText(tempProcessPara.m_strParaName);
	m_AddrTypeEdit.GetWindowText(tempProcessPara.m_strAddressType);
	m_ReadAddrIndexEdit.GetWindowText(tempProcessPara.m_strReadAddrIndex);
	m_WriteAddrIndexEdit.GetWindowText(tempProcessPara.m_strWriteAddrIndex);

	tempProcessPara.m_ValueType = m_ValueTypeComboBox.GetCurSel();

	tempProcessPara.m_IsConfig = GetConfigState();
	tempProcessPara.m_IsVisible = GetVisibleState();

	if (!m_ParaCheckUtil.ProcessParaCheck(tempProcessPara, m_nSelectedItem))
	{
		m_pDataProvider->m_vectProModulePara[m_nSelectedItem] = tempProcessPara;
		m_pDataProvider->UpdateTableItem(CDataProvider::tbProcessPara, m_pDataProvider->m_vectProModulePara[m_nSelectedItem].m_Id);
	}


	CDialog::OnOK();
}


void CEditModuleParaPopDlg::OnCbnSelchangeLine()
{
	// TODO:  在此添加控件通知处理程序代码
	CString LineName;
	m_LineComboBox.GetWindowText(LineName);
	ModuleComboxPaint(LineName);

}




BOOL CEditModuleParaPopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CProcessPara tempFormula = m_pDataProvider->m_vectProModulePara[m_nSelectedItem];

	m_NameEdit.SetWindowText(tempFormula.m_strParaName);
	m_UnitEdit.SetWindowText(tempFormula.m_strUnit);
	m_AddrTypeEdit.SetWindowText(tempFormula.m_strAddressType);
	m_ReadAddrIndexEdit.SetWindowText(tempFormula.m_strReadAddrIndex);
	m_WriteAddrIndexEdit.SetWindowText(tempFormula.m_strWriteAddrIndex);

	ShowConfigState(tempFormula.m_IsConfig);
	ShowVisibleState(tempFormula.m_IsVisible);

	ValTypeComboBoxInit();
	m_ValueTypeComboBox.SetCurSel(tempFormula.m_ValueType);


	m_LineComboBox.ResetContent();
	m_LineComboBox.AddString(tempFormula.m_strProductionLineName);
	m_LineComboBox.SetCurSel(0);
	//把剩余的可选生产线加入到Combobox中
	for (int i = 0; i < m_pDataProvider->m_vectProductionLine.size(); i++)
	{
		if (m_pDataProvider->m_vectProductionLine[i].m_strLineName != tempFormula.m_strProductionLineName)
		{
			m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[i].m_strLineName);
		}
	}

	m_ModuleComboBox.ResetContent();
	m_ModuleComboBox.AddString(tempFormula.m_strProcessModuleName);
	m_ModuleComboBox.SetCurSel(0);
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName != tempFormula.m_strProcessModuleName && (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == tempFormula.m_strProductionLineName))
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}

	m_PlcComboBox.ResetContent();
	m_PlcComboBox.AddString(tempFormula.m_strPlcName);
	m_PlcComboBox.SetCurSel(0);
	for (int i = 0; i < m_pDataProvider->m_vectPlc.size(); i++)
	{
		if (m_pDataProvider->m_vectPlc[i].m_strPlcName != tempFormula.m_strPlcName)
		{
			m_PlcComboBox.AddString(m_pDataProvider->m_vectPlc[i].m_strPlcName);
		}

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

int CEditModuleParaPopDlg::ValTypeComboBoxInit()
{
	m_ValueTypeComboBox.ResetContent();
	m_ValueTypeComboBox.AddString(_T("Bool"));
	m_ValueTypeComboBox.AddString(_T("Byte"));
	m_ValueTypeComboBox.AddString(_T("Short"));
	m_ValueTypeComboBox.AddString(_T("Long"));
	m_ValueTypeComboBox.AddString(_T("Float"));
	m_ValueTypeComboBox.AddString(_T("Double"));

	return 0;
}

int CEditModuleParaPopDlg::ModuleComboxPaint(CString LineName)
{
	m_ModuleComboBox.ResetContent();
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == LineName)
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}
	m_ModuleComboBox.SetCurSel(0);
	return 0;
}


void CEditModuleParaPopDlg::ShowConfigState(BOOL IsConfig)
{
	if (IsConfig) //是
	{
		((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_POPDLG))->SetCheck(TRUE);//选上
		((CButton *)GetDlgItem(IDC_RA2_EDITMODULEPARA_POPDLG))->SetCheck(FALSE);// 不选上
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_POPDLG))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RA2_EDITMODULEPARA_POPDLG))->SetCheck(TRUE);
	}

}
void CEditModuleParaPopDlg::ShowVisibleState(BOOL IsVisible)
{
	if (IsVisible)
	{
		((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_POPDLG))->SetCheck(TRUE);//选上
		((CButton *)GetDlgItem(IDC_RA4_EDITMODULEPARA_POPDLG))->SetCheck(FALSE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_POPDLG))->SetCheck(FALSE);//选上
		((CButton *)GetDlgItem(IDC_RA4_EDITMODULEPARA_POPDLG))->SetCheck(TRUE);
	}

}

BOOL CEditModuleParaPopDlg::GetConfigState()
{
	if (((CButton *)GetDlgItem(IDC_RA1_EDITMODULEPARA_POPDLG))->GetCheck())
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CEditModuleParaPopDlg::GetVisibleState()
{
	if (((CButton *)GetDlgItem(IDC_RA3_EDITMODULEPARA_POPDLG))->GetCheck())
	{
		return TRUE;
	}
	return FALSE;
}



void CEditModuleParaPopDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}
