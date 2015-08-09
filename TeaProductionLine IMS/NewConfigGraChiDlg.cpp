// NewConfigGraChiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "NewConfigGraChiDlg.h"
#include "afxdialogex.h"


// CNewConfigGraChiDlg �Ի���
bool CNewConfigGraChiDlg::m_bIsAddConfig = false;
IMPLEMENT_DYNAMIC(CNewConfigGraChiDlg, CDialogEx)

CNewConfigGraChiDlg::CNewConfigGraChiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewConfigGraChiDlg::IDD, pParent)
{
	m_nLastSelLineItem = -1;
	m_bHaveEditCreate = false;
}

CNewConfigGraChiDlg::~CNewConfigGraChiDlg()
{
}

void CNewConfigGraChiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edNewConfigName);
	DDX_Control(pDX, IDC_COMBO1, m_cboxNewConfigLine);
	DDX_Control(pDX, IDC_EDIT3, m_edNote);
	DDX_Control(pDX, IDC_COMBO2, m_cboxModule);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
}


BEGIN_MESSAGE_MAP(CNewConfigGraChiDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewConfigGraChiDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CNewConfigGraChiDlg::OnCbnDropdownCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CNewConfigGraChiDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNewConfigGraChiDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNewConfigGraChiDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewConfigGraChiDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CNewConfigGraChiDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, &CNewConfigGraChiDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &CNewConfigGraChiDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CNewConfigGraChiDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CNewConfigGraChiDlg::OnBnClickedButton5)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CNewConfigGraChiDlg::OnNMClickList2)
	ON_EN_KILLFOCUS(IDC_EDIT_CREATE, &CNewConfigGraChiDlg::OnEnKillfocusEditCreate)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewConfigGraChiDlg::OnBnClickedButton1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CNewConfigGraChiDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// CNewConfigGraChiDlg ��Ϣ�������


BOOL CNewConfigGraChiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ������list�ı�ͷ//
	CRect rectList1;
	m_list1.GetWindowRect(&rectList1);
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);
	m_list1.InsertColumn(0, _T(""), LVCFMT_CENTER, rectList1.Width() / 24, -1);
	m_list1.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList1.Width() / 9, -1);
	m_list1.InsertColumn(2, _T("����"), LVCFMT_CENTER, rectList1.Width() / 9 * 4, -1);
	m_list1.InsertColumn(3, _T("�Ƿ���"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.8, -1);
	m_list1.InsertColumn(4, _T("��λ"), LVCFMT_CENTER, rectList1.Width() / 9 * 1.8, -1);

	CRect rectList2;
	m_list2.GetWindowRect(&rectList2);
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES  | LBS_OWNERDRAWVARIABLE);
	m_list2.InsertColumn(0, _T(""), LVCFMT_CENTER, rectList2.Width() / 24, -1);
	m_list2.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList2.Width() / 9, -1);
	m_list2.InsertColumn(2, _T("����"), LVCFMT_CENTER, rectList2.Width() / 9 * 4, -1);
	m_list2.InsertColumn(3, _T("�趨ֵ"), LVCFMT_CENTER, rectList2.Width() / 9 * 1.8, -1);
	m_list2.InsertColumn(4, _T("��λ"), LVCFMT_CENTER, rectList2.Width() / 9 * 1.8, -1);

	//��д������������//
	m_cboxNewConfigLine.ResetContent();                            //�����������//
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size();n++)
		m_cboxNewConfigLine.AddString(m_pDataProvider->m_vectProductionLine[n].m_strLineName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CNewConfigGraChiDlg::searchModuleByLineID(int lineID)       //���������ߵ�ID�ҵ��������е�ģ�飬���洢��m_vectCombo//
{
	if (!m_vectCombo.empty())
		m_vectCombo.clear();
	for (int n = 0; n < m_pDataProvider->m_vectProcessModule.size();n++)
		if (m_pDataProvider->m_vectProcessModule[n].m_ProcessLineId==lineID)
			m_vectCombo.push_back(m_pDataProvider->m_vectProcessModule[n]);
}

void CNewConfigGraChiDlg::searchModuleParaByModuleID(int moduleID)     //����ģ��ID�ҵ��������н����䷽�Ĺ��ղ��������洢��m_vectList1//
{
	if (!m_vectList1.empty())
	    m_vectList1.clear();
	for (int n = 0; n < m_pDataProvider->m_vectProModulePara.size();n++)
		if (m_pDataProvider->m_vectProModulePara[n].m_ProcessModuleId == moduleID && m_pDataProvider->m_vectProModulePara[n].m_IsConfig!=0)
			m_vectList1.push_back(m_pDataProvider->m_vectProModulePara[n]);
}

//����������������ݷ����仯//
void CNewConfigGraChiDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nLastSelLineItem == m_cboxNewConfigLine.GetCurSel())
		return;
	else
		m_nLastSelLineItem = m_cboxNewConfigLine.GetCurSel();
	//���������ģ��������//
	m_list2.DeleteAllItems();
	m_list1.DeleteAllItems();
	m_vectList1.clear();
	m_vectList2.clear();
	m_cboxModule.ResetContent();

	//������дģ��������//
	int nTemp = m_cboxNewConfigLine.GetCurSel();
	searchModuleByLineID(m_pDataProvider->m_vectProductionLine[nTemp].m_Id);
	for (int n = 0; n < m_vectCombo.size();n++)
		m_cboxModule.AddString(m_vectCombo[n].m_strProcessModuleName);
}

