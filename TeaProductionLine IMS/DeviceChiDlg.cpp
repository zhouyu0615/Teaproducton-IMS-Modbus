// DeviceChiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "DeviceChiDlg.h"
#include "afxdialogex.h"


// CDeviceChiDlg �Ի���

IMPLEMENT_DYNAMIC(CDeviceChiDlg, CDialog)

CDeviceChiDlg::CDeviceChiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceChiDlg::IDD, pParent)
{
	m_nCurSelModuleId = 0;//��ʼ����������������ǰѡ��ģ��ID//
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


// CDeviceChiDlg ��Ϣ�������

//�����С�����仯����Ӧ����//
void CDeviceChiDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
		ReSize();

}


BOOL CDeviceChiDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitTreeContrl();   //��ʼ��������//

	SetTimer(1, 1000, NULL);
	
	//��ʼ��2���б��//
	m_bHaveEditCreate = false;            //��ʼ����־λ����ʾ��û�д����༭��//
	CRect rectList1;
	m_listModulePara.GetWindowRect(&rectList1);
	m_listModulePara.SetExtendedStyle(m_listModulePara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE );
	m_listModulePara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listModulePara.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList1.Width() / 27*2, -1);
	m_listModulePara.InsertColumn(2, _T("���ղ���"), LVCFMT_CENTER, rectList1.Width() / 9 * 3.6, -1);
	m_listModulePara.InsertColumn(3, _T("��ǰֵ"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.6, -1);
	m_listModulePara.InsertColumn(4, _T("�趨ֵ"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.6, -1);
	m_listModulePara.InsertColumn(5, _T("��λ"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.5, -1);

	CRect rectList2;
	m_listDevicePara.GetWindowRect(&rectList2);
	m_listDevicePara.SetExtendedStyle(m_listDevicePara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE);
	m_listDevicePara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listDevicePara.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList2.Width() / 7*1.2, -1);
	m_listDevicePara.InsertColumn(2, _T("�豸"), LVCFMT_CENTER, rectList2.Width() / 7 * 3.92, -1);
	m_listDevicePara.InsertColumn(3, _T("��ǰ״̬"), LVCFMT_CENTER, rectList2.Width() / 7 * 1.8, -1);

	//�����ؼ���С//
	CRect TempRect;
	GetClientRect(&TempRect);                                                    //ȡ�ͻ�����С//    
	m_OldSize.x = TempRect.right - TempRect.left;
	m_OldSize.y = TempRect.bottom - TempRect.top;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//���²��ִ����ڵĿؼ�//
void CDeviceChiDlg::ReSize()
{
	float fsp[2];
	POINT recNewSize; //��ȡ���ڶԻ���Ĵ�С//  
	CRect TempRect;
	GetClientRect(&TempRect);     //ȡ�ͻ�����С//    
	recNewSize.x = TempRect.right - TempRect.left;
	recNewSize.y = TempRect.bottom - TempRect.top;
	fsp[0] = (float)recNewSize.x / m_OldSize.x;
	fsp[1] = (float)recNewSize.y / m_OldSize.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�//  
	CPoint OldBRPoint, BRPoint; //���½�//  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�//    
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID//  
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

//���³�ʼ�����οؼ�//
void CDeviceChiDlg::InitTreeContrl()
{
	m_treeDevice.DeleteAllItems();
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��//   
	HTREEITEM hFirItem;  // �ɱ�ʾ��һһ���ڵ�ľ��//
	HICON hIcon[1];      // ͼ��������//
	hIcon[0] = theApp.LoadIcon(IDI_ICONPLUSGREEN);
	// ����ͼ������CImageList����   
	m_imageList.Create(32, 32, ILC_COLOR32, 1, 1);
	m_imageList.Add(hIcon[0]);
	// Ϊ���οؼ�����ͼ������//  
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

//�����οؼ�ѡ����Ŀ�����仯ʱ����Ӧ����//
void CDeviceChiDlg::OnTvnSelchangedTreeDeviceChidlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//ɾ�������б��ؼ�������//
	m_listDevicePara.DeleteAllItems();
	m_listModulePara.DeleteAllItems();

	m_video.StopPlay();   //��Ƶ����ֹͣ//

	HTREEITEM hCurSelItem = m_treeDevice.GetSelectedItem();
	UINT TempID = m_treeDevice.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeDevice.GetParentItem(hCurSelItem);
	CString strCurPosition;
	if (hParentItem!=NULL)                              //���ѡ�е��ǹ���ģ��ڵ�//
	{
		m_nCurSelModuleId = TempID;                                                                 //��ǰѡ��ģ���ID//
		CString strLineName = m_treeDevice.GetItemText(hParentItem);    //��������������//
		strCurPosition = _T("��ǰλ�ã� ") + strLineName + _T(" >> ") + m_treeDevice.GetItemText(hCurSelItem)+_T(" >> ");  //λ��������//
		m_textCurPosition.SetWindowText(strCurPosition);  
		
		SearchFromDataProvider(m_nCurSelModuleId);    //����ǰѡ��ģ���µ�����ͷ�����ղ������豸�����浽��ʱ����//
		WriteToDeviceList();                          //��д�����б��//
		WriteToModuleList();
		if (!m_vectTempVideo.empty())                 //�����ģ������Ƶ��أ�����ʾ//
		{
			m_video.SetDeviceInfo(m_vectTempVideo[0].m_strIPAddr, m_vectTempVideo[0].m_port, 0, _T("admin"), _T("admin"));
			m_video.StartPlay();
		}		
	}
	else                                             //���ѡ�е��������߽ڵ�//
	{
		strCurPosition = _T("��ǰλ�ã� ") + m_treeDevice.GetItemText(hCurSelItem) + _T(" >> ");
		m_textCurPosition.SetWindowText(strCurPosition);
		m_listModulePara.DeleteAllItems();
		m_listDevicePara.DeleteAllItems();
	}

}

//����ǰѡ��ģ���µ�����ͷ�����ղ������豸�����浽��ʱ����//
void CDeviceChiDlg::SearchFromDataProvider(UINT nCerSelModuleId)
{
	m_vectTempDevicePara.clear();
	m_vectTempModulePara.clear();
	m_vectTempVideo.clear();
	for (int n = 0; n < m_pDataProvider->m_vectDevicePara.size();n++)  //�豸����//
	{
		if (m_pDataProvider->m_vectDevicePara[n].m_ProcessModuleId==nCerSelModuleId)
		{
			m_vectTempDevicePara.push_back(m_pDataProvider->m_vectDevicePara[n]);
		}
	}
	for (int i = 0; i < m_pDataProvider->m_vectVideo.size();i++)      //����ͷ//
    {
		if (m_pDataProvider->m_vectVideo[i].m_ModuleId==nCerSelModuleId)
		{
			m_vectTempVideo.push_back(m_pDataProvider->m_vectVideo[i]);
			break;
		}
    }
	for (int j = 0; j < m_pDataProvider->m_vectProModulePara.size();j++)    //���ղ���//
	{
		if (m_pDataProvider->m_vectProModulePara[j].m_ProcessModuleId==nCerSelModuleId && m_pDataProvider->m_vectProModulePara[j].m_IsVisible)
		{
			m_vectTempModulePara.push_back(m_pDataProvider->m_vectProModulePara[j]);
		}
	}
}

//��д���ղ����б��//
void CDeviceChiDlg::WriteToModuleList()
{
	m_listModulePara.DeleteAllItems();
	CString strItem;                                               //ģ���µĹ��ղ�����ʾ��list1//
	for (int n = 0; n < m_vectTempModulePara.size(); n++)
	{
		strItem.Format(_T("%d"), n + 1);
		m_listModulePara.InsertItem(n, _T(""));
		m_listModulePara.SetItemText(n, 1, strItem);
		m_listModulePara.SetItemText(n, 2, m_vectTempModulePara[n].m_strParaName);	
		if (m_vectTempModulePara[n].m_fSetValue==-3001)
		{
			m_listModulePara.SetItemText(n, 4, _T("��"));
		} 
		else
		{
			strItem.Format(_T("%.2f"), m_vectTempModulePara[n].m_fSetValue);
			m_listModulePara.SetItemText(n, 4, strItem);
		}
		m_listModulePara.SetItemText(n, 5, m_vectTempModulePara[n].m_strUnit);
	}  
}   

//��д�豸�����б��//
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
			m_listDevicePara.SetItemText(n, 3, _T("����"));
		}
		else
		{
			m_listDevicePara.SetItemText(n, 3, _T("ֹͣ"));
		}
	}
}

void CDeviceChiDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(0, 0, 250));   //����Ϊ��ɫ����
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


HBRUSH CDeviceChiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor==CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(RGB(0, 0, 0));             //������ɫ//
		pDC->SetBkMode(TRANSPARENT);                 // ����͸��//
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	else
		hbr = m_brush;
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//˫���豸�����б����Ӧ����//
void CDeviceChiDlg::OnNMDblclkLi2Devicepara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_nDClkLineItem = pNMItemActivate->iItem;

	if (m_nDClkLineItem == -1)
		return;
	CDeviceContrlPopDlg DeviceContrlPopDlg;          //�豸����̨��������//
	DeviceContrlPopDlg.m_vDevicePara.push_back(m_vectTempDevicePara[m_nDClkLineItem]);        //��ѡ���豸����������������//
	DeviceContrlPopDlg.DoModal();

	*pResult = 0;
}

//˫�����ղ����б����Ӧ����//
void CDeviceChiDlg::OnNMDblclkLi1Modulepara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������//
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	if (pEditCtrl->iItem == -1)                                                //������ǹ�����//
	{
		if (m_bHaveEditCreate == true)                                            //���֮ǰ�����˱༭������ٵ�//
		{
			distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);        //���ٵ�Ԫ��༭�����//
			m_bHaveEditCreate = false;
		}
	}
	else
	{
		if (m_bHaveEditCreate == true)
		{
			if (!(m_OldItem == pEditCtrl->iItem && m_OldSubItem == pEditCtrl->iSubItem))    //������еĵ�Ԫ����֮ǰ�����õ�//
			{
				distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);
				m_bHaveEditCreate = false;
				createEdit(pEditCtrl, &m_Edit, m_OldItem, m_OldSubItem, m_bHaveEditCreate);      //�����༭��//
			}
			else                                                                       //���еĵ�Ԫ����֮ǰ�����õ�//
			{
				m_Edit.SetFocus();                                                     //����Ϊ����//
			}
		}
		else
		{
			m_OldItem = pEditCtrl->iItem;                                                 //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
			m_OldSubItem = pEditCtrl->iSubItem;                                           //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
			createEdit(pEditCtrl, &m_Edit, m_OldItem, m_OldSubItem, m_bHaveEditCreate);         //�����༭��//
		}
	}
	*pResult = 0;
}

