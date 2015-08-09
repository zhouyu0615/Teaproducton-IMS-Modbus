#include "stdafx.h"
#include "TCPClient.h"


CTCPClient::CTCPClient()
{
	//��ʼ��Socket����
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 1), &wd);
	m_nPort = 502;
	m_bIsconnected = FALSE;
	m_bIsopen = FALSE;
	//�����˳��߳��¼��ľ��,��ʼ״̬Ϊ���źţ��Զ���ԭ��������ҪReestEvent�������ֹ���ԭ�ź�����
//	m_hExitThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//��ȡ�����ھ��
	m_pWndOwner = AfxGetMainWnd();
	//��ʼ��ȫ��������
	m_pDataP = CDataProvider::getInstance();
	m_pThread = NULL;
	InitializeCriticalSection(&m_RBCS); //��ʼ���ٽ���
}


CTCPClient::~CTCPClient()
{
	//�ͷ�Socket��Դ
	WSACleanup();
	//�ر��˳��߳��¼��ľ��
//	SetEvent(m_hExitThreadEvent);
//	DeleteCriticalSection(&m_RBCS);
}


void CTCPClient::CreatePollThread()
{
	m_pThread = new CThread(this);
	m_pThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);

}

void CTCPClient::StartPollThread()
{
	m_pThread->Start();
	m_pThread->SetThreadName(m_strRemoteHost);
}
void CTCPClient::ResumePollThread()
{
	m_pThread->Resume();
}
void CTCPClient::SuspendPollThread()
{
	m_pThread->Suspend();
}

void CTCPClient::Run()
{
	fd_set fdRead;
	int nRet;
	//�����¼��ȴ�ʱ��
	TIMEVAL tvTime;
	tvTime.tv_sec = 1;
	tvTime.tv_usec = 0;
	while (TRUE)
	{
		if (m_bIsconnected == FALSE)
		{
			TRACE("����ʧ��");
				Sleep(500);
				continue;
		}

		SendData();
		//�յ��˳��¼��������߳�
		//if (WaitForSingleObject(m_hExitThreadEvent, 0) == WAIT_OBJECT_0)
		//{
		//	break;
		//}
		//��fdRead�¼�Ϊ��
		FD_ZERO(&fdRead);
		//���ͻ���Socket���ö��¼�
		FD_SET(this->m_Socket, &fdRead);
		//����select�������ж��Ƿ��ж��¼�����
		nRet = select(10, &fdRead, NULL, NULL, &tvTime);

		if (nRet == SOCKET_ERROR)
		{
			WSAGetLastError();
			//��ȡ�ļ�������ʧ��
			TRACE("��ȡ�ļ�������ʧ��\n");
			//�رտͻ���socket
			closesocket(m_Socket);
			WSACleanup();
			m_bIsconnected = FALSE;
			m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
			//break;
		}

		if (nRet > 0)
		{
			if (FD_ISSET(m_Socket, &fdRead))
			{
				//���fdset��ϵ���ļ����fd�Ƿ�ɶ�д����>0��ʾ�ɶ�д����
				//�������¼�
				char cRecvBuf[RECEIVE_BUFF_SIZE];
				int nRecvLen;
				ZeroMemory(cRecvBuf, RECEIVE_BUFF_SIZE);
				TRACE("���ݶ�ȡ�¼�������ִ�ж�����\n");
				//��������
				nRecvLen = recv(m_Socket, cRecvBuf, RECEIVE_BUFF_SIZE, 0);
				if (nRecvLen == SOCKET_ERROR)
				{
					int nError = WSAGetLastError();
					//���ݽ��ղ���ʧ��
					TRACE("���ݽ��ղ���ʧ��\n");
					//�رտͻ���socket
					closesocket(m_Socket);
					m_bIsconnected = FALSE;
					m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
					//break;
				}
				else if (nRecvLen == 0)
				{
					//�����Ͽ������¼�
					TRACE("���ݽ��յȴ������������ж�\n");
					//�رտͻ���socket
					closesocket(m_Socket);
		
					m_bIsconnected = FALSE;
					m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
					//break;
				}
				else
				{
					//�������ݽ����¼�����sendmessage���ƽ����յ����鷢�͵����״���
					//SetReadDataPacket(m_strRemoteHost, cRecvBuf);
					DealRecvData(cRecvBuf);
					m_bIsconnected = TRUE;
					m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(TRUE);
					TRACE("%d ���ݽ��ճɹ�\n",m_pThread->GetThreadID());
				}
			}
		}

		Sleep(200);
	}
	

}