//���û��㿪������������//
void CNewConfigGraChiDlg::OnCbnDropdownCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!m_vectList2.empty())
	{
		AfxMessageBox(_T("���棡��ʱ����������ѡ�����ʧδ���������!"));
	}
}

//����ģ��������ѡ�����ݷ����仯//
void CNewConfigGraChiDlg::OnCbnSelchangeCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nTemp = m_cboxModule.GetCurSel();                  //�õ�������ǰѡ����Ŀ�����//
	searchModuleParaByModuleID(m_vectCombo[nTemp].m_Id);   //��ģ����µĹ��ղ���д�������ݴ�m_vectList1//
	std::vector<int> vectItem;                             //�ݴ�m_vectList1���Ѿ���ѡ���䷽�Ĳ������±�//
	for (int n = 0; n < m_vectList1.size();n++)            //����m_vectList1���Ѿ���ѡ���䷽�Ĳ������±�//
		for (int m = 0; m < m_vectList2.size();m++)
			if (m_vectList1[n].m_Id==m_vectList2[m].m_Id)
			{
				vectItem.push_back(n);
				break;
			}
	for (int n = vectItem.size()-1; n >= 0; n--)          //ɾ������m_vectList1���Ѿ���ѡ���䷽�Ĳ���//
	{
		m_vectList1.erase(m_vectList1.begin()+vectItem[n]);
	}

	//��д��ѡ�����б��//
	m_list1.DeleteAllItems();
	CString strItem;
	for (int n = 0; n < m_vectList1.size();n++)
	{
		m_list1.InsertItem(n, _T(""));
		strItem.Format(_T("%d"), n + 1);
		m_list1.SetItemText(n, 1, strItem);
		m_list1.SetItemText(n, 2, m_vectList1[n].m_strParaName);
		if (m_vectList1[n].m_IsVisible==0)
			m_list1.SetItemText(n, 3, _T("��"));
		else
			m_list1.SetItemText(n, 3, _T("��"));
		m_list1.SetItemText(n, 4, m_vectList1[n].m_strUnit);
	}
}

//��ѡ������ȫѡ��ť��Ӧ����//
void CNewConfigGraChiDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nNumOfCount = m_list1.GetItemCount();
	for (int n = 0; n < nNumOfCount;n++)
		m_list1.SetCheck(n);
}

//��ѡ���������ѡ��ť//
void CNewConfigGraChiDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_list1.GetItemCount(); n++)
		m_list1.SetCheck(n,0);
}

