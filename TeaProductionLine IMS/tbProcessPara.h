// tbProcessPara.h : CtbProcessPara ������

#pragma once

// ���������� 2015��7��31�� ������, 15:14

class CtbProcessPara : public CRecordset
{
public:
	CtbProcessPara(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbProcessPara)

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
	long	m_PLCId;
	long	m_ProcessModuleId;
	long	m_ProductionLineId;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	CStringA	m_PlcName;
	CStringA	m_Description;
	float	m_ParaValue;
	CStringA	m_ParaName;
	long	m_IsConfig;
	long	m_IsVisible;
	long	m_ValueType;
	CStringA	m_ReadAddressIndex;
	CStringA	m_AddressType;
	CStringA	m_WriteAddressIndex;
	CStringA	m_Units;

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


