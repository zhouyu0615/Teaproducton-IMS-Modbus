#pragma once
#include "afxcmn.h"
#include "EditDeviceParaTabDlg.h"
#include "EditErrorParaTabDlg.h"
#include "EditModuleParaTabDlg.h"
#include "EditStateParaTabDlg.h"


// CEditPlcParaDlg �Ի���

class CEditPlcParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPlcParaDlg)

public:
	CEditPlcParaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPlcParaDlg();

// �Ի�������
	enum { IDD = IDD_EDITPLCPARADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab1;
	virtual BOOL OnInitDialog();
	CEditDeviceParaTabDlg m_EditDeviceParaTabDlg;     //�ĸ���ǩ����//
	CEditErrorParaTabDlg m_EditErrorParaTabDlg;
	CEditModuleParaTabDlg m_EditModuleParaTabDlg;
	CEditStateParaTabDlg m_EditStateParaTabDlg;
	afx_msg void OnTcnSelchangeTabEditplcparadlg(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
};