//============================================//
//���ܣ����ڴ򿪿ͻ���Socket
//��ڣ���
//���ڣ���
//���أ�TRUE--�򿪳ɹ���FALSE--��ʧ��
//============================================//
bool CTCPClient::Open()
{
	//��λ�߳��˳��¼�
//	ResetEvent(m_hExitThreadEvent);
	//����TCP�׽���
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == SOCKET_ERROR)
	{
		m_bIsopen = FALSE;
		return FALSE;
	}

	m_bIsopen = TRUE;
	return TRUE;
}

//============================================//
//���ܣ����ڽ�����TCP����������
//��ڣ���
//���ڣ���
//���أ�TRUE--�������ӳɹ���FALSE--��������ʧ��
//============================================//
bool CTCPClient::Connect()
{
	struct sockaddr_in addr;
	int nErr;
	char cAnsiRemoteHost[255];

	//��λ��ǰ���ӵ�PLC�ڹ����������е�����λ��

	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPort);
	//�˴�Ҫ��˫�ֽ�ת���ɵ��ֽ�
	ZeroMemory(cAnsiRemoteHost, 255);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_strRemoteHost, wcslen(m_strRemoteHost), cAnsiRemoteHost, wcslen(m_strRemoteHost), NULL, NULL);
	addr.sin_addr.S_un.S_addr = inet_addr(cAnsiRemoteHost);
	//�������ӵ�Socket�ͻ��ˣ�����Ҫbind()
	//����ͬ�����ӷ�ʽ��connectֱ�ӷ��سɹ�����ʧ��
	nErr = connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr));
	if (nErr == SOCKET_ERROR)
	{
		TRACE("����ʧ��\n");
		m_bIsconnected = FALSE;
		m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
		//Close();
		return FALSE;
	}
	//����ͨѶģʽΪ�첽ģʽ
	DWORD dwUl = 1;
	ioctlsocket(m_Socket, FIONBIO, &dwUl);
	TRACE("���ӳɹ�\n");
	m_bIsconnected = TRUE;
	m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(TRUE);

	return TRUE;
}



//============================================//
//���ܣ����ڹرտͻ���Socket
//��ڣ���
//���ڣ���
//���أ�TRUE--�رճɹ���FALSE--�ر�ʧ��
//============================================//
bool CTCPClient::Close()
{
	//����ͨѶ�߳̽����¼�
//	SetEvent(m_hExitThreadEvent);
//	Sleep(100);
	//�ر�Socket���ͷ���Դ
	int nErr = closesocket(m_Socket);
	if (nErr == SOCKET_ERROR)
	{
		return FALSE;
	}
	m_bIsconnected = FALSE;
	m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
	return TRUE;
}

//============================================//
//���ܣ���������˷�������
//��ڣ�c_pcSendBuf:�����͵�����
//      nLen:���������ݵĳ���
//���ڣ���
//���أ�TRUE���������ݳɹ���FALSE����������ʧ��
//============================================//
bool CTCPClient::SendData()
{
	int nBytes = 0;
	int nSendBytes = 0;

	while (nSendBytes < m_nSendBufLen)
	{
		nBytes = send(m_Socket, m_pcSendBuf + nSendBytes, m_nSendBufLen - nSendBytes, 0);
		if (nBytes == SOCKET_ERROR)
		{
			int nErrorCode = WSAGetLastError();
			//��������ʧ��
			TRACE("��������ʧ��\n");
			//�ر�Socket
			Close();
			m_bIsconnected = FALSE;
			m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(FALSE);
			return FALSE;
		}
		//������ݹ���������һ���Է�����ɣ���ֶ�δ���
		nSendBytes = nSendBytes + nBytes;
		if (nSendBytes < m_nSendBufLen)
		{
			Sleep(10);
		}
	}
	TRACE("�������ݳɹ�\n");
	m_bIsconnected = TRUE;
	m_pDataP->m_vectPlc[GetPlcClassIndex()].SetConectedState(TRUE);
	return TRUE;
}


void CTCPClient::SetSendBuff(char *pcSendBuf, int nLen)
{
	m_pcSendBuf = pcSendBuf;
	m_nSendBufLen = nLen;
}


