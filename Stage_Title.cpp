#include "Stage_Title.h"
namespace FIGHTING_GAME
{
	Stage_Title::Stage_Title(Renderer* renderer)
	{
		renderer_title = renderer;
		Model_num = 0;
	}
	HRESULT Stage_Title::InitStage() 
	{
		move_timer = 0;
		//3Dモデル
		/*{
			Model_data = new ThreeDModel_data[1];
			renderer_title->LoadModel(MODEL_head, &model_1);
			this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		}*/
		//2D画像
		{
			TextureName[0] = { "data/TEXTURE/title_1.png" };
			TextureName[1] = { "data/TEXTURE/title_2.png" };
			TextureName[2] = { "data/TEXTURE/title_3.png" };
			TextureName[3] = { "data/TEXTURE/title_4.png" };
			Plane_NOZ_data = new TwoDPlane_NOZ_data[TITLE_IMAGEMAX];
			for (int i = 0; i < TITLE_IMAGEMAX; i++)
			{
				Plane_NOZ_data[i].TextureName = TextureName[i];
				Plane_NOZ_data[i].g_Texture = NULL;
				D3DX11CreateShaderResourceViewFromFile(renderer_title->GetDevice(),
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
				renderer_title->GetDevice()->CreateBuffer(&bd, NULL, &Plane_NOZ_data[i].g_vertexBuffer);

				// プレイヤーの初期化
				
				switch (i)
				{
				case 0:
					Plane_NOZ_data[i].g_Use = true;
					Plane_NOZ_data[i].g_w = 100;
					Plane_NOZ_data[i].g_h = 100;
					Plane_NOZ_data[i].window_w = -100.0f;
					Plane_NOZ_data[i].window_h = -100.0f;
					Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
					break;
				case 1:
					Plane_NOZ_data[i].g_Use = false;
					Plane_NOZ_data[i].g_w = 100;
					Plane_NOZ_data[i].g_h = 100;
					Plane_NOZ_data[i].window_w = -50.0f;
					Plane_NOZ_data[i].window_h = -50.0f;
					Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
					break;
				case 2:
					Plane_NOZ_data[i].g_Use = true;
					Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
					Plane_NOZ_data[i].g_h = 100.0f;
					Plane_NOZ_data[i].window_w = -SCREEN_WIDTH / 2;
					Plane_NOZ_data[i].window_h = (SCREEN_HEIGHT * 3) / 4;
					Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
					break;
				case 3:
					Plane_NOZ_data[i].g_Use = true;
					Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
					Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
					Plane_NOZ_data[i].window_w = SCREEN_WIDTH / 2;
					Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
					Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
					break;
				
				}
			}
		}
		
		return S_OK;
	}
	void Stage_Title::UninitStage() 
	{
		for (int i = 0; i < TITLE_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_vertexBuffer)
			{
				Plane_NOZ_data[i].g_vertexBuffer->Release();
				Plane_NOZ_data[i].g_vertexBuffer = NULL;
			}
			Plane_NOZ_data[i].g_Texture->Release();
			Plane_NOZ_data[i].g_Texture = NULL;
		}
		//renderer_title->UnloadModel(&model_1);

		delete[] Plane_NOZ_data;
		//delete[] Model_data;
	}
	void Stage_Title::UpdateStage()
	{
		//Model_data[0].rot.y += D3DX_PI / 200.0f;

		
		for (int i = 0; i < 2; i++)
		{
			Plane_NOZ_data[i].window_w += 1;
			Plane_NOZ_data[i].window_h += 1;
			if (Plane_NOZ_data[0].window_w >= 0.0f)
			{
				Plane_NOZ_data[0].window_w = -100.0f;
			}
			if (Plane_NOZ_data[0].window_h >= (0.0f))
			{
				Plane_NOZ_data[0].window_h = -100.0f;
			}

			if (Plane_NOZ_data[1].window_w >= 50.0f)
			{
				Plane_NOZ_data[1].window_w = -50.0f;
			}
			if (Plane_NOZ_data[1].window_h >= 50.0f)
			{
				Plane_NOZ_data[1].window_h = -50.0f;
			}
			
			if (Plane_NOZ_data[i].g_Use == true)
			{
				if (move_timer < (TITLE_MOVEMAX/2))
				{
					Plane_NOZ_data[i].g_Color.a += 1.0f/ (TITLE_MOVEMAX / 2);
				}
				else if (move_timer >= (TITLE_MOVEMAX / 2))
				{
					Plane_NOZ_data[i].g_Color.a -= 1.0f / (TITLE_MOVEMAX / 2);
				}
			}
		}
		
		Plane_NOZ_data[2].window_w += 1;
		if (Plane_NOZ_data[2].window_w >= SCREEN_WIDTH / 2)
		{
			Plane_NOZ_data[2].window_w = -SCREEN_WIDTH / 2;
		}

		move_timer++;
		if (move_timer >= TITLE_MOVEMAX)
		{
			move_timer = 0;
			for (int i = 0; i < 2; i++)
			{
				if (Plane_NOZ_data[i].g_Use == true)
				{
					Plane_NOZ_data[i].g_Use = false;
				}
				else
				{
					Plane_NOZ_data[i].g_Use = true;
				}
			}
		}
		
		
	}
	void Stage_Title::DrawStage() 
	{
		for (int i = 0; i < TITLE_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_Use == true)
			{
				if (i == 0 || i == 1)
				{
					for (int k = 0; k < (SCREEN_WIDTH / Plane_NOZ_data[i].g_w) + 2; k++)
					{
						for (int j = 0; j < (SCREEN_HEIGHT / Plane_NOZ_data[i].g_h) + 2; j++)
						{
							renderer_title->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture,
								(Plane_NOZ_data[i].window_w + (k*Plane_NOZ_data[i].g_w)), (Plane_NOZ_data[i].window_h + (j*Plane_NOZ_data[i].g_h)), Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
						}
					}
				}
				else if (i == 2)
				{
					for (int k = 0; k < 2; k++)
					{
						renderer_title->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, 
							(Plane_NOZ_data[i].window_w+ (k*Plane_NOZ_data[i].g_w)), Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
					}
				}
				else if (i == 3)
				{
					renderer_title->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
				}
			}
		}
		

	}

	void Stage_Title::SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl)
	{
		Model_data[Model_num].use = use;
		Model_data[Model_num].pos = pos;
		Model_data[Model_num].rot = rot;
		Model_data[Model_num].rot_move = rot_move;
		Model_data[Model_num].scl = scl;
		Model_data[Model_num].color_a = 0;
		this->Model_num++;
	}
	void Stage_Title::Set2DPlane()
	{

	}
}