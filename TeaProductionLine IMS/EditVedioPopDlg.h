#pragma once
#include "afxwin.h"
#include "DataProvider.h"


// CEditVedioPopDlg �Ի���

class CEditVedioPopDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditVedioPopDlg)

public:
	CEditVedioPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditVedioPopDlg();

// �Ի�������
	enum { IDD = IDD_EDITVEDIO_POPDLG };
	int m_nSelectedItem;
	CDataProvider* m_pDataProvider = CDataProvider::getInstance();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_LineComboBox;
	CComboBox m_ModuleComboBox;
	CEdit m_VideoNameEdit;
	CEdit m_IPAddrEdit;
	CEdit m_PortEdit;
	afx_msg void OnCbnSelchangeCo1EditvedioPopdlg();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
