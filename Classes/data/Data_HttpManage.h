#ifndef DATA_HTTP_MANAGE_H
#define DATA_HTTP_MANAGE_H

#include "HttpClient.h"
#include <string>
#include "CrossApp.h"

using namespace CrossApp::extension;

typedef void (CAObject::*SEL_HttpManager)(const char*);
#define HttpManager_selector(_SELECTOR) (SEL_HttpManager)(&_SELECTOR)

class Data_HttpManage : public CAObject
{
public:
	struct S_HttpMessage
	{
		CAObject*		_obj;
		SEL_HttpManager	_func;
	};
public:
	Data_HttpManage() :
		//m_callBack(nullptr),
		m_firstPush(true),
		m_messageId(0){}

	static Data_HttpManage* GetInstance();

	//添加数据
	void					PushPostData(const std::string& name, const std::string& value);
	void					PushPostData(const std::string& name, int value);

	//发送消息
	void				    SendData(const std::string& Url, CAHttpRequest::HttpRequestType type = CAHttpRequest::kHttpPost);

	//接受消息
	void					ReceiveHttpCallBack(CAHttpClient* client, CAHttpResponse* response);

	//消息的回调函数
	void					SetHttpCallBack(CAObject* target, SEL_HttpManager callfunc);
	void					RemoveHttpCallBack(CAObject* target);
private:
	void					PushDataEnd(const std::string& url);

	void					pushDataHead();

	void					ClearData(std::string key);
private:
	static Data_HttpManage* s_DataHttp;

	std::string				m_dataStr;

	//消息返回的回掉函数
	map<std::string, S_HttpMessage>	m_callBackMap;

	bool					m_firstPush;


	int						m_messageId;
};

class HttpMessage
{
public:
	HttpMessage(int tag, const std::string &url, const std::string &data);

	int GetTag()				{ return m_tag; }
private:
	int				m_tag;
	std::string		m_url;
	std::string		m_data;
};

#endif