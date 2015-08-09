// tbFormula.h : CtbFormula ���ʵ��



// CtbFormula ʵ��

// ���������� 2015��8��1�� ������, 08:12

#include "stdafx.h"
#include "tbFormula.h"
IMPLEMENT_DYNAMIC(CtbFormula, CRecordset)

CtbFormula::CtbFormula(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_FormulaName = "";
	m_FormulaId = 0;
	m_ProductionLineId = 0;
	m_ProductionLineName = "";
	m_ProcessParaId = 0;
	m_ProcessParaName = "";
	m_DefaultValue = 0.0;
	m_ParaValueUnit = "";
	m_Note = "";
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_IsDefaultFormula = 0;
	m_IsCurrentFormula = 0;
	m_nFields = 14;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbFormula::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbFormula::GetDefaultSQL()
{
	return _T("[dbo].[tbFormula]");
}

void CtbFormula::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[FormulaName]"), m_FormulaName);
	RFX_Long(pFX, _T("[FormulaId]"), m_FormulaId);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Long(pFX, _T("[ProcessParaId]"), m_ProcessParaId);
	RFX_Text(pFX, _T("[ProcessParaName]"), m_ProcessParaName);
	RFX_Single(pFX, _T("[DefaultValue]"), m_DefaultValue);
	RFX_Text(pFX, _T("[ParaValueUnit]"), m_ParaValueUnit);
	RFX_Text(pFX, _T("[Note]"), m_Note);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Long(pFX, _T("[IsDefaultFormula]"), m_IsDefaultFormula);
	RFX_Long(pFX, _T("[IsCurrentFormula]"), m_IsCurrentFormula);

}
/////////////////////////////////////////////////////////////////////////////
// CtbFormula ���

#ifdef _DEBUG
void CtbFormula::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbFormula::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


