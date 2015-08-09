// DeviceChiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "DeviceChiDlg.h"
#include "afxdialogex.h"


// CDeviceChiDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceChiDlg, CDialog)

CDeviceChiDlg::CDeviceChiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceChiDlg::IDD, pParent)
{
	m_nCurSelModuleId = 0;//初始化变量，导航栏当前选中模块ID//
	m_brush.CreateSolidBrush(RGB(198, 198, 198));
}

CDeviceChiDlg::~CDeviceChiDlg()
{
}

void CDeviceChiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEVICE_CHIDLG, m_treeDevice);
	DDX_Control(pDX, IDC_LI1_MODULEPARA, m_listModulePara);
	DDX_Control(pDX, IDC_LI2_DEVICEPARA, m_listDevicePara);
	DDX_Control(pDX, IDC_ST_CURPOSITION, m_textCurPosition);
	DDX_Control(pDX, IDC_REALPLAYXCTRL1, m_video);
}


BEGIN_MESSAGE_MAP(CDeviceChiDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEVICE_CHIDLG, &CDeviceChiDlg::OnTvnSelchangedTreeDeviceChidlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LI2_DEVICEPARA, &CDeviceChiDlg::OnNMDblclkLi2Devicepara)
	ON_NOTIFY(NM_DBLCLK, IDC_LI1_MODULEPARA, &CDeviceChiDlg::OnNMDblclkLi1Modulepara)
	ON_EN_KILLFOCUS(IDC_EDIT_CREATEID, &CDeviceChiDlg::OnEnKillfocusEditCreateid)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDeviceChiDlg 消息处理程序

//窗体大小发生变化的响应函数//
void CDeviceChiDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
		ReSize();

}


