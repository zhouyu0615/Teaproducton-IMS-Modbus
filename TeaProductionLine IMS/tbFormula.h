// tbFormula.h : CtbFormula ������

#pragma once

// ���������� 2015��8��1�� ������, 08:12

class CtbFormula : public CRecordset
{
public:
	CtbFormula(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbFormula)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_Id;
	CStringA	m_FormulaName;
	long	m_FormulaId;
	long	m_ProductionLineId;
	CStringA	m_ProductionLineName;
	long	m_ProcessParaId;
	CStringA	m_ProcessParaName;
	float	m_DefaultValue;
	CStringA	m_ParaValueUnit;
	CStringA	m_Note;
	CTime	m_CreatedDateTime;
	CTime	m_LastUpdatedDateTime;
	long	m_IsDefaultFormula;
	long	m_IsCurrentFormula;

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


