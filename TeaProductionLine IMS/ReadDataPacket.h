#pragma once
#include <vector>
using namespace std;


class CReadDataPacket
{
public:
	CReadDataPacket();
	virtual ~CReadDataPacket();

public:
	CString m_strIP;    //������ԴIP��ַ
	int m_nDataLen;     //���ݳ���
	vector<CString> m_vstrDataPacket;    //���ݰ�����
};

