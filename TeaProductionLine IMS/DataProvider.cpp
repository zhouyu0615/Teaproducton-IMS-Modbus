#include "stdafx.h"
#include "DataProvider.h"

#include "tbUser.h"
#include "tbProductionLine.h"
#include "tbProcessModule.h"
#include "tbDevice.h"
#include "tbPLc.h"
#include "tbVideo.h"


#include "tbLoginUser.h"
#include "tbDevicePara.h"
#include "tbFaultPara.h"
#include "tbProcessPara.h"
#include "tbStatePara.h"





CDataProvider::CDataProvider()
{

}


CDataProvider::~CDataProvider()
{
	delete(Instance);
}

CDataProvider::CDataProvider(const CDataProvider&)
{
};

CDataProvider*   CDataProvider::Instance = NULL;

CRITICAL_SECTION Cs;
CDataProvider* CDataProvider::getInstance(){

	InitializeCriticalSection(&Cs);
	if (Instance == NULL)
	{
		EnterCriticalSection(&Cs);
		if (Instance == NULL)
		{
			Instance = new CDataProvider();
		}
		LeaveCriticalSection(&Cs);
	}

	return Instance;
}

void CDataProvider::InitDataProvider()
{
	this->ReadLoginUserFormDatabase();

	this->ReadUserFromDatabase();
	this->ReadProLineFromDatabase();
	this->ReadProModuleFromDatabase();
	this->ReadDeviceFromDatabase();
	this->ReadPlcFromDatabase();
	this->ReadVideoFromDatabase();

	this->ReadDeviceParaFromDatabase();
	this->ReadProcessParaFromDatabase();
	this->ReadFaultParaFromDatabase();
	this->ReadStateParaFromDatabase();
	this->ReadFormulaFormDatabase();
}



