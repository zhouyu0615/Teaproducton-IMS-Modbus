// tbLoginUser.h : CtbLoginUser ���ʵ��



// CtbLoginUser ʵ��

// ���������� 2015��7��26�� ������, 08:58

#include "stdafx.h"
#include "tbLoginUser.h"
IMPLEMENT_DYNAMIC(CtbLoginUser, CRecordset)

CtbLoginUser::CtbLoginUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_LoginName = "";
	m_LoginPassWd = "";
	m_LastLoginInTime;
	m_CreatedDateTime;
	m_PermissionLevel = 0;
	m_LastUpdatedDateTime;
	m_IsAutoLogin = 0;
	m_IsRememberPasswd = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbLoginUser::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbLoginUser::GetDefaultSQL()
{
	return _T("[dbo].[tbLoginUser]");
}

void CtbLoginUser::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[LoginName]"), m_LoginName);
	RFX_Text(pFX, _T("[LoginPassWd]"), m_LoginPassWd);
	RFX_Date(pFX, _T("[LastLoginInTime]"), m_LastLoginInTime);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Long(pFX, _T("[PermissionLevel]"), m_PermissionLevel);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Long(pFX, _T("[IsAutoLogin]"), m_IsAutoLogin);
	RFX_Long(pFX, _T("[IsRememberPasswd]"), m_IsRememberPasswd);

}
/////////////////////////////////////////////////////////////////////////////
// CtbLoginUser ���

#ifdef _DEBUG
void CtbLoginUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbLoginUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


