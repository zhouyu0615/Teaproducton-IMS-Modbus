#pragma once
#include "afxcmn.h"
#include "DataProvider.h"
#include "afxwin.h"
#include <vector>
#include "DevicePara.h"
#include "ProcessModulePara.h"
#include "VideoClass.h"
#include "realplayxctrl1.h"
#include "DeviceContrlPopDlg.h"

// CDeviceChiDlg �Ի���

class CDeviceChiDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceChiDlg)

public:
	CDeviceChiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceChiDlg();

// �Ի�������
	enum { IDD = IDD_DEVICE_CHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT m_OldSize;                                    //�����С�����仯ǰ�ĳߴ�//
	void ReSize();                                      //ʹ�ؼ�����Ӧ�Ի����С�ı仯//
	virtual BOOL OnInitDialog();
	CTreeCtrl m_treeDevice;                             //���οؼ�//
	CDataProvider *m_pDataProvider = CDataProvider::getInstance(); //����Դ//
	void InitTreeContrl();                              //��ʼ�����οؼ�//
	afx_msg void OnTvnSelchangedTreeDeviceChidlg(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listModulePara;
	CListCtrl m_listDevicePara;
	UINT m_nCurSelModuleId;                             //��ǰѡ�й���ģ���ID//

	CStatic m_textCurPosition;                          //��ʾ��ǰλ�õľ�̬�ı���//
	std::vector<CDevicePara> m_vectTempDevicePara;      //�ݴ浱ǰѡ��ģ�������е��豸����//
	std::vector<CProcessPara> m_vectTempModulePara;     //�ݴ浱ǰѡ��ģ���µ����й��ղ���//
	std::vector<CVideoClass> m_vectTempVideo;           //�ݴ浱ǰѡ��ģ��������������ͷ//
	void SearchFromDataProvider(UINT nCerSelModuleId);  //����ǰѡ��ģ����µ�����ͷ�����ղ������豸�����ֱ�洢����ʱ����//
	CRealplayxctrl1 m_video;
	void WriteToModuleList();                           //��д���ղ����б��//
	void WriteToDeviceList();                           //��д�豸�����б��//
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_brush;                                    //��ˢ//
	afx_msg void OnNMDblclkLi2Devicepara(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nDClkLineItem;                               //�û����豸�����б����˫���е��б�//
	CImageList m_imageList;  //ͼ������//

	int m_OldItem;    //�ձ༭����//  
	int m_OldSubItem; //�ձ༭����//  
	CEdit m_Edit;     //���ɵ�Ԫ�༭�����//
	bool m_bHaveEditCreate;//��־�༭���Ѿ�������//
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);//������Ԫ��༭����//
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);//���ٵ�Ԫ��༭�����//

	afx_msg void OnNMDblclkLi1Modulepara(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	afx_msg void OnEnKillfocusEditCreateid();                     //�༭��ʧȥ����//
	void RePaintModuleList();                   //�ػ����ղ����б�//
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void UpdateParaValue();
	void UpdateParaValueShow();
};
