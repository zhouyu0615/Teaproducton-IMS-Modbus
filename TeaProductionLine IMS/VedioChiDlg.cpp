// VedioChiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "VedioChiDlg.h"
#include "afxdialogex.h"


// CVedioChiDlg 对话框

IMPLEMENT_DYNAMIC(CVedioChiDlg, CDialog)

CVedioChiDlg::CVedioChiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVedioChiDlg::IDD, pParent)
{
	m_nPicStyle = 4;  //初始化，4画面风格//
	m_nNumOfPage = 1; //当前显示的页码//
	m_bIsVedioPlay = false;  //初始化摄像头是否已经在播放标识符//
}

CVedioChiDlg::~CVedioChiDlg()
{
}

void CVedioChiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REALPLAYXCTRL1, m_vedio1);
	DDX_Control(pDX, IDC_REALPLAYXCTRL2, m_vedio2);
	DDX_Control(pDX, IDC_REALPLAYXCTRL3, m_vedio3);
	DDX_Control(pDX, IDC_REALPLAYXCTRL4, m_vedio4);
	DDX_Control(pDX, IDC_REALPLAYXCTRL5, m_vedio5);
	DDX_Control(pDX, IDC_REALPLAYXCTRL6, m_vedio6);
	DDX_Control(pDX, IDC_REALPLAYXCTRL7, m_vedio7);
	DDX_Control(pDX, IDC_REALPLAYXCTRL8, m_vedio8);
	DDX_Control(pDX, IDC_REALPLAYXCTRL9, m_vedio9);
	DDX_Control(pDX, IDC_REALPLAYXCTRL10, m_vedio10);
	DDX_Control(pDX, IDC_REALPLAYXCTRL11, m_vedio11);
	DDX_Control(pDX, IDC_REALPLAYXCTRL12, m_vedio12);
	DDX_Control(pDX, IDC_REALPLAYXCTRL13, m_vedio13);
	DDX_Control(pDX, IDC_REALPLAYXCTRL14, m_vedio14);
	DDX_Control(pDX, IDC_REALPLAYXCTRL15, m_vedio15);
	DDX_Control(pDX, IDC_REALPLAYXCTRL16, m_vedio16);
	DDX_Control(pDX, IDC_REALPLAYXCTRL17, m_vedio17);
	DDX_Control(pDX, IDC_REALPLAYXCTRL18, m_vedio18);
}


BEGIN_MESSAGE_MAP(CVedioChiDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_PLAY, &CVedioChiDlg::OnBnClickedBtPlay)
	ON_BN_CLICKED(IDC_BT_STOP, &CVedioChiDlg::OnBnClickedBtStop)
	ON_BN_CLICKED(IDC_BUTTON3, &CVedioChiDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BT_SINGLEPIC, &CVedioChiDlg::OnBnClickedBtSinglepic)
	ON_BN_CLICKED(IDC_BT_FOURPIC, &CVedioChiDlg::OnBnClickedBtFourpic)
	ON_BN_CLICKED(IDC_BT_NINEPIC, &CVedioChiDlg::OnBnClickedBtNinepic)
	ON_BN_CLICKED(IDC_BT_16PIC, &CVedioChiDlg::OnBnClickedBt16pic)
	ON_BN_CLICKED(IDC_BT_NEXT, &CVedioChiDlg::OnBnClickedBtNext)
	ON_BN_CLICKED(IDC_BT_LAST, &CVedioChiDlg::OnBnClickedBtLast)
END_MESSAGE_MAP()


// CVedioChiDlg 消息处理程序

//窗体大小变化时，使控件自适应//
void CVedioChiDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
		ReSize();
}


