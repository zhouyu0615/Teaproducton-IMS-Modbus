
// TeaProductionLine IMS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTeaProductionLineIMSApp: 
// �йش����ʵ�֣������ TeaProductionLine IMS.cpp
//

class CTeaProductionLineIMSApp : public CWinApp
{
public:
	CTeaProductionLineIMSApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTeaProductionLineIMSApp theApp;