#pragma once
#include "LoginDlg.h"

// CEditUserPopDlg �Ի���

class CEditUserPopDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditUserPopDlg)

public:
	CEditUserPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditUserPopDlg();

// �Ի�������
	enum { IDD = IDD_EDITUSER_POPDLG };
	CDataProvider *m_pDataProvider = CDataProvider::getInstance(); //����Դ///

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	long EditUserId;		//�б��ѡ���û���ID///
	long ManagerId;			//�洢����Ա��ID///
	int EditUserIndex;
	virtual BOOL OnInitDialog();
};
