// AddConfigParaPopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "AddConfigParaPopDlg.h"
#include "afxdialogex.h"


// CAddConfigParaPopDlg �Ի���

IMPLEMENT_DYNAMIC(CAddConfigParaPopDlg, CDialogEx)

CAddConfigParaPopDlg::CAddConfigParaPopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddConfigParaPopDlg::IDD, pParent)
{

}

CAddConfigParaPopDlg::~CAddConfigParaPopDlg()
{
}

void CAddConfigParaPopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CAddConfigParaPopDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddConfigParaPopDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddConfigParaPopDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddConfigParaPopDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAddConfigParaPopDlg ��Ϣ�������


BOOL CAddConfigParaPopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ��LIST1�ı�ͷ//
	CRect rectList1;
	m_list.GetWindowRect(&rectList1);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, rectList1.Width() / 24, -1);
	m_list.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList1.Width() / 13*1.1, -1);
	m_list.InsertColumn(2, _T("����"), LVCFMT_CENTER, rectList1.Width() / 13 * 4, -1);
	m_list.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rectList1.Width() / 13 * 4, -1);
	m_list.InsertColumn(4, _T("�Ƿ���"), LVCFMT_CENTER, rectList1.Width() / 13 * 1.8, -1);
	m_list.InsertColumn(5, _T("��λ"), LVCFMT_CENTER, rectList1.Width() / 13 * 1.6, -1);

	//����б������//
	m_list.DeleteAllItems();
	CString strItem;
	for (int n = 0; n < m_vectNewPara.size();n++)
	{
		m_list.InsertItem(n, _T(""));
		strItem.Format(_T("%d"), n + 1);
		m_list.SetItemText(n, 1, strItem);
		m_list.SetItemText(n, 2, m_vectNewPara[n].m_strParaName);
		m_list.SetItemText(n, 3, m_vectNewPara[n].m_strProcessModuleName);
		if (m_vectNewPara[n].m_IsVisible!=0)
		{
			m_list.SetItemText(n, 4, _T("��"));
		} 
		else
		{
			m_list.SetItemText(n, 4, _T("��"));
		}
		m_list.SetItemText(n, 5, m_vectNewPara[n].m_strUnit);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAddConfigParaPopDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
}

//ȫѡ��ť//
void CAddConfigParaPopDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_list.GetItemCount();n++)
	{
		m_list.SetCheck(n);
	}
}

//��ѡ��ť//
void CAddConfigParaPopDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_list.GetItemCount(); n++)
	{
		if (m_list.GetCheck(n))
			m_list.SetCheck(n, 0);
		else
			m_list.SetCheck(n);
	}
}

//��Ӱ�ť//
void CAddConfigParaPopDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = m_list.GetItemCount()-1; n >=0; n--)
	{
		if (m_list.GetCheck(n))
		{
			m_list.DeleteItem(n);
			m_pDataProvider->m_vectTempProModulePara.push_back(m_vectNewPara[n]);
			m_vectNewPara.erase(m_vectNewPara.begin() + n);
		}
	}
	CString strItem;
	for (int n = 0; n < m_list.GetItemCount();n++)       //���������//
	{
		strItem.Format(_T("%d"), n + 1);
		m_list.SetItemText(n, 1, strItem);
	}
}
