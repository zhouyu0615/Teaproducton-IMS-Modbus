// tbPLc.h : CtbPLc ������

#pragma once

// ���������� 2015��7��29�� ������, 20:10

class CtbPLc : public CRecordset
{
public:
	CtbPLc(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbPLc)

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
	CStringA	m_PLCName;
	long	m_UserId;
	CStringA	m_Description;
	CStringA	m_ProductionLineName;
	long	m_ProductionLineId;
	CStringA	m_strIPAddr;
	long	m_ReadStartAddr;
	long	m_ReadLength;
	long	m_WriteStartAddr;
	long	m_WriteLength;
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


