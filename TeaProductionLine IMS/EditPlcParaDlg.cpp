// EditPlcParaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "EditPlcParaDlg.h"
#include "afxdialogex.h"


// CEditPlcParaDlg �Ի���

IMPLEMENT_DYNAMIC(CEditPlcParaDlg, CDialog)

CEditPlcParaDlg::CEditPlcParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPlcParaDlg::IDD, pParent)
{

}

CEditPlcParaDlg::~CEditPlcParaDlg()
{
}

void CEditPlcParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_EDITPLCPARADLG, m_tab1);
}


BEGIN_MESSAGE_MAP(CEditPlcParaDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_EDITPLCPARADLG, &CEditPlcParaDlg::OnTcnSelchangeTabEditplcparadlg)
END_MESSAGE_MAP()


// CEditPlcParaDlg ��Ϣ�������


BOOL CEditPlcParaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ����ǩ�ؼ�//
	m_tab1.InsertItem(0, _T("���ղ���"));
	m_tab1.InsertItem(1, _T("�豸����"));
	m_tab1.InsertItem(2, _T("���ϲ���"));
	m_tab1.InsertItem(3, _T("״̬����"));
	m_EditModuleParaTabDlg.Create(IDD_EDITMODULEPARA_TABDLG, &m_tab1);
	m_EditDeviceParaTabDlg.Create(IDD_EDITDEVICEPARA_TABDLG, &m_tab1);
	m_EditErrorParaTabDlg.Create(IDD_EDITERRORPARA_TABDLG, &m_tab1);
	m_EditStateParaTabDlg.Create(IDD_EDITSTATEPARA_TABDLG, &m_tab1);
	CRect tabRect;          // ��ǩ�ؼ��ͻ�����λ�úʹ�С//	
	m_tab1.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect //
	tabRect.left += 1;      // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ //  
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;	   
	m_EditModuleParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);// ���ݵ����õ�tabRect�����ӶԻ���//
	m_EditDeviceParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_EditErrorParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_EditStateParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//��ǩ�ؼ�ѡ����Ŀ�����ı�ʱ����Ӧ����//
void CEditPlcParaDlg::OnTcnSelchangeTabEditplcparadlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CRect tabRect;               // ��ǩ�ؼ��ͻ�����Rect//

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ//
	m_tab1.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tab1.GetCurSel())  //����ѡ��ı�ǩ����ʾ��Ӧ�Ի���//
	{
	case 0:
		m_EditModuleParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_EditDeviceParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditErrorParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditStateParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		m_EditModuleParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditDeviceParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_EditErrorParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditStateParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		m_EditModuleParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditDeviceParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditErrorParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_EditStateParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_EditModuleParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditDeviceParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditErrorParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_EditStateParaTabDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}


void CEditPlcParaDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
