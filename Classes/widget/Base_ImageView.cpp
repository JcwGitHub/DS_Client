#include "Base_ImageView.h"

Base_ImageView* Base_ImageView::creat(const std::string& filePath)
{
	Base_ImageView* _image = new Base_ImageView();
	if (_image&&_image->initWithImage(CAImage::create(filePath)))
	{
		_image->autorelease();
		return _image;
	}

	CC_SAFE_RELEASE_NULL(_image);
	return NULL;
}
//网络图片的获取
Base_ImageView* Base_ImageView::CreatWithUrl(const std::string& url)
{
	Base_ImageView* ima = new Base_ImageView();
	if (ima->init(url))
	{
		ima->autorelease();
		return ima;
	}

	CC_SAFE_RELEASE_NULL(ima);
	return NULL;
}

bool Base_ImageView::init(const std::string& url)
{
	if (!CAImageView::init())
	{
		return false;
	}


	m_Url = url;

	m_image = CAImageCache::sharedImageCache()->imageForKey(m_Url);
	if (m_image)
	{
		DownLoadSucess();
	}
	else
	{
		DownLoadImage();
	}
	return true;
}

void Base_ImageView::ReceiveHttpCallBack(CAHttpClient* client, CAHttpResponse* response)
{
	//消息是否处理成功
	if (!response->isSucceed())
	{
		CCLog("/**************DownLoadImage Error!**************/");
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

	//创建图片
	m_image = CAImage::createWithImageData((const unsigned char*)res.c_str(), res.length(), m_Url);

	DownLoadSucess();
}

void Base_ImageView::DownLoadImage()
{
	//发送消息
	CAHttpClient* http = CAHttpClient::getInstance();

	CAHttpRequest* request = new CAHttpRequest();

	request->setUrl(m_Url.c_str());

	request->setRequestType(CAHttpRequest::kHttpGet);

	request->setResponseCallback(this, httpresponse_selector(Base_ImageView::ReceiveHttpCallBack));

	//发送消息
	http->send(request);


	//清除消息
	request->release();
}

void Base_ImageView::DownLoadSucess()
{
	this->setImage(m_image);
}