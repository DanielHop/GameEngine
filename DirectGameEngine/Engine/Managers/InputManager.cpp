#include "InputManager.h"

bool InputManager::IsKeyDown(KEYS key)
{
	return m_keys.at(key);
}

void InputManager::KeyDown(KEYS key)
{
	m_keys.at(key) = true;
}

void InputManager::KeyUp(KEYS key)
{
	m_keys.at(key) = false;
}