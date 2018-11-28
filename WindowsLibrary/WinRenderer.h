#pragma once

#include "..\CommonFiles\IRenderer.h"
#include <Windows.h>
#include <d3d11.h>
#include <sstream>
#include <string>
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "WICTextureLoader.h"
#include "WinMesh.h"
#include "Material.h"
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
		DirectionalLight Light;
		GameEntity* EntityStored;
		/*ID3D11ShaderResourceView* TestSRV;
		ID3D11SamplerState* sampler;*/
		Material* testMaterial;
	
	public:

		WinRenderer();
		virtual ~WinRenderer();
		void Init();
		void MessageLoop();
		bool MessageExist();
		void EndFrame();
		//void DrawQuad();
		void DrawMesh(IMesh *Mesh);
		void  LightingInfo(DirectionalLight light);

		static WinRenderer* WinRendererInstance;
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HRESULT InitWindow();
		HRESULT InitDirectX();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();
		SimpleVertexShader* getVertexShader();
		SimplePixelShader* getPixelShader();
		void LoadShaders();
		/*void LoadTextures();
		void InitializeMaterial();*/
		Material* getMaterial();
		glm::mat4x4 getworldMatrix();
		glm::mat4x4 getviewMatrix();
		glm::mat4x4 getprojectionMatrix();
		//Temp Variables
		/*DirectX::XMFLOAT4X4 worldMatrix;
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;*/
		glm::mat4x4 worldMatrix;
		glm::mat4x4 viewMatrix;
		glm::mat4x4 projectionMatrix;

		ID3D11Buffer * vertexBufferPointer;
		ID3D11Buffer * indexBufferPointer;
		//Vertex* vertices;
	};
