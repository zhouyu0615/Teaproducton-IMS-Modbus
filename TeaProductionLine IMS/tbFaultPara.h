// tbFaultPara.h : CtbFaultPara ������

#pragma once

// ���������� 2015��7��26�� ������, 08:57

class CtbFaultPara : public CRecordset
{
public:
	CtbFaultPara(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbFaultPara)

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
	long	m_DeviceId;
	long	m_ProductionLineId;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	CStringA	m_DeviceName;
	CStringA	m_PlcName;
	CStringA	m_Description;
	long	m_ParaValue;
	CStringA	m_ParaName;
	CStringA	m_AddressIndex;

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


