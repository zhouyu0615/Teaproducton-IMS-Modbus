// EditDevicePopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditDevicePopDlg.h"
#include "afxdialogex.h"
#include "DeviceClass.h"


// CEditDevicePopDlg �Ի���

IMPLEMENT_DYNAMIC(CEditDevicePopDlg, CDialogEx)

CEditDevicePopDlg::CEditDevicePopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDevicePopDlg::IDD, pParent)
{

}

CEditDevicePopDlg::~CEditDevicePopDlg()
{
}

void CEditDevicePopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CO1_EDITDEVICE_POPDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO2_EDITDEVICE_POPDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_ED1_EDITDEVICE_POPDLG, m_DeviceNameEdit);
	DDX_Control(pDX, IDC_ED2_EDITDEVICE_POPDLG, m_DeviceTypeEdit);
	DDX_Control(pDX, IDC_ED3_EDITDEVICE_POPDLG, m_DescriptionEdit);
}


BEGIN_MESSAGE_MAP(CEditDevicePopDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CO1_EDITDEVICE_POPDLG, &CEditDevicePopDlg::OnCbnSelchangeCo1EditdevicePopdlg)
	ON_BN_CLICKED(IDOK, &CEditDevicePopDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditDevicePopDlg ��Ϣ�������


void CEditDevicePopDlg::OnCbnSelchangeCo1EditdevicePopdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ModuleComboBox.ResetContent();

	CString LineName;
	m_LineComboBox.GetWindowText(LineName);

	for (int i = 0; i < m_pDataProVider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProVider->m_vectProcessModule[i].m_strProductionLineName == LineName)
		{
			m_ModuleComboBox.AddString(m_pDataProVider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}
	m_ModuleComboBox.SetCurSel(0);

}


void CEditDevicePopDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString LineName, ModuleName, DeviceName, DeviceType;
	m_LineComboBox.GetWindowText(LineName);
	m_ModuleComboBox.GetWindowText(ModuleName);
	m_DeviceNameEdit.GetWindowText(DeviceName);
	m_DeviceTypeEdit.GetWindowText(DeviceType);

	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_strProductionLineName = LineName;
	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_strProcessModuleName = ModuleName;
	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_strDeviceName = DeviceName;
	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_strDeviceType = DeviceType;

	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_ProductionLineId = m_pDataProVider->FindProLineId(LineName);
	m_pDataProVider->m_vectDevice[m_nSelectedItem].m_ProcessModuleId = m_pDataProVider->FindProModuleId(LineName, ModuleName);

	int DeviceId = m_pDataProVider->m_vectDevice[m_nSelectedItem].m_Id;
	m_pDataProVider->UpdateTableItem(CDataProvider::tbDevice, DeviceId);
	
	m_pDataProVider->UpdataRelatedToDevice(DeviceId, DeviceName);

	CDialogEx::OnOK();
}


BOOL CEditDevicePopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDeviceClass tempDevice = m_pDataProVider->m_vectDevice[m_nSelectedItem];

	m_LineComboBox.ResetContent();
	m_LineComboBox.AddString(tempDevice.m_strProductionLineName);
	m_LineComboBox.SetCurSel(0);
	//��ʣ�����������ӵ�LineComboBox��
	for (int i = 0; i < m_pDataProVider->m_vectProductionLine.size();i++)
	{
		if (m_pDataProVider->m_vectProductionLine[i].m_strLineName != tempDevice.m_strProductionLineName)
		{
			m_LineComboBox.AddString(m_pDataProVider->m_vectProductionLine[i].m_strLineName);
		}
	}

	m_ModuleComboBox.ResetContent();
	m_ModuleComboBox.AddString(tempDevice.m_strProcessModuleName);
	m_ModuleComboBox.SetCurSel(0);
	//��ѡ�е��������µĿɹ�ѡ���ģ����뵽ModuleComboBox����ȥ
	for (int i = 0; i < m_pDataProVider->m_vectProcessModule.size();i++)
	{
		if (m_pDataProVider->m_vectProcessModule[i].m_strProductionLineName == tempDevice.m_strProductionLineName && (m_pDataProVider->m_vectProcessModule[i].m_strProcessModuleName != tempDevice.m_strProcessModuleName))
		{
			m_ModuleComboBox.AddString(m_pDataProVider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}

	m_DeviceNameEdit.SetWindowText(tempDevice.m_strDeviceName);
	m_DeviceTypeEdit.SetWindowText(tempDevice.m_strDeviceType);
	//m_DescriptionEdit.SetWindowText(tempDevice.m_)



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEditDevicePopDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
