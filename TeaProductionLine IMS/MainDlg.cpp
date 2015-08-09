
// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "MainDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg �Ի���


IMPLEMENT_DYNAMIC(CMainDlg, CDialog);

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	m_nCurChiDlg = 1;                                 //��ʼ����ǰ��ʾ�Ӵ���ı�ʶ��//

	//��ȡ���ݿ⵽����Դ//
	m_pDataProvider->InitDataProvider();
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size();n++)  //Ϊÿ�������������䷽//
	{
		m_pDataProvider->SetCurConfig(m_pDataProvider->m_vectProductionLine[n].m_Id, 1);
	}
}

CMainDlg::~CMainDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����

	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CityComboBox);
	DDX_Control(pDX, IDC_EDIT1, m_edWeatherInfo);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_USER, &CMainDlg::OnBnClickedBtUser)
	ON_COMMAND(IDM_SYSTEMINIT, &CMainDlg::OnSysteminit)
	ON_COMMAND(IDM_PLCPARA, &CMainDlg::OnPlcpara)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_VEDIO, &CMainDlg::OnBnClickedBtVedio)
	ON_BN_CLICKED(IDC_BT_DEVICE, &CMainDlg::OnBnClickedBtDevice)
	ON_BN_CLICKED(IDC_BT_CONFIG, &CMainDlg::OnBnClickedBtConfig)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedUpdateWeather)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_COMMAND(IDM_LOGOUT, &CMainDlg::OnLogout)
	ON_COMMAND(IDM_PLCSTATUS, &CMainDlg::OnPlcstatus)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDlg::OnBnClickedStopPollModbus)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();


	//�ж��Ƿ����û�ѡ�����Զ���¼������ֱ�ӵ�¼//
	bool bIsAnyAutoLoginUser = false;    //�Ƿ����û�ѡ���Զ���¼//
	for (int n = 0; n < m_pDataProvider->m_vectLoginUser.size();n++)   //�����û�ѡ�����Զ���¼��������ֵ����ǰ�û�//
	{
		if (m_pDataProvider->m_vectLoginUser[n].m_IsAutoLogin)
		{
			CLoginDlg::LoginUser_CurrentId = m_pDataProvider->m_vectLoginUser[n].m_Id;
			CLoginDlg::LoginUser_CurrentPermissionLevel = m_pDataProvider->m_vectLoginUser[n].m_PermissionLevel;
			bIsAnyAutoLoginUser = true;
			break;
		}
	}
	if (!bIsAnyAutoLoginUser)          
		m_LoginDlg.DoModal();				//���û���Զ���¼�˻����򵯳���¼����//

	//���������ӽ��棬������//
	CRect CurWindowRect, ChiDlgRect;
	GetClientRect(&CurWindowRect);
	ChiDlgRect.left = CurWindowRect.right / 280;
	ChiDlgRect.top = CurWindowRect.bottom / 5.85 ;
	ChiDlgRect.bottom = CurWindowRect.bottom/40*39.95;
	ChiDlgRect.right = CurWindowRect.right / 5 * 3.7;
	
	m_DeviceChiDlg.Create(IDD_DEVICE_CHIDLG,this);	
	m_DeviceChiDlg.MoveWindow(ChiDlgRect);
	m_DeviceChiDlg.ShowWindow(SW_HIDE);


	CRect CurWindowRect1, ChiDlgRect1;
	GetClientRect(&CurWindowRect1);
	
	ChiDlgRect1.left = CurWindowRect1.right / 280;
	ChiDlgRect1.top = CurWindowRect1.bottom / 6.2;
	ChiDlgRect1.bottom = CurWindowRect1.bottom / 40 * 38.2;
	ChiDlgRect1.right = CurWindowRect1.right / 5 * 3.84;
	m_VedioChiDlg.Create(IDD_VEDIO_CHIDLG,this);
	m_VedioChiDlg.MoveWindow(ChiDlgRect1);
	m_VedioChiDlg.ShowWindow(SW_SHOW);


	m_ConfigChiDlg.Create(IDD_CONFIG_CHIDLG, this);
	m_ConfigChiDlg.MoveWindow(ChiDlgRect1);
	m_ConfigChiDlg.ShowWindow(SW_HIDE);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	SetTimer(1, 1000, NULL);			//����ʱ�Ӻ���///
	//���������///
	FontDate.CreatePointFont(130, _T("����"), NULL);		//������������///
	FontTime.CreatePointFont(200, _T("����"), NULL);		//����ʱ������///
	GetDlgItem(IDC_STATIC_DATE)->SetFont(&FontDate);	//�����úõ�����Ӧ�õ���̬����///
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&FontTime);

	//�����ؼ���С//
	CRect TempRect;
	GetClientRect(&TempRect);                                                    //ȡ�ͻ�����С//    
	m_OldSize.x = TempRect.right - TempRect.left;
	m_OldSize.y = TempRect.bottom - TempRect.top;

	//���״̬��//
	m_StatBar = new CStatusBarCtrl;
	TempRect.top = TempRect.bottom /75;                                         //����״̬���ľ�������//
	m_StatBar->Create(WS_BORDER | WS_VISIBLE | CBRS_BOTTOM, TempRect, this, 3);
	int nParts[4] = { TempRect.right / 6, TempRect.right / 3, TempRect.right / 2, -1 };                                       //�ָ�ߴ�//
	m_StatBar->SetParts(4, nParts);                                              //�ָ�״̬��//
	m_StatBar->SetText(_T("״̬����"), 0, 0);                                    //��һ����������"״̬����"//
	m_StatBar->SetText(_T("��һ��������"), 1, 0); 
	m_StatBar->SetText(_T("��������"), 2, 0);
	m_StatBar->SetText(_T("��ע"), 3, 0);
	m_StatBar->ShowWindow(SW_SHOW);

	
	//����Ԥ��
	m_CityComboBox.AddString(_T("��ɳ"));
	m_CityComboBox.AddString(_T("����"));
	m_CityComboBox.AddString(_T("����"));
	m_CityComboBox.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CMainDlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void CMainDlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CMainDlg::OnCancel()
{
	OnBnClickedStopPollModbus();// �����ã��˳��ص���ѯ�߳�
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMainDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


//���û�������ť��Ӧ����//
void CMainDlg::OnBnClickedBtUser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_UserManageDlg.DoModal() == IDOK)           //�����û��������//
	{
		ShowWindow(SW_HIDE);
		CLoginDlg::LoginUser_CurrentPermissionLevel = 0;
		CLoginDlg::LoginUser_CurrentId = 0;
		if(m_LoginDlg.DoModal()==IDOK)
		    ShowWindow(SW_SHOW);
	}
}


