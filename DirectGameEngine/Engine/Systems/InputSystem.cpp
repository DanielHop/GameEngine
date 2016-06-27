#include "InputSystem.h"

void InputSystem::Init()
{

}

void InputSystem::EmptyUpdate()
{
	for (auto& g : m_gamePads)
		g->Update();
}

void InputSystem::AddGamepad(unsigned int count)
{
	if (m_gamePads.size() == 4)
		return;

	m_gamePads.push_back(std::unique_ptr<Gamepad>{ new Gamepad(m_gamePads.size() + 1)});
}