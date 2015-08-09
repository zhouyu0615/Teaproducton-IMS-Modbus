// PlcStatusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "PlcStatusDlg.h"
#include "afxdialogex.h"




// CPlcStatusDlg �Ի���

IMPLEMENT_DYNAMIC(CPlcStatusDlg, CDialogEx)

CPlcStatusDlg::CPlcStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlcStatusDlg::IDD, pParent)
{
	m_pDataProvider = CDataProvider::getInstance();
	m_IsStartMonitor = FALSE;
}

CPlcStatusDlg::~CPlcStatusDlg()
{
}

void CPlcStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PlcStatusList);
	DDX_Control(pDX, IDC_STARTCYCLE, m_btStartMonitor);
	DDX_Control(pDX, IDC_STOPCYCLE, m_btStopMonitor);
}


BEGIN_MESSAGE_MAP(CPlcStatusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_STARTCYCLE, &CPlcStatusDlg::OnBnClickedStartcycle)
	ON_BN_CLICKED(IDC_STOPCYCLE, &CPlcStatusDlg::OnBnClickedStopcycle)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPlcStatusDlg ��Ϣ�������


void CPlcStatusDlg::OnBnClickedStartcycle()
{
	m_IsStartMonitor = TRUE;
	m_btStartMonitor.EnableWindow(FALSE);
	m_btStopMonitor.EnableWindow(TRUE);
	  
}





void CPlcStatusDlg::OnBnClickedStopcycle()
{
	m_IsStartMonitor = FALSE;
	m_btStartMonitor.EnableWindow(TRUE);
	m_btStopMonitor.EnableWindow(FALSE);

}


void CPlcStatusDlg::UpdatePlcState()
{
	m_PlcStatusList.SetRedraw(FALSE);
	int length = m_pDataProvider->m_vectPlc.size();
	for (int i = 0; i < length; i++)
	{
	m_PlcStatusList.SetItemText(i, 4, m_pDataProvider->m_vectPlc[i].GetConectedString());
	}

	m_PlcStatusList.SetRedraw(TRUE);
	m_PlcStatusList.Invalidate();
	m_PlcStatusList.UpdateWindow();

}

void CPlcStatusDlg::OnListPaint()
{
	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");
	//�����б�ؼ����//
	CRect rect1;
	m_PlcStatusList.GetWindowRect(&rect1);
	m_PlcStatusList.SetExtendedStyle(m_PlcStatusList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//����б�//
	m_PlcStatusList.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_PlcStatusList.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_PlcStatusList.DeleteColumn(i);

	m_PlcStatusList.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_PlcStatusList.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 8, -1);
	m_PlcStatusList.InsertColumn(2, _T("PLC��"), LVCFMT_CENTER, rect1.Width() / 8 * 2, -1);
	m_PlcStatusList.InsertColumn(3, _T("IP��ַ"), LVCFMT_CENTER, rect1.Width() / 8 * 3, -1);
	m_PlcStatusList.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, rect1.Width() / 8 * 1.8, -1);
	//��д������//
	int length = m_pDataProvider->m_vectPlc.size();
	for (int i = 0; i < length; i++)
	{
		litem.iItem = i;
		CString str;
		str.Format(_T("%d"), i + 1);
		m_PlcStatusList.InsertItem(&litem);
		m_PlcStatusList.SetItemText(i, 1, str);
		m_PlcStatusList.SetItemText(i, 2, m_pDataProvider->m_vectPlc[i].m_strPlcName);
		m_PlcStatusList.SetItemText(i, 3, m_pDataProvider->m_vectPlc[i].m_strIPAddr);
		m_PlcStatusList.SetItemText(i, 4, m_pDataProvider->m_vectPlc[i].GetConectedString());				
	}
}

BOOL CPlcStatusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	SetTimer(1, 1000,NULL); //����ˢ�½���Ķ�ʱ��

	m_btStartMonitor.EnableWindow(TRUE);
	m_btStopMonitor.EnableWindow(FALSE);
	OnListPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void CPlcStatusDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CPlcStatusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_IsStartMonitor)
	{
		UpdatePlcState();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
