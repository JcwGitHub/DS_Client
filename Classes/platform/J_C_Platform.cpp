#include "J_C_Platform.h"

J_C_Platform* J_C_Platform::m_platform = 0;
void J_C_Platform::AddDelegate(J_C_Delegate* _delegate)
{
	m_delegates.push_back(_delegate);
}

void J_C_Platform::SendMessage(int nType)
{
	AndroidLog("444");
	for (size_t i = 0; i < m_delegates.size(); i++)
	{
		AndroidLog("5555");
		switch (nType)
		{
		case 1:
			m_delegates[i]->TaoBaoUserInfoUpdate();
			break;
		}
	}

}
