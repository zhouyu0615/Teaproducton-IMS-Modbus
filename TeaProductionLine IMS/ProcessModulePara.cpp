#include "stdafx.h"
#include "ProcessModulePara.h"


CProcessPara::CProcessPara()
{
	m_Id = 0;
	m_ProcessModuleId = 0;
	m_ProductionLineId = 0;
	m_strProductionLineName = _T("");
	m_strProcessModuleName = _T("");
	m_strPlcName = _T("");
	m_strDescription = _T("");
	m_ParaValue = 0;
	m_strParaName = _T("");
	m_IsConfig = 0;
	m_IsVisible = 0;
	m_ValueType = 0;
	m_strReadAddrIndex = _T("");
	m_strAddressType = _T("");
	m_PlcId = 0;
	m_strCreatedDateTime = _T("");
	m_strLastUpdatedDateTime = _T("");
	m_strUnit = _T("");
	m_strWriteAddrIndex = _T("");
	m_fSetValue = -3001;

}


CProcessPara::~CProcessPara()
{
}

CString CProcessPara::ConvertValTypeToString()
{
	switch (m_ValueType)
	{
	case VALUETYPE_BOOL:
		return _T("Bool");
	case VALUETYPE_BYTE:
		return _T("Byte");
	case VALUETYPE_SHORT:
		return _T("Short");
	case VALUETYPE_LONG:
		return _T("Long");
	case VALUETYPE_FLOAT:
		return _T("Float");
	case VALUETYPE_DOUBLE:
		return _T("Double");
	default:
		return _T("Null");
	}

}

CString CProcessPara::ConvertIsConfigToString()
{
	if (m_IsConfig)
	{
		return _T("ÊÇ");
	}
	else
	{
		return _T("·ñ");
	}
}


CString CProcessPara::ConvertIsVisibleToString()
{
	if (m_IsVisible)
	{
		return _T("ÊÇ");
	}
	else
	{
		return _T("·ñ");
	}
}


CString CProcessPara::ConvertParaValueToString()
{

	CString strPareValue;
	strPareValue.Format(_T("%3.2f"), m_ParaValue);


	return strPareValue;
}

CString CProcessPara::ConvertSetValueToString()
{
	CString strSetValue;
	strSetValue.Format(_T("%.2f"), m_fSetValue);

	return strSetValue;
}

int CProcessPara::SetParaValue(float fParaValue)
{
	//unsigned long *p = (unsigned long *)&m_ParaValue;
	//InterlockedExchange(p, fParaValue);

	m_ParaValue = fParaValue;
	return 0;
}

int CProcessPara::GetReadAddrIndex()
{
	return _ttoi(m_strReadAddrIndex);
}