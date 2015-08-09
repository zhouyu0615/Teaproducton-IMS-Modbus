#include "stdafx.h"
#include "PlcClass.h"
#include <winnt.h>



CPlcClass::CPlcClass()
{
	m_Id = 0;
	m_strPlcName = _T("");
	m_strDescription = _T("");
	m_strProductionLineName = _T("");
	m_strIPAddr = _T("");
	m_UserId = 0;
	m_ReadStartAddr = 0;
	m_ReadLength = 0;
	m_WriteStartAddr = 0;
	m_WriteLength = 0;
	m_SortIndex = 0;
	m_bIsConnected = 0;


}


CPlcClass::~CPlcClass()
{
}


void CPlcClass::SetConectedState(int IsConnected)
{
	unsigned long *p = (unsigned long *)&m_bIsConnected;
	InterlockedExchange(p, IsConnected);

}

CString CPlcClass::GetConectedString()
{
	if (m_bIsConnected)
	{
		return _T("已连接");
	}
	else
	{
		return _T("断开");
	}

}


BOOL CPlcClass::GetConectedState()
{
	return (BOOL)m_bIsConnected;
}


int CPlcClass::GetPlcReadMemorySize()
{
	return m_PlcReadMemory.size();
}

BYTE  CPlcClass::GetReadByte(int ReadByteAddr)
{
	int length = m_PlcReadMemory.size();
	ASSERT(ReadByteAddr < length);
	if (ReadByteAddr>=length)
	{
		return 0;
	}

	return m_PlcReadMemory[ReadByteAddr];

}
BOOL CPlcClass::GetReadBit(int ReadByteAddr, int bitOffset)
{
	int length = m_PlcReadMemory.size();
	ASSERT(ReadByteAddr < length);
	ASSERT(bitOffset < 8);

	return ((m_PlcReadMemory[ReadByteAddr]>>bitOffset)&0x01);

}