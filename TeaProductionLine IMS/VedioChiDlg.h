#pragma once
#include "realplayxctrl1.h"
#include "DataProvider.h"
#include <vector>

// CVedioChiDlg 对话框

class CVedioChiDlg : public CDialog
{
	DECLARE_DYNAMIC(CVedioChiDlg)

public:
	CVedioChiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVedioChiDlg();

// 对话框数据
	enum { IDD = IDD_VEDIO_CHIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);    //窗体大小发生变化时的响应函数//
	POINT m_OldSize;                                    //窗体大小发生变化前的尺寸//
	void ReSize();                                      //使控件自适应对话框大小的变化//
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedBtPlay();
	afx_msg void OnBnClickedBtStop();
	afx_msg void OnBnClickedButton3();
	int m_nPicStyle;              //画面风格标志，1单画面、4表示四画面，9表示九画面，16表示十六画面//
	int m_nNumOfPage;             //当需要多页面时，当前显示页面的页码//

	CRealplayxctrl1 m_vedio1;     //16个视频播放器//
	CRealplayxctrl1 m_vedio2;
	CRealplayxctrl1 m_vedio3;
	CRealplayxctrl1 m_vedio4;
	CRealplayxctrl1 m_vedio5;
	CRealplayxctrl1 m_vedio6;
	CRealplayxctrl1 m_vedio7;
	CRealplayxctrl1 m_vedio8;
	CRealplayxctrl1 m_vedio9;
	CRealplayxctrl1 m_vedio10;
	CRealplayxctrl1 m_vedio11;
	CRealplayxctrl1 m_vedio12;
	CRealplayxctrl1 m_vedio13;
	CRealplayxctrl1 m_vedio14;
	CRealplayxctrl1 m_vedio15;
	CRealplayxctrl1 m_vedio16;
	afx_msg void OnBnClickedBtSinglepic();
	afx_msg void OnBnClickedBtFourpic();
	afx_msg void OnBnClickedBtNinepic();
	afx_msg void OnBnClickedBt16pic();
	void ShowOneVedio(CRealplayxctrl1 &vedio);           //自定义函数，显示指定单个摄像头//
	void ShowFourVedio(CRealplayxctrl1 &vedio1, CRealplayxctrl1 &vedio2, CRealplayxctrl1 &vedio3, CRealplayxctrl1 &vedio4);//显示指定的四个摄像头//
	void ShowNineVedio(int nPage);     //九画面显示摄像头//
	CRealplayxctrl1 m_vedio17;
	CRealplayxctrl1 m_vedio18;
	CDataProvider *m_pDataProvider = CDataProvider::getInstance();    //数据源//
	void connectVedio();          //重新读取数据库，连接摄像头//
	bool m_bIsVedioPlay;          //摄像头是否已在播放标志符//
	int m_nNumOfVedio;            //摄像头个数//
	afx_msg void OnBnClickedBtNext();
	afx_msg void OnBnClickedBtLast();
	std::vector<CRealplayxctrl1*> m_vectVedio;//存储已添加摄像头的ActiveX控件//
	virtual void OnOK();
};
