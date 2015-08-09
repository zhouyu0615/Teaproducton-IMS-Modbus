#pragma once
#include "afxcmn.h"
#include "DataProvider.h"
#include "EditUserPopDlg.h"
#include "afxwin.h"


// CAllUserManageDlg �Ի���

class CAllUserManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CAllUserManageDlg)

public:
	CAllUserManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAllUserManageDlg();

// �Ի�������
	enum { IDD = IDD_ALLUSERMANAGEDLG };
	int index;//�����ݴ����Ա�����б��ʱ������ڵ��б�///
    //static long UserID;		//�б����ѡ���û���ID///
	CDataProvider *m_pDataProvider=CDataProvider::getInstance(); //����Դ///


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_UserInfo;			//�û���������б��ĳ�Ա����///
	afx_msg void OnBnClickedBt1Adduser();
	virtual BOOL OnInitDialog();
	void MyOnPint();
	afx_msg void OnBnClickedBt2Clearall();
	afx_msg void OnNMRClickLi1Allusermanagedlg(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edUserName;
	CEdit m_edPassword;
};
