#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DataProvider.h"
#include "EditStateParaPopDlg.h"
#include "ParaCheckUtil.h"


// CEditStateParaTabDlg �Ի���

class CEditStateParaTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditStateParaTabDlg)

public:
	CEditStateParaTabDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditStateParaTabDlg();

// �Ի�������
	enum { IDD = IDD_EDITSTATEPARA_TABDLG };
	int m_nSelectedItem;
	CDataProvider* m_pDataProvider = CDataProvider::getInstance();
	CEditStateParaPopDlg m_StateParaPopDlg;

	CParaCheckUtil m_ParaCheckUtil;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list1;
	CComboBox m_LineComboBox;
	CComboBox m_ModuleComboBox;
	CComboBox m_PlcComboBox;
	CEdit m_NameEdit;
	CEdit m_AddrIndexEdit;
	CEdit m_NoteEdit;
	afx_msg void OnBnClickedAddItem();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClearEdit();
	afx_msg void OnBnClickedClearAll();
	afx_msg void OnCbnSelchangeLine();

	int MyOnPaint();
	int ListOnPaint();
	int LineComboxPaint();
	int ModuleComboxPaint(CString LineName);
	int PlcComboxPaint();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
};
