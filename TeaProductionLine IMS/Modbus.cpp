#include "stdafx.h"
#include "Modbus.h"


CModbus::CModbus()
{
	//初始化运行环境
	//创建退出轮询线程事件句柄,初始状态为无信号，自动复原（即不需要ReestEvent函数来手工复原信号量）
	//m_hExitThreadCycle = CreateEvent(NULL, FALSE, FALSE, NULL);
	//初始化全局数据类
	m_pDataP = CDataProvider::getInstance();

	m_WndCycleThread = NULL;

	m_DispatchThread = NULL;
}


CModbus::~CModbus()
{
	//关闭退出轮询线程事件句柄

	CloseHandle(m_WndCycleThread);
	//CloseHandle(m_hExitThreadCycle);
	delete(m_DispatchThread);
}



//====================================================================================================//
//功能：根据数据库中读取的PLC信息，创建CTCPClient容器，启动modbus轮询线程，实时读，并根据窗口需求写modbus数据      
//入口：vPlcClass:待连接的所有PLC的类，包括PLCIP地址，读取缓冲区大小等              
//出口：无
//返回：无
//====================================================================================================//
void CModbus::CycleStart()
{
	//根据PLC数量添加CTCPClient容器
	m_vMultipleTCPClient.clear();
	m_vPlcClass = m_pDataP->m_vectPlc;
	m_nCountTCPClient = m_vPlcClass.size();
	for (int i = 0; i < m_nCountTCPClient; i++)
	{
		m_pTCPClient = new CTCPClient;
		m_pTCPClient->m_strRemoteHost = m_vPlcClass[i].m_strIPAddr;
		m_vMultipleTCPClient.push_back(*m_pTCPClient);
	}

	//复位退出轮询线程事件	
	//	ResetEvent(m_hExitThreadCycle);

	//启动轮询线程

	m_WndCycleThread = AfxBeginThread(CycleThreadFunc, this, THREAD_PRIORITY_ABOVE_NORMAL);		

	
	if (!m_WndCycleThread)
	{
		//线程启动不成功
		m_bIsCycling = FALSE;
		m_bModbusRead = FALSE;
	}
	else
	{
		//线程启动成功，开始轮询
		m_bIsCycling = TRUE;
		m_bModbusRead = TRUE;
	}

	//启动数据分发线程


	m_DispatchThread = new CThread(this);
	m_DispatchThread->Start();

}

//====================================================================================================//
//功能：停止轮询线程，即停止对PLC的读和写，并断开PLC的连接
//入口：无         
//出口：无
//返回：无
//====================================================================================================//
void CModbus::CycleDisconnect()
{
	//发送轮询线程退出事件
	//SetEvent(m_hExitThreadCycle);
	m_WndCycleThread->SuspendThread();
	m_DispatchThread->Suspend();
	for (int i = 0; i < m_nCountTCPClient; i++)
	{
		if (m_vMultipleTCPClient[i].m_bIsconnected == TRUE)
		{
			m_vMultipleTCPClient[i].SuspendPollThread();
			m_vMultipleTCPClient[i].Close();
		}
	}
	m_bIsCycling = FALSE;
	m_bModbusRead = FALSE;
}

//====================================================================================================//
//功能：读保持寄存器功能
//入口：plcClass：CPlcClass类，存储读目标的IP，读取的起始地址以及寄存器数量，便于生成读取数据帧
//      nPlcIndex：标记当前PLC在PLC列表中的序列索引，便于定位
//出口：无
//返回：TRUE:数据读取成功；FALSE:数据读取失败
//====================================================================================================//
bool CModbus::CycleReadHoldingReg(CPlcClass plcClass, int nPlcIndex)
{
	BYTE* pbyReadHeader;
	pbyReadHeader = CreateReadHeader(plcClass, nPlcIndex);
	//读功能数据包长度固定，12个字节
	if (SendData(nPlcIndex, pbyReadHeader, 12) == TRUE)
	{
		//读数据功能代码发送成功
		return TRUE;
	}
	else
	{
		//读功能数据发送失败
		return FALSE;
	}
}

