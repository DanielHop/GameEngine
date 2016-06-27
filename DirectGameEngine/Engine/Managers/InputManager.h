#pragma once

#include <Vector>

enum KEYS
{
	A, B, C,
	D, E, F,
	G, H, I,
	J, K, L,
	M, N, O,
	P, Q, R,
	S, T, U,
	V, W, X,
	Y, Z
};

class InputManager
{
public:
	static void KeyDown(KEYS key);
	static void KeyUp(KEYS key);
	static bool IsKeyDown(KEYS key);

private:
	static std::vector<bool> m_keys;
};