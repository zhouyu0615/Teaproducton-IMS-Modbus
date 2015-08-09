#include "stdafx.h"
#include "FaultPara.h"


CFaultPara::CFaultPara()
{
	m_Id = 0;
	m_strCreatedDateTime = _T("");
	m_strLastUpdatedDateTime = _T("");
	m_PLCId = 0;
	m_ProcessModuleId = 0;
	m_DeviceId = 0;
	m_ProductionLineId = 0;
	m_strProductionLineName = _T("");
	m_strProcessName = _T("");
	m_strPlcName = _T("");
	m_strDescription = _T("");
	m_strDeviceName = _T("");
	m_strParaName = _T("");
	m_ParaValue = 0;
	m_strAddressIndex = _T("");
}


CFaultPara::~CFaultPara()
{
}
