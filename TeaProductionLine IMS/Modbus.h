#pragma once
#include "TCPClient.h"
#include <vector>
#include "PlcClass.h"
#include "Thread.h"

using namespace std;
#define FCT_READ_COILS		        0x01	// ����Ȧ
#define FCT_READ_HOLD_REG	        0x03	// �����ּĴ��� 
#define FCT_WRITE_SINGLE_COILS      0x05	// д��Ȧ 
#define FCT_WRITE_SINGLE_HOLD_REG   0x06	// д�����Ĵ��� 
#define FCT_WRITE_MULTIPLE_REG	    0x10	// д����Ĵ���

class CModbus:CThread,CWnd
{
public:
	CModbus();
	virtual ~CModbus();

public:
	vector<CTCPClient> m_vMultipleTCPClient;    //TCP�ͻ�����������������װһ����TCP�ͻ��˶���
	vector<CPlcClass> m_vPlcClass;              //PLC������
	int m_nCountTCPClient;                //TCP�ͻ�����������	
	bool m_bIsCycling;                   //��ѯ�������
	CDataProvider *m_pDataP;             //ָ��ȫ�����ݴ洢��

	
private:
	//HANDLE m_hExitThreadCycle;           //�˳���ѯ�߳̾��
	CWinThread* m_WndCycleThread;        //��ѯ�߳̾��
	int m_nIndex;                        //��ѯ����
	int m_nWriteIndex;                   //д������ѯ��������д���ܱ�ʶΪTRUE��ÿд���һ��PLC����+1��������ڵ�m_nCountTCPClientʱ��д���ܱ�ʶΪFALSE������
	bool m_bModbusRead;                  //д���ܱ�ʶ
	bool m_bModbusWrite;                 //�����ܱ�ʶ
	CTCPClient* m_pTCPClient;    //���ڶ�̬����TCPClient����push_back()����Vector����
	BYTE* m_pbyReadHeader;       //ָ�����ɵĶ���������֡

public:
	void CycleStart();     //�������ݿ��ȡ��PLC�����������TCPClient������������ѯ�߳�     
	void CycleDisconnect();               //�Ͽ���ѯ״̬�������Ͽ���PLC������״̬
	bool CycleReadHoldingReg(CPlcClass plcClass,int nPlcIndex);       //��ѯ���Ĵ�������
	BYTE* CreateReadHeader(CPlcClass plcClass, int nPlcIndex);        //��������������֡
	//bool WriteHoldingReg(CDataWritePacket DataWritePacket);         //д�Ĵ�������
	bool SendData(int nIndex, BYTE* pbySendbuf, int nLen);          //��ָ����IP��ַ���͹�������֡
	int GetResponseData(WPARAM wparam, LPARAM lparam);  //��ȡ�ɴ����ṩ�ģ�ָ����IP��ַ�ģ���TCPCLient���յ������ݣ������н���������

	void DispatchReadData();
	BOOL  VerifyRecvData(int Index);
	int GetPlcClassIndex(CString strIpAddr);            //��ȡ��ǰPLC�ڹ������������е�λ������


	CThread *m_DispatchThread;
	virtual void Run(); //���ݷַ��̵߳����к���//


private:
	static UINT CycleThreadFunc(LPVOID lparam);               //��ѯ�߳�
};

