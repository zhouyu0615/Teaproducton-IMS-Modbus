// tbDevice.h : CtbDevice ������

#pragma once

// ���������� 2015��7��29�� ������, 21:01

class CtbDevice : public CRecordset
{
public:
	CtbDevice(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbDevice)

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
	CStringA	m_DeviceName;
	long	m_DeviceTypeId;
	long	m_ProcessModuleId;
	CStringA	m_ProductionLineName;
	long	m_ProductionLineId;
	CStringA	m_DeviceType;
	CStringA	m_ProcessModuleName;
	CStringA	m_Description;
	long	m_SortIndex;

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


