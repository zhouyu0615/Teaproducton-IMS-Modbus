#pragma once
#include "afxwin.h"
#include "DataProvider.h"


// CEditDevicePopDlg �Ի���

class CEditDevicePopDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDevicePopDlg)

public:
	CEditDevicePopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditDevicePopDlg();

// �Ի�������
	enum { IDD = IDD_EDITDEVICE_POPDLG };
	int m_nSelectedItem;
	CDataProvider* m_pDataProVider = CDataProvider::getInstance();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_LineComboBox;
	CComboBox m_ModuleComboBox;
	CEdit m_DeviceNameEdit;
	CEdit m_DeviceTypeEdit;
	CEdit m_DescriptionEdit;
	afx_msg void OnCbnSelchangeCo1EditdevicePopdlg();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
