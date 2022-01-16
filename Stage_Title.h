#include "Main.h"
#include "Stage.h"
#include "Renderer.h"
#include "Collider3D.h"
namespace FIGHTING_GAME
{
	class Stage_Title:Stage
	{
	private:
#define TITLE_MODELMAX (1)
#define TITLE_IMAGEMAX (4)
#define TITLE_MOVEMAX (100)
#define MODEL_head			"data/MODEL/player_head_nobody.obj"
		Renderer* renderer_title;
		int Model_num;
		int move_timer;

		char* TextureName[TITLE_IMAGEMAX];
		ThreeDModel_data *Model_data;
		//TwoDPlane_single_data *Plane_single_data;
		//TwoDPlane_plural_data *Plane_plural_data;
		TwoDPlane_NOZ_data *Plane_NOZ_data;
		//TwoDPlane_All2D_data *Plane_All2D_data;

		void SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl);
		void Set2DPlane();
	public:
		DX11_MODEL			model_1;				// ÉÇÉfÉãèÓïÒ
		Stage_Title(Renderer* renderer);
		HRESULT InitStage() override;
		void UninitStage() override;
		void UpdateStage() override;
		void DrawStage() override;

	};

}