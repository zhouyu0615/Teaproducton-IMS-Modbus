
// MainDlg.h : ͷ�ļ�
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

// CMainDlg �Ի���
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg);
	friend class CTeaProductionLineIMSDlgAutoProxy;

// ����
public:
	CMainDlg(CWnd* pParent = NULL);	   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAINDLG };       //IDD_TEAPRODUCTIONLINEIMS_DIALOG

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CTeaProductionLineIMSDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
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
	CUserManageDlg m_UserManageDlg;                      //�û��������//
	afx_msg void OnSysteminit();    
	afx_msg void OnPlcpara();       
	CInitDlg m_InitDlg;                                 //��ʼ������//
	CEditPlcParaDlg m_EditPlcParaDlg;                   //PLC�������ý���//
	afx_msg void OnSize(UINT nType, int cx, int cy);    //�����С�����仯ʱ����Ӧ����//
	POINT m_OldSize;                                    //�����С�����仯ǰ�ĳߴ�//
	void ReSize();                                      //ʹ�ؼ�����Ӧ�Ի����С�ı仯//
	CStatusBarCtrl *m_StatBar;                          //״̬��//
	CVedioChiDlg m_VedioChiDlg;                         //��Ƶ����ӽ���//
	CDeviceChiDlg m_DeviceChiDlg;                       //�豸����ӽ���//
	CConfigChiDlg m_ConfigChiDlg;                       //�䷽���ӽ���//
	afx_msg void OnBnClickedBtVedio();
	int m_nCurChiDlg;                                    //��ʶ��ǰ����������ʾ���Ӵ��壬1��ʶ��Ƶ��أ�2��ʾ�豸��أ�3�䷽��4������ͼ//
	afx_msg void OnBnClickedBtDevice();
	CDataProvider *m_pDataProvider = CDataProvider::getInstance();      //����Դ//
	afx_msg void OnBnClickedBtConfig();
	afx_msg void OnDestroy();
	CComboBox m_CityComboBox;
	CEdit m_edWeatherInfo;
	afx_msg void OnBnClickedUpdateWeather();

	CWeather m_weather;
	CLoginDlg m_LoginDlg;							//��¼����///

	CModbus m_Modbus;                               //modbus���ӱ���

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CStatic  m_Font;	//   ///
	CFont FontDate;		//����������///
	CFont FontTime;		//ʱ��������///
public:
	afx_msg void OnLogout();
	afx_msg void OnPlcstatus();
	CPlcStatusDlg m_PLCStatusDlg;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedStopPollModbus();
};
