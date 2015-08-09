// tbDevice.h : CtbDevice ���ʵ��



// CtbDevice ʵ��

// ���������� 2015��7��29�� ������, 21:01

#include "stdafx.h"
#include "tbDevice.h"
IMPLEMENT_DYNAMIC(CtbDevice, CRecordset)

CtbDevice::CtbDevice(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_DeviceName = "";
	m_DeviceTypeId = 0;
	m_ProcessModuleId = 0;
	m_ProductionLineName = "";
	m_ProductionLineId = 0;
	m_DeviceType = "";
	m_ProcessModuleName = "";
	m_Description = "";
	m_SortIndex = 0;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbDevice::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbDevice::GetDefaultSQL()
{
	return _T("[dbo].[tbDevice]");
}

void CtbDevice::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Text(pFX, _T("[DeviceName]"), m_DeviceName);
	RFX_Long(pFX, _T("[DeviceTypeId]"), m_DeviceTypeId);
	RFX_Long(pFX, _T("[ProcessModuleId]"), m_ProcessModuleId);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Text(pFX, _T("[DeviceType]"), m_DeviceType);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Long(pFX, _T("[SortIndex]"), m_SortIndex);

}
/////////////////////////////////////////////////////////////////////////////
// CtbDevice ���

#ifdef _DEBUG
void CtbDevice::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbDevice::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


