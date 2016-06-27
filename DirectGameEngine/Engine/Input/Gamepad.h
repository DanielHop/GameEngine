#pragma once

#include <Windows.h>
#include <Xinput.h>



class Gamepad
{
public:
	Gamepad(unsigned int index);
	~Gamepad();

	void Update();

	bool LStickInDeadZone();
	bool RStickInDeadZone();

	XINPUT_STATE GetState();
	unsigned int GetIndex();
	bool IsConnected();

private:
	XINPUT_STATE m_state;
	unsigned int m_index;

};

