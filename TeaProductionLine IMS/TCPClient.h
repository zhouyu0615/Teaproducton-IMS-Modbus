#pragma once

#define WM_SOCKETCOMM_RECIEVECHAR       WM_USER+1 //������Ϣ����ʾ���յ��ַ������洢�����뻺������
#define FCT_READ_COILS		        0x01	// ����Ȧ
#define FCT_READ_HOLD_REG	        0x03	// �����ּĴ��� 
#define FCT_WRITE_SINGLE_COILS      0x05	// д��Ȧ 
#define FCT_WRITE_SINGLE_HOLD_REG   0x06	// д�����Ĵ��� 
#define FCT_WRITE_MULTIPLE_REG	    0x10	// д����Ĵ���

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
	CString m_strRemoteHost;             //Զ�̷���IP��ַ
	int m_nPort;                         //Զ�̷��ʶ˿ڣ�modbus�̶����ʶ˿ڣ�502
	bool m_bIsconnected;                 //Socket����״̬
	bool m_bIsopen;                      //Socket��״̬
	CDataProvider *m_pDataP;             //ָ��ȫ�����ݴ洢��

private:
	SOCKET m_Socket;                     //ͨѶSocket���
	//HANDLE m_hExitThreadEvent;           //�˳�ͨѶ�߳��¼��ľ��
	CWinThread* m_WndTCPThread;          //ͨѶ�߳̾��
	HANDLE m_hTCPThreadHandle;
	CWnd* m_pWndOwner;                   //�����ھ��

public:
	bool Open();                         //��Socket�Լ�����ͨѶ�¼��̣߳�����Socket��Ϣ
	bool Connect();                      //����Socket
	bool Close();                        //�ر�Socket
	bool SendData();    //��������

	void SetSendBuff(char *pcSendBuf, int nLen);
	char *m_pcSendBuf;
	int   m_nSendBufLen;

	/*����m_vRecvBuff���ٽ�������*/
	CRITICAL_SECTION m_RBCS;
	std::vector<BYTE> m_vRecvBuff;
	void DealRecvData(char* pcRcvData);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/

	void CreatePollThread();
	void StartPollThread();
	void ResumePollThread();
	void SuspendPollThread();
	virtual void Run(); 
	CThread *m_pThread;

private:
	static UINT SocketThreadFunc(LPVOID lparam); //ͨѶ�߳����к���
	void ProcessMessage(int nMessageIndex, char* pcIP, char* pcSendData, CWnd* pTCPOwner);   //��ָ�����ڷ��ͽ��յ�����Ϣ
	void SetReadDataPacket(CString strIP, char* pcRcvData);
	int GetPlcClassIndex();            //��ȡ��ǰPLC�ڹ������������е�λ������


};

