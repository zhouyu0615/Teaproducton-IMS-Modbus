// ConfigChiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "ConfigChiDlg.h"
#include "afxdialogex.h"


// CConfigChiDlg 对话框

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


// CConfigChiDlg 消息处理程序


BOOL CConfigChiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化标签控件//
	m_tabConfig.InsertItem(0, _T("已有配方"));
	m_tabConfig.InsertItem(1, _T("新建配方"));
	m_OldConfigGraChiDlg.Create(IDD_OLDCONFIG_GRACHIDLG, &m_tabConfig);
	m_NewConfigGraChiDlg.Create(IDD_NEWCONFIG_GRACHIDLG, &m_tabConfig);
	CRect tabRect;                                                       // 标签控件客户区的位置和大小//	
	m_tabConfig.GetClientRect(&tabRect);                                 // 获取标签控件客户区Rect //
	tabRect.left += 1;                                                   // 调整tabRect，使其覆盖范围适合放置标签页 //  
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	m_OldConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);// 根据调整好的tabRect放置子对话框//
	m_NewConfigGraChiDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//切换标签界面//
void CConfigChiDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CRect tabRect;               // 标签控件客户区的Rect//
	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页//
	m_tabConfig.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tabConfig.GetCurSel())  //根据选择的标签，显示相应对话框//
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
