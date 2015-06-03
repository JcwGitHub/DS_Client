#include "J_C_Win_Platform.h"


J_C_Platform* J_C_Platform::GetInstance()
{
	if (!m_platform)
	{
		m_platform = new J_C_WIN_Platform();
	}

	return m_platform;
}