#pragma once
class CFaultPara
{
public:
	CFaultPara();
	~CFaultPara();
	int m_Id;
	CString m_strCreatedDateTime;
	CString m_strLastUpdatedDateTime;
	int m_PLCId;
	int m_ProcessModuleId;
	int m_DeviceId;
	int m_ProductionLineId;
	CString m_strProductionLineName;
	CString m_strProcessName;
	CString m_strPlcName;
	CString m_strDescription;
	CString m_strDeviceName;
	CString m_strParaName;
	int m_ParaValue;
	CString m_strAddressIndex;
};

