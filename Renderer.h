#include "Main.h"
namespace FIGHTING_GAME
{
#ifndef _RENDERER_H_
#define _RENDERER_H_
	class Renderer
	{
	private:
		D3D_FEATURE_LEVEL       g_FeatureLevel;

		ID3D11DeviceContext*    g_ImmediateContext;
		IDXGISwapChain*         g_SwapChain;
		ID3D11RenderTargetView* g_RenderTargetView;
		ID3D11DepthStencilView* g_DepthStencilView;

		ID3D11VertexShader*     g_VertexShader;
		ID3D11PixelShader*      g_PixelShader;
		ID3D11InputLayout*      g_VertexLayout;
		ID3D11Buffer*			g_WorldBuffer;
		ID3D11Buffer*			g_ViewBuffer;
		ID3D11Buffer*			g_ProjectionBuffer;
		ID3D11Buffer*			g_MaterialBuffer;
		ID3D11Buffer*			g_LightBuffer;
		ID3D11Buffer*			g_FogBuffer;
		ID3D11Buffer*			g_FuchiBuffer ;
		ID3D11Buffer*			g_CameraBuffer;

		ID3D11DepthStencilState* g_DepthStateEnable;
		ID3D11DepthStencilState* g_DepthStateDisable;

		ID3D11BlendState*		g_BlendStateNone;
		ID3D11BlendState*		g_BlendStateAlphaBlend;
		ID3D11BlendState*		g_BlendStateAdd;
		ID3D11BlendState*		g_BlendStateSubtract;
		BLEND_MODE				g_BlendStateParam;

		ID3D11RasterizerState*	g_RasterStateCullCW;
		ID3D11RasterizerState*	g_RasterStateCullCCW;

		MATERIAL_CBUFFER_BASE material_cbuffer;
		LIGHT_CBUFFER_BASE light_cbuffer;
		FOG_CBUFFER_BASE fog_cbuffer;
		FUCHI			g_Fuchi;
	public:
		ID3D11Device*           g_D3DDevice;
		ID3D11RasterizerState*	g_RasterStateCullOff;

		Renderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		void UninitRenderer();

		void Clear();
		void Present();
		void DebugTextOut(char* text, int x, int y);

		ID3D11Device *GetDevice();
		ID3D11DeviceContext *GetDeviceContext();

		void SetDepthEnable(bool Enable);
		void SetBlendState(BLEND_MODE bm);
		void SetCullingMode(CULL_MODE cm);
		void SetAlphaTestEnable(BOOL flag);

		void SetWorldViewProjection2D();
		void SetWorldMatrix(D3DXMATRIX *WorldMatrix);
		void SetViewMatrix(D3DXMATRIX *ViewMatrix);
		void SetProjectionMatrix(D3DXMATRIX *ProjectionMatrix);

		void SetMaterial(MATERIAL_BASE *material);

		void SetLightBuffer();
		void SetLightEnable(BOOL flag);
		void SetLight(int index, LIGHT_BASE* light);

		void SetFogBuffer();
		void SetFogEnable(BOOL flag);
		void SetFog(FOG_BASE* fog);

		void SetFuchi(int flag);
		void SetShaderCamera(D3DXVECTOR3 pos);

		void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);

		void SetSpriteLeftTop(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
		void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);

		void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
			float U, float V, float UW, float VH,
			D3DXCOLOR Color, float Rot);



		void Draw_3DModel(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL model, bool fuchi, int	color_a);
		void Draw_3DModel_Part(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL* model);
		

		void Draw_2DPlane_plural(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
			int	nNumVertexIndex, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld);
		void Draw_2DPlane_single(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
			int	nNumVertexIndex, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, D3DXMATRIX	mtxWorld);
		void Draw_2DPlane_NOZ(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, float px, float py, float pw, float ph, float tw, float th
			, float tx, float ty, D3DXCOLOR	color);
		void Draw_2DPlane_All2D(ID3D11Buffer *vertexBuffer, D3DXMATRIX mtxWorldParticle, D3DXMATRIX g_camera_mtxView, D3DXVECTOR3 scale, D3DXVECTOR3 pos,
			MATERIAL_BASE material, ID3D11ShaderResourceView	*g_Texture);

		void Draw_Collider_box(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
			D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld, Collider3D_Tag tag,
			float wx, float hy, float lz, float r);


		void DrawModel(DX11_MODEL *Model, int	color_a);
		void LoadObj(char *FileName, MODEL *Model, DX11_MODEL *D3DXModel);
		void LoadMaterial(char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum);

		void LoadModel(char *FileName, DX11_MODEL *Model);
		void UnloadModel(DX11_MODEL *Model);
	};
#endif
}