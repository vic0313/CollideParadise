#include "Main.h"
#include "Character.h"
#include "Input.h"
#include "Enemy.h"
#include "Sound.h"
namespace FIGHTING_GAME
{
#ifndef _PLAYER_H_
#define _PLAYER_H_
#define PLAYERMODEL_body			"data/MODEL/player_body.obj"
#define PLAYERMODEL_head			"data/MODEL/player_head_nobody.obj"
#define PLAYERMODEL_leftarm_up		"data/MODEL/player_left_arm_up.obj"
#define PLAYERMODEL_leftarm_down	"data/MODEL/player_left_arm_down.obj"
#define PLAYERMODEL_lefthend		"data/MODEL/player_left_hend.obj"
#define PLAYERMODEL_rightarm_up		"data/MODEL/player_right_arm_up.obj"
#define PLAYERMODEL_rightarm_down	"data/MODEL/player_right_arm_down.obj"
#define PLAYERMODEL_righthend		"data/MODEL/player_right_hend.obj"
#define PLAYERMODEL_leftfoot_up		"data/MODEL/player_left_foot_up.obj"
#define PLAYERMODEL_leftfoot_down	"data/MODEL/player_left_foot_down.obj"
#define PLAYERMODEL_rightfoot_up	"data/MODEL/player_right_foot_up.obj"
#define PLAYERMODEL_rightfoot_down	"data/MODEL/player_right_foot_down.obj"
#define PLAYERMODEL_leftfoot_sole	"data/MODEL/player_left_foot_sole.obj"
#define PLAYERMODEL_rightfoot_sole	"data/MODEL/player_right_foot_sole.obj"

#define PLAYER_MOVE_SPD_PLUS	(1.2f)
#define PLAYER_MOVE_SPD_MAX	(5)
#define PLAYER_MOVE_AIRSPD_PLUS	(0.5f)
#define PLAYER_MOVE_SPD_BACK_MAX	(2)
#define PLAYER_MOVE_SPD_SIDEBACK_MAX	(3)
#define PLAYER_MOVE_SPD_SLIP	(10)

#define PLAYER_MOVE_SPD_NORMALATTACK	(3)
#define PLAYER_MOVE_SPD_AIRATTACK	(7)
#define PLAYER_MOVE_SPD_AIRDOWNATTACK	(12)

#define  PLAYERPART_MAX	(14)

#define PLAYER_KIND_OF_ACTION	(13)
#define PLAYER_ACTION_SWITCH_TIME  (0.1f)
#define PLAYER_ACTION_JUMP_SWITCH_TIME  (0.1f)
#define PLAYER_SLIP_MAX  (2)
#define  PLAYER_HP_MAX	(10)
#define  PLAYER_BLOW_MAX	(5)
	class Player_movepoint_CONTROL
	{
	public:
		//ãLò^ópÇÃïœêî
		D3DXVECTOR3 Hitpoint_pos[4];//ç°ÇÃîªíËÇÃPOINTÇÃãLò^
		D3DXVECTOR3 moveway[4];//ç°ÇÃîªíËPOSÇ©ÇÁHITPOINTÇ‹Ç≈ÇÃå¸ó ãLò^
		D3DXVECTOR3 Hitpoint_NormalWall[4];//ç°ÇÃîªíËÇÃHITPOINTÇÃñ@å¸ó ãLò^
		float kyori[4];//ç°ÇÃîªíËÇÃPOINTÇ∆RAYCASTÇÃHITPOINTÇÃãóó£ãLò^
		int min_num = 0;
	};

	class Player:public Character
	{
	private:
		enum MoveSpd_control
		{
			no_move = 0,
			move_normal,
			back,
			side_back,
		};
		
		
		
		
		
		//MoveSpd_control		spd_control;
		//MoveSpd_control		spd_control_next;
		Collider3D*			enemy_collider;
		Input* input;
		
		CharacterAnimation*	playerAnimation;
		

		void PlayerInput(void);
		void SetPlayerAnimation(void);
	public:
		bool air_move;
		int slip_num;
		Player_action		player_action_now;
		Player_action		player_action_next;
		int		Blow_point;

		Player(Renderer* g_renderer,Input* g_input,Collider3D* g_collider, Camera* g_camera, Stage_Game_map1* g_map1,Sound* g_sound);
		HRESULT InitCharacter(void) override;
		void UninitCharacter(void) override;
		void UpdateCharacter(void) override;
		void DrawCharacter(void) override;
		void Update_Player_Pos(void);
		
		void Animation_control(void) override;
		void GetOthercollider(Collider3D* stage, Collider3D* g_enemy) ;
		void SetWeapon(Weapon* g_weapon);
		void Speed_control(void);
	};


#endif
}