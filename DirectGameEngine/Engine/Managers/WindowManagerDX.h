#pragma once

#include <windows.h>
#include <windowsx.h>

class DXApp;

class WindowManagerDX
{
public:
	WindowManagerDX(HINSTANCE hIstance, int show, int width, int height);
	~WindowManagerDX();

	bool Init(DXApp* dxApp);
	void PrepareWindow();
	void UpdateRendering();
	void DestroyWindow();

	auto getWidth() { return m_width; }
	auto getHeight() { return m_height; }
	auto getClose() { return false; }
	auto getWindow() { return m_mainHandle; }

private:
	HINSTANCE m_hInstance;
	HWND m_mainHandle;
	int m_cmdShow;
	int m_width{ 1680 }, m_height{ 1050 };
};

