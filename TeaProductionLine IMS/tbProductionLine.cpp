// tbProductionLine.h : CtbProductionLine ���ʵ��



// CtbProductionLine ʵ��

// ���������� 2015��7��29�� ������, 19:34

#include "stdafx.h"
#include "tbProductionLine.h"
IMPLEMENT_DYNAMIC(CtbProductionLine, CRecordset)

CtbProductionLine::CtbProductionLine(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_LineName = "";
	m_UserId = 0;
	m_Capacity = "";
	m_Description = "";
	m_SortIndex = 0;
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbProductionLine::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbProductionLine::GetDefaultSQL()
{
	return _T("[dbo].[tbProductionLine]");
}

void CtbProductionLine::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Text(pFX, _T("[LineName]"), m_LineName);
	RFX_Long(pFX, _T("[UserId]"), m_UserId);
	RFX_Text(pFX, _T("[Capacity]"), m_Capacity);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Long(pFX, _T("[SortIndex]"), m_SortIndex);

}
/////////////////////////////////////////////////////////////////////////////
// CtbProductionLine ���

#ifdef _DEBUG
void CtbProductionLine::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbProductionLine::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


