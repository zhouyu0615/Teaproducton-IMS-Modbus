#pragma once
#include "TCPClient.h"
#include <vector>
#include "PlcClass.h"
#include "Thread.h"

using namespace std;
#define FCT_READ_COILS		        0x01	// 读线圈
#define FCT_READ_HOLD_REG	        0x03	// 读保持寄存器 
#define FCT_WRITE_SINGLE_COILS      0x05	// 写线圈 
#define FCT_WRITE_SINGLE_HOLD_REG   0x06	// 写单个寄存器 
#define FCT_WRITE_MULTIPLE_REG	    0x10	// 写多个寄存器

class CModbus:CThread,CWnd
{
public:
	CModbus();
	virtual ~CModbus();

public:
	vector<CTCPClient> m_vMultipleTCPClient;    //TCP客户端连接类容器，封装一连串TCP客户端对象
	vector<CPlcClass> m_vPlcClass;              //PLC类容器
	int m_nCountTCPClient;                //TCP客户端连接数量	
	bool m_bIsCycling;                   //轮询启动标记
	CDataProvider *m_pDataP;             //指向全局数据存储类

	
private:
	//HANDLE m_hExitThreadCycle;           //退出轮询线程句柄
	CWinThread* m_WndCycleThread;        //轮询线程句柄
	int m_nIndex;                        //轮询索引
	int m_nWriteIndex;                   //写功能轮询索引，当写功能标识为TRUE，每写完成一个PLC，则+1，当其大于等m_nCountTCPClient时，写功能标识为FALSE，清零
	bool m_bModbusRead;                  //写功能标识
	bool m_bModbusWrite;                 //读功能标识
	CTCPClient* m_pTCPClient;    //用于动态创建TCPClient对象，push_back()进入Vector容器
	BYTE* m_pbyReadHeader;       //指向生成的读功能数据帧

public:
	void CycleStart();     //根据数据库读取的PLC类容器，添加TCPClient容器，启动轮询线程     
	void CycleDisconnect();               //断开轮询状态，并不断开与PLC的连接状态
	bool CycleReadHoldingReg(CPlcClass plcClass,int nPlcIndex);       //轮询读寄存器操作
	BYTE* CreateReadHeader(CPlcClass plcClass, int nPlcIndex);        //创建读功能数据帧
	//bool WriteHoldingReg(CDataWritePacket DataWritePacket);         //写寄存器操作
	bool SendData(int nIndex, BYTE* pbySendbuf, int nLen);          //向指定的IP地址发送功能数据帧
	int GetResponseData(WPARAM wparam, LPARAM lparam);  //获取由窗口提供的，指定了IP地址的，由TCPCLient接收到的数据，并进行解析，反馈

	void DispatchReadData();
	BOOL  VerifyRecvData(int Index);
	int GetPlcClassIndex(CString strIpAddr);            //获取当前PLC在公共数据容器中的位置索引


	CThread *m_DispatchThread;
	virtual void Run(); //数据分发线程的运行函数//


private:
	static UINT CycleThreadFunc(LPVOID lparam);               //轮询线程
};

