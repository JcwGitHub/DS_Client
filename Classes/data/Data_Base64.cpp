#include "Data_Base64.h"
#include "CrossApp.h"

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

void MY_Base64_Encode(std::string& target) 
{
	std::string ret;
	int i = 0;
	int j = 0;
	int in_len = target.length();
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = target[target.length()-in_len-1];

		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}


	CCLog("%s  =====Encode=====   %s", target.c_str(),ret.c_str());

	target.clear();
	target = ret;
}

void MY_Bbase64_Decode(std::string& target) {
	int in_len = target.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (target[in_] != '=') && is_base64(target[in_])) {
		char_array_4[i++] = target[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	CCLog("%s  =====Decode=====   %s", target.c_str(), ret.c_str());
	target.clear();
	target = ret;
}


Data_Base* Data_Base::s_DataBase = NULL;
Data_Base::Data_Base()
{
	m_NarBar_H = 98;
	m_TabBar_H = 98;
	m_firstLogin = false;
}
Data_Base* Data_Base::GetInstance()
{
	if (!s_DataBase)
	{
		s_DataBase = new Data_Base();
		s_DataBase->init();
	}

	return s_DataBase;
}

void Data_Base::PushSearch(const std::string& _key)
{
	m_searchList.insert(m_searchList.begin(),_key);
	SaveAndGet();
}

void Data_Base::ClearSearch()
{
	m_searchList.clear();
	SaveAndGet();
}

void Data_Base::SaveAndGet(bool flag /*= true*/)
{
	std::string _fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "searchList.xml";
	tinyxml2::XMLDocument _doc;
	unsigned long _size;

	unsigned char* _date = CCFileUtils::sharedFileUtils()->getFileData(_fullPath.c_str(), "rb", &_size);

	tinyxml2::XMLElement* root = NULL;
	tinyxml2::XMLElement* child = NULL;
	if (_doc.Parse((const char*)_date, _size))
	{
		tinyxml2::XMLDeclaration* _dec = _doc.NewDeclaration();
		_doc.LinkEndChild(_dec);
		root = _doc.NewElement("root");
		_doc.LinkEndChild(root);
	}

	root = _doc.FirstChildElement("root");

	if (flag)
	{
		//保存
		root->DeleteChildren();

		for (size_t i = 0; i < m_searchList.size(); i++)
		{
			//记录前10个
			if (i >= 10)
				break;

			child = _doc.NewElement("search");
			child->SetAttribute("text", m_searchList[i].c_str());
			root->LinkEndChild(child);
		}

		_doc.SaveFile(_fullPath.c_str());
	}
	else
	{
		//读取
		m_searchList.clear();

		child = root->FirstChildElement();
		while (child)
		{
			m_searchList.push_back(child->Attribute("text"));

			child = child->NextSiblingElement();
		}

		m_searchList.push_back(UTF8("女"));
	}
}

bool Data_Base::init()
{
	SaveAndGet(false);
	CheckFirstLogin();
	return true;
}

void Data_Base::CheckFirstLogin()
{
	std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath() + "client.xml";
	FILE * fp = NULL;
	if ((fp = fopen(_path.c_str(), "rb"))==NULL)
	{
		fp = fopen(_path.c_str(), "w");
		m_firstLogin = true;
	}

		fclose(fp);
}