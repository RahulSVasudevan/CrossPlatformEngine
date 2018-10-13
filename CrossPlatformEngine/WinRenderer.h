#pragma once

#include"IRenderer.h"
#include <Windows.h>
#include <d3d11.h>
#include <sstream>
#include <string>
#include "SimpleShader.h"

#pragma comment(lib, "d3d11.lib")


#ifdef _WIN32

	class WinRenderer : public IRenderer
	{
		int x;

		HINSTANCE	hInstance;		// The handle to the application
		HWND		hWnd;			// The handle to the window itself

									// Size of the window's client area
		unsigned int width;
		unsigned int height;

		// DirectX related objects and variables
		D3D_FEATURE_LEVEL		dxFeatureLevel;
		IDXGISwapChain*			swapChain;
		ID3D11Device*			device;
		ID3D11DeviceContext*	context;

		ID3D11RenderTargetView* backBufferRTV;
		ID3D11DepthStencilView* depthStencilView;

		SimpleVertexShader* vertexShader;
		SimplePixelShader* pixelShader;
	
	public:

		WinRenderer();
		int Test();
		void Init();
		void MessageLoop();
		bool MessageExist();
		void EndFrame();

		static WinRenderer* WinRendererInstance;
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HRESULT InitWindow();
		HRESULT InitDirectX();
		
		void LoadShaders();
	};

#endif