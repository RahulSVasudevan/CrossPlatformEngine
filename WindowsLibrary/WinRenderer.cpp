
#include "stdafx.h"
#include "WinRenderer.h"


	WinRenderer::WinRenderer()
	{
		device = 0;
		context = 0;
		swapChain = 0;
		backBufferRTV = 0;
		depthStencilView = 0;

		width = 1280;
		height = 720;
		camera = new ICamera();
	}

	WinRenderer::~WinRenderer()
	{


		delete vertexShader;
		delete pixelShader;
		//delete camera;

		//DELETE SKY shaders

		delete skyVS;
		delete skyPS;

		if (skyDepthState) { skyDepthState->Release(); }
		if (skySRV) { skySRV->Release(); }
		if (skySampler) { skySampler->Release(); }
		if (skyRastState) { skyRastState->Release(); }

		if (depthStencilView) { depthStencilView->Release(); }
		if (backBufferRTV) { backBufferRTV->Release(); }

		if (swapChain) { swapChain->Release(); }
		if (context) { context->Release(); }
		if (device) { device->Release(); }
		if (rasterizer) { rasterizer->Release(); }
	}

	void WinRenderer::Init()
	{
		hInstance = GetModuleHandle(0);
		HRESULT status = InitWindow();
		camera->InitialiseCamera(width, height);
		status = InitDirectX();

		LoadShaders();

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		

		/*
		// Temp Code
		vec3 cameraPos = vec3(0.0f, 160.0f, 400.0f);
		vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
		//vec3 cameraDirection = normalize(cameraPos - cameraTarget);
		vec3 cameraDirection = vec3(0.0f,-0.5f,-1.0f);
		vec3 up = vec3(0.0f, 1.0f, 0.0f);
		vec3 cameraRight = normalize(cross(up, cameraDirection));

		viewMatrix = lookAt(cameraPos, cameraTarget, up);
		viewMatrix = transpose(viewMatrix);
		worldMatrix = mat4(1.0f);

		projectionMatrix = perspective(0.25f * 3.1415926535f, (float)width / height, 0.1f, 1000.0f);
		projectionMatrix = transpose(projectionMatrix);

		*/
		//XMMATRIX W = XMMatrixIdentity();
		//XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));

		//XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
		//XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
		//XMVECTOR up = XMVectorSet(0, 1, 0, 0);
		//XMMATRIX V = XMMatrixLookToLH(
		//	pos,     // The position of the "camera"
		//	dir,     // Direction the camera is looking
		//	up);     // "Up" direction in 3D space (prevents roll)
		//XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

		//XMMATRIX P = XMMatrixPerspectiveFovLH(
		//	0.25f * 3.1415926535f,		// Field of View Angle
		//	(float)width / height,		// Aspect ratio
		//	0.1f,						// Near clip plane distance
		//	100.0f);					// Far clip plane distance
		//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!


		//Vertex vertices[]
		//{
		//{ XMFLOAT3(+1.0f, +1.0f, +0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		//{ XMFLOAT3(-1.0f, +1.0f, +0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		//{ XMFLOAT3(+1.0f, -1.0f, +0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		//{ XMFLOAT3(-1.0f, -1.0f, +0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		//};


		//unsigned int indices[] = { 0, 2,1, 3, 1, 2 };

		//vertexBufferPointer = 0;
		//indexBufferPointer = 0;

		//D3D11_BUFFER_DESC vbd;
		//vbd.Usage = D3D11_USAGE_DEFAULT;
		//vbd.ByteWidth = sizeof(Vertex) * 4;
		//vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//vbd.CPUAccessFlags = 0;
		//vbd.MiscFlags = 0;
		//vbd.StructureByteStride = 0;

		//D3D11_SUBRESOURCE_DATA initialVertexData;
		//initialVertexData.pSysMem = vertices;

		//HRESULT hResult = device->CreateBuffer(&vbd, &initialVertexData, &vertexBufferPointer);


		////Index Buffer Creation

		//D3D11_BUFFER_DESC ibd;
		//ibd.Usage = D3D11_USAGE_DEFAULT;
		//ibd.ByteWidth = sizeof(unsigned int) * 6;
		//ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//ibd.CPUAccessFlags = 0;
		//ibd.MiscFlags = 0;
		//ibd.StructureByteStride = 0;


		//D3D11_SUBRESOURCE_DATA initialIndexData;
		//initialIndexData.pSysMem = indices;

		//hResult = device->CreateBuffer(&ibd, &initialIndexData, &indexBufferPointer);

		
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
		if (PeekMessage(&msg, NULL, 0, 0, 0))
		{
			if (msg.message == WM_QUIT)
				return false;
			else
			{
				GetMessage(&msg, NULL, 0, 0);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return true;
	}

	void WinRenderer::BeginFrame()
	{
		const float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		context->ClearRenderTargetView(backBufferRTV, color);
		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		context->RSSetState(rasterizer);
	}

	void WinRenderer::EndFrame()
	{
		swapChain->Present(0, 0);

	}

	//void WinRenderer::DrawVertices()
	//{
	//	const float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//	context->ClearRenderTargetView(backBufferRTV, color);
	//	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//	mat4x4 identity = mat4x4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
	//	vertexShader->SetMatrix4x4("world", (const float*)&identity);
	//	vertexShader->SetMatrix4x4("view", (const float*)&identity);
	//	vertexShader->SetMatrix4x4("projection", (const float*)&identity);

	//	vertexShader->CopyAllBufferData();

	//	vertexShader->SetShader();
	//	pixelShader->SetShader();

	//	UINT stride = sizeof(Vertex);
	//	UINT offset = 0;

	//	ID3D11Buffer * v = vertexBufferPointer;

	//	context->IASetVertexBuffers(0, 1, &vertexBufferPointer, &stride, &offset);
	//	context->IASetIndexBuffer(indexBufferPointer, DXGI_FORMAT_R32_UINT, 0);
	//	context->DrawIndexed(6,0,0);    

	//}

	void WinRenderer::DrawSkyMesh(void * vEntity)
	{
		GameEntity *entity = reinterpret_cast<GameEntity*>(vEntity);
		WinMesh* WMesh = entity->GetMesh();

		UINT stride = sizeof(VertexCommon);
		UINT offset = 0;

		ID3D11Buffer * v = WMesh->GetVertexBuffer();
		ID3D11Buffer * i = WMesh->GetIndexBuffer();

		context->IASetVertexBuffers(0, 1, &v, &stride, &offset);
		context->IASetIndexBuffer(WMesh->GetIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);

		glm::mat4 view = getviewMatrix();
		glm::mat4 projection = getprojectionMatrix();

		// Set up the sky shaders
		const float* convertedView = (const float*)value_ptr(view);
		const float* convertedProjection = (const float*)value_ptr(projection);
		skyVS->SetMatrix4x4("view", convertedView);
		skyVS->SetMatrix4x4("projection", convertedProjection);
		skyVS->CopyAllBufferData();
		skyVS->SetShader();

		skyPS->SetShaderResourceView("wallTexture", skySRV);
		skyPS->SetSamplerState("basicSampler", skySampler);
		skyVS->CopyAllBufferData();
		skyPS->SetShader();

		// Set up the render states necessary for the sky
		context->RSSetState(skyRastState);
		context->OMSetDepthStencilState(skyDepthState, 0);
		context->DrawIndexed(WMesh->indexSize, 0, 0);

		// When done rendering, reset any and all states for the next frame
		context->RSSetState(0);
		context->OMSetDepthStencilState(0, 0);

	}

	void WinRenderer::DrawMesh(void* vEntity, void *material)
	{
		GameEntity *entity = reinterpret_cast<GameEntity*>(vEntity);
		WinMesh* WMesh = entity->GetMesh();
		Material* mat = reinterpret_cast<Material*>(material);

		const float* world = (const float*)value_ptr(entity->GetWorldMatrix());
		const float* convertedView = (const float*)value_ptr(getviewMatrix());
		const float* convertedProjection = (const float*)value_ptr(getprojectionMatrix());
		vertexShader->SetMatrix4x4("world", world);
		vertexShader->SetMatrix4x4("view", convertedView);
		vertexShader->SetMatrix4x4("projection", convertedProjection);
		vertexShader->CopyAllBufferData();
		vertexShader->SetShader();

		pixelShader->SetShaderResourceView("wallTexture", mat->getSRV());
		pixelShader->SetSamplerState("basicSampler", mat->getsamplerState());

		pixelShader->CopyAllBufferData();
		pixelShader->SetShader();
		pixelShader->SetData("light", &Light, sizeof(DirectionalLight));
	

		UINT stride = sizeof(VertexCommon);
		UINT offset = 0;


		ID3D11Buffer * v = WMesh->GetVertexBuffer();

		context->IASetVertexBuffers(0, 1, &v, &stride, &offset);
		context->IASetIndexBuffer(WMesh->GetIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
		context->DrawIndexed(WMesh->indexSize, 0, 0);

		int a = 0;
	}

	void WinRenderer::LightingInfo(DirectionalLight light)
	{
		Light = light;
	}


	LRESULT WinRenderer::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:

		{

			unsigned char keycode = static_cast<unsigned char>(wParam);
			const bool wasPressed = lParam & 0x40000000;//0x400000000 is binary 0100 0000 0000 0000 0000 0000 0000 0000(31stbit).
			if (!wasPressed) // value is 0 if the key is being pressed
			{
				OutputDebugString(L"\ninside keydown switch case");
				Keyboard::getInstance()->OnKeyPressed(keycode);
			}
			return 0;
		}



		case WM_KEYUP:
		{

			unsigned char keycode = static_cast<unsigned char>(wParam);
			const bool wasPressed = lParam & 0x40000000; //The value is always 1 for a WM_KEYUP message.
			if (wasPressed)
			{
				OutputDebugString(L"\ninside keyup switch case");
				Keyboard::getInstance()->OnKeyReleased(keycode);
			}
			return 0;

		}
		case WM_CHAR:
		{

			unsigned char c = static_cast<unsigned char>(wParam);

			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed) // value is 0 if the key is being pressed
			{
				Keyboard::getInstance()->OnChar(c);
			}

			return 0;

		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}


	// Creating Window
	HRESULT WinRenderer::InitWindow()
	{
		WNDCLASS wndClass = {}; // Zero out the memory
		wndClass.lpfnWndProc = WinRenderer::WindowProc;
		wndClass.hInstance = hInstance;						// Our app's handle
		wndClass.lpszClassName = (L"window");

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

		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

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


		// Create a rasterizer state
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.DepthBias = 1000; // Multiplied by (smallest possible value > 0 in depth buffer)
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.SlopeScaledDepthBias = 1.0f;
		device->CreateRasterizerState(&rasterizerDesc, &rasterizer);


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

	ID3D11Device * WinRenderer::GetDevice()
	{
		return device;
	}

	ID3D11DeviceContext * WinRenderer::GetContext() {
		return context;
	}

	SimpleVertexShader * WinRenderer::getVertexShader()
	{
		return vertexShader;
	}

	SimplePixelShader * WinRenderer::getPixelShader()
	{
		return pixelShader;
	}

	void WinRenderer::LoadShaders()
	{


		CreateDDSTextureFromFile(device, context, L"../Assets/Materials/SunnyCubeMap.dds", 0, &skySRV);

		skyVS = new SimpleVertexShader(device, context);
		bool success1 = skyVS->LoadShaderFile(L"../CrossPlatformMain/skyVS.cso");

		skyPS = new SimplePixelShader(device, context);
		success1 = skyPS->LoadShaderFile(L"../CrossPlatformMain/skyPS.cso");


		// Create a sampler state that holds options for sampling
		// The descriptions should always just be local variables
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX; // Setting this allows for mip maps to work! (if they exist)

												// Ask DirectX for the actual object
		device->CreateSamplerState(&samplerDesc, &skySampler);

		// Create states for sky rendering
		D3D11_RASTERIZER_DESC rs = {};
		rs.CullMode = D3D11_CULL_NONE;
		rs.FillMode = D3D11_FILL_SOLID;
		device->CreateRasterizerState(&rs, &skyRastState);

		D3D11_DEPTH_STENCIL_DESC ds = {};
		ds.DepthEnable = true;
		ds.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		ds.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		device->CreateDepthStencilState(&ds, &skyDepthState);

		// Tell the input assembler stage of the pipeline what kind of
		// geometric primitives (points, lines or triangles) we want to draw.  
		// Essentially: "What kind of shape should the GPU draw with our data?"
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//Normal Vertex and Pixel shader loading
		vertexShader = new SimpleVertexShader(device, context);
		bool success = vertexShader->LoadShaderFile(L"../CrossPlatformMain/VertexShader.cso");

		pixelShader = new SimplePixelShader(device, context);
		success = pixelShader->LoadShaderFile(L"../CrossPlatformMain/PixelShader.cso");
	}

	void WinRenderer::checkInput(char a)
	{
		if (a == 'w')
			camera->moveFront();

		if (a == 's')
			camera->moveBack();

		if (a == 'a')
			camera->moveLeft();

		if (a == 'd')
			camera->moveRight();

	}

	glm::mat4x4 WinRenderer::getworldMatrix()
	{
		worldMatrix = camera->GetWorldMatrix();
		return worldMatrix;
	}

	glm::mat4x4 WinRenderer::getviewMatrix()
	{
		viewMatrix = camera->GetViewMatrix();
		return viewMatrix;
	}

	glm::mat4x4 WinRenderer::getprojectionMatrix()
	{
		projectionMatrix = camera->GetProjectionMatrix();
		return projectionMatrix;
	}


