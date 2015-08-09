#pragma once
#include "afxcmn.h"
#include "OldConfigGraChiDlg.h"
#include "NewConfigGraChiDlg.h"

// CConfigChiDlg 对话框

class CConfigChiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigChiDlg)

public:
	CConfigChiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigChiDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_CHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabConfig;                                  //标签控件//
	COldConfigGraChiDlg m_OldConfigGraChiDlg;              //修改配方界面//
	CNewConfigGraChiDlg m_NewConfigGraChiDlg;              //新建配方界面//
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
