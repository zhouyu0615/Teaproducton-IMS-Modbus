// tbVideo.h : CtbVideo ������

#pragma once

// ���������� 2015��7��29�� ������, 20:10

class CtbVideo : public CRecordset
{
public:
	CtbVideo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbVideo)

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
	long	m_ProcessModuleId;
	long	m_Port;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	long	m_ProductionLineId;
	CStringA	m_Description;
	CStringA	m_VideoName;
	CStringA	m_IPAddr;
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


