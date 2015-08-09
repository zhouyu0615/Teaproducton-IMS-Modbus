#pragma once
#include "afxcmn.h"

#include "PlcClass.h"
#include "DataProvider.h"
#include "afxwin.h"


// CPlcStatusDlg 对话框

class CPlcStatusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlcStatusDlg)

public:
	CPlcStatusDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlcStatusDlg();

// 对话框数据
	enum { IDD = IDD_PLCSTATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDataProvider * m_pDataProvider;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartcycle();
	afx_msg void OnBnClickedStopcycle();
	CListCtrl m_PlcStatusList;

	void OnListPaint();
	void UpdatePlcState();


	BOOL m_IsStartMonitor;
	
	virtual BOOL OnInitDialog();
	CButton m_btStartMonitor;
	CButton m_btStopMonitor;

	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
