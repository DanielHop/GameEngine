#pragma once

#include "../Systems/System.h"
#include "../Input/Gamepad.h"

class InputSystem : public System
{
public:
	InputSystem() { m_type = EMPTY_UPDATE; }
	~InputSystem(){}

	void Init()override;
	void EmptyUpdate()override;

	void AddGamepad(unsigned int count = 1);
private:
	std::vector<std::unique_ptr<Gamepad>> m_gamePads;
};