#include "Base_PageView.h"
#include "Data_Define.h"


Base_PageView* Base_PageView::creat(const CCRect& rect, const CAPageViewDirection& type)
{
	Base_PageView* page = new Base_PageView();
	if (page&&page->init(rect,type))
	{
		page->autorelease();
		return page;
	}

	CC_SAFE_RELEASE_NULL(page);
	return NULL;
}

bool Base_PageView::init(const CCRect& rect, const CAPageViewDirection& type)
{
	m_pageTag			 = NULL;
	m_autoScroll		 = false;
	m_nCurrPage			 = 0;
	m_pPageViewDelegate  = NULL;
	m_ePageViewDirection = type;
	if (!CAPageView::initWithCenter(rect))
	{
		return false;
	}

	setPageViewDelegate(this);

	setCurrPage(1, false);
	return true;
}

void Base_PageView::pageViewDidBeginTurning(CAPageView* pageView)
{
	int a = 0;
}

void Base_PageView::pageViewDidEndTurning(CAPageView* pageView)
{
	if (pageView->getCurrPage()==1)
	{
		return;
	}
	m_atIndex = (m_atIndex + (pageView->getCurrPage() - 1) + m_views.size()) % m_views.size();	
	pageView->setCurrPage(1, false);
	ChangePage();
}

void Base_PageView::pageViewDidSelectPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point)
{
	int a = 0;
}

void Base_PageView::SetAutoScroll(bool flag /*= true*/)
{
	//当前属性
	m_atIndex = 0;
	m_autoScroll = flag;

	this->setCurrPage(1, false);

	this->ChangePage();

	//开启定时器
	if (m_autoScroll)
	{
		CAScheduler::schedule(schedule_selector(Base_PageView::updateImage), this, 5.0f, kCCRepeatForever,5.0f);
	}
	else
	{

	}
}

void Base_PageView::SetPageViews(const CAVector<CAView*>& vec)
{
	this->setViews(vec);

	//保存位置
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i>=3) break;

		m_point[i] = vec.at(i)->getFrameOrigin();
	}

	//保存节点
	m_views.clear();
	for (size_t i = 0; i < vec.size(); i++)
	{
		m_views.push_back(vec.at(i));
	}
}

void Base_PageView::ChangePage()
{
	int _op[3] = { 
		(m_atIndex - 1 + m_views.size()) % m_views.size(), 
		m_atIndex, 
		(m_atIndex + 1) % m_views.size() 
	};


	for (size_t i = 0; i < m_views.size(); i++)
	{
		m_views[i]->setVisible(false);
	}
	for (size_t i = 0; i < 3; i++)
	{
		m_views[_op[i]]->setVisible(true);
		m_views[_op[i]]->setFrameOrigin(m_point[i]);
	}

	if (m_pageTag)
	{
		m_pageTag->SetCurIndex(m_atIndex);
	}
}

void Base_PageView::updateImage(float dt)
{
	this->setCurrPage(2, true,true);
}

Base_PageTag* Base_PageView::GetPageTag()
{
	if (!m_pageTag)
	{
		m_pageTag = Base_PageTag::creat(m_views.size());
		m_pageTag->setFrameOrigin(CCPoint(
			getCenter().size.width - m_pageTag->getFrame().size.width,
			getCenter().size.height - m_pageTag->getFrame().size.height));
		m_pageTag->SetCurIndex(m_atIndex);
	}

	return m_pageTag;
}



//page 底下标签页
Base_PageTag* Base_PageTag::creat(int nums)
{
	Base_PageTag* _tag = new Base_PageTag();
	if (_tag&&_tag->init(nums))
	{
		_tag->autorelease();
		return _tag;
	}

	CC_SAFE_RELEASE_NULL(_tag);
	return NULL;
}
bool Base_PageTag::init(int nums)
{
	if (!CAView::init())
	{
		return false;
	}

	//大小25*25 间隙5
	this->setFrame(FitRect(0,0,30*nums,35));
	this->setColor(CAColor_clear);


	//设计尺寸
	CCSize _dSize = CCSize(25, 25);
	
	char _str[8];
	for (size_t i = 0; i < nums; i++)
	{
		CAView* _tag = CAView::createWithFrame(FitRect(30 * i, 0, _dSize.width, _dSize.width), CAColor_gray);
		_tag->setTag(1000+i);
		this->addSubview(_tag);

		sprintf(_str, "%d", i + 1);
		CALabel* label = CALabel::createWithCenter(FitRect(_dSize.width/2,_dSize.height/2, 25, 25));
		label->setText(_str);
		label->setFontSize(_px(20));
		label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		label->setTextAlignment(CATextAlignmentCenter);
		label->setColor(CAColor_white);
		_tag->addSubview(label);
	}
	return true;
}

void Base_PageTag::SetCurIndex(int index)
{
	int _tag = 0;
	CAView* _view = this->getSubviewByTag(1000 + _tag);
	while (_view)
	{
		if (_tag==index)
		{
			_view->setColor(CAColor_red);
		}
		else
		{
			_view->setColor(CAColor_gray);
		}
		_tag += 1;
		_view = this->getSubviewByTag(1000 + _tag);
	}
}




