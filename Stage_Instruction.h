#include "Main.h"
#include "Stage.h"
#include "Renderer.h"
#include "Collider3D.h"
#include "Input.h"
namespace FIGHTING_GAME
{
	class Stage_Instruction :Stage
	{
	private:
#define INSTRUCTION_IMAGEMAX (6)
		Renderer* renderer_Instruction;
		//int Model_num;
		char* TextureName[INSTRUCTION_IMAGEMAX];
		int choice;
		
		TwoDPlane_NOZ_data *Plane_NOZ_data;
		Input* input;

		void SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl);
		void Set2DPlane();
	public:
		Stage_Instruction(Renderer* renderer,Input* g_input);
		HRESULT InitStage() override;
		void UninitStage() override;
		void UpdateStage() override;
		void DrawStage() override;

	};

}