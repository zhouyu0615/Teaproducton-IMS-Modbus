// OldConfigGraChiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProductionLine IMS.h"
#include "OldConfigGraChiDlg.h"
#include "afxdialogex.h"


// COldConfigGraChiDlg �Ի���

IMPLEMENT_DYNAMIC(COldConfigGraChiDlg, CDialogEx)

COldConfigGraChiDlg::COldConfigGraChiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COldConfigGraChiDlg::IDD, pParent)
{
	m_bIsNameChange=false;                 //��ǰ�༭���ڵ��䷽�Ƿ����˸���//
	m_bIsParaValueChange=false;            //�Ƿ��޸����䷽������ֵ//
	m_bIsNoteChange=false;                 //�Ƿ��޸����䷽�ı�ע//
	m_bIsDelePara=false;                   //�Ƿ�ɾ�����䷽����//
	m_bIsAddPara=false;                    //�Ƿ�������䷽����//
	m_strOldName=_T("");                  //�޸�֮ǰ���䷽��//
	m_strOldNote = _T("");                 //�޸�֮ǰ�ı�ע//
	m_bIsCurConfigChange = false;
}

COldConfigGraChiDlg::~COldConfigGraChiDlg()
{
}

void COldConfigGraChiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listAllConfig);
	DDX_Control(pDX, IDC_LIST1, m_listConfigPara);
	DDX_Control(pDX, IDC_TREE1, m_treeConfig);
	DDX_Control(pDX, IDC_EDIT4, m_edConfigName);
	DDX_Control(pDX, IDC_EDIT5, m_edConfigLine);
	DDX_Control(pDX, IDC_EDIT6, m_edNote);
}


BEGIN_MESSAGE_MAP(COldConfigGraChiDlg, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &COldConfigGraChiDlg::OnTvnSelchangedTree1)
//	ON_EN_CHANGE(IDC_EDIT4, &COldConfigGraChiDlg::OnEnChangeEdit4)
ON_NOTIFY(NM_RCLICK, IDC_LIST1, &COldConfigGraChiDlg::OnNMRClickList1)
ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, &COldConfigGraChiDlg::OnTvnSelchangingTree1)
//ON_EN_KILLFOCUS(IDC_EDIT4, &COldConfigGraChiDlg::OnEnKillfocusEdit4)
//ON_EN_KILLFOCUS(IDC_EDIT6, &COldConfigGraChiDlg::OnEnKillfocusEdit6)
ON_BN_CLICKED(IDC_BUTTON6, &COldConfigGraChiDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON2, &COldConfigGraChiDlg::OnBnClickedButton2)
ON_NOTIFY(NM_CLICK, IDC_LIST1, &COldConfigGraChiDlg::OnNMClickList1)
ON_EN_KILLFOCUS(IDC_EDIT_CREATE1, &COldConfigGraChiDlg::OnEnKillfocusEditCreate1)
ON_BN_CLICKED(IDC_BUTTON1, &COldConfigGraChiDlg::OnBnClickedButton1)
ON_EN_KILLFOCUS(IDC_EDIT4, &COldConfigGraChiDlg::OnEnKillfocusEdit4)
ON_BN_CLICKED(IDC_BUTTON7, &COldConfigGraChiDlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON3, &COldConfigGraChiDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &COldConfigGraChiDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// COldConfigGraChiDlg ��Ϣ�������


BOOL COldConfigGraChiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ�������б�ı�ͷ//
	CRect rectList1;
	m_listAllConfig.GetWindowRect(&rectList1);
	m_listAllConfig.SetExtendedStyle(m_listAllConfig.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE);
	m_listAllConfig.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listAllConfig.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList1.Width() / 11, -1);
	m_listAllConfig.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rectList1.Width() / 11*4, -1);
	m_listAllConfig.InsertColumn(3, _T("����ʹ�õ��䷽"), LVCFMT_CENTER, rectList1.Width() / 11*3, -1);
	m_listAllConfig.InsertColumn(4, _T("Ĭ���䷽"), LVCFMT_CENTER, rectList1.Width() / 11*3, -1);

	CRect rectList2;
	m_listConfigPara.GetWindowRect(&rectList2);
	m_listConfigPara.SetExtendedStyle(m_listConfigPara.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LBS_OWNERDRAWVARIABLE);
	m_listConfigPara.InsertColumn(0, _T(""), LVCFMT_CENTER, rectList2.Width() / 24, -1);
	m_listConfigPara.InsertColumn(1, _T("���"), LVCFMT_CENTER, rectList2.Width() / 9, -1);
	m_listConfigPara.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rectList2.Width() / 9 * 4, -1);
	m_listConfigPara.InsertColumn(3, _T("�趨ֵ"), LVCFMT_CENTER, rectList2.Width() / 9 * 1.8, -1);
	m_listConfigPara.InsertColumn(4, _T("��λ"), LVCFMT_CENTER, rectList2.Width() / 9 * 1.8, -1);

	InitTreeContrl();                      //��д��������//
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size();n++)          //��д�б��1//
		WriteToList1(m_pDataProvider->m_vectProductionLine[n].m_Id, m_pDataProvider->m_vectProductionLine[n].m_strLineName, n);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//��д��������//
