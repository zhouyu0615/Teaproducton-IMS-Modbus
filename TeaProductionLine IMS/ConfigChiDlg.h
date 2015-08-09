#pragma once
#include "afxcmn.h"
#include "OldConfigGraChiDlg.h"
#include "NewConfigGraChiDlg.h"

// CConfigChiDlg �Ի���

class CConfigChiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigChiDlg)

public:
	CConfigChiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigChiDlg();

// �Ի�������
	enum { IDD = IDD_CONFIG_CHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabConfig;                                  //��ǩ�ؼ�//
	COldConfigGraChiDlg m_OldConfigGraChiDlg;              //�޸��䷽����//
	CNewConfigGraChiDlg m_NewConfigGraChiDlg;              //�½��䷽����//
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