//====================================================================================================//
//功能：创建读功能数据帧
//入口：plcClass：CPlcClass类，存储读目标的IP，读取的起始地址以及寄存器数量，便于生成读取数据帧
//      nPlcIndex：标记当前PLC在PLC列表中的序列索引，便于定位
//出口：无
//返回：BYTE类型数组，用于返回组装好的数据帧地址
//====================================================================================================//
BYTE* CModbus::CreateReadHeader(CPlcClass plcClass, int nPlcIndex)
{
	m_pbyReadHeader = new BYTE[12];
	m_pbyReadHeader[0] = nPlcIndex >> 8;     //事务处理标识符，高低位，占两字节
	m_pbyReadHeader[1] = nPlcIndex;
	m_pbyReadHeader[2] = 0x00;               //协议标识符，高低位，占两字节，常量，为0x0000
	m_pbyReadHeader[3] = 0x00;
	m_pbyReadHeader[4] = 0x00;               //后续字节数据长度，高低位，占两字节，读功能数据包为常量：0x0006
	m_pbyReadHeader[5] = 0x06;
	m_pbyReadHeader[6] = 0xff;               //单元标识符，占一字节，采用TCP/IP时，通过IP地址寻址，忽略此标识符，常量：0xff
	m_pbyReadHeader[7] = FCT_READ_HOLD_REG;  //功能代码,占一字节，上述宏定义
	m_pbyReadHeader[8] = plcClass.m_ReadStartAddr >> 8;   //开始寄存器地址，高低位，占两字节
	m_pbyReadHeader[9] = plcClass.m_ReadStartAddr;
	m_pbyReadHeader[10] = plcClass.m_ReadLength >> 8;     //读取寄存器个数，高低位，占两字节
	m_pbyReadHeader[11] = plcClass.m_ReadLength;
	return m_pbyReadHeader;
}

//====================================================================================================//
//功能：向指定的PLC发送功能代码数据   
//入口：nIndex：目标PLC在本类中向量容器里面所存储的位置索引，由数据类方法实现并返回
//      pbySendbuf：要发送的功能代码数据帧，有数据类方法实现并返回
//      nLen：要发送的数据帧的长度，由数据类方法实现并返回
//出口：无
//返回：TRUE:数据读取成功；FALSE:数据读取失败
//====================================================================================================//
bool CModbus::SendData(int nIndex, BYTE* pbySendbuf, int nLen)
{
	m_vMultipleTCPClient[nIndex].SetSendBuff((CHAR*)pbySendbuf, nLen);
	return true;
}

//====================================================================================================//
//功能：由窗体声明的Modbus类对象在接到窗口消息时调用，解析Socket接收到的内容，根据功能封装成数据包返回
//入口：wparam：指向接收消息的Socket对应的IP地址值
//      lparam：消息指针，指向由Socket接收到的消息的存储地址
//出口：无
//返回：非0:数据解析成功并返回数据个数；0:数据解析失败或数据无意义
//====================================================================================================//
int CModbus::GetResponseData(WPARAM wparam, LPARAM lparam)
{
	int nSizeOfResponseReadData;   //读功能接收到的数据信息个数（16位信息字个数）
	UINT wTemp;
	BYTE* info = (BYTE*)lparam;    //获取数据信息
	if (info[7] == FCT_READ_HOLD_REG)
	{
		//如果解析的代码是读操作功能返回的代码//
		nSizeOfResponseReadData = info[8];
		if (nSizeOfResponseReadData % 2 != 0)
		{
			nSizeOfResponseReadData = nSizeOfResponseReadData + 1;
		}
		//m_vMultipleDataReadPacket[nIndex].m_vResponseReadData.clear();
		for (int i = 0; i < nSizeOfResponseReadData; i = i + 2)
		{
			wTemp = ((info[i + 9] & 0xff) << 8) | (info[i + 9 + 1]);
			//m_vMultipleDataReadPacket[nIndex].m_vResponseReadData.push_back(wTemp);
		}
		return nSizeOfResponseReadData / 2;
	}
	else
	{
		//不是读功能返回的代码//
		return 0;
	}
}

