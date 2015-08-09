// ConfigChiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "ConfigChiDlg.h"
#include "afxdialogex.h"


// CConfigChiDlg �Ի���

IMPLEMENT_DYNAMIC(CConfigChiDlg, CDialogEx)

CConfigChiDlg::CConfigChiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigChiDlg::IDD, pParent)
{

}

CConfigChiDlg::~CConfigChiDlg()
{
}

void CConfigChiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabConfig);
}


BEGIN_MESSAGE_MAP(CConfigChiDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CConfigChiDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CConfigChiDlg ��Ϣ�������


BOOL CConfigChiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ����ǩ�ؼ�//
	m_tabConfig.InsertItem(0, _T("�����䷽"));
	m_tabConfig.InsertItem(1, _T("�½��䷽"));
	m_OldConfigGraChiDlg.Create(IDD_OLDCONFIG_GRACHIDLG, &m_tabConfig);
	m_NewConfigGraChiDlg.Create(IDD_NEWCONFIG_GRACHIDLG, &m_tabConfig);
	CRect tabRect;                                                       // ��ǩ�ؼ��ͻ�����λ�úʹ�С//	
	m_tabConfig.GetClientRect(&tabRect);                                 // ��ȡ��ǩ�ؼ��ͻ���Rect //
	tabRect.left += 1;                                                   // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ //  
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	m_OldConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);// ���ݵ����õ�tabRect�����ӶԻ���//
	m_NewConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//�л���ǩ����//
void CConfigChiDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CRect tabRect;               // ��ǩ�ؼ��ͻ�����Rect//
	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ//
	m_tabConfig.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tabConfig.GetCurSel())  //����ѡ��ı�ǩ����ʾ��Ӧ�Ի���//
	{
	case 0:
		if (m_NewConfigGraChiDlg.m_bIsAddConfig==true)
		{
			m_OldConfigGraChiDlg.ReInitDlg();
			m_NewConfigGraChiDlg.m_bIsAddConfig = false;
		}
		m_OldConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_NewConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		m_OldConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_NewConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}

	*pResult = 0;
}
