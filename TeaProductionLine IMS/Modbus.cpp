#include "stdafx.h"
#include "Modbus.h"


CModbus::CModbus()
{
	//��ʼ�����л���
	//�����˳���ѯ�߳��¼����,��ʼ״̬Ϊ���źţ��Զ���ԭ��������ҪReestEvent�������ֹ���ԭ�ź�����
	//m_hExitThreadCycle = CreateEvent(NULL, FALSE, FALSE, NULL);
	//��ʼ��ȫ��������
	m_pDataP = CDataProvider::getInstance();

	m_WndCycleThread = NULL;

	m_DispatchThread = NULL;
}


CModbus::~CModbus()
{
	//�ر��˳���ѯ�߳��¼����

	CloseHandle(m_WndCycleThread);
	//CloseHandle(m_hExitThreadCycle);
	delete(m_DispatchThread);
}



//====================================================================================================//
//���ܣ��������ݿ��ж�ȡ��PLC��Ϣ������CTCPClient����������modbus��ѯ�̣߳�ʵʱ���������ݴ�������дmodbus����      
//��ڣ�vPlcClass:�����ӵ�����PLC���࣬����PLCIP��ַ����ȡ��������С��              
//���ڣ���
//���أ���
//====================================================================================================//
void CModbus::CycleStart()
{
	//����PLC�������CTCPClient����
	m_vMultipleTCPClient.clear();
	m_vPlcClass = m_pDataP->m_vectPlc;
	m_nCountTCPClient = m_vPlcClass.size();
	for (int i = 0; i < m_nCountTCPClient; i++)
	{
		m_pTCPClient = new CTCPClient;
		m_pTCPClient->m_strRemoteHost = m_vPlcClass[i].m_strIPAddr;
		m_vMultipleTCPClient.push_back(*m_pTCPClient);
	}

	//��λ�˳���ѯ�߳��¼�	
	//	ResetEvent(m_hExitThreadCycle);

	//������ѯ�߳�

	m_WndCycleThread = AfxBeginThread(CycleThreadFunc, this, THREAD_PRIORITY_ABOVE_NORMAL);		

	
	if (!m_WndCycleThread)
	{
		//�߳��������ɹ�
		m_bIsCycling = FALSE;
		m_bModbusRead = FALSE;
	}
	else
	{
		//�߳������ɹ�����ʼ��ѯ
		m_bIsCycling = TRUE;
		m_bModbusRead = TRUE;
	}

	//�������ݷַ��߳�


	m_DispatchThread = new CThread(this);
	m_DispatchThread->Start();

}