//==================================================================//
//功能：此线程用于轮询PLC，打开、连接、读取和写入数据
//入口：lparam:无类型指针，可以通过此参数，向线程中传入需要用到的资源
//      此处将CModbus类实例指针传入
//      nLen:待发送数据的长度
//出口：无
//返回：返回值无意义，返回0
//==================================================================//
UINT CModbus::CycleThreadFunc(LPVOID lparam)
{
	CModbus* pmd;
	pmd = (CModbus*)lparam;
	pmd->m_nIndex = 0;
	pmd->m_nWriteIndex = 0;
	//线程启动，打开定时器，周期性复位读写状态

	while (TRUE)
	{
		//收到退出事件，结束线程//
		//if (WaitForSingleObject(pmd->m_hExitThreadCycle, 0) == WAIT_OBJECT_0)
		//{
		//	break;
		//}

		if (pmd->m_vMultipleTCPClient.size() <= 0)
		{
			continue;
		}
	
		for (int i = 0; i < pmd->m_vMultipleTCPClient.size(); i++)
		{
			if (pmd->m_vMultipleTCPClient[i].m_bIsconnected == FALSE)
			{
				pmd->CycleReadHoldingReg(pmd->m_vPlcClass[i], i);
				//未连接状态，则连接//
				pmd->m_vMultipleTCPClient[i].Close();
				pmd->m_vMultipleTCPClient[i].Open();
				pmd->m_vMultipleTCPClient[i].Connect();
				if (pmd->m_vMultipleTCPClient[i].m_bIsconnected == TRUE)
				{
					if (pmd->m_vMultipleTCPClient[i].m_pThread==NULL)
					{
						pmd->m_vMultipleTCPClient[i].CreatePollThread();
						pmd->m_vMultipleTCPClient[i].StartPollThread();
					}
					else
					{
						pmd->m_vMultipleTCPClient[i].ResumePollThread();
					}
				}

			}
		}
		Sleep(200);
	}
	return 0;
}

//分发各个成功连接的TCP线程读取到的数据
void CModbus::DispatchReadData()
{
	int nSizeOfResponseReadData;   //字节个数//
	int lenth = m_vMultipleTCPClient.size();
	int sizeOfRecvBuff;
	int PlcIndex;
	int TcpIndex;
	for (TcpIndex = 0; TcpIndex < lenth; TcpIndex++)
	{	
		if (m_vMultipleTCPClient[TcpIndex].m_bIsconnected == FALSE)
		{
			continue;
		}
		EnterCriticalSection(&m_vMultipleTCPClient[TcpIndex].m_RBCS);
		sizeOfRecvBuff = m_vMultipleTCPClient[TcpIndex].m_vRecvBuff.size();
		if (m_vMultipleTCPClient[TcpIndex].m_bIsconnected&&sizeOfRecvBuff > 9) //当前客户端成功连接
		{
			if (m_vMultipleTCPClient[TcpIndex].m_vRecvBuff[7] == FCT_READ_HOLD_REG)
			{
				//如果解析的代码是读操作功能返回的代码//
				nSizeOfResponseReadData = m_vMultipleTCPClient[TcpIndex].m_vRecvBuff[8];
			}

			PlcIndex = GetPlcClassIndex(m_vMultipleTCPClient[TcpIndex].m_strRemoteHost);
		
			m_pDataP->m_vectPlc[PlcIndex].m_PlcReadMemory.clear();
			for (int i = 0; i < nSizeOfResponseReadData; i++)
			{
				m_pDataP->m_vectPlc[PlcIndex].m_PlcReadMemory.push_back(m_vMultipleTCPClient[TcpIndex].m_vRecvBuff[9 + i]);

			}
			m_pDataP->DispatchParaValue(PlcIndex);
		}
		LeaveCriticalSection(&m_vMultipleTCPClient[TcpIndex].m_RBCS);
	}
}

//检验数据的完整性
//index 为校验的数据在m_vMultipleTCPClient中的索引
//校验通过返回0，否则返回1
BOOL CModbus::VerifyRecvData(int Index)
{
	return 0;
}

int CModbus::GetPlcClassIndex(CString strIpAddr)
{
	int PlcIndex;
	for (PlcIndex = 0; PlcIndex < m_pDataP->m_vectPlc.size(); PlcIndex++)
	{
		if (strIpAddr == m_pDataP->m_vectPlc[PlcIndex].m_strIPAddr)
		{
			return PlcIndex;
		}
	}
	return 0;

}


void CModbus::Run()
{
	while (TRUE)
	{
		TRACE("数据分发线程正在分发");
		DispatchReadData();
		Sleep(100);
	}

}