//�����ɹ����յ����ַ������뵽m_vRecvBuff�У���MODBUS�����ݷַ��߳̽��ж�ȡ�ַ�
void CTCPClient::DealRecvData(char* pcRcvData)
{
	EnterCriticalSection(&m_RBCS);
	m_vRecvBuff.clear();
	for (int i = 0; i < RECEIVE_BUFF_SIZE;i++)
	{
		m_vRecvBuff.push_back(*pcRcvData++);
	}
	LeaveCriticalSection(&m_RBCS);
	Sleep(100);

}



//==================================================================//
//���ܣ������������ڷ��ʹ�����Ϣ��������Ӧ
//��ڣ�nMessageIndex:���α�����ͨ���˲�����ָ�����͵���Ϣ�ı��
//      pcIP:���͵ĵ�һ��������ָ��洢��ǰSocket��IP��ַ���ڴ�ռ�
//      pSendData:���͵ĵڶ���������ָ��洢��ǰҪ���ݵ����ݵ��ڴ�ռ�
//      pTCPOwner:����ָ�룬ָ������Ϣ��Ŀ�괰�ھ��
//���ڣ���
//���أ�����ֵ�����壬����0
//==================================================================//
void CTCPClient::ProcessMessage(int nMessageIndex, char* pcIP, char* pSendData, CWnd* pTCPOwner)
{
	::SendMessage(pTCPOwner->m_hWnd, nMessageIndex, (WPARAM)pcIP, (LPARAM)pSendData);
}

//==================================================================//
//���ܣ��ѵ�ǰ���յ������ݸ��µ������������д洢
//��ڣ�strIP:�����ݰ���IP��ַ
//      pcRcvData:ָ��洢��ǰҪ���ݵ����ݵ��ڴ�ռ�
//���ڣ���
//���أ��޷���ֵ
//==================================================================//
void CTCPClient::SetReadDataPacket(CString strIP, char* pcRcvData)
{
	int j;
	int nSizeOfResponseReadData;    //�����ܽ��յ���������Ϣ����(�ֽڸ���)
	vector<CString> vstrReadData;   //�Ѷ����ܷ��ص������ֽ�ת���ɶ����ƴ���ת�����ַ����洢
	CString strTemp;
	vstrReadData.clear();

	//�������ݰ�
	if (pcRcvData[7] == FCT_READ_HOLD_REG)
	{
		//��������Ĵ����Ƕ��������ܷ��صĴ���
		nSizeOfResponseReadData = pcRcvData[8];
		for (int i = 0; i < nSizeOfResponseReadData; i++)
		{
			strTemp = pcRcvData[9 + i];
			vstrReadData.push_back(strTemp);
		}
		//��ѯ�������������Ƿ���ڵ�ǰIP��������
		for (j = 0; j < m_pDataP->m_vectReadDataPacket.size(); j++)
		{
			if (m_pDataP->m_vectReadDataPacket[j].m_strIP == strIP)
			{
				m_pDataP->m_vectReadDataPacket[j].m_vstrDataPacket.clear();
				//���IP��ַ�Ѿ����ڣ�����µ�ǰ���ݰ�				
				for (int k = 0; k < vstrReadData.size(); k++)
				{
					m_pDataP->m_vectReadDataPacket[j].m_vstrDataPacket.push_back(vstrReadData[k]);
				}
				break;
			}
		}
		if (j >= m_pDataP->m_vectReadDataPacket.size())
		{
			//���IP��ַ�����ڣ�����ӵ���������������
			CReadDataPacket TempPacket;
			TempPacket.m_strIP = strIP;
			TempPacket.m_nDataLen = vstrReadData.size();
			TempPacket.m_vstrDataPacket.clear();
			for (int k = 0; k < vstrReadData.size(); k++)
			{
				TempPacket.m_vstrDataPacket.push_back(vstrReadData[k]);
			}
			m_pDataP->m_vectReadDataPacket.push_back(TempPacket);
		}
	}
}

//==================================================================//
//���ܣ���ȡ��ǰPLC�ڹ������������е�λ������
//��ڣ���
//���ڣ���
//���أ�����ֵ��ǰPLC����
//==================================================================//
int CTCPClient::GetPlcClassIndex()
{
	int nIndex;
	for (int i = 0; i < m_pDataP->m_vectPlc.size(); i++)
	{
		if (m_pDataP->m_vectPlc[i].m_strIPAddr == m_strRemoteHost)
		{
			nIndex = i;
			break;
		}
	}
	return nIndex;
}