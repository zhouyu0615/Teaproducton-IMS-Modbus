#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataProvider.h"
#include <vector>
#include "ProcessModulePara.h"
#include "ProcessModuleClass.h"
#include "FormulaClass.h"
// CNewConfigGraChiDlg �Ի���

class CNewConfigGraChiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewConfigGraChiDlg)

public:
	CNewConfigGraChiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewConfigGraChiDlg();

// �Ի�������
	enum { IDD = IDD_NEWCONFIG_GRACHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edNewConfigName;         //�䷽���Ʊ༭��//
	CComboBox m_cboxNewConfigLine;   //����������������//
	CEdit m_edNote;                  //��ע�༭��//
	CComboBox m_cboxModule;          //ģ��������//
	CListCtrl m_list1;               //��ѡ�����б��//
	CListCtrl m_list2;               //��ѡ�����б��//
	virtual BOOL OnInitDialog();
	CDataProvider *m_pDataProvider = CDataProvider::getInstance();       //����Դ//
	std::vector<CProcessPara>  m_vectList1;           //��ʾ���б��1������//
	std::vector<CProcessPara>  m_vectList2;           //�洢���䷽����������//
	std::vector<CProcessModuleClass>  m_vectCombo;    //����ģ����������ݴ�����//
	CFormulaClass m_TempFormula;                      //һ���䷽��¼//
	void searchModuleByLineID(int lineID);                      //���������ߵ�ID�ҵ��������е�ģ�飬���洢��m_vectCombo//
	void searchModuleParaByModuleID(int moduleID);              //����ģ��ID�ҵ��������й��ղ��������洢��m_vectList1//
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	int m_nLastSelLineItem;                          //��һ����ѡ������������������//
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();

	//list2�༭���������������������//
	int m_OldItem;           //�ձ༭����//  
	int m_OldSubItem;        //�ձ༭����//  
	CEdit m_Edit;            //���ɵ�Ԫ�༭�����//
	bool m_bHaveEditCreate;  //��־�༭���Ѿ�������//
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat); //������Ԫ��༭����//
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);                       //���ٵ�Ԫ��༭�����//
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditCreate();
	virtual void OnOK();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnKillfocusEdit1();
	static bool m_bIsAddConfig;  //�䷽�Ƿ����ı�//
};
