#include "Phase_Game.h"
namespace FIGHTING_GAME
{

	Phase_Game::Phase_Game(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera)
	{
		renderer_g = g_renderer;
		input_g = g_input;
		sound_g = g_sound;
		light_g = g_light;
		camera_g = g_camera;
		
		
	
	}
	HRESULT Phase_Game::InitGamePhase()
	{
		//stage
		Collider_Stage = new Collider3D(renderer_g, Stage_object);
		Collider_Stage->InitCollider3D();
		map1 = new Stage_Game_map1(renderer_g, Collider_Stage);
		map1->InitStage();
		//player
		Collider_Player = new Collider3D(renderer_g, Player_object);
		Collider_Player->InitCollider3D();
		Player_one = new Player(renderer_g, input_g, Collider_Player, camera_g, map1, sound_g);
		Player_one->InitCharacter();
		
		//enemy
		Collider_Enemy = new Collider3D(renderer_g, Enemy_object);
		Collider_Enemy->InitCollider3D();
		Enemy_all = new Enemy[ENEMY_MAX];
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			
			Enemy_all[i].Get_Object(renderer_g, Collider_Enemy, map1, Player_one, sound_g, i);
			Enemy_all[i].InitCharacter();
			if (i != 0)
			{
				Enemy_all[i].Get_Model(&Enemy_all[0].part[0].model, &Enemy_all[0].part[1].model, &Enemy_all[0].part[2].model, &Enemy_all[0].part[3].model, &Enemy_all[0].part[4].model, &Enemy_all[0].part[5].model, &Enemy_all[0].part[8].model, &Enemy_all[0].part[9].model, &Enemy_all[0].part[12].model, &Enemy_all[0].model);
				Enemy_all[i].weapon->Get_Model(&Enemy_all[0].weapon->model);
			}
		}
		//UI
		g_UI = new UI(renderer_g, Player_one, Enemy_all, map1);
		g_UI->InitUI();


		renderer_g->SetLightEnable(true);
		renderer_g->SetCullingMode(CULL_MODE_BACK);
		
		camera_g->g_ViewPortType = TYPE_FULL_SCREEN;
		camera_g->InitCamera();
		light_g->InitLight();
		sound_g->PlaySound(SOUND_LABEL_BGM_sample003);

		//Colliderì]ëó
		Player_one->GetOthercollider(Collider_Stage, Collider_Enemy);
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			Enemy_all[i].GetOthercollider(Collider_Stage, Collider_Player);
		}
		return S_OK;
	}

	void Phase_Game::Update_GamePhase()
	{

		if (input_g->GetKeyboardTrigger(DIK_6))
		{
			GameDate::DrawType = Draw_normal;
		}
		else if (input_g->GetKeyboardTrigger(DIK_7))
		{
			GameDate::DrawType = Draw_Both;
		}
		else if (input_g->GetKeyboardTrigger(DIK_8))
		{
			GameDate::DrawType = Draw_ColliderOnly;
		}
		
		light_g->UpdateLight();
		if(GameDate::GameMode== pasue)
		{
		
		}
		else if(GameDate::GameMode == camera_free)
		{
			camera_g->UpdateCamera();
		}
		else 
		{
			map1->UpdateStage();
			Player_one->UpdateCharacter();
			g_UI->Update_UI();
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				
				Enemy_all[i].UpdateCharacter();
			}
			camera_g->UpdateCamera();
		}
		
		
		
		
	}
	void Phase_Game::Draw_GamePhase()
	{
		switch (camera_g->g_ViewPortType)
		{
		case TYPE_FULL_SCREEN:
			camera_g->SetViewPort(TYPE_FULL_SCREEN);
			break;
		}
		//ÉvÉåÉCÉÑÇÃï`âÊ
		Player_one->DrawCharacter();
		//ÉGÉlÉ~Å[ÇÃï`âÊ
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (Enemy_all[i].use == true)
			{
				Enemy_all[i].DrawCharacter();
			}
		}
		//STAGEÇÃï`âÊ
		map1->DrawStage();
		
		//ColliderÇÃï`âÊ
		if (GameDate::DrawType == Draw_ColliderOnly || GameDate::DrawType == Draw_Both)
		{
			Collider_Stage->DrawCollider3D();
			Collider_Player->DrawCollider3D();
			Collider_Enemy->DrawCollider3D();
		}
		//ÉpÅ[ÉeÉBÉNÉãÇÃï`âÊ
		//UIÇÃï`âÊ
		g_UI->Draw_UI();
		
	}
	void Phase_Game::Uninit_GamePhase()
	{
		map1->UninitStage();
		Player_one->UninitCharacter();
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			Enemy_all[i].UninitCharacter();
		}
		Collider_Stage->UninitCollider3D();
		Collider_Player->UninitCollider3D();
		Collider_Enemy->UninitCollider3D();

		delete Collider_Stage;
		delete Collider_Player;
		delete Collider_Enemy;
		delete map1;
		delete Player_one;
		delete[] Enemy_all;
	}
}