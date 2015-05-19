#include "Base_NavBar.h"

bool Base_NavBar::init()
{
	return true; 
}

void Base_NavBar::BarAddSubView(CAView* _view)
{
	m_pContainers.back()->insertSubview(_view, 10 + m_pContainers.back()->getSubviewsCount());
}
