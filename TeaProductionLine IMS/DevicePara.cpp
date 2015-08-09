#include "stdafx.h"
#include "DevicePara.h"


CDevicePara::CDevicePara()
{
	m_Id = 0;
	m_strCreatedDateTime = _T("");
	m_strLastUpdatedDateTime = _T("");
	m_ProductionLineId = 0;
	m_ProcessModuleId = 0;
	m_PlcId = 0;
	m_DeviceId = 0;
	m_strProductionLineName = _T("");
	m_strProcessModuleName = _T("");
	m_strDeviceName = _T("");
	m_strPlcName = _T("");
	m_ControlValue = 0;
	m_StateValue = 0;
	m_strControlAddrIndex = _T("");
	m_strStateAddrIndex = _T("");
	m_strDescription = _T("");
	m_strParaName = _T("");
}


CDevicePara::~CDevicePara()
{
}

