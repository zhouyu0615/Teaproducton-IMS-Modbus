#pragma once

#define WM_SOCKETCOMM_RECIEVECHAR       WM_USER+1 //窗口消息，表示接收到字符串并存储在输入缓冲区内
#define FCT_READ_COILS		        0x01	// 读线圈
#define FCT_READ_HOLD_REG	        0x03	// 读保持寄存器 
#define FCT_WRITE_SINGLE_COILS      0x05	// 写线圈 
#define FCT_WRITE_SINGLE_HOLD_REG   0x06	// 写单个寄存器 
#define FCT_WRITE_MULTIPLE_REG	    0x10	// 写多个寄存器

#define RECEIVE_BUFF_SIZE  500

#include <winsock.h>
#include "DataProvider.h"
#include "ReadDataPacket.h"
#include "Thread.h"
#include "vector"
#include "PlcClass.h"


class CTCPClient:Runnable
{
public:
	CTCPClient();
	virtual ~CTCPClient();
public:
	CString m_strRemoteHost;             //远程访问IP地址
	int m_nPort;                         //远程访问端口，modbus固定访问端口：502
	bool m_bIsconnected;                 //Socket连接状态
	bool m_bIsopen;                      //Socket打开状态
	CDataProvider *m_pDataP;             //指向全局数据存储类

private:
	SOCKET m_Socket;                     //通讯Socket句柄
	//HANDLE m_hExitThreadEvent;           //退出通讯线程事件的句柄
	CWinThread* m_WndTCPThread;          //通讯线程句柄
	HANDLE m_hTCPThreadHandle;
	CWnd* m_pWndOwner;                   //父窗口句柄

public:
	bool Open();                         //打开Socket以及启动通讯事件线程，接收Socket消息
	bool Connect();                      //连接Socket
	bool Close();                        //关闭Socket
	bool SendData();    //发送数据

	void SetSendBuff(char *pcSendBuf, int nLen);
	char *m_pcSendBuf;
	int   m_nSendBufLen;

	/*保护m_vRecvBuff的临界区变量*/
	CRITICAL_SECTION m_RBCS;
	std::vector<BYTE> m_vRecvBuff;
	void DealRecvData(char* pcRcvData);

	/**
	运行的线程函数，可以使用派生类重写此函数
	**/

	void CreatePollThread();
	void StartPollThread();
	void ResumePollThread();
	void SuspendPollThread();
	virtual void Run(); 
	CThread *m_pThread;

private:
	static UINT SocketThreadFunc(LPVOID lparam); //通讯线程运行函数
	void ProcessMessage(int nMessageIndex, char* pcIP, char* pcSendData, CWnd* pTCPOwner);   //向指定窗口发送接收到的消息
	void SetReadDataPacket(CString strIP, char* pcRcvData);
	int GetPlcClassIndex();            //获取当前PLC在公共数据容器中的位置索引


};

