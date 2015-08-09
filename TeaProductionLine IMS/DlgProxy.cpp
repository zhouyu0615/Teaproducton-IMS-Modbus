
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "DlgProxy.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTeaProductionLineIMSDlgAutoProxy

IMPLEMENT_DYNCREATE(CTeaProductionLineIMSDlgAutoProxy, CCmdTarget)

CTeaProductionLineIMSDlgAutoProxy::CTeaProductionLineIMSDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMainDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainDlg)))
		{
			m_pDialog = reinterpret_cast<CMainDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CTeaProductionLineIMSDlgAutoProxy::~CTeaProductionLineIMSDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CTeaProductionLineIMSDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CTeaProductionLineIMSDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTeaProductionLineIMSDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_ITeaProductionLineIMS ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E6E392E5-4C19-4ED0-B641-A0A468860781}
static const IID IID_ITeaProductionLineIMS =
{ 0xE6E392E5, 0x4C19, 0x4ED0, { 0xB6, 0x41, 0xA0, 0xA4, 0x68, 0x86, 0x7, 0x81 } };

BEGIN_INTERFACE_MAP(CTeaProductionLineIMSDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CTeaProductionLineIMSDlgAutoProxy, IID_ITeaProductionLineIMS, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {1C8FCBEA-5A91-49C9-BCE6-A437D8025D2E}
IMPLEMENT_OLECREATE2(CTeaProductionLineIMSDlgAutoProxy, "TeaProductionLineIMS.Application", 0x1c8fcbea, 0x5a91, 0x49c9, 0xbc, 0xe6, 0xa4, 0x37, 0xd8, 0x2, 0x5d, 0x2e)


// CTeaProductionLineIMSDlgAutoProxy ��Ϣ�������
