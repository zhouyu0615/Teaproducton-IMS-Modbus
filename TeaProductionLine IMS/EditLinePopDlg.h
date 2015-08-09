#pragma once
#include "afxwin.h"
#include "DataProvider.h"


// CEditLinePopDlg �Ի���

class CEditLinePopDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditLinePopDlg)

public:
	CEditLinePopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditLinePopDlg();

// �Ի�������
	enum { IDD = IDD_EDITLINE_POPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	int m_nSelectedItem;
	CEdit m_editLineName;
	CEdit m_editCapacity;
	CEdit m_editDescription;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

private:
	CDataProvider* m_pDataProvider = CDataProvider::getInstance();

	virtual void OnOK();
};
