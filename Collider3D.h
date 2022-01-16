#pragma once
#include "Main.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "Calculate.h"
namespace FIGHTING_GAME
{

#define PLAYERCOLLIDER_MAX (21)
#define ENEMY_COLLIDER3D_MAX (294)
#define ATTACK_COLLIDER3D_MAX (2)
#define STAGE_COLLIDER3D_MAX (80)
#define BIGSWORD_COLLIDER3D_MAX (1)
#define ENEMYWEAPON_COLLIDER3D_MAX (1)
#define COLLIDER3D_RENDER_CIRCLE_POLYNUM (26)
#define COLLIDER3D_RENDER_SIZE (0.5f)
	
#ifndef _COLLIDER_H_
#define _COLLIDER_H_
	class COLLIDER3D
	{
	public:
		MATERIAL_BASE	material;
		D3DXMATRIX		mtxWorld;					// ワールドマトリックス
		D3DXVECTOR3			pos;
		D3DXVECTOR3			rot;				// モデルの向き(回転)
		D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
		bool				Use;
		Collider3DType		type;
		Collider3D_Tag		tag;
		float				wx;
		float				hy;
		float				lz;
		float				r;
		D3DXVECTOR3			normalDirect[3];
		bool				isCollision;
		bool				draw_check;
		int					modeltype;
	};

	class Collider3D
	{
	private:
		Calculate* math;

		Renderer* collider_renderer;
		Input* collider_input;
		Camera* collider_camera;
		ID3D11Buffer					*g_VertexBuffer;	             // 頂点情報
		ID3D11Buffer					*g_VertexBuffercircle;	     // 円頂点情報
		ID3D11ShaderResourceView		*g_Texture;	 // テクスチャ情報
		int							Collidernum;
		char* g_TextureName;
	public:
		int							ColliderMax;
		COLLIDER3D				    *g_Collider3D;	     // colliderワーク
		Collider3D(Renderer* renderer,Collider3D_Tag tag);
		HRESULT InitCollider3D();
		void UninitCollider3D(void);
		void UpdateCollider3D(void);
		void DrawCollider3D(void);

		

		int CreateCollider3DBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float wx, float hy, float lz, Collider3DType type, Collider3D_Tag tag);
		HRESULT MakeVertexCollider3D(void);
		void SetCollider3D(int Collidernum, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
		void SetCollider3D_scl(int Collidernum, D3DXVECTOR3 scl);
		void SetCollider3D_use(int Collidernum, bool use);

		
		bool CheckHitOBB(COLLIDER3D *col_1, COLLIDER3D *col_2);
		FLOAT LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);
		bool RayCast(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 * hit, D3DXVECTOR3 *normal);
		bool RayCast_Top(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 * hit, D3DXVECTOR3 *normal);

		bool RayHitGround(D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL	model, float start_UP);
		bool RayHitTop(D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL	model);
		bool RayHitWall(D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL	model, D3DXVECTOR3 move_way);
	};

#endif
}