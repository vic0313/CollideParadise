#include "UI.h"
namespace FIGHTING_GAME
{


	UI::UI(Renderer* g_renderer, Player* g_player, Enemy* g_enemy, Stage_Game_map1* g_map1)
	{
		renderer= g_renderer;
		player= g_player;
		enemy= g_enemy;
		map1= g_map1;
	}
	HRESULT UI::InitUI()
	{
		TextureName[0] = { "data/TEXTURE/UI_0.png" };
		TextureName[1] = { "data/TEXTURE/UI_1.png" };
		TextureName[2] = { "data/TEXTURE/UI_background.png" };
		TextureName[3] = { "data/TEXTURE/UI_2.png" };
		TextureName[4] = { "data/TEXTURE/UI_2.png" };
		TextureName[5] = { "data/TEXTURE/UI_3.png" };
		Plane_NOZ_data = new TwoDPlane_NOZ_data[UI_MAX];
		for (int i = 0; i < UI_MAX; i++)
		{
			Plane_NOZ_data[i].TextureName = TextureName[i];
			Plane_NOZ_data[i].g_Texture = NULL;
			D3DX11CreateShaderResourceViewFromFile(renderer->GetDevice(),
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
			renderer->GetDevice()->CreateBuffer(&bd, NULL, &Plane_NOZ_data[i].g_vertexBuffer);

			switch (i)
			{
			case 0:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 180.0f;
				Plane_NOZ_data[i].g_h = 80.0f;
				Plane_NOZ_data[i].window_w = 120.0f;
				Plane_NOZ_data[i].window_h = 108.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 1:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 180.0f;
				Plane_NOZ_data[i].g_h = 80.0f;
				Plane_NOZ_data[i].window_w = 120.0f;
				Plane_NOZ_data[i].window_h = 108.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 2:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
				Plane_NOZ_data[i].window_w = SCREEN_WIDTH / 2;
				Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 3:
				//slip
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 60;
				Plane_NOZ_data[i].g_h = 80;
				Plane_NOZ_data[i].window_w = 890.0f;
				Plane_NOZ_data[i].window_h = 72;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(0.0, 0.0, 0.0, 1.0);
				break;
			case 4:
				//HP
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 30;
				Plane_NOZ_data[i].g_h = 40;
				Plane_NOZ_data[i].window_w = 142.0f;
				Plane_NOZ_data[i].window_h = 46;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(0.0, 0.0, 0.0, 1.0);
				break;
			case 5:
				//HP
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 80;
				Plane_NOZ_data[i].g_h = 120;
				Plane_NOZ_data[i].window_w = 250.0f;
				Plane_NOZ_data[i].window_h = 90.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			}
		}
		return S_OK;
	}
	void UI::Uninit_UI()
	{
		for (int i = 0; i < UI_MAX; i++)
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
	void UI::Update_UI()
	{
		if (player->air_move == true)
		{
			Plane_NOZ_data[5].g_Color.a = 0.5f;
		}
		else
		{
			Plane_NOZ_data[5].g_Color.a = 1.0f;
		}
	}
	void UI::Draw_UI()
	{
		for (int i = 0; i < UI_MAX; i++)
		{
			if (i == 1)
			{
				float a=(float)(player->Blow_point)/ PLAYER_BLOW_MAX;
				if (a == 0)continue;
				float c = Plane_NOZ_data[i].g_w * a;
				float b = (Plane_NOZ_data[i].window_w - (Plane_NOZ_data[i].g_w / 2)) + ((c)/2);
				
				//float b = 9 / PLAYER_BLOW_MAX;
				renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, b, Plane_NOZ_data[i].window_h, c, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, a, 1.0f, Plane_NOZ_data[i].g_Color);
			}
			else if (i == 3)
			{
				//slip
				float x = (float)((player->slip_num % 10)*0.1f);
				renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, x, 0.0f, 0.1f, 1.0f, Plane_NOZ_data[i].g_Color);
			}
			else if (i == 4)
			{
				//HP
				if (player->HP < 10)
				{
					float x = (float)(((int)(player->HP) % 10)*0.1f);
					if (player->dying == true)
					{
						x = 0;
					}
					renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, x, 0.0f, 0.1f, 1.0f, Plane_NOZ_data[i].g_Color);
				}
				else
				{
					float a = (float)(((int)(player->HP) % 10)*0.1f);
					float b = Plane_NOZ_data[i].window_w + (Plane_NOZ_data[i].g_w / 2);
					renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, b, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, a, 0.0f, 0.1f, 1.0f, Plane_NOZ_data[i].g_Color);
					a = (float)(((int)(player->HP/10) % 10)*0.1f);
					b = Plane_NOZ_data[i].window_w - (Plane_NOZ_data[i].g_w / 2);
					renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, b, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, a, 0.0f, 0.1f, 1.0f, Plane_NOZ_data[i].g_Color);
				}
				
			}
			else
			{
				renderer->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
			}
			
		}
	}

}