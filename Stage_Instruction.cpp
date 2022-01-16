#include "Stage_Instruction.h"
namespace FIGHTING_GAME
{
	Stage_Instruction::Stage_Instruction(Renderer* renderer, Input* g_input)
	{
		renderer_Instruction = renderer;
		input = g_input;
	}
	HRESULT Stage_Instruction::InitStage()
	{
		TextureName[0] = { "data/TEXTURE/Instruction_1.png" };
		TextureName[1] = { "data/TEXTURE/Instruction_2.png" };
		TextureName[2] = { "data/TEXTURE/Instruction_3.png" };
		TextureName[3] = { "data/TEXTURE/Instruction_4.png" };
		TextureName[4] = { "data/TEXTURE/Instruction_5.png" };
		TextureName[5] = { "data/TEXTURE/Instruction_6.png" };
		choice = 0;
		Plane_NOZ_data = new TwoDPlane_NOZ_data[INSTRUCTION_IMAGEMAX];
		for (int i = 0; i < INSTRUCTION_IMAGEMAX; i++)
		{
			Plane_NOZ_data[i].TextureName = TextureName[i];
			Plane_NOZ_data[i].g_Texture = NULL;
			D3DX11CreateShaderResourceViewFromFile(renderer_Instruction->GetDevice(),
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
			renderer_Instruction->GetDevice()->CreateBuffer(&bd, NULL, &Plane_NOZ_data[i].g_vertexBuffer);

			
			Plane_NOZ_data[i].g_Use = true;
			Plane_NOZ_data[i].g_w = SCREEN_WIDTH;
			Plane_NOZ_data[i].g_h = SCREEN_HEIGHT;
			Plane_NOZ_data[i].window_w = SCREEN_WIDTH / 2;
			Plane_NOZ_data[i].window_h = SCREEN_HEIGHT / 2;
			Plane_NOZ_data[i].g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			for (int i = 2; i < INSTRUCTION_IMAGEMAX; i++)
			{
				Plane_NOZ_data[i].g_Use = false;
			}
			
		}
		Plane_NOZ_data[5].g_Use = true;
		Plane_NOZ_data[5].g_w = 20.0f;
		Plane_NOZ_data[5].g_h = 20.0f;
		Plane_NOZ_data[5].window_w = 192.0f;
		Plane_NOZ_data[5].window_h =  450.0f;
		return S_OK;
	}
	void Stage_Instruction::UninitStage()
	{
		for (int i = 0; i < INSTRUCTION_IMAGEMAX; i++)
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
	void Stage_Instruction::UpdateStage()
	{
		switch (choice)
		{
		case 0:
			Plane_NOZ_data[5].window_w = 192.0f;
			if (input->GetKeyboardTrigger(DIK_D))
			{
				Plane_NOZ_data[2].g_Use = true;
				Plane_NOZ_data[1].g_Use = false;
				choice = 1;
			}
			break;
		case 1:
			Plane_NOZ_data[5].window_w = 384.0f;
			if(input->GetKeyboardTrigger(DIK_A))
			{
				Plane_NOZ_data[1].g_Use = true;
				Plane_NOZ_data[2].g_Use = false;
				choice = 0;
			}
			else if (input->GetKeyboardTrigger(DIK_D))
			{
				Plane_NOZ_data[3].g_Use = true;
				Plane_NOZ_data[2].g_Use = false;
				choice = 2;
			}
			break;
		case 2:
			Plane_NOZ_data[5].window_w = 576.0f;
			if (input->GetKeyboardTrigger(DIK_A))
			{
				Plane_NOZ_data[2].g_Use = true;
				Plane_NOZ_data[3].g_Use = false;
				choice = 1;
			}
			else if (input->GetKeyboardTrigger(DIK_D))
			{
				Plane_NOZ_data[4].g_Use = true;
				Plane_NOZ_data[3].g_Use = false;
				choice = 3;
			}
			break;
		case 3:
			Plane_NOZ_data[5].window_w = 768.0f;
			if (input->GetKeyboardTrigger(DIK_A))
			{
				Plane_NOZ_data[3].g_Use = true;
				Plane_NOZ_data[4].g_Use = false;
				choice = 2;
			}
			break;
		}

	}
	void Stage_Instruction::DrawStage()
	{
		for (int i = 0; i < INSTRUCTION_IMAGEMAX; i++)
		{
			if (Plane_NOZ_data[i].g_Use == true)
			{
				renderer_Instruction->Draw_2DPlane_NOZ(Plane_NOZ_data[i].g_vertexBuffer, Plane_NOZ_data[i].g_Texture, Plane_NOZ_data[i].window_w, Plane_NOZ_data[i].window_h, Plane_NOZ_data[i].g_w, Plane_NOZ_data[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f, Plane_NOZ_data[i].g_Color);
			}
		}
	}

	void Stage_Instruction::SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl)
	{
		//Model_data[Model_num]->use = use;
		//Model_data[Model_num]->pos = pos;
		//Model_data[Model_num]->rot = rot;
		//Model_data[Model_num]->rot_move = rot_move;
		//Model_data[Model_num]->scl = scl;
		//this->Model_num++;
	}
	void Stage_Instruction::Set2DPlane()
	{

	}
}