//====================================================================================================//
//���ܣ�ֹͣ��ѯ�̣߳���ֹͣ��PLC�Ķ���д�����Ͽ�PLC������
//��ڣ���         
//���ڣ���
//���أ���
//====================================================================================================//
void CModbus::CycleDisconnect()
{
	//������ѯ�߳��˳��¼�
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
//���ܣ������ּĴ�������
//��ڣ�plcClass��CPlcClass�࣬�洢��Ŀ���IP����ȡ����ʼ��ַ�Լ��Ĵ����������������ɶ�ȡ����֡
//      nPlcIndex����ǵ�ǰPLC��PLC�б��е��������������ڶ�λ
//���ڣ���
//���أ�TRUE:���ݶ�ȡ�ɹ���FALSE:���ݶ�ȡʧ��
//====================================================================================================//
bool CModbus::CycleReadHoldingReg(CPlcClass plcClass, int nPlcIndex)
{
	BYTE* pbyReadHeader;
	pbyReadHeader = CreateReadHeader(plcClass, nPlcIndex);
	//���������ݰ����ȹ̶���12���ֽ�
	if (SendData(nPlcIndex, pbyReadHeader, 12) == TRUE)
	{
		//�����ݹ��ܴ��뷢�ͳɹ�
		return TRUE;
	}
	else
	{
		//���������ݷ���ʧ��
		return FALSE;
	}
}

//====================================================================================================//
//���ܣ���������������֡
//��ڣ�plcClass��CPlcClass�࣬�洢��Ŀ���IP����ȡ����ʼ��ַ�Լ��Ĵ����������������ɶ�ȡ����֡
//      nPlcIndex����ǵ�ǰPLC��PLC�б��е��������������ڶ�λ
//���ڣ���
//���أ�BYTE�������飬���ڷ�����װ�õ�����֡��ַ
//====================================================================================================//
BYTE* CModbus::CreateReadHeader(CPlcClass plcClass, int nPlcIndex)
{
	m_pbyReadHeader = new BYTE[12];
	m_pbyReadHeader[0] = nPlcIndex >> 8;     //�������ʶ�����ߵ�λ��ռ���ֽ�
	m_pbyReadHeader[1] = nPlcIndex;
	m_pbyReadHeader[2] = 0x00;               //Э���ʶ�����ߵ�λ��ռ���ֽڣ�������Ϊ0x0000
	m_pbyReadHeader[3] = 0x00;
	m_pbyReadHeader[4] = 0x00;               //�����ֽ����ݳ��ȣ��ߵ�λ��ռ���ֽڣ����������ݰ�Ϊ������0x0006
	m_pbyReadHeader[5] = 0x06;
	m_pbyReadHeader[6] = 0xff;               //��Ԫ��ʶ����ռһ�ֽڣ�����TCP/IPʱ��ͨ��IP��ַѰַ�����Դ˱�ʶ����������0xff
	m_pbyReadHeader[7] = FCT_READ_HOLD_REG;  //���ܴ���,ռһ�ֽڣ������궨��
	m_pbyReadHeader[8] = plcClass.m_ReadStartAddr >> 8;   //��ʼ�Ĵ�����ַ���ߵ�λ��ռ���ֽ�
	m_pbyReadHeader[9] = plcClass.m_ReadStartAddr;
	m_pbyReadHeader[10] = plcClass.m_ReadLength >> 8;     //��ȡ�Ĵ����������ߵ�λ��ռ���ֽ�
	m_pbyReadHeader[11] = plcClass.m_ReadLength;
	return m_pbyReadHeader;
}

//====================================================================================================//
//���ܣ���ָ����PLC���͹��ܴ�������   
//��ڣ�nIndex��Ŀ��PLC�ڱ��������������������洢��λ���������������෽��ʵ�ֲ�����
//      pbySendbuf��Ҫ���͵Ĺ��ܴ�������֡���������෽��ʵ�ֲ�����
//      nLen��Ҫ���͵�����֡�ĳ��ȣ��������෽��ʵ�ֲ�����
//���ڣ���
//���أ�TRUE:���ݶ�ȡ�ɹ���FALSE:���ݶ�ȡʧ��
//====================================================================================================//
bool CModbus::SendData(int nIndex, BYTE* pbySendbuf, int nLen)
{
	m_vMultipleTCPClient[nIndex].SetSendBuff((CHAR*)pbySendbuf, nLen);
	return true;
}

//====================================================================================================//
//���ܣ��ɴ���������Modbus������ڽӵ�������Ϣʱ���ã�����Socket���յ������ݣ����ݹ��ܷ�װ�����ݰ�����
//��ڣ�wparam��ָ�������Ϣ��Socket��Ӧ��IP��ֵַ
//      lparam����Ϣָ�룬ָ����Socket���յ�����Ϣ�Ĵ洢��ַ
//���ڣ���
//���أ���0:���ݽ����ɹ����������ݸ�����0:���ݽ���ʧ�ܻ�����������
//====================================================================================================//
int CModbus::GetResponseData(WPARAM wparam, LPARAM lparam)
{
	int nSizeOfResponseReadData;   //�����ܽ��յ���������Ϣ������16λ��Ϣ�ָ�����
	UINT wTemp;
	BYTE* info = (BYTE*)lparam;    //��ȡ������Ϣ
	if (info[7] == FCT_READ_HOLD_REG)
	{
		//��������Ĵ����Ƕ��������ܷ��صĴ���//
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
		//���Ƕ����ܷ��صĴ���//
		return 0;
	}
}

//==================================================================//
//���ܣ����߳�������ѯPLC���򿪡����ӡ���ȡ��д������
//��ڣ�lparam:������ָ�룬����ͨ���˲��������߳��д�����Ҫ�õ�����Դ
//      �˴���CModbus��ʵ��ָ�봫��
//      nLen:���������ݵĳ���
//���ڣ���
//���أ�����ֵ�����壬����0
//==================================================================//
UINT CModbus::CycleThreadFunc(LPVOID lparam)
{
	CModbus* pmd;
	pmd = (CModbus*)lparam;
	pmd->m_nIndex = 0;
	pmd->m_nWriteIndex = 0;
	//�߳��������򿪶�ʱ���������Ը�λ��д״̬

	while (TRUE)
	{
		//�յ��˳��¼��������߳�//
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
				//δ����״̬��������//
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

//�ַ������ɹ����ӵ�TCP�̶߳�ȡ��������
void CModbus::DispatchReadData()
{
	int nSizeOfResponseReadData;   //�ֽڸ���//
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
		if (m_vMultipleTCPClient[TcpIndex].m_bIsconnected&&sizeOfRecvBuff > 9) //��ǰ�ͻ��˳ɹ�����
		{
			if (m_vMultipleTCPClient[TcpIndex].m_vRecvBuff[7] == FCT_READ_HOLD_REG)
			{
				//��������Ĵ����Ƕ��������ܷ��صĴ���//
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

//�������ݵ�������
//index ΪУ���������m_vMultipleTCPClient�е�����
//У��ͨ������0�����򷵻�1
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
		TRACE("���ݷַ��߳����ڷַ�");
		DispatchReadData();
		Sleep(100);
	}

}