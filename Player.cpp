#include "Player.h"
#include <algorithm>
namespace FIGHTING_GAME
{

	Player::Player(Renderer* g_renderer, Input* g_input, Collider3D* g_collider,Camera* g_camera, Stage_Game_map1* g_map1,Sound* g_sound)
	{
		renderer = g_renderer;
		input = g_input;
		collider = g_collider;
		camera = g_camera;
		map1 = g_map1;
		sound = g_sound;
		weapon = new Weapon(renderer);
		
	}
	HRESULT Player::InitCharacter()
	{
		//Player用アニメーションを設置
		this->SetPlayerAnimation();
		
		//Playerの初期データを設置
		{
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pos_destine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			moveway_xyz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			spd = 0.0f;
			spd_y = 0.0f;
			collider_wxhylz = D3DXVECTOR3(30.0f, 80.0f, 30.0f); //playerのPOSを制御のcollider
			player_action_now= stand_bigsword;
			//player_action_now = normal_attack_1;
			player_action_next= stand_bigsword;
			//player_action_next = normal_attack_1;
			can_switch_action = true;
			air_move = false;
			slip_num = PLAYER_SLIP_MAX;
		}

		//Playerのモデルpart物件を設立
		part = new Character[PLAYERPART_MAX];
		//Playerの全てのcolliderナンバーを設立
		collider_c = new int[PLAYERCOLLIDER_MAX];
		//Player用モデルをLoadする
		{
			renderer->LoadModel(PLAYERMODEL_body, &part[part_body].model);
			renderer->LoadModel(PLAYERMODEL_head, &part[part_head].model);
			renderer->LoadModel(PLAYERMODEL_leftarm_up, &part[part_leftarm_up].model);
			renderer->LoadModel(PLAYERMODEL_leftarm_down, &part[part_leftarm_down].model);
			renderer->LoadModel(PLAYERMODEL_lefthend, &part[part_lefthend].model);
			renderer->LoadModel(PLAYERMODEL_rightarm_up, &part[part_rightarm_up].model);
			//renderer->LoadModel(PLAYERMODEL_rightarm_down, &part[part_rightarm_down].model);
			//renderer->LoadModel(PLAYERMODEL_righthend, &part[part_righthend].model);
			renderer->LoadModel(PLAYERMODEL_leftfoot_up, &part[part_leftfoot_up].model);
			renderer->LoadModel(PLAYERMODEL_leftfoot_down, &part[part_leftfoot_down].model);
			//renderer->LoadModel(PLAYERMODEL_rightfoot_up, &part[part_rightfoot_up].model);
			//renderer->LoadModel(PLAYERMODEL_rightfoot_down, &part[part_rightfoot_down].model);
			renderer->LoadModel(PLAYERMODEL_leftfoot_sole, &part[part_leftfoot_sole].model);
			//renderer->LoadModel(PLAYERMODEL_rightfoot_sole, &part[part_rightfoot_sole].model);
		}
		//Playerのモデルpart物件の最初の場所と　collider大きさと場所を設立
		{
			part[part_body].pos_origin = D3DXVECTOR3(0.0f, 47.0f, 0.0f);
			part[part_body].pos_collider = D3DXVECTOR3(0.0f, 47.0f, 0.0f);
			part[part_body].collider_wxhylz = D3DXVECTOR3(17.0f, 28.0f, 15.0f);

			part[part_head].pos_origin = D3DXVECTOR3(0.0f, 68.0f, 0.0f);
			part[part_head].pos_collider = D3DXVECTOR3(0.0f, 68.0f, 0.0f);
			part[part_head].collider_wxhylz = D3DXVECTOR3(15.0f, 17.0f, 15.0f);

			part[part_leftarm_up].pos_origin = D3DXVECTOR3(12.0f, 60.0f, 0.0f);
			part[part_leftarm_up].pos_collider = D3DXVECTOR3(12.0f, 53.0f, 0.0f);
			part[part_leftarm_up].collider_wxhylz = D3DXVECTOR3(5.0f, 17.0f, 5.0f);

			part[part_leftarm_down].pos_origin = D3DXVECTOR3(12.0f, 46.0f, 0.0f);
			part[part_leftarm_down].pos_collider = D3DXVECTOR3(12.0f, 39.0f, 0.0f);
			part[part_leftarm_down].collider_wxhylz = D3DXVECTOR3(5.0f, 12.0f, 5.0f);

			part[part_lefthend].pos_origin = D3DXVECTOR3(12.0f, 31.0f, 0.0f);
			part[part_lefthend].pos_collider = D3DXVECTOR3(12.0f, 31.0f, 0.0f);
			part[part_lefthend].collider_wxhylz = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

			part[part_rightarm_up].pos_origin = D3DXVECTOR3(-12.0f, 60.0f, 0.0f);
			part[part_rightarm_up].pos_collider = D3DXVECTOR3(-12.0f, 53.0f, 0.0f);
			part[part_rightarm_up].collider_wxhylz = D3DXVECTOR3(5.0f, 17.0f, 5.0f);

			part[part_rightarm_down].pos_origin = D3DXVECTOR3(-12.0f, 46.0f, 0.0f);
			part[part_rightarm_down].pos_collider = D3DXVECTOR3(-12.0f, 39.0f, 0.0f);
			part[part_rightarm_down].collider_wxhylz = D3DXVECTOR3(5.0f, 12.0f, 5.0f);

			part[part_righthend].pos_origin = D3DXVECTOR3(-12.0f, 31.0f, 0.0f);
			part[part_righthend].pos_collider = D3DXVECTOR3(-12.0f, 31.0f, 0.0f);
			part[part_righthend].collider_wxhylz = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

			part[part_leftfoot_up].pos_origin = D3DXVECTOR3(4.5f, 35.5f, 0.0f);
			part[part_leftfoot_up].pos_collider = D3DXVECTOR3(4.5f, 28.5f, 0.0f);
			part[part_leftfoot_up].collider_wxhylz = D3DXVECTOR3(6.0f, 14.0f, 6.0f);

			part[part_leftfoot_down].pos_origin = D3DXVECTOR3(4.5f, 19.0f, 0.0f);
			part[part_leftfoot_down].pos_collider = D3DXVECTOR3(4.5f, 12.0f, 0.0f);
			part[part_leftfoot_down].collider_wxhylz = D3DXVECTOR3(6.0f, 18.0f, 6.0f);

			part[part_rightfoot_up].pos_origin = D3DXVECTOR3(-4.5f, 35.5f, 0.0f);
			part[part_rightfoot_up].pos_collider = D3DXVECTOR3(-4.5f, 28.5f, 0.0f);
			part[part_rightfoot_up].collider_wxhylz = D3DXVECTOR3(6.0f, 14.0f, 6.0f);

			part[part_rightfoot_down].pos_origin = D3DXVECTOR3(-4.5f, 19.0f, 0.0f);
			part[part_rightfoot_down].pos_collider = D3DXVECTOR3(-4.5f, 12.0f, 0.0f);
			part[part_rightfoot_down].collider_wxhylz = D3DXVECTOR3(6.0f, 18.0f, 6.0f);

			part[part_leftfoot_sole].pos_origin = D3DXVECTOR3(-4.5f, 5.0f, 0.0f);
			part[part_leftfoot_sole].pos_collider = D3DXVECTOR3(-4.5f, 5.0f, 0.0f);
			part[part_leftfoot_sole].collider_wxhylz = D3DXVECTOR3(8.0f, 3.0f, 8.0f);

			part[part_rightfoot_sole].pos_origin = D3DXVECTOR3(4.5f, 5.0f, 0.0f);
			part[part_rightfoot_sole].pos_collider = D3DXVECTOR3(4.5f, 5.0f, 0.0f);
			part[part_rightfoot_sole].collider_wxhylz = D3DXVECTOR3(8.0f, 3.0f, 8.0f);

			for (int i = 0; i < PLAYERPART_MAX; i++)
			{
				part[i].pos = part[i].pos_origin;
				part[i].rot = rot;
				part[i].scl = scl;
				collider_c[i] = collider->CreateCollider3DBox(part[i].pos_collider, part[i].rot, part[i].collider_wxhylz.x, part[i].collider_wxhylz.y, part[i].collider_wxhylz.z, Collider3DType_box, Player_Part_object);
				part[i].collider_index = collider_c[i];
				part[i].move_time = 0.0f;
			}
			collider_c[Character_collider_top] = collider->CreateCollider3DBox(		D3DXVECTOR3(0.0f, collider_wxhylz.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, 0.0f, collider_wxhylz.z, Collider3DType_box, Player_object);
			collider_c[Character_collider_stand] = collider->CreateCollider3DBox(	D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, 0.0f, collider_wxhylz.z, Collider3DType_box, Player_object);
			collider_c[Character_collider_front] = collider->CreateCollider3DBox(	D3DXVECTOR3(0.0f, (collider_wxhylz.y/2),(-collider_wxhylz.z/2)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, collider_wxhylz.y, 0.0f, Collider3DType_box, Player_object);
			collider_c[Character_collider_behind] = collider->CreateCollider3DBox(	D3DXVECTOR3(0.0f, (collider_wxhylz.y / 2), (collider_wxhylz.z / 2)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, collider_wxhylz.y, 0.0f, Collider3DType_box, Player_object);
			collider_c[Character_collider_left] = collider->CreateCollider3DBox(	D3DXVECTOR3((-collider_wxhylz.x / 2), (collider_wxhylz.y / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, Player_object);
			collider_c[Character_collider_right] = collider->CreateCollider3DBox(	D3DXVECTOR3((collider_wxhylz.x / 2), (collider_wxhylz.y / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, Player_object);
			collider_c[Character_collider_camera] = collider->CreateCollider3DBox(camera->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),10.0f, 10.0f, 10.0f, Collider3DType_box, Player_object);
		}

		action_time_start = 0.0f;
		action_time_end=0.0f;
		weapon->InitWeapon(bigsword);
		pos = D3DXVECTOR3(0.0f, 200.0f, 2000.0f);
		reborn_pos = pos;
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//rot_destine = rot;
		HP = PLAYER_HP_MAX;
		Blow_point = 0;
		use = true;
		dying = false;
		beAttack = false;
		spd = 0.4f;
		rangex=0;
		kyorix=0;
		return S_OK;
	}
	
	void Player::UpdateCharacter()
	{
		if (dying == true)
		{
			if (player_action_next != stand_bigsword)
			{
				player_action_next = stand_bigsword;
				anime_change = lastaction_setting;
			}
			HP += 0.3f;
			//ENEMYのアニメーションを計算して、モデルの姿勢を修正
			this->Animation_control();
			//修正したPLAYERのpartのposとrotを現在のposを反応する
			this->Update_Player_Pos();
			if (HP >= PLAYER_HP_MAX)
			{
				HP = PLAYER_HP_MAX;
				dying = false;
				pos = reborn_pos;
				use = true;
			}
		}
		else
		{
			// 入力処理
			if (beAttack == false)
			{
				this->PlayerInput();
			}
			//入力しだrotを使って、現在PLAYERのrot修正
			this->RotRevise();

			//PLAYERの移動量を計算する
			if (beAttack == false)
			{
				moveway_xyz.x = (-sinf(rot.y))*spd;
				moveway_xyz.z = (-cosf(rot.y))*spd;
			}
			

			//現在のPOSをPLAYERの移動量で加算して、移動後のPOSを計算
			
			this->Character_edge_control();
			if (pos_destine.y <= (-100.0f))
			{
				slip_num = 1;
				if (anime_change == action_no_switch|| player_action_next== be_attack)
				{
					beAttack = false;
					air_move = true;
					spd = 0;
					player_action_next = action_jump;
					anime_change = lastaction_setting;
				}
			}
			moveway_xyz.y = spd_y;
			pos_destine = pos;
			pos_destine += moveway_xyz;
			//PLAYERとMODELのPOSを制御====================================================

				//stageのcollider判定
			touch_ans = false;//地面を触ったどうかを判定の変数
			touch_top_ans = false;//頭を触ったどうかを判定の変数
			ground_y = pos_destine.y;//現在POSの地面の高さの変数
			//移動後のPOSを修正
			this->Character_PosUpdate();
			
			//カメラとMODELの透明化処理
			collider->SetCollider3D(Character_collider_camera, camera->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			for (int i = 0; i < map1->Model_num; i++)
			{
				D3DXVECTOR3 move_kyori = map1->Model_data[i].collider_pos - camera->pos;
				float kyori = D3DXVec3Length(&move_kyori);
				if (kyori > (10.0f + map1->Model_data[i].collider_radius))
				{
					map1->Model_data[i].color_a = 0;
					continue;
				}
				bool camera_ans = false;
				for (int j = 0; j < map1->Model_data[i].index_max; j++)
				{
					if (camera_ans == false) camera_ans = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_camera]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
					if (camera_ans == true)break;
				}
				if (camera_ans == true)
				{
					map1->Model_data[i].color_a = 1;
				}
				else
				{
					map1->Model_data[i].color_a = 0;
				}
			}

			if (touch_ans == true)
			{
				slip_num = PLAYER_SLIP_MAX;
				if (beAttack == true)
				{
					beAttack = false;
					spd = 0;
					if (player_action_next != stand_bigsword)
					{
						player_action_next = stand_bigsword;
						anime_change = lastaction_setting;
					}
				}
				
			}
			this->Character_edge_control();
			//修正した移動量をPLAYERのposを加算して、移動します。
			pos += moveway_xyz;
			//PLAYERのアニメーションを計算して、モデルの姿勢を修正
			this->Animation_control();
			//修正したPLAYERのpartのposとrotを現在のposを反応する
			this->Update_Player_Pos();

			//PLAYERのSPDを制御=====================================================================	
			this->Speed_control();
			//=====================================================================
			int ball_break = 8;
			//PLAYERのPOS関わらない他の物事の衝突判定(攻撃、hpの処理とか
			for (int i = 32; i < (map1->Model_num - 1); i++)
			{
				if (map1->Model_data[i].use == false)
				{
					ball_break--;
					continue;
				}
				D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
				move_kyori.y += (collider_wxhylz.y / 2);
				move_kyori = map1->Model_data[i].collider_pos - move_kyori;
				float kyori = D3DXVec3Length(&move_kyori);
				float kyori_p = sqrtf((collider_wxhylz.x*collider_wxhylz.x) + (collider_wxhylz.z + collider_wxhylz.z) + (collider_wxhylz.y + collider_wxhylz.y));
				//if model中心点とplayerposの距離　< modelのr+playerのr  =>BBC判定に進む
				if (kyori > (kyori_p + map1->Model_data[i].collider_radius))continue;

				if (player_action_now == normal_attack_1 || player_action_now == normal_attack_2 || player_action_now == normal_attack_3 || player_action_now == jump_attack_start || player_action_now == jump_attack_end || player_action_now == spin_attack)
				{
					if (anime_change == action_no_switch)
					{
						bool weapon_ans = false;
						weapon_ans = collider->CheckHitOBB(&weapon->collider->g_Collider3D[weapon->collider_index[0]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[0]]);
						if (weapon_ans == true && map1->Model_data[i].use == true)
						{
							sound->PlaySoundA(SOUND_LABEL_SE_bomb000);
							map1->Model_data[i].use = false;
							stage_collider->SetCollider3D_use(map1->Model_data[i].collider_index[0], false);
							//map1_collider->SetCollider3D_use(Model_data[num].collider_index[0], true);

						}
					}
				}
			}

			if (ball_break <= 0)
			{
				GameDate::ChangePhaseCheck = MODE_RESULT;
			}
			//プレイヤのposとrotを使って、カメラのposとrotを修正する
			camera->SetPlayerDate(pos, rot);
		}
	}
	void Player::DrawCharacter()
	{
		if (use == true && GameDate::DrawType != Draw_ColliderOnly)
		{
			for (int i = 0; i < PLAYERPART_MAX; i++)
			{
				if (i == part_rightarm_down)
				{
					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[part_leftarm_down].model);
				}
				else if (i == part_righthend)
				{
					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[part_lefthend].model);
					weapon->DrawWeapon();
				}
				else if (i == part_rightfoot_up)
				{
					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[part_leftfoot_up].model);
				}
				else if (i == part_rightfoot_down)
				{
					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[part_leftfoot_down].model);
				}
				else if (i == part_rightfoot_sole)
				{
					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[part_leftfoot_sole].model);
				}
				else
				{

					renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, &part[i].model);
				}
			}
		}
		
	}

