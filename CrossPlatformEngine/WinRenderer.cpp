

#include "stdafx.h"
#include "WinRenderer.h"

#ifdef _WIN32

	WinRenderer::WinRenderer()
	{
		device = 0;
		context = 0;
		swapChain = 0;
		backBufferRTV = 0;
		depthStencilView = 0;

		width = 1280;
		height = 720;
	}

	int WinRenderer::Test()
	{
		return x;
	}

	void WinRenderer::Init()
	{
		hInstance = GetModuleHandle(0);

		HRESULT status = InitWindow();
		status = InitDirectX();

		LoadShaders();

		const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };
		context->ClearRenderTargetView(backBufferRTV, color);
		context->ClearDepthStencilView(depthStencilView,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f,0);
	}

	void WinRenderer::MessageLoop()
	{
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	bool WinRenderer::MessageExist()
	{
		MSG msg = {};
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}

		return false;
	}

	void WinRenderer::EndFrame()
	{
		swapChain->Present(0, 0);
	}


	LRESULT WinRenderer::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	// Creating Window
	HRESULT WinRenderer::InitWindow()
	{
		WNDCLASS wndClass = {}; // Zero out the memory
		wndClass.lpfnWndProc = WinRenderer::WindowProc;
		wndClass.hInstance = hInstance;						// Our app's handle
		wndClass.lpszClassName = L"Direct3DWindowClass";

		if (!RegisterClass(&wndClass))
		{
			DWORD error = GetLastError();

			if (error != ERROR_CLASS_ALREADY_EXISTS)
				return HRESULT_FROM_WIN32(error);
		}
	
		hWnd = CreateWindowEx(0,
			wndClass.lpszClassName,
			wndClass.lpszClassName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,			// No parent window
			NULL,			// No menu
			hInstance,	// The app's handle
			NULL);			// No other windows in our application

						// Ensure the window was created properly
		if (hWnd == NULL)
		{
			DWORD error = GetLastError();
			return HRESULT_FROM_WIN32(error);
		}

		// The window exists but is not visible yet
		// We need to tell Windows to show it, and how to show it
		ShowWindow(hWnd, SW_SHOW);		

		return S_OK;
	}

	HRESULT WinRenderer::InitDirectX()
	{
		unsigned int deviceFlags = 0;

		// Create a description of how our swap
		// chain should work
		DXGI_SWAP_CHAIN_DESC swapDesc = {};
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Width = width;
		swapDesc.BufferDesc.Height = height;
		swapDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.Flags = 0;
		swapDesc.OutputWindow = hWnd;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Windowed = true;

		// Result variable for below function calls
		HRESULT hr = S_OK;

		// Attempt to initialize DirectX
		hr = D3D11CreateDeviceAndSwapChain(
			0,							// Video adapter (physical GPU) to use, or null for default
			D3D_DRIVER_TYPE_HARDWARE,	// We want to use the hardware (GPU)
			0,							// Used when doing software rendering
			deviceFlags,				// Any special options
			0,							// Optional array of possible verisons we want as fallbacks
			0,							// The number of fallbacks in the above param
			D3D11_SDK_VERSION,			// Current version of the SDK
			&swapDesc,					// Address of swap chain options
			&swapChain,					// Pointer to our Swap Chain pointer
			&device,					// Pointer to our Device pointer
			&dxFeatureLevel,			// This will hold the actual feature level the app will use
			&context);					// Pointer to our Device Context pointer
		if (FAILED(hr)) return hr;

		// The above function created the back buffer render target
		// for us, but we need a reference to it
		ID3D11Texture2D* backBufferTexture;
		swapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&backBufferTexture);

		// Now that we have the texture, create a render target view
		// for the back buffer so we can render into it.  Then release
		// our local reference to the texture, since we have the view.
		device->CreateRenderTargetView(
			backBufferTexture,
			0,
			&backBufferRTV);
		backBufferTexture->Release();

		// Set up the description of the texture to use for the depth buffer
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		// Create the depth buffer and its view, then 
		// release our reference to the texture
		ID3D11Texture2D* depthBufferTexture;
		hr = device->CreateTexture2D(&depthStencilDesc, 0, &depthBufferTexture);
		hr = device->CreateDepthStencilView(depthBufferTexture, 0, &depthStencilView);
		depthBufferTexture->Release();

		// Bind the views to the pipeline, so rendering properly 
		// uses their underlying textures
		context->OMSetRenderTargets(1, &backBufferRTV, depthStencilView);

		// Lastly, set up a viewport so we render into
		// to correct portion of the window
		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		context->RSSetViewports(1, &viewport);

		// Return the "everything is ok" HRESULT value
		return S_OK;

	}

	void WinRenderer::LoadShaders()
	{
		vertexShader = new SimpleVertexShader(device, context);
		vertexShader->LoadShaderFile(L"VertexShader.cso");

		pixelShader = new SimplePixelShader(device, context);
		pixelShader->LoadShaderFile(L"PixelShader.cso");
	}



#endif