void COldConfigGraChiDlg::InitTreeContrl()
{
	m_treeConfig.DeleteAllItems();
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��//   
	HTREEITEM hFirItem;  // �ɱ�ʾ��һһ���ڵ�ľ��//
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)
	{
		hRoot = m_treeConfig.InsertItem(m_pDataProvider->m_vectProductionLine[n].m_strLineName, 0, 0, NULL, TVI_LAST);
		m_treeConfig.SetItemData(hRoot, m_pDataProvider->m_vectProductionLine[n].m_Id);
		searchConfigFromLine(m_pDataProvider->m_vectProductionLine[n].m_Id);
		for (int i = 0; i < m_vectConfigID.size();i++)
		{
			hFirItem = m_treeConfig.InsertItem(m_vectConfigName[i], 0, 0, hRoot, TVI_LAST);
			m_treeConfig.SetItemData(hFirItem,m_vectConfigID[i]);
		}
	}
}

//����������ID�ҵ����µ������䷽�������䷽ID�����ƶ�Ӧ����set����//
void COldConfigGraChiDlg::searchConfigFromLine(int nLineID)
{
	m_vectConfigID.clear();
	m_vectConfigName.clear();
	bool bHaveAdd;                             //�Ƿ������//
	for (int k = 0; k < m_pDataProvider->m_vectFormula.size();k++)
	{
		if (nLineID==m_pDataProvider->m_vectFormula[k].m_ProductionLineId)         //����ü�¼�������������뵱ǰ������һ��//
		{
			bHaveAdd = false;
			for (int m = 0; m < m_vectConfigID.size();m++)                         //�жϸü�¼���䷽�Ƿ��ѱ����//
			{
				if (m_pDataProvider->m_vectFormula[k].m_FormulaId==m_vectConfigID[m])       //����䷽ID�Ѿ���ӹ���//
			    {
					bHaveAdd = true;
					break;
			    }
			}
			if (!bHaveAdd)         //���δ���//
			{
				m_vectConfigID.push_back(m_pDataProvider->m_vectFormula[k].m_FormulaId);
				m_vectConfigName.push_back(m_pDataProvider->m_vectFormula[k].m_strFormulaName);
			}
		}
	}
}

//��дlist1�ĵ�nItem+1��//
void COldConfigGraChiDlg::WriteToList1(int nLineID, CString strLineName, int nItem)
{
	CString strItem;
	strItem.Format(_T("%d"), nItem + 1);
	m_listAllConfig.InsertItem(nItem, _T(""));
	m_listAllConfig.SetItemText(nItem, 1, strItem);
	m_listAllConfig.SetItemText(nItem, 2, strLineName);
	bool bHaveFindDefault = false;         //���������Ƿ��趨��Ĭ���䷽//
	bool bHaveFindCurrent = false;         //���������Ƿ�����ʹ��ĳ�䷽//
	for (int n = 0; n<m_pDataProvider->m_vectFormula.size(); n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_ProductionLineId == nLineID && m_pDataProvider->m_vectFormula[n].m_IsCurrentFormula != 0)
		{
			m_listAllConfig.SetItemText(nItem, 3, m_pDataProvider->m_vectFormula[n].m_strFormulaName);
			bHaveFindCurrent = true;
			break;
		}
	}
	if (!bHaveFindCurrent)                //�����δָ��ʹ�õ��䷽//
		m_listAllConfig.SetItemText(nItem, 3, _T("δָ��"));
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size();n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_ProductionLineId == nLineID && m_pDataProvider->m_vectFormula[n].m_IsDefaultFormula!=0)
		{
			m_listAllConfig.SetItemText(nItem, 4, m_pDataProvider->m_vectFormula[n].m_strFormulaName);
			bHaveFindDefault = true;
			break;
		}
	}
	if (!bHaveFindDefault)            //�����δָ��Ĭ���䷽//
		m_listAllConfig.SetItemText(nItem, 4, _T("δָ��"));
}

