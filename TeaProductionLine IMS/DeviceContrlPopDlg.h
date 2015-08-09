#pragma once
#include <vector>
#include "DevicePara.h"
// CDeviceContrlPopDlg 对话框

class CDeviceContrlPopDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceContrlPopDlg)

public:
	CDeviceContrlPopDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceContrlPopDlg();
	std::vector<CDevicePara> m_vDevicePara;             //容器，用于暂存当前被选中的设备参数//

// 对话框数据
	enum { IDD = IDD_DEVICECONTRL_POPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
	CFont m_myFont;            //自定义字体//
};
