#pragma once
#include "MyWinHeader.h"

#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include "Position.h"
#include "Vertex.h"


#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3d10.lib")
#pragma comment (lib,"D3DCompiler.lib")


class Rhombus
{
public:
	Rhombus(HWND handle, Position pos, float height, float width);
	~Rhombus();
	void RenderTriangleFrame();
	void PresentFrame();
	void ClearRenderTarget();

	void SetCenter(Position newPos);
	void SetHeight(float height);
	void SetWidth(float width);
private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;


	ID3D10Blob* m_vertexShaderData;
	ID3D10Blob* m_pixelShaderData;


	HWND m_handle;

	void InitD3d();
	void SetViewport();
	void SetRenderTarget();
	void CreateBase3dObjects();
	void InitShaders();


	void UpdateVertices();

	Vertex* m_vertexArray;
	Position m_pos;
	float m_height;
	float m_width;
};
