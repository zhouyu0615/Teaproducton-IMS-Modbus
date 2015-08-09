// tbDevicePara.h : CtbDevicePara ������

#pragma once

// ���������� 2015��7��26�� ������, 16:18

class CtbDevicePara : public CRecordset
{
public:
	CtbDevicePara(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbDevicePara)

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
	long	m_PLCId;
	long	m_DeviceId;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	CStringA	m_PlcName;
	CStringA	m_DeviceName;
	long	m_ControlValue;
	long	m_StateValue;
	CStringA	m_ControlAddrIndex;
	CStringA	m_StateAddrIndex;
	CStringA	m_Description;
	CStringA	m_ParaName;

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


