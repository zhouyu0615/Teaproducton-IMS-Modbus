
// MainDlg.h : 头文件
//

#pragma once
#include "UserManageDlg.h"
#include "InitDlg.h"
#include "EditPlcParaDlg.h"
#include "VedioChiDlg.h"
#include "DeviceChiDlg.h"
#include "DataProvider.h"
#include "ConfigChiDlg.h"
#include "afxwin.h"
#include "Weather.h"
#include "PlcStatusDlg.h"
#include "Modbus.h"


class CTeaProductionLineIMSDlgAutoProxy;
#define ID_VEDIODLG 1
#define ID_DEVICEDLG 2
#define ID_CONFIGDLG 3
#define ID_TOTALPROCESSLINE 4

// CMainDlg 对话框
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg);
	friend class CTeaProductionLineIMSDlgAutoProxy;

// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAINDLG };       //IDD_TEAPRODUCTIONLINEIMS_DIALOG

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CTeaProductionLineIMSDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedBtUser();
	CUserManageDlg m_UserManageDlg;                      //用户管理界面//
	afx_msg void OnSysteminit();    
	afx_msg void OnPlcpara();       
	CInitDlg m_InitDlg;                                 //初始化界面//
	CEditPlcParaDlg m_EditPlcParaDlg;                   //PLC参数配置界面//
	afx_msg void OnSize(UINT nType, int cx, int cy);    //窗体大小发生变化时的响应函数//
	POINT m_OldSize;                                    //窗体大小发生变化前的尺寸//
	void ReSize();                                      //使控件自适应对话框大小的变化//
	CStatusBarCtrl *m_StatBar;                          //状态栏//
	CVedioChiDlg m_VedioChiDlg;                         //视频监控子界面//
	CDeviceChiDlg m_DeviceChiDlg;                       //设备监控子界面//
	CConfigChiDlg m_ConfigChiDlg;                       //配方配子界面//
	afx_msg void OnBnClickedBtVedio();
	int m_nCurChiDlg;                                    //标识当前主窗体内显示的子窗体，1标识视频监控，2表示设备监控，3配方，4生产总图//
	afx_msg void OnBnClickedBtDevice();
	CDataProvider *m_pDataProvider = CDataProvider::getInstance();      //数据源//
	afx_msg void OnBnClickedBtConfig();
	afx_msg void OnDestroy();
	CComboBox m_CityComboBox;
	CEdit m_edWeatherInfo;
	afx_msg void OnBnClickedUpdateWeather();

	CWeather m_weather;
	CLoginDlg m_LoginDlg;							//登录界面///

	CModbus m_Modbus;                               //modbus连接变量

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CStatic  m_Font;	//   ///
	CFont FontDate;		//日期字体风格///
	CFont FontTime;		//时间字体风格///
public:
	afx_msg void OnLogout();
	afx_msg void OnPlcstatus();
	CPlcStatusDlg m_PLCStatusDlg;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedStopPollModbus();
};
