#include "Renderer.h"
namespace FIGHTING_GAME
{

	Renderer::Renderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) {
		g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
		g_D3DDevice = NULL;
		g_ImmediateContext = NULL;
		g_SwapChain = NULL;
		g_RenderTargetView = NULL;
		g_DepthStencilView = NULL;

		g_VertexShader = NULL;
		g_PixelShader = NULL;
		g_VertexLayout = NULL;
		g_WorldBuffer = NULL;
		g_ViewBuffer = NULL;
		g_ProjectionBuffer = NULL;
		g_MaterialBuffer = NULL;
		g_LightBuffer = NULL;
		g_FogBuffer = NULL;
		g_FuchiBuffer = NULL;
		g_CameraBuffer = NULL;
		this->InitRenderer(hInstance, hWnd, bWindow);
	}

		HRESULT Renderer::InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
		{
		HRESULT hr = S_OK;

		// デバイス、スワップチェーン、コンテキスト生成
		DWORD deviceFlags = 0;
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = SCREEN_WIDTH;
		sd.BufferDesc.Height = SCREEN_HEIGHT;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		//デバッグ文字出力用設定
#ifdef _DEBUG
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;
		deviceFlags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

		hr = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			deviceFlags,
			NULL,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&g_SwapChain,
			&g_D3DDevice,
			&g_FeatureLevel,
			&g_ImmediateContext);
		if (FAILED(hr))
			return hr;

		//デバッグ文字出力用設定
#ifdef _DEBUG
		hr = g_SwapChain->ResizeBuffers(0, SCREEN_WIDTH, SCREEN_HEIGHT, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE); // N.B. the GDI compatible flag
		if (FAILED(hr))
			return hr;