BOOL CDeviceChiDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitTreeContrl();   //初始化导航栏//

	SetTimer(1, 1000, NULL);
	
	//初始化2个列表框//
	m_bHaveEditCreate = false;            //初始化标志位，表示还没有创建编辑框//
	CRect rectList1;
	m_listModulePara.GetWindowRect(&rectList1);
	m_listModulePara.SetExtendedStyle(m_listModulePara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE );
	m_listModulePara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listModulePara.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rectList1.Width() / 27*2, -1);
	m_listModulePara.InsertColumn(2, _T("工艺参数"), LVCFMT_CENTER, rectList1.Width() / 9 * 3.6, -1);
	m_listModulePara.InsertColumn(3, _T("当前值"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.6, -1);
	m_listModulePara.InsertColumn(4, _T("设定值"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.6, -1);
	m_listModulePara.InsertColumn(5, _T("单位"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.5, -1);

	CRect rectList2;
	m_listDevicePara.GetWindowRect(&rectList2);
	m_listDevicePara.SetExtendedStyle(m_listDevicePara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE);
	m_listDevicePara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listDevicePara.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rectList2.Width() / 7*1.2, -1);
	m_listDevicePara.InsertColumn(2, _T("设备"), LVCFMT_CENTER, rectList2.Width() / 7 * 3.92, -1);
	m_listDevicePara.InsertColumn(3, _T("当前状态"), LVCFMT_CENTER, rectList2.Width() / 7 * 1.8, -1);

	//调整控件大小//
	CRect TempRect;
	GetClientRect(&TempRect);                                                    //取客户区大小//    
	m_OldSize.x = TempRect.right - TempRect.left;
	m_OldSize.y = TempRect.bottom - TempRect.top;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//重新布局窗体内的控件//
void CDeviceChiDlg::ReSize()
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

//重新初始化树形控件//
void CDeviceChiDlg::InitTreeContrl()
{
	m_treeDevice.DeleteAllItems();
	HTREEITEM hRoot;     // 树的根节点的句柄//   
	HTREEITEM hFirItem;  // 可表示任一一级节点的句柄//
	HICON hIcon[1];      // 图标句柄数组//
	hIcon[0] = theApp.LoadIcon(IDI_ICONPLUSGREEN);
	// 创建图像序列CImageList对象   
	m_imageList.Create(32, 32, ILC_COLOR32, 1, 1);
	m_imageList.Add(hIcon[0]);
	// 为树形控件设置图像序列//  
	m_treeDevice.SetImageList(&m_imageList, TVSIL_NORMAL);
	for (int nLine = 0; nLine < m_pDataProvider->m_vectProductionLine.size();nLine++)
	{
		hRoot = m_treeDevice.InsertItem(m_pDataProvider->m_vectProductionLine[nLine].m_strLineName, 0, 0, NULL, TVI_LAST);
		m_treeDevice.SetItemData(hRoot, m_pDataProvider->m_vectProductionLine[nLine].m_Id);
		for (int nModule = 0; nModule < m_pDataProvider->m_vectProcessModule.size();nModule++)
		{
			if (m_pDataProvider->m_vectProcessModule[nModule].m_ProcessLineId == m_pDataProvider->m_vectProductionLine[nLine].m_Id)
			{
				hFirItem = m_treeDevice.InsertItem(m_pDataProvider->m_vectProcessModule[nModule].m_strProcessModuleName, 0, 0, hRoot, TVI_LAST);
				m_treeDevice.SetItemData(hFirItem, m_pDataProvider->m_vectProcessModule[nModule].m_Id);
			}
		}
	}
}

//当树形控件选中条目发生变化时的响应函数//
void CDeviceChiDlg::OnTvnSelchangedTreeDeviceChidlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	//删除两个列表框控件的内容//
	m_listDevicePara.DeleteAllItems();
	m_listModulePara.DeleteAllItems();

	m_video.StopPlay();   //视频播放停止//

	HTREEITEM hCurSelItem = m_treeDevice.GetSelectedItem();
	UINT TempID = m_treeDevice.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeDevice.GetParentItem(hCurSelItem);
	CString strCurPosition;
	if (hParentItem!=NULL)                              //如果选中的是工艺模块节点//
	{
		m_nCurSelModuleId = TempID;                                                                 //当前选中模块的ID//
		CString strLineName = m_treeDevice.GetItemText(hParentItem);    //所属生产线名称//
		strCurPosition = _T("当前位置： ") + strLineName + _T(" >> ") + m_treeDevice.GetItemText(hCurSelItem)+_T(" >> ");  //位置栏更新//
		m_textCurPosition.SetWindowText(strCurPosition);  
		
		SearchFromDataProvider(m_nCurSelModuleId);    //将当前选中模块下的摄像头、工艺参数、设备参数存到临时容器//
		WriteToDeviceList();                          //填写两个列表框//
		WriteToModuleList();
		if (!m_vectTempVideo.empty())                 //如果该模块有视频监控，则显示//
		{
			m_video.SetDeviceInfo(m_vectTempVideo[0].m_strIPAddr, m_vectTempVideo[0].m_port, 0, _T("admin"), _T("admin"));
			m_video.StartPlay();
		}		
	}
	else                                             //如果选中的是生产线节点//
	{
		strCurPosition = _T("当前位置： ") + m_treeDevice.GetItemText(hCurSelItem) + _T(" >> ");
		m_textCurPosition.SetWindowText(strCurPosition);
		m_listModulePara.DeleteAllItems();
		m_listDevicePara.DeleteAllItems();
	}

}

//将当前选中模块下的摄像头、工艺参数、设备参数存到临时容器//
void CDeviceChiDlg::SearchFromDataProvider(UINT nCerSelModuleId)
{
	m_vectTempDevicePara.clear();
	m_vectTempModulePara.clear();
	m_vectTempVideo.clear();
	for (int n = 0; n < m_pDataProvider->m_vectDevicePara.size();n++)  //设备参数//
	{
		if (m_pDataProvider->m_vectDevicePara[n].m_ProcessModuleId==nCerSelModuleId)
		{
			m_vectTempDevicePara.push_back(m_pDataProvider->m_vectDevicePara[n]);
		}
	}
	for (int i = 0; i < m_pDataProvider->m_vectVideo.size();i++)      //摄像头//
    {
		if (m_pDataProvider->m_vectVideo[i].m_ModuleId==nCerSelModuleId)
		{
			m_vectTempVideo.push_back(m_pDataProvider->m_vectVideo[i]);
			break;
		}
    }
	for (int j = 0; j < m_pDataProvider->m_vectProModulePara.size();j++)    //工艺参数//
	{
		if (m_pDataProvider->m_vectProModulePara[j].m_ProcessModuleId==nCerSelModuleId && m_pDataProvider->m_vectProModulePara[j].m_IsVisible)
		{
			m_vectTempModulePara.push_back(m_pDataProvider->m_vectProModulePara[j]);
		}
	}
}

//填写工艺参数列表框//
void CDeviceChiDlg::WriteToModuleList()
{
	m_listModulePara.DeleteAllItems();
	CString strItem;                                               //模块下的工艺参数显示在list1//
	for (int n = 0; n < m_vectTempModulePara.size(); n++)
	{
		strItem.Format(_T("%d"), n + 1);
		m_listModulePara.InsertItem(n, _T(""));
		m_listModulePara.SetItemText(n, 1, strItem);
		m_listModulePara.SetItemText(n, 2, m_vectTempModulePara[n].m_strParaName);	
		if (m_vectTempModulePara[n].m_fSetValue==-3001)
		{
			m_listModulePara.SetItemText(n, 4, _T("无"));
		} 
		else
		{
			strItem.Format(_T("%.2f"), m_vectTempModulePara[n].m_fSetValue);
			m_listModulePara.SetItemText(n, 4, strItem);
		}
		m_listModulePara.SetItemText(n, 5, m_vectTempModulePara[n].m_strUnit);
	}  
}   

//填写设备参数列表框//
void CDeviceChiDlg::WriteToDeviceList()                          
{
	m_listDevicePara.DeleteAllItems();
	CString strItem;
	for (int n = 0; n < m_vectTempDevicePara.size(); n++)
	{
		m_listDevicePara.InsertItem(n, _T(""));
		strItem.Format(_T("%d"), n + 1);
		m_listDevicePara.SetItemText(n, 1, strItem);
		m_listDevicePara.SetItemText(n, 2, m_vectTempDevicePara[n].m_strDeviceName);
		if (m_vectTempDevicePara[n].m_StateValue == 1)
		{
			m_listDevicePara.SetItemText(n, 3, _T("运行"));
		}
		else
		{
			m_listDevicePara.SetItemText(n, 3, _T("停止"));
		}
	}
}

void CDeviceChiDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(0, 0, 250));   //设置为绿色背景
	// 不为绘图消息调用 CDialog::OnPaint()
}


