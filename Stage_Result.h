#include "Main.h"
#include "Stage.h"
#include "Renderer.h"
#include "Collider3D.h"
namespace FIGHTING_GAME
{
	class Stage_Result :Stage
	{
	private:
#define RESULT_MODELMAX (1)
#define RESULT_IMAGEMAX (1)
		Renderer* renderer_Result;
		int Model_num;


		char* TextureName[RESULT_IMAGEMAX];
		//ThreeDModel_data *Model_data[RESULT_MODELMAX];
		//TwoDPlane_single_data *Plane_single_data;
		//TwoDPlane_plural_data *Plane_plural_data[1];
		TwoDPlane_NOZ_data *Plane_NOZ_data;
		//TwoDPlane_All2D_data *Plane_All2D_data;

		void SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl);
		void Set2DPlane();
	public:
		Stage_Result(Renderer* renderer);
		HRESULT InitStage() override;
		void UninitStage() override;
		void UpdateStage() override;
		void DrawStage() override;

	};

}