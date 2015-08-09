// tbFaultPara.h : CtbFaultPara ���ʵ��



// CtbFaultPara ʵ��

// ���������� 2015��7��26�� ������, 08:57

#include "stdafx.h"
#include "tbFaultPara.h"
IMPLEMENT_DYNAMIC(CtbFaultPara, CRecordset)

CtbFaultPara::CtbFaultPara(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_PLCId = 0;
	m_ProcessModuleId = 0;
	m_DeviceId = 0;
	m_ProductionLineId = 0;
	m_ProductionLineName = "";
	m_ProcessModuleName = "";
	m_DeviceName = "";
	m_PlcName = "";
	m_Description = "";
	m_ParaValue = 0;
	m_ParaName = "";
	m_AddressIndex = "";
	m_nFields = 15;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbFaultPara::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbFaultPara::GetDefaultSQL()
{
	return _T("[dbo].[tbFaultPara]");
}

void CtbFaultPara::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Long(pFX, _T("[PLCId]"), m_PLCId);
	RFX_Long(pFX, _T("[ProcessModuleId]"), m_ProcessModuleId);
	RFX_Long(pFX, _T("[DeviceId]"), m_DeviceId);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Text(pFX, _T("[DeviceName]"), m_DeviceName);
	RFX_Text(pFX, _T("[PlcName]"), m_PlcName);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Long(pFX, _T("[ParaValue]"), m_ParaValue);
	RFX_Text(pFX, _T("[ParaName]"), m_ParaName);
	RFX_Text(pFX, _T("[AddressIndex]"), m_AddressIndex);

}
/////////////////////////////////////////////////////////////////////////////
// CtbFaultPara ���

#ifdef _DEBUG
void CtbFaultPara::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbFaultPara::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


