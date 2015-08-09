#pragma once
class CProcessPara
{
public:
	CProcessPara();
	~CProcessPara();

	static const int VALUETYPE_BOOL = 0;
	static const int VALUETYPE_BYTE = 1;
	static const int VALUETYPE_SHORT = 2;
	static const int VALUETYPE_LONG = 3;
	static const int VALUETYPE_FLOAT = 4;
	static const int VALUETYPE_DOUBLE = 5;


	int m_Id;
	int m_ProcessModuleId;
	int m_ProductionLineId;
	CString m_strCreatedDateTime;
	CString  m_strLastUpdatedDateTime;
	CString m_strProductionLineName;
	CString m_strProcessModuleName;
	CString m_strPlcName;
	CString m_strDescription;
	float m_ParaValue;
	CString m_strParaName;
	int m_IsConfig;
	int m_IsVisible;
	int m_ValueType;
	CString m_strReadAddrIndex;
	CString m_strAddressType;
	int m_PlcId;
	CString m_strUnit;
	CString m_strWriteAddrIndex;

	float m_fSetValue;

	CString ConvertValTypeToString();
	CString ConvertIsConfigToString();
	CString ConvertIsVisibleToString();

	CString ConvertParaValueToString();
	CString ConvertSetValueToString();

	int SetParaValue(float fParaValue);

	int GetReadAddrIndex();
};