//���οؼ�ѡ����Ŀ�����ı�ʱ//
void COldConfigGraChiDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	HTREEITEM hCurSelItem = m_treeConfig.GetSelectedItem();
	UINT TempID = m_treeConfig.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeConfig.GetParentItem(hCurSelItem);
	bool bHaveWriteLineName=false;         //�Ƿ��Ѿ���д�����������ơ���ע���䷽����//
	m_listConfigPara.DeleteAllItems();     //����䷽�����б�//
	m_vectConfigPara.clear();              //�������//
	CString strItem;
	if (hCurSelItem==NULL)                             //���ѡ�е��������߽ڵ�//
	{
		m_edConfigLine.SetWindowText(_T(""));
		m_edConfigName.SetWindowText(_T(""));
		m_edNote.SetWindowText(_T(""));
		m_strOldName = _T("");
		m_strOldNote = _T("");
	}
	else                        //���ѡ�е����䷽�ڵ�//
	{
		for (int n = 0; n < m_pDataProvider->m_vectFormula.size();n++)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId==TempID && !bHaveWriteLineName)  //��д�䷽���ơ�ʹ�������ߡ���ע//
			{
				m_edNote.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strNote);
				m_strOldNote = m_pDataProvider->m_vectFormula[n].m_strNote;
				m_edConfigName.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strFormulaName);
				m_strOldName = m_pDataProvider->m_vectFormula[n].m_strFormulaName;
				m_edConfigLine.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strProductionLineName);
				bHaveWriteLineName = true;
			}
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == TempID)   //�����䷽�����в���д��m_vectConfigPara//
				m_vectConfigPara.push_back(m_pDataProvider->m_vectFormula[n]);
		}
		for (int n = 0; n < m_vectConfigPara.size();n++)                //��дlist2//
		{
			m_listConfigPara.InsertItem(n, _T(""));
			strItem.Format(_T("%d"), n + 1);
			m_listConfigPara.SetItemText(n, 1, strItem);
			m_listConfigPara.SetItemText(n, 2, m_vectConfigPara[n].m_strProcessParaName);
			strItem.Format(_T("%.2f"), m_vectConfigPara[n].m_DefaultValue);
			m_listConfigPara.SetItemText(n, 3, strItem);
			m_listConfigPara.SetItemText(n, 4, m_vectConfigPara[n].m_strParaValueUnit);
		}
	}
}

//�һ�list2//
void COldConfigGraChiDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem == -1)
		return;
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_MENU_OLDCONFIG);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;          //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);  //�õ���괦//
	UINT nResult = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	CString strItem;
	switch (nResult)
	{
	case ID_ALLSEL:
		for (int n = 0; n < m_listConfigPara.GetItemCount();n++)
			m_listConfigPara.SetCheck(n);
		break;
	case ID_KILLSEL:
		for (int n = 0; n < m_listConfigPara.GetItemCount(); n++)
			m_listConfigPara.SetCheck(n,0);
		break;
	case ID_DELETEPARA:
		for (int n = m_vectConfigPara.size() - 1; n >= 0;n--)   //���������ѡ������������б���ȥ��//
		{
			if (m_listConfigPara.GetCheck(n))
			{
				m_vectConfigPara.erase(m_vectConfigPara.begin() + n);
				m_listConfigPara.DeleteItem(n);
				m_bIsDelePara = true;
			}
		}
		if (m_bIsDelePara)
		    for (int n = 0; n < m_listConfigPara.GetItemCount();n++)  //�����б������ʾ�����//
		    {
			    strItem.Format(_T("%d"), n + 1);
			    m_listConfigPara.SetItemText(n, 1, strItem);
		     }
		break;
	case ID_ADDPARA:              //����²������䷽//
		AddParaToConfig();
		break;
	default:
		break;
	}
	*pResult = 0;
}

//������ѡ����������仯//
void COldConfigGraChiDlg::OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//�ж��䷽���ƺͱ�ע�Ƿ����仯//
	CString strCurName, strCurNote;
	m_edConfigName.GetWindowText(strCurName);
	m_edNote.GetWindowText(strCurNote);
	strCurName = strCurName.Trim();
	strCurNote = strCurNote.Trim();
	if (strCurName != m_strOldName && m_strOldName != _T(""))
		m_bIsNameChange = true;
	else
		m_bIsNameChange = false;
	if (strCurNote != m_strOldNote && m_strOldName != _T(""))
		m_bIsNoteChange = true;
	else
		m_bIsNoteChange = false;

	int nResult;
	if (m_bIsAddPara||m_bIsDelePara||m_bIsNameChange||m_bIsNoteChange||m_bIsParaValueChange)  //�����δ������޸��򵯳�����//
	{
		nResult = MessageBox(_T("�䷽��Ϣ�ѱ��޸ģ��Ƿ񱣴棿"), _T("��ʾ"), MB_YESNO | MB_ICONEXCLAMATION);
		if (nResult==IDYES)
			saveChange();//�����޸�//
		m_bIsNameChange = false;                 //��ǰ�༭���ڵ��䷽�Ƿ����˸���//
		m_bIsParaValueChange = false;            //�Ƿ��޸����䷽������ֵ//
		m_bIsNoteChange = false;                 //�Ƿ��޸����䷽�ı�ע//
		m_bIsDelePara = false;                   //�Ƿ�ɾ�����䷽����//
		m_bIsAddPara = false;                    //�Ƿ�������䷽����//
	} 
}

