#pragma once
#include "afxwin.h"
#include "DataProvider.h"
#include "StatePara.h"
#include "ParaCheckUtil.h"


// CEditStateParaPopDlg �Ի���

class CEditStateParaPopDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditStateParaPopDlg)

public:
	CEditStateParaPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditStateParaPopDlg();

// �Ի�������
	enum { IDD = IDD_EDITSTATEPARA_POPDLG };
	int m_nSelectedItem;
	CDataProvider* m_pDataProvider = CDataProvider::getInstance();

	CParaCheckUtil m_ParaCheckUtil;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeLine();
	CComboBox m_LineComboBox;
	CComboBox m_ModuleComboBox;
	CComboBox m_PlcComboBox;
	CEdit m_NameEdit;
	CEdit m_AddrIndexEdit;
	CEdit m_NoteEdit;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	int ModuleComboxPaint(CString LineName);
	virtual void OnOK();
	afx_msg void OnCbnSelchangeCo3EditstateparaPopdlg();
};
