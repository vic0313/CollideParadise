#pragma once
#include "Main.h"
#include "Renderer.h"
#include "Collider3D.h"
#include "Calculate.h"
namespace FIGHTING_GAME
{
#ifndef _WEAPON_H_
#define _WEAPON_H_
#define BIGSWORD			"data/MODEL/bigsword.obj"
#define ENEMY_WEAPON		"data/MODEL/enemy_weapon.obj"
	enum Weapon_type
	{
		bigsword = 0,
		enemy_weapon,
		weaponobj_load,
	};
	class Weapon
	{
	private:
		int weapon_type_num;
		Renderer* renderer;
	public:
		Collider3D* collider;
		D3DXVECTOR3				pos;
		D3DXVECTOR3				rot;
		D3DXVECTOR3				scl;
		float					move_time;			// 実行時間
		float					move_time_next;			// 実行時間
		D3DXVECTOR3				collider_wxhylz;
		int*					collider_index;
		DX11_MODEL				model;				// モデル情報
		DX11_MODEL*			model_repeat;
		D3DXMATRIX				mtxWorld;			// ワールドマトリックス
		Weapon( Renderer* g_renderer);
		HRESULT InitWeapon(Weapon_type weapon_type);
		void UninitWeapon(int num);
		void UpdateWeapon(void);
		void DrawWeapon(void);
		void Update_Pos(D3DXVECTOR3 g_pos, D3DXVECTOR3 g_rot);
		void Update_Scl(D3DXVECTOR3 g_scl);
		void Update_Collider(void);
		void Get_Model(DX11_MODEL* weapon);
	};
#endif
}

