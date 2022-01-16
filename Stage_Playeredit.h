#include "Main.h"
#include "Stage.h"
#include "Renderer.h"
#include "Collider3D.h"
#include "Input.h"
namespace FIGHTING_GAME
{
	class Stage_Playeredit :Stage
	{
	private:
#define PLAYEREDIT_IMAGEMAX (10)
		Renderer* renderer_Playeredit;
		int move_timer;
		int move_timer2;
		bool move_check;
		int choice;
		bool check;
		Input* input;
		char* TextureName[PLAYEREDIT_IMAGEMAX];
		TwoDPlane_NOZ_data *Plane_NOZ_data;

	public:
		Stage_Playeredit(Renderer* renderer, Input* g_input);
		HRESULT InitStage() override;
		void UninitStage() override;
		void UpdateStage() override;
		void DrawStage() override;

	};

}