//�˵�����ϵͳ���á���ť��Ӧ����//
void CMainDlg::OnSysteminit()
{
	// TODO:  �ڴ���������������
	if (CLoginDlg::LoginUser_CurrentPermissionLevel == 1)
		m_InitDlg.DoModal();
	else
		AfxMessageBox(_T("��û��Ȩ�޽��иò�����"));
}


//PLC�������ð�ť��Ӧ����//
void CMainDlg::OnPlcpara()
{
	// TODO:  �ڴ���������������
	if (CLoginDlg::LoginUser_CurrentPermissionLevel == 1)
		m_EditPlcParaDlg.DoModal();
	else
		AfxMessageBox(_T("��û��Ȩ�޽��иò�����"));
}

//���巢����С�仯ʱ����Ӧ����//
void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

//���²��ִ����ڵĿؼ�//
void CMainDlg::ReSize()
{
	double fsp[2];
	POINT recNewSize;                                 //��ȡ���ڶԻ���Ĵ�С//  
	CRect TempRect;
	GetClientRect(&TempRect);                         //ȡ�ͻ�����С//    
	recNewSize.x = TempRect.right - TempRect.left;
	recNewSize.y = TempRect.bottom - TempRect.top;
	fsp[0] = (double)recNewSize.x / m_OldSize.x;
	fsp[1] = (double)recNewSize.y / m_OldSize.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint;                       //���Ͻ�//  
	CPoint OldBRPoint, BRPoint;                       //���½�//  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�//    
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);              //ȡ��ID//  
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = double(OldTLPoint.x*fsp[0]);
		TLPoint.y = double(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = double(OldBRPoint.x *fsp[0]);
		BRPoint.y = double(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
	/*	if (woc == IDC_ST_PIC)
		{
			GetDlgItem(IDD_DEVICE_CHIDLG)->MoveWindow(Rect, TRUE);
			GetDlgItem(IDD_VEDIO_CHIDLG)->MoveWindow(Rect, TRUE);
		}*/
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	m_OldSize = recNewSize;
}

//��������Ƶ��ء���ť����Ӧ����//
void CMainDlg::OnBnClickedBtVedio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nCurChiDlg == ID_VEDIODLG)
		return;
	m_DeviceChiDlg.ShowWindow(SW_HIDE);
	m_VedioChiDlg.ShowWindow(SW_SHOW);
	m_ConfigChiDlg.ShowWindow(SW_HIDE);
	m_nCurChiDlg = ID_VEDIODLG;               //��ӦΪ��ǰ��ʾ�ӽ���ı�ʶ����ֵ//
}