BOOL CVedioChiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//将18个摄像头显示控件放入容器//
	m_vectVedio.push_back(&m_vedio1);
	m_vectVedio.push_back(&m_vedio2);
	m_vectVedio.push_back(&m_vedio3);
	m_vectVedio.push_back(&m_vedio4);
	m_vectVedio.push_back(&m_vedio5);
	m_vectVedio.push_back(&m_vedio6);
	m_vectVedio.push_back(&m_vedio7);
	m_vectVedio.push_back(&m_vedio8);
	m_vectVedio.push_back(&m_vedio9);
	m_vectVedio.push_back(&m_vedio10);
	m_vectVedio.push_back(&m_vedio11);
	m_vectVedio.push_back(&m_vedio12);
	m_vectVedio.push_back(&m_vedio13);
	m_vectVedio.push_back(&m_vedio14);
	m_vectVedio.push_back(&m_vedio15);
	m_vectVedio.push_back(&m_vedio16);
	m_vectVedio.push_back(&m_vedio17);
	m_vectVedio.push_back(&m_vedio18);

	//调整控件大小//
	CRect TempRect;
	GetClientRect(&TempRect);                                                    //取客户区大小//    
	m_OldSize.x = TempRect.right - TempRect.left;
	m_OldSize.y = TempRect.bottom - TempRect.top;

	ShowFourVedio(m_vedio1, m_vedio2, m_vedio3, m_vedio4);    //默认显示四窗格//
	GetDlgItem(IDC_ST_PAGE)->SetWindowText(_T("1"));

	//读取数据库，注册相机//
	m_nNumOfVedio = m_pDataProvider->m_vectVideo.size();      //数据库中相机的个数//
	if (m_nNumOfVedio > 4)                                    //如果摄像头个数大于4，则使能下一页按钮//
		GetDlgItem(IDC_BT_NEXT)->EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//窗体大小发生变化时，控件自适应函数//
void CVedioChiDlg::ReSize()
{
	float fsp[2];
	POINT recNewSize; //获取现在对话框的大小//  
	CRect TempRect;
	GetClientRect(&TempRect);     //取客户区大小//    
	recNewSize.x = TempRect.right - TempRect.left;
	recNewSize.y = TempRect.bottom - TempRect.top;
	fsp[0] = (float)recNewSize.x / m_OldSize.x;
	fsp[1] = (float)recNewSize.y / m_OldSize.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角//  
	CPoint OldBRPoint, BRPoint; //右下角//  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件//    
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID//  
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	m_OldSize = recNewSize;
}

//开始所有按钮响应函数//
void CVedioChiDlg::OnBnClickedBtPlay()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int n = 0; n < m_nNumOfVedio; n++)
	{
		m_vectVedio[n]->SetDeviceInfo(m_pDataProvider->m_vectVideo[n].m_strIPAddr, m_pDataProvider->m_vectVideo[n].m_port, 0, _T("admin"), _T("admin"));
		m_vectVedio[n]->StartPlay();
	}
}

//停止所有响应函数//
void CVedioChiDlg::OnBnClickedBtStop()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int n = 0; n < m_nNumOfVedio; n++)
		m_vectVedio[n]->StopPlay();
}

//刷新按钮的响应函数//
void CVedioChiDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	connectVedio();
}

//连接摄像头，并播放//
void CVedioChiDlg::connectVedio()
{
	m_nNumOfVedio = m_pDataProvider->m_vectVideo.size();
	for (int n = 0; n < m_nNumOfVedio;n++)
	{
		m_vectVedio[n]->SetDeviceInfo(m_pDataProvider->m_vectVideo[n].m_strIPAddr, m_pDataProvider->m_vectVideo[n].m_port, 0, _T("admin"), _T("admin"));
		m_vectVedio[n]->StartPlay();
	}
}

//单画面按钮响应函数//
void CVedioChiDlg::OnBnClickedBtSinglepic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nPicStyle != 1)
	{
		ShowOneVedio(m_vedio1);
		m_nNumOfPage = 1;
		GetDlgItem(IDC_ST_PAGE)->SetWindowText(_T("1"));
		GetDlgItem(IDC_BT_LAST)->EnableWindow(FALSE);
		if (m_nNumOfVedio > 1)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
	}

}

//四画面按钮响应函数//
void CVedioChiDlg::OnBnClickedBtFourpic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nPicStyle != 4)
	{
		ShowFourVedio(m_vedio1, m_vedio2, m_vedio3, m_vedio4);
		m_nNumOfPage = 1;
		GetDlgItem(IDC_ST_PAGE)->SetWindowText(_T("1"));
		GetDlgItem(IDC_BT_LAST)->EnableWindow(FALSE);
		if (m_nNumOfVedio > 4)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
	}
}

//九画面按钮响应函数//
void CVedioChiDlg::OnBnClickedBtNinepic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nPicStyle != 9)
	{
		ShowNineVedio(1);
		GetDlgItem(IDC_ST_PAGE)->SetWindowText(_T("1"));
		GetDlgItem(IDC_BT_LAST)->EnableWindow(FALSE);
		if (m_nNumOfVedio > 9)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
	}
}

