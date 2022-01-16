#include "Weapon.h"
namespace FIGHTING_GAME
{
	Weapon::Weapon( Renderer* g_renderer)
	{
		renderer = g_renderer;
	}
	HRESULT Weapon::InitWeapon(Weapon_type weapon_type)
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scl = D3DXVECTOR3(1.0f, 1.0f, 1.5f);
		weapon_type_num = weapon_type;
		switch (weapon_type)
		{
		case bigsword:
			collider_wxhylz = D3DXVECTOR3(5.0f, 10.0f, 78.0f); //player‚ÌPOS‚ð§Œä‚Ìcollider
			renderer->LoadModel(BIGSWORD, &model);
			collider = new Collider3D(renderer, BigSwordWeapon_object);
			collider->InitCollider3D();
			collider_index = new int[0];
			collider_index[0] = collider->CreateCollider3DBox(pos, rot, collider_wxhylz.x, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, BigSwordWeapon_object);
			break;
		case enemy_weapon:

			collider_wxhylz = D3DXVECTOR3(20.0f, 10.0f, 38.0f); //player‚ÌPOS‚ð§Œä‚Ìcollider
			renderer->LoadModel(ENEMY_WEAPON, &model);
			collider = new Collider3D(renderer, EnemyWeapon);
			collider->InitCollider3D();
			collider_index = new int[0];
			collider_index[0] = collider->CreateCollider3DBox(pos, rot, collider_wxhylz.x, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, EnemyWeapon);
			
			break;
		case weaponobj_load:
			collider_wxhylz = D3DXVECTOR3(20.0f, 10.0f, 38.0f); //player‚ÌPOS‚ð§Œä‚Ìcollider
			collider = new Collider3D(renderer, EnemyWeapon);
			collider->InitCollider3D();
			collider_index = new int[0];
			collider_index[0] = collider->CreateCollider3DBox(pos, rot, collider_wxhylz.x, collider_wxhylz.y, collider_wxhylz.z, Collider3DType_box, EnemyWeapon);

			break;
		}
		
		return S_OK;
	}
	void Weapon::UninitWeapon(int num)
	{
		if (num == 0)
		{
			renderer->UnloadModel(&model);
		}
		delete collider_index;
		delete collider;
		
	}
	void Weapon::UpdateWeapon(void)
	{
		
		
		
		
	}
	void Weapon::DrawWeapon(void)
	{
		if (GameDate::DrawType != Draw_ColliderOnly )
		{
			if (weapon_type_num == weaponobj_load)
			{
				renderer->Draw_3DModel_Part(mtxWorld, scl, rot, pos, model_repeat);
			}
			else
			{
				renderer->Draw_3DModel(mtxWorld, scl, rot, pos, model, false, 0);
			}
		}
		
		if (GameDate::DrawType == Draw_ColliderOnly || GameDate::DrawType == Draw_Both)
		{
			collider->DrawCollider3D();
		}
	}
	void Weapon::Update_Pos(D3DXVECTOR3 g_pos, D3DXVECTOR3 g_rot)
	{
		pos = g_pos;
		rot = g_rot;
	}

	void Weapon::Update_Scl(D3DXVECTOR3 g_scl)
	{
		D3DXVECTOR3 scl_g = g_scl;
		collider->SetCollider3D_scl(collider_index[0], scl_g);
	}
	void Weapon::Update_Collider()
	{
		D3DXVECTOR3	pos_collider = pos;
		float len = (collider_wxhylz.z / 2);
		float rr = abs(len * cosf(rot.x));
		pos_collider.y += len * sinf(rot.x);
		if (abs(rot.x) > (D3DX_PI / 2))
		{
			pos_collider.x += (rr)* sinf(rot.y);
			pos_collider.z += (rr)* cosf(rot.y);
		}
		else
		{
			pos_collider.x -= (rr)* sinf(rot.y);
			pos_collider.z -= (rr)* cosf(rot.y);
		}

		collider->SetCollider3D(collider_index[0], pos_collider, rot);
	}

	void Weapon::Get_Model(DX11_MODEL* weapon)
	{
		model_repeat = weapon;
	}
}