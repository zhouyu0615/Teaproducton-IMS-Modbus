#pragma once
#include "afxwin.h"
#include "DataProvider.h"
#include "LoginUser.h"

// CLoginDlg �Ի���

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGINDLG };

	CDataProvider *m_LoginDataProvider = CDataProvider::getInstance(); //����Դ///

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
protected:
	HICON m_hIcon;			//  ///

	//��������Ϣӳ�亯��///
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	static long m_PermissionLevel;                 //�û�Ȩ�ޱ�ʶ��0�������Ա��1�������Ա//
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
	CComboBox m_LoginUserName;
	CLoginUser LoginUser;					//�����û�����///
	CString LoginUser_PermissionLevel;		//ȷ���û�Ȩ���ǹ���Ա���ǲ���Ա///

	static long LoginUser_CurrentId;				//��ǰ��¼�û���ID��,�û��޸�����ʱ����ID����///
	static long LoginUser_CurrentPermissionLevel;	//��ǰ��¼�û���Ȩ�ޣ������ж��û����޹��������û�Ȩ��///

	 
	CEdit m_EditPasswd;
	afx_msg void OnCbnSelchangeComboUsername();
	CButton CheckPassWd;
	CButton CheckAutoLogin;


//	afx_msg void OnCbnEditchangeComboUsername();
	afx_msg void OnCbnSelchangeComboUserright();
};