//�����޸�,�����޸ı�־λ����Ϊ��//
void COldConfigGraChiDlg::saveChange()
{
	//�ж��Ƿ��иĶ�//
	if (!m_bIsAddPara && !m_bIsDelePara && !m_bIsNameChange && !m_bIsNoteChange && !m_bIsParaValueChange)
		return;
	
	//�ж����䷽�����Ƿ�Ϸ�//
	CString strNewName;
	m_edConfigName.GetWindowText(strNewName);
	strNewName = strNewName.Trim();
	if (strNewName.IsEmpty())
	{
		AfxMessageBox(_T("����ʧ�ܣ��䷽���Ʋ���Ϊ�գ�"));
		return;
	}
	if (m_bIsNameChange)
	{
		for (int q = 0; q < m_pDataProvider->m_vectFormula.size();q++)
		{
			if (m_pDataProvider->m_vectFormula[q].m_strFormulaName == strNewName)
			{
				AfxMessageBox(_T("����ʧ�ܣ��������ѱ�ʹ�á�"));
				return;
			}
		}
	}

	//�ж��䷽�Ƿ�Ϊ��//
	if (m_vectConfigPara.empty())
	{
		AfxMessageBox(_T("����ʧ�ܣ�����Ϊ�䷽��Ӳ�����"));
		return;
	}

	//�ж��䷽�����Ƿ񶼾����趨ֵ//
	for (int n = 0; n < m_vectConfigPara.size();n++)
	{
		if (m_vectConfigPara[n].m_DefaultValue==-3001)
		{
			AfxMessageBox(_T("����ʧ�ܣ���Ϊÿ���䷽�������Ԥ��ֵ��"));
			return;
		}
	}

	bool bIsBeDele;     //�ò����Ƿ�ɾ����//
	if (m_bIsDelePara)  //������䷽������ɾ����//
	{
		for (int n = m_pDataProvider->m_vectFormula.size() - 1; n >= 0;n--)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem()))
			{
				bIsBeDele = true;
				for (int i = 0; i < m_vectConfigPara.size(); i++)   //��ѯ�ò����Ƿ�ɾ����//
					if (m_pDataProvider->m_vectFormula[n].m_Id == m_vectConfigPara[i].m_Id)
					{
						bIsBeDele = false;
						break;
					}
				if (bIsBeDele)           //����ò����ѱ�ɾ�����������Դ���������ݿ�ɾ��//
				{
					m_pDataProvider->DeleteDbTableItem(CDataProvider::tbFormula, m_pDataProvider->m_vectFormula[n].m_Id);
					m_pDataProvider->m_vectFormula.erase(m_pDataProvider->m_vectFormula.begin() + n);
				}
			}
		}
		
	}

	if (m_bIsAddPara)   //��������˲���//
	{
		for (int n = 0; n < m_vectConfigPara.size();n++)
			if (m_vectConfigPara[n].m_Id==0)           //����ò��������䷽������//
				m_pDataProvider->AddFormulaToDatabase(m_vectConfigPara[n]);
		
	}

	if (m_bIsParaValueChange)    //����в�����ֵ���޸�//
	{
		for (int n = 0; n < m_vectConfigPara.size();n++)
		{
			for (int i = 0; i < m_pDataProvider->m_vectFormula.size();i++)
			{
				if (m_pDataProvider->m_vectFormula[i].m_FormulaId == m_vectConfigPara[n].m_FormulaId && m_vectConfigPara[n].m_ProcessParaId == m_pDataProvider->m_vectFormula[i].m_ProcessParaId)
				{
					m_pDataProvider->m_vectFormula[i].m_DefaultValue = m_vectConfigPara[n].m_DefaultValue;
					m_pDataProvider->UpdateTableItem(CDataProvider::tbFormula, m_pDataProvider->m_vectFormula[i].m_Id);
					break;
				}
			}
		}
		
	}

	if (m_vectConfigPara[0].m_IsCurrentFormula != 0 && (m_bIsDelePara || m_bIsAddPara || m_bIsParaValueChange))  //����ǵ�ǰʹ�õ��䷽�����������趨ֵ����������иĶ�//
	{
		m_pDataProvider->SetCurConfig(m_vectConfigPara[0].m_ProductionLineId, m_vectConfigPara[0].m_FormulaId);
		m_bIsCurConfigChange = true;
	}
	m_bIsDelePara = false;                   //�Ƿ�ɾ�����䷽������0//
	m_bIsParaValueChange = false;            //�Ƿ��޸����䷽������ֵ��0//
	m_bIsAddPara = false;                          //�Ƿ�������䷽��������0//


	if (m_bIsNameChange)        //����䷽���Ʊ��޸�//
	{
		for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem()))
			{
				m_pDataProvider->m_vectFormula[n].m_strFormulaName = strNewName;
				m_pDataProvider->UpdateTableItem(CDataProvider::tbFormula, m_pDataProvider->m_vectFormula[n].m_Id);
			}
		}
		m_treeConfig.SetItemText(m_treeConfig.GetSelectedItem(), strNewName);  //�޸�������//
		m_strOldName = strNewName;             
		m_bIsNameChange = false;                 //�䷽�����Ƿ��޸ģ���0//
	}

	CString strNewNote;
	if (m_bIsNoteChange)        //����䷽�ı�ע���޸�//
	{
		m_edNote.GetWindowText(strNewNote);         //��ȡ�µı�ע����//
		strNewNote = strNewNote.Trim();
		for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem()))
			{
				m_pDataProvider->m_vectFormula[n].m_strNote = strNewNote;
				m_pDataProvider->UpdateTableItem(CDataProvider::tbFormula, m_pDataProvider->m_vectFormula[n].m_Id);
			}
		}
		m_strOldNote = strNewNote;
		m_bIsNoteChange = false;                     //�Ƿ��޸����䷽�ı�ע����0//
	}
	AfxMessageBox(_T("����ɹ���"));
}

