#include "WindowManagerDX.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

WindowManagerDX::WindowManagerDX(HINSTANCE hInstance, int cmdShow, int width, int height) : m_hInstance{ hInstance }, m_cmdShow{ cmdShow }, m_width{ width }, m_height { height }
{
}


WindowManagerDX::~WindowManagerDX()
{
}

bool WindowManagerDX::Init(DXApp* dxApp)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Test";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"Register class failed", 0, 0);
		return false;
	}

	m_mainHandle = CreateWindow(L"Test", L"DirectApp",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_width, m_height,
		0, 0, m_hInstance, 0);

	if (m_mainHandle == 0)
	{
		MessageBox(0, L"Creating of window failed", 0, 0);
		return false;
	}

	ShowWindow(m_mainHandle, m_cmdShow);
	UpdateWindow(m_mainHandle);

	return true;
}

void WindowManagerDX::PrepareWindow()
{

}

void WindowManagerDX::UpdateRendering()
{

}

void WindowManagerDX::DestroyWindow()
{

}

