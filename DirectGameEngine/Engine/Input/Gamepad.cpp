#include "Gamepad.h"

Gamepad::Gamepad(unsigned int index) : m_index{ index - 1}
{}

Gamepad::~Gamepad()
{
}

void Gamepad::Update()
{
	m_state = GetState();
}

bool Gamepad::LStickInDeadZone()
{
	short sX = m_state.Gamepad.sThumbLX;
	short sY = m_state.Gamepad.sThumbLY;

	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

bool Gamepad::RStickInDeadZone()
{
	short sX = m_state.Gamepad.sThumbRX;
	short sY = m_state.Gamepad.sThumbRY;

	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

XINPUT_STATE Gamepad::GetState()
{
	XINPUT_STATE returnState;

	ZeroMemory(&returnState, sizeof(XINPUT_STATE));

	XInputGetState(m_index, &returnState);

	return returnState;
}

unsigned int Gamepad::GetIndex()
{
	return m_index - 1;
}

bool Gamepad::IsConnected()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));

	DWORD result = XInputGetState(m_index, &m_state);

	if (result == ERROR_SUCCESS)
		return true;
	else
		return false;
}