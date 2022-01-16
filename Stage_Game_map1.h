#include "Main.h"
#include "Stage.h"
#include "Renderer.h"
#include "Collider3D.h"
namespace FIGHTING_GAME
{
#ifndef _STAGE_GAME_MAP1_
#define _STAGE_GAME_MAP1_

#define GAME_MAP1_MODELMAX (41)
#define GAMEMODEL_1 "data/MODEL/stage1_floor.obj"
#define GAMEMODEL_2 "data/MODEL/stage1_floor2.obj"
#define GAMEMODEL_3 "data/MODEL/stage1_Circle.obj"
#define GAMEMODEL_4 "data/MODEL/stage1_slope.obj"
#define GAMEMODEL_5 "data/MODEL/stage1_start.obj"
#define GAMEMODEL_6 "data/MODEL/stage1_ladder1.obj"
#define GAMEMODEL_7 "data/MODEL/stage1_floor3.obj"
#define GAMEMODEL_8 "data/MODEL/stage1_floor4.obj"
#define GAMEMODEL_9 "data/MODEL/stage1_ladder2.obj"
#define GAMEMODEL_10 "data/MODEL/stage1_floor5.obj"
#define GAMEMODEL_11 "data/MODEL/stage1_sand.obj"
#define GAMEMODEL_12 "data/MODEL/stage1_centre.obj"
#define GAMEMODEL_13 "data/MODEL/stage1_ladder2--2.obj"
#define GAMEMODEL_14 "data/MODEL/stage1_block.obj"
#define GAMEMODEL_15 "data/MODEL/sky.obj"
#define GAMEMODEL_16 "data/MODEL/star.obj"
	class Stage_Game_map1:Stage
	{
	private:
		Renderer* renderer_map1;
		Collider3D* map1_collider;
		
		int Collider_num;
		static char* Game_TextureName[];

		/*TwoDPlane_single_data *Plane_single_data;
		TwoDPlane_plural_data *Plane_plural_data[1];
		TwoDPlane_NOZ_data *Plane_NOZ_data;
		TwoDPlane_All2D_data *Plane_All2D_data;*/

		void SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl, Stage_Model_Num num);
		void SetCollider(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl);
		void Set2DPlane();
	public:
		int Model_num;
		ThreeDModel_data *Model_data;
		DX11_MODEL			model_1;				// モデル情報
		DX11_MODEL			model_2;				// モデル情報
		DX11_MODEL			model_3;				// モデル情報
		DX11_MODEL			model_4;				// モデル情報
		DX11_MODEL			model_5;				// モデル情報
		DX11_MODEL			model_6;				// モデル情報
		DX11_MODEL			model_7;				// モデル情報
		DX11_MODEL			model_8;				// モデル情報
		DX11_MODEL			model_9;				// モデル情報
		DX11_MODEL			model_10;				// モデル情報
		DX11_MODEL			model_11;				// モデル情報
		DX11_MODEL			model_12;				// モデル情報
		DX11_MODEL			model_13;				// モデル情報
		DX11_MODEL			model_14;				// モデル情報
		DX11_MODEL			model_15;				// モデル情報
		DX11_MODEL			model_16;				// モデル情報
		Stage_Game_map1(Renderer* renderer, Collider3D* collider);
		HRESULT InitStage() override;
		void UninitStage() override;
		void UpdateStage() override;
		void DrawStage() override;

		
	};
#endif
}