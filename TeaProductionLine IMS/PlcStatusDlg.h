#pragma once
#include "afxcmn.h"

#include "PlcClass.h"
#include "DataProvider.h"
#include "afxwin.h"


// CPlcStatusDlg �Ի���

class CPlcStatusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlcStatusDlg)

public:
	CPlcStatusDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlcStatusDlg();

// �Ի�������
	enum { IDD = IDD_PLCSTATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