//�����䷽��ť����Ӧ����//
void CNewConfigGraChiDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	std::vector<int> vectSelItem;           //�ݴ�LIST1�ڱ�ѡ����Ŀ���±�//
	int nNumOfList2Item;                    //ĿǰList2��������Ŀ������//	
	CString strItem;                        //�б��2���к�//
	for (int n = 0;n<m_vectList1.size();n++)                          //������б�ѡ����Ŀ���±�//
	{
		if (m_list1.GetCheck(n))
		{
			vectSelItem.push_back(n);
			m_vectList2.push_back(m_vectList1[n]);
			nNumOfList2Item = m_list2.GetItemCount();                //list2�ڵ�ǰ������Ŀ������//
			m_list2.InsertItem(nNumOfList2Item, _T(""));
			strItem.Format(_T("%d"), nNumOfList2Item + 1);
			m_list2.SetItemText(nNumOfList2Item, 1, strItem);
			m_list2.SetItemText(nNumOfList2Item, 2, m_vectList1[n].m_strParaName);
			m_list2.SetItemText(nNumOfList2Item, 4, m_vectList1[n].m_strUnit);
		}
	}	
	for (int n = vectSelItem.size()-1; n >= 0; n--)                   
	{
		m_list1.DeleteItem(vectSelItem[n]);                           //�Ӵ�ѡ�б���ɾ��//
		m_vectList1.erase(m_vectList1.begin() + vectSelItem[n]);      //��m_vectList1ɾ��//
	}
	if (!vectSelItem.empty())                    //���ɾ����ĳЩ��Ŀ������д�б������ʾ�����//
		for (int n = 0; n < m_list1.GetItemCount(); n++)
		{
			strItem.Format(_T("%d"), n + 1);
			m_list1.SetItemText(n, 1, strItem);
		}
}

//��ѡ������ȫѡ��ť//
void CNewConfigGraChiDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_list2.GetItemCount(); n++)
		m_list2.SetCheck(n);
}

//��ѡ���������ѡ��ť//
void CNewConfigGraChiDlg::OnBnClickedButton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_list2.GetItemCount(); n++)
		m_list2.SetCheck(n, 0);
}

//��ѡ������ɾ����ť//
void CNewConfigGraChiDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nCurSelModuleItem = m_cboxModule.GetCurSel();           //ģ��������ǰѡ�е���Ŀ�����//
	int nCurSelModuleID = -1;
	int nNumOfList1;                                            //list1�ڹ��м���//
	CString strTemp;                                            //�ݴ�LIST1���к�//
	std::vector<int> vectTemp;                                  //�ݴ汻ѡ��ɾ���Ĳ�����m_vectList2����±�//
	if (nCurSelModuleItem >= 0)                                 //��ȡ��ǰѡ��ģ���ID//
		nCurSelModuleID = m_vectCombo[nCurSelModuleItem].m_Id;

	for (int n = 0; n < m_list2.GetItemCount();n++)       
	{
		if (m_list2.GetCheck(n))                          //�����ѡ��״̬//
		{
			if (m_vectList2[n].m_ProcessModuleId == nCurSelModuleID)  //�����ѡ�в�������ģ��������ģ������������ѡ��ģ��//
			{
				m_vectList2[n].m_fSetValue=-3001;                     //�������Ż�m_vectList1ǰ������������趨ֵ//
				m_vectList1.push_back(m_vectList2[n]);                //���ò����Ż�m_vectList1//
				nNumOfList1 = m_list1.GetItemCount();                 //���б��1����ʾ�ò���//
				m_list1.InsertItem(nNumOfList1, _T(""));
				strTemp.Format(_T("%d"), nNumOfList1 + 1);
				m_list1.SetItemText(nNumOfList1, 1, strTemp);
				m_list1.SetItemText(nNumOfList1, 2, m_vectList2[n].m_strParaName);
				if (m_vectList2[n].m_IsVisible == 0)
					m_list1.SetItemText(nNumOfList1, 3, _T("��"));
				else
					m_list1.SetItemText(nNumOfList1, 3, _T("��"));
				m_list1.SetItemText(nNumOfList1, 4, m_vectList2[n].m_strUnit);
			}
			vectTemp.push_back(n);                           //����ѡ�в�����m_vectList2����±��������//
		}
	}

	for (int n = vectTemp.size() - 1; n >= 0;n--)            //��ѡ�еĲ������б��������2���б�2ɾ��//
	{
		m_vectList2.erase(m_vectList2.begin() + vectTemp[n]);
		m_list2.DeleteItem(vectTemp[n]);
	}

	if (!vectTemp.empty())                    //���ɾ����ĳЩ��Ŀ������д�б������ʾ�����//
		for (int n = 0; n < m_list2.GetItemCount();n++)
        {
			strTemp.Format(_T("%d"), n + 1);
			m_list2.SetItemText(n, 1, strTemp);
        }
}

//���ֵ��ť//
void CNewConfigGraChiDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int n = 0; n < m_vectList2.size();n++)
	{
		m_vectList2[n].m_fSetValue=-3001;          //������趨ֵ//
		m_list2.SetItemText(n, 3, _T(""));         //��Ӧ�б��λ����ʾΪ��//
	}
}

//�������ð�ť����Ӧ����//
void CNewConfigGraChiDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strName, strNote;
	m_edNewConfigName.GetWindowText(strName);
	m_edNote.GetWindowText(strNote);
	if (strName == _T("") && strNote == _T("") && m_cboxNewConfigLine.GetCurSel() == CB_ERR)
		return;
	int nResult = MessageBox(_T("�ò�������ʧ����δ��������ݣ��Ƿ������"), _T("����"), MB_YESNO | MB_ICONEXCLAMATION);
	if (nResult == IDYES)
	{ 
		m_edNewConfigName.SetWindowText(_T(""));  //ɾ�������������//
		m_edNote.SetWindowText(_T(""));
		m_cboxModule.ResetContent();
		m_cboxNewConfigLine.ResetContent();
		m_list1.DeleteAllItems();
		m_vectList1.clear();
		m_list2.DeleteAllItems();
		m_vectList2.clear();
		m_vectCombo.clear();
		for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)   //������д������������//
			m_cboxNewConfigLine.AddString(m_pDataProvider->m_vectProductionLine[n].m_strLineName);
		m_nLastSelLineItem = -1;
	}
}

//�����б��2//
void CNewConfigGraChiDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	if (pEditCtrl->iItem == -1 || pEditCtrl->iSubItem!=3)                                                //������ǹ�����//
	{
		if (m_bHaveEditCreate == true)                                            //���֮ǰ�����˱༭������ٵ�//
		{
			distroyEdit(&m_list2, &m_Edit, m_OldItem, m_OldSubItem);              //���ٵ�Ԫ��༭�����//
			m_bHaveEditCreate = false;
		}
	}
	else
	{
		if (m_bHaveEditCreate == true)
		{
			if (!(m_OldItem == pEditCtrl->iItem && m_OldSubItem == pEditCtrl->iSubItem))    //������еĵ�Ԫ����֮ǰ�����õ�//
			{
				distroyEdit(&m_list1, &m_Edit, m_OldItem, m_OldSubItem);
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

//�����༭��//
void CNewConfigGraChiDlg::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
//pEditCtrlΪ�б����ָ�룬createditΪ�༭��ָ�����//
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼//
{
	Item = pEditCtrl->iItem;                     //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	SubItem = pEditCtrl->iSubItem;               //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_CENTER | ES_WANTRETURN, CRect(0, 0, 0, 0), this, IDC_EDIT_CREATE);  //�����༭�����,IDC_EDIT_CREATEΪ�ؼ�ID��//
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);                   //��������//
	createdit->SetParent(&m_list2);                      //��listcontrol����Ϊ������//
	CRect  EditRect;
	m_list2.GetSubItemRect(m_OldItem, 3, LVIR_LABEL, EditRect);      //��ȡ��Ԫ��Ŀռ�λ����Ϣ//
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_list2.GetColumnWidth(3) - 1, EditRect.bottom - 1);//+1��-1�ñ༭�����ڵ�ס�б���е�������//
	CString strTemp;
	strTemp = m_list2.GetItemText(m_OldItem, 3);
	createdit->SetWindowText(strTemp);
	createdit->MoveWindow(&EditRect);                                      //���༭��λ�÷�����Ӧ��Ԫ����//
	createdit->ShowWindow(SW_SHOW);                                        //��ʾ�༭���ڵ�Ԫ������//
	createdit->SetFocus();                                                 //����Ϊ����//
	createdit->SetSel(-1);                                                 //���ù�����ı������ֵ����//
}

//���ٱ༭��//
void CNewConfigGraChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString strEditData;
	distroyedit->GetWindowText(strEditData);
	strEditData = strEditData.Trim();
	if (strEditData.IsEmpty())             //�������Ϊ�գ������ٱ༭��//
	{
		distroyedit->DestroyWindow();
		m_vectList2[Item].m_fSetValue = -3001;
		list->SetItemText(Item, 3, _T(""));
		return;
	}
	if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
	{
		list->SetItemText(Item, 3, strEditData);      //���޸�д���б��//
		float tempfloat = (float)_wtof(strEditData);
		m_vectList2[Item].m_fSetValue = tempfloat;    //���޸ĺ��ֵ��������//
	}
	else
		AfxMessageBox(_T("�Ƿ����������������֣�"));
	distroyedit->DestroyWindow();                          //���ٶ���//
}

//�༭��ʧȥ����//
void CNewConfigGraChiDlg::OnEnKillfocusEditCreate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bHaveEditCreate == true)                                               //���֮ǰ�����˱༭������ٵ�//
	{
		distroyEdit(&m_list2, &m_Edit, m_OldItem, m_OldSubItem);                 //���ٵ�Ԫ��༭�����//
		m_bHaveEditCreate = false;
	}
}

//�����麯��//
void CNewConfigGraChiDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_list2.SetFocus();
}

//�����䷽��ť//
void CNewConfigGraChiDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strConfigName;
	m_edNewConfigName.GetWindowText(strConfigName);
	strConfigName = strConfigName.Trim();
	if (strConfigName == _T(""))          //����䷽���Ƿ�Ϊ��//
	{
		AfxMessageBox(_T("�������䷽ʧ�ܣ�����Ϊ�䷽������"));
		return;
	}
	for (int n = 0; n < m_vectList2.size();n++)   //�������䷽�Ĳ����趨ֵ�Ƿ�����//
	{
		if (m_list2.GetItemText(n,3)==_T(""))
		{
			AfxMessageBox(_T("�������䷽ʧ�ܣ���Ϊÿ���䷽�������Ԥ��ֵ��"));
			return;
		}
	}
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size();n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_strFormulaName==strConfigName)
		{
			AfxMessageBox(_T("�������䷽ʧ�ܣ����䷽�����ѱ�ʹ�ã�������������"));
			return;
		}
	}
	CString strNote;         //�洢��ע����//
	m_edNote.GetWindowText(strNote);
	for (int n = 0; n < m_vectList2.size(); n++)    //�������ݿ�//
	{
		m_TempFormula.m_IsCurrentFormula = 0;
		m_TempFormula.m_DefaultValue = m_vectList2[n].m_fSetValue;
		m_TempFormula.m_IsDefaultFormula = 0;
		m_TempFormula.m_ProcessParaId = m_vectList2[n].m_Id;
		m_TempFormula.m_ProductionLineId = m_vectList2[n].m_ProductionLineId;
		m_TempFormula.m_strFormulaName = strConfigName;
		m_TempFormula.m_strNote = strNote;
		m_TempFormula.m_strParaValueUnit = m_vectList2[n].m_strUnit;
		m_TempFormula.m_strProcessParaName = m_vectList2[n].m_strParaName;
		m_TempFormula.m_strProductionLineName = m_vectList2[n].m_strProductionLineName;
		m_pDataProvider->AddFormulaToDatabase(m_TempFormula);
	}
	AfxMessageBox(_T("�������䷽�ɹ���"));
	m_bIsAddConfig = true;
	//�����������ʾ��//
	m_edNewConfigName.SetWindowText(_T(""));
	m_edNote.SetWindowText(_T(""));
	m_cboxNewConfigLine.ResetContent();
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)   //������д������������//
		m_cboxNewConfigLine.AddString(m_pDataProvider->m_vectProductionLine[n].m_strLineName);
	m_nLastSelLineItem = -1;
	m_cboxModule.ResetContent();
	m_vectCombo.clear();
	m_list1.DeleteAllItems();
	m_vectList1.clear();
	m_list2.DeleteAllItems();
	m_vectList2.clear();
}

//����䷽�����Ƿ��ѱ�ʹ��//
void CNewConfigGraChiDlg::OnEnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strConfigName;
	m_edNewConfigName.GetWindowText(strConfigName);
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_strFormulaName == strConfigName)
		{
			AfxMessageBox(_T("���䷽�����ѱ�ʹ�ã��������������䷽��"));
			return;
		}
	}
}
