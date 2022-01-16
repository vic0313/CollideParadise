#pragma once
#include "Main.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "Collider3D.h"
#include "Calculate.h"
#include "Collider3D.h"
#include "Stage_Game_map1.h"
#include "Weapon.h"
#include "Sound.h"
#include <time.h>
namespace FIGHTING_GAME
{
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define CHARACTERPART_MAX	(14)
	class CharacterAnimation
	{
	public:
		INTERPOLATION_DATA_BASE *body;
		INTERPOLATION_DATA_BASE *head;
		INTERPOLATION_DATA_BASE *leftarm_up;
		INTERPOLATION_DATA_BASE *leftarm_down;
		INTERPOLATION_DATA_BASE *lefthend;
		INTERPOLATION_DATA_BASE *righthend;
		INTERPOLATION_DATA_BASE *rightarm_up;
		INTERPOLATION_DATA_BASE *rightarm_down;
		INTERPOLATION_DATA_BASE *leftfoot_up;
		INTERPOLATION_DATA_BASE *leftfoot_down;
		INTERPOLATION_DATA_BASE *rightfoot_up;
		INTERPOLATION_DATA_BASE *rightfoot_down;
		INTERPOLATION_DATA_BASE *leftfoot_sole;
		INTERPOLATION_DATA_BASE *rightfoot_sole;
	};

	class Character
	{
	protected:
		enum Action_Switch_stage
		{
			action_no_switch = 0,
			lastaction_setting,
			lastaction_setting_over,
		};
		enum Human_Character_num
		{
			part_body = 0,
			part_head,
			part_leftarm_up,
			part_leftarm_down,
			part_lefthend,
			part_rightarm_up,
			part_rightarm_down,
			part_righthend,
			part_leftfoot_up,
			part_leftfoot_down,
			part_rightfoot_up,
			part_rightfoot_down,
			part_leftfoot_sole,
			part_rightfoot_sole,
			Character_collider_top,
			Character_collider_stand,
			Character_collider_front,
			Character_collider_behind,
			Character_collider_left,
			Character_collider_right,
			Character_collider_camera,
		};
		enum Character_Collider_Pos_num
		{
			top_Collider,
			down_Collider,
			front_Collider,
			behind_Collider,
			left_Collider,
			right_Collider,
		};
		enum Character_Pos_Update_num
		{
			XY_left_up = 0,
			XY_right_up,
			XY_left_down,
			XY_right_down,
			Xo,
			Xx,
			Yo,
			Yx,
			No_num,
		};
		enum Player_action
		{
			stand_bigsword = 0,
			action_walk,
			action_walk_back,
			action_jump,
			normal_attack_1,
			normal_attack_2,
			normal_attack_3,
			jump_attack_start,
			jump_attack_end,
			spin_attack,
			slip_move,
			be_attack,
			guard,
			no_action,
			no_action_battleing,
		};
		
		int					shadowIdx;			// 影のインデックス番号
		

		// クォータニオン
		D3DXQUATERNION		Quaternion;
		
		Stage_Game_map1* map1;
		Camera* camera;
		Renderer* renderer;
		Collider3D* collider;		//player用
		Collider3D* stage_collider;
		Sound* sound;

		int		*collider_c;
		bool	can_switch_action;
	public:
		Weapon* weapon;
		// 階層アニメーション用のメンバー変数
		INTERPOLATION_DATA_BASE	*part_anime;		// アニメデータのテーブル先頭アドレス
		INTERPOLATION_DATA_BASE	*part_anime_next;
		float					move_time;			// 実行時間
		float					move_time_next;			// 実行時間
		D3DXVECTOR3				anime_pos_temporary;
		D3DXVECTOR3				anime_rot_temporary;
		D3DXVECTOR3				anime_scl_temporary;
		D3DXVECTOR3				anime_pos_plus;
		D3DXVECTOR3				anime_rot_plus;
		D3DXVECTOR3				anime_scl_plus;
		Action_Switch_stage		anime_change;
		float				action_time_start;
		float				action_time_end;
		//collider
		int						collider_index;
		D3DXVECTOR3				pos_collider;
		D3DXVECTOR3				collider_wxhylz;
		//
		DX11_MODEL				model;				// モデル情報
		D3DXMATRIX				mtxWorld;			// ワールドマトリックス
		D3DXVECTOR3				pos;
		D3DXVECTOR3				pos_destine;
		D3DXVECTOR3				pos_origin;
		D3DXVECTOR3				reborn_pos;
		float HP;
		bool	dying;
		float ground_y;
		bool touch_ans;
		bool touch_top_ans;
		bool				use;				// 生きるかどうか
		float					spd;
		float					spd_y;
		D3DXVECTOR3				moveway_xyz;
		D3DXVECTOR3				rot;				// モデルの向き(回転)
		D3DXVECTOR3				rot_destine;
		D3DXVECTOR3				scl;				// モデルの大きさ(スケール)
		float rangex;
		float kyorix;
		Character	*part;
		bool	beAttack;

		virtual HRESULT InitCharacter(void);
		virtual void UninitCharacter(void);
		virtual void UpdateCharacter(void);
		virtual void DrawCharacter(void);
		virtual void Update_Pos();
		virtual void Animation_control(void);

		void RotRevise(void);
		void Character_edge_control(void);
		void Character_PosUpdate(void);
		bool Character_RayHitGround(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos, float start_UP);
		bool Character_RayHitTop(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos);
		bool Character_RayHitWall(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos, D3DXVECTOR3 ray_way);
		void Update_Collider(D3DXVECTOR3 pos_in, D3DXVECTOR3 rot_in);
	};
#endif
}