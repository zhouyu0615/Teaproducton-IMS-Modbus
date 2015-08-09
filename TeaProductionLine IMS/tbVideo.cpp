// tbVideo.h : CtbVideo ���ʵ��



// CtbVideo ʵ��

// ���������� 2015��7��29�� ������, 20:10

#include "stdafx.h"
#include "tbVideo.h"
IMPLEMENT_DYNAMIC(CtbVideo, CRecordset)

CtbVideo::CtbVideo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_ProcessModuleId = 0;
	m_Port = 0;
	m_ProductionLineName = "";
	m_ProcessModuleName = "";
	m_ProductionLineId = 0;
	m_Description = "";
	m_VideoName = "";
	m_IPAddr = "";
	m_SortIndex = 0;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbVideo::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbVideo::GetDefaultSQL()
{
	return _T("[dbo].[tbVideo]");
}

void CtbVideo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Long(pFX, _T("[ProcessModuleId]"), m_ProcessModuleId);
	RFX_Long(pFX, _T("[Port]"), m_Port);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[VideoName]"), m_VideoName);
	RFX_Text(pFX, _T("[IPAddr]"), m_IPAddr);
	RFX_Long(pFX, _T("[SortIndex]"), m_SortIndex);

}
/////////////////////////////////////////////////////////////////////////////
// CtbVideo ���

#ifdef _DEBUG
void CtbVideo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbVideo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


