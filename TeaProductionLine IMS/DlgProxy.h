
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CMainDlg;


// CTeaProductionLineIMSDlgAutoProxy ����Ŀ��

class CTeaProductionLineIMSDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CTeaProductionLineIMSDlgAutoProxy)

	CTeaProductionLineIMSDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CMainDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CTeaProductionLineIMSDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTeaProductionLineIMSDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