//16画面按钮的响应函数//
void CVedioChiDlg::OnBnClickedBt16pic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nPicStyle != 16)
	{
		CRect RectOfChiDlg, rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, rect9,rect10,rect11,rect12,rect13,rect14,rect15,rect16;
		GetWindowRect(RectOfChiDlg);
		ScreenToClient(RectOfChiDlg);

		rect1.left = RectOfChiDlg.left;
		rect1.top = RectOfChiDlg.top;
		rect1.bottom = RectOfChiDlg.bottom / 16 * 3.6;
		rect1.right = RectOfChiDlg.right / 240 * 59;

		rect2.left = RectOfChiDlg.right / 4;
		rect2.bottom = RectOfChiDlg.bottom / 16 * 3.6;
		rect2.top = RectOfChiDlg.top;
		rect2.right = RectOfChiDlg.right / 240 * 119;

		rect3.left = RectOfChiDlg.right / 2;
		rect3.top = RectOfChiDlg.top;
		rect3.right = RectOfChiDlg.right/240*179;
		rect3.bottom = RectOfChiDlg.bottom / 16 * 3.6;

		rect4.left = RectOfChiDlg.right/4*3;
		rect4.top = RectOfChiDlg.top;
		rect4.right = RectOfChiDlg.right;
		rect4.bottom = RectOfChiDlg.bottom / 16 * 3.6;

		rect5.left = RectOfChiDlg.left;
		rect5.top = RectOfChiDlg.bottom / 16 * 3.7;
		rect5.right = RectOfChiDlg.right / 240 * 59;
		rect5.bottom = RectOfChiDlg.bottom / 16 * 7.3;

		rect6.left = RectOfChiDlg.right / 4;
		rect6.top = RectOfChiDlg.bottom / 16 * 3.7;
		rect6.right = RectOfChiDlg.right/240*119;
		rect6.bottom = RectOfChiDlg.bottom / 16 * 7.3;

		rect7.left = RectOfChiDlg.right / 2;
		rect7.top = RectOfChiDlg.bottom / 16 * 3.7;
		rect7.right = RectOfChiDlg.right / 240 * 179;
		rect7.bottom = RectOfChiDlg.bottom / 16 * 7.3;

		rect8.left = RectOfChiDlg.right / 4 * 3;
		rect8.top = RectOfChiDlg.bottom / 16 * 3.7;
		rect8.right = RectOfChiDlg.right;
		rect8.bottom = RectOfChiDlg.bottom / 16 * 7.3;

		rect9.left = RectOfChiDlg.left;
		rect9.top = RectOfChiDlg.bottom / 16 * 7.4;
		rect9.right = RectOfChiDlg.right / 240 * 59;
		rect9.bottom = RectOfChiDlg.bottom / 16 * 11;

		rect10.left = RectOfChiDlg.right / 4;
		rect10.top = RectOfChiDlg.bottom / 16 * 7.4;
		rect10.right = RectOfChiDlg.right / 240 * 119;
		rect10.bottom = RectOfChiDlg.bottom / 16 * 11;

		rect11.left = RectOfChiDlg.right / 2;
		rect11.top = RectOfChiDlg.bottom / 16 * 7.4;
		rect11.right = RectOfChiDlg.right / 240 * 179;
		rect11.bottom = RectOfChiDlg.bottom / 16 * 11;

		rect12.left = RectOfChiDlg.right / 4 * 3;
		rect12.top = RectOfChiDlg.bottom / 16 * 7.4;
		rect12.right = RectOfChiDlg.right;
		rect12.bottom = RectOfChiDlg.bottom / 16 * 11;

		rect13.left = RectOfChiDlg.left;
		rect13.top = RectOfChiDlg.bottom / 16 * 11.1;
		rect13.right = RectOfChiDlg.right / 240 * 59;
		rect13.bottom = RectOfChiDlg.bottom / 16 * 14.7;

		rect14.left = RectOfChiDlg.right / 4;
		rect14.top = RectOfChiDlg.bottom / 16 * 11.1;
		rect14.right = RectOfChiDlg.right / 240 * 119;
		rect14.bottom = RectOfChiDlg.bottom / 16 * 14.7;

		rect15.left = RectOfChiDlg.right / 2;
		rect15.top = RectOfChiDlg.bottom / 16 * 11.1;
		rect15.right = RectOfChiDlg.right / 240 * 179;
		rect15.bottom = RectOfChiDlg.bottom / 16 * 14.7;

		rect16.left = RectOfChiDlg.right / 4 * 3;
		rect16.top = RectOfChiDlg.bottom / 16 * 11.1;
		rect16.right = RectOfChiDlg.right;
		rect16.bottom = RectOfChiDlg.bottom / 16 * 14.7;

		m_vedio1.MoveWindow(rect1);
		m_vedio2.MoveWindow(rect2);
		m_vedio3.MoveWindow(rect3);
		m_vedio4.MoveWindow(rect4);
		m_vedio5.MoveWindow(rect5);
		m_vedio6.MoveWindow(rect6);
		m_vedio7.MoveWindow(rect7);
		m_vedio8.MoveWindow(rect8);
		m_vedio9.MoveWindow(rect9);
		m_vedio10.MoveWindow(rect10);
		m_vedio11.MoveWindow(rect11);
		m_vedio12.MoveWindow(rect12);
		m_vedio13.MoveWindow(rect13);
		m_vedio14.MoveWindow(rect14);
		m_vedio15.MoveWindow(rect15);
		m_vedio16.MoveWindow(rect16);

		for (int n = 0; n < 16; n++)
			m_vectVedio[n]->ShowWindow(SW_SHOW);
		m_vedio17.ShowWindow(SW_HIDE);
		m_vedio18.ShowWindow(SW_HIDE);
		
		m_nPicStyle = 16;
		m_nNumOfPage = 1;
		GetDlgItem(IDC_ST_PAGE)->SetWindowText(_T("1"));
		GetDlgItem(IDC_BT_LAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
	}

}

//显示指定单个摄像头，并修改画面风格标志//
void CVedioChiDlg::ShowOneVedio(CRealplayxctrl1 &vedio)
{
	CRect RectOfChiDlg, rect1;
	GetWindowRect(RectOfChiDlg);
	ScreenToClient(RectOfChiDlg);
	rect1.left = RectOfChiDlg.left;
	rect1.top = RectOfChiDlg.top;
	rect1.bottom = RectOfChiDlg.bottom / 16 * 14.7;
	rect1.right = RectOfChiDlg.right;
	vedio.MoveWindow(rect1);

	for (int n = 0; n < 18; n++)
		m_vectVedio[n]->ShowWindow(SW_HIDE);
	
	vedio.ShowWindow(SW_SHOW);
	m_nPicStyle = 1;
}

//显示指定的四个摄像头，并修改画面风格标志//
void CVedioChiDlg::ShowFourVedio(CRealplayxctrl1 &vedio1, CRealplayxctrl1 &vedio2, CRealplayxctrl1 &vedio3, CRealplayxctrl1 &vedio4)
{
	CRect RectOfChiDlg, rect1, rect2, rect3, rect4;
	GetWindowRect(RectOfChiDlg);
	ScreenToClient(RectOfChiDlg);

	rect1.left = RectOfChiDlg.left;
	rect1.top = RectOfChiDlg.top;
	rect1.bottom = RectOfChiDlg.bottom / 16 * 7.3;
	rect1.right = RectOfChiDlg.right / 2.01;

	rect2.left = RectOfChiDlg.right / 1.99;
	rect2.bottom = RectOfChiDlg.bottom / 16 * 7.3;
	rect2.top = RectOfChiDlg.top;
	rect2.right = RectOfChiDlg.right;

	rect3.left = RectOfChiDlg.left;
	rect3.top = RectOfChiDlg.bottom / 16 * 7.4;
	rect3.right = RectOfChiDlg.right / 2.01;
	rect3.bottom = RectOfChiDlg.bottom / 16 * 14.7;

	rect4.left = RectOfChiDlg.right / 1.99;
	rect4.top = RectOfChiDlg.bottom / 16 * 7.4;
	rect4.right = RectOfChiDlg.right;
	rect4.bottom = RectOfChiDlg.bottom / 16 * 14.7;

	vedio1.MoveWindow(rect1);
	vedio2.MoveWindow(rect2);
	vedio3.MoveWindow(rect3);
	vedio4.MoveWindow(rect4);
	for (int n = 0; n < 18; n++)
		m_vectVedio[n]->ShowWindow(SW_HIDE);

	vedio1.ShowWindow(SW_SHOW);
	vedio2.ShowWindow(SW_SHOW);
	vedio3.ShowWindow(SW_SHOW);
	vedio4.ShowWindow(SW_SHOW);

	m_nPicStyle = 4;
}

