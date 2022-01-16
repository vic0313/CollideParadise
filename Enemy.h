#pragma once
#include "Main.h"
#include "Character.h"
#include "Renderer.h"
#include "Player.h"
namespace FIGHTING_GAME
{
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define ENEMYMODEL_body				"data/MODEL/enemy_body.obj"
#define ENEMYMODEL_head				"data/MODEL/enemy_head_nobody.obj"
#define ENEMYMODEL_leftarm_up		"data/MODEL/enemy_left_arm_up.obj"
#define ENEMYMODEL_leftarm_down		"data/MODEL/enemy_left_arm_down.obj"
#define ENEMYMODEL_lefthend			"data/MODEL/enemy_left_hend.obj"
#define ENEMYMODEL_rightarm_up		"data/MODEL/enemy_right_arm_up.obj"
#define ENEMYMODEL_rightarm_down	"data/MODEL/enemy_right_arm_down.obj"
#define ENEMYMODEL_righthend		"data/MODEL/enemy_right_hend.obj"
#define ENEMYMODEL_leftfoot_up		"data/MODEL/enemy_left_foot_up.obj"
#define ENEMYMODEL_leftfoot_down	"data/MODEL/enemy_left_foot_down.obj"
#define ENEMYMODEL_rightfoot_up		"data/MODEL/enemy_right_foot_up.obj"
#define ENEMYMODEL_rightfoot_down	"data/MODEL/enemy_right_foot_down.obj"
#define ENEMYMODEL_leftfoot_sole	"data/MODEL/enemy_left_foot_sole.obj"
#define ENEMYMODEL_rightfoot_sole	"data/MODEL/enemy_right_foot_sole.obj"
#define ENEMYMODEL_discover	"data/MODEL/enemy_discover.obj"
#define ENEMY_MAX		(14)

#define ENEMYPART_MAX	(14)
#define ENEMY_ACTION_SWITCH_TIME (0.1f)
#define ENEMY_KIND_OF_ACTION (4)
#define ENEMY_MOVEWAY_CHANGE_STANDBY	(150)
#define ENEMY_MOVEWAY_CHANGE_MAX	(150)
#define	ONE_ENEMY_COLLIDER3D_MAX	(21)
#define ENEMY_HP_MAX	(10)
#define ENEMY_SERCH_RANGE	(400.0f)
	class Enemy:public Character
	{
	private:
		enum Enemy_action
		{
			stand_enemy = 0,
			walk_enemy,
			attack_enemy,
			be_attack_enemy,
		};
		Collider3D*			player_collider;
		CharacterAnimation*	enemyAnimation;
		Player*				player;
		Enemy_action		enemy_action_now;
		Enemy_action		enemy_action_next;
		DX11_MODEL*			enemy_model_body;
		DX11_MODEL*			enemy_model_head;
		DX11_MODEL*			enemy_model_leftarm_up;
		DX11_MODEL*			enemy_model_leftarm_down;
		DX11_MODEL*			enemy_model_lefthend;
		DX11_MODEL*			enemy_model_rightarm_up;
		DX11_MODEL*			enemy_model_leftfoot_up;
		DX11_MODEL*			enemy_model_leftfoot_down;
		DX11_MODEL*			enemy_model_leftfoot_sole;
		DX11_MODEL*			enemy_model_discover;
		
		int beattack_timer;
		bool	player_serch ;
		bool	attack_hit;
		D3DXVECTOR3 beAttack_moveway;
		int		enemy_num;
		int		moveway_change;
		void SetEnemyAnimation(void);
	public:
		Enemy();
		//HRESULT InitEnemy(Renderer* g_renderer, Collider3D* g_collider, Stage_Game_map1* g_map1, Player* g_player,int enemynum) ;
		HRESULT InitCharacter(void) override;
		void UninitCharacter(void) override;
		void UpdateCharacter(void) override;
		void DrawCharacter(void) override;
		void Update_Enemy_Pos(void);

		void Player_toward_rot(void);
		void Enemy_Attack(void);
		void Enemy_beAttack(void);
		void Enemy_Move(void);
		void Animation_control(void) override;
		void GetOthercollider(Collider3D* stage, Collider3D* player);
		void Get_Object(Renderer* g_renderer, Collider3D* g_collider, Stage_Game_map1* g_map1, Player* g_player, Sound* sound_g,int enemynum);
		void Get_Model(DX11_MODEL* body, DX11_MODEL* head, DX11_MODEL* leftarm_up, DX11_MODEL* leftarm_down, DX11_MODEL* lefthend, DX11_MODEL* rightarm_up, DX11_MODEL* leftfoot_up, DX11_MODEL* leftfoot_down, DX11_MODEL* leftfoot_sole, DX11_MODEL* discover);
	};
#endif
}