	void Player::UninitCharacter()
	{
		for (int i = 0; i < PLAYERPART_MAX; i++)
		{
			if (i == part_rightarm_down || i == part_righthend || i == part_rightfoot_up
				|| i == part_rightfoot_down || i == part_rightfoot_sole)continue;
			renderer->UnloadModel(&part[i].model);
		}
		//weapon->UninitWeapon(0);
		delete weapon;
		delete[] playerAnimation;
		delete[] part;
		delete[] collider_c;

		
	}

	void Player::Update_Player_Pos()
	{
		this->Update_Pos();
		Update_Collider(pos, rot);
		//武器のPOSとCollider変化
		if (player_action_now == normal_attack_1 || player_action_now == normal_attack_2 || player_action_now == normal_attack_3 ||
			player_action_now == jump_attack_start || player_action_now == jump_attack_end || player_action_now == spin_attack || player_action_now == guard)
		{
			D3DXVECTOR3 w_scl = D3DXVECTOR3(5.0f, 10.0f, 78.0f);
			switch (player_action_now)
			{
			case normal_attack_1:
				w_scl = D3DXVECTOR3(40.0f, 10.0f, 78.0f);
				break;
			case normal_attack_2:
				w_scl = D3DXVECTOR3(40.0f, 10.0f, 78.0f);
				break;
			case normal_attack_3:
				w_scl = D3DXVECTOR3(40.0f, 10.0f, 78.0f);
				break;
			case jump_attack_start:
				w_scl = D3DXVECTOR3(55.0f, 10.0f, 78.0f);
				break;
			case jump_attack_end:
				w_scl = D3DXVECTOR3(55.0f, 10.0f, 78.0f);
				break;
			case spin_attack:
				w_scl = D3DXVECTOR3(40.0f, 10.0f, 78.0f);
				break;
			case guard:
				w_scl = D3DXVECTOR3(5.0f, 50.0f, 78.0f);
				break;
			}
			weapon->Update_Scl(w_scl);
		}
		else
		{
			D3DXVECTOR3 w_scl = D3DXVECTOR3(5.0f, 10.0f, 78.0f);
			weapon->Update_Scl(w_scl);
		}
		weapon->Update_Pos(part[part_righthend].pos, part[part_righthend].rot);
		weapon->Update_Collider();
	}

