#pragma once
#include <vector>
using namespace std;


class CReadDataPacket
{
public:
	CReadDataPacket();
	virtual ~CReadDataPacket();

public:
	CString m_strIP;    //数据来源IP地址
	int m_nDataLen;     //数据长度
	vector<CString> m_vstrDataPacket;    //数据包内容
};

