#pragma once
#include "Main.h"
#include "Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage_Game_map1.h"
#include "Stage.h"
namespace FIGHTING_GAME
{
#define UI_MAX (6)
	class UI:Stage
	{
	private:
		Renderer* renderer;
		Player* player;
		Enemy* enemy;
		Stage_Game_map1* map1;
		TwoDPlane_NOZ_data *Plane_NOZ_data;
		char* TextureName[UI_MAX];
	public:
		UI(Renderer* g_renderer, Player* g_player,Enemy* g_enemy, Stage_Game_map1* g_map1);
		HRESULT InitUI();
		void Uninit_UI();
		void Update_UI();
		void Draw_UI();


	};

}