#endif

		// レンダーターゲットビュー生成、設定
		ID3D11Texture2D* pBackBuffer = NULL;
		g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		g_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_RenderTargetView);
		pBackBuffer->Release();



		//ステンシル用テクスチャー作成
		ID3D11Texture2D* depthTexture = NULL;
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = sd.BufferDesc.Width;
		td.Height = sd.BufferDesc.Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		td.SampleDesc = sd.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		g_D3DDevice->CreateTexture2D(&td, NULL, &depthTexture);

		//ステンシルターゲット作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = td.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Flags = 0;
		g_D3DDevice->CreateDepthStencilView(depthTexture, &dsvd, &g_DepthStencilView);


		g_ImmediateContext->OMSetRenderTargets(1, &g_RenderTargetView, g_DepthStencilView);


		// ビューポート設定
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)SCREEN_WIDTH;
		vp.Height = (FLOAT)SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		g_ImmediateContext->RSSetViewports(1, &vp);



		// ラスタライザステート作成
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_SOLID;
		//rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;
		rd.DepthClipEnable = TRUE;
		rd.MultisampleEnable = FALSE;
		g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullOff);

		rd.CullMode = D3D11_CULL_FRONT;
		g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCW);

		rd.CullMode = D3D11_CULL_BACK;
		g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCCW);

		// カリングモード設定（CCW）
		SetCullingMode(CULL_MODE_BACK);



		// ブレンドステートの作成
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.IndependentBlendEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateAlphaBlend);

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateNone);

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateAdd);

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateSubtract);

		// アルファブレンド設定
		SetBlendState(BLEND_MODE_ALPHABLEND);




		// 深度ステンシルステート作成
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.StencilEnable = FALSE;

		g_D3DDevice->CreateDepthStencilState(&depthStencilDesc, &g_DepthStateEnable);//深度有効ステート

	   //depthStencilDesc.DepthEnable = FALSE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		g_D3DDevice->CreateDepthStencilState(&depthStencilDesc, &g_DepthStateDisable);//深度無効ステート

	   // 深度ステンシルステート設定
		SetDepthEnable(true);



		// サンプラーステート設定
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		ID3D11SamplerState* samplerState = NULL;
		g_D3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

		g_ImmediateContext->PSSetSamplers(0, 1, &samplerState);



		// 頂点シェーダコンパイル・生成
		ID3DBlob* pErrorBlob;
		ID3DBlob* pVSBlob = NULL;
		hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR);
		}

		g_D3DDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_VertexShader);

		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		g_D3DDevice->CreateInputLayout(layout,
			numElements,
			pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(),
			&g_VertexLayout);

		pVSBlob->Release();


		// ピクセルシェーダコンパイル・生成
		ID3DBlob* pPSBlob = NULL;
		hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR);
		}

		g_D3DDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_PixelShader);

		pPSBlob->Release();


		// 定数バッファ生成
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		//ワールドマトリクス
		g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_WorldBuffer);
		g_ImmediateContext->VSSetConstantBuffers(0, 1, &g_WorldBuffer);
		g_ImmediateContext->PSSetConstantBuffers(0, 1, &g_WorldBuffer);

		//ビューマトリクス
		g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ViewBuffer);
		g_ImmediateContext->VSSetConstantBuffers(1, 1, &g_ViewBuffer);
		g_ImmediateContext->PSSetConstantBuffers(1, 1, &g_ViewBuffer);

		//プロジェクションマトリクス
		g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ProjectionBuffer);
		g_ImmediateContext->VSSetConstantBuffers(2, 1, &g_ProjectionBuffer);
		g_ImmediateContext->PSSetConstantBuffers(2, 1, &g_ProjectionBuffer);


		//マテリアル情報

		hBufferDesc.ByteWidth = sizeof(MATERIAL_CBUFFER_BASE);
		g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_MaterialBuffer);
		g_ImmediateContext->VSSetConstantBuffers(3, 1, &g_MaterialBuffer);
		g_ImmediateContext->PSSetConstantBuffers(3, 1, &g_MaterialBuffer);

		//ライト情報

		hBufferDesc.ByteWidth = sizeof(LIGHT_CBUFFER_BASE);
		g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_LightBuffer);
		g_ImmediateContext->VSSetConstantBuffers(4, 1, &g_LightBuffer);
		g_ImmediateContext->PSSetConstantBuffers(4, 1, &g_LightBuffer);

		//フォグ情報
		hBufferDesc.ByteWidth = sizeof(FOG_CBUFFER_BASE);
		 g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, & g_FogBuffer);
		 g_ImmediateContext->VSSetConstantBuffers(5, 1, & g_FogBuffer);
		 g_ImmediateContext->PSSetConstantBuffers(5, 1, & g_FogBuffer);

		 //縁取り
		 hBufferDesc.ByteWidth = sizeof(FUCHI);
		 g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_FuchiBuffer);
		 g_ImmediateContext->VSSetConstantBuffers(6, 1, &g_FuchiBuffer);
		 g_ImmediateContext->PSSetConstantBuffers(6, 1, &g_FuchiBuffer);

		 //カメラ
		 hBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
		 g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_CameraBuffer);
		 g_ImmediateContext->VSSetConstantBuffers(7, 1, &g_CameraBuffer);
		 g_ImmediateContext->PSSetConstantBuffers(7, 1, &g_CameraBuffer);


		// 入力レイアウト設定
		g_ImmediateContext->IASetInputLayout(g_VertexLayout);

		// シェーダ設定
		g_ImmediateContext->VSSetShader(g_VertexShader, NULL, 0);
		g_ImmediateContext->PSSetShader(g_PixelShader, NULL, 0);

		//ライト初期化


		ZeroMemory(&light_cbuffer, sizeof(LIGHT_CBUFFER_BASE));
		light_cbuffer.Direction[0] = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
		light_cbuffer.Diffuse[0] = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
		light_cbuffer.Ambient[0] = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		light_cbuffer.Flags[0].Type = LIGHT_TYPE_DIRECTIONAL;
		 SetLightBuffer();
		
		
		//マテリアル初期化
		 MATERIAL_BASE material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 SetMaterial(&material);

		 return S_OK;
	}
	