//��Ӳ������䷽//
void COldConfigGraChiDlg::AddParaToConfig()
{
	HTREEITEM hCurSelItem = m_treeConfig.GetSelectedItem();   //��õ�ǰ��������ѡ�нڵ�//
	UINT TempID = m_treeConfig.GetItemData(hCurSelItem);
	HTREEITEM hParentItem = m_treeConfig.GetParentItem(hCurSelItem);
	if (hParentItem == NULL)             //���������ѡ�е��������߽ڵ㣬��������//
		return;
	m_AddConfigParaPopDlg.m_vectNewPara.clear();              //��յ������������//
		
	UINT nLineID = m_treeConfig.GetItemData(hParentItem);                //ѡ���䷽���������ߵ�ID//

	//�����������¿ɽ����䷽��δ�����䷽�Ĳ���������������//
	bool bIsInConfig = false;
	for (int n = 0; n < m_pDataProvider->m_vectProModulePara.size(); n++)
	{
		if (m_pDataProvider->m_vectProModulePara[n].m_ProductionLineId == nLineID && m_pDataProvider->m_vectProModulePara[n].m_IsConfig)
		{
			bIsInConfig = false;
			for (int i = 0; i < m_vectConfigPara.size(); i++)
			{
				if (m_vectConfigPara[i].m_ProcessParaId == m_pDataProvider->m_vectProModulePara[n].m_Id)
				{
					bIsInConfig = true;
					break;
				}
			}
			if (!bIsInConfig)
				m_AddConfigParaPopDlg.m_vectNewPara.push_back(m_pDataProvider->m_vectProModulePara[n]);
		}
	}
	if (m_AddConfigParaPopDlg.m_vectNewPara.empty())
	{
		AfxMessageBox(_T("û�пɹ���ӵĲ�����"));
		return;
	}
	m_AddConfigParaPopDlg.DoModal();   //������Ӳ����Ľ���//

	if (m_pDataProvider->m_vectTempProModulePara.empty())   //���û������Ӳ������˳����������������򽫱�־λ��1//
		return;
	else
		m_bIsAddPara = true;
	
	CFormulaClass TempConfigPara;
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)    //����ǰ�䷽�Ļ�����Ϣ��ֵ�������Ĳ���//
	{
		if (m_pDataProvider->m_vectFormula[n].m_FormulaId==TempID)
		{
			TempConfigPara.m_IsCurrentFormula = m_pDataProvider->m_vectFormula[n].m_IsCurrentFormula;
			TempConfigPara.m_IsDefaultFormula = m_pDataProvider->m_vectFormula[n].m_IsDefaultFormula;
			TempConfigPara.m_strFormulaName = m_pDataProvider->m_vectFormula[n].m_strFormulaName;
			TempConfigPara.m_strNote = m_pDataProvider->m_vectFormula[n].m_strNote;
			TempConfigPara.m_ProductionLineId = m_pDataProvider->m_vectFormula[n].m_ProductionLineId;
			TempConfigPara.m_strProductionLineName = m_pDataProvider->m_vectFormula[n].m_strProductionLineName;
			TempConfigPara.m_DefaultValue = -3001;
			TempConfigPara.m_FormulaId = TempID;
			TempConfigPara.m_Id = 0;
			break;
		}
	}

	//����û��ڵ�����������˲���������Щ��������m_vectConfigPara,����ʾ//
	CString strItem1;
	int nItem;
	for (int m = 0; m < m_pDataProvider->m_vectTempProModulePara.size();m++)
	{
		//TempConfigPara.m_DefaultValue = m_pDataProvider->m_vectTempProModulePara[m].m_fSetValue;

		TempConfigPara.m_ProcessParaId = m_pDataProvider->m_vectTempProModulePara[m].m_Id;		
		TempConfigPara.m_strParaValueUnit = m_pDataProvider->m_vectTempProModulePara[m].m_strUnit;
		TempConfigPara.m_strProcessParaName = m_pDataProvider->m_vectTempProModulePara[m].m_strParaName;
		m_vectConfigPara.push_back(TempConfigPara);
		nItem = m_listConfigPara.GetItemCount();
		m_listConfigPara.InsertItem(nItem, _T(""));
		strItem1.Format(_T("%d"), nItem + 1);
		m_listConfigPara.SetItemText(nItem, 1, strItem1);
		m_listConfigPara.SetItemText(nItem, 2, TempConfigPara.m_strProcessParaName);
		m_listConfigPara.SetItemText(nItem, 3, _T(""));
		m_listConfigPara.SetItemText(nItem, 4, TempConfigPara.m_strParaValueUnit);
	}
	m_pDataProvider->m_vectTempProModulePara.clear();         //�������Դ�ڵ���ʱ����//
}


//��Ӳ�����ť//
void COldConfigGraChiDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AddParaToConfig();
}

