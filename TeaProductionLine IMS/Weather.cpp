#include "stdafx.h"
#include "Weather.h"
#include "afxinet.h"
#include "atlutil.h"





CWeather::CWeather()
{
	CString m_strCity = _T("长沙");
}


CWeather::~CWeather()
{
}


void CWeather::UpdateWeather(CString strCity)
{
	m_strCity = strCity;

	//CString strURL =_T("http://api.map.baidu.com/telematics/v3/weather?location=长沙&output=json&ak=XQzZKLyQnEGv2B2ZBy3ry1Qt");
	//CString strURL = _T("http://api.map.baidu.com/telematics/v3/weather?location=%E9%95%BF%E6%B2%99&output=json&ak=XQzZKLyQnEGv2B2ZBy3ry1Qt");

	//CString strURL = _T("http://php.weather.sina.com.cn/iframe/index/w_cl.php?day=1&city=长沙&dfc=1&charset=utf-8");

	//CString strURL = _T("http://m.weather.com.cn/mweather/101250101.shtml");
	//CString strURL = _T("http://m.weather.com.cn/data/101250101.shtml");

	//CString strURL = _T("http://api.heweather.com/x3/weather?city=%E9%95%BF%E6%B2%99&key=e54b86179fff4845966f864bdac9d488");


	//CString strURL;
	//strURL.Format(_T("http://api.heweather.com/x3/weather?city='%s'&key=e54b86179fff4845966f864bdac9d488"),location);




	DWORD len = 1024;
	CString location = m_strCity;
	PTCHAR pchBuffer = NULL;
	pchBuffer = new TCHAR[lstrlen(location) * 10];

	AtlEscapeUrl(location, pchBuffer, &len, 1024, ATL_URL_ENCODE_PERCENT);

	location.Format(_T("%s"), pchBuffer);
	delete[] pchBuffer;
	CString strURL;
	strURL.Format(_T("http://api.heweather.com/x3/weather?city=%s&key=e54b86179fff4845966f864bdac9d488"), location);
	
	CString strHtml=OpenUrl(strURL);
	GetDataFromHtml(strHtml);

}


CString CWeather::OpenUrl(CString strURL)
{
	CInternetSession session(NULL, 0);
	CHttpFile *file = NULL;


	CString  strHtml = _T(""); //存放网页数据	//
	try
	{
		file = (CHttpFile*)session.OpenURL(strURL);
	}
	catch (CInternetException *m_pException)
	{
		file = NULL;
		m_pException->m_dwError;
		m_pException->Delete();
		session.Close();
		AfxMessageBox(_T("网络连接错误"));
		return strHtml;
	}
	CString strLine;
	char sRecived[1024];
	CString tempstr;
	if (file != NULL) {
		while (file->ReadString(tempstr)!=NULL)
		{
			strHtml += tempstr;
		}
	}
	else
	{
		AfxMessageBox(_T("fail"));
	}

	session.Close();
	file->Close();
	delete file; 
	file = NULL;

	ConvertToUnicode(strHtml);
	return strHtml;

}




int CWeather::GetDataFromHtml(CString strHtml)
{

	int leftPos = strHtml.Find(_T("pm25"));
	
	m_strPM25 = strHtml.Mid(leftPos + 7, 2);
	
	leftPos = strHtml.Find(_T("\"basic\":{\"city\":"));
	m_strCity = strHtml.Mid(leftPos + 17, 2);

	leftPos = strHtml.Find(_T("\"hum\":"));
	m_strHum = strHtml.Mid(leftPos + 7, 2);

	leftPos = strHtml.Find(_T("\"tmp\":{\"max\":"));
	m_HighTemp = strHtml.Mid(leftPos + 14, 2);
	m_LowTemp = strHtml.Mid(leftPos + 25, 2);

	leftPos = strHtml.Find(_T("\"txt_d\":"));
	m_strWeather = strHtml.Mid(leftPos + 9, 7);

	m_strWeather.Replace(_T("\""), _T(""));
	m_strWeather.Replace(_T("\,"), _T(""));
	m_strWeather.Replace(_T("t"), _T(""));
	m_strWeather.Replace(_T("x"), _T(""));

    int startPos = strHtml.Find(_T("\"hourly_forecast\""));
	leftPos = strHtml.Find(_T("\"tmp\":"),startPos);
	m_curTemp = strHtml.Mid(leftPos + 7, 2);

	leftPos = strHtml.Find(_T("\"loc\":"));
	m_strDate = strHtml.Mid(leftPos+7,17);
	m_strDate.Replace(_T("\""), _T(""));



	m_strWeatherInfo.Format(_T("%s,日期：%s,%s,当前温度：%s℃,今日温度：%s~%s℃,空气湿度:%s%%"),m_strCity,m_strDate,m_strWeather,m_curTemp,m_LowTemp,m_HighTemp,m_strHum);

	return 0;
}







void CWeather::ConvertToUnicode(CString& strUtf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)strUtf8, -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len];
	memset(wszGBK, 0, len * 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len];
	memset(szGBK, 0, len);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	strUtf8 = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}





