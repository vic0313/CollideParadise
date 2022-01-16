#include "Stage_Result.h"
namespace FIGHTING_GAME
{
	Stage_Result::Stage_Result(Renderer* renderer)
	{
		renderer_Result = renderer;
		Model_num = 0;
	}
	HRESULT Stage_Result::InitStage()
	{
		TextureName[0] = { "data/TEXTURE/result_1.png" };
		Plane_NOZ_data = new TwoDPlane_NOZ_data[RESULT_IMAGEMAX];
		for (int i = 0; i < RESULT_IMAGEMAX; i++)
		{
			Plane_NOZ_data[i].TextureName = TextureName[i];
			Plane_NOZ_data[i].g_Texture = NULL;
			D3DX11CreateShaderResourceViewFromFile(renderer_Result->GetDevice(),
				Plane_NOZ_data[i].TextureName,
				NULL,
				NULL,
				&Plane_NOZ_data[i].g_Texture,
				NULL);

			// 頂点バッファ生成
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D_BASE) * 4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			renderer_Result->GetDevice()->CreateBuffer(&bd, NULL, &Plane_NOZ_data[i].g_vertexBuffer);

			// プレイヤーの初期化

			switch (i)
			{
			case 0:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
				Plane_NOZ_data[i].window_w = SCREEN_WIDTH / 2;
				Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			}
		}
		return S_OK;
	}
	void Stage_Result::UninitStage()
	{
		for (int i = 0; i < RESULT_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_vertexBuffer)
			{
				Plane_NOZ_data[i].g_vertexBuffer->Release();
				Plane_NOZ_data[i].g_vertexBuffer = NULL;
			}
			Plane_NOZ_data[i].g_Texture->Release();
			Plane_NOZ_data[i].g_Texture = NULL;
		}
		delete[] Plane_NOZ_data;
	}
	void Stage_Result::UpdateStage()
	{

	}
	void Stage_Result::DrawStage()
	{
		for (int i = 0; i < RESULT_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_Use == true)
			{
				renderer_Result->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
			}
		}
	}

	void Stage_Result::SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl)
	{
		//Model_data[Model_num]->use = use;
		//Model_data[Model_num]->pos = pos;
		//Model_data[Model_num]->rot = rot;
		//Model_data[Model_num]->rot_move = rot_move;
		//Model_data[Model_num]->scl = scl;
		//
		//this->Model_num++;
	}
	void Stage_Result::Set2DPlane()
	{

	}
}