HBRUSH CDeviceChiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor==CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(RGB(0, 0, 0));             //字体颜色//
		pDC->SetBkMode(TRANSPARENT);                 // 背景透明//
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	else
		hbr = m_brush;
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//双击设备参数列表的响应函数//
void CDeviceChiDlg::OnNMDblclkLi2Devicepara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	m_nDClkLineItem = pNMItemActivate->iItem;

	if (m_nDClkLineItem == -1)
		return;
	CDeviceContrlPopDlg DeviceContrlPopDlg;          //设备控制台弹出窗口//
	DeviceContrlPopDlg.m_vDevicePara.push_back(m_vectTempDevicePara[m_nDClkLineItem]);        //将选中设备参数传到弹出界面//
	DeviceContrlPopDlg.DoModal();

	*pResult = 0;
}

//双击工艺参数列表的响应函数//
void CDeviceChiDlg::OnNMDblclkLi1Modulepara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码//
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	if (pEditCtrl->iItem == -1)                                                //点击到非工作区//
	{
		if (m_bHaveEditCreate == true)                                            //如果之前创建了编辑框就销毁掉//
		{
			distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);        //销毁单元格编辑框对象//
			m_bHaveEditCreate = false;
		}
	}
	else
	{
		if (m_bHaveEditCreate == true)
		{
			if (!(m_OldItem == pEditCtrl->iItem && m_OldSubItem == pEditCtrl->iSubItem))    //如果点中的单元格不是之前创建好的//
			{
				distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);
				m_bHaveEditCreate = false;
				createEdit(pEditCtrl, &m_Edit, m_OldItem, m_OldSubItem, m_bHaveEditCreate);      //创建编辑框//
			}
			else                                                                       //点中的单元格是之前创建好的//
			{
				m_Edit.SetFocus();                                                     //设置为焦点//
			}
		}
		else
		{
			m_OldItem = pEditCtrl->iItem;                                                 //将点中的单元格的行赋值给“刚编辑过的行”以便后期处理//
			m_OldSubItem = pEditCtrl->iSubItem;                                           //将点中的单元格的行赋值给“刚编辑过的列”以便后期处理//
			createEdit(pEditCtrl, &m_Edit, m_OldItem, m_OldSubItem, m_bHaveEditCreate);         //创建编辑框//
		}
	}
	*pResult = 0;
}