	void Player::PlayerInput()
	{
		//角度修正
		while (camera->rot.y > D3DX_PI || camera->rot.y < (-D3DX_PI))
		{
			if (camera->rot.y > 0)
			{
				camera->rot.y -= 2 * D3DX_PI;
			}
			else if (camera->rot.y < 0)
			{
				camera->rot.y += 2 * D3DX_PI;
			}
		}
		// 移動処理
		if (GameDate::GameMode == normal)
		{
			float spd_now = spd;

			if (player_action_next != be_attack && player_action_now != be_attack)
			{
				bool mouse_ans = input->IsMouseLeftTriggered();
				bool mouse_ans2 = input->IsMouseRightTriggered();
				if (can_switch_action == true)
				{
					if (input->GetKeyboardPress(DIK_A))
					{
						rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					else if (input->GetKeyboardPress(DIK_D))
					{
						rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					if (input->GetKeyboardPress(DIK_W))
					{
						rot_destine.y = (camera->rot.y);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					else if (input->GetKeyboardPress(DIK_S))
					{
						rot_destine.y = (camera->rot.y) - (D3DX_PI);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}

					if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
					{
						rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
					{
						rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
					{
						rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;
					}
					else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
					{
						rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);
						spd = spd_now + PLAYER_MOVE_SPD_PLUS;

					}
					if (spd > PLAYER_MOVE_SPD_MAX)spd = PLAYER_MOVE_SPD_MAX;

					bool action_choice = false;
					if (input->GetKeyboardTrigger(DIK_SPACE) && action_choice == false)
					{
						//if (touch_ans == true)
						{
							if (player_action_now != action_jump)
							{
								player_action_next = action_jump;
								anime_change = lastaction_setting;
								action_choice = true;
								can_switch_action = false;
								if (spd_y < 0)
								{
									spd_y = 0;
								}
								spd_y += 7.0f;
							}
						}
					}
					else if (mouse_ans==true && action_choice == false)
					{
						if (player_action_next != normal_attack_1)
						{
							player_action_next = normal_attack_1;
							anime_change = lastaction_setting;
							can_switch_action = false;
							action_choice = true;
						}
					}
					else if (input->GetKeyboardTrigger(DIK_2) && action_choice == false)
					{
						if (player_action_next != spin_attack)
						{
							player_action_next = spin_attack;
							anime_change = lastaction_setting;
							can_switch_action = false;
							action_choice = true;
						}
					}
					else if (mouse_ans2==true && action_choice == false)
					{
						if (spd_y != 0 && touch_ans == false )
						{
							if (player_action_next != jump_attack_end)
							{
								air_move = true;
								can_switch_action = false;
								action_choice = true;
								player_action_next = jump_attack_end;
								anime_change = lastaction_setting;
							}
						}
						else if (spd_y == 0 && touch_ans == true)
						{
							if (player_action_next != jump_attack_start)
							{
								player_action_next = jump_attack_start;
								anime_change = lastaction_setting;
								can_switch_action = false;
								action_choice = true;
							}
						}

					}
					else if (input->GetKeyboardTrigger(DIK_F) && action_choice == false&& slip_num > 0)
					{
						if (player_action_next != slip_move)
						{
							slip_num--;
							can_switch_action = false;
							action_choice = true;
							spd_y = 0;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
						}
					}
				}
				else
				{
					if (player_action_now == normal_attack_1 && player_action_next == normal_attack_1)
					{
						if (part[0].move_time >= 2 )
						{
							if (player_action_next != normal_attack_2 && mouse_ans==true)
							{
								player_action_next = normal_attack_2;
								anime_change = lastaction_setting;
							}
							
							if (input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
							}
							else if (input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
							}
							if (input->GetKeyboardPress(DIK_W))
							{
								rot_destine.y = (camera->rot.y);
							}
							else if (input->GetKeyboardPress(DIK_S))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI);
							}

							if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
							}
							else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
							}
							if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
							}
							else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);

							}
						}
						if (input->GetKeyboardTrigger(DIK_F)&& player_action_next != slip_move&& slip_num > 0)
						{
							slip_num--;
							spd_y = 0;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
						}
					}
					else if (player_action_now == normal_attack_2 && player_action_next == normal_attack_2)
					{
						if (part[0].move_time >= 2 )
						{
							if (player_action_next != normal_attack_3 && mouse_ans==true)
							{
								player_action_next = normal_attack_3;
								anime_change = lastaction_setting;
							}
							if (input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
							}
							else if (input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
							}
							if (input->GetKeyboardPress(DIK_W))
							{
								rot_destine.y = (camera->rot.y);
							}
							else if (input->GetKeyboardPress(DIK_S))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI);
							}

							if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
							}
							else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
							}
							if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
							}
							else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);

							}
						}
						if (input->GetKeyboardTrigger(DIK_F)&& player_action_next != slip_move && slip_num > 0)
						{
							slip_num--;
							spd_y = 0;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
						}
					}
					else if (player_action_now == normal_attack_3 && player_action_next == normal_attack_3)
					{
						if (part[0].move_time >= 2 )
						{
							if (player_action_next != normal_attack_1 && mouse_ans==true)
							{
								player_action_next = normal_attack_1;
								anime_change = lastaction_setting;
							}

							if (input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
							}
							else if (input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
							}
							if (input->GetKeyboardPress(DIK_W))
							{
								rot_destine.y = (camera->rot.y);
							}
							else if (input->GetKeyboardPress(DIK_S))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI);
							}

							if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
							}
							else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
							}
							if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
							{
								rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
							}
							else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
							{
								rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);

							}
						}
						if (input->GetKeyboardTrigger(DIK_F)&& player_action_next != slip_move && slip_num > 0)
						{
							slip_num--;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
						}
					}
					else if (player_action_now == jump_attack_start && player_action_next == jump_attack_start)
					{
						if (part[0].move_time >= 3 && player_action_next != jump_attack_end && mouse_ans2==true)
						{
							player_action_next = jump_attack_end;
							anime_change = lastaction_setting;
							air_move = true;
						}
						else if (input->GetKeyboardTrigger(DIK_F) &&player_action_next != slip_move && slip_num > 0)
						{
							slip_num--;
							can_switch_action = false;
							air_move = true;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
							
						}
					}
					else if (player_action_now == action_jump )
					{
						if (input->GetKeyboardPress(DIK_A))
						{
							rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						else if (input->GetKeyboardPress(DIK_D))
						{
							rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						if (input->GetKeyboardPress(DIK_W))
						{
							rot_destine.y = (camera->rot.y);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						else if (input->GetKeyboardPress(DIK_S))
						{
							rot_destine.y = (camera->rot.y) - (D3DX_PI);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}

						if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
						{
							rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
						{
							rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
						{
							rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;
						}
						else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
						{
							rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);
							spd = spd_now + PLAYER_MOVE_AIRSPD_PLUS;

						}
						if (spd >= PLAYER_MOVE_SPD_MAX)spd = PLAYER_MOVE_SPD_MAX;
						if (mouse_ans2==true  && player_action_next != jump_attack_end)
						{
							spd_y = 0;
							air_move = true;
							player_action_next = jump_attack_end;
							anime_change = lastaction_setting;
							
						}
						else if (input->GetKeyboardTrigger(DIK_SPACE) )
						{
							if (anime_change == action_no_switch && air_move == false)
							{
								spd_y = 0;
								player_action_next = action_jump;
								anime_change = lastaction_setting;
								can_switch_action = false;
								air_move = true;
								if (spd_y < 0)
								{
									spd_y = 0;
								}
								spd_y += 7.0f;
							}
							else if (anime_change != action_no_switch )
							{
								if (player_action_next == action_walk || player_action_next == action_walk_back || player_action_next == stand_bigsword)
								{
									spd_y = 0;
									player_action_next = action_jump;
									anime_change = lastaction_setting;
									can_switch_action = false;
									air_move = false;
									if (spd_y < 0)
									{
										spd_y = 0;
									}
									spd_y += 7.0f;
								}
							}
							

						}
						else if (player_action_next != slip_move&& input->GetKeyboardTrigger(DIK_F) && slip_num>0)
						{
							slip_num--;
							can_switch_action = false;
							air_move = true;
							player_action_next = slip_move;
							anime_change = lastaction_setting;
						}
					}
					else if (player_action_now == slip_move)
					{
						if (part[0].move_time < 1)
						{
							if (mouse_ans==true && touch_ans == true)
							{
								if (player_action_next != normal_attack_1)
								{
									player_action_next = normal_attack_1;
									anime_change = lastaction_setting;
									can_switch_action = false;
								}
							}
							else if(mouse_ans2==true )
							{
								if (touch_ans == false )
								{
									if (player_action_next != jump_attack_end)
									{
										air_move = true;
										can_switch_action = false;
										player_action_next = jump_attack_end;
										anime_change = lastaction_setting;
									}
								}
								else if (touch_ans == true)
								{
									if (player_action_next != jump_attack_start)
									{
										player_action_next = jump_attack_start;
										anime_change = lastaction_setting;
										can_switch_action = false;
									}
								}
							}
							else if (input->GetKeyboardTrigger(DIK_SPACE) && touch_ans == true)
							{
								if (player_action_now != action_jump)
								{
									player_action_next = action_jump;
									anime_change = lastaction_setting;
									can_switch_action = false;
									
								}
							}
						}
					}
					else if (player_action_next == action_walk || player_action_next == action_walk_back || player_action_next == stand_bigsword)
					{

					}
				}
			}
		}
		else if (GameDate::GameMode == camera_lock_on)  //未完成
		{
			/*if (spd == 0)
			{
				spd_control = no_move;
			}*/
			if (can_switch_action == true)
			{
				if (input->GetKeyboardPress(DIK_A))
				{
					player_action_next = action_walk;
					rot_destine.y = (camera->rot.y) - (D3DX_PI / 2);
				}
				else if (input->GetKeyboardPress(DIK_D))
				{
					player_action_next = action_walk;
					rot_destine.y = (camera->rot.y) + (D3DX_PI / 2);
				}
				if (input->GetKeyboardPress(DIK_W))
				{
					player_action_next = action_walk;
					rot_destine.y = (camera->rot.y);
				}
				else if (input->GetKeyboardPress(DIK_S))
				{
					player_action_next = action_walk_back;
					rot_destine.y = (camera->rot.y) - (D3DX_PI);
				}

				if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_A))
				{
					player_action_next = action_walk;
					rot_destine.y = (camera->rot.y) - (D3DX_PI / 4);
				}
				else if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
				{
					player_action_next = action_walk;
					rot_destine.y = (camera->rot.y) + (D3DX_PI / 4);
				}
				if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
				{
					player_action_next = action_walk_back;
					rot_destine.y = (camera->rot.y) - (D3DX_PI * 3 / 4);
				}
				else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_D))
				{
					player_action_next = action_walk_back;
					rot_destine.y = (camera->rot.y) + (D3DX_PI * 3 / 4);
				}

			}
		}
	}

	void Player::SetPlayerAnimation()
	{
		playerAnimation = new CharacterAnimation[PLAYER_KIND_OF_ACTION];

		////copy用

		//{
		//	Animation_Max = 3;
		//	playerAnimation[normal_attack_3].body = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].head = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
		//	playerAnimation[normal_attack_3].body[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].body[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].body[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].head[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].head[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].head[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].leftarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].leftarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].lefthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].lefthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].lefthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].righthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].righthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].righthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].rightarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].rightarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].leftfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].leftfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].leftfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].leftfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].rightfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].rightfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
		//	playerAnimation[normal_attack_3].rightfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//	playerAnimation[normal_attack_3].rightfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		//}

		int Animation_Max=0;
		//stand_bigsword
		{
			Animation_Max = 3;
			playerAnimation[stand_bigsword].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[stand_bigsword].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[stand_bigsword].body[0]				= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].body[1]				= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].body[2]				= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/9, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/9, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[stand_bigsword].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[stand_bigsword].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[stand_bigsword].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[stand_bigsword].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.8f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.2f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/8, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/8, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/8, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, D3DX_PI/10, D3DX_PI/10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[stand_bigsword].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, D3DX_PI/10, D3DX_PI/10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[stand_bigsword].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, D3DX_PI/10, D3DX_PI/10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			
		}

		//action_walk
		{
			Animation_Max = 11;
			playerAnimation[action_walk].body			= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].head			= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].leftarm_up		= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].leftarm_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].lefthend		= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].righthend		= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].rightarm_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].rightarm_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].leftfoot_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].leftfoot_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].rightfoot_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].leftfoot_sole	= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			
			playerAnimation[action_walk].body[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[action_walk].body[1]				= { D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[2]				= { D3DXVECTOR3(0.0f, -1.8f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1  };
			playerAnimation[action_walk].body[4]				= { D3DXVECTOR3(0.0f, 0.5f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[5]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[6]				= { D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[7]				= { D3DXVECTOR3(0.0f, -1.8f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].body[8]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].body[9]				= { D3DXVECTOR3(0.0f, 0.5f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].body[10]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].head[4]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[5]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[6]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[7]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[8]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].head[9]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].head[10]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].leftarm_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftarm_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftarm_up[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_up[10]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/11),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/12),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/12),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/11),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/11),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/12),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/12),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftarm_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/11),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].leftarm_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, -D3DX_PI/11),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			playerAnimation[action_walk].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			playerAnimation[action_walk].lefthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].lefthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].lefthend[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].lefthend[10]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[action_walk].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			playerAnimation[action_walk].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].righthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].righthend[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].righthend[10]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].rightarm_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightarm_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightarm_up[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.1f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.2f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.1f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.1f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.2f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.1f, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightarm_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightarm_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].leftfoot_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, -D3DX_PI / 7, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_up[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].leftfoot_sole[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].leftfoot_sole[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 7, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_up[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, -D3DX_PI / 7, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, -D3DX_PI / 7, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].rightfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[action_walk].rightfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			playerAnimation[action_walk].rightfoot_sole[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[action_walk].rightfoot_sole[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
		}

		//action_jump
		{
			Animation_Max = 5;
			playerAnimation[action_jump].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_jump].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[action_jump].body[0]				= { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].body[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].body[2]				= { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].body[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].body[4]				= { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].head[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/10, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].head[4]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].leftarm_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, -D3DX_PI/9, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, -D3DX_PI/9, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, -D3DX_PI/9, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/9, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/9,  -D3DX_PI/6),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/9,  -D3DX_PI/5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, D3DX_PI/9,  -D3DX_PI/6),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20  };
			playerAnimation[action_jump].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20  };
			playerAnimation[action_jump].lefthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].lefthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/1.7f, D3DX_PI/1.1f, D3DX_PI/3),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20  };
			playerAnimation[action_jump].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/1.5f, D3DX_PI/1.1f, D3DX_PI/3),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20  };
			playerAnimation[action_jump].righthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 1.7f, D3DX_PI / 1.1f, D3DX_PI / 3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].righthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].rightarm_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].leftfoot_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, -D3DX_PI/7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].leftfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, 0.0f, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.5f, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2, D3DX_PI/8, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].rightfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI / 8, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
			playerAnimation[action_jump].rightfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
			playerAnimation[action_jump].rightfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		}

		//action_walk_back
		{
			Animation_Max = 5;
			playerAnimation[action_walk_back].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[action_walk_back].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[action_walk_back].body[0]				= { D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].body[1]				= { D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].body[2]				= { D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].body[3]				= { D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 12, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].body[4]				= { D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].head[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].head[4]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_up[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].leftarm_up[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_up[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_up[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_up[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/15, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/12, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/9, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/12, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/15, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[action_walk_back].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[action_walk_back].lefthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].lefthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[action_walk_back].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/1.1f, D3DX_PI/3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30  };
			playerAnimation[action_walk_back].righthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/1.1f, D3DX_PI/3),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].righthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/1.1f, D3DX_PI/3),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].leftfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI/7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].rightfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2,0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			playerAnimation[action_walk_back].rightfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			playerAnimation[action_walk_back].rightfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
		}
		
		//normal_attack_1
		{
			Animation_Max = 6;
			playerAnimation[normal_attack_1].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_1].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[normal_attack_1].body[0]			= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[normal_attack_1].body[1]			= { D3DXVECTOR3(0.0f, 0.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].body[2]			= { D3DXVECTOR3(0.0f, -4.0f, 4.0f), D3DXVECTOR3(-D3DX_PI / 15, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].body[3]			= { D3DXVECTOR3(0.0f, -4.0f, 4.0f), D3DXVECTOR3(-D3DX_PI / 15, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].body[4]			= { D3DXVECTOR3(0.0f, 0.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].body[5]			= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].head[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].head[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].head[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 15, D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].head[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 15, D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].head[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].head[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].leftarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 4, -D3DX_PI / 13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.5f, -D3DX_PI / 13),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.5f, -D3DX_PI / 13),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 4, -D3DX_PI / 13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].lefthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].lefthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].lefthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].lefthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].lefthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].lefthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI /1.5f, D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI /2.5f, D3DX_PI / 1.5f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].righthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI / 2.5f, D3DX_PI / 1.5f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].righthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI / 1.5f, D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].righthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, -D3DX_PI / 15, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, -D3DX_PI / 15, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 4, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 4, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.5f, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, D3DX_PI / 7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, D3DX_PI / 7, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.5f, -D3DX_PI / 7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].leftfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].leftfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_up[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].rightfoot_up[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_up[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_up[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_up[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_up[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_1].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 6, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 6, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[normal_attack_1].rightfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_1].rightfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
		}

		//normal_attack_2
		{
			Animation_Max = 6;
			playerAnimation[normal_attack_2].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_2].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[normal_attack_2].body[0]			= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, -D3DX_PI / 2.5f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[normal_attack_2].body[1]			= { D3DXVECTOR3(0.0f, 0.0f, -2.0f), D3DXVECTOR3(-D3DX_PI / 10, -D3DX_PI / 10, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].body[2]			= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].body[3]			= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].body[4]			= { D3DXVECTOR3(0.0f, 0.0f, -2.0f), D3DXVECTOR3(-D3DX_PI / 10, -D3DX_PI / 10, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[normal_attack_2].body[5]			= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, -D3DX_PI / 2.5f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].head[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, D3DX_PI / 2.5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[normal_attack_2].head[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].head[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].head[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].head[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].head[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, D3DX_PI / 2.5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, -D3DX_PI / 20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, D3DX_PI / 8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, D3DX_PI / 8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, -D3DX_PI / 20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].leftarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 5),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].leftarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, -D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, -D3DX_PI / 2),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, -D3DX_PI / 2),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, -D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].leftarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 5),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].lefthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].lefthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].lefthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].lefthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].lefthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].lefthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, -D3DX_PI / 7, -D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, -D3DX_PI / 7, -D3DX_PI / 1.5f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI /2, -D3DX_PI / 7, -D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].righthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI /2, -D3DX_PI / 7, -D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].righthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, -D3DX_PI / 7, -D3DX_PI / 1.5f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].righthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, -D3DX_PI / 7, -D3DX_PI / 2),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 8, D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 8, D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, D3DX_PI / 3, -D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, D3DX_PI / 3, -D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 8, D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].rightarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 8, D3DX_PI / 15),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].rightarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.5f, -D3DX_PI / 7, D3DX_PI / 13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2,  D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].leftfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.5f, -D3DX_PI / 7, D3DX_PI / 13),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].leftfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, -D3DX_PI / 13),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].leftfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].leftfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, -D3DX_PI / 13),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_up[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, D3DX_PI / 2.5f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].rightfoot_up[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_up[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, -D3DX_PI / 6),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_up[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, -D3DX_PI / 6),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_up[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].rightfoot_up[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, D3DX_PI / 2.5f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].rightfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_2].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 6, D3DX_PI / 6),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 6, D3DX_PI / 6),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_2].rightfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_2].rightfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
		}

		//normal_attack_3
		{
			Animation_Max = 5;
			playerAnimation[normal_attack_3].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[normal_attack_3].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[normal_attack_3].body[0]			= { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[normal_attack_3].body[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[normal_attack_3].body[2]			= { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].body[3]			= { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].body[4]			= { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].head[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].head[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].head[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].head[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].head[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.05f, 0.0f,  D3DX_PI/18),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.05f, 0.0f,  -D3DX_PI/20),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.7f, 0.0f,  -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.7f, 0.0f,  -D3DX_PI/8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.05f, 0.0f,  D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].leftarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 7),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].leftarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].lefthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].lefthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			playerAnimation[normal_attack_3].lefthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[normal_attack_3].lefthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].lefthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI/2.6f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/6, 0.0f, -D3DX_PI/4.2f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			playerAnimation[normal_attack_3].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/6, 0.0f, -D3DX_PI/7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[normal_attack_3].righthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/6, 0.0f, -D3DX_PI/7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].righthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.6f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.1f, 0.0f, -D3DX_PI/18),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.1f, 0.0f, D3DX_PI/25),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, D3DX_PI/7.5f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, D3DX_PI/7.5f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.1f, 0.0f, -D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2.2f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2.2f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 30, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 30, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].leftfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_up[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].rightfoot_up[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].rightfoot_up[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_up[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_up[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[normal_attack_3].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[normal_attack_3].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[normal_attack_3].rightfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			
		}

		//jump_attack_start
		{
			Animation_Max = 6;
			playerAnimation[jump_attack_start].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_start].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[jump_attack_start].body[0]				= { D3DXVECTOR3(0.0f, -2.0f, 4.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/3, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 ,Animation_Max };
			playerAnimation[jump_attack_start].body[1]				= { D3DXVECTOR3(0.0f, -4.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 };
			playerAnimation[jump_attack_start].body[2]				= { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].body[3]				= { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].body[4]				= { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].body[5]				= { D3DXVECTOR3(0.0f, -2.0f, 4.0f), D3DXVECTOR3(-D3DX_PI / 7, D3DX_PI / 3, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/3, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_start].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 };
			playerAnimation[jump_attack_start].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 };
			playerAnimation[jump_attack_start].head[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].head[4]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, -D3DX_PI/10, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].head[5]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, -D3DX_PI / 3, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.4f, 0.0f, -D3DX_PI/7),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.1f, 0.0f, -D3DX_PI/7),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.9f, 0.0f, -D3DX_PI/7),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.9f, 0.0f, -D3DX_PI/7),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/9, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].leftarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3.2f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3.2f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 };
			playerAnimation[jump_attack_start].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[jump_attack_start].lefthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].lefthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].lefthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3.2f, -D3DX_PI/5, D3DX_PI/1.2f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/4, -D3DX_PI/8, D3DX_PI/1.17f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),3 };
			playerAnimation[jump_attack_start].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/4, -D3DX_PI/8, D3DX_PI/1.17f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			playerAnimation[jump_attack_start].righthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/1.1f, -D3DX_PI/8, D3DX_PI/1.17f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].righthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/1.1f, -D3DX_PI/8, D3DX_PI/1.17f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].righthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3.2f, -D3DX_PI / 5, D3DX_PI / 1.2f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, 0.0f, -D3DX_PI/5),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, 0.0f, D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.2f, 0.0f, D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.2f, 0.0f, D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.2f, 0.0f, D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, -D3DX_PI / 5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/8, -D3DX_PI/5, D3DX_PI/2.5f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].rightarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, -D3DX_PI / 5, D3DX_PI / 2.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, -D3DX_PI/5, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2.5f, -D3DX_PI/20, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.8f, -D3DX_PI/20, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, -D3DX_PI / 5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].leftfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].leftfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].leftfoot_sole[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, D3DX_PI/5, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, D3DX_PI/5, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].rightfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/8, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/8, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 8, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, D3DX_PI/10, D3DX_PI/10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),3  ,Animation_Max };
			playerAnimation[jump_attack_start].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/10, D3DX_PI/10, D3DX_PI/10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),3};
			playerAnimation[jump_attack_start].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, D3DX_PI/6, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_start].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/6, D3DX_PI/6, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/6, D3DX_PI/6, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_start].rightfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		}

		//jump_attack_end
		{
			Animation_Max = 5;
			playerAnimation[jump_attack_end].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[jump_attack_end].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[jump_attack_end].body[0] = { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].body[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].body[2] = { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].body[3] = { D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].body[4] = { D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].head[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].head[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].head[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].head[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].head[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].leftarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.05f, 0.0f,  D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].leftarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.05f, 0.0f,  -D3DX_PI / 20),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].leftarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.7f, 0.0f,  -D3DX_PI / 8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].leftarm_up[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.7f, 0.0f,  -D3DX_PI / 8),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].leftarm_up[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.05f, 0.0f,  D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].leftarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].leftarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 7),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].leftarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].leftarm_down[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].leftarm_down[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].lefthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].lefthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].lefthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].lefthend[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].lefthend[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].righthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.6f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].righthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 6, 0.0f, -D3DX_PI / 4.2f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].righthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 6, 0.0f, -D3DX_PI / 7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].righthend[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 6, 0.0f, -D3DX_PI / 7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].righthend[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.6f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].rightarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.1f, 0.0f, -D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].rightarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.1f, 0.0f, D3DX_PI / 25),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].rightarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, D3DX_PI / 7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].rightarm_up[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, D3DX_PI / 7.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].rightarm_up[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.1f, 0.0f, -D3DX_PI / 18),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].rightarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].rightarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].rightarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].rightarm_down[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].rightarm_down[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2.2f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].leftfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 30, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].leftfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].leftfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].leftfoot_up[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].leftfoot_up[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 30, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].leftfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].leftfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].leftfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].leftfoot_down[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].leftfoot_down[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].leftfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].leftfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].leftfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].leftfoot_sole[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].leftfoot_sole[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].rightfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].rightfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].rightfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].rightfoot_up[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].rightfoot_up[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 10, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].rightfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].rightfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].rightfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].rightfoot_down[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].rightfoot_down[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[jump_attack_end].rightfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[jump_attack_end].rightfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			playerAnimation[jump_attack_end].rightfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),12 };
			playerAnimation[jump_attack_end].rightfoot_sole[3] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[jump_attack_end].rightfoot_sole[4] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 }; 
		}

		//spin_attack
		{
			Animation_Max = 6;
			playerAnimation[spin_attack].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].lefthend= new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[spin_attack].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[spin_attack].body[0]			= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			playerAnimation[spin_attack].body[1]			= { D3DXVECTOR3(0.0f, -2.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].body[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, (-D3DX_PI * 9) / 8, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].body[3]			= { D3DXVECTOR3(0.0f, -6.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, (-D3DX_PI*2), 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].body[4]			= { D3DXVECTOR3(0.0f, -6.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, (-D3DX_PI*2) , 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].body[5]			= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].head[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/ 5, -D3DX_PI/7, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].head[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].head[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 7, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].head[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].head[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].head[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, -D3DX_PI / 7, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.7f, 0.0f, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.7f, 0.0f, -D3DX_PI/15),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, -D3DX_PI / 8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/7, -D3DX_PI/8),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].leftarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/15, 0.0f,  -D3DX_PI/3),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/15, 0.0f,  -D3DX_PI/3),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10,  -D3DX_PI/10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/10,  -D3DX_PI/10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 7, -D3DX_PI / 8),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].lefthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].lefthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].lefthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].lefthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].lefthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].lefthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/5, D3DX_PI/1.1f, D3DX_PI/3),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/2, D3DX_PI/1.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/2, D3DX_PI/1.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].righthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/2, D3DX_PI/1.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].righthend[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.5f, D3DX_PI/2, D3DX_PI/1.5f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].righthend[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, D3DX_PI / 1.1f, D3DX_PI / 3),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),10  };
			playerAnimation[spin_attack].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, -D3DX_PI/5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, -D3DX_PI/5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, -D3DX_PI/5, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightarm_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, -D3DX_PI / 5, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, D3DX_PI/12, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, -D3DX_PI/20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/3, 0.0f, -D3DX_PI/20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, D3DX_PI / 12, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/2.2f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.2f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 12, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 12, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].leftfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 8, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_up[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, -D3DX_PI/5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].rightfoot_up[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_up[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/4, 0.0f, -D3DX_PI/5),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_up[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_up[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_up[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, -D3DX_PI / 5),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/8, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/8, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/7, D3DX_PI/8, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_down[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_down[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 7, D3DX_PI / 8, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, D3DX_PI/5, D3DX_PI/5),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			playerAnimation[spin_attack].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),							D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_sole[4]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[spin_attack].rightfoot_sole[5]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, D3DX_PI / 5, D3DX_PI / 5),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			
		}

		//slip_move
		{
		Animation_Max = 2;
		playerAnimation[slip_move].body = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].head = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
		playerAnimation[slip_move].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

		playerAnimation[slip_move].body[0]				= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].body[1]				= { D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.4f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.4f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 2, D3DX_PI / 2),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 2, D3DX_PI / 2),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 7),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 7),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.6f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.6f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI /1.6f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI /1.6f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		playerAnimation[slip_move].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		playerAnimation[slip_move].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };

		}

		//be_attack
		{
			Animation_Max = 3;
			playerAnimation[be_attack].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[be_attack].body[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].body[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].body[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 1.8f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 1.8f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 1.8f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 1.8f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			playerAnimation[be_attack].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			playerAnimation[be_attack].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
		}

		//guard
		{
			Animation_Max = 2;
			playerAnimation[guard].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			playerAnimation[guard].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			playerAnimation[guard].body[0]				= { D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].body[1]				= { D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, D3DX_PI / 20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, D3DX_PI / 20),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.7f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2.7f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, -D3DX_PI / 4, D3DX_PI / 5),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 5, -D3DX_PI / 4, D3DX_PI / 5),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, 0.0f, D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, -D3DX_PI / 14),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, -D3DX_PI / 14),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, -D3DX_PI / 30),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 20, 0.0f, -D3DX_PI / 30),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 10),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
			playerAnimation[guard].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6.5f, D3DX_PI / 3, D3DX_PI / 10),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 ,Animation_Max };
			playerAnimation[guard].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6.5f, D3DX_PI / 3, D3DX_PI / 10),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),15 };
		}
	}

	void Player::Animation_control()
	{
		//今のアニメーションをもらう
		{
			part[part_body].part_anime = playerAnimation[player_action_now].body;
			part[part_head].part_anime = playerAnimation[player_action_now].head;
			part[part_leftarm_up].part_anime = playerAnimation[player_action_now].leftarm_up;
			part[part_leftarm_down].part_anime = playerAnimation[player_action_now].leftarm_down;
			part[part_lefthend].part_anime = playerAnimation[player_action_now].lefthend;
			part[part_rightarm_up].part_anime = playerAnimation[player_action_now].rightarm_up;
			part[part_rightarm_down].part_anime = playerAnimation[player_action_now].rightarm_down;
			part[part_righthend].part_anime = playerAnimation[player_action_now].righthend;
			part[part_leftfoot_up].part_anime = playerAnimation[player_action_now].leftfoot_up;
			part[part_leftfoot_down].part_anime = playerAnimation[player_action_now].leftfoot_down;
			part[part_rightfoot_up].part_anime = playerAnimation[player_action_now].rightfoot_up;
			part[part_rightfoot_down].part_anime = playerAnimation[player_action_now].rightfoot_down;
			part[part_leftfoot_sole].part_anime = playerAnimation[player_action_now].leftfoot_sole;
			part[part_rightfoot_sole].part_anime = playerAnimation[player_action_now].rightfoot_sole;
		}
		//もしアニメーションが変りたいなら　NEXTアニメーションをもらう
		if (anime_change == lastaction_setting)
		{
			part[part_body].part_anime_next				= playerAnimation[player_action_next].body;
			part[part_head].part_anime_next				= playerAnimation[player_action_next].head;
			part[part_leftarm_up].part_anime_next		= playerAnimation[player_action_next].leftarm_up;
			part[part_leftarm_down].part_anime_next		= playerAnimation[player_action_next].leftarm_down;
			part[part_lefthend].part_anime_next			= playerAnimation[player_action_next].lefthend;
			part[part_rightarm_up].part_anime_next		= playerAnimation[player_action_next].rightarm_up;
			part[part_rightarm_down].part_anime_next	= playerAnimation[player_action_next].rightarm_down;
			part[part_righthend].part_anime_next		= playerAnimation[player_action_next].righthend;
			part[part_leftfoot_up].part_anime_next		= playerAnimation[player_action_next].leftfoot_up;
			part[part_leftfoot_down].part_anime_next	= playerAnimation[player_action_next].leftfoot_down;
			part[part_rightfoot_up].part_anime_next		= playerAnimation[player_action_next].rightfoot_up;
			part[part_rightfoot_down].part_anime_next	= playerAnimation[player_action_next].rightfoot_down;
			part[part_leftfoot_sole].part_anime_next	= playerAnimation[player_action_next].leftfoot_sole;
			part[part_rightfoot_sole].part_anime_next	= playerAnimation[player_action_next].rightfoot_sole;
		}
		
		for (int i = 0; i < PLAYERPART_MAX; i++)
		{
			if (anime_change == action_no_switch)
			{
				int index = (int)part[i].move_time;
				float	time = part[i].move_time - index;
				//int		size = sizeof(part[i].part_anime) / sizeof(INTERPOLATION_DATA_BASE);
				int		size = playerAnimation[player_action_now].body[0].Array_long;
				float dt = 1.0f / part[i].part_anime[index].frame;	// 1フレームで進める時間
				part[i].move_time += dt;					// アニメーションの合計時間に足す

				if (player_action_now == action_jump)
				{
					if (index == 2 &&spd_y>0.5f)
					{
						time = 0.0f;
						index = 2;
						part[i].move_time = 2.0f;
					}
					else if (index == 3 && spd_y <= 0.5f)
					{
						time = 0.0f;
						index = 3;
						part[i].move_time = 3.0f;
					}

					// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 vec_new = part[i].part_anime[index + 1].pos - part[i].part_anime[index].pos;
					part[i].anime_pos_plus = part[i].part_anime[index].pos + vec_new * time;

					// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 rot_new = part[i].part_anime[index + 1].rot - part[i].part_anime[index].rot;
					part[i].anime_rot_plus = part[i].part_anime[index].rot + rot_new * time;
					// scaleを求める S = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 scl_new = part[i].part_anime[index + 1].scl - part[i].part_anime[index].scl;
					part[i].anime_scl_plus = part[i].part_anime[index].scl + scl_new * time;
				}
				else if (player_action_now == jump_attack_end)
				{
					if (index >= 2 )
					{
						time = 0.0f;
						index = 2;
						part[i].move_time = 2.0f;
					}

					// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 vec_new = part[i].part_anime[index + 1].pos - part[i].part_anime[index].pos;
					part[i].anime_pos_plus = part[i].part_anime[index].pos + vec_new * time;

					// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 rot_new = part[i].part_anime[index + 1].rot - part[i].part_anime[index].rot;
					part[i].anime_rot_plus = part[i].part_anime[index].rot + rot_new * time;
					// scaleを求める S = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 scl_new = part[i].part_anime[index + 1].scl - part[i].part_anime[index].scl;
					part[i].anime_scl_plus = part[i].part_anime[index].scl + scl_new * time;
				}
				else if (player_action_now == spin_attack)
				{
					if (index >= 3 )
					{
						D3DXVECTOR3 rot_next = part[i].part_anime[index + 1].rot;
						D3DXVECTOR3 rot_now= part[i].part_anime[index].rot;
						//角度修正
						{
							while (rot_now.y > D3DX_PI || rot_now.y < (-D3DX_PI))
							{
								if (rot_now.y > 0)
								{
									rot_now.y -= 2 * D3DX_PI;
								}
								else if (rot_now.y < 0)
								{
									rot_now.y += 2 * D3DX_PI;
								}
							}
							while (rot_now.x > D3DX_PI || rot_now.x < (-D3DX_PI))
							{
								if (rot_now.x > 0)
								{
									rot_now.x -= 2 * D3DX_PI;
								}
								else if (rot_now.x < 0)
								{
									rot_now.x += 2 * D3DX_PI;
								}
							}
							while (rot_now.z > D3DX_PI || rot_now.z < (-D3DX_PI))
							{
								if (rot_now.z > 0)
								{
									rot_now.z -= 2 * D3DX_PI;
								}
								else if (rot_now.z < 0)
								{
									rot_now.z += 2 * D3DX_PI;
								}
							}
						}
						//角度修正
						{
							while (rot_next.y > D3DX_PI || rot_next.y < (-D3DX_PI))
							{
								if (rot_next.y > 0)
								{
									rot_next.y -= 2 * D3DX_PI;
								}
								else if (rot_next.y < 0)
								{
									rot_next.y += 2 * D3DX_PI;
								}
							}
							while (rot_next.x > D3DX_PI || rot_next.x < (-D3DX_PI))
							{
								if (rot_next.x > 0)
								{
									rot_next.x -= 2 * D3DX_PI;
								}
								else if (rot_next.x < 0)
								{
									rot_next.x += 2 * D3DX_PI;
								}
							}
							while (rot_next.z > D3DX_PI || rot_next.z < (-D3DX_PI))
							{
								if (rot_next.z > 0)
								{
									rot_next.z -= 2 * D3DX_PI;
								}
								else if (rot_next.z < 0)
								{
									rot_next.z += 2 * D3DX_PI;
								}
							}
						}
						// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 vec_new = part[i].part_anime[index + 1].pos - part[i].part_anime[index].pos;
						part[i].anime_pos_plus = part[i].part_anime[index].pos + vec_new * time;

						// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 rot_new = rot_next - rot_now;
						part[i].anime_rot_plus = rot_now + rot_new * time;
						// scaleを求める S = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 scl_new = part[i].part_anime[index + 1].scl - part[i].part_anime[index].scl;
						part[i].anime_scl_plus = part[i].part_anime[index].scl + scl_new * time;
					}
					else
					{
						// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 vec_new = part[i].part_anime[index + 1].pos - part[i].part_anime[index].pos;
						part[i].anime_pos_plus = part[i].part_anime[index].pos + vec_new * time;

						// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 rot_new = part[i].part_anime[index + 1].rot - part[i].part_anime[index].rot;
						part[i].anime_rot_plus = part[i].part_anime[index].rot + rot_new * time;
						// scaleを求める S = StartX + (EndX - StartX) * 今の時間
						D3DXVECTOR3 scl_new = part[i].part_anime[index + 1].scl - part[i].part_anime[index].scl;
						part[i].anime_scl_plus = part[i].part_anime[index].scl + scl_new * time;
					}

					
				}
				else
				{
					if (index > (size - 2))	// ゴールをオーバーしていたら、最初へ戻す
					{
						part[i].move_time = 0.0f;
						index = 0;
					}
					// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 vec_new = part[i].part_anime[index + 1].pos - part[i].part_anime[index].pos;
					part[i].anime_pos_plus = part[i].part_anime[index].pos + vec_new * time;

					// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 rot_new = part[i].part_anime[index + 1].rot - part[i].part_anime[index].rot;
					part[i].anime_rot_plus = part[i].part_anime[index].rot + rot_new * time;
					// scaleを求める S = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 scl_new = part[i].part_anime[index + 1].scl - part[i].part_anime[index].scl;
					part[i].anime_scl_plus = part[i].part_anime[index].scl + scl_new * time;
				}
			}
			else
			{
				
				if (anime_change == lastaction_setting)
				{
					for (int j = 0; j < PLAYERPART_MAX; j++)
					{
						// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
						part[j].anime_pos_temporary = part[j].anime_pos_plus;

						// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
						part[j].anime_rot_temporary = part[j].anime_rot_plus;

						// scaleを求める S = StartX + (EndX - StartX) * 今の時間
						part[j].anime_scl_temporary = part[j].anime_scl_plus;

						part[j].move_time = 0.0f;
						anime_change = lastaction_setting_over;
					}
				}
				int index = (int)part[i].move_time;
				float time = part[i].move_time - index;
				if (player_action_next == action_jump)
				{
					part[i].move_time += PLAYER_ACTION_JUMP_SWITCH_TIME;
					if (part[i].move_time >= (1.0f))	// ゴールをオーバーしていたら、最初へ戻す
					{
						for (int j = 0; j < PLAYERPART_MAX; j++)
						{
							if (player_action_now == jump_attack_start)
							{
								part[j].move_time = 2.0f;
							}
							else if (player_action_now == slip_move && touch_ans == false)
							{
								part[j].move_time = 3.0f;
							}
							else
							{
								part[j].move_time = 1.0f;
							}
							
						}
						if (player_action_now != action_jump)
						{
							anime_change = action_no_switch;
							if (spd_y >= 0)
							{
								//if (player_action_now == action_walk || player_action_now == action_walk_back || player_action_now == stand_bigsword)
								//{
								//	spd_y += 7.0f;
								//}
								//else if (player_action_now == slip_move&& air_move == false && touch_ans==true)
								//{
								//	spd_y += 7.0f;
								//}
								if (player_action_now == slip_move && air_move == false && touch_ans == true)
								{
									spd_y += 7.0f;
								}
							}
							else if (spd_y < 0)
							{
								for (int j = 0; j < PLAYERPART_MAX; j++)
								{
									part[j].move_time = 3.0f;
								}
							}
							player_action_now = player_action_next;
							break;
						}
						else
						{
							player_action_now = player_action_next;
							anime_change = action_no_switch;
							//if (spd_y < 0)
							//{
							//	spd_y = 0;
							//}
							//spd_y += 7.0f;
							break;
						}
						
					}
					int anime_num = 0;
					if (spd_y < 0 )
					{
						anime_num = 3;
					}
					if (player_action_now == slip_move && air_move == true)
					{
						anime_num = 3;
					}
					if (player_action_now == jump_attack_start)
					{
						anime_num = 2;
					}
					// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 vec_new = part[i].part_anime_next[anime_num].pos - part[i].anime_pos_temporary;
					part[i].anime_pos_plus = part[i].anime_pos_temporary + vec_new * time;

					// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 rot_new = part[i].part_anime_next[anime_num].rot - part[i].anime_rot_temporary;
					part[i].anime_rot_plus = part[i].anime_rot_temporary + rot_new * time;

					// scaleを求める S = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 scl_new = part[i].part_anime_next[anime_num].scl - part[i].anime_scl_temporary;
					part[i].anime_scl_plus = part[i].anime_scl_temporary + scl_new * time;
				}
				else
				{
					
					part[i].move_time += PLAYER_ACTION_SWITCH_TIME;					// アニメーションの合計時間に足す
					if (part[i].move_time >= (1.0f))	// ゴールをオーバーしていたら、最初へ戻す
					{
						for (int j = 0; j < PLAYERPART_MAX; j++)
						{
							part[j].move_time = 1.0f;
							if (player_action_next == slip_move)
							{
								part[j].move_time = 0.0f;
							}
						}
						if (player_action_next == jump_attack_end)
						{
							spd_y = -PLAYER_MOVE_SPD_AIRDOWNATTACK;
						}
						player_action_now = player_action_next;
						anime_change = action_no_switch;
						break;
					}
					// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 vec_new = part[i].part_anime_next[0].pos - part[i].anime_pos_temporary;
					part[i].anime_pos_plus = part[i].anime_pos_temporary + vec_new * time;

					// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 rot_new = part[i].part_anime_next[0].rot - part[i].anime_rot_temporary;
					part[i].anime_rot_plus = part[i].anime_rot_temporary + rot_new * time;

					// scaleを求める S = StartX + (EndX - StartX) * 今の時間
					D3DXVECTOR3 scl_new = part[i].part_anime_next[0].scl - part[i].anime_scl_temporary;
					part[i].anime_scl_plus = part[i].anime_scl_temporary + scl_new * time;
				}
			}
		}
	}

	void Player::Speed_control()
	{
		//if重力加速度の発生はtrue、PLAYERのY方向のspdを減算する
		//xz方向の速度減らすとY方向の重力加速度の発生判定
		//PLAYERは空中ならば、xz方向の速度は減らない

		//特定アクションもxz方向の速度は減らない
		if (player_action_now == action_walk || player_action_now == action_walk_back || player_action_now == stand_bigsword)
		{
			if (touch_ans == true)
			{
				if (player_action_next == action_walk || player_action_next == action_walk_back || player_action_next == stand_bigsword)
				{
					can_switch_action = true;
					spd *= 0.7f;
				}
				air_move = false;
				spd_y = 0;


				if (spd <= 0.01)
				{
					spd = 0;
				}

				if (player_action_now != stand_bigsword && spd < 0.7 &&anime_change == action_no_switch)
				{
					player_action_next = stand_bigsword;
					anime_change = lastaction_setting;
				}
				if (player_action_now != action_walk && spd >= 0.7 && anime_change == action_no_switch)
				{
					player_action_next = action_walk;
					anime_change = lastaction_setting;
				}
			}
			else
			{
				spd_y -= (9.8f) / 60;
				if (player_action_now != action_jump && anime_change == action_no_switch && spd_y < 1.0f)
				{
					player_action_next = action_jump;
					anime_change = lastaction_setting;
				}
			}
		}
		else if (player_action_now == action_jump && anime_change == action_no_switch)
		{
			if (touch_ans == true && part[0].move_time > 1)
			{
				if (spd < 0.7)
				{
					player_action_next = stand_bigsword;
				}
				else
				{
					player_action_next = action_walk;
				}
				anime_change = lastaction_setting;
			}
			else
			{
				spd *= 0.9f;
				spd_y -= (9.8f) / 60;
			}
		}
		else if (player_action_now == normal_attack_1 || player_action_now == normal_attack_2 || player_action_now == normal_attack_3)
		{
			if (part[0].move_time < 2)
			{
				if (player_action_next == normal_attack_1 || player_action_next == normal_attack_2 || player_action_next == normal_attack_3)
				{
					spd = PLAYER_MOVE_SPD_NORMALATTACK;
				}
			}
			else
			{
				spd = 0;
			}

			if (touch_ans == true)
			{
				if (player_action_now == normal_attack_1 && player_action_next == normal_attack_1 && part[0].move_time > 3 && anime_change == action_no_switch)
				{
					if (spd < 0.7)
					{
						player_action_next = stand_bigsword;
					}
					else
					{
						player_action_next = action_walk;
					}
					anime_change = lastaction_setting;
				}
				else if (player_action_now == normal_attack_2 && player_action_next == normal_attack_2 && part[0].move_time > 3 && anime_change == action_no_switch)
				{
					if (spd < 0.7)
					{
						player_action_next = stand_bigsword;
					}
					else
					{
						player_action_next = action_walk;
					}
					anime_change = lastaction_setting;
				}
				else if (player_action_now == normal_attack_3 && player_action_next == normal_attack_3 && part[0].move_time > 3 && anime_change == action_no_switch)
				{
					if (spd < 0.7)
					{
						player_action_next = stand_bigsword;
					}
					else
					{
						player_action_next = action_walk;
					}
					anime_change = lastaction_setting;
				}
			}
			else
			{
				spd_y -= (9.8f) / 60;
				if (part[0].move_time > 3)
				{
					if (player_action_now != action_jump && anime_change == action_no_switch && spd_y != 0.0f)
					{
						can_switch_action = true;
						player_action_next = action_jump;
						anime_change = lastaction_setting;
					}
				}
			}


		}
		else if (player_action_now == spin_attack)
		{
			spd = 0;
			if (part[0].move_time >= 4)	// ゴールをオーバーしていたら、最初へ戻す
			{
				if (touch_ans == true)
				{
					if (player_action_next == spin_attack)
					{
						player_action_next = stand_bigsword;
						anime_change = lastaction_setting;
					}
				}
				else
				{
					if (player_action_next == spin_attack)
					{
						player_action_next = action_jump;
						anime_change = lastaction_setting;
					}
				}
			}
		}
		else if (player_action_now == jump_attack_start)
		{

			spd = 0;
			if (part[0].move_time >= 2 && part[0].move_time < 3)
			{
				spd_y = PLAYER_MOVE_SPD_AIRATTACK;
			}
			else if (part[0].move_time >= 3)
			{
				spd_y -= (9.8f) / 60;
			}

			if (part[0].move_time >= 4)
			{
				player_action_next = action_jump;
				anime_change = lastaction_setting;
			}
		}
		else if (player_action_now == jump_attack_end)
		{
			spd_y -= (9.8f) / 60;
			spd = 0;
			if (part[0].move_time < 1)
			{
				spd_y = -PLAYER_MOVE_SPD_AIRDOWNATTACK;
			}
			if (touch_ans == true && anime_change == action_no_switch)
			{
				player_action_next = stand_bigsword;
				anime_change = lastaction_setting;
			}
		}
		else if (player_action_now == slip_move)
		{
			spd = PLAYER_MOVE_SPD_SLIP;
			if (player_action_next == slip_move)
			{
				spd_y = 0;
			}

			if (part[0].move_time >= 1)
			{
				if (touch_ans == true)
				{
					player_action_next = action_walk;
					anime_change = lastaction_setting;
				}
				else
				{
					player_action_next = action_jump;
					anime_change = lastaction_setting;
				}
			}
		}
		else
		{
			spd_y -= (9.8f) / 60;
			if (player_action_now != action_jump && anime_change == action_no_switch && pos.y != 0.0f&&beAttack!=true)
			{
				
				player_action_next = action_jump;
				anime_change = lastaction_setting;
			}
		}
	}
	void Player::GetOthercollider(Collider3D* stage, Collider3D* enemy)
	{
		enemy_collider = enemy;
		stage_collider = stage;
	}
	void Player::SetWeapon(Weapon* g_weapon)
	{
		weapon=g_weapon;
	}
}