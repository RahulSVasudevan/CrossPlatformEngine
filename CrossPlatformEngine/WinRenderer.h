#pragma once

#include"..\CommonMain\IRenderer.h"
#include <Windows.h>
#include <d3d11.h>
#include <sstream>
#include <string>
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "WinMesh.h"

#pragma comment(lib, "d3d11.lib")


using namespace DirectX;

	struct Vertex
	{
		DirectX::XMFLOAT3 Position;	    // The position of the vertex
		DirectX::XMFLOAT4 Color;        // The color of the vertex
	};


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
		virtual ~WinRenderer();
		void Init();
		void MessageLoop();
		bool MessageExist();
		void EndFrame();
		void DrawQuad();
		void DrawMesh(IMesh *Mesh);
		HWND *GetWindowHandle();

		static WinRenderer* WinRendererInstance;
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HRESULT InitWindow();
		HRESULT InitDirectX();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();
		
		void LoadShaders();

		//Temp Variables
		DirectX::XMFLOAT4X4 worldMatrix;
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;

		ID3D11Buffer * vertexBufferPointer;
		ID3D11Buffer * indexBufferPointer;
		//Vertex* vertices;
	};
