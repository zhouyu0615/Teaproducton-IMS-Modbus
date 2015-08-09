// tbProcessModule.h : CtbProcessModule ���ʵ��



// CtbProcessModule ʵ��

// ���������� 2015��7��29�� ������, 20:09

#include "stdafx.h"
#include "tbProcessModule.h"
IMPLEMENT_DYNAMIC(CtbProcessModule, CRecordset)

CtbProcessModule::CtbProcessModule(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_ModuleName = "";
	m_ModuleTypeId = 0;
	m_UserId = 0;
	m_Description = "";
	m_ProductionLineName = "";
	m_ProductionLineId = 0;
	m_SortIndex = 0;
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbProcessModule::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbProcessModule::GetDefaultSQL()
{
	return _T("[dbo].[tbProcessModule]");
}

void CtbProcessModule::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Text(pFX, _T("[ModuleName]"), m_ModuleName);
	RFX_Long(pFX, _T("[ModuleTypeId]"), m_ModuleTypeId);
	RFX_Long(pFX, _T("[UserId]"), m_UserId);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Long(pFX, _T("[SortIndex]"), m_SortIndex);

}
/////////////////////////////////////////////////////////////////////////////
// CtbProcessModule ���

#ifdef _DEBUG
void CtbProcessModule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbProcessModule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