//������Ԫ��༭����//
void CDeviceChiDlg::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
//pEditCtrlΪ�б����ָ�룬createditΪ�༭��ָ�����//
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼//
{
	Item = pEditCtrl->iItem;                     //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	SubItem = pEditCtrl->iSubItem;               //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_CENTER | ES_WANTRETURN,CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);  //�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��//
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);                   //��������//
	createdit->SetParent(&m_listModulePara);                      //��listcontrol����Ϊ������//
	CRect  EditRect;
	m_listModulePara.GetSubItemRect(m_OldItem, 4, LVIR_LABEL, EditRect);      //��ȡ��Ԫ��Ŀռ�λ����Ϣ//
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listModulePara.GetColumnWidth(4) - 1, EditRect.bottom - 1);//+1��-1�ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_listModulePara.GetItemText(m_OldItem, 4);             //��õ�ǰ�趨ֵ//
	createdit->SetWindowText(strItem);                                     //����Ԫ���ַ���ʾ�ڱ༭����//
	createdit->MoveWindow(&EditRect);                                      //���༭��λ�÷�����Ӧ��Ԫ����//
	createdit->ShowWindow(SW_SHOW);                                        //��ʾ�༭���ڵ�Ԫ������//
	createdit->SetFocus();                                                 //����Ϊ����//
	createdit->SetSel(-1);                                                 //���ù�����ı������ֵ����//
}

void CDeviceChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString strEditData;
	distroyedit->GetWindowText(strEditData);
	strEditData = strEditData.Trim();
	if (strEditData.IsEmpty())             //�������Ϊ�գ������ٱ༭��//
	{
		AfxMessageBox(_T("�Ƿ����������벻��Ϊ�գ�"));
		distroyedit->DestroyWindow();
		return;
	}
	if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
	{
		if(IDYES==MessageBox(_T("�Ƿ񱣴���޸ģ�"), _T("��ʾ"), MB_ICONQUESTION | MB_YESNO))
		{
			list->SetItemText(Item, 4, strEditData);      //���޸�д���б��//
			//����ӣ����޸�д��PLC//

		}
	}             
	else
		AfxMessageBox(_T("�Ƿ����������������֣�"));
	distroyedit->DestroyWindow();                          //���ٶ���//
}

//�����麯��//
void CDeviceChiDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_listModulePara.SetFocus();
}

//�༭��ʧȥ����//
void CDeviceChiDlg::OnEnKillfocusEditCreateid()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bHaveEditCreate == true)                                               //���֮ǰ�����˱༭������ٵ�//
	{
		distroyEdit(&m_listModulePara, &m_Edit, m_OldItem, m_OldSubItem);           //���ٵ�Ԫ��༭�����//
		m_bHaveEditCreate = false;
	}
}

//�ػ����ղ����б�//
void CDeviceChiDlg::RePaintModuleList()
{
	HTREEITEM hCurSelItem = m_treeDevice.GetSelectedItem();
	UINT nCerSelModuleId = m_treeDevice.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeDevice.GetParentItem(hCurSelItem);
	if (hParentItem!=NULL)
	{
		m_vectTempModulePara.clear();
		for (int j = 0; j < m_pDataProvider->m_vectProModulePara.size(); j++)    //���ղ���//
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ


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