//������豸��ء���ť����Ӧ����//
void CMainDlg::OnBnClickedBtDevice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nCurChiDlg == ID_DEVICEDLG)  //�����ǰ��ʾ���ӽ����Ѿ����豸��ؽ��棬�����κ���Ӧ//
		return;	
	if (m_ConfigChiDlg.m_OldConfigGraChiDlg.m_bIsCurConfigChange)
	{
		m_DeviceChiDlg.RePaintModuleList();
		m_ConfigChiDlg.m_OldConfigGraChiDlg.m_bIsCurConfigChange = false;
	}
	m_VedioChiDlg.ShowWindow(SW_HIDE);
	m_DeviceChiDlg.ShowWindow(SW_SHOW);
	m_ConfigChiDlg.ShowWindow(SW_HIDE);
	m_nCurChiDlg = ID_DEVICEDLG;         //��ӦΪ��ǰ��ʾ�ӽ���ı�ʶ����ֵ//
}

//�䷽��ť����Ӧ����//
void CMainDlg::OnBnClickedBtConfig()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nCurChiDlg == ID_CONFIGDLG)
		return;
	m_ConfigChiDlg.ShowWindow(SW_SHOW);
	m_DeviceChiDlg.ShowWindow(SW_HIDE);
	m_VedioChiDlg.ShowWindow(SW_HIDE);
	m_nCurChiDlg = ID_CONFIGDLG;
}

//����������//
void CMainDlg::OnDestroy()
{

	CDialog::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CMainDlg::OnBnClickedUpdateWeather()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strCity;
	m_CityComboBox.GetWindowText(strCity);
	m_weather.UpdateWeather(strCity);

	m_edWeatherInfo.SetWindowText(m_weather.m_strWeatherInfo);

}

//��ʾʱ�����Ϣ����///
void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString StrDate = CTime::GetCurrentTime().Format("%Y��%m��%d��");	//StrDateΪ��ǰ����///
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(StrDate);
	CString StrTime = CTime::GetCurrentTime().Format("%H:%M:%S");		//StrTimeΪ��ǰʱ��///
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(StrTime);
	CDialog::OnTimer(nIDEvent);
}

//ʱ����ʾ�����ɫ����///
HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
		
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_DATE)
	{
		pDC->SetTextColor(RGB(72, 61, 139));				//�������ھ�̬���е���ɫ///
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
	{
		pDC->SetTextColor(RGB(72, 61, 139));				//����ʱ�侲̬���е���ɫ///
	}
	return hbr;
}

//�˵���ע����ť//
void CMainDlg::OnLogout()
{
	// TODO:  �ڴ���������������
	ShowWindow(SW_HIDE);
	CLoginDlg::LoginUser_CurrentPermissionLevel = 0;
	CLoginDlg::LoginUser_CurrentId = 0;
	if (m_LoginDlg.DoModal() == IDCANCEL)
		PostQuitMessage(0);
	else
		ShowWindow(SW_SHOW);
}

//�˵�������PLC״̬����//
void CMainDlg::OnPlcstatus()
{
	// TODO:  �ڴ���������������
	m_PLCStatusDlg.Create(IDD_PLCSTATUS,this);
	m_PLCStatusDlg.ShowWindow(SW_SHOW);
}


void CMainDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����modbus.CycleStart()����PLC��ѯ����
	if (m_Modbus.m_bIsCycling == TRUE)
	{
		return;
	}
	m_Modbus.CycleStart();
}


void CMainDlg::OnBnClickedStopPollModbus()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Modbus.m_bIsCycling == TRUE)
	{
		m_Modbus.CycleDisconnect();
	}
}



