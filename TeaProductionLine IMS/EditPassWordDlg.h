#pragma once
#include "DataProvider.h"
#include "LoginUser.h"
#include "LoginDlg.h"
// CEditPassWordDlg �Ի���

class CEditPassWordDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPassWordDlg)

public:
	CEditPassWordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPassWordDlg();

// �Ի�������
	enum { IDD = IDD_EDITPASSWORDDLG };

	CDataProvider *m_pDataProvider = CDataProvider::getInstance(); //����Դ///
	long CurrentId;		//����ǰ��¼�û���ID����CurrentId///
	int UserNumber;											//��ס�û����Ҹ���///

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBt1SaveEditpassworddlg();
	static long LoginUser_CurrentId;				//��ǰ��¼�û���ID��,�û��޸�����ʱ����ID����///

	virtual BOOL OnInitDialog();
};