//ɾ���䷽��ť//
void COldConfigGraChiDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	UINT TempID;
	if (m_strOldName!=_T(""))
	{
		TempID = m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem());
		for (int n = 0; n < m_pDataProvider->m_vectFormula.size();n++)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == TempID && m_pDataProvider->m_vectFormula[n].m_IsCurrentFormula)
			{
				AfxMessageBox(_T("���䷽����ʹ���У��޷�ɾ��������ͣ���䷽��"));
				return;
			}
		}
		int nResult = MessageBox(_T("�ò����޷��ָ����Ƿ������"), _T("����"), MB_YESNO | MB_ICONEXCLAMATION);
		if (nResult==IDYES)
		{
			m_pDataProvider->DeleteFormula(TempID);         //������Դ���������ݿ�ɾ�����䷽//
			ReInitDlg();//���»����������ڣ���ձ�־λ//		
		}
	}
}


void COldConfigGraChiDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	m_listConfigPara.SetFocus();
}

//�����б��2//
void COldConfigGraChiDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	if (pEditCtrl->iItem == -1 || pEditCtrl->iSubItem != 3)                                                //������ǹ�����//
	{
		if (m_bHaveEditCreate == true)                                            //���֮ǰ�����˱༭������ٵ�//
		{
			distroyEdit(&m_listConfigPara, &m_Edit, m_OldItem, m_OldSubItem);              //���ٵ�Ԫ��༭�����//
			m_bHaveEditCreate = false;
		}
	}
	else
	{
		if (m_bHaveEditCreate == true)
		{
			if (!(m_OldItem == pEditCtrl->iItem && m_OldSubItem == pEditCtrl->iSubItem))    //������еĵ�Ԫ����֮ǰ�����õ�//
			{
				distroyEdit(&m_listConfigPara, &m_Edit, m_OldItem, m_OldSubItem);
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
void COldConfigGraChiDlg::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
//pEditCtrlΪ�б����ָ�룬createditΪ�༭��ָ�����//
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼//
{
	Item = pEditCtrl->iItem;                     //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	SubItem = pEditCtrl->iSubItem;               //�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���//
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_CENTER | ES_WANTRETURN, CRect(0, 0, 0, 0), this, IDC_EDIT_CREATE1);  //�����༭�����,IDC_EDIT_CREATEΪ�ؼ�ID��//
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);                   //��������//
	createdit->SetParent(&m_listConfigPara);                      //��listcontrol����Ϊ������//
	CRect  EditRect;
	m_listConfigPara.GetSubItemRect(m_OldItem, 3, LVIR_LABEL, EditRect);      //��ȡ��Ԫ��Ŀռ�λ����Ϣ//
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listConfigPara.GetColumnWidth(3) - 1, EditRect.bottom - 1);//+1��-1�ñ༭�����ڵ�ס�б���е�������//
	CString strTemp;
	strTemp = m_listConfigPara.GetItemText(m_OldItem, 3);
	createdit->SetWindowText(strTemp);
	createdit->MoveWindow(&EditRect);                                      //���༭��λ�÷�����Ӧ��Ԫ����//
	createdit->ShowWindow(SW_SHOW);                                        //��ʾ�༭���ڵ�Ԫ������//
	createdit->SetFocus();                                                 //����Ϊ����//
	createdit->SetSel(-1);                                                 //���ù�����ı������ֵ����//
}

//���ٱ༭��//
void COldConfigGraChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString strEditData;
	distroyedit->GetWindowText(strEditData);
	strEditData = strEditData.Trim();

	if (strEditData.IsEmpty())             //�������Ϊ�գ������ٱ༭��//
	{
		distroyedit->DestroyWindow();
		if (m_vectConfigPara[Item].m_DefaultValue!=-3001)
		{
			m_vectConfigPara[Item].m_DefaultValue = -3001;
			m_bIsParaValueChange = true;
		}
		list->SetItemText(Item, 3, _T(""));
		return;
	}
	if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
	{
		float tempfloat = (float)_wtof(strEditData);
		strEditData.Format(_T("%.2f"), tempfloat);
		list->SetItemText(Item, 3, strEditData);                 //���޸�д���б��//
		if (tempfloat != m_vectConfigPara[Item].m_DefaultValue)  //�ж�ֵ�Ƿ����˱仯//
		{
			m_vectConfigPara[Item].m_DefaultValue = tempfloat;    //���޸ĺ��ֵ��������//
			m_bIsParaValueChange = true;
		}
		
	}
	else
		AfxMessageBox(_T("�Ƿ����������������֣�"));
	distroyedit->DestroyWindow();                          //���ٶ���//
}

//�༭��ʧȥ����//
void COldConfigGraChiDlg::OnEnKillfocusEditCreate1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bHaveEditCreate == true)                                               //���֮ǰ�����˱༭������ٵ�//
	{
		distroyEdit(&m_listConfigPara, &m_Edit, m_OldItem, m_OldSubItem);                 //���ٵ�Ԫ��༭�����//
		m_bHaveEditCreate = false;
	}
}