//显示九画面,并修改页码标志和画面风格标志//
void CVedioChiDlg::ShowNineVedio(int nPage)
{
	if (nPage != 1 && nPage != 2)
		return;

	CRect RectOfChiDlg, rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, rect9;
	GetWindowRect(RectOfChiDlg);
	ScreenToClient(RectOfChiDlg);

	rect1.left = RectOfChiDlg.left;
	rect1.top = RectOfChiDlg.top;
	rect1.bottom = RectOfChiDlg.bottom / 16 * 4.8;
	rect1.right = RectOfChiDlg.right / 240 * 79;

	rect2.left = RectOfChiDlg.right / 3;
	rect2.bottom = RectOfChiDlg.bottom / 16 * 4.8;
	rect2.top = RectOfChiDlg.top;
	rect2.right = RectOfChiDlg.right / 240 * 159;

	rect3.left = RectOfChiDlg.right / 3 * 2;
	rect3.top = RectOfChiDlg.top;
	rect3.right = RectOfChiDlg.right;
	rect3.bottom = RectOfChiDlg.bottom / 16 * 4.8;

	rect4.left = RectOfChiDlg.left;
	rect4.top = RectOfChiDlg.bottom / 16 * 4.9;
	rect4.right = RectOfChiDlg.right / 240 * 79;
	rect4.bottom = RectOfChiDlg.bottom / 16 * 9.7;

	rect5.left = RectOfChiDlg.right / 3;
	rect5.top = RectOfChiDlg.bottom / 16 * 4.9;
	rect5.right = RectOfChiDlg.right / 240 * 159;
	rect5.bottom = RectOfChiDlg.bottom / 16 * 9.7;

	rect6.left = RectOfChiDlg.right / 3 * 2;
	rect6.top = RectOfChiDlg.bottom / 16 * 4.9;
	rect6.right = RectOfChiDlg.right;
	rect6.bottom = RectOfChiDlg.bottom / 16 * 9.7;

	rect7.left = RectOfChiDlg.left;
	rect7.top = RectOfChiDlg.bottom / 16 * 9.8;
	rect7.right = RectOfChiDlg.right / 240 * 79;
	rect7.bottom = RectOfChiDlg.bottom / 16 * 14.7;

	rect8.left = RectOfChiDlg.right / 3;
	rect8.top = RectOfChiDlg.bottom / 16 * 9.8;
	rect8.right = RectOfChiDlg.right / 240 * 159;
	rect8.bottom = RectOfChiDlg.bottom / 16 * 14.7;

	rect9.left = RectOfChiDlg.right / 3 * 2;
	rect9.top = RectOfChiDlg.bottom / 16 * 9.8;
	rect9.right = RectOfChiDlg.right;
	rect9.bottom = RectOfChiDlg.bottom / 16 * 14.7;
	switch(nPage)
    {
	case 1:
		m_vedio1.MoveWindow(rect1);
		m_vedio2.MoveWindow(rect2);
		m_vedio3.MoveWindow(rect3);
		m_vedio4.MoveWindow(rect4);
		m_vedio5.MoveWindow(rect5);
		m_vedio6.MoveWindow(rect6);
		m_vedio7.MoveWindow(rect7);
		m_vedio8.MoveWindow(rect8);
		m_vedio9.MoveWindow(rect9);
		m_vedio10.ShowWindow(SW_HIDE);
		m_vedio11.ShowWindow(SW_HIDE);
		m_vedio12.ShowWindow(SW_HIDE);
		m_vedio13.ShowWindow(SW_HIDE);
		m_vedio14.ShowWindow(SW_HIDE);
		m_vedio15.ShowWindow(SW_HIDE);
		m_vedio16.ShowWindow(SW_HIDE);
		m_vedio17.ShowWindow(SW_HIDE);
		m_vedio18.ShowWindow(SW_HIDE);
		m_vedio1.ShowWindow(SW_SHOW);
		m_vedio2.ShowWindow(SW_SHOW);
		m_vedio3.ShowWindow(SW_SHOW);
		m_vedio4.ShowWindow(SW_SHOW);
		m_vedio5.ShowWindow(SW_SHOW);
		m_vedio6.ShowWindow(SW_SHOW);
		m_vedio7.ShowWindow(SW_SHOW);
		m_vedio8.ShowWindow(SW_SHOW);
		m_vedio9.ShowWindow(SW_SHOW);
		m_nPicStyle = 9;
		m_nNumOfPage = 1;
		break;
	case 2:
		m_vedio10.MoveWindow(rect1);
		m_vedio11.MoveWindow(rect2);
		m_vedio12.MoveWindow(rect3);
		m_vedio13.MoveWindow(rect4);
		m_vedio14.MoveWindow(rect5);
		m_vedio15.MoveWindow(rect6);
		m_vedio16.MoveWindow(rect7);
		m_vedio17.MoveWindow(rect8);
		m_vedio18.MoveWindow(rect9);
		m_vedio1.ShowWindow(SW_HIDE);
		m_vedio2.ShowWindow(SW_HIDE);
		m_vedio3.ShowWindow(SW_HIDE);
		m_vedio4.ShowWindow(SW_HIDE);
		m_vedio5.ShowWindow(SW_HIDE);
		m_vedio6.ShowWindow(SW_HIDE);
		m_vedio7.ShowWindow(SW_HIDE);
		m_vedio8.ShowWindow(SW_HIDE);
		m_vedio9.ShowWindow(SW_HIDE);
		m_vedio10.ShowWindow(SW_SHOW);
		m_vedio11.ShowWindow(SW_SHOW);
		m_vedio12.ShowWindow(SW_SHOW);
		m_vedio13.ShowWindow(SW_SHOW);
		m_vedio14.ShowWindow(SW_SHOW);
		m_vedio15.ShowWindow(SW_SHOW);
		m_vedio16.ShowWindow(SW_SHOW);
		m_vedio17.ShowWindow(SW_SHOW);
		m_vedio18.ShowWindow(SW_SHOW);
		m_nNumOfPage = 2;
		m_nPicStyle = 9;
		break;
	default:
		break;
    } 
	
}

