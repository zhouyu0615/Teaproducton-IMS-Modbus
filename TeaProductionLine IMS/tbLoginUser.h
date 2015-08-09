// tbLoginUser.h : CtbLoginUser ������

#pragma once

// ���������� 2015��7��26�� ������, 08:58

class CtbLoginUser : public CRecordset
{
public:
	CtbLoginUser(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbLoginUser)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_Id;
	CStringA	m_LoginName;
	CStringA	m_LoginPassWd;
	CTime	m_LastLoginInTime;
	CTime	m_CreatedDateTime;
	long	m_PermissionLevel;
	CTime	m_LastUpdatedDateTime;
	long	m_IsAutoLogin;
	long	m_IsRememberPasswd;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


