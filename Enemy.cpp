#include "Enemy.h"
namespace FIGHTING_GAME
{
	Enemy::Enemy()
	{
	}

	HRESULT Enemy::InitCharacter()
	{
		
		//Player用アニメーションを設置
		this->SetEnemyAnimation();
		weapon = new Weapon(renderer);
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
			enemy_action_now = walk_enemy;
			enemy_action_next = walk_enemy;
			anime_change = action_no_switch;
			can_switch_action = true;
		}

		//Playerのモデルpart物件を設立
		part = new Character[ENEMYPART_MAX];
		//Playerの全てのcolliderナンバーを設立
		collider_c = new int[ONE_ENEMY_COLLIDER3D_MAX];
		//Player用モデルをLoadする
		if(enemy_num==0)
		{
			renderer->LoadModel(ENEMYMODEL_body, &part[part_body].model);
			renderer->LoadModel(ENEMYMODEL_head, &part[part_head].model);
			renderer->LoadModel(ENEMYMODEL_leftarm_up, &part[part_leftarm_up].model);
			renderer->LoadModel(ENEMYMODEL_leftarm_down, &part[part_leftarm_down].model);
			renderer->LoadModel(ENEMYMODEL_lefthend, &part[part_lefthend].model);
			renderer->LoadModel(ENEMYMODEL_rightarm_up, &part[part_rightarm_up].model);
			//renderer->LoadModel(ENEMYMODEL_rightarm_down, &part[part_rightarm_down].model);
			//renderer->LoadModel(ENEMYMODEL_righthend, &part[part_righthend].model);
			renderer->LoadModel(ENEMYMODEL_leftfoot_up, &part[part_leftfoot_up].model);
			renderer->LoadModel(ENEMYMODEL_leftfoot_down, &part[part_leftfoot_down].model);
			//renderer->LoadModel(ENEMYMODEL_rightfoot_up, &part[part_rightfoot_up].model);
			//renderer->LoadModel(ENEMYMODEL_rightfoot_down, &part[part_rightfoot_down].model);
			renderer->LoadModel(ENEMYMODEL_leftfoot_sole, &part[part_leftfoot_sole].model);
			//renderer->LoadModel(PLAYERMODEL_rightfoot_sole, &part[part_rightfoot_sole].model);
			renderer->LoadModel(ENEMYMODEL_discover, &model);
			weapon->InitWeapon(enemy_weapon);
		}
		else
		{
			weapon->InitWeapon(weaponobj_load);
		}
		//Playerのモデルpart物件の最初の場所と　collider大きさと場所を設立
		{
			part[part_body].pos_origin = D3DXVECTOR3(0.0f, 47.0f, 0.0f);
			part[part_body].pos_collider = D3DXVECTOR3(0.0f, 47.0f, 0.0f);
			part[part_body].collider_wxhylz = D3DXVECTOR3(17.0f, 28.0f, 15.0f);

			part[part_head].pos_origin = D3DXVECTOR3(0.0f, 68.0f, 0.0f);
			part[part_head].pos_collider = D3DXVECTOR3(0.0f, 68.0f, 0.0f);
			part[part_head].collider_wxhylz = D3DXVECTOR3(15.0f, 17.0f, 15.0f);

			part[part_leftarm_up].pos_origin = D3DXVECTOR3(11.0f, 60.0f, 0.0f);
			part[part_leftarm_up].pos_collider = D3DXVECTOR3(11.0f, 53.0f, 0.0f);
			part[part_leftarm_up].collider_wxhylz = D3DXVECTOR3(5.0f, 17.0f, 5.0f);

			part[part_leftarm_down].pos_origin = D3DXVECTOR3(11.0f, 46.0f, 0.0f);
			part[part_leftarm_down].pos_collider = D3DXVECTOR3(11.0f, 39.0f, 0.0f);
			part[part_leftarm_down].collider_wxhylz = D3DXVECTOR3(5.0f, 12.0f, 5.0f);

			part[part_lefthend].pos_origin = D3DXVECTOR3(11.0f, 31.0f, 0.0f);
			part[part_lefthend].pos_collider = D3DXVECTOR3(11.0f, 31.0f, 0.0f);
			part[part_lefthend].collider_wxhylz = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

			part[part_rightarm_up].pos_origin = D3DXVECTOR3(-11.0f, 60.0f, 0.0f);
			part[part_rightarm_up].pos_collider = D3DXVECTOR3(-11.0f, 53.0f, 0.0f);
			part[part_rightarm_up].collider_wxhylz = D3DXVECTOR3(5.0f, 17.0f, 5.0f);

			part[part_rightarm_down].pos_origin = D3DXVECTOR3(-11.0f, 46.0f, 0.0f);
			part[part_rightarm_down].pos_collider = D3DXVECTOR3(-11.0f, 39.0f, 0.0f);
			part[part_rightarm_down].collider_wxhylz = D3DXVECTOR3(5.0f, 12.0f, 5.0f);

			part[part_righthend].pos_origin = D3DXVECTOR3(-11.0f, 31.0f, 0.0f);
			part[part_righthend].pos_collider = D3DXVECTOR3(-11.0f, 31.0f, 0.0f);
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

			for (int i = 0; i < ENEMYPART_MAX; i++)
			{
				part[i].pos = part[i].pos_origin;
				part[i].rot = rot;
				part[i].scl = scl;
				collider_c[i] = collider->CreateCollider3DBox(part[i].pos_collider, part[i].rot, part[i].collider_wxhylz.x, part[i].collider_wxhylz.y, part[i].collider_wxhylz.z, Collider3DType_box, Enemy_Part_object);
				part[i].collider_index = collider_c[i];
				part[i].move_time = 0.0f;
			}
			collider_c[Character_collider_top]		= collider->CreateCollider3DBox(D3DXVECTOR3(0.0f, collider_wxhylz.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, 0.0f, collider_wxhylz.z, Collider3DType_box, Enemy_object);
			collider_c[Character_collider_stand]	= collider->CreateCollider3DBox(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, 0.0f, collider_wxhylz.z, Collider3DType_box, Enemy_object);
			collider_c[Character_collider_front]	= collider->CreateCollider3DBox(D3DXVECTOR3(0.0f, (collider_wxhylz.y / 2), (-collider_wxhylz.z / 2)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, collider_wxhylz.y, 0.0f, Collider3DType_box, Enemy_object);
			collider_c[Character_collider_behind]	= collider->CreateCollider3DBox(D3DXVECTOR3(0.0f, (collider_wxhylz.y / 2), (collider_wxhylz.z / 2)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), collider_wxhylz.x, collider_wxhylz.y, 0.0f, Collider3DType_box, Enemy_object);
			collider_c[Character_collider_left]		= collider->CreateCollider3DBox(D3DXVECTOR3((-collider_wxhylz.x / 2), (collider_wxhylz.y / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, Enemy_object);
			collider_c[Character_collider_right]	= collider->CreateCollider3DBox(D3DXVECTOR3((collider_wxhylz.x / 2), (collider_wxhylz.y / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, Enemy_object);
			collider_c[20]							= collider->CreateCollider3DBox(D3DXVECTOR3(0.0f, (collider_wxhylz.y / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SERCH_RANGE, collider_wxhylz.y, ENEMY_SERCH_RANGE, Collider3DType_box, Enemy_object);
		}

		action_time_start = 0.0f;
		action_time_end = 0.0f;
		
		pos = D3DXVECTOR3(2.0f* enemy_num , 0.0f, 1000.0f);
		if (enemy_num >= 0&& enemy_num < 4 )
		{
			pos = D3DXVECTOR3(((10.0f* enemy_num)-50.0f), 0.0f, 1000.0f);
		}
		else if(enemy_num >= 4 && enemy_num < 8)
		{
			pos = D3DXVECTOR3(((10.0f* enemy_num) - 50.0f), 0.0f, -1000.0f);
		}
		else if (enemy_num >= 8 && enemy_num < 10)
		{
			pos = D3DXVECTOR3(-1867.62f, 435.0f, ((10.0f* enemy_num) - 25.0f));
		}
		else if (enemy_num >= 10 && enemy_num < 11)
		{
			pos = D3DXVECTOR3(-1477.82f, 910.0f, -1748.39f);
		}
		else if (enemy_num >= 11 && enemy_num < 13)
		{
			pos = D3DXVECTOR3(1533.79f + (5.0f* enemy_num), 685.0f, -1527.44f+ (5.0f* enemy_num));
		}
		else if (enemy_num >= 13 && enemy_num < 14)
		{
			pos = D3DXVECTOR3(0.0f, 1010.0f, 0.0f);
		}
		reborn_pos = pos;
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot_destine = rot;
		spd = 0.0f;
		HP = ENEMY_HP_MAX;
		player_serch = false;
		use = true;
		dying = false;
		beAttack = false;
		attack_hit = false;
		beattack_timer = 0;
		beAttack_moveway = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rangex = 0;
		kyorix = 0;
		moveway_change = 0;
		srand((unsigned)time(NULL));
		return S_OK;
	}

	void Enemy::UpdateCharacter()
	{
		if (dying == true)
		{
			beAttack = false;
			if (enemy_action_next != stand_enemy)
			{
				enemy_action_next = stand_enemy;
				anime_change = lastaction_setting;
			}
			HP += 0.3f;
			if (anime_change != action_no_switch)
			{
				//ENEMYのアニメーションを計算して、モデルの姿勢を修正
				this->Animation_control();
				//修正したPLAYERのpartのposとrotを現在のposを反応する
				this->Update_Enemy_Pos();
			}
			
			if (HP >= ENEMY_HP_MAX)
			{
				HP = ENEMY_HP_MAX;
				dying = false;
				pos = reborn_pos;
				use = true;
			}
		}
		else
		{
			this->Enemy_Move();
			this->RotRevise();

			if (beAttack == false)
			{
				moveway_xyz.x = (-sinf(rot.y))*spd;
				moveway_xyz.z = (-cosf(rot.y))*spd;
				moveway_xyz.y = spd_y;
			}
			else
			{
				moveway_xyz.y = spd_y;
			}
			
			this->Enemy_beAttack();
			//現在のPOSをPLAYERの移動量で加算して、移動後のPOSを計算
			pos_destine = pos;
			pos_destine += moveway_xyz;
			this->Character_edge_control();

			//PLAYERとMODELのPOSを制御====================================================

			//stageのcollider判定
			touch_ans = false;//地面を触ったどうかを判定の変数
			touch_top_ans = false;//頭を触ったどうかを判定の変数
			ground_y = pos_destine.y;//現在POSの地面の高さの変数
			//移動後のPOSを修正
			this->Character_PosUpdate();
			if (touch_ans == false)
			{
				spd_y -= (9.8f) / 60;
			}
			else
			{
				if (touch_ans == true && spd_y <= 0 && beAttack == true)
				{
					beAttack = false;
					beattack_timer = 0;
					spd = 0;
				}
				spd_y = 0;
			}
			if (beAttack == true)
			{
				beattack_timer++;
				if (beattack_timer > 25)
				{
					beAttack = false;
					beattack_timer = 0;
				}
			}
			this->Character_edge_control();
			//修正した移動量をPLAYERのposを加算して、移動します。
			pos += moveway_xyz;
			//PLAYERのアニメーションを計算して、モデルの姿勢を修正
			this->Animation_control();
			//修正したPLAYERのpartのposとrotを現在のposを反応する
			this->Update_Enemy_Pos();

			//PLAYERのSPDを制御=====================================================================	

			//=====================================================================

			//ENEMYのPOS関わらない他の物事の衝突判定(攻撃、hpの処理とか
			if (enemy_action_next != attack_enemy)
			{
				attack_hit = false;
			}
			this->Enemy_Attack();
			if (pos.y < (reborn_pos.y - 150.0f))
			{
				HP = 0;
				spd = 0;
				spd_y = 0;
				dying = true;
				use = false;
			}
		}


	}
	void Enemy::DrawCharacter()
	{
		if (use == true && GameDate::DrawType != Draw_ColliderOnly &&dying!=true)
		{
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori = player->pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			if (kyori < (1500.0f)&& move_kyori.y>(-300.0f))
			{
				for (int i = 0; i < ONE_ENEMY_COLLIDER3D_MAX; i++)
				{
					if (collider->g_Collider3D[collider_c[i]].Use == false)
					{
						collider->SetCollider3D_use(collider_c[i], true);
					}
				}

				D3DXVECTOR3 discover_pos = pos;
				discover_pos.y += 90.0f;
				if (enemy_num == 0)
				{
					for (int i = 0; i < CHARACTERPART_MAX; i++)
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
					if (player_serch == true)
					{
						renderer->Draw_3DModel_Part(mtxWorld, scl, rot, discover_pos, &model);
					}
				}
				else
				{
					for (int i = 0; i < CHARACTERPART_MAX; i++)
					{
						switch (i)
						{
						case part_body:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_body);
							break;
						case part_head:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_head);
							break;
						case part_leftarm_up:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftarm_up);
							break;
						case part_leftarm_down:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftarm_down);
							break;
						case part_lefthend:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_lefthend);
							break;
						case part_rightarm_up:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_rightarm_up);
							break;
						case part_rightarm_down:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftarm_down);
							break;
						case part_righthend:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_lefthend);
							weapon->DrawWeapon();
							break;
						case part_leftfoot_up:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_up);
							break;
						case part_leftfoot_down:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_down);
							break;
						case part_rightfoot_up:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_up);
							break;
						case part_rightfoot_down:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_down);
							break;
						case part_leftfoot_sole:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_sole);
							break;
						case part_rightfoot_sole:
							renderer->Draw_3DModel_Part(part[i].mtxWorld, part[i].scl, part[i].rot, part[i].pos, enemy_model_leftfoot_sole);
							break;
						}
					}
					if (player_serch == true)
					{
						renderer->Draw_3DModel_Part(mtxWorld, scl, rot, discover_pos, enemy_model_discover);
					}
				}
			}
			else
			{
				for (int i = 0; i < ONE_ENEMY_COLLIDER3D_MAX; i++)
				{
					if (collider->g_Collider3D[collider_c[i]].Use == true)
					{
						collider->SetCollider3D_use(collider_c[i], false);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < ONE_ENEMY_COLLIDER3D_MAX; i++)
			{
				if (collider->g_Collider3D[collider_c[i]].Use == true)
				{
					collider->SetCollider3D_use(collider_c[i], false);
				}
			}
		}
	}

	void Enemy::UninitCharacter()
	{
		if (enemy_num == 0)
		{
			renderer->UnloadModel(&model);
			//weapon->UninitWeapon(0);
			for (int i = 0; i < CHARACTERPART_MAX; i++)
			{
				if (i == part_rightarm_down || i == part_righthend || i == part_rightfoot_up
					|| i == part_rightfoot_down || i == part_rightfoot_sole)continue;
				renderer->UnloadModel(&part[i].model);
			}
		}
		else
		{
			//weapon->UninitWeapon(1);
		}
		delete[] enemyAnimation;
		delete weapon;
		delete[] part;
		delete[] collider_c;

		
	}

	void Enemy::Animation_control()
	{
		//今のアニメーションをもらう
		{
			part[part_body].part_anime				= enemyAnimation[enemy_action_now].body;
			part[part_head].part_anime				= enemyAnimation[enemy_action_now].head;
			part[part_leftarm_up].part_anime		= enemyAnimation[enemy_action_now].leftarm_up;
			part[part_leftarm_down].part_anime		= enemyAnimation[enemy_action_now].leftarm_down;
			part[part_lefthend].part_anime			= enemyAnimation[enemy_action_now].lefthend;
			part[part_rightarm_up].part_anime		= enemyAnimation[enemy_action_now].rightarm_up;
			part[part_rightarm_down].part_anime		= enemyAnimation[enemy_action_now].rightarm_down;
			part[part_righthend].part_anime			= enemyAnimation[enemy_action_now].righthend;
			part[part_leftfoot_up].part_anime		= enemyAnimation[enemy_action_now].leftfoot_up;
			part[part_leftfoot_down].part_anime		= enemyAnimation[enemy_action_now].leftfoot_down;
			part[part_rightfoot_up].part_anime		= enemyAnimation[enemy_action_now].rightfoot_up;
			part[part_rightfoot_down].part_anime	= enemyAnimation[enemy_action_now].rightfoot_down;
			part[part_leftfoot_sole].part_anime		= enemyAnimation[enemy_action_now].leftfoot_sole;
			part[part_rightfoot_sole].part_anime	= enemyAnimation[enemy_action_now].rightfoot_sole;
		}
		//もしアニメーションが変りたいなら　NEXTアニメーションをもらう
		if (anime_change == lastaction_setting)
		{
			part[part_body].part_anime_next					= enemyAnimation[enemy_action_next].body;
			part[part_head].part_anime_next					= enemyAnimation[enemy_action_next].head;
			part[part_leftarm_up].part_anime_next			= enemyAnimation[enemy_action_next].leftarm_up;
			part[part_leftarm_down].part_anime_next			= enemyAnimation[enemy_action_next].leftarm_down;
			part[part_lefthend].part_anime_next				= enemyAnimation[enemy_action_next].lefthend;
			part[part_rightarm_up].part_anime_next			= enemyAnimation[enemy_action_next].rightarm_up;
			part[part_rightarm_down].part_anime_next		= enemyAnimation[enemy_action_next].rightarm_down;
			part[part_righthend].part_anime_next			= enemyAnimation[enemy_action_next].righthend;
			part[part_leftfoot_up].part_anime_next			= enemyAnimation[enemy_action_next].leftfoot_up;
			part[part_leftfoot_down].part_anime_next		= enemyAnimation[enemy_action_next].leftfoot_down;
			part[part_rightfoot_up].part_anime_next			= enemyAnimation[enemy_action_next].rightfoot_up;
			part[part_rightfoot_down].part_anime_next		= enemyAnimation[enemy_action_next].rightfoot_down;
			part[part_leftfoot_sole].part_anime_next		= enemyAnimation[enemy_action_next].leftfoot_sole;
			part[part_rightfoot_sole].part_anime_next		= enemyAnimation[enemy_action_next].rightfoot_sole;
		}

		for (int i = 0; i < ENEMYPART_MAX; i++)
		{
			if (anime_change == action_no_switch)
			{
				int index = (int)part[i].move_time;
				float	time = part[i].move_time - index;
				//int		size = sizeof(part[i].part_anime) / sizeof(INTERPOLATION_DATA_BASE);
				int		size = enemyAnimation[enemy_action_now].body[0].Array_long;
				float dt = 1.0f / part[i].part_anime[index].frame;	// 1フレームで進める時間
				part[i].move_time += dt;					// アニメーションの合計時間に足す

				if (index > (size - 2))	// ゴールをオーバーしていたら、最初へ戻す
				{
					part[i].move_time = 0.0f;
					index = 0;
					if (enemy_action_now==attack_enemy&& attack_hit == true)
					{
						attack_hit = false;
					}
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
			else
			{
				if (anime_change == lastaction_setting)
				{
					for (int j = 0; j < ENEMYPART_MAX; j++)
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
				
				part[i].move_time += ENEMY_ACTION_SWITCH_TIME;					// アニメーションの合計時間に足す
				if (part[i].move_time >= (1.0f))	// ゴールをオーバーしていたら、最初へ戻す
				{
					for (int j = 0; j < ENEMYPART_MAX; j++)
					{
						part[j].move_time = 1.0f;
					}
					enemy_action_now = enemy_action_next;
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

	void Enemy::Update_Enemy_Pos()
	{
		this->Update_Pos();
		this->Update_Collider(pos, rot);
		weapon->Update_Pos(part[part_righthend].pos, part[part_righthend].rot);
		weapon->Update_Collider();
		D3DXVECTOR3 serch_pos = pos_destine;
		serch_pos.y += (collider_wxhylz.y / 2);
		collider->SetCollider3D(collider_c[20], serch_pos, rot);
	}

	void Enemy::Enemy_Move()
	{
		if (beAttack == false)
		{
			player_serch = false;
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori.y += (collider_wxhylz.y / 2);
			move_kyori = player->pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			float kyori_p = sqrtf((ENEMY_SERCH_RANGE*ENEMY_SERCH_RANGE) + (ENEMY_SERCH_RANGE + ENEMY_SERCH_RANGE));
			//if model中心点とplayerposの距離　< modelのr+playerのr  =>BBC判定に進む
			if (kyori < (kyori_p))
			{
				for (int i = 14; i < 20; i++)
				{
					if (player_serch == false)
					{
						player_serch = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[20]], &player_collider->g_Collider3D[i]);
						if (player_serch == true)break;
					}
				}
			}
			else
			{
				player_serch = false;
			}


			if (spd_y == 0)
			{
				if (player_serch == false)
				{
					moveway_change++;
					if (moveway_change > ENEMY_MOVEWAY_CHANGE_STANDBY)
					{
						spd = 0;
						if (enemy_action_next != stand_enemy)
						{
							enemy_action_next = stand_enemy;
							anime_change = lastaction_setting;
						}
						if (moveway_change > ENEMY_MOVEWAY_CHANGE_MAX)
						{
							int aa = rand() % (10);
							if (aa >= 5)
							{
								aa = rand() % (10) + 1;
								rot_destine.y = rot.y + (D3DX_PI / (aa));
							}
							else
							{
								aa = rand() % (10) + 1;
								rot_destine.y = rot.y + (-D3DX_PI) / (aa);
							}
							moveway_change = 0;
						}
					}
					else
					{
						if (enemy_action_next != walk_enemy)
						{
							enemy_action_next = walk_enemy;
							anime_change = lastaction_setting;
						}
						spd = 3;
					}
				}
				else
				{
					moveway_change = 0;
					this->Player_toward_rot();
					
					D3DXVECTOR3 p_m = player->pos - pos_destine;
					p_m.y = 0.0f;
					float p_e_kyori = D3DXVec3Length(&p_m);
					if (p_e_kyori < ((collider_wxhylz.x * 2.5f) / 2))
					{
						spd = 0;
						if (enemy_action_next != attack_enemy)
						{
							enemy_action_next = attack_enemy;
							anime_change = lastaction_setting;
						}
					}
					else
					{
						if (enemy_action_now == attack_enemy && part[0].move_time < 3.0)
						{
							spd = 0;
						}
						else
						{
							spd = 3;
							if (enemy_action_next != walk_enemy)
							{
								enemy_action_next = walk_enemy;
								anime_change = lastaction_setting;
							}
						}
					}
				}
			}
			else
			{
				if (enemy_action_next != be_attack_enemy)
				{
					enemy_action_next = be_attack_enemy;
					anime_change = lastaction_setting;
				}
				if (pos_destine.y < 150.0f)
				{
					D3DXVECTOR3 p_m = -pos_destine;
					p_m.y = 0.0f;
					float p_e_kyori = D3DXVec3Length(&p_m);
					Calculate* math = new Calculate();
					D3DXVECTOR3 zzz = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					float rot_destiney = math->Two_vector_angle(&p_m, &zzz);
					zzz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					delete math;
					if (zzz.x > pos_destine.x  &&zzz.z >= pos_destine.z)
					{
						//rot_destiney  = (-D3DX_PI)+abs(rot_destiney );
						rot_destiney = (-D3DX_PI / 2) - abs(rot_destiney);
					}
					else if (zzz.x > pos_destine.x && zzz.z < pos_destine.z)
					{
						rot_destiney = -abs(rot_destiney);
					}
					else if (zzz.x < pos_destine.x&&zzz.z >= pos_destine.z)
					{
						//rot_destiney  = D3DX_PI-abs(rot_destiney );
						rot_destiney = (D3DX_PI / 2) + abs(rot_destiney);
					}
					else if (zzz.x < pos_destine.x&& zzz.z < pos_destine.z)
					{
						rot_destiney = abs(rot_destiney);
					}
					else if (pos_destine.x == zzz.x&&zzz.z > pos_destine.z)
					{
						rot_destiney = D3DX_PI;
					}
					else if (zzz.x > pos_destine.x&& zzz.z < pos_destine.z)
					{
						rot_destiney = 0;
					}
					rot_destine.y = rot_destiney;
				}
				spd = 3;
			}
		}
		else
		{
			if (enemy_action_next != be_attack_enemy)
			{
				enemy_action_next = be_attack_enemy;
				anime_change = lastaction_setting;
			}
		}
		
	}
	void Enemy::SetEnemyAnimation(void)
	{
		enemyAnimation = new CharacterAnimation[ENEMY_KIND_OF_ACTION];
		int Animation_Max = 0;
		
		//stand_enemy
		{
			Animation_Max = 3;
			enemyAnimation[stand_enemy].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[stand_enemy].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

			enemyAnimation[stand_enemy].body[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].body[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].body[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].head[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].head[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].head[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].leftarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].leftarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].lefthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].lefthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].lefthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].righthend[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].righthend[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].righthend[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightarm_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].rightarm_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightarm_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightarm_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].rightarm_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightarm_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].leftfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].leftfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].leftfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].leftfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_up[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].rightfoot_up[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_up[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_down[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].rightfoot_down[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_down[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_sole[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 ,Animation_Max };
			enemyAnimation[stand_enemy].rightfoot_sole[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };
			enemyAnimation[stand_enemy].rightfoot_sole[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),30 };

		}

		//walk_enemy
		{
			Animation_Max = 11;
			enemyAnimation[walk_enemy].body			= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].head			= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].leftarm_up		= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].leftarm_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].lefthend		= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].righthend		= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].rightarm_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].rightarm_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].leftfoot_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].leftfoot_down	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].rightfoot_up	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].leftfoot_sole	= new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[walk_enemy].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			
			enemyAnimation[walk_enemy].body[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI/9, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 ,Animation_Max };
			enemyAnimation[walk_enemy].body[1]				= { D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[2]				= { D3DXVECTOR3(0.0f, -1.8f, 0.0f), D3DXVECTOR3(-D3DX_PI/9, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1  };
			enemyAnimation[walk_enemy].body[4]				= { D3DXVECTOR3(0.0f, 0.5f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[5]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[6]				= { D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[7]				= { D3DXVECTOR3(0.0f, -1.8f, 0.0f), D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].body[8]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].body[9]				= { D3DXVECTOR3(0.0f, 0.5f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].body[10]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR3(-D3DX_PI / 9, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[3]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].head[4]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[5]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[6]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[7]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[8]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].head[9]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].head[10]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/7, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftarm_up[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftarm_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].leftarm_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			enemyAnimation[walk_enemy].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			enemyAnimation[walk_enemy].lefthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].lefthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].lefthend[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].lefthend[10]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  };
			enemyAnimation[walk_enemy].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5   };
			enemyAnimation[walk_enemy].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].righthend[4]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[5]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[6]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[7]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[8]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].righthend[9]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].righthend[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI/2),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightarm_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightarm_up[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/3, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightarm_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightarm_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightarm_down[10]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_up[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].leftfoot_sole[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].leftfoot_sole[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_up[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.2f, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3, 0.0f, 0.0f),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 3.5f, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 5, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_up[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_up[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),	D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].rightfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_down[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 3, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_down[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 8, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_down[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5  ,Animation_Max };
			enemyAnimation[walk_enemy].rightfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_sole[4]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[5]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[6]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[7]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 9, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[8]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),1 };
			enemyAnimation[walk_enemy].rightfoot_sole[9]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
			enemyAnimation[walk_enemy].rightfoot_sole[10]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),5 };
		}

		//attack_enemy
		{
		Animation_Max = 4;
		enemyAnimation[attack_enemy].body = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].head = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
		enemyAnimation[attack_enemy].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];

		enemyAnimation[attack_enemy].body[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].body[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].body[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].body[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].head[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].head[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].head[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].head[3]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].leftarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].lefthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].lefthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].lefthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].lefthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].righthend[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].righthend[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].righthend[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].righthend[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI, 0.0f, -D3DX_PI/12),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/5, 0.0f, D3DX_PI/9),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].rightarm_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/12, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightarm_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 1.5f, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_up[3]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].leftfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].leftfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].leftfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_up[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].rightfoot_up[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_up[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_up[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI/6, 0.0f, 0.0f),				D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_down[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI/12, 0.0f, 0.0f),			D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 ,Animation_Max };
		enemyAnimation[attack_enemy].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		enemyAnimation[attack_enemy].rightfoot_sole[3]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),20 };
		}

		//be_attack_enemy
		{
			Animation_Max = 3;
			enemyAnimation[be_attack_enemy].body = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].head = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].leftarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].leftarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].lefthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].righthend = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].rightarm_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].rightarm_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].leftfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].leftfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].rightfoot_up = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].rightfoot_down = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].leftfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].rightfoot_sole = new INTERPOLATION_DATA_BASE[Animation_Max];
			enemyAnimation[be_attack_enemy].body[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].body[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].body[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 20, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].head[0]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].head[1]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].head[2]				= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 1.8f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].leftarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 1.8f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].leftarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].lefthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].lefthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].lefthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].righthend[0]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].righthend[1]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].righthend[2]			= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightarm_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 1.8f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].rightarm_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightarm_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 1.8f),					D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightarm_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].rightarm_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightarm_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 3),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].leftfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, -D3DX_PI / 10, D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_down[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].leftfoot_down[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_down[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_sole[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].leftfoot_sole[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].leftfoot_sole[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_up[0]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].rightfoot_up[1]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_up[2]		= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 4, D3DX_PI / 10, -D3DX_PI / 10),		D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_down[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].rightfoot_down[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_down[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 10, 0.0f, 0.0f),						D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_sole[0]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 ,Animation_Max };
			enemyAnimation[be_attack_enemy].rightfoot_sole[1]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
			enemyAnimation[be_attack_enemy].rightfoot_sole[2]	= { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),								D3DXVECTOR3(1.0f, 1.0f, 1.0f),10 };
		}


	}
	void Enemy::Enemy_Attack()
	{
		if (enemy_action_now == attack_enemy&&player->beAttack==false&& attack_hit==false&& part[0].move_time>1.0f)
		{
			bool atk_ans = false;
			for (int i = 0; i < ENEMYPART_MAX; i++)
			{
				atk_ans = collider->CheckHitOBB(&weapon->collider->g_Collider3D[weapon->collider_index[0]], &player_collider->g_Collider3D[player->part[i].collider_index]);
				if (atk_ans == true)
				{
					break;
				}
			}
			if (atk_ans == true)
			{
				attack_hit = true;
				player->Blow_point++;
				if (player->Blow_point > PLAYER_BLOW_MAX)
				{
					player->beAttack = true;
					player->Blow_point = 0;
					if (player->player_action_next != be_attack)
					{
						player->player_action_next = be_attack;
						player->anime_change = lastaction_setting;
					}
					//player->moveway_xyz = player->pos-weapon->collider->g_Collider3D->pos ;
					//player->moveway_xyz.y = 0.0f;
					//D3DXVec3Normalize(&player->moveway_xyz, &player->moveway_xyz);
					player->spd = 8;
					player->spd_y = 6;
					player->HP--;
					if (player->HP <= 0)
					{
						player->HP = 0;
						player->spd = 0;
						player->spd_y = 0;
						player->dying = true;
						player->use = false;
					}
					player->moveway_xyz = D3DXVECTOR3((-sinf(rot.y))*player->spd, player->spd_y, (-cosf(rot.y))* player->spd);
				}
				
			}
		}
	}
	void Enemy::Enemy_beAttack()
	{
		if (beAttack == false)
		{
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori.y += (collider_wxhylz.y / 2);
			move_kyori = player->pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			float kyori_p = sqrtf((ENEMY_SERCH_RANGE*ENEMY_SERCH_RANGE) + (ENEMY_SERCH_RANGE + ENEMY_SERCH_RANGE));
			if (kyori < (kyori_p))
			{
				if (player->player_action_now == normal_attack_1 || player->player_action_now == normal_attack_2 || player->player_action_now == normal_attack_3 || player->player_action_now == jump_attack_start || player->player_action_now == jump_attack_end || player->player_action_now == spin_attack)
				{
					{
						bool atk_ans = false;
						for (int i = 0; i < ENEMYPART_MAX; i++)
						{
							atk_ans = collider->CheckHitOBB(&collider->g_Collider3D[part[i].collider_index], &player->weapon->collider->g_Collider3D[player->weapon->collider_index[0]]);
							if (atk_ans == true)
							{
								break;
							}
						}
						if (atk_ans == true)
						{
							moveway_xyz = pos_destine - player->weapon->collider->g_Collider3D->pos;
							moveway_xyz.y = 0.0f;
							D3DXVec3Normalize(&moveway_xyz, &moveway_xyz);
							switch (player->player_action_now)
							{
							case normal_attack_1:
								spd = 10;
								spd_y = 3;
								HP--;
								break;
							case normal_attack_2:
								spd = 12;
								spd_y = 3;
								HP -= 2;
								break;
							case normal_attack_3:
								spd = 15;
								spd_y = 3;
								HP -= 3;
								break;
							case jump_attack_start:
								spd = 1;
								spd_y = 10;
								HP -= 2;
								break;
							case spin_attack:
								spd = 5;
								spd_y = 3;
								HP -= 1;
								break;
							case jump_attack_end:
								spd = 10;
								spd_y = 5;
								HP -= 2;
								break;
							}

							moveway_xyz = D3DXVECTOR3(moveway_xyz.x*spd, spd_y, moveway_xyz.z * spd);
							beAttack = true;
							if (HP > 0)
							{
								sound->PlaySoundA(SOUND_LABEL_SE_hit000);
							}
							else
							{
								sound->PlaySoundA(SOUND_LABEL_SE_bomb000);
							}
							

						}
					}
				}
			}
		}
		else
		{
			if (player->player_action_now == jump_attack_end&&(pos.y+ collider_wxhylz.y)> player->weapon->collider->g_Collider3D[player->weapon->collider_index[0]].pos.y)
			{
				D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
				move_kyori.y += (collider_wxhylz.y / 2);
				move_kyori = player->pos - move_kyori;
				float kyori = D3DXVec3Length(&move_kyori);
				float kyori_p = sqrtf((ENEMY_SERCH_RANGE*ENEMY_SERCH_RANGE) + (ENEMY_SERCH_RANGE + ENEMY_SERCH_RANGE));
				if (kyori < (kyori_p))
				{
					bool atk_ans = false;
					for (int i = 0; i < ENEMYPART_MAX; i++)
					{
						atk_ans = collider->CheckHitOBB(&collider->g_Collider3D[part[i].collider_index], &player->weapon->collider->g_Collider3D[player->weapon->collider_index[0]]);
						if (atk_ans == true)
						{
							break;
						}
					}
					if (atk_ans == true)
					{
						moveway_xyz = pos_destine - player->weapon->collider->g_Collider3D->pos;
						moveway_xyz.y = 0.0f;
						D3DXVec3Normalize(&moveway_xyz, &moveway_xyz);
						spd = 10;
						spd_y = 5;
						HP -= 2;
						moveway_xyz = D3DXVECTOR3(moveway_xyz.x*spd, spd_y, moveway_xyz.z * spd);
						beAttack = true;
						if (HP > 0)
						{
							sound->PlaySoundA(SOUND_LABEL_SE_hit000);
						}
						else
						{
							sound->PlaySoundA(SOUND_LABEL_SE_bomb000);
						}
					}
				}
			}
		}

		if (HP <= 0)
		{
			HP = 0;
			spd = 0;
			spd_y = 0;
			dying = true;
			use = false;
		}
	}
	void Enemy::Player_toward_rot()
	{
		D3DXVECTOR3 p_m = player->pos - pos_destine;
		p_m.y = 0.0f;
		float p_e_kyori = D3DXVec3Length(&p_m);
		Calculate* math = new Calculate();
		D3DXVECTOR3 zzz = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		float rot_destiney = math->Two_vector_angle(&p_m, &zzz);
		//math->Four_out_Five_in(range);
		delete math;
		if (player->pos.x > pos_destine.x  &&player->pos.z >= pos_destine.z)
		{
			//rot_destiney  = (-D3DX_PI)+abs(rot_destiney );
			rot_destiney = (-D3DX_PI / 2) - abs(rot_destiney);
		}
		else if (player->pos.x > pos_destine.x && player->pos.z < pos_destine.z)
		{
			rot_destiney = -abs(rot_destiney);
		}
		else if (player->pos.x < pos_destine.x&&player->pos.z >= pos_destine.z)
		{
			//rot_destiney  = D3DX_PI-abs(rot_destiney );
			rot_destiney = (D3DX_PI / 2) + abs(rot_destiney);
		}
		else if (player->pos.x < pos_destine.x&& player->pos.z < pos_destine.z)
		{
			rot_destiney = abs(rot_destiney);
		}
		else if (pos_destine.x == player->pos.x&&player->pos.z > pos_destine.z)
		{
			rot_destiney = D3DX_PI;
		}
		else if (player->pos.x > pos_destine.x&& player->pos.z < pos_destine.z)
		{
			rot_destiney = 0;
		}
		rot_destine.y = rot_destiney;
	}
	void Enemy::Get_Object(Renderer* g_renderer, Collider3D* g_collider, Stage_Game_map1* g_map1, Player* g_player, Sound* sound_g, int enemynum)
	{
		renderer = g_renderer;
		collider = g_collider;
		map1 = g_map1;
		player = g_player;
		enemy_num = enemynum;
		sound = sound_g;
		
	}
	void Enemy::GetOthercollider(Collider3D* stage, Collider3D* player)
	{
		player_collider = player;
		stage_collider = stage;
	}
	void Enemy::Get_Model(DX11_MODEL* body, DX11_MODEL* head, DX11_MODEL* leftarm_up, DX11_MODEL* leftarm_down, DX11_MODEL* lefthend, DX11_MODEL* rightarm_up, DX11_MODEL* leftfoot_up, DX11_MODEL* leftfoot_down, DX11_MODEL* leftfoot_sole, DX11_MODEL* discover)
	{

		enemy_model_body = body;
		enemy_model_head = head;
		enemy_model_leftarm_up = leftarm_up;
		enemy_model_leftarm_down = leftarm_down;
		enemy_model_lefthend = lefthend;
		enemy_model_rightarm_up = rightarm_up;
		enemy_model_leftfoot_up = leftfoot_up;
		enemy_model_leftfoot_down = leftfoot_down;
		enemy_model_leftfoot_sole = leftfoot_sole;
		enemy_model_discover = discover;
	}

}