int CDataProvider::ExecutionSQL(CString strSql)
{
	CtbUser tbUser;
	try{
		if (tbUser.Open(CRecordset::dynaset)){
			tbUser.m_pDatabase->ExecuteSQL(strSql);
		}
		else{
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			tbUser.Close();
			return 1;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbUser.Close();

	return 0;
}


int CDataProvider::FindProLineId(CString ProducitonLineName)
{
	int ProLineId;
	for (int i = 0; i < m_vectProductionLine.size(); i++)
	{
		if (ProducitonLineName == m_vectProductionLine[i].m_strLineName)
		{
			ProLineId = m_vectProductionLine[i].m_Id;
			return ProLineId;
		}
	}
	return 0;
}


int CDataProvider::FindProModuleId(CString ProductionLineName, CString ModuleName)
{
	int ProModuleId;
	for (int i = 0; i < m_vectProcessModule.size(); i++)
	{
		if (ProductionLineName == m_vectProcessModule[i].m_strProductionLineName
			&&ModuleName == m_vectProcessModule[i].m_strProcessModuleName)
		{
			ProModuleId = m_vectProcessModule[i].m_Id;
			return ProModuleId;
		}
	}
	return 0;
}


int CDataProvider::FindPlcId(CString PlcName)
{
	int PlcId;
	for (int i = 0; i < m_vectPlc.size(); i++)
	{
		if (PlcName == m_vectPlc[i].m_strPlcName)
		{
			PlcId = m_vectPlc[i].m_Id;
			return PlcId;
		}
	}
	return 0;

}

int CDataProvider::FindDeviceId(CString ProductionLineName, CString ModuleName, CString DeviceName)
{
	int DeviceId;
	for (int i = 0; i < m_vectDevice.size(); i++)
	{
		if (ProductionLineName == m_vectDevice[i].m_strProductionLineName
			&&ModuleName == m_vectDevice[i].m_strProcessModuleName
			&&DeviceName == m_vectDevice[i].m_strDeviceName)
		{
			DeviceId = m_vectDevice[i].m_Id;
			return DeviceId;
		}
	}

	return 0;
}

int CDataProvider::FindProcessParaId(CString ProcessParaName)
{
	for (int i = 0; i < m_vectProModulePara.size(); i++)
	{
		if (ProcessParaName == m_vectProModulePara[i].m_strParaName)
		{
			return m_vectProModulePara[i].m_Id;
		}
	}
	return 0;
}

CString CDataProvider::FindProcessParaName(int ProcessParaId)
{
	for (int i = 0; i < m_vectProModulePara.size(); i++)
	{
		if (ProcessParaId == m_vectProModulePara[i].m_strParaName)
		{
			return m_vectProModulePara[i].m_strParaName;
		}
	}
	return _T("");
}


void CDataProvider::AddLoginUserToDatabase(CLoginUser tempLoginUser)
{
	int length = m_vectLoginUser.size();
	if (length == 0)
	{
		tempLoginUser.m_Id = 1000; //��½�û���ʼID
	}
	else{
		tempLoginUser.m_Id = m_vectLoginUser[length - 1].m_Id + 1;
	}

	m_vectLoginUser.push_back(tempLoginUser);

	CtbLoginUser m_tbLoginUserSet;
	try{
		if (m_tbLoginUserSet.IsOpen())
			m_tbLoginUserSet.Close();
		if (!m_tbLoginUserSet.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (m_tbLoginUserSet.CanUpdate()){
		m_tbLoginUserSet.AddNew();

		CTime time = CTime::GetCurrentTime();
		m_tbLoginUserSet.m_Id = tempLoginUser.m_Id;
		m_tbLoginUserSet.m_CreatedDateTime = time;
		m_tbLoginUserSet.m_LastUpdatedDateTime = time;
		m_tbLoginUserSet.m_LoginName = tempLoginUser.m_strLoginName;
		m_tbLoginUserSet.m_LoginPassWd = tempLoginUser.m_strLoginPassWd;
		m_tbLoginUserSet.m_PermissionLevel = tempLoginUser.m_PermissionLevel;
		m_tbLoginUserSet.m_IsAutoLogin = tempLoginUser.m_IsAutoLogin;
		m_tbLoginUserSet.m_IsRememberPasswd = tempLoginUser.m_IsRememberPasswd;

		m_tbLoginUserSet.Update();

	}
	m_tbLoginUserSet.Close();

}

void CDataProvider::UpdateUserLoginTime(int LoginUserId)
{
	CString strsql;
	strsql.Format(_T("UPDATE tbLoginUser SET LastLoginInTime=getdate() where ID=%d"), LoginUserId);
	CtbLoginUser tbLoginUser;
	try{
		if (tbLoginUser.Open(CRecordset::dynaset)){
			tbLoginUser.m_pDatabase->ExecuteSQL(strsql);
		}
		else{
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			tbLoginUser.Close();
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbLoginUser.Close();
}

void CDataProvider::AddUserToDatabase(CUserClass tempUser)
{
	CtbUser m_tbUserSet;
	try{
		if (m_tbUserSet.IsOpen())
			m_tbUserSet.Close();
		if (!m_tbUserSet.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}


	int length = m_vectUser.size();
	if (m_vectUser.size() == 0) //���õ�һ���û���ID
	{
		tempUser.m_UserId = 1000;
	}
	else
	{
		tempUser.m_UserId = m_vectUser[length - 1].m_UserId + 1;
	}

	m_vectUser.push_back(tempUser);

	if (m_tbUserSet.CanUpdate()){
		m_tbUserSet.AddNew();

		CTime time = CTime::GetCurrentTime();
		m_tbUserSet.m_Id = tempUser.m_UserId;
		m_tbUserSet.m_CreatedDateTime = time;
		m_tbUserSet.m_LastUpdatedDateTime = time;
		m_tbUserSet.m_UserName = tempUser.m_strUserName;
		m_tbUserSet.m_UserPassword = tempUser.m_strUserPasswd;
		m_tbUserSet.m_UserCode = tempUser.m_strUserCode;
		m_tbUserSet.m_Note = tempUser.m_strNote;
		m_tbUserSet.Update();

	}
	m_tbUserSet.Close();
}




void CDataProvider::AddProLineToDatabase(CProductionLineClass tempProLine)
{

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	int length = m_vectProductionLine.size();

	if (length == 0)//���õ�һ�������ߵ�ID
	{
		tempProLine.m_Id = 1;
		tempProLine.m_SortIndex = 1;
	}
	else{
		tempProLine.m_Id = m_vectProductionLine[length - 1].m_Id + 1;
		tempProLine.m_SortIndex = m_vectProductionLine[length - 1].m_SortIndex + 1;
	}
	tempProLine.m_UserId = m_vectUser[0].m_UserId; ////Ψһ�û�ID

	m_vectProductionLine.push_back(tempProLine);

	if (tbProductionLine.CanUpdate()){
		tbProductionLine.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProductionLine.m_Id = tempProLine.m_Id;
		tbProductionLine.m_CreatedDateTime = time;
		tbProductionLine.m_LastUpdatedDateTime = time;
		tbProductionLine.m_LineName = tempProLine.m_strLineName;
		tbProductionLine.m_UserId = tempProLine.m_UserId;
		tbProductionLine.m_Capacity = tempProLine.m_strCapacity;
		tbProductionLine.m_Description = tempProLine.m_strDescription;
		tbProductionLine.m_SortIndex = tempProLine.m_SortIndex;
		tbProductionLine.Update();
	}

	tbProductionLine.Close();
}




void CDataProvider::AddProModuleToDatabase(CProcessModuleClass tempProModule)
{
	CtbProcessModule tbProcessModule;
	try{
		if (tbProcessModule.IsOpen())
			tbProcessModule.Close();
		if (!tbProcessModule.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	int length = m_vectProcessModule.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempProModule.m_Id = 1000;
		tempProModule.m_SortIndex = 1000;
	}
	else{
		tempProModule.m_Id = m_vectProcessModule[length - 1].m_Id + 1;
		tempProModule.m_SortIndex = m_vectProcessModule[length - 1].m_SortIndex + 1;
	}

	//�洢ģ�������û�ID
	tempProModule.m_UserId = m_vectUser[0].m_UserId;
	//�ҳ�����ģ�����������ߵ�ID
	int ProLineId = FindProLineId(tempProModule.m_strProductionLineName);
	tempProModule.m_ProcessLineId = ProLineId;

	m_vectProcessModule.push_back(tempProModule);

	if (tbProcessModule.CanUpdate()){
		tbProcessModule.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProcessModule.m_Id = tempProModule.m_Id;
		tbProcessModule.m_CreatedDateTime = time;
		tbProcessModule.m_LastUpdatedDateTime = time;
		tbProcessModule.m_ProductionLineName = tempProModule.m_strProductionLineName;
		tbProcessModule.m_UserId = tempProModule.m_UserId; //Ψһ�û�ID
		tbProcessModule.m_ProductionLineId = tempProModule.m_ProcessLineId; //����������ID
		tbProcessModule.m_ModuleName = tempProModule.m_strProcessModuleName;
		tbProcessModule.m_Description = tempProModule.m_strDescription;
		tbProcessModule.m_SortIndex = tempProModule.m_SortIndex;
		tbProcessModule.Update();
	}

	tbProcessModule.Close();


}

void CDataProvider::AddDeviceToDatabase(CDeviceClass tempDevice)
{
	CtbDevice tbDevice;
	try{
		if (tbDevice.IsOpen())
			tbDevice.Close();
		if (!tbDevice.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	int length = m_vectDevice.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempDevice.m_Id = 1000;
		tempDevice.m_SortIndex = 1000;
	}
	else{
		tempDevice.m_Id = m_vectDevice[length - 1].m_Id + 1;
		tempDevice.m_SortIndex = m_vectDevice[length - 1].m_SortIndex + 1;
	}


	int ProLineId, ProModuleId;
	//�ҵ����豸���������ߵ�ID
	ProLineId = FindProLineId(tempDevice.m_strProductionLineName);
	//�ҵ��豸�����Ĺ���ģ���ID
	ProModuleId = FindProModuleId(tempDevice.m_strProductionLineName, tempDevice.m_strProcessModuleName);

	tempDevice.m_ProductionLineId = ProLineId;
	tempDevice.m_ProcessModuleId = ProModuleId;

	m_vectDevice.push_back(tempDevice);

	if (tbDevice.CanUpdate()){
		tbDevice.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbDevice.m_Id = tempDevice.m_Id;
		tbDevice.m_CreatedDateTime = time;
		tbDevice.m_LastUpdatedDateTime = time;
		tbDevice.m_ProductionLineName = tempDevice.m_strProductionLineName;
		tbDevice.m_ProcessModuleName = tempDevice.m_strProcessModuleName;
		tbDevice.m_DeviceName = tempDevice.m_strDeviceName;
		tbDevice.m_DeviceType = tempDevice.m_strDeviceType;
		tbDevice.m_ProductionLineId = tempDevice.m_ProductionLineId; //���������ߵ�ID
		tbDevice.m_ProcessModuleId = tempDevice.m_ProcessModuleId;// ��������ģ���ID
		tbDevice.m_SortIndex = tempDevice.m_SortIndex;

		tbDevice.Update();

	}

	tbDevice.Close();
}


void CDataProvider::AddPlcToDatabase(CPlcClass tempPlc)
{
	CtbPLc tbPlc;
	try{
		if (tbPlc.IsOpen())
			tbPlc.Close();
		if (!tbPlc.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	int length = m_vectPlc.size();
	if (length == 0)//���õ�һ��PLC ID
	{
		tempPlc.m_Id = 1000;
		tempPlc.m_SortIndex = 1000;
	}
	else{
		tempPlc.m_Id = m_vectPlc[length - 1].m_Id + 1;
		tempPlc.m_SortIndex = m_vectPlc[length - 1].m_SortIndex + 1;
	}

	tempPlc.m_UserId = m_vectUser[0].m_UserId;
	int ProlineId = FindProLineId(tempPlc.m_strProductionLineName); //�ҳ�PLC���������ߵ�ID
	tempPlc.m_ProductionLineId = ProlineId;

	m_vectPlc.push_back(tempPlc);

	if (tbPlc.CanUpdate()){
		tbPlc.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbPlc.m_Id = tempPlc.m_Id;
		tbPlc.m_CreatedDateTime = time;
		tbPlc.m_LastUpdatedDateTime = time;
		tbPlc.m_ProductionLineName = tempPlc.m_strProductionLineName;
		tbPlc.m_UserId = tempPlc.m_UserId; //Ψһ�û�ID
		tbPlc.m_PLCName = tempPlc.m_strPlcName;
		tbPlc.m_strIPAddr = tempPlc.m_strIPAddr;
		tbPlc.m_ReadStartAddr = tempPlc.m_ReadStartAddr;
		tbPlc.m_ReadLength = tempPlc.m_ReadLength;
		tbPlc.m_WriteStartAddr = tempPlc.m_WriteStartAddr;
		tbPlc.m_WriteLength = tempPlc.m_WriteLength;
		tbPlc.m_Description = tempPlc.m_strDescription;
		tbPlc.m_SortIndex = tempPlc.m_SortIndex;

		tbPlc.Update();

	}

	tbPlc.Close();
}


void CDataProvider::AddVideoToDatabase(CVideoClass tempVideo)
{

	CtbVideo tbVideo;
	try{
		if (tbVideo.IsOpen())
			tbVideo.Close();
		if (!tbVideo.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}


	int length = m_vectVideo.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempVideo.m_Id = 1000;
		tempVideo.m_SortIndex = 1000;
	}
	else{
		tempVideo.m_Id = m_vectVideo[length - 1].m_Id + 1;
		tempVideo.m_SortIndex = m_vectVideo[length - 1].m_SortIndex + 1;
	}


	tempVideo.m_ProductionLineId = FindProLineId(tempVideo.m_strProductionLineName);
	tempVideo.m_ModuleId = FindProModuleId(tempVideo.m_strProductionLineName, tempVideo.m_strProcessModuleName);


	m_vectVideo.push_back(tempVideo);

	if (tbVideo.CanUpdate()){
		tbVideo.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbVideo.m_Id = tempVideo.m_Id;
		tbVideo.m_CreatedDateTime = time;
		tbVideo.m_LastUpdatedDateTime = time;
		tbVideo.m_ProductionLineName = tempVideo.m_strProductionLineName;
		tbVideo.m_ProcessModuleName = tempVideo.m_strProcessModuleName;
		tbVideo.m_VideoName = tempVideo.m_strVideoName;
		tbVideo.m_IPAddr = tempVideo.m_strIPAddr;
		tbVideo.m_Port = tempVideo.m_port;

		tbVideo.m_ProductionLineId = tempVideo.m_ProductionLineId;
		tbVideo.m_ProcessModuleId = tempVideo.m_ModuleId;
		tbVideo.m_SortIndex = tempVideo.m_SortIndex;

		tbVideo.Update();

	}

	tbVideo.Close();

}


void CDataProvider::AddDeviceParaToDatabase(CDevicePara tempDevicePara)
{
	CtbDevicePara tbDevicePara;
	try{
		if (tbDevicePara.IsOpen())
			tbDevicePara.Close();
		if (!tbDevicePara.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}


	int length = m_vectDevicePara.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempDevicePara.m_Id = 1000;
	}
	else{
		tempDevicePara.m_Id = m_vectDevicePara[length - 1].m_Id + 1;
	}

	tempDevicePara.m_ProductionLineId = FindProLineId(tempDevicePara.m_strProductionLineName);
	tempDevicePara.m_ProcessModuleId = FindProModuleId(tempDevicePara.m_strProductionLineName, tempDevicePara.m_strProcessModuleName);
	tempDevicePara.m_PlcId = FindPlcId(tempDevicePara.m_strPlcName);
	tempDevicePara.m_DeviceId = FindDeviceId(tempDevicePara.m_strProductionLineName, tempDevicePara.m_strProcessModuleName, tempDevicePara.m_strDeviceName);

	m_vectDevicePara.push_back(tempDevicePara);

	if (tbDevicePara.CanUpdate()){
		tbDevicePara.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbDevicePara.m_Id = tempDevicePara.m_Id;
		tbDevicePara.m_CreatedDateTime = time;
		tbDevicePara.m_LastUpdatedDateTime = time;
		tbDevicePara.m_ProductionLineName = tempDevicePara.m_strProductionLineName;
		tbDevicePara.m_ProcessModuleName = tempDevicePara.m_strProcessModuleName;
		tbDevicePara.m_PlcName = tempDevicePara.m_strPlcName;
		tbDevicePara.m_PLCId = tempDevicePara.m_PlcId;
		tbDevicePara.m_DeviceName = tempDevicePara.m_strDeviceName;
		tbDevicePara.m_DeviceId = tempDevicePara.m_DeviceId;
		tbDevicePara.m_ProductionLineId = tempDevicePara.m_ProductionLineId;
		tbDevicePara.m_ProcessModuleId = tempDevicePara.m_ProcessModuleId;
		tbDevicePara.m_ControlAddrIndex = tempDevicePara.m_strControlAddrIndex;
		tbDevicePara.m_ControlValue = tempDevicePara.m_ControlValue;
		tbDevicePara.m_StateValue = tempDevicePara.m_StateValue;
		tbDevicePara.m_StateAddrIndex = tempDevicePara.m_strStateAddrIndex;
		tbDevicePara.m_ParaName = tempDevicePara.m_strParaName;
		tbDevicePara.m_Description = tempDevicePara.m_strDescription;


		tbDevicePara.Update();

	}
	tbDevicePara.Close();
}


void CDataProvider::AddFaultParaToDatabase(CFaultPara tempFaultPara)
{
	CtbFaultPara tbFaultPara;
	try{
		if (tbFaultPara.IsOpen())
			tbFaultPara.Close();
		if (!tbFaultPara.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}


	int length = m_vectFaultPara.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempFaultPara.m_Id = 1000;
	}
	else{
		tempFaultPara.m_Id = m_vectFaultPara[length - 1].m_Id + 1;
	}

	tempFaultPara.m_ProductionLineId = FindProLineId(tempFaultPara.m_strProductionLineName);
	tempFaultPara.m_ProcessModuleId = FindProModuleId(tempFaultPara.m_strProductionLineName, tempFaultPara.m_strProcessName);
	tempFaultPara.m_DeviceId = FindDeviceId(tempFaultPara.m_strProductionLineName, tempFaultPara.m_strProcessName, tempFaultPara.m_strDeviceName);
	tempFaultPara.m_PLCId = FindPlcId(tempFaultPara.m_strPlcName);

	m_vectFaultPara.push_back(tempFaultPara);

	if (tbFaultPara.CanUpdate()){
		tbFaultPara.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbFaultPara.m_Id = tempFaultPara.m_Id;
		tbFaultPara.m_CreatedDateTime = time;
		tbFaultPara.m_LastUpdatedDateTime = time;
		tbFaultPara.m_ProductionLineName = tempFaultPara.m_strProductionLineName;
		tbFaultPara.m_ProcessModuleName = tempFaultPara.m_strProcessName;
		tbFaultPara.m_ProductionLineId = tempFaultPara.m_ProductionLineId;
		tbFaultPara.m_ProcessModuleId = tempFaultPara.m_ProcessModuleId;
		tbFaultPara.m_DeviceName = tempFaultPara.m_strDeviceName;
		tbFaultPara.m_DeviceId = tempFaultPara.m_DeviceId;
		tbFaultPara.m_PlcName = tempFaultPara.m_strPlcName;
		tbFaultPara.m_PLCId = tempFaultPara.m_PLCId;
		tbFaultPara.m_AddressIndex = tempFaultPara.m_strAddressIndex;
		tbFaultPara.m_ParaValue = tempFaultPara.m_ParaValue;
		tbFaultPara.m_ParaName = tempFaultPara.m_strParaName;
		tbFaultPara.m_Description = tempFaultPara.m_strDescription;

		tbFaultPara.Update();

	}

	tbFaultPara.Close();

}

void CDataProvider::AddProcessParaToDatabase(CProcessPara tempProcessPara)
{
	CtbProcessPara tbProcessPara;
	try{
		if (tbProcessPara.IsOpen())
			tbProcessPara.Close();
		if (!tbProcessPara.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}


	int length = m_vectProModulePara.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempProcessPara.m_Id = 1000;
	}
	else{
		tempProcessPara.m_Id = m_vectProModulePara[length - 1].m_Id + 1;
	}

	tempProcessPara.m_ProductionLineId = FindProLineId(tempProcessPara.m_strProductionLineName);
	tempProcessPara.m_ProcessModuleId = FindProModuleId(tempProcessPara.m_strProductionLineName, tempProcessPara.m_strProcessModuleName);
	tempProcessPara.m_PlcId = FindPlcId(tempProcessPara.m_strPlcName);

	m_vectProModulePara.push_back(tempProcessPara);

	if (tbProcessPara.CanUpdate()){
		tbProcessPara.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProcessPara.m_Id = tempProcessPara.m_Id;
		tbProcessPara.m_CreatedDateTime = time;
		tbProcessPara.m_LastUpdatedDateTime = time;
		tbProcessPara.m_ProductionLineName = tempProcessPara.m_strProductionLineName;
		tbProcessPara.m_ProcessModuleName = tempProcessPara.m_strProcessModuleName;
		tbProcessPara.m_ProductionLineId = tempProcessPara.m_ProductionLineId;
		tbProcessPara.m_ProcessModuleId = tempProcessPara.m_ProcessModuleId;
		tbProcessPara.m_PlcName = tempProcessPara.m_strPlcName;
		tbProcessPara.m_PLCId = tempProcessPara.m_PlcId;
		tbProcessPara.m_ReadAddressIndex = tempProcessPara.m_strReadAddrIndex;
		tbProcessPara.m_WriteAddressIndex = tempProcessPara.m_strWriteAddrIndex;
		tbProcessPara.m_Units = tempProcessPara.m_strUnit;
		tbProcessPara.m_AddressType = tempProcessPara.m_strAddressType;
		tbProcessPara.m_ParaValue = tempProcessPara.m_ParaValue;
		tbProcessPara.m_ParaName = tempProcessPara.m_strParaName;
		tbProcessPara.m_Description = tempProcessPara.m_strDescription;
		tbProcessPara.m_ValueType = tempProcessPara.m_ValueType;
		tbProcessPara.m_IsConfig = tempProcessPara.m_IsConfig;
		tbProcessPara.m_IsVisible = tempProcessPara.m_IsVisible;

		tbProcessPara.Update();

	}

	tbProcessPara.Close();

}

void CDataProvider::AddStateParaToDatabase(CStatePara tempStatePara)
{
	CtbStatePara tbStatePara;
	try{
		if (tbStatePara.IsOpen())
			tbStatePara.Close();
		if (!tbStatePara.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	int length = m_vectStatePara.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempStatePara.m_Id = 1000;
	}
	else{
		tempStatePara.m_Id = m_vectStatePara[length - 1].m_Id + 1;
	}

	tempStatePara.m_ProductionLineId = FindProLineId(tempStatePara.m_strProductionLineName);
	tempStatePara.m_ProcessModuleId = FindProModuleId(tempStatePara.m_strProductionLineName, tempStatePara.m_strProcessModuleName);
	tempStatePara.m_PlcId = FindPlcId(tempStatePara.m_strPlcName);


	m_vectStatePara.push_back(tempStatePara);

	if (tbStatePara.CanUpdate()){
		tbStatePara.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbStatePara.m_Id = tempStatePara.m_Id;
		tbStatePara.m_CreatedDateTime = time;
		tbStatePara.m_LastUpdatedDateTime = time;
		tbStatePara.m_ProductionLineName = tempStatePara.m_strProductionLineName;
		tbStatePara.m_ProcessModuleName = tempStatePara.m_strProcessModuleName;
		tbStatePara.m_ProductionLineId = tempStatePara.m_ProductionLineId;
		tbStatePara.m_ProcessModuleId = tempStatePara.m_ProcessModuleId;
		tbStatePara.m_PlcName = tempStatePara.m_strPlcName;
		tbStatePara.m_PLCId = tempStatePara.m_PlcId;
		tbStatePara.m_AddressIndex = tempStatePara.m_strAddressIndex;
		tbStatePara.m_ParaValue = tempStatePara.m_ParaValue;
		tbStatePara.m_ParaName = tempStatePara.m_strParaName;
		tbStatePara.m_Description = tempStatePara.m_strDescription;

		tbStatePara.Update();

	}

	tbStatePara.Close();


}


void CDataProvider::AddFormulaToDatabase(CFormulaClass tempFormula)
{
	CtbFormula tbFormula;
	try{
		if (tbFormula.IsOpen())
			tbFormula.Close();
		if (!tbFormula.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	int length = m_vectFormula.size();
	if (length == 0)//���õ�һ��ģ��ID
	{
		tempFormula.m_Id = 1000;

	}
	else{
		tempFormula.m_Id = m_vectFormula[length - 1].m_Id + 1;
	}

	tempFormula.m_FormulaId = FindFormulaId(tempFormula.m_strFormulaName);
	//tempFormula.m_ProductionLineId = FindProLineId(tempFormula.m_strProductionLineName);
	//tempFormula.m_strProcessParaName = FindProcessParaName(tempFormula.m_ProcessParaId);

	m_vectFormula.push_back(tempFormula);
	if (tbFormula.CanUpdate()){
		tbFormula.AddNew();
		CTime time = CTime::GetCurrentTime();
		tbFormula.m_Id = tempFormula.m_Id;
		tbFormula.m_CreatedDateTime = time;
		tbFormula.m_LastUpdatedDateTime = time;
		tbFormula.m_ProductionLineName = tempFormula.m_strProductionLineName;
		tbFormula.m_ProductionLineId = tempFormula.m_ProductionLineId;
		tbFormula.m_FormulaId = tempFormula.m_FormulaId;
		tbFormula.m_FormulaName = tempFormula.m_strFormulaName;
		tbFormula.m_Note = tempFormula.m_strNote;
		tbFormula.m_ParaValueUnit = tempFormula.m_strParaValueUnit;
		tbFormula.m_DefaultValue = tempFormula.m_DefaultValue;
		tbFormula.m_ProcessParaId = tempFormula.m_ProcessParaId;
		tbFormula.m_ProcessParaName = tempFormula.m_strProcessParaName;
		tbFormula.m_IsDefaultFormula = tempFormula.m_IsDefaultFormula;
		tbFormula.m_IsCurrentFormula = tempFormula.m_IsCurrentFormula;
		tbFormula.Update();
	}

	tbFormula.Close();
}

//���Ϊ��һ���䷽�ĵ�һ����¼�������FormulaIDΪ1000��������ͬһ���䷽���򷵻�ͬһ�䷽��ID
//��Ϊ�½��䷽�����������һ��FormulaID
int CDataProvider::FindFormulaId(CString FormulaName)
{
	int len = m_vectFormula.size();
	if (len == 0)
	{
		return 1000;
	}
	else{

		for (int i = 0; i < m_vectFormula.size(); i++)
		{
			if (FormulaName == m_vectFormula[i].m_strFormulaName)
			{
				return m_vectFormula[i].m_FormulaId;
			}
		}
		return m_vectFormula[len - 1].m_FormulaId + 1;
	}
}

void CDataProvider::ReadDeviceParaFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbDevicePara order by Id"));

	CtbDevicePara  tbDevicePara;
	try{
		if (tbDevicePara.IsOpen())
			tbDevicePara.Close();
		if (!tbDevicePara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbDevicePara.IsBOF())
	{
		return;
	}

	m_vectDevicePara.clear();
	CDevicePara tempDevicePara;
	tbDevicePara.MoveFirst();
	while (!tbDevicePara.IsEOF()){
		tempDevicePara.m_Id = tbDevicePara.m_Id;
		tempDevicePara.m_strCreatedDateTime = tbDevicePara.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempDevicePara.m_strLastUpdatedDateTime = tbDevicePara.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempDevicePara.m_strProductionLineName = tbDevicePara.m_ProductionLineName;
		tempDevicePara.m_strProcessModuleName = tbDevicePara.m_ProcessModuleName;
		tempDevicePara.m_strPlcName = tbDevicePara.m_PlcName;

		tempDevicePara.m_strDeviceName = tbDevicePara.m_DeviceName;
		tempDevicePara.m_DeviceId = tbDevicePara.m_DeviceId;
		tempDevicePara.m_PlcId = tbDevicePara.m_PLCId;
		tempDevicePara.m_ProductionLineId = tbDevicePara.m_ProductionLineId;
		tempDevicePara.m_ProcessModuleId = tbDevicePara.m_ProcessModuleId;
		tempDevicePara.m_strControlAddrIndex = tbDevicePara.m_ControlAddrIndex;
		tempDevicePara.m_ControlValue = tbDevicePara.m_ControlValue;
		tempDevicePara.m_StateValue = tbDevicePara.m_StateValue;
		tempDevicePara.m_strStateAddrIndex = tbDevicePara.m_StateAddrIndex;
		tempDevicePara.m_strParaName = tbDevicePara.m_ParaName;
		tempDevicePara.m_strDescription = tbDevicePara.m_Description;

		m_vectDevicePara.push_back(tempDevicePara);
		tbDevicePara.MoveNext();
	}

	tbDevicePara.Close();
}

void CDataProvider::ReadFaultParaFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbFaultPara order by Id"));

	CtbFaultPara  tbFaultPara;
	try{
		if (tbFaultPara.IsOpen())
			tbFaultPara.Close();
		if (!tbFaultPara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbFaultPara.IsBOF())
	{
		return;
	}
	m_vectFaultPara.clear();
	CFaultPara tempFaultPara;

	tbFaultPara.MoveFirst();
	while (!tbFaultPara.IsEOF()){

		tempFaultPara.m_Id = tbFaultPara.m_Id;
		tempFaultPara.m_strCreatedDateTime = tbFaultPara.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempFaultPara.m_strLastUpdatedDateTime = tbFaultPara.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempFaultPara.m_strProductionLineName = tbFaultPara.m_ProductionLineName;
		tempFaultPara.m_strProcessName = tbFaultPara.m_ProcessModuleName;
		tempFaultPara.m_ProductionLineId = tbFaultPara.m_ProductionLineId;
		tempFaultPara.m_ProcessModuleId = tbFaultPara.m_ProcessModuleId;
		tempFaultPara.m_strDeviceName = tbFaultPara.m_DeviceName;
		tempFaultPara.m_DeviceId = tbFaultPara.m_DeviceId;
		tempFaultPara.m_strPlcName = tbFaultPara.m_PlcName;
		tempFaultPara.m_PLCId = tbFaultPara.m_PLCId;
		tempFaultPara.m_strAddressIndex = tbFaultPara.m_AddressIndex;
		tempFaultPara.m_ParaValue = tbFaultPara.m_ParaValue;
		tempFaultPara.m_strParaName = tbFaultPara.m_ParaName;
		tempFaultPara.m_strDescription = tbFaultPara.m_Description;

		m_vectFaultPara.push_back(tempFaultPara);
		tbFaultPara.MoveNext();
	}
	tbFaultPara.Close();

}

void CDataProvider::ReadProcessParaFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbProcessPara order by Id"));

	CtbProcessPara  tbProcessPara;
	try{
		if (tbProcessPara.IsOpen())
			tbProcessPara.Close();
		if (!tbProcessPara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProcessPara.IsBOF())
	{
		return;
	}

	m_vectProModulePara.clear();
	CProcessPara tempProcessPara;
	tbProcessPara.MoveFirst();
	while (!tbProcessPara.IsEOF()){

		tempProcessPara.m_Id = tbProcessPara.m_Id;
		tempProcessPara.m_strCreatedDateTime = tbProcessPara.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempProcessPara.m_strLastUpdatedDateTime = tbProcessPara.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempProcessPara.m_strProductionLineName = tbProcessPara.m_ProductionLineName;
		tempProcessPara.m_strProcessModuleName = tbProcessPara.m_ProcessModuleName;
		tempProcessPara.m_ProductionLineId = tbProcessPara.m_ProductionLineId;
		tempProcessPara.m_ProcessModuleId = tbProcessPara.m_ProcessModuleId;
		tempProcessPara.m_strPlcName = tbProcessPara.m_PlcName;
		tempProcessPara.m_PlcId = tbProcessPara.m_PLCId;
		tempProcessPara.m_strReadAddrIndex = tbProcessPara.m_ReadAddressIndex;
		tempProcessPara.m_strWriteAddrIndex = tbProcessPara.m_WriteAddressIndex;
		tempProcessPara.m_strUnit = tbProcessPara.m_Units;
		tempProcessPara.m_strAddressType = tbProcessPara.m_AddressType;
		tempProcessPara.m_ParaValue = tbProcessPara.m_ParaValue;
		tempProcessPara.m_strParaName = tbProcessPara.m_ParaName;
		tempProcessPara.m_strDescription = tbProcessPara.m_Description;
		tempProcessPara.m_ValueType = tbProcessPara.m_ValueType;
		tempProcessPara.m_IsConfig = tbProcessPara.m_IsConfig;
		tempProcessPara.m_IsVisible = tbProcessPara.m_IsVisible;

		m_vectProModulePara.push_back(tempProcessPara);
		tbProcessPara.MoveNext();
	}
	tbProcessPara.Close();

}

void CDataProvider::ReadStateParaFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbStatePara order by Id"));

	CtbStatePara  tbStatePara;
	try{
		if (tbStatePara.IsOpen())
			tbStatePara.Close();
		if (!tbStatePara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbStatePara.IsBOF())
	{
		return;
	}
	m_vectStatePara.clear();
	CStatePara tempStatePara;
	tbStatePara.MoveFirst();
	while (!tbStatePara.IsEOF()){
		tempStatePara.m_Id = tbStatePara.m_Id;
		tempStatePara.m_strCreatedDateTime = tbStatePara.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempStatePara.m_strLastUpdateDateTime = tbStatePara.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempStatePara.m_strProductionLineName = tbStatePara.m_ProductionLineName;
		tempStatePara.m_strProcessModuleName = tbStatePara.m_ProcessModuleName;
		tempStatePara.m_ProductionLineId = tbStatePara.m_ProductionLineId;
		tempStatePara.m_ProcessModuleId = tbStatePara.m_ProcessModuleId;
		tempStatePara.m_strPlcName = tbStatePara.m_PlcName;
		tempStatePara.m_PlcId = tbStatePara.m_PLCId;
		tempStatePara.m_strAddressIndex = tbStatePara.m_AddressIndex;
		tempStatePara.m_ParaValue = tbStatePara.m_ParaValue;
		tempStatePara.m_strParaName = tbStatePara.m_ParaName;
		tempStatePara.m_strDescription = tbStatePara.m_Description;

		m_vectStatePara.push_back(tempStatePara);
		tbStatePara.MoveNext();
	}
	tbStatePara.Close();



}

void CDataProvider::ReadLoginUserFormDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbLoginUser order by Id"));

	CtbLoginUser tbLoginUser;
	try{
		if (tbLoginUser.IsOpen())
			tbLoginUser.Close();
		if (!tbLoginUser.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbLoginUser.IsBOF())
	{
		return;
	}


	m_vectLoginUser.clear();

	CLoginUser tempLoginUser;
	tbLoginUser.MoveFirst();
	while (!tbLoginUser.IsEOF()){
		//��ȡ���Ա���� Ψһ�� �û�ID
		tempLoginUser.m_Id = tbLoginUser.m_Id;
		tempLoginUser.m_strCreatedDateTime = tbLoginUser.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempLoginUser.m_strLastUpdatedDateTime = tbLoginUser.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempLoginUser.m_strLastLoginInTime = tbLoginUser.m_LastLoginInTime.Format(_T("%Y-%m-%d %H:%M:%S"));
		tempLoginUser.m_strLoginName = tbLoginUser.m_LoginName;
		tempLoginUser.m_strLoginPassWd = tbLoginUser.m_LoginPassWd;

		tempLoginUser.m_PermissionLevel = tbLoginUser.m_PermissionLevel;
		tempLoginUser.m_IsRememberPasswd = tbLoginUser.m_IsRememberPasswd;
		tempLoginUser.m_IsAutoLogin = tbLoginUser.m_IsAutoLogin;

		m_vectLoginUser.push_back(tempLoginUser);

		tbLoginUser.MoveNext();
	}

	tbLoginUser.Close();
}


void CDataProvider::ReadUserFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbUser order by Id"));

	CtbUser tbUser;
	try{
		if (tbUser.IsOpen())
			tbUser.Close();
		if (!tbUser.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbUser.IsBOF())
	{
		return;
	}

	m_vectUser.clear();
	CUserClass tempUser;
	tbUser.MoveFirst();
	while (!tbUser.IsEOF()){
		//��ȡ���Ա���� Ψһ�� �û�ID//
		tempUser.m_UserId = tbUser.m_Id;
		tempUser.m_strUserName = tbUser.m_UserName;
		tempUser.m_strUserPasswd = tbUser.m_UserPassword;
		tempUser.m_strUserCode = tbUser.m_UserCode;
		tempUser.m_strNote = tbUser.m_Note;
		m_vectUser.push_back(tempUser);

		tbUser.MoveNext();

	}

	tbUser.Close();

}



void CDataProvider::ReadProLineFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbProductionLine order by SortIndex"));

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProductionLine.IsBOF())
	{
		return;
	}

	m_vectProductionLine.clear();
	CProductionLineClass tempProductionLine;
	tbProductionLine.MoveFirst();
	while (!tbProductionLine.IsEOF()){

		tempProductionLine.m_Id = tbProductionLine.m_Id;
		tempProductionLine.m_strLineName = tbProductionLine.m_LineName;
		tempProductionLine.m_strCapacity = tbProductionLine.m_Capacity;
		tempProductionLine.m_strDescription = tbProductionLine.m_Description;

		tempProductionLine.m_UserId = tbProductionLine.m_UserId;
		tempProductionLine.m_SortIndex = tbProductionLine.m_SortIndex;

		m_vectProductionLine.push_back(tempProductionLine);
		tbProductionLine.MoveNext();
	}

	tbProductionLine.Close();

}


void CDataProvider::ReadProModuleFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbProcessModule order by SortIndex"));

	CtbProcessModule  tbProcessModule;
	try{
		if (tbProcessModule.IsOpen())
			tbProcessModule.Close();
		if (!tbProcessModule.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProcessModule.IsBOF())
	{
		return;
	}

	m_vectProcessModule.clear();
	CProcessModuleClass tempModule;
	tbProcessModule.MoveFirst();
	while (!tbProcessModule.IsEOF()){

		tempModule.m_Id = tbProcessModule.m_Id;
		tempModule.m_strProductionLineName = tbProcessModule.m_ProductionLineName;
		tempModule.m_strProcessModuleName = tbProcessModule.m_ModuleName;
		tempModule.m_strDescription = tbProcessModule.m_Description;

		tempModule.m_ProcessLineId = tbProcessModule.m_ProductionLineId;

		tempModule.m_UserId = tbProcessModule.m_UserId;
		tempModule.m_SortIndex = tbProcessModule.m_SortIndex;

		m_vectProcessModule.push_back(tempModule);
		tbProcessModule.MoveNext();
	}

	tbProcessModule.Close();

}


void CDataProvider::ReadDeviceFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbDevice order by SortIndex"));

	CtbDevice  tbDevice;
	try{
		if (tbDevice.IsOpen())
			tbDevice.Close();
		if (!tbDevice.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	if (tbDevice.IsEOF())
	{
		return;
	}

	m_vectDevice.clear();
	CDeviceClass tempDevice;
	tbDevice.MoveFirst();
	while (!tbDevice.IsEOF()){
		tempDevice.m_Id = tbDevice.m_Id;
		tempDevice.m_strProductionLineName = tbDevice.m_ProductionLineName;
		tempDevice.m_strProcessModuleName = tbDevice.m_ProcessModuleName;
		tempDevice.m_strDeviceName = tbDevice.m_DeviceName;
		tempDevice.m_strDeviceType = tbDevice.m_DeviceType;
		tempDevice.m_ProcessModuleId = tbDevice.m_ProcessModuleId;
		tempDevice.m_ProductionLineId = tbDevice.m_ProductionLineId;
		tempDevice.m_SortIndex = tbDevice.m_SortIndex;

		m_vectDevice.push_back(tempDevice);
		tbDevice.MoveNext();
	}

	tbDevice.Close();

}





void CDataProvider::ReadPlcFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbPLc order by SortIndex"));

	CtbPLc  tbPlc;
	try{
		if (tbPlc.IsOpen())
			tbPlc.Close();
		if (!tbPlc.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbPlc.IsEOF())
	{
		return;
	}

	m_vectPlc.clear();
	CPlcClass tempPlc;
	tbPlc.MoveFirst();
	while (!tbPlc.IsEOF()){

		tempPlc.m_Id = tbPlc.m_Id;
		tempPlc.m_strProductionLineName = tbPlc.m_ProductionLineName;
		tempPlc.m_ProductionLineId = tbPlc.m_ProductionLineId;

		tempPlc.m_strPlcName = tbPlc.m_PLCName;
		tempPlc.m_strIPAddr = tbPlc.m_strIPAddr;
		tempPlc.m_strDescription = tbPlc.m_Description;
		tempPlc.m_ReadStartAddr = tbPlc.m_ReadStartAddr;
		tempPlc.m_ReadLength = tbPlc.m_ReadLength;
		tempPlc.m_WriteStartAddr = tbPlc.m_WriteStartAddr;
		tempPlc.m_WriteLength = tbPlc.m_WriteLength;

		tempPlc.m_SortIndex = tbPlc.m_SortIndex;

		m_vectPlc.push_back(tempPlc);
		tbPlc.MoveNext();
	}

	tbPlc.Close();


}




void CDataProvider::ReadVideoFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbVideo order by SortIndex"));

	CtbVideo  tbVideo;
	try{
		if (tbVideo.IsOpen())
			tbVideo.Close();
		if (!tbVideo.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbVideo.IsEOF())
	{
		tbVideo.Close();
		return;
	}

	m_vectVideo.clear();
	CVideoClass tempVideo;
	tbVideo.MoveFirst();
	while (!tbVideo.IsEOF()){

		tempVideo.m_Id = tbVideo.m_Id;
		tempVideo.m_strProductionLineName = tbVideo.m_ProductionLineName;
		tempVideo.m_strProcessModuleName = tbVideo.m_ProcessModuleName;
		tempVideo.m_strIPAddr = tbVideo.m_IPAddr;
		tempVideo.m_strVideoName = tbVideo.m_VideoName;

		tempVideo.m_port = tbVideo.m_Port;

		tempVideo.m_ProductionLineId = tbVideo.m_ProductionLineId;
		tempVideo.m_ModuleId = tbVideo.m_ProcessModuleId;
		tempVideo.m_SortIndex = tbVideo.m_SortIndex;

		m_vectVideo.push_back(tempVideo);
		tbVideo.MoveNext();
	}

	tbVideo.Close();


}

void CDataProvider::ReadFormulaFormDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbFormula order by Id"));

	CtbFormula  tbFormula;
	try{
		if (tbFormula.IsOpen())
			tbFormula.Close();
		if (!tbFormula.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbFormula.IsEOF())
	{
		tbFormula.Close();
		return;
	}

	m_vectFormula.clear();
	CFormulaClass tempFormula;
	tbFormula.MoveFirst();
	while (!tbFormula.IsEOF()){

		tempFormula.m_Id = tbFormula.m_Id;

		tempFormula.m_strProductionLineName = tbFormula.m_ProductionLineName;
		tempFormula.m_ProductionLineId = tbFormula.m_ProductionLineId;
		tempFormula.m_FormulaId = tbFormula.m_FormulaId;
		tempFormula.m_strFormulaName = tbFormula.m_FormulaName;
		tempFormula.m_strNote = tbFormula.m_Note;
		tempFormula.m_strParaValueUnit = tbFormula.m_ParaValueUnit;
		tempFormula.m_DefaultValue = tbFormula.m_DefaultValue;
		tempFormula.m_ProcessParaId = tbFormula.m_ProcessParaId;
		tempFormula.m_strProcessParaName = tbFormula.m_ProcessParaName;

		tempFormula.m_IsDefaultFormula = tbFormula.m_IsDefaultFormula;
		tempFormula.m_IsCurrentFormula = tbFormula.m_IsCurrentFormula;

		m_vectFormula.push_back(tempFormula);
		tbFormula.MoveNext();
	}

	tbFormula.Close();
}



/*�������ܣ�ɾ��ö������dbTable�������ṩ�ĸ����������
������DeleteDbTable(tbProductionLine)ɾ�������߱�������������е���
*/

int CDataProvider::DeleteDbTable(enumDBTABLE dbTable)
{
	CString strsql;

	switch (dbTable)
	{
	case CDataProvider::tbUser:
		strsql.Format(_T("DELETE FROM tbUser"));
		m_vectUser.clear();
		break;
	case CDataProvider::tbProductionLine:
		strsql.Format(_T("DELETE FROM tbProductionLine"));
		m_vectProductionLine.clear();
		break;
	case CDataProvider::tbProcessModule:
		strsql.Format(_T("DELETE FROM tbProcessModule"));
		m_vectProcessModule.clear();
		break;
	case CDataProvider::tbDevice:
		strsql.Format(_T("DELETE FROM tbDevice"));
		m_vectDevice.clear();
		break;
	case CDataProvider::tbPLc:
		strsql.Format(_T("DELETE FROM tbPLc"));
		m_vectPlc.clear();
		break;
	case CDataProvider::tbVideo:
		strsql.Format(_T("DELETE FROM tbVideo"));
		m_vectVideo.clear();
		break;
	case CDataProvider::tbLoginUser:
		strsql.Format(_T("DELETE FROM tbLoginUser"));
		m_vectLoginUser.clear();
		break;
	case CDataProvider::tbDevicePara:
		strsql.Format(_T("DELETE FROM tbDevicePara"));
		m_vectDevicePara.clear();
		break;
	case CDataProvider::tbStatePara:
		strsql.Format(_T("DELETE FROM tbStatePara"));
		m_vectStatePara.clear();
		break;
	case CDataProvider::tbFaultPara:
		strsql.Format(_T("DELETE FROM tbFaultPara"));
		m_vectFaultPara.clear();
		break;
	case CDataProvider::tbProcessPara:
		strsql.Format(_T("DELETE FROM tbProcessPara"));
		m_vectProModulePara.clear();
		break;
	case CDataProvider::tbFormula:
		strsql.Format(_T("DELETE FROM tbFormula"));
		m_vectFormula.clear();
		break;
	default:
		break;
	}

	ExecutionSQL(strsql);

	return 0;
}


/*�������ܣ��ض�ɾ��ö������dbTable�ṩ�ı���ɾ���ض�ID����*/

int CDataProvider::DeleteDbTableItem(enumDBTABLE dbTable, int Id)
{
	CString strsql;

	switch (dbTable)
	{
	case CDataProvider::tbUser:
		strsql.Format(_T("DELETE FROM tbUser WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbProductionLine:
		strsql.Format(_T("DELETE FROM tbProductionLine WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbProcessModule:
		strsql.Format(_T("DELETE FROM tbProcessModule WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbDevice:
		strsql.Format(_T("DELETE FROM tbDevice WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbPLc:
		strsql.Format(_T("DELETE FROM tbPLc WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbVideo:
		strsql.Format(_T("DELETE FROM tbVideo WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbLoginUser:
		strsql.Format(_T("DELETE FROM tbLoginUser WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbDevicePara:
		strsql.Format(_T("DELETE FROM tbDevicePara WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbFaultPara:
		strsql.Format(_T("DELETE FROM tbFaultPara WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbProcessPara:
		strsql.Format(_T("DELETE FROM tbProcessPara WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbStatePara:
		strsql.Format(_T("DELETE FROM tbStatePara WHERE Id = '%d'"), Id);
		break;
	case CDataProvider::tbFormula:
		strsql.Format(_T("DELETE FROM tbFormula WHERE Id = '%d'"), Id);
		break;
	default:
		break;
	}

	ExecutionSQL(strsql);
	return 0;
}



/*
����˵�������޸Ķ�Ӧ��m_vect+��Ӧ���е�ֵ���ٵ��ô˺������޸����ݿ��е�ֵ
�������ܣ���ö������dbDBTABLE �еļ������У��޸��ض�ID����Ŀ��Ӧ����Ϣ
*/
int CDataProvider::UpdateTableItem(enumDBTABLE dbTable, int Id)
{
	CString strsql;
	CProductionLineClass tempProLine;
	CProcessModuleClass tempModule;
	CDeviceClass    tempDevice;
	CPlcClass      tempPlc;
	CVideoClass    tempVideo;

	CLoginUser tempLoginUser;
	CDevicePara tempDevicePara;
	CFaultPara tempFaultPara;
	CProcessPara tempProcessPara;
	CStatePara tempStatePara;
	CFormulaClass tempFormula;

	int i = 0;

	switch (dbTable)
	{
	case CDataProvider::tbUser: //�û�����һ��
		strsql.Format(_T("UPDATE tbUser SET LastUpdatedDateTime=getdate(), UserName = '%s',UserPassword='%s',UserCode='%s',Note='%s' WHERE Id ='%d'"),
			m_vectUser[0].m_strUserName, m_vectUser[0].m_strUserPasswd,
			m_vectUser[0].m_strUserCode, m_vectUser[0].m_strNote, Id);
		break;
	case CDataProvider::tbProductionLine:

		for (i = 0; i < m_vectProductionLine.size(); i++)
		{
			if (Id == m_vectProductionLine[i].m_Id)
			{
				tempProLine = m_vectProductionLine[i];
				break;
			}

		}
		strsql.Format(_T("UPDATE tbProductionLine SET LastUpdatedDateTime=getdate(), LineName = '%s',Capacity='%s',Description='%s',SortIndex='%d' WHERE Id = '%d'"),
			tempProLine.m_strLineName,
			tempProLine.m_strCapacity,
			tempProLine.m_strDescription,
			tempProLine.m_SortIndex,
			Id);
		break;
	case CDataProvider::tbProcessModule:
		for (i = 0; i < m_vectProcessModule.size(); i++)
		{
			if (Id == m_vectProcessModule[i].m_Id)
			{
				tempModule = m_vectProcessModule[i];
				break;
			}

		}
		tempModule.m_ProcessLineId = FindProLineId(tempModule.m_strProductionLineName);
		m_vectProcessModule[i] = tempModule;
		strsql.Format(_T("UPDATE tbProcessModule SET LastUpdatedDateTime=getdate(), ModuleName = '%s',ProductionLineName='%s',Description='%s',ProductionLineId='%d',SortIndex='%d' WHERE Id = '%d'"),
			tempModule.m_strProcessModuleName,
			tempModule.m_strProductionLineName,
			tempModule.m_strDescription,
			tempModule.m_ProcessLineId,
			tempModule.m_SortIndex,
			Id);
		break;
	case CDataProvider::tbDevice:
		for (i = 0; i < m_vectDevice.size(); i++)
		{
			if (Id == m_vectDevice[i].m_Id)
			{
				tempDevice = m_vectDevice[i];
				break;
			}
		}
		tempDevice.m_ProductionLineId = FindProLineId(tempDevice.m_strProductionLineName);
		tempDevice.m_ProcessModuleId = FindProModuleId(tempDevice.m_strProductionLineName, tempDevice.m_strProcessModuleName);
		m_vectDevice[i] = tempDevice;

		strsql.Format(_T("UPDATE tbDevice  SET LastUpdatedDateTime=getdate(), ProductionLineName='%s',ProcessModuleName = '%s',ProductionLineId='%d',ProcessModuleId='%d',DeviceName='%s',DeviceType='%s',SortIndex='%d' WHERE Id = '%d'"),
			tempDevice.m_strProductionLineName,
			tempDevice.m_strProcessModuleName,
			tempDevice.m_ProductionLineId,
			tempDevice.m_ProcessModuleId,
			tempDevice.m_strDeviceName,
			tempDevice.m_strDeviceType,
			tempDevice.m_SortIndex,
			Id);

		break;
	case CDataProvider::tbPLc:
		for (i = 0; i < m_vectPlc.size(); i++)
		{
			if (Id == m_vectPlc[i].m_Id)
			{
				tempPlc = m_vectPlc[i];
				break;
			}

		}
		strsql.Format(_T("UPDATE tbPLc SET LastUpdatedDateTime=getdate(), ProductionLineName = '%s',PLCName='%s',strIPAddr='%s',ReadStartAddr='%d',ReadLength='%d',WriteStartAddr='%d',WriteLength='%d',Description='%s',SortIndex='%d' WHERE Id = '%d'"),
			tempPlc.m_strProductionLineName, tempPlc.m_strPlcName,
			tempPlc.m_strIPAddr,
			tempPlc.m_ReadStartAddr,
			tempPlc.m_ReadLength,
			tempPlc.m_WriteStartAddr,
			tempPlc.m_WriteLength,
			tempPlc.m_strDescription,
			tempPlc.m_SortIndex,
			Id);
		break;
	case CDataProvider::tbVideo:
		for (i = 0; i < m_vectVideo.size(); i++)
		{
			if (Id == m_vectVideo[i].m_Id)
			{
				tempVideo = m_vectVideo[i];
				break;
			}

		}
		tempVideo.m_ProductionLineId = FindProLineId(tempVideo.m_strProductionLineName);
		tempVideo.m_ModuleId = FindProModuleId(tempVideo.m_strProductionLineName, tempVideo.m_strProcessModuleName);
		m_vectVideo[i] = tempVideo;

		strsql.Format(_T("UPDATE tbVideo SET LastUpdatedDateTime=getdate(), ProductionLineName = '%s',ProcessModuleName='%s',ProductionLineId='%d',ProcessModuleId='%d',VideoName='%s',IPAddr='%s',SortIndex='%d' WHERE Id = '%d'"),
			tempVideo.m_strProductionLineName,
			tempVideo.m_strProcessModuleName,
			tempVideo.m_ProductionLineId,
			tempVideo.m_ModuleId,
			tempVideo.m_strVideoName,
			tempVideo.m_strIPAddr,
			tempVideo.m_SortIndex,
			Id);
		break;

	case CDataProvider::tbLoginUser:
		for (i = 0; i < m_vectLoginUser.size(); i++)
		{
			if (Id == m_vectLoginUser[i].m_Id)
			{
				tempLoginUser = m_vectLoginUser[i];
				break;
			}
		}

		strsql.Format(_T("UPDATE tbLoginUser SET  LastUpdatedDateTime=getdate(), LoginName = '%s',LoginPassWd='%s',PermissionLevel='%d',IsAutoLogin='%d',IsRememberPasswd='%d' WHERE Id = '%d'"),
			tempLoginUser.m_strLoginName,
			tempLoginUser.m_strLoginPassWd,
			tempLoginUser.m_PermissionLevel,
			tempLoginUser.m_IsAutoLogin,
			tempLoginUser.m_IsRememberPasswd,
			Id);
		break;

	case CDataProvider::tbDevicePara:
		for (i = 0; i < m_vectDevicePara.size(); i++)
		{
			if (Id == m_vectDevicePara[i].m_Id)
			{
				tempDevicePara = m_vectDevicePara[i];
				break;
			}

		}
		tempDevicePara.m_ProductionLineId = FindProLineId(tempDevicePara.m_strProductionLineName);
		tempDevicePara.m_ProcessModuleId = FindProModuleId(tempDevicePara.m_strProductionLineName, tempDevicePara.m_strProcessModuleName);
		tempDevicePara.m_DeviceId = FindDeviceId(tempDevicePara.m_strProductionLineName, tempDevicePara.m_strProcessModuleName, tempDevicePara.m_strDeviceName);
		tempDevicePara.m_PlcId = FindPlcId(tempDevicePara.m_strPlcName);
		m_vectDevicePara[i] = tempDevicePara;

		strsql.Format(_T("UPDATE tbDevicePara SET LastUpdatedDateTime=getdate(), ProductionLineId='%d',ProcessModuleId='%d',PLCId='%d',DeviceId='%d',ProductionLineName='%s',ProcessModuleName='%s',PlcName='%s',DeviceName='%s',ParaName='%s',ControlValue='%d',StateValue='%d',ControlAddrIndex='%s',StateAddrIndex='%s',Description='%s' WHERE Id='%d'"),
			tempDevicePara.m_ProductionLineId,
			tempDevicePara.m_ProcessModuleId,
			tempDevicePara.m_PlcId,
			tempDevicePara.m_DeviceId,
			tempDevicePara.m_strProductionLineName,
			tempDevicePara.m_strProcessModuleName,
			tempDevicePara.m_strPlcName,
			tempDevicePara.m_strDeviceName,
			tempDevicePara.m_strParaName,
			tempDevicePara.m_ControlValue,
			tempDevicePara.m_StateValue,
			tempDevicePara.m_strControlAddrIndex,
			tempDevicePara.m_strStateAddrIndex,
			tempDevicePara.m_strDescription,
			Id);
		break;

	case CDataProvider::tbFaultPara:
		for (i = 0; i < m_vectFaultPara.size(); i++)
		{
			if (Id == m_vectFaultPara[i].m_Id)
			{
				tempFaultPara = m_vectFaultPara[i];
				break;
			}

		}
		tempFaultPara.m_ProductionLineId = FindProLineId(tempFaultPara.m_strProductionLineName);
		tempFaultPara.m_ProcessModuleId = FindProModuleId(tempFaultPara.m_strProductionLineName, tempFaultPara.m_strProcessName);
		tempFaultPara.m_DeviceId = FindDeviceId(tempDevicePara.m_strProductionLineName, tempFaultPara.m_strProcessName, tempFaultPara.m_strDeviceName);
		tempFaultPara.m_PLCId = FindPlcId(tempFaultPara.m_strPlcName);

		m_vectFaultPara[i] = tempFaultPara;

		strsql.Format(_T("UPDATE tbFaultPara SET LastUpdatedDateTime=getdate(), ProductionLineId='%d',ProcessModuleId='%d',PLCId='%d',DeviceId='%d',ProductionLineName='%s',ProcessModuleName='%s',PlcName='%s',DeviceName='%s',ParaName='%s',ParaValue='%d',AddressIndex='%s',Description='%s' WHERE Id='%d'"),
			tempFaultPara.m_ProductionLineId,
			tempFaultPara.m_ProcessModuleId,
			tempFaultPara.m_PLCId,
			tempFaultPara.m_DeviceId,
			tempFaultPara.m_strProductionLineName,
			tempFaultPara.m_strProcessName,
			tempFaultPara.m_strPlcName,
			tempFaultPara.m_strDeviceName,
			tempFaultPara.m_strParaName,
			tempFaultPara.m_ParaValue,
			tempFaultPara.m_strAddressIndex,
			tempFaultPara.m_strDescription,
			Id);
		break;
	case tbProcessPara:
		for (i = 0; i < m_vectProModulePara.size(); i++)
		{
			if (Id == m_vectProModulePara[i].m_Id)
			{
				tempProcessPara = m_vectProModulePara[i];
				break;
			}
		}
		tempProcessPara.m_ProductionLineId = FindProLineId(tempProcessPara.m_strProductionLineName);
		tempProcessPara.m_ProcessModuleId = FindProModuleId(tempProcessPara.m_strProductionLineName, tempProcessPara.m_strProcessModuleName);
		tempProcessPara.m_PlcId = FindPlcId(tempProcessPara.m_strPlcName);
		m_vectProModulePara[i] = tempProcessPara;

		strsql.Format(_T("UPDATE tbProcessPara SET LastUpdatedDateTime=getdate(), ProductionLineId='%d',ProcessModuleId='%d',PLCId='%d',ProductionLineName='%s',ProcessModuleName='%s',PlcName='%s',ParaName='%s',ParaValue='%f',IsConfig='%d',IsVisible='%d',ReadAddressIndex='%s',WriteAddressIndex='%s',Units='%s',ValueType='%d',AddressType='%s',Description='%s' WHERE Id='%d'"),
			tempProcessPara.m_ProductionLineId,
			tempProcessPara.m_ProcessModuleId,
			tempProcessPara.m_PlcId,
			tempProcessPara.m_strProductionLineName,
			tempProcessPara.m_strProcessModuleName,
			tempProcessPara.m_strPlcName,
			tempProcessPara.m_strParaName,
			tempProcessPara.m_ParaValue,
			tempProcessPara.m_IsConfig,
			tempProcessPara.m_IsVisible,
			tempProcessPara.m_strReadAddrIndex,
			tempProcessPara.m_strWriteAddrIndex,
			tempProcessPara.m_strUnit,
			tempProcessPara.m_ValueType,
			tempProcessPara.m_strAddressType,
			tempProcessPara.m_strDescription,
			Id);
		break;

	case tbStatePara:
		for (i = 0; i < m_vectStatePara.size(); i++)
		{
			if (Id == m_vectStatePara[i].m_Id)
			{
				tempStatePara = m_vectStatePara[i];
				break;
			}
		}
		tempStatePara.m_ProductionLineId = FindProLineId(tempStatePara.m_strProductionLineName);
		tempStatePara.m_ProcessModuleId = FindProModuleId(tempStatePara.m_strProductionLineName, tempStatePara.m_strProcessModuleName);
		tempStatePara.m_PlcId = FindPlcId(tempStatePara.m_strPlcName);

		m_vectStatePara[i] = tempStatePara;

		strsql.Format(_T("UPDATE tbStatePara SET LastUpdatedDateTime=getdate(), ProductionLineId='%d',ProcessModuleId='%d',PLCId='%d',ProductionLineName='%s',ProcessModuleName='%s',PlcName='%s',ParaName='%s',ParaValue='%d',AddressIndex='%s',Description='%s' WHERE Id='%d'"),
			tempStatePara.m_ProductionLineId,
			tempStatePara.m_ProcessModuleId,
			tempStatePara.m_PlcId,
			tempStatePara.m_strProductionLineName,
			tempStatePara.m_strProcessModuleName,
			tempStatePara.m_strPlcName,
			tempStatePara.m_strParaName,
			tempStatePara.m_ParaValue,
			tempStatePara.m_strAddressIndex,
			tempStatePara.m_strDescription,
			Id);
		break;
	case tbFormula:
		for (i = 0; i < m_vectFormula.size(); i++)
		{
			if (Id == m_vectFormula[i].m_Id)
			{
				tempFormula = m_vectFormula[i];
				break;
			}
		}
		tempFormula.m_ProductionLineId = FindProLineId(tempFormula.m_strProductionLineName);

		tempFormula.m_FormulaId = FindFormulaId(tempFormula.m_strFormulaName);
		//tempFormula.m_strProcessParaName = FindProcessParaName(tempFormula.m_ProcessParaId);

		m_vectFormula[i] = tempFormula;

		strsql.Format(_T("UPDATE tbFormula SET LastUpdatedDateTime=getdate(), ProductionLineId='%d',ProductionLineName='%s',FormulaName='%s',FormulaId='%d',ProcessParaId='%d',ProcessParaName='%s',ParaValueUnit='%s',Note='%s',DefaultValue='%f',IsDefaultFormula='%d',IsCurrentFormula='%d'WHERE Id='%d'"),
			tempFormula.m_ProductionLineId,
			tempFormula.m_strProductionLineName,
			tempFormula.m_strFormulaName,
			tempFormula.m_FormulaId,
			tempFormula.m_ProcessParaId,
			tempFormula.m_strProcessParaName,
			tempFormula.m_strParaValueUnit,
			tempFormula.m_strNote,
			tempFormula.m_DefaultValue,
			tempFormula.m_IsDefaultFormula,
			tempFormula.m_IsCurrentFormula,
			Id);
		break;
	default:
		break;
	}

	ExecutionSQL(strsql);
	return 0;
}



int CDataProvider::DeleteModule(CString ProductionLineName){

	for (pModuleIter = m_vectProcessModule.begin();
		pModuleIter != m_vectProcessModule.end();)
	{
		if (pModuleIter->m_strProductionLineName == ProductionLineName)
		{
			//ɾ���ڴ��������������//
			pModuleIter = m_vectProcessModule.erase(pModuleIter);
		}
		else
		{
			pModuleIter++;
		}

	}

	CString strsql;
	strsql.Format(_T("DELETE FROM tbProcessModule WHERE ProductionLineName='%s' "), ProductionLineName);

	ExecutionSQL(strsql);

	return 0;
}


int CDataProvider::DeleteDevice(CString ProductionLineName, CString ModuleName){

	for (pDeviceIter = m_vectDevice.begin();
		pDeviceIter != m_vectDevice.end();
		)
	{
		if (pDeviceIter->m_strProductionLineName == ProductionLineName
			&& (ModuleName.IsEmpty() || pDeviceIter->m_strProcessModuleName == ModuleName))
		{
			//ɾ���ڴ��������������//
			pDeviceIter = m_vectDevice.erase(pDeviceIter);
		}
		else{
			pDeviceIter++;
		}

	}

	//ɾ�����ݿ����������//
	CString strsql;
	strsql.Format(_T("DELETE FROM tbDevice WHERE ProductionLineName='%s'AND ProcessModuleName='%s'"), ProductionLineName, ModuleName);

	ExecutionSQL(strsql);
	return 0;
}


int CDataProvider::DeletePlc(CString ProductionLineName){

	for (pPlcIter = m_vectPlc.begin();
		pPlcIter != m_vectPlc.end();
		)
	{
		if (pPlcIter->m_strProductionLineName == ProductionLineName)
		{
			//ɾ���ڴ��������������
			pPlcIter = m_vectPlc.erase(pPlcIter);
		}
		else
		{
			pPlcIter++;
		}

	}
	//ɾ�����ݿ����������//
	CString strsql;
	strsql.Format(_T("DELETE FROM tbPLc WHERE ProductionLineName='%s' "), ProductionLineName);

	ExecutionSQL(strsql);

	return 0;
}

int CDataProvider::DeleteVideo(CString ProductionLineName, CString ModuleName)
{

	for (pVideoIter = m_vectVideo.begin();
		pVideoIter != m_vectVideo.end();
		)
	{
		if (pVideoIter->m_strProductionLineName == ProductionLineName
			&& (ModuleName.IsEmpty() || pVideoIter->m_strProcessModuleName == ModuleName))
		{
			//ɾ���ڴ��������������//
			pVideoIter = m_vectVideo.erase(pVideoIter);
		}
		else
		{
			pVideoIter++;
		}
	}

	//ɾ�����ݿ����������
	CString strsql;
	strsql.Format(_T("DELETE FROM tbVideo WHERE ProductionLineName='%s' AND  ProcessModuleName='%s'"), ProductionLineName, ModuleName);

	ExecutionSQL(strsql);

	return 0;
}


int CDataProvider::DeleteParaRelatedToLine(int ProductionLineId)
{
	//ɾ����ص��豸����//
	for (pDeviceParaIter = m_vectDevicePara.begin(); pDeviceParaIter != m_vectDevicePara.end();)
	{
		if (pDeviceParaIter->m_ProductionLineId == ProductionLineId)
		{
			pDeviceParaIter = m_vectDevicePara.erase(pDeviceParaIter);
		}
		else
		{
			++pDeviceParaIter;
		}
	}
	CString strsql;
	strsql.Format(_T("DELETE FROM tbDevicePara WHERE ProductionLineId='%d'"), ProductionLineId);
	ExecutionSQL(strsql);

	//ɾ��״̬�������//
	for (pStateParaIter = m_vectStatePara.begin(); pStateParaIter != m_vectStatePara.end();)
	{
		if (pStateParaIter->m_ProductionLineId == ProductionLineId)
		{
			pStateParaIter = m_vectStatePara.erase(pStateParaIter);
		}
		else
		{
			++pStateParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbStatePara WHERE ProductionLineId='%d'"), ProductionLineId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ղ���//
	for (pProcessParaIter = m_vectProModulePara.begin(); pProcessParaIter != m_vectProModulePara.end();)
	{
		if (pProcessParaIter->m_ProductionLineId == ProductionLineId)
		{
			pProcessParaIter = m_vectProModulePara.erase(pProcessParaIter);
		}
		else
		{
			++pProcessParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbProcessPara WHERE ProductionLineId='%d'"), ProductionLineId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ϲ���//
	for (pFaultParaIter = m_vectFaultPara.begin(); pFaultParaIter != m_vectFaultPara.end();)
	{
		if (pFaultParaIter->m_ProductionLineId == ProductionLineId)
		{
			pFaultParaIter = m_vectFaultPara.erase(pFaultParaIter);
		}
		else
		{
			++pFaultParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbFaultPara WHERE ProductionLineId='%d'"), ProductionLineId);
	ExecutionSQL(strsql);


	return 0;
}

//�����ṩ�Ĺ���ģ���ID,ɾ���빤��ģ����ص����в���//
int CDataProvider::DeleteParaRelatedToModule(int ModuleId)
{
	//ɾ����ص��豸����//
	for (pDeviceParaIter = m_vectDevicePara.begin(); pDeviceParaIter != m_vectDevicePara.end();)
	{
		if (pDeviceParaIter->m_ProcessModuleId == ModuleId)
		{
			pDeviceParaIter = m_vectDevicePara.erase(pDeviceParaIter);
		}
		else
		{
			++pDeviceParaIter;
		}
	}
	CString strsql;
	strsql.Format(_T("DELETE FROM tbDevicePara WHERE ProcessModuleId='%d'"), ModuleId);
	ExecutionSQL(strsql);

	//ɾ��״̬�������//
	for (pStateParaIter = m_vectStatePara.begin(); pStateParaIter != m_vectStatePara.end();)
	{
		if (pStateParaIter->m_ProcessModuleId == ModuleId)
		{
			pStateParaIter = m_vectStatePara.erase(pStateParaIter);
		}
		else
		{
			++pStateParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbStatePara WHERE ProcessModuleId='%d'"), ModuleId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ղ���//
	for (pProcessParaIter = m_vectProModulePara.begin(); pProcessParaIter != m_vectProModulePara.end();)
	{
		if (pProcessParaIter->m_ProcessModuleId == ModuleId)
		{
			pProcessParaIter = m_vectProModulePara.erase(pProcessParaIter);
		}
		else
		{
			++pProcessParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbProcessPara WHERE ProcessModuleId='%d'"), ModuleId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ϲ���//
	for (pFaultParaIter = m_vectFaultPara.begin(); pFaultParaIter != m_vectFaultPara.end();)
	{
		if (pFaultParaIter->m_ProcessModuleId == ModuleId)
		{
			pFaultParaIter = m_vectFaultPara.erase(pFaultParaIter);
		}
		else
		{
			++pFaultParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbFaultPara WHERE ProcessModuleId='%d'"), ModuleId);
	ExecutionSQL(strsql);


	return 0;
}




//�����ṩ���豸��ID,ɾ�����豸��ص����в���//
int CDataProvider::DeleteParaRelatedToDevice(int DeviceId)
{
	//ɾ����ص��豸����//
	for (pDeviceParaIter = m_vectDevicePara.begin(); pDeviceParaIter != m_vectDevicePara.end();)
	{
		if (pDeviceParaIter->m_DeviceId == DeviceId)
		{
			pDeviceParaIter = m_vectDevicePara.erase(pDeviceParaIter);
		}
		else
		{
			++pDeviceParaIter;
		}
	}
	CString strsql;
	strsql.Format(_T("DELETE FROM tbDevicePara WHERE DeviceId='%d'"), DeviceId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ϲ���//
	for (pFaultParaIter = m_vectFaultPara.begin(); pFaultParaIter != m_vectFaultPara.end();)
	{
		if (pFaultParaIter->m_ProcessModuleId == DeviceId)
		{
			pFaultParaIter = m_vectFaultPara.erase(pFaultParaIter);
		}
		else
		{
			++pFaultParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbFaultPara WHERE DeviceId='%d'"), DeviceId);
	ExecutionSQL(strsql);

	return 0;
}


int CDataProvider::DeleteParaRelatedToPlc(int PlcId)
{
	//ɾ����ص��豸����//
	for (pDeviceParaIter = m_vectDevicePara.begin(); pDeviceParaIter != m_vectDevicePara.end();)
	{
		if (pDeviceParaIter->m_PlcId == PlcId)
		{
			pDeviceParaIter = m_vectDevicePara.erase(pDeviceParaIter);
		}
		else
		{
			++pDeviceParaIter;
		}
	}
	CString strsql;
	strsql.Format(_T("DELETE FROM tbDevicePara WHERE PLCId='%d'"), PlcId);
	ExecutionSQL(strsql);

	//ɾ��״̬�������//
	for (pStateParaIter = m_vectStatePara.begin(); pStateParaIter != m_vectStatePara.end();)
	{
		if (pStateParaIter->m_PlcId == PlcId)
		{
			pStateParaIter = m_vectStatePara.erase(pStateParaIter);
		}
		else
		{
			++pStateParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbStatePara WHERE PLCId='%d'"), PlcId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ղ���//
	for (pProcessParaIter = m_vectProModulePara.begin(); pProcessParaIter != m_vectProModulePara.end();)
	{
		if (pProcessParaIter->m_PlcId == PlcId)
		{
			pProcessParaIter = m_vectProModulePara.erase(pProcessParaIter);
		}
		else
		{
			++pProcessParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbProcessPara WHERE PLCId='%d'"), PlcId);
	ExecutionSQL(strsql);

	//ɾ����صĹ��ϲ���//
	for (pFaultParaIter = m_vectFaultPara.begin(); pFaultParaIter != m_vectFaultPara.end();)
	{
		if (pFaultParaIter->m_PLCId == PlcId)
		{
			pFaultParaIter = m_vectFaultPara.erase(pFaultParaIter);
		}
		else
		{
			++pFaultParaIter;
		}
	}
	strsql.Format(_T("DELETE FROM tbFaultPara WHERE PLCId='%d'"), PlcId);
	ExecutionSQL(strsql);

	return 0;
}


//�����ṩ�������ߵ�ID������ɾ�������������йص��䷽
int CDataProvider::DeleteFormulaRelatedToLine(int ProductionLineID)
{
	//ɾ���������������//
	for (pFormulaIter = m_vectFormula.begin(); pFormulaIter != m_vectFormula.end();)
	{
		if (ProductionLineID == pFormulaIter->m_ProductionLineId)
		{
			pFormulaIter = m_vectFormula.erase(pFormulaIter);
		}
		else
		{
			++pFormulaIter;
		}
	}
	//ɾ�����ݿ����������//
	CString strsql;
	strsql.Format(_T("DELETE FROM tbFormula WHERE ProductionLineId='%d'"), ProductionLineID);
	ExecutionSQL(strsql);

	return 0;
}

//�����ṩ���䷽��FormulaId������ɾ�������䷽//
int CDataProvider::DeleteFormula(int FormulaId)
{
	for (pFormulaIter = m_vectFormula.begin(); pFormulaIter != m_vectFormula.end();)
	{
		if (FormulaId == pFormulaIter->m_FormulaId)
		{
			pFormulaIter = m_vectFormula.erase(pFormulaIter);
		}
		else
		{
			++pFormulaIter;
		}
	}

	CString strsql;
	strsql.Format(_T("DELETE FROM tbFormula WHERE FormulaId='%d'"), FormulaId);

	ExecutionSQL(strsql);
	return 0;
}



/*  ���ݴ���Ĳ��� 	ExecutionSQL(strsql); ModuleName��
   ��m_vectDevice�������ҳ���ص�Device
   �洢����Ա���� m_vTempDevice��

   */
int CDataProvider::SearchDevice(CString ProductionLineName, CString ModuleName)
{
	m_vTempDevice.clear();
	for (pDeviceIter = m_vectDevice.begin(); pDeviceIter != m_vectDevice.end(); pDeviceIter++)
	{
		if (pDeviceIter->m_strProductionLineName == ProductionLineName
			&&pDeviceIter->m_strProcessModuleName == ModuleName)
		{
			m_vTempDevice.push_back(*pDeviceIter);
		}

	}
	return 0;
}




int CDataProvider::SearchVideo(CString ProductionLineName, CString ModuleName)
{
	m_vTempVideo.clear();
	for (pVideoIter = m_vectVideo.begin(); pVideoIter != m_vectVideo.end(); pVideoIter++)
	{
		if (pVideoIter->m_strProductionLineName == ProductionLineName
			&&pVideoIter->m_strProcessModuleName == ModuleName)
		{
			m_vTempVideo.push_back(*pVideoIter);
		}
	}
	return 0;
}


/*�޸�����������ص�ģ�飬�豸������ͷ,���ղ������豸���������ϲ�����ģ�������״̬�����д洢��������������
   ����˵��:int LineId,�޸ĵ������ߵ�ID,
   CString modifyLineName ,�����������޸ĳ�modifyLineName

   */
int CDataProvider::UpdateRelatedToLine(int LineId, CString modifyLineName)
{
	CString strsql;

	for (int i = 0; i < m_vectProcessModule.size(); i++)
	{
		if (m_vectProcessModule[i].m_ProcessLineId == LineId)
		{
			m_vectProcessModule[i].m_strProductionLineName = modifyLineName;
		}
	}
	//�������ݿ�//
	strsql.Format(_T("UPDATE tbProcessModule SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);


	for (int i = 0; i < m_vectDevice.size(); i++)
	{
		if (m_vectDevice[i].m_ProductionLineId == LineId)
		{
			m_vectDevice[i].m_strProductionLineName = modifyLineName;
		}
	}

	//�������ݿ�//
	strsql.Format(_T("UPDATE tbDevice SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);

	//�޸�����ͷ
	for (int i = 0; i < m_vectVideo.size(); i++)
	{
		if (m_vectVideo[i].m_ProductionLineId == LineId)
		{
			m_vectVideo[i].m_strProductionLineName = modifyLineName;
		}
	}
	//�������ݿ�//
	strsql.Format(_T("UPDATE tbVideo SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);


	//�޸Ĺ��ղ���//
	for (int i = 0; i < m_vectProModulePara.size(); i++)
	{

		if (m_vectProModulePara[i].m_ProductionLineId == LineId)
		{
			m_vectProModulePara[i].m_strProductionLineName = modifyLineName;
		}
	}

	strsql.Format(_T("UPDATE tbProcessPara SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);


	//�޸Ĺ��ϲ���//
	for (int i = 0; i < m_vectFaultPara.size(); i++)
	{

		if (m_vectFaultPara[i].m_ProductionLineId == LineId)
		{
			m_vectFaultPara[i].m_strProductionLineName = modifyLineName;
		}
	}

	strsql.Format(_T("UPDATE tbFaultPara SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);

	//�޸�״̬����//
	for (int i = 0; i < m_vectStatePara.size(); i++)
	{

		if (m_vectStatePara[i].m_ProductionLineId == LineId)
		{
			m_vectStatePara[i].m_strProductionLineName = modifyLineName;
		}
	}

	strsql.Format(_T("UPDATE tbStatePara SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);


	//�޸��豸����//
	for (int i = 0; i < m_vectDevicePara.size(); i++)
	{

		if (m_vectDevicePara[i].m_ProductionLineId == LineId)
		{
			m_vectDevicePara[i].m_strProductionLineName = modifyLineName;
		}
	}

	strsql.Format(_T("UPDATE tbDevicePara SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);


	//�޸��䷽//
	for (int i = 0; i < m_vectFormula.size(); i++)
	{
		if (m_vectFormula[i].m_ProductionLineId == LineId)
		{
			m_vectDevicePara[i].m_strProductionLineName = modifyLineName;
		}
	}
	strsql.Format(_T("UPDATE tbFormula SET LastUpdatedDateTime=getdate(), ProductionLineName='%s' WHERE ProductionLineId ='%d'"), modifyLineName, LineId);
	ExecutionSQL(strsql);

	return 0;
}


int CDataProvider::UpdateRelatedToModule(int ModuleId, CString modifyModuleName)
{
	CString strsql;
	//�޸��豸//
	for (int i = 0; i < m_vectDevice.size(); i++)
	{
		if (m_vectDevice[i].m_ProcessModuleId == ModuleId)
		{
			m_vectDevice[i].m_strProcessModuleName = modifyModuleName;
		}
	}
	strsql.Format(_T("UPDATE tbDevice SET LastUpdatedDateTime=getdate(), ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);


	//�޸�����ͷ//
	for (int i = 0; i < m_vectVideo.size(); i++)
	{
		if (m_vectVideo[i].m_ModuleId == ModuleId)
		{
			m_vectVideo[i].m_strProcessModuleName = modifyModuleName;
			UpdateTableItem(tbVideo, m_vectVideo[i].m_Id);
		}
	}

	strsql.Format(_T("UPDATE tbVideo SET LastUpdatedDateTime=getdate(), ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);

	//�޸Ĺ��ղ���//
	for (int i = 0; i < m_vectProModulePara.size(); i++)
	{

		if (m_vectProModulePara[i].m_ProcessModuleId == ModuleId)
		{
			m_vectProModulePara[i].m_strProcessModuleName = modifyModuleName;
		}
	}
	strsql.Format(_T("UPDATE tbProcessPara SET LastUpdatedDateTime=getdate(), ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);


	//�޸Ĺ��ϲ���//
	for (int i = 0; i < m_vectFaultPara.size(); i++)
	{

		if (m_vectFaultPara[i].m_ProcessModuleId == ModuleId)
		{
			m_vectFaultPara[i].m_strProcessName = modifyModuleName;
		}
	}
	strsql.Format(_T("UPDATE tbFaultPara SET LastUpdatedDateTime=getdate(),ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);

	//�޸�״̬����//
	for (int i = 0; i < m_vectStatePara.size(); i++)
	{

		if (m_vectStatePara[i].m_ProcessModuleId == ModuleId)
		{
			m_vectStatePara[i].m_strProcessModuleName = modifyModuleName;
		}
	}

	strsql.Format(_T("UPDATE tbStatePara SET LastUpdatedDateTime=getdate(), ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);

	//�޸��豸����//
	for (int i = 0; i < m_vectDevicePara.size(); i++)
	{

		if (m_vectDevicePara[i].m_ProcessModuleId == ModuleId)
		{
			m_vectDevicePara[i].m_strProcessModuleName = modifyModuleName;
		}
	}

	strsql.Format(_T("UPDATE tbDevicePara SET LastUpdatedDateTime=getdate(), ProcessModuleName='%s' WHERE ProcessModuleId ='%d'"), modifyModuleName, ModuleId);
	ExecutionSQL(strsql);

	return 0;
}


int CDataProvider::UpdataRelatedToDevice(int DeviceId, CString modifyDeviceName)
{
	CString strsql;
	//�޸��豸����//
	for (int i = 0; i < m_vectDevicePara.size(); i++)
	{

		if (m_vectDevicePara[i].m_DeviceId == DeviceId)
		{
			m_vectDevicePara[i].m_strDeviceName = modifyDeviceName;
		}
	}

	strsql.Format(_T("UPDATE tbDevicePara SET LastUpdatedDateTime=getdate(), DeviceName='%s' WHERE DeviceId ='%d'"), modifyDeviceName, DeviceId);
	ExecutionSQL(strsql);

	//�޸Ĺ��ϲ���//
	for (int i = 0; i < m_vectFaultPara.size(); i++)
	{

		if (m_vectFaultPara[i].m_DeviceId == DeviceId)
		{
			m_vectFaultPara[i].m_strDeviceName = modifyDeviceName;
		}
	}
	strsql.Format(_T("UPDATE tbFaultPara SET LastUpdatedDateTime=getdate(), DeviceName='%s' WHERE DeviceId ='%d'"), modifyDeviceName, DeviceId);
	ExecutionSQL(strsql);

	return 0;
}

int CDataProvider::UpdateRelatedToPlc(int PlcId, CString modifyPlcName)
{
	CString strsql;
	//�޸Ĺ��ղ���//
	for (int i = 0; i < m_vectProModulePara.size(); i++)
	{

		if (m_vectProModulePara[i].m_PlcId == PlcId)
		{
			m_vectProModulePara[i].m_strPlcName = modifyPlcName;
		}
	}
	strsql.Format(_T("UPDATE tbProcessPara SET LastUpdatedDateTime=getdate(), PlcName='%s' WHERE PLCId ='%d'"), modifyPlcName, PlcId);
	ExecutionSQL(strsql);


	//�޸Ĺ��ϲ���//
	for (int i = 0; i < m_vectFaultPara.size(); i++)
	{

		if (m_vectFaultPara[i].m_PLCId == PlcId)
		{
			m_vectFaultPara[i].m_strPlcName = modifyPlcName;
		}
	}
	strsql.Format(_T("UPDATE tbFaultPara SET LastUpdatedDateTime=getdate(), PlcName='%s' WHERE PLCId ='%d'"), modifyPlcName, PlcId);
	ExecutionSQL(strsql);

	//�޸�״̬����//
	for (int i = 0; i < m_vectStatePara.size(); i++)
	{

		if (m_vectStatePara[i].m_PlcId == PlcId)
		{
			m_vectStatePara[i].m_strPlcName = modifyPlcName;
		}
	}

	strsql.Format(_T("UPDATE tbStatePara SET LastUpdatedDateTime=getdate(), PlcName='%s' WHERE PLCId ='%d'"), modifyPlcName, PlcId);
	ExecutionSQL(strsql);

	//�޸��豸����//
	for (int i = 0; i < m_vectDevicePara.size(); i++)
	{

		if (m_vectDevicePara[i].m_PlcId == PlcId)
		{
			m_vectDevicePara[i].m_strPlcName = modifyPlcName;
		}
	}

	strsql.Format(_T("UPDATE tbDevicePara SET LastUpdatedDateTime=getdate(), PlcName='%s' WHERE PLCId ='%d'"), modifyPlcName, PlcId);
	ExecutionSQL(strsql);

	return 0;
}








void CDataProvider::SetDefaultConfig(int LineID, int ConfigID)
{
	if (!ConfigID)           //���������䷽IDΪ0����ʹ��������û��Ĭ���䷽//
	{
		for (int x = 0; x < m_vectFormula.size(); x++)
		{
			if (m_vectFormula[x].m_ProductionLineId == LineID && m_vectFormula[x].m_IsDefaultFormula != 0)
			{
				m_vectFormula[x].m_IsDefaultFormula = 0;
				UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
			}
		}
	}
	else                 //�����������䷽ID��������ΪĬ���䷽//
	{
		for (int x = 0; x < m_vectFormula.size(); x++)
		{
			if (m_vectFormula[x].m_ProductionLineId == LineID)
			{
				if (m_vectFormula[x].m_FormulaId == ConfigID)
				{
					m_vectFormula[x].m_IsDefaultFormula = 1;
					UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
				}
				else
				{
					if (m_vectFormula[x].m_IsDefaultFormula != 0)
					{
						m_vectFormula[x].m_IsDefaultFormula = 0;
						UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
					}
				}
			}
		}
	}
}


void CDataProvider::SetCurConfig(int LineID, int ConfigID)
{
	int nDefaultConfigID = 0;   //��ǰ�����ߵ�Ĭ���䷽��ID//
	int switchID = ConfigID;
	if (ConfigID == 1)
	{
		for (int x = 0; x < m_vectFormula.size(); x++)
			if (m_vectFormula[x].m_IsDefaultFormula == 1 && LineID == m_vectFormula[x].m_ProductionLineId)
			{
				nDefaultConfigID = m_vectFormula[x].m_FormulaId;
				break;
			}
		if (nDefaultConfigID == 0)   //��Ĭ���䷽�����ڣ���ʹ���κ��䷽//
			switchID = 0;
	}
	switch (switchID)
	{
	case 0:           //�䷽IDΪ0������յ�ǰѡ���䷽//
		for (int x = 0; x < m_vectFormula.size(); x++)
			if (LineID == m_vectFormula[x].m_ProductionLineId && m_vectFormula[x].m_IsCurrentFormula == 1)
			{
				m_vectFormula[x].m_IsCurrentFormula = 0;
				UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
			}
		for (int x = 0; x < m_vectProModulePara.size(); x++)
			if (m_vectProModulePara[x].m_ProductionLineId == LineID && m_vectProModulePara[x].m_IsConfig != 0 && m_vectProModulePara[x].m_fSetValue != -3001)
				m_vectProModulePara[x].m_fSetValue = -3001;
		break;
	case 1:           //�䷽IDΪ1������Ĭ���䷽����ʹ��Ĭ���䷽//
		for (int x = 0; x < m_vectProModulePara.size(); x++)
			if (m_vectProModulePara[x].m_ProductionLineId == LineID && m_vectProModulePara[x].m_IsConfig != 0 && m_vectProModulePara[x].m_fSetValue != -3001)
				m_vectProModulePara[x].m_fSetValue = -3001;
		for (int x = 0; x < m_vectFormula.size(); x++)
			if (m_vectFormula[x].m_ProductionLineId == LineID)
				if (m_vectFormula[x].m_FormulaId == nDefaultConfigID)
				{
					if (m_vectFormula[x].m_IsCurrentFormula != 1)
					{
						m_vectFormula[x].m_IsCurrentFormula = 1;
						UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
					}
					for (int y = 0; y < m_vectProModulePara.size(); y++)
						if (m_vectProModulePara[y].m_Id == m_vectFormula[x].m_ProcessParaId)
							m_vectProModulePara[y].m_fSetValue = m_vectFormula[x].m_DefaultValue;
				}
				else
					if (m_vectFormula[x].m_IsCurrentFormula == 1)
					{
						m_vectFormula[x].m_IsCurrentFormula = 0;
						UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
					}
		break;
	default:          //�����䷽ID����ʹ�ø�IDָ����䷽//
		for (int x = 0; x < m_vectProModulePara.size(); x++)
			if (m_vectProModulePara[x].m_ProductionLineId == LineID && m_vectProModulePara[x].m_IsConfig != 0 && m_vectProModulePara[x].m_fSetValue != -3001)
				m_vectProModulePara[x].m_fSetValue = -3001;
		for (int x = 0; x < m_vectFormula.size(); x++)
			if (m_vectFormula[x].m_ProductionLineId == LineID)
				if (m_vectFormula[x].m_FormulaId == ConfigID)
				{
					if (m_vectFormula[x].m_IsCurrentFormula != 1)
					{
						m_vectFormula[x].m_IsCurrentFormula = 1;
						UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
					}
					for (int y = 0; y < m_vectProModulePara.size(); y++)
						if (m_vectProModulePara[y].m_Id == m_vectFormula[x].m_ProcessParaId)
							m_vectProModulePara[y].m_fSetValue = m_vectFormula[x].m_DefaultValue;
				}
				else
					if (m_vectFormula[x].m_IsCurrentFormula == 1)
					{
						m_vectFormula[x].m_IsCurrentFormula = 0;
						UpdateTableItem(tbFormula, m_vectFormula[x].m_Id);
					}
		break;
	}

}




void CDataProvider::DispatchParaValue(int PlcIndex)
{
	int len = m_vectProModulePara.size();
	CProcessPara tempProPara;


	if (PlcIndex >= m_vectPlc.size())
	{
		return;
	}

	for (int i = 0; i < len; i++)
	{
		if (m_vectProModulePara[i].m_PlcId == m_vectPlc[PlcIndex].m_Id
			&& (m_vectPlc[PlcIndex].GetPlcReadMemorySize() > m_vectProModulePara[i].GetReadAddrIndex()))
		{
			float ParaValue = (float)m_vectPlc[PlcIndex].GetReadByte(_ttoi(m_vectProModulePara[i].m_strReadAddrIndex));
			m_vectProModulePara[i].SetParaValue(ParaValue);
		}
	}

}