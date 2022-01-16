#include "GAME.h"


namespace FIGHTING_GAME
{
	MODE	GameDate::GamePhase_now = MODE_GAME;
	MODE	GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
	Game_Mode GameDate::GameMode = normal;
	Draw_Type GameDate::DrawType = Draw_normal;

	//=============================================================================
	// ƒQ[ƒ€‰Šú‰»
	//=============================================================================
	HRESULT GAME::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
	{
		GameDate::GamePhase_now = MODE_TITLE;
		GameDate::ChangePhaseCheck = MODE_NO_CHANGE;

		renderer = new Renderer(hInstance, hWnd, bWindow);
		input = new Input(hInstance, hWnd);
		sound = new Sound(hWnd);
		camera=new Camera(renderer,input);
		light=new Light(renderer);
		
		renderer->SetLightEnable(true);
		renderer->SetCullingMode(CULL_MODE_BACK);
		g_Fade = new Phase_Fade(renderer, sound);

		
		this->ChangePhase(GameDate::GamePhase_now, GameDate::GamePhase_now);

		return S_OK;
	}
	
	//=============================================================================
	// ƒQ[ƒ€‰Šú‰»
	//=============================================================================
	void GAME::Run()
	{
		
		ShowCursor(FALSE);
		
		if (input->GetKeyboardTrigger(DIK_9))
		{
			GameDate::GameMode = normal;
		}else if (input->GetKeyboardTrigger(DIK_0))
		{
			GameDate::GameMode = camera_free;
		}

		if (input->GetKeyboardTrigger(DIK_O))
		{
			D3D11_RASTERIZER_DESC rd;
			ZeroMemory(&rd, sizeof(rd));
			rd.FillMode = D3D11_FILL_SOLID;
			rd.CullMode = D3D11_CULL_NONE;
			rd.DepthClipEnable = TRUE;
			rd.MultisampleEnable = FALSE;
			renderer->g_D3DDevice->CreateRasterizerState(&rd, &renderer->g_RasterStateCullOff);
		}
		if (input->GetKeyboardTrigger(DIK_P))
		{
			D3D11_RASTERIZER_DESC rd;
			ZeroMemory(&rd, sizeof(rd));
			rd.FillMode = D3D11_FILL_WIREFRAME;
			rd.CullMode = D3D11_CULL_NONE;
			rd.DepthClipEnable = TRUE;
			rd.MultisampleEnable = FALSE;
			renderer->g_D3DDevice->CreateRasterizerState(&rd, &renderer->g_RasterStateCullOff);
		}

		if (GameDate::ChangePhaseCheck != MODE_NO_CHANGE&& GameDate::ChangePhaseCheck != MODE_CHANGER_ALREADY)
		{
				switch (GameDate::ChangePhaseCheck)
				{
				case MODE_TITLE:
					g_Fade->SetFade(FADE_OUT, MODE_TITLE);
					GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
					break;
				case MODE_INSTRUCTION:
					 g_Fade->SetFade(FADE_OUT, MODE_INSTRUCTION);
					GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
					break;
				case MODE_PLAYEREDIT:
					 g_Fade->SetFade(FADE_OUT, MODE_PLAYEREDIT);
					GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
					break;
				case MODE_GAME:
					 g_Fade->SetFade(FADE_OUT, MODE_GAME);
					GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
					break;
				case MODE_RESULT:
					 g_Fade->SetFade(FADE_OUT, MODE_RESULT);
					GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
					break;
				}
			
		}
		if (GameDate::ChangePhaseCheck == MODE_CHANGER_ALREADY)
		{
			this->ChangePhase(GameDate::GamePhase_now, g_Fade->g_ModeNext);
			GameDate::ChangePhaseCheck = MODE_NO_CHANGE;
		}
		
		//Update
		input->UpdateInput();
		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
			//Update
			 g_Title->Update_TitlePhase();
			break;
		case MODE_INSTRUCTION:
			//Update
			 g_Instruction->Update_InstructionPhase();
			break;
		case MODE_PLAYEREDIT:
			//Update
			 g_Playeredit->Update_PlayereditPhase();
			break;
		case MODE_GAME:
			//Update
			 g_Game->Update_GamePhase();
			break;
		case MODE_RESULT:
			//Update
			 g_Result->Update_ResultPhase();
			break;
		}
		
		g_Fade->Update_FadePhase();

		
		//Draw
		renderer->Clear();
		camera->SetCamera();
		

		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
			 g_Title->Draw_TitlePhase();
			break;
		case MODE_INSTRUCTION:
			 g_Instruction->Draw_InstructionPhase();
			break;
		case MODE_PLAYEREDIT:
			 g_Playeredit->Draw_PlayereditPhase();
			break;
		case MODE_GAME:
			 g_Game->Draw_GamePhase();
			break;
		case MODE_RESULT:
			 g_Result->Draw_ResultPhase();
			break;
		}
		g_Fade->Draw_FadePhase();
		renderer->Present();
	}

	//=============================================================================
	// ƒQ[ƒ€I—¹ˆ—
	//=============================================================================
	void GAME::Uninit()
	{
		renderer->UninitRenderer();
		input->UninitInput();
		sound->UninitSound();
		camera->UninitCamera();
		g_Fade->Uninit_FadePhase();
		
		delete light;
		delete renderer;
		delete input;
		delete sound;
		delete camera;
		delete g_Fade;
		
	}
	

	void GAME::ChangePhase(MODE GamePhase_now, MODE GamePhase_next)
	{
		
		
		switch (GamePhase_now)
		{
		case MODE_TITLE:
			if (GamePhase_next != MODE_TITLE)
			{
				g_Title->Uninit_TitlePhase();
				delete g_Title;
			}
			break;
		case MODE_INSTRUCTION:
			g_Instruction->Uninit_InstructionPhase();
			delete g_Instruction;
			break;
		case MODE_PLAYEREDIT:
			 g_Playeredit->Uninit_PlayereditPhase();
			 delete g_Playeredit;
			break;
		case MODE_GAME:
			g_Game->Uninit_GamePhase();
			delete g_Game;
			break;
		case MODE_RESULT:
			
			g_Result->Uninit_ResultPhase();
			delete g_Result;
			
			break;
		}
		GameDate::GamePhase_now = GamePhase_next;

		
		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
			g_Title = new Phase_Title(renderer, input,sound, light, camera);
			g_Title->InitTitlePhase();
			break;
		case MODE_INSTRUCTION:
			g_Instruction = new Phase_Instruction( renderer, input, sound,light, camera);
			g_Instruction->InitInstructionPhase();
			break;
		case MODE_PLAYEREDIT:
			g_Playeredit = new Phase_Playeredit(renderer, input, sound, light, camera);
			g_Playeredit->InitPlayereditPhase();
			break;
		case MODE_GAME:
			g_Game = new Phase_Game(renderer, input, sound, light, camera);
			g_Game->InitGamePhase();
			break;
		case MODE_RESULT:
			g_Result = new Phase_Result(renderer, input, sound, light, camera);
			g_Result->InitResultPhase();
			break;
		}

	}
}