// DeviceContrlPopDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "DeviceContrlPopDlg.h"
#include "afxdialogex.h"


// CDeviceContrlPopDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceContrlPopDlg, CDialogEx)

CDeviceContrlPopDlg::CDeviceContrlPopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeviceContrlPopDlg::IDD, pParent)
{

}

CDeviceContrlPopDlg::~CDeviceContrlPopDlg()
{
}

void CDeviceContrlPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeviceContrlPopDlg, CDialogEx)
END_MESSAGE_MAP()


// CDeviceContrlPopDlg 消息处理程序


BOOL CDeviceContrlPopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_myFont.CreatePointFont(150, _T("微软雅黑"), NULL);
	if (!m_vDevicePara.empty())
	{
		if (m_vDevicePara[0].m_StateValue==1)
		{
			GetDlgItem(IDC_PIC_GREENLIGHT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PIC_WHITELIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ST_STATE)->SetWindowText(_T("正在运行"));
		}
		else
		{
			GetDlgItem(IDC_PIC_GREENLIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PIC_WHITELIGHT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ST_STATE)->SetWindowText(_T("停止"));
		}
		GetDlgItem(IDC_ST_DEVICENAME)->SetFont(&m_myFont);
		GetDlgItem(IDC_ST_DEVICENAME)->SetWindowText(m_vDevicePara[0].m_strDeviceName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
