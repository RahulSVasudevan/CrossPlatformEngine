#pragma once

#include "..\CommonFiles\IRenderer.h"
#include <Windows.h>
#include <d3d11.h>
#include <sstream>
#include <string>
#include "SimpleShader.h"
#include"Keyboard.h"
#include <DirectXMath.h>
#include "WinMesh.h"
#include "WinCamera.h"
#include "../packages/directxtk_desktop_2015.2018.11.20.1/include/DDSTextureLoader.h"

#include"GameEntity.h"
#include"..\CommonFiles\Maths.h"
#pragma comment(lib, "d3d11.lib")


using namespace DirectX;

	struct Vertex
	{
		DirectX::XMFLOAT3 Position;	    // The position of the vertex
		DirectX::XMFLOAT4 Color;        // The color of the vertex
	};


	class WinRenderer : public IRenderer
	{

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

		// SKY Shader data
		//SkyBox
		SimpleVertexShader* skyVS;
		SimplePixelShader* skyPS;
		//Pixel shader data
		ID3D11ShaderResourceView* skySRV;
		ID3D11SamplerState* skySampler;
		// Sky render states
		ID3D11RasterizerState* skyRastState;
		ID3D11DepthStencilState* skyDepthState;

		ID3D11RenderTargetView* backBufferRTV;
		ID3D11DepthStencilView* depthStencilView;
		ID3D11RasterizerState*  rasterizer;

		SimpleVertexShader* vertexShader;
		SimplePixelShader* pixelShader;
		DirectionalLight Light;


	
	public:

		WinRenderer();
		virtual ~WinRenderer();
		void Init();
		void MessageLoop();
		bool MessageExist();
		void BeginFrame();
		void EndFrame();
		//void DrawVertices();

		virtual void DrawSkyMesh(void *Mesh) override;
		virtual void DrawMesh(void *Mesh) override;
		void  LightingInfo(DirectionalLight light);
		void checkInput(char);

		static WinRenderer* WinRendererInstance;
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HRESULT InitWindow();
		HRESULT InitDirectX();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();
		SimpleVertexShader* getVertexShader();
		SimplePixelShader* getPixelShader();

		SimpleVertexShader* getSkyVS();
		SimplePixelShader* getskyPS();
		void LoadShaders();
		glm::mat4x4 getworldMatrix();
		glm::mat4x4 getviewMatrix();
		glm::mat4x4 getprojectionMatrix();

		glm::mat4x4 worldMatrix;
		glm::mat4x4 viewMatrix;
		glm::mat4x4 projectionMatrix;
		ID3D11Buffer * vertexBufferPointer;
		ID3D11Buffer * indexBufferPointer;
		//Vertex* vertices;
	};