//下一页按钮响应函数//
void CVedioChiDlg::OnBnClickedBtNext()
{
	// TODO:  在此添加控件通知处理程序代码

	switch (m_nPicStyle)
	{
	case 1:
		ShowOneVedio(*(m_vectVedio[m_nNumOfPage]));
		if (m_nNumOfPage >= m_pDataProvider->m_vectVideo.size() - 1)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
		m_nNumOfPage++;
		break;
	case 4:
		ShowFourVedio(*(m_vectVedio[m_nNumOfPage * 4]), *(m_vectVedio[m_nNumOfPage * 4 + 1]), *(m_vectVedio[m_nNumOfPage * 4 + 2]), *(m_vectVedio[m_nNumOfPage * 4 + 3]));
		if (m_nNumOfPage >= (m_pDataProvider->m_vectVideo.size()-1)/4)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
		m_nNumOfPage++;
		break;
	case 9:
		ShowNineVedio(2);
		GetDlgItem(IDC_BT_NEXT)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
	if (m_nNumOfPage > 1)
		GetDlgItem(IDC_BT_LAST)->EnableWindow(TRUE);
	CString strPage;
	strPage.Format(_T("%d"), m_nNumOfPage);
	GetDlgItem(IDC_ST_PAGE)->SetWindowText(strPage);
}

//上一页按钮响应函数//
void CVedioChiDlg::OnBnClickedBtLast()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nNumOfPage > 1)
		m_nNumOfPage--;
	else
		return;
	switch (m_nPicStyle)
	{
	case 1:
		ShowOneVedio(*(m_vectVedio[m_nNumOfPage-1]));
		if (GetDlgItem(IDC_BT_NEXT)->IsWindowEnabled() == false)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(true);
		break;
	case 4:
		ShowFourVedio(*(m_vectVedio[m_nNumOfPage * 4-4]), *(m_vectVedio[m_nNumOfPage * 4 -3]), *(m_vectVedio[m_nNumOfPage * 4 - 2]), *(m_vectVedio[m_nNumOfPage * 4 -1]));
		if (GetDlgItem(IDC_BT_NEXT)->IsWindowEnabled() == false)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(true);
		break;
	case 9:
		ShowNineVedio(1);
		if (GetDlgItem(IDC_BT_NEXT)->IsWindowEnabled() == false)
			GetDlgItem(IDC_BT_NEXT)->EnableWindow(true);
		break;
	default:
		break;
	}
	if (m_nNumOfPage <= 1)
		GetDlgItem(IDC_BT_LAST)->EnableWindow(false);
	CString strPage;
	strPage.Format(_T("%d"), m_nNumOfPage);
	GetDlgItem(IDC_ST_PAGE)->SetWindowText(strPage);
}

//重载虚函数//
void CVedioChiDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

}