void COldConfigGraChiDlg::ReInitDlg()   //���³�ʼ������//
{
	//���»����������ڣ���ձ�־λ//
	//�޸ı�־λ��0//
	m_bIsNameChange = false;                 //��ǰ�༭���ڵ��䷽�Ƿ����˸���//
	m_bIsParaValueChange = false;            //�Ƿ��޸����䷽������ֵ//
	m_bIsNoteChange = false;                 //�Ƿ��޸����䷽�ı�ע//
	m_bIsDelePara = false;                   //�Ƿ�ɾ�����䷽����//
	m_bIsAddPara = false;                    //�Ƿ�������䷽����//
	m_strOldName = _T("");
	m_strOldNote = _T("");
	m_edConfigLine.SetWindowText(_T(""));
	m_edNote.SetWindowText(_T(""));
	m_edConfigName.SetWindowText(_T(""));
	m_vectConfigPara.clear();
	m_listConfigPara.DeleteAllItems();

	InitTreeContrl();                               //������д��������//
	m_listAllConfig.DeleteAllItems();
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)          //������д�б��1//
		WriteToList1(m_pDataProvider->m_vectProductionLine[n].m_Id, m_pDataProvider->m_vectProductionLine[n].m_strLineName, n);
}

//�����޸İ�ť//
void COldConfigGraChiDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//�ж��䷽���ƺͱ�ע�Ƿ����仯//
	CString strCurName, strCurNote;
	m_edConfigName.GetWindowText(strCurName);
	m_edNote.GetWindowText(strCurNote);
	strCurName = strCurName.Trim();
	strCurNote = strCurNote.Trim();
	if (strCurName != m_strOldName && m_strOldName != _T(""))
		m_bIsNameChange = true;
	else
		m_bIsNameChange = false;
	if (strCurNote != m_strOldNote && m_strOldName != _T(""))
		m_bIsNoteChange = true;
	else
		m_bIsNoteChange = false;
	//����//
	saveChange();
}

//���Ʊ༭��ʧȥ����//
void COldConfigGraChiDlg::OnEnKillfocusEdit4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strCurName;
	m_edConfigName.GetWindowText(strCurName);
	strCurName = strCurName.Trim();
	if (strCurName.IsEmpty()&&!m_strOldName.IsEmpty())
	{
		AfxMessageBox(_T("���棡�䷽���Ʋ���Ϊ�գ�"));
	}
}

//�������İ�ť//
void COldConfigGraChiDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ж��䷽���ƺͱ�ע�Ƿ����仯//
	CString strCurName, strCurNote;
	m_edConfigName.GetWindowText(strCurName);
	m_edNote.GetWindowText(strCurNote);
	strCurName = strCurName.Trim();
	strCurNote = strCurNote.Trim();
	if (strCurName != m_strOldName && m_strOldName != _T(""))
		m_bIsNameChange = true;
	else
		m_bIsNameChange = false;
	if (strCurNote != m_strOldNote && m_strOldName != _T(""))
		m_bIsNoteChange = true;
	else
		m_bIsNoteChange = false;

	//�ж��Ƿ��иĶ�//
	if (!m_bIsAddPara && !m_bIsDelePara && !m_bIsNameChange && !m_bIsNoteChange && !m_bIsParaValueChange)
		return;

	//������д�༭��//
	m_listConfigPara.DeleteAllItems();
	m_vectConfigPara.clear();
	HTREEITEM hCurSelItem = m_treeConfig.GetSelectedItem();
	UINT TempID = m_treeConfig.GetItemData(hCurSelItem);     //�õ���ǰѡ���䷽��ID//
	bool bHaveWriteLineName = false;         //�Ƿ��Ѿ���д�����������ơ���ע���䷽����//
	CString strItem;
	if (m_treeConfig.GetParentItem(hCurSelItem)==NULL)                             //���ѡ�е��������߽ڵ�//
	{
		m_edConfigLine.SetWindowText(_T(""));
		m_edConfigName.SetWindowText(_T(""));
		m_edNote.SetWindowText(_T(""));
		m_strOldName = _T("");
		m_strOldNote = _T("");
	}
	else                        //���ѡ�е����䷽�ڵ�//
	{
		for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)
		{
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == TempID && !bHaveWriteLineName)  //��д�䷽���ơ�ʹ�������ߡ���ע//
			{
				m_edNote.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strNote);
				m_strOldNote = m_pDataProvider->m_vectFormula[n].m_strNote;
				m_edConfigName.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strFormulaName);
				m_strOldName = m_pDataProvider->m_vectFormula[n].m_strFormulaName;
				m_edConfigLine.SetWindowText(m_pDataProvider->m_vectFormula[n].m_strProductionLineName);
				bHaveWriteLineName = true;
			}
			if (m_pDataProvider->m_vectFormula[n].m_FormulaId == TempID)   //�����䷽�����в���д��m_vectConfigPara//
				m_vectConfigPara.push_back(m_pDataProvider->m_vectFormula[n]);
		}
		for (int n = 0; n < m_vectConfigPara.size(); n++)                //��дlist2//
		{
			m_listConfigPara.InsertItem(n, _T(""));
			strItem.Format(_T("%d"), n + 1);
			m_listConfigPara.SetItemText(n, 1, strItem);
			m_listConfigPara.SetItemText(n, 2, m_vectConfigPara[n].m_strProcessParaName);
			strItem.Format(_T("%.2f"), m_vectConfigPara[n].m_DefaultValue);
			m_listConfigPara.SetItemText(n, 3, strItem);
			m_listConfigPara.SetItemText(n, 4, m_vectConfigPara[n].m_strParaValueUnit);
		}
	}
	m_bIsNameChange = false;                 //��ǰ�༭���ڵ��䷽�Ƿ����˸���//
	m_bIsParaValueChange = false;            //�Ƿ��޸����䷽������ֵ//
	m_bIsNoteChange = false;                 //�Ƿ��޸����䷽�ı�ע//
	m_bIsDelePara = false;                   //�Ƿ�ɾ�����䷽����//
	m_bIsAddPara = false;                    //�Ƿ�������䷽����//
}

