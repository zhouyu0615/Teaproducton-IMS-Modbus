#pragma once
#include "AllUserManageDlg.h"
#include "EditPassWordDlg.h"

// CUserManageDlg �Ի���

class CUserManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserManageDlg)

public:
	CUserManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserManageDlg();
	CAllUserManageDlg m_AllUserManageDlg;   //�����û��������//
	CEditPassWordDlg m_EditPasswordDlg;     //�޸��������//

// �Ի�������
	enum { IDD = IDD_USERMANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtAlluser();
	afx_msg void OnBnClickedBtEditpassword();
	afx_msg void OnBnClickedBtLogout();
};
