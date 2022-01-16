#include "Stage_Playeredit.h"
namespace FIGHTING_GAME
{
	Stage_Playeredit::Stage_Playeredit(Renderer* renderer, Input* g_input)
	{
		renderer_Playeredit= renderer;
		input = g_input;
	}
	HRESULT Stage_Playeredit::InitStage()
	{
		move_timer = 0;
		move_timer2=0;
		move_check=false;
		choice = 0;
		check=false;
		TextureName[0] = { "data/TEXTURE/title_1.png" };
		TextureName[1] = { "data/TEXTURE/title_2.png" };
		TextureName[2] = { "data/TEXTURE/edit_0.png" };
		TextureName[3] = { "data/TEXTURE/edit_1.png" };
		TextureName[4] = { "data/TEXTURE/edit_2.png" };
		TextureName[5] = { "data/TEXTURE/edit_2.png" };
		TextureName[6] = { "data/TEXTURE/edit_2.png" };
		TextureName[7] = { "data/TEXTURE/edit_0_1.png" };
		TextureName[8] = { "data/TEXTURE/edit_0_1_2.png" };
		TextureName[9] = { "data/TEXTURE/edit_0_2.png" };
		Plane_NOZ_data = new TwoDPlane_NOZ_data[PLAYEREDIT_IMAGEMAX];
		for (int i = 0; i < PLAYEREDIT_IMAGEMAX; i++)
		{
			Plane_NOZ_data[i].TextureName = TextureName[i];
			Plane_NOZ_data[i].g_Texture = NULL;
			D3DX11CreateShaderResourceViewFromFile(renderer_Playeredit->GetDevice(),
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
			renderer_Playeredit->GetDevice()->CreateBuffer(&bd, NULL, &Plane_NOZ_data[i].g_vertexBuffer);

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
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
				Plane_NOZ_data[i].window_w = SCREEN_WIDTH / 2;
				Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 3:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH / 8;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT / 8;
				Plane_NOZ_data[i].window_w = 150.0f;
				Plane_NOZ_data[i].window_h = 50.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 4:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH/8;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT/8;
				Plane_NOZ_data[i].window_w = 150.0f;
				Plane_NOZ_data[i].window_h = 150.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 5:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH / 8;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT / 8;
				Plane_NOZ_data[i].window_w = 150.0f;
				Plane_NOZ_data[i].window_h = 250.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 6:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH / 8;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT / 8;
				Plane_NOZ_data[i].window_w = 150.0f;
				Plane_NOZ_data[i].window_h = 350.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 7:
				Plane_NOZ_data[i].g_Use = false;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH ;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT ;
				Plane_NOZ_data[i].window_w = (SCREEN_WIDTH / 2)+10;
				Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 8:
				Plane_NOZ_data[i].g_Use = false;
				Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
				Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
				Plane_NOZ_data[i].window_w = (SCREEN_WIDTH / 2) + 10;
				Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			case 9:
				Plane_NOZ_data[i].g_Use = true;
				Plane_NOZ_data[i].g_w = 50.0f;
				Plane_NOZ_data[i].g_h = 70.0f;
				Plane_NOZ_data[i].window_w = 50.0f;
				Plane_NOZ_data[i].window_h = 50.0f;
				Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
				break;
			}
		}
	
		return S_OK;
	}
	void Stage_Playeredit::UninitStage()
	{
		for (int i = 0; i < PLAYEREDIT_IMAGEMAX; i++)
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
	void Stage_Playeredit::UpdateStage()
	{
		{
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
					if (move_timer < (100 / 2))
					{
						Plane_NOZ_data[i].g_Color.a += 1.0f / (100 / 2);
					}
					else if (move_timer >= (100 / 2))
					{
						Plane_NOZ_data[i].g_Color.a -= 1.0f / (100 / 2);
					}
				}
			}
			move_timer++;
			if (move_timer >= 100)
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
		
		switch (choice)
		{
		case 0:
			Plane_NOZ_data[9].window_h = 50.0f;
			if (input->GetKeyboardTrigger(DIK_RETURN)&& check == false&& move_check == false)
			{
				check = true;
			}
			else if (input->GetKeyboardTrigger(DIK_X) && check == true && move_check == true)
			{
				check = false;
				Plane_NOZ_data[7].g_Use = false;
			}
			else if (input->GetKeyboardTrigger(DIK_S) && check == false && move_check == false)
			{
				choice = 1;
			}

			if (move_check == false && check == true)
			{
				Plane_NOZ_data[3].g_w += SCREEN_WIDTH / 20;
				Plane_NOZ_data[3].g_h += SCREEN_HEIGHT / 20;
				Plane_NOZ_data[3].window_w += 57.5f;
				Plane_NOZ_data[3].window_h += 31.25f;
				if (Plane_NOZ_data[3].g_w >= SCREEN_WIDTH / 2)
				{
					Plane_NOZ_data[3].g_w = SCREEN_WIDTH / 2;
					Plane_NOZ_data[3].g_h = SCREEN_HEIGHT / 2;
					Plane_NOZ_data[3].window_w = 640.0f;
					Plane_NOZ_data[3].window_h = 300.0f;
					move_check = true;
					Plane_NOZ_data[7].g_Use = true;
				}
			}else if (move_check == true && check == false)
			{
				Plane_NOZ_data[3].g_w -= SCREEN_WIDTH / 20;
				Plane_NOZ_data[3].g_h -= SCREEN_HEIGHT / 20;
				Plane_NOZ_data[3].window_w -= 57.5f;
				Plane_NOZ_data[3].window_h -= 31.25f;
				if (Plane_NOZ_data[3].g_w <= SCREEN_WIDTH / 8)
				{
					Plane_NOZ_data[3].g_w = SCREEN_WIDTH / 8;
					Plane_NOZ_data[3].g_h = SCREEN_HEIGHT / 8;
					Plane_NOZ_data[3].window_w = 150.0f;
					Plane_NOZ_data[3].window_h = 50.0f;
					move_check = false;
				}
			}
			break;
		case 1:
			Plane_NOZ_data[9].window_h = 150.0f;
			if (input->GetKeyboardTrigger(DIK_RETURN) && check == false && move_check == false)
			{
				check = true;
			}
			else if (input->GetKeyboardTrigger(DIK_X) && check == true && move_check == true)
			{
				check = false;
				Plane_NOZ_data[8].g_Use = false;
			}
			else if (input->GetKeyboardTrigger(DIK_W) && check == false && move_check == false)
			{
				choice = 0;
			}
			else if (input->GetKeyboardTrigger(DIK_S) && check == false && move_check == false)
			{
				choice = 2;
			}

			if (move_check == false && check == true)
			{
				Plane_NOZ_data[4].g_w += SCREEN_WIDTH / 20;
				Plane_NOZ_data[4].g_h += SCREEN_HEIGHT / 20;
				Plane_NOZ_data[4].window_w += 57.5f;
				Plane_NOZ_data[4].window_h += 18.75f;
				if (Plane_NOZ_data[4].g_w >= SCREEN_WIDTH / 2)
				{
					Plane_NOZ_data[4].g_w = SCREEN_WIDTH / 2;
					Plane_NOZ_data[4].g_h = SCREEN_HEIGHT / 2;
					Plane_NOZ_data[4].window_w = 640.0f;
					Plane_NOZ_data[4].window_h = 300.0f;
					move_check = true;
					Plane_NOZ_data[8].g_Use = true;
				}
			}
			else if (move_check == true && check == false)
			{
				Plane_NOZ_data[4].g_w -= SCREEN_WIDTH / 20;
				Plane_NOZ_data[4].g_h -= SCREEN_HEIGHT / 20;
				Plane_NOZ_data[4].window_w -= 57.5f;
				Plane_NOZ_data[4].window_h -= 18.75f;
				if (Plane_NOZ_data[4].g_w <= SCREEN_WIDTH / 8)
				{
					Plane_NOZ_data[4].g_w = SCREEN_WIDTH / 8;
					Plane_NOZ_data[4].g_h = SCREEN_HEIGHT / 8;
					Plane_NOZ_data[4].window_w = 150.0f;
					Plane_NOZ_data[4].window_h = 150.0f;
					move_check = false;
				}
			}
			break;

			break;
		case 2:
			Plane_NOZ_data[9].window_h = 250.0f;
			if (input->GetKeyboardTrigger(DIK_RETURN) && check == false && move_check == false)
			{
				check = true;
			}
			else if (input->GetKeyboardTrigger(DIK_X) && check == true && move_check == true)
			{
				check = false;
				Plane_NOZ_data[8].g_Use = false;
			}
			else if (input->GetKeyboardTrigger(DIK_W) && check == false && move_check == false)
			{
				choice = 1;
			}
			else if (input->GetKeyboardTrigger(DIK_S) && check == false && move_check == false)
			{
				choice = 3;
			}

			if (move_check == false && check == true)
			{
				Plane_NOZ_data[5].g_w += SCREEN_WIDTH / 20;
				Plane_NOZ_data[5].g_h += SCREEN_HEIGHT / 20;
				Plane_NOZ_data[5].window_w += 57.5f;
				Plane_NOZ_data[5].window_h += 6.25f;
				if (Plane_NOZ_data[5].g_w >= SCREEN_WIDTH / 2)
				{
					Plane_NOZ_data[5].g_w = SCREEN_WIDTH / 2;
					Plane_NOZ_data[5].g_h = SCREEN_HEIGHT / 2;
					Plane_NOZ_data[5].window_w = 640.0f;
					Plane_NOZ_data[5].window_h = 300.0f;
					move_check = true;
					Plane_NOZ_data[8].g_Use = true;
				}
			}
			else if (move_check == true && check == false)
			{
				Plane_NOZ_data[5].g_w -= SCREEN_WIDTH / 20;
				Plane_NOZ_data[5].g_h -= SCREEN_HEIGHT / 20;
				Plane_NOZ_data[5].window_w -= 57.5f;
				Plane_NOZ_data[5].window_h -= 6.25f;
				if (Plane_NOZ_data[5].g_w <= SCREEN_WIDTH / 8)
				{
					Plane_NOZ_data[5].g_w = SCREEN_WIDTH / 8;
					Plane_NOZ_data[5].g_h = SCREEN_HEIGHT / 8;
					Plane_NOZ_data[5].window_w = 150.0f;
					Plane_NOZ_data[5].window_h = 250.0f;
					move_check = false;
				}
			}
			break;
		case 3:
			Plane_NOZ_data[9].window_h = 350.0f;
			if (input->GetKeyboardTrigger(DIK_RETURN) && check == false && move_check == false)
			{
				check = true;
			}
			else if (input->GetKeyboardTrigger(DIK_X) && check == true && move_check == true)
			{
				check = false;
				Plane_NOZ_data[8].g_Use = false;
			}
			else if (input->GetKeyboardTrigger(DIK_W) && check == false)
			{
				choice = 2;
			}
			if (move_check == false && check == true)
			{
				Plane_NOZ_data[6].g_w += SCREEN_WIDTH / 20;
				Plane_NOZ_data[6].g_h += SCREEN_HEIGHT / 20;
				Plane_NOZ_data[6].window_w += 57.5f;
				Plane_NOZ_data[6].window_h -= 6.25f;
				if (Plane_NOZ_data[6].g_w >= SCREEN_WIDTH / 2)
				{
					Plane_NOZ_data[6].g_w = SCREEN_WIDTH / 2;
					Plane_NOZ_data[6].g_h = SCREEN_HEIGHT / 2;
					Plane_NOZ_data[6].window_w = 640.0f;
					Plane_NOZ_data[6].window_h = 300.0f;
					move_check = true;
					Plane_NOZ_data[8].g_Use = true;
				}
			}
			else if (move_check == true && check == false)
			{
				Plane_NOZ_data[6].g_w -= SCREEN_WIDTH / 20;
				Plane_NOZ_data[6].g_h -= SCREEN_HEIGHT / 20;
				Plane_NOZ_data[6].window_w -= 57.5f;
				Plane_NOZ_data[6].window_h += 6.25f;
				if (Plane_NOZ_data[6].g_w <= SCREEN_WIDTH / 8)
				{
					Plane_NOZ_data[6].g_w = SCREEN_WIDTH / 8;
					Plane_NOZ_data[6].g_h = SCREEN_HEIGHT / 8;
					Plane_NOZ_data[6].window_w = 150.0f;
					Plane_NOZ_data[6].window_h = 350.0f;
					move_check = false;
				}
			}


			break;
		}

		if (input->GetKeyboardTrigger(DIK_RETURN)&& check==true && move_check == true&& choice==0)
		{
			GameDate::ChangePhaseCheck = MODE_INSTRUCTION;
		}
	}
	void Stage_Playeredit::DrawStage()
	{
		for (int i = 0; i < PLAYEREDIT_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_Use == true)
			{
				if (i == 0 || i == 1)
				{
					for (int k = 0; k < (SCREEN_WIDTH / Plane_NOZ_data[i].g_w) + 2; k++)
					{
						for (int j = 0; j < (SCREEN_HEIGHT / Plane_NOZ_data[i].g_h) + 2; j++)
						{
							renderer_Playeredit->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture,
								(Plane_NOZ_data[i].window_w + (k*Plane_NOZ_data[i].g_w)), (Plane_NOZ_data[i].window_h + (j*Plane_NOZ_data[i].g_h)), Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
						}
					}
				}
				else
				{
					renderer_Playeredit->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
				}
			}
		}

	}

}