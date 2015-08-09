// tbStatePara.h : CtbStatePara ���ʵ��



// CtbStatePara ʵ��

// ���������� 2015��7��27�� ����һ, 09:27

#include "stdafx.h"
#include "tbStatePara.h"
IMPLEMENT_DYNAMIC(CtbStatePara, CRecordset)

CtbStatePara::CtbStatePara(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_ProductionLineId = 0;
	m_ProcessModuleId = 0;
	m_ProductionLineName = "";
	m_ProcessModuleName = "";
	m_PLCId = 0;
	m_ParaName = "";
	m_AddressIndex = "";
	m_ParaValue = 0;
	m_Description = "";
	m_PlcName = "";
	m_nFields = 13;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbStatePara::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbStatePara::GetDefaultSQL()
{
	return _T("[dbo].[tbStatePara]");
}

void CtbStatePara::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Long(pFX, _T("[ProcessModuleId]"), m_ProcessModuleId);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Long(pFX, _T("[PLCId]"), m_PLCId);
	RFX_Text(pFX, _T("[ParaName]"), m_ParaName);
	RFX_Text(pFX, _T("[AddressIndex]"), m_AddressIndex);
	RFX_Long(pFX, _T("[ParaValue]"), m_ParaValue);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[PlcName]"), m_PlcName);

}
/////////////////////////////////////////////////////////////////////////////
// CtbStatePara ���

#ifdef _DEBUG
void CtbStatePara::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbStatePara::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


