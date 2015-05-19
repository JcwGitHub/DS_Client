#include "Data_HttpManage.h"
#include "Data_Define.h"



Data_HttpManage* Data_HttpManage::s_DataHttp = NULL;
Data_HttpManage* Data_HttpManage::GetInstance()
{
	if (s_DataHttp==NULL)
	{
		s_DataHttp = new Data_HttpManage();
	}

	return s_DataHttp;
}

void Data_HttpManage::PushPostData(const std::string& name, const std::string& value)
{
	//消息默认参数
	pushDataHead();


	//添加消息key
	m_dataStr += '"';
	m_dataStr += name;
	m_dataStr += '"';
	m_dataStr += ':';

	//添加消息值
	std::string _value = value;
	MY_Base64_Encode(_value);
	m_dataStr += '"';
	m_dataStr += _value;
	m_dataStr += '"';
	m_dataStr += ',';
}

void Data_HttpManage::PushPostData(const std::string& name, int value)
{
	PushPostData(name, C_IntToString(value));
}
void Data_HttpManage::SendData(const std::string& Url, CAHttpRequest::HttpRequestType type)
{
	//检测消息头
	pushDataHead();

	//准备发送消息
	PushDataEnd(Url);

	//发送消息
	CAHttpClient* http = CrossApp::extension::CAHttpClient::getInstance();

	CAHttpRequest* request = new CrossApp::extension::CAHttpRequest();

	request->setUrl(m_dataStr.c_str());

	request->setRequestType(type);

	request->setRequestData(m_dataStr.c_str(), m_dataStr.length());

	request->setResponseCallback(this, httpresponse_selector(Data_HttpManage::ReceiveHttpCallBack));

// 	CSJson::Value _tag(messageTag);

	
	request->setTag(C_IntToString(m_messageId).c_str());

	//发送消息
// 	http->setTimeoutForConnect(5);
// 	http->setTimeoutForRead(5);
	http->send(request);


	//清除消息
	request->release();
	m_firstPush = true;
	m_dataStr.clear();
}
void Data_HttpManage::ReceiveHttpCallBack(CAHttpClient* client, CAHttpResponse* response)
{
	std::string _key = response->getHttpRequest()->getTag();
	//消息是否处理成功
	if (!response->isSucceed())
	{
		CCLog("/**************Recive Http Message Error!**************/");
		ClearData(_key);
		return;
	}

	//接收数据
	std::vector<char> *data = response->getResponseData();
	int _code = response->getResponseCode();
	std::string res;
	for (int i = 0; i < (int)data->size(); i++)
	{
		res += (*data)[i];
	}

	//打印消息
	CCLog("/*****************************/");
	CCLog("Recive Message = %s", res.c_str());
	CCLog("/*****************************/");


	//发送消息
	map<std::string, S_HttpMessage>::iterator itor;
	itor = m_callBackMap.find(_key);
	if (itor!=m_callBackMap.end())
	{
		(m_callBackMap[_key]._obj->*m_callBackMap[_key]._func)(res.c_str());
	}
	
	ClearData(_key);
}
void Data_HttpManage::PushDataEnd(const std::string& url)
{
	//处理消息尾
	int _length = m_dataStr.find_last_of(",");
	m_dataStr   = m_dataStr.substr(0, _length);
	m_dataStr   += "}";

	std::string _head = "http://yun.9miao.com/" + url + "?data=";
	std::string _data = '{' + m_dataStr;

	//消息体加密
	MY_Base64_Encode(_data);
	m_dataStr = _head + _data;

	//打印消息
	CCLog("/*****************************/");
	CCLog("Http Message = %s",m_dataStr.c_str());
	CCLog("/*****************************/");
}

void Data_HttpManage::pushDataHead()
{
	//默认消息带User_Appkey User_UserKey User_UserId

	if (m_dataStr.empty()&&m_firstPush)
	{
		m_firstPush = false;
		PushPostData("appkey", User_Appkey);
		PushPostData("userkey", User_UserKey);
		PushPostData("userid", User_UserId);
	}
}

void Data_HttpManage::ClearData(std::string key)
{
	map<std::string, S_HttpMessage>::iterator itor;
	itor = m_callBackMap.find(key);
	if (itor!=m_callBackMap.end())
	{
		m_callBackMap.erase(itor);
	}

}

void Data_HttpManage::SetHttpCallBack(CAObject* target, SEL_HttpManager callfunc)
{
	S_HttpMessage _http;
	_http._obj = target;
	_http._func = callfunc;
	m_callBackMap[C_IntToString(m_messageId++)] = _http;
}

void Data_HttpManage::RemoveHttpCallBack(CAObject* target)
{
	map<std::string, S_HttpMessage>::iterator itor;
	vector<std::string> _temp;
	for (itor = m_callBackMap.begin(); itor != m_callBackMap.end(); itor++)
	{
		if (itor->second._obj == target)
		{
			_temp.push_back(itor->first);
		}
	}


	for (size_t i = 0; i < _temp.size(); i++)
	{
		itor = m_callBackMap.find(_temp[i]);
		if (itor!=m_callBackMap.end())
		{
			m_callBackMap.erase(itor);
		}
	}
}




//-----------------------------------------------
// 消息
//-----------------------------------------------
HttpMessage::HttpMessage(int tag, const std::string &url, const std::string &data)
{
	m_data = data;
	m_tag = tag;
	m_url = url;
}