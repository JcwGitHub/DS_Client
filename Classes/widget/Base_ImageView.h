#ifndef BASE_IMAGEVIEW_H
#define BASE_IMAGEVIEW_H

#include "HttpClient.h"

using namespace CrossApp::extension;
class Base_ImageView : public CAImageView
{
public:
	static Base_ImageView* creat(const std::string& filePath);

	//url
	static Base_ImageView* CreatWithUrl(const std::string& url);

	void			  ReceiveHttpCallBack(CAHttpClient* client,CAHttpResponse* response);
protected:
private:
	virtual bool	  init(const std::string& url);

	//下载图片
	void			  DownLoadImage();

	//下载完成
	void			  DownLoadSucess();
private:
	unsigned long   m_uid;

	std::string     m_Url;

	CAImage*        m_image;
};
#endif