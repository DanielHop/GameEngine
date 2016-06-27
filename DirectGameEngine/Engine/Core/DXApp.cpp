#include "DXApp.h"

namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	DXApp* gd3dApp = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return gd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}




DXApp::DXApp(HINSTANCE hInstance, int show) :
	m_hInstance{ hInstance }, m_showCmd{show}
{
	gd3dApp = this;
}


DXApp::~DXApp()
{

}

bool DXApp::Start()
{
	if (!Init())
		return false;
	Run();
	Shutdown();
	return true;
}

bool DXApp::Init()
{
	return (InitWindow() && InitDirectX());
}

void DXApp::Run()
{
	MSG msg = { 0 };

	BOOL bRet = 1;

	float dt = 0;
	PreInit();
	InitGame();
	LateInit();
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_gameTimer->Tick();
			if (!m_appPaused)
			{
				CalculateFrameStats();
				dt += m_gameTimer->DeltaTime();
				if (dt >= 1.f / TICKS_PER_SECOND)
				{
					OnTickUpdate(m_gameTimer->DeltaTime());
					LateTickUpdate(m_gameTimer->DeltaTime());
					dt = 0;
					tick++;
				}
				if (tick == TICKS_PER_SECOND)
				{
					std::wstringstream ss;
					ss << "DirectX title - FPS: ";
					ss << fps;
					BOOL b = SetWindowText(m_mainHandle, LPCWSTR(ss.str().c_str()));
					DWORD d = GetLastError();
					fps = 0;
					tick = 0;
				}
				PrepareWindow();
				RenderUpdate();
				RenderWindow();
				fps++;
			}
			else
			{
				Sleep(100);
			}
		}
	}

}

void DXApp::PrepareWindow()
{
	m_d3dImmediateContext->ClearRenderTargetView(m_d3dRenderTargetView, reinterpret_cast<const float*>(&Colours::Black));
	m_d3dImmediateContext->ClearDepthStencilView(m_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

	m_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DXApp::RenderWindow()
{
	m_d3dSwapChain->Present(0, 0);
}

void DXApp::CalculateFrameStats()
{

}

void DXApp::TimerUpdate()
{
	double time = std::clock();

	duration += (time - prevTime) / (double)CLOCKS_PER_SEC;
	tickDuration += (time - prevTime) / (double)CLOCKS_PER_SEC;
	prevTime = time;

	fps++;

	if (duration >= 1)
	{
		
		fps = 0;
		duration = 0;
	}
}

LRESULT DXApp::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYDOWN:
		KeyDown(wParam);
		return 0;
	case WM_KEYUP:
		KeyUp(wParam);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DXApp::Shutdown()
{
	ShutdownLocal();
	ShutdownWindow();
	m_d3dDepthStencilView->Release();
	m_d3dSwapChain->Release();
	m_d3dRenderTargetView->Release();
	m_d3dDepthStencilBuffer->Release();
	m_d3dDevice->Release();
	m_d3dImmediateContext->Release();

}

bool DXApp::InitWindow()
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
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
		m_clientWidth, m_clientHeight,
		0, 0, m_hInstance, 0);

	if (m_mainHandle == 0)
	{
		MessageBox(0, L"Creating of window failed", 0, 0);
		return false;
	}

	ShowWindow(m_mainHandle, m_showCmd);
	UpdateWindow(m_mainHandle);

	return true;
}

bool DXApp::InitDirectX()
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featurelvl;
	HRESULT hr = D3D11CreateDevice(
		0,				//default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlags,
		0, 0,
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&featurelvl,
		&m_d3dImmediateContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"Creation of Context failed", 0, 0);
		return false;
	}

	if (featurelvl != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"DirectX11 not supported", 0, 0);
		return false;
	}

	m_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);
	assert(m_4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_clientWidth;
	sd.BufferDesc.Height = m_clientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (m_enable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow =m_mainHandle;
	sd.Windowed = m_windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice* dxgiDevice = 0;
	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	dxgiFactory->CreateSwapChain(m_d3dDevice, &sd, &m_d3dSwapChain);
	//NO ALT-ENTER
	dxgiFactory->MakeWindowAssociation(m_mainHandle, DXGI_MWA_NO_ALT_ENTER);

	UINT i = 0;
	IDXGIAdapter* pAdapter;
	std::vector<IDXGIAdapter*> vAdapters;
	while (dxgiFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		//pAdapter->CheckInterfaceSupport(__uuidof(DIRECT3D_VERSION), DIRECT3D_11.0);
		i++;
	}

	//MessageBox(0, LPCWSTR(std::to_string(vAdapters.size()).c_str()), 0, 0);

	for (auto a : vAdapters)a->Release();
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	ID3D11Texture2D* backBuffer;
	m_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&backBuffer));
	m_d3dDevice->CreateRenderTargetView(backBuffer, 0, &m_d3dRenderTargetView);
	backBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = m_clientWidth;
	depthStencilDesc.Height = m_clientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	if (m_enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 0;
	}
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	m_d3dDevice->CreateTexture2D(&depthStencilDesc,
		0,
		&m_d3dDepthStencilBuffer);

	m_d3dDevice->CreateDepthStencilView(m_d3dDepthStencilBuffer,
		0,
		&m_d3dDepthStencilView);

	m_d3dImmediateContext->OMSetRenderTargets(1, &m_d3dRenderTargetView, m_d3dDepthStencilView);

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
	vp.Width	= static_cast<float>(m_clientWidth);
	vp.Height	= static_cast<float>(m_clientHeight);
	vp.MinDepth = 0.f;
	vp.MaxDepth = 0.f;

	m_d3dImmediateContext->RSSetViewports(1, &vp);

	return true;
}

void DXApp::ShutdownWindow()
{

}