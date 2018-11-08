#include "WinCanvas.h"

WinCanvas::WinCanvas() {

}

//WinCanvas::WinCanvas(ID3D11Device *device, ID3D11DeviceContext *context) {
//	this->device = device;
//	this->context = context;
//}

//This should be the proper way to deallocate a map
WinCanvas::~WinCanvas() {
	for (map<string, ID3D11ShaderResourceView*>::iterator itr = shaderResourceViews.begin(); itr != shaderResourceViews.end(); itr++) {
		delete itr->second;
	}
}

void WinCanvas::Initialize() {
	spriteBatch.reset(new SpriteBatch(context));
}

void WinCanvas::DeInitialize() {

}

//In the future, should create SRV files and render them on screen separately
void WinCanvas::Render() {
	if (device == nullptr || context == nullptr) return;
	CommonStates states(device);
	spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	RECT tempRect;
	tempRect.bottom = 50;
	tempRect.top = 0;
	tempRect.left = 0;
	tempRect.right = 50;
	for (map<string, ID3D11ShaderResourceView*>::iterator itr = shaderResourceViews.begin(); itr != shaderResourceViews.end(); itr++) {
		spriteBatch->Draw(itr->second, tempRect);
	}


	spriteBatch->End();
	context->OMSetBlendState(0, 0, 0xFFFFFFFF);
	context->OMSetDepthStencilState(0, 0);
}

void WinCanvas::AssignDeviceAndContext(ID3D11Device *device, ID3D11DeviceContext *context) {
	this->device = device;
	this->context = context;
}

//Not sure if proper way to add pointers into maps
void WinCanvas::CreateTextureFromFile(wstring filename, string textureName) {
	if (device == nullptr || context == nullptr) return;
	if (shaderResourceViews[textureName] != nullptr) return;

	ID3D11ShaderResourceView *ptr;
	shaderResourceViews.insert(std::pair<string, ID3D11ShaderResourceView*>(textureName, ptr));
	CreateWICTextureFromFile(device, filename.c_str(), nullptr, &shaderResourceViews[textureName]);
}