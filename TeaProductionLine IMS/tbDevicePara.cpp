// tbDevicePara.h : CtbDevicePara ���ʵ��



// CtbDevicePara ʵ��

// ���������� 2015��7��26�� ������, 16:18

#include "stdafx.h"
#include "tbDevicePara.h"
IMPLEMENT_DYNAMIC(CtbDevicePara, CRecordset)

CtbDevicePara::CtbDevicePara(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_ProductionLineId = 0;
	m_ProcessModuleId = 0;
	m_PLCId = 0;
	m_DeviceId = 0;
	m_ProductionLineName = "";
	m_ProcessModuleName = "";
	m_PlcName = "";
	m_DeviceName = "";
	m_ControlValue = 0;
	m_StateValue = 0;
	m_ControlAddrIndex = "";
	m_StateAddrIndex = "";
	m_Description = "";
	m_ParaName = "";
	m_nFields = 17;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbDevicePara::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbDevicePara::GetDefaultSQL()
{
	return _T("[dbo].[tbDevicePara]");
}

void CtbDevicePara::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[PLCId]"), m_PLCId);
	RFX_Long(pFX, _T("[DeviceId]"), m_DeviceId);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Text(pFX, _T("[PlcName]"), m_PlcName);
	RFX_Text(pFX, _T("[DeviceName]"), m_DeviceName);
	RFX_Long(pFX, _T("[ControlValue]"), m_ControlValue);
	RFX_Long(pFX, _T("[StateValue]"), m_StateValue);
	RFX_Text(pFX, _T("[ControlAddrIndex]"), m_ControlAddrIndex);
	RFX_Text(pFX, _T("[StateAddrIndex]"), m_StateAddrIndex);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ParaName]"), m_ParaName);

}
/////////////////////////////////////////////////////////////////////////////
// CtbDevicePara ���

#ifdef _DEBUG
void CtbDevicePara::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbDevicePara::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