//=============================================================================
// 終了処理
//=============================================================================
	void Renderer::UninitRenderer()
	{
		// オブジェクト解放
		if ( g_DepthStateEnable)		 g_DepthStateEnable->Release();
		if ( g_DepthStateDisable)		 g_DepthStateDisable->Release();
		if ( g_BlendStateNone)			 g_BlendStateNone->Release();
		if ( g_BlendStateAlphaBlend)	 g_BlendStateAlphaBlend->Release();
		if ( g_BlendStateAdd)			 g_BlendStateAdd->Release();
		if ( g_BlendStateSubtract)		 g_BlendStateSubtract->Release();
		if ( g_RasterStateCullOff)		 g_RasterStateCullOff->Release();
		if ( g_RasterStateCullCW)		 g_RasterStateCullCW->Release();
		if ( g_RasterStateCullCCW)		 g_RasterStateCullCCW->Release();

		if ( g_WorldBuffer)				 g_WorldBuffer->Release();
		if ( g_ViewBuffer)				 g_ViewBuffer->Release();
		if ( g_ProjectionBuffer)		 g_ProjectionBuffer->Release();
		if ( g_MaterialBuffer)			 g_MaterialBuffer->Release();
		if ( g_LightBuffer)				g_LightBuffer->Release();
		if ( g_FogBuffer)				 g_FogBuffer->Release();

		if ( g_VertexLayout)			 g_VertexLayout->Release();
		if ( g_VertexShader)			 g_VertexShader->Release();
		if ( g_PixelShader)				g_PixelShader->Release();

		if ( g_ImmediateContext)		 g_ImmediateContext->ClearState();
		if ( g_RenderTargetView)		 g_RenderTargetView->Release();
		if ( g_SwapChain)				 g_SwapChain->Release();
		if ( g_ImmediateContext)		 g_ImmediateContext->Release();
		if ( g_D3DDevice)				 g_D3DDevice->Release();
	}



	//=============================================================================
	// バックバッファクリア
	//=============================================================================
	void Renderer::Clear()
	{
		// バックバッファクリア
		float ClearColor[4] = { 0.0f, 1.0f, 0.8f, 1.0f };
		 g_ImmediateContext->ClearRenderTargetView( g_RenderTargetView, ClearColor);
		 g_ImmediateContext->ClearDepthStencilView( g_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}


	//=============================================================================
	// プレゼント
	//=============================================================================
	void Renderer::Present()
	{
		 g_SwapChain->Present(0, 0);
	}


	//=============================================================================
	// デバッグ用テキスト出力
	//=============================================================================
	void Renderer::DebugTextOut(char* text, int x, int y)
	{
#ifdef _DEBUG
		HRESULT hr;

		//バックバッファからサーフェスを取得する
		IDXGISurface1* pBackSurface = NULL;
		hr =  g_SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackSurface);

		if (SUCCEEDED(hr))
		{
			//取得したサーフェスからデバイスコンテキストを取得する
			HDC hdc;
			hr = pBackSurface->GetDC(FALSE, &hdc);

			if (SUCCEEDED(hr))
			{
				//文字色を白に変更
				SetTextColor(hdc, RGB(255, 255, 255));
				//背景を透明に変更
				SetBkMode(hdc, TRANSPARENT);

				RECT rect;
				rect.left = 0;
				rect.top = 0;
				rect.right = SCREEN_WIDTH;
				rect.bottom = SCREEN_HEIGHT;

				//テキスト出力
				DrawText(hdc, text, strlen(text), &rect, DT_LEFT);

				//デバイスコンテキストを解放する
				pBackSurface->ReleaseDC(NULL);
			}
			//サーフェスを解放する
			pBackSurface->Release();

			//レンダリングターゲットがリセットされるのでセットしなおす
			 g_ImmediateContext->OMSetRenderTargets(1, & g_RenderTargetView,  g_DepthStencilView);
		}
#endif
	}

	//=============================================================================
