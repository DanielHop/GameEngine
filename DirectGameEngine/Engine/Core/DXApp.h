#pragma once

#include <memory>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <vector>
#include <assert.h>
#include <string>
#include <sstream>

#include <d3d11.h>
#include <directXmath.h>

#include "../Core/GameTimer.h"
#include "../Util/D3DUtil.h"

#define TICKS_PER_SECOND 60.f



class DXApp
{
public:
	DXApp(HINSTANCE hInstance, int show);
	~DXApp();

	bool Start();
	virtual bool Init();
	void Run();
	void Shutdown();

	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	bool InitWindow();
	bool InitDirectX();

	void TimerUpdate();
	void CalculateFrameStats();
	virtual void PrepareWindow();
	virtual void RenderWindow();

	virtual void PreInit() {}
	virtual void InitGame() {}
	virtual void LateInit() {}
	virtual void OnTickUpdate(float dt) = 0;
	virtual void LateTickUpdate(float dt) {}
	virtual void RenderUpdate() = 0;

	virtual void ShutdownLocal(){}

	void ShutdownWindow();

	virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
	virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
	virtual void OnMouseMove(WPARAM btnState, int x, int y) {}

	virtual void KeyDown(WPARAM wParam){}
	virtual void KeyUp(WPARAM wParam) {}

protected:
	unsigned int fps{ 0 };

	int m_showCmd;
	HWND m_mainHandle;
	HINSTANCE m_hInstance;
	bool m_enable4xMsaa;
	bool m_appPaused{false};
	bool m_windowed;
	UINT m_4xMsaaQuality;

	ID3D11Device*			m_d3dDevice;
	IDXGISwapChain*			m_d3dSwapChain;
	ID3D11DeviceContext*	m_d3dImmediateContext;
	ID3D11RenderTargetView*	m_d3dRenderTargetView;
	ID3D11Texture2D*		m_d3dDepthStencilBuffer;
	ID3D11DepthStencilView*	m_d3dDepthStencilView;

	int m_clientWidth{ 1280 }, m_clientHeight{ 720 }, tick{ 0 };
	float m_aspectRatio{(float)m_clientWidth / (float)m_clientHeight };
	double prevTime, duration{ 0 }, tickDuration{ 0 };
	float tps{ (float)1 / TICKS_PER_SECOND };

	std::unique_ptr<GameTimer> m_gameTimer{ new GameTimer() };
};

