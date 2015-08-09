// DeviceContrlPopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "DeviceContrlPopDlg.h"
#include "afxdialogex.h"


// CDeviceContrlPopDlg �Ի���

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


// CDeviceContrlPopDlg ��Ϣ�������


BOOL CDeviceContrlPopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_myFont.CreatePointFont(150, _T("΢���ź�"), NULL);
	if (!m_vDevicePara.empty())
	{
		if (m_vDevicePara[0].m_StateValue==1)
		{
			GetDlgItem(IDC_PIC_GREENLIGHT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PIC_WHITELIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ST_STATE)->SetWindowText(_T("��������"));
		}
		else
		{
			GetDlgItem(IDC_PIC_GREENLIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PIC_WHITELIGHT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ST_STATE)->SetWindowText(_T("ֹͣ"));
		}
		GetDlgItem(IDC_ST_DEVICENAME)->SetFont(&m_myFont);
		GetDlgItem(IDC_ST_DEVICENAME)->SetWindowText(m_vDevicePara[0].m_strDeviceName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