// 頂点データ設定
//=============================================================================
	void Renderer::SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_BASE *vertex = (VERTEX_3D_BASE*)msr.pData;

		float hw, hh;
		hw = Width * 0.5f;		// コンピューターは割り算が苦手
		hh = Height * 0.5f;		// 掛け算の方が処理が速い

		// 指定された座標を中心に設定するプログラム

		// 頂点０番（左上の頂点）
		vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(U, V);

		// 頂点１番（右上の頂点）
		vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

		// 頂点２番（左下の頂点）
		vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

		// 頂点３番（右下の頂点）
		vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

		// 左上を原点として設定するプログラム
		//vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
		//vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[0].TexCoord = D3DXVECTOR2(U, V);

		//vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
		//vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

		//vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
		//vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

		//vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
		//vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);



		GetDeviceContext()->Unmap(buf, 0);

	}


	void Renderer::SetSpriteLeftTop(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_BASE *vertex = (VERTEX_3D_BASE*)msr.pData;

		// 左上を原点として設定するプログラム
		vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(U, V);

		vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

		vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

		vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);



		GetDeviceContext()->Unmap(buf, 0);

	}



	void Renderer::SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height,float U, float V, float UW, float VH,D3DXCOLOR color)
	{

		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_BASE *vertex = (VERTEX_3D_BASE*)msr.pData;

		float hw, hh;
		hw = Width * 0.5f;		// コンピューターは割り算が苦手
		hh = Height * 0.5f;		// 掛け算の方が処理が速い

		// 指定された座標を中心に設定するプログラム

		// 頂点０番（左上の頂点）
		vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
		vertex[0].Diffuse = color;
		vertex[0].TexCoord = D3DXVECTOR2(U, V);

		// 頂点１番（右上の頂点）
		vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
		vertex[1].Diffuse = color;
		vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

		// 頂点２番（左下の頂点）
		vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
		vertex[2].Diffuse = color;
		vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

		// 頂点３番（右下の頂点）
		vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
		vertex[3].Diffuse = color;
		vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

		GetDeviceContext()->Unmap(buf, 0);

	}


	void Renderer::SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
		float U, float V, float UW, float VH,
		D3DXCOLOR Color, float Rot)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D_BASE *vertex = (VERTEX_3D_BASE*)msr.pData;

		float hw, hh;
		hw = Width * 0.5f;		// コンピューターは割り算が苦手
		hh = Height * 0.5f;		// 掛け算の方が処理が速い

		// 指定された座標を中心に回転するプログラム
		float BaseAngle = atan2f(hh, hw);			// 中心点から頂点に対する角度
		D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
		float Radius = D3DXVec2Length(&temp);	// 中心点から頂点に対する距離

		// ここでアフィン変換（sincosのやつ）を使って4頂点を回転させる
		float x = X - cosf(BaseAngle + Rot) * Radius;
		float y = Y - sinf(BaseAngle + Rot) * Radius;
		vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

		x = X + cosf(BaseAngle - Rot) * Radius;
		y = Y - sinf(BaseAngle - Rot) * Radius;
		vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

		x = X - cosf(BaseAngle - Rot) * Radius;
		y = Y + sinf(BaseAngle - Rot) * Radius;
		vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

		x = X + cosf(BaseAngle + Rot) * Radius;
		y = Y + sinf(BaseAngle + Rot) * Radius;
		vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

		vertex[0].Diffuse = Color;
		vertex[1].Diffuse = Color;
		vertex[2].Diffuse = Color;
		vertex[3].Diffuse = Color;

		vertex[0].TexCoord = D3DXVECTOR2(U, V);
		vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
		vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

		GetDeviceContext()->Unmap(buf, 0);

	}

	


	ID3D11Device*  Renderer::GetDevice()
	{
		return  g_D3DDevice;
	}


	ID3D11DeviceContext* Renderer::GetDeviceContext()
	{
		return  g_ImmediateContext;
	}


	void Renderer::SetDepthEnable(bool Enable)
	{

		if (Enable)
			g_ImmediateContext->OMSetDepthStencilState(g_DepthStateEnable, NULL);
		else
			g_ImmediateContext->OMSetDepthStencilState(g_DepthStateDisable, NULL);

	}

	void Renderer::SetBlendState(BLEND_MODE bm)
	{
		g_BlendStateParam = bm;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		switch (g_BlendStateParam)
		{
		case BLEND_MODE_NONE:
			g_ImmediateContext->OMSetBlendState(g_BlendStateNone, blendFactor, 0xffffffff);
			break;
		case BLEND_MODE_ALPHABLEND:
			g_ImmediateContext->OMSetBlendState(g_BlendStateAlphaBlend, blendFactor, 0xffffffff);
			break;
		case BLEND_MODE_ADD:
			g_ImmediateContext->OMSetBlendState(g_BlendStateAdd, blendFactor, 0xffffffff);
			break;
		case BLEND_MODE_SUBTRACT:
			g_ImmediateContext->OMSetBlendState(g_BlendStateSubtract, blendFactor, 0xffffffff);
			break;
		}
	}

	void Renderer::SetCullingMode(CULL_MODE cm)
	{
		switch (cm)
		{
		case CULL_MODE_NONE:
			g_ImmediateContext->RSSetState(g_RasterStateCullOff);
			break;
		case CULL_MODE_FRONT:
			g_ImmediateContext->RSSetState(g_RasterStateCullCW);
			break;
		case CULL_MODE_BACK:
			g_ImmediateContext->RSSetState(g_RasterStateCullCCW);
			break;
		}
	}

	void Renderer::SetAlphaTestEnable(BOOL flag)
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		if (flag)
			blendDesc.AlphaToCoverageEnable = TRUE;
		else
			blendDesc.AlphaToCoverageEnable = FALSE;

		blendDesc.IndependentBlendEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;

		switch (g_BlendStateParam)
		{
		case BLEND_MODE_NONE:
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		case BLEND_MODE_ALPHABLEND:
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		case BLEND_MODE_ADD:
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		case BLEND_MODE_SUBTRACT:
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		}

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		ID3D11BlendState* blendState = NULL;
		g_D3DDevice->CreateBlendState(&blendDesc, &blendState);
		g_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

		if (blendState != NULL)
			blendState->Release();
	}

	void Renderer::SetWorldViewProjection2D()
	{
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		D3DXMatrixTranspose(&world, &world);
		this->GetDeviceContext()->UpdateSubresource(g_WorldBuffer, 0, NULL, &world, 0, 0);

		D3DXMATRIX view;
		D3DXMatrixIdentity(&view);
		D3DXMatrixTranspose(&view, &view);
		this->GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);

		D3DXMATRIX worldViewProjection;
		D3DXMatrixOrthoOffCenterLH(&worldViewProjection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
		D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);
		this->GetDeviceContext()->UpdateSubresource(g_ProjectionBuffer, 0, NULL, &worldViewProjection, 0, 0);
	}

	void Renderer::SetWorldMatrix(D3DXMATRIX *WorldMatrix)
	{
		D3DXMATRIX world;
		world = *WorldMatrix;
		D3DXMatrixTranspose(&world, &world);

		GetDeviceContext()->UpdateSubresource(g_WorldBuffer, 0, NULL, &world, 0, 0);
	}

	void Renderer::SetViewMatrix(D3DXMATRIX *ViewMatrix)
	{
		D3DXMATRIX view;
		view = *ViewMatrix;
		D3DXMatrixTranspose(&view, &view);

		GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);
	}

	void Renderer::SetProjectionMatrix(D3DXMATRIX *ProjectionMatrix)
	{
		D3DXMATRIX projection;
		projection = *ProjectionMatrix;
		D3DXMatrixTranspose(&projection, &projection);

		GetDeviceContext()->UpdateSubresource(g_ProjectionBuffer, 0, NULL, &projection, 0, 0);
	}

	void Renderer::SetMaterial(MATERIAL_BASE *material)
	{
		material_cbuffer.Diffuse = material->Diffuse;
		material_cbuffer.Ambient = material->Ambient;
		material_cbuffer.Specular = material->Specular;
		material_cbuffer.Emission = material->Emission;
		material_cbuffer.Shininess = material->Shininess;
		material_cbuffer.noTexSampling = material->noTexSampling;
		GetDeviceContext()->UpdateSubresource(g_MaterialBuffer, 0, NULL, &material_cbuffer, 0, 0);
	}

	void Renderer::SetLightBuffer()
	{
		GetDeviceContext()->UpdateSubresource(g_LightBuffer, 0, NULL, &light_cbuffer, 0, 0);
	}

	void Renderer::SetLightEnable(BOOL flag)
	{
		// フラグを更新する
		this->light_cbuffer.Enable = flag;

		SetLightBuffer();
	}

	void Renderer::SetLight(int index, LIGHT_BASE* pLight)
	{
		light_cbuffer.Position[index] = D3DXVECTOR4(pLight->Position.x, pLight->Position.y, pLight->Position.z, 0.0f);
		light_cbuffer.Direction[index] = D3DXVECTOR4(pLight->Direction.x, pLight->Direction.y, pLight->Direction.z, 0.0f);
		light_cbuffer.Diffuse[index] = pLight->Diffuse;
		light_cbuffer.Ambient[index] = pLight->Ambient;
		light_cbuffer.Flags[index].Type = pLight->Type;
		light_cbuffer.Attenuation[index].x = pLight->Attenuation;

		SetLightBuffer();
	}

	void Renderer::SetFogBuffer()
	{
		GetDeviceContext()->UpdateSubresource(g_FogBuffer, 0, NULL, &fog_cbuffer, 0, 0);
	}

	void Renderer::SetFogEnable(BOOL flag)
	{
		// フラグを更新する
		fog_cbuffer.Enable = flag;

		SetFogBuffer();
	}

	void Renderer::SetFog(FOG_BASE* pFog)
	{
		fog_cbuffer.Fog.x = pFog->FogStart;
		fog_cbuffer.Fog.y = pFog->FogEnd;
		fog_cbuffer.FogColor = pFog->FogColor;

		SetFogBuffer();
	}

	void Renderer::SetFuchi(int flag)
	{
		g_Fuchi.fuchi = flag;
		GetDeviceContext()->UpdateSubresource(g_FuchiBuffer, 0, NULL, &g_Fuchi, 0, 0);
	}


	void Renderer::SetShaderCamera(D3DXVECTOR3 pos)
	{
		D3DXVECTOR4 tmp = (D3DXVECTOR4)pos;
		GetDeviceContext()->UpdateSubresource(g_CameraBuffer, 0, NULL, &tmp, 0, 0);
	}


}