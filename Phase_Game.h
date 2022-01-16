#pragma once
#include "Main.h"
#include "Stage_Game_map1.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sound.h"
#include "Input.h"
#include "Light.h"
#include "Collider3D.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
namespace FIGHTING_GAME
{
#ifndef _PHASE_GAME_H_
#define _PHASE_GAME_H_
	class Phase_Game 
	{
	private:

		Stage_Game_map1* map1;
		Collider3D*		Collider_Stage;
		Player*			Player_one;
		Collider3D*		Collider_Player;
		Enemy*			Enemy_all;
		Collider3D*		Collider_Enemy;
		UI*				g_UI;

		Renderer* renderer_g;
		Camera* camera_g;
		Sound* sound_g;
		Light* light_g;
		Input* input_g;

	public:
		Phase_Game(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera);
		HRESULT InitGamePhase();
		void Uninit_GamePhase();
		void Update_GamePhase();
		void Draw_GamePhase();
	};
#endif
}