#pragma once
#include <vector>
#include "DevicePara.h"
// CDeviceContrlPopDlg �Ի���

class CDeviceContrlPopDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceContrlPopDlg)

public:
	CDeviceContrlPopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceContrlPopDlg();
	std::vector<CDevicePara> m_vDevicePara;             //�����������ݴ浱ǰ��ѡ�е��豸����//

// �Ի�������
	enum { IDD = IDD_DEVICECONTRL_POPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
	CFont m_myFont;            //�Զ�������//
};
