

#include "stdafx.h"
#include "WinRenderer.h"

#ifdef _WIN32

	WinRenderer::WinRenderer()
	{
		x = 5;
		//WinRendererInstance = this;
	}

	int WinRenderer::Test()
	{
		return x;
	}

	void WinRenderer::Init()
	{
		hInstance = GetModuleHandle(0);

		HRESULT s = InitWindow();

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

	HRESULT WinRenderer::InitWindow()
	{
		//HWND hwndC = GetConsoleWindow();
		

		// Start window creation by filling out the
		// appropriate window class struct
		WNDCLASS wndClass = {}; // Zero out the memory
		wndClass.lpfnWndProc = WinRenderer::WindowProc;
		wndClass.hInstance = hInstance;						// Our app's handle
		wndClass.lpszClassName = L"Direct3DWindowClass";

		if (!RegisterClass(&wndClass))
		{
			// Get the most recent error
			DWORD error = GetLastError();

			// If the class exists, that's actually fine.  Otherwise,
			// we can't proceed with the next step.
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


		

		// Return an "everything is ok" HRESULT value
		return S_OK;

	}



#endif