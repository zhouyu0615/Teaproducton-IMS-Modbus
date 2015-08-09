#pragma once
#include "DataProvider.h"
#include <vector>
#include "FormulaClass.h"
#include "ProcessModulePara.h"
#include "afxcmn.h"

// CAddConfigParaPopDlg �Ի���

class CAddConfigParaPopDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddConfigParaPopDlg)

public:
	CAddConfigParaPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddConfigParaPopDlg();

// �Ի�������
	enum { IDD = IDD_ADDCONFIGPARA_POPDLG };
	CDataProvider *m_pDataProvider = CDataProvider::getInstance();    //����Դ//
	//std::vector<CProcessPara> m_vectOldPara;         //�ѽ����䷽�Ĳ���//
	std::vector<CProcessPara> m_vectNewPara;           //��ѡ����//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
};
