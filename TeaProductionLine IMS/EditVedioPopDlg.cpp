// EditVedioPopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditVedioPopDlg.h"
#include "afxdialogex.h"
#include "VideoClass.h"


// CEditVedioPopDlg �Ի���

IMPLEMENT_DYNAMIC(CEditVedioPopDlg, CDialog)

CEditVedioPopDlg::CEditVedioPopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditVedioPopDlg::IDD, pParent)
{

}

CEditVedioPopDlg::~CEditVedioPopDlg()
{
}

void CEditVedioPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CO1_EDITVEDIO_POPDLG, m_LineComboBox);
	DDX_Control(pDX, IDC_CO2_EDITVEDIO_POPDLG, m_ModuleComboBox);
	DDX_Control(pDX, IDC_ED1_EDITVEDIO_POPDLG, m_VideoNameEdit);
	DDX_Control(pDX, IDC_ED2_EDITVEDIO_POPDLG, m_IPAddrEdit);
	DDX_Control(pDX, IDC_ED3_EDITVEDIO_POPDLG, m_PortEdit);
}


BEGIN_MESSAGE_MAP(CEditVedioPopDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CO1_EDITVEDIO_POPDLG, &CEditVedioPopDlg::OnCbnSelchangeCo1EditvedioPopdlg)
	ON_BN_CLICKED(IDOK, &CEditVedioPopDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditVedioPopDlg ��Ϣ�������


void CEditVedioPopDlg::OnCbnSelchangeCo1EditvedioPopdlg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ModuleComboBox.ResetContent();

	CString LineName;
	m_LineComboBox.GetWindowText(LineName);

	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == LineName)
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}
	m_ModuleComboBox.SetCurSel(0);

}


void CEditVedioPopDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_LineComboBox.GetWindowText(m_pDataProvider->m_vectVideo[m_nSelectedItem].m_strProductionLineName);
	m_ModuleComboBox.GetWindowText(m_pDataProvider->m_vectVideo[m_nSelectedItem].m_strProcessModuleName);

	m_VideoNameEdit.GetWindowText(m_pDataProvider->m_vectVideo[m_nSelectedItem].m_strVideoName);
	CString str;
	m_PortEdit.GetWindowText(str);

	m_pDataProvider->m_vectVideo[m_nSelectedItem].m_port = _ttoi(str);

	m_pDataProvider->UpdateTableItem(CDataProvider::tbVideo, m_pDataProvider->m_vectVideo[m_nSelectedItem].m_Id);

	CDialog::OnOK();
}


BOOL CEditVedioPopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CVideoClass tempVideo = m_pDataProvider->m_vectVideo[m_nSelectedItem];
	m_LineComboBox.ResetContent();
	m_LineComboBox.AddString(tempVideo.m_strProductionLineName);
	m_LineComboBox.SetCurSel(0);
	//��ʣ�����������ӵ�LineComboBox��
	for (int i = 0; i < m_pDataProvider->m_vectProductionLine.size(); i++)
	{
		if (m_pDataProvider->m_vectProductionLine[i].m_strLineName != tempVideo.m_strProductionLineName)
		{
			m_LineComboBox.AddString(m_pDataProvider->m_vectProductionLine[i].m_strLineName);
		}
	}

	m_ModuleComboBox.ResetContent();
	m_ModuleComboBox.AddString(tempVideo.m_strProcessModuleName);
	m_ModuleComboBox.SetCurSel(0);
	//��ѡ�е��������µĿɹ�ѡ���ģ����뵽ModuleComboBox����ȥ
	for (int i = 0; i < m_pDataProvider->m_vectProcessModule.size(); i++)
	{
		if (m_pDataProvider->m_vectProcessModule[i].m_strProductionLineName == tempVideo.m_strProductionLineName && (m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName != tempVideo.m_strProcessModuleName))
		{
			m_ModuleComboBox.AddString(m_pDataProvider->m_vectProcessModule[i].m_strProcessModuleName);
		}
	}


	m_VideoNameEdit.SetWindowText(tempVideo.m_strVideoName);
	m_IPAddrEdit.SetWindowText(tempVideo.m_strIPAddr);
	CString str;
	str.Format(_T("%d"), tempVideo.m_port);
	m_PortEdit.SetWindowText(str);




	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEditVedioPopDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
