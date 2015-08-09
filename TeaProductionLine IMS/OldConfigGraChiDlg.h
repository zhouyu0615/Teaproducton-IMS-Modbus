#pragma once
#include "DataProvider.h"
#include "NewConfigGraChiDlg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "FormulaClass.h"
#include "AddConfigParaPopDlg.h"

// COldConfigGraChiDlg �Ի���

class COldConfigGraChiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COldConfigGraChiDlg)

public:
	COldConfigGraChiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COldConfigGraChiDlg();

// �Ի�������
	enum { IDD = IDD_OLDCONFIG_GRACHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listAllConfig;     //�ؼ�����//
	CListCtrl m_listConfigPara;
	CTreeCtrl m_treeConfig;
	CEdit m_edConfigName;
	CEdit m_edConfigLine;
	CEdit m_edNote;

	CDataProvider *m_pDataProvider = CDataProvider::getInstance();    //����Դ//
	std::vector<int> m_vectConfigID;
	std::vector<CString> m_vectConfigName;

	void InitTreeContrl();                                  //��ʼ����������//
	void searchConfigFromLine(int nLineID);                 //���������ߵ�ID�ҵ����µ��䷽,�����䷽���ƺ�ID�浽SET����//
	void WriteToList1(int nLineID,CString strLineName,int nItem);    //��дlist�ĵ�nItem+1��//

	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

	bool m_bIsNameChange;                 //��ǰ�༭���ڵ��䷽�Ƿ����˸���//
	bool m_bIsParaValueChange;            //�Ƿ��޸����䷽������ֵ//
	bool m_bIsNoteChange;                 //�Ƿ��޸����䷽�ı�ע//
	bool m_bIsDelePara;                   //�Ƿ�ɾ�����䷽����//
	bool m_bIsAddPara;                    //�Ƿ�������䷽����//
	CString m_strOldName;                  //�޸�֮ǰ���䷽��//
	CString m_strOldNote;                 //�޸�֮ǰ�ı�ע//
	std::vector<CFormulaClass> m_vectConfigPara;    //��˳��洢list2�ڵ��䷽����//

	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void saveChange();          //�����޸�//
	void AddParaToConfig();     //��Ӳ������䷽//
	CAddConfigParaPopDlg m_AddConfigParaPopDlg;   // ����䷽�����Ľ���//
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton2();

	//list2�༭���������������������//
	int m_OldItem;           //�ձ༭����//  
	int m_OldSubItem;        //�ձ༭����//  
	CEdit m_Edit;            //���ɵ�Ԫ�༭�����//
	bool m_bHaveEditCreate;  //��־�༭���Ѿ�������//
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat); //������Ԫ��༭����//
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);                       //���ٵ�Ԫ��༭�����//
	virtual void OnOK();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditCreate1();
	void ReInitDlg();                  //���³�ʼ������//
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton3();
	bool m_bIsCurConfigChange;         //��ǰʹ���䷽�Ƿ����仯//
	afx_msg void OnBnClickedButton4();
};