//创建单元格编辑框函数//
void CDeviceChiDlg::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
//pEditCtrl为列表对象指针，createdit为编辑框指针对象//
//Item为创建单元格在列表中的行，SubItem则为列，havecreat为对象创建标准//
{
	Item = pEditCtrl->iItem;                     //将点中的单元格的行赋值给“刚编辑过的行”以便后期处理//
	SubItem = pEditCtrl->iSubItem;               //将点中的单元格的行赋值给“刚编辑过的列”以便后期处理//
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_CENTER | ES_WANTRETURN,CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);  //创建编辑框对象,IDC_EDIT_CREATEID为控件ID号//
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);                   //设置字体//
	createdit->SetParent(&m_listModulePara);                      //将listcontrol设置为父窗口//
	CRect  EditRect;
	m_listModulePara.GetSubItemRect(m_OldItem, 4, LVIR_LABEL, EditRect);      //获取单元格的空间位置信息//
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listModulePara.GetColumnWidth(4) - 1, EditRect.bottom - 1);//+1和-1让编辑框不至于挡住列表框中的网格线
	CString strItem = m_listModulePara.GetItemText(m_OldItem, 4);             //获得当前设定值//
	createdit->SetWindowText(strItem);                                     //将单元格字符显示在编辑框上//
	createdit->MoveWindow(&EditRect);                                      //将编辑框位置放在相应单元格上//
	createdit->ShowWindow(SW_SHOW);                                        //显示编辑框在单元格上面//
	createdit->SetFocus();                                                 //设置为焦点//
	createdit->SetSel(-1);                                                 //设置光标在文本框文字的最后//
}

void CDeviceChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString strEditData;
	distroyedit->GetWindowText(strEditData);
	strEditData = strEditData.Trim();
	if (strEditData.IsEmpty())             //如果输入为空，则销毁编辑框//
	{
		AfxMessageBox(_T("非法操作，输入不能为空！"));
		distroyedit->DestroyWindow();
		return;
	}
	if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
	{
		if(IDYES==MessageBox(_T("是否保存该修改？"), _T("提示"), MB_ICONQUESTION | MB_YESNO))
		{
			list->SetItemText(Item, 4, strEditData);      //将修改写入列表框//
			//待添加，将修改写入PLC//

		}
	}             
	else
		AfxMessageBox(_T("非法操作，请输入数字！"));
	distroyedit->DestroyWindow();                          //销毁对象//
}

//重载虚函数//
void CDeviceChiDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	m_listModulePara.SetFocus();
}

//编辑框失去焦点//
void CDeviceChiDlg::OnEnKillfocusEditCreateid()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bHaveEditCreate == true)                                               //如果之前创建了编辑框就销毁掉//
	{
		distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);           //销毁单元格编辑框对象//
		m_bHaveEditCreate = false;
	}
}

//重画工艺参数列表//
void CDeviceChiDlg::RePaintModuleList()
{
	HTREEITEM hCurSelItem = m_treeDevice.GetSelectedItem();
	UINT nCerSelModuleId = m_treeDevice.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeDevice.GetParentItem(hCurSelItem);
	if (hParentItem!=NULL)
	{
		m_vectTempModulePara.clear();
		for (int j = 0; j < m_pDataProvider->m_vectProModulePara.size(); j++)    //工艺参数//
		{
			if (m_pDataProvider->m_vectProModulePara[j].m_ProcessModuleId == nCerSelModuleId && m_pDataProvider->m_vectProModulePara[j].m_IsVisible)
			{
				m_vectTempModulePara.push_back(m_pDataProvider->m_vectProModulePara[j]);
			}
		}
		WriteToModuleList();
	}
}


void CDeviceChiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值


	UpdateParaValueShow();


	CDialog::OnTimer(nIDEvent);
}



void CDeviceChiDlg::UpdateParaValueShow()
{
	m_listModulePara.SetRedraw(FALSE);
	for (int i = 0; i < m_pDataProvider->m_vectProModulePara.size();i++)
	{
		m_listModulePara.SetItemText(i, 3, m_pDataProvider->m_vectProModulePara[i].ConvertParaValueToString());
	}
	m_listModulePara.SetRedraw(TRUE);
	m_listModulePara.Invalidate();
	m_listModulePara.UpdateWindow();

}
