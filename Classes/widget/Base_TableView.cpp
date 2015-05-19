#include "Base_TableView.h"
#include "Data_Define.h"

Base_TableView* Base_TableView::creat(const CCRect& rect)
{
	Base_TableView* table = new Base_TableView();
	if (table&&table->init(rect))
	{
		table->autorelease();
		return table;
	}

	CC_SAFE_RELEASE_NULL(table);
	return NULL;
}

bool Base_TableView::init(const CCRect& rect)
{
	if (!CATableView::initWithFrame(rect))
	{
		return false;
	}


	return true;
}



//cell
Base_Cell* Base_Cell::creatWith(const std::string& key)
{
	Base_Cell* cell = new Base_Cell();
	if (cell&&cell->init(key))
	{
		cell->autorelease();
		return cell;
	}

	CC_SAFE_RELEASE_NULL(cell);
	return NULL;
}

bool Base_Cell::init(const std::string& key)
{
	if (!CATableViewCell::initWithReuseIdentifier(key))
	{
		return false;
	}

	
	return true;
}

void Base_Cell::normalTableViewCell()
{
	m_pBackgroundView->setColor(ccc4(235, 234, 234, 255));
	
	m_pBackgroundView->removeAllSubviews();
}

void Base_Cell::highlightedTableViewCell()
{
	m_pBackgroundView->setColor(CAColor_red);
}

void Base_Cell::selectedTableViewCell()
{
	CAView* sel = CAView::createWithFrame(CCRect(0, 0, FitX(5), this->getBounds().size.height), CAColor_red);
	m_pBackgroundView->setColor(ccc4(255, 255, 255, 255));
	m_pBackgroundView->addSubview(sel);
}

//////////////////////////////////////////////////////////////////////////
Base_Cell1* Base_Cell1::creatWith(const std::string& key)
{
	Base_Cell1* cell = new Base_Cell1();
	if (cell&&cell->initWith(key))
	{
		cell->autorelease();
		return cell;
	}

	CC_SAFE_RELEASE_NULL(cell);
	return NULL;
}

void Base_Cell1::normalTableViewCell()
{
	m_pBackgroundView->setColor(m_bgColor);
}

void Base_Cell1::highlightedTableViewCell()
{
	m_pBackgroundView->setColor(m_bgColor);
}

void Base_Cell1::selectedTableViewCell()
{
	m_pBackgroundView->setColor(m_bgColor);
}
void Base_Cell1::disabledTableViewCell()
{
	m_pBackgroundView->setColor(m_bgColor);
}
bool Base_Cell1::initWith(const std::string& key)
{
	m_bgColor = CAColor_clear;

	if (!CATableViewCell::initWithReuseIdentifier(key))
	{
		return false;
	}
	
	return true;
}

void Base_Cell1::SetBgColor(CAColor4B color)
{
	m_bgColor = color;
	normalTableViewCell();
}