//ʹ���䷽��ť//
void COldConfigGraChiDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ж��䷽���ƺͱ�ע�Ƿ����仯//
	CString strCurName, strCurNote;
	m_edConfigName.GetWindowText(strCurName);
	m_edNote.GetWindowText(strCurNote);
	strCurName = strCurName.Trim();
	strCurNote = strCurNote.Trim();
	if (strCurName != m_strOldName && m_strOldName != _T(""))
		m_bIsNameChange = true;
	else
		m_bIsNameChange = false;
	if (strCurNote != m_strOldNote && m_strOldName != _T(""))
		m_bIsNoteChange = true;
	else
		m_bIsNoteChange = false;

	if (m_bIsAddPara || m_bIsDelePara || m_bIsNameChange || m_bIsNoteChange || m_bIsParaValueChange) //����䷽���޸�����δ���棬���ֹ����//
	{
		AfxMessageBox(_T("���ȱ����޸ģ�"));
		return;
	}
	int nIDofCurConfig;   //��ǰ������ѡ���䷽��ID//
	int nIDofLine;        //��ǰѡ���䷽���������ߵ�ID//
	nIDofCurConfig = m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem());
	if (m_treeConfig.GetParentItem(m_treeConfig.GetSelectedItem()) == NULL)  //���ѡ�е��������߽ڵ㣬��������//
		return;
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size();n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_FormulaId==nIDofCurConfig)
		{
			nIDofLine = m_pDataProvider->m_vectFormula[n].m_ProductionLineId;
			break;
		}
	}
	m_pDataProvider->SetCurConfig(nIDofLine, nIDofCurConfig);
	m_listAllConfig.DeleteAllItems();    //������д�б��1//
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)          
		WriteToList1(m_pDataProvider->m_vectProductionLine[n].m_Id, m_pDataProvider->m_vectProductionLine[n].m_strLineName, n);
	m_bIsCurConfigChange = true;  //����ʹ�õ��䷽�����˱仯//
	AfxMessageBox(_T("ʹ���䷽�ɹ���"));
}

//��ΪĬ���䷽��ť//
void COldConfigGraChiDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ж��䷽���ƺͱ�ע�Ƿ����仯//
	CString strCurName, strCurNote;
	m_edConfigName.GetWindowText(strCurName);
	m_edNote.GetWindowText(strCurNote);
	strCurName = strCurName.Trim();
	strCurNote = strCurNote.Trim();
	if (strCurName != m_strOldName && m_strOldName != _T(""))
		m_bIsNameChange = true;
	else
		m_bIsNameChange = false;
	if (strCurNote != m_strOldNote && m_strOldName != _T(""))
		m_bIsNoteChange = true;
	else
		m_bIsNoteChange = false;

	if (m_bIsAddPara || m_bIsDelePara || m_bIsNameChange || m_bIsNoteChange || m_bIsParaValueChange) //����䷽���޸�����δ���棬���ֹ����//
	{
		AfxMessageBox(_T("���ȱ����޸ģ�"));
		return;
	}
	int nIDofCurConfig;   //��ǰ������ѡ���䷽��ID//
	int nIDofLine;        //��ǰѡ���䷽���������ߵ�ID//
	nIDofCurConfig = m_treeConfig.GetItemData(m_treeConfig.GetSelectedItem());
	if (m_treeConfig.GetParentItem(m_treeConfig.GetSelectedItem()) == NULL)  //���ѡ�е��������߽ڵ㣬��������//
		return;
	for (int n = 0; n < m_pDataProvider->m_vectFormula.size(); n++)
	{
		if (m_pDataProvider->m_vectFormula[n].m_FormulaId == nIDofCurConfig)
		{
			nIDofLine = m_pDataProvider->m_vectFormula[n].m_ProductionLineId;
			break;
		}
	}
	m_pDataProvider->SetDefaultConfig(nIDofLine, nIDofCurConfig);
	m_listAllConfig.DeleteAllItems();    //������д�б��1//
	for (int n = 0; n < m_pDataProvider->m_vectProductionLine.size(); n++)
		WriteToList1(m_pDataProvider->m_vectProductionLine[n].m_Id, m_pDataProvider->m_vectProductionLine[n].m_strLineName, n);
	AfxMessageBox(_T("����Ĭ���䷽�ɹ���"));
}
