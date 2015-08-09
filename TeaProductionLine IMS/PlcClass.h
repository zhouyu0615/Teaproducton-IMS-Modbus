#pragma once
#include <vector>

class CPlcClass
{

private:
	int m_bIsConnected;
public:
	CPlcClass();
	~CPlcClass();
	int m_Id;
	CString m_strPlcName;
	CString m_strDescription;
	CString m_strProductionLineName;
	int m_ProductionLineId;

    //int m_Port;
	CString m_strIPAddr;
	int m_UserId;
	int m_ReadStartAddr;
	int m_ReadLength;
	int m_WriteStartAddr;
	int m_WriteLength;
	int m_SortIndex;

	std::vector<BYTE> m_PlcReadMemory;

	int GetPlcReadMemorySize();

	BYTE  GetReadByte(int ReadByteAddr);
	BOOL GetReadBit(int ReadByteAddr, int bitOffset);

	void SetConectedState(BOOL IsConnected);
	BOOL GetConectedState();

	CString GetConectedString();

};

