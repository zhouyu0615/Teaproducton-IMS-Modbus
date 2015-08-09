#pragma once
#include "afxwin.h"
#include "FaultPara.h"
#include "DataProvider.h"
#include "ParaCheckUtil.h"


// CEditErrorParaPopDlg �Ի���

class CEditErrorParaPopDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditErrorParaPopDlg)

public:
	CEditErrorParaPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditErrorParaPopDlg();

// �Ի�������
	enum { IDD = IDD_EDITERRORPARA_POPDLG };
	int m_nSelectedItem;
	CDataProvider* m_pDataProvider = CDataProvider::getInstance();

	CParaCheckUtil m_ParaCheckUtil;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	int LineComboxPaint();
	int ModuleComboxPaint(CString LineName);
	int DeviceComboxPaint(CString LineName, CString ModuleName);
	CComboBox m_LineComboBox;
	CComboBox m_ModuleComboBox;
	CComboBox m_DeviceComboBox;
	CComboBox m_PlcComboBox;
	CEdit m_NameEdit;
	CEdit m_AddrIndexEdit;
	CEdit m_NoteEdit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeLine();
	afx_msg void OnCbnSelchangeModule();
	virtual void OnOK();
};
