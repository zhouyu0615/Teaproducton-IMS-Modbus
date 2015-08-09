// tbStatePara.h : CtbStatePara ������

#pragma once

// ���������� 2015��7��27�� ����һ, 09:27

class CtbStatePara : public CRecordset
{
public:
	CtbStatePara(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbStatePara)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_Id;
	CTime	m_CreatedDateTime;
	CTime	m_LastUpdatedDateTime;
	long	m_ProductionLineId;
	long	m_ProcessModuleId;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	long	m_PLCId;
	CStringA	m_ParaName;
	CStringA	m_AddressIndex;
	long	m_ParaValue;
	CStringA	m_Description;
	CStringA	m_PlcName;

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


