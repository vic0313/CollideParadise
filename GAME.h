#include "Main.h"

#include "Renderer.h"
#include "Phase_Game.h"
#include "Phase_Instruction.h"
#include "Phase_Playeredit.h"
#include "Phase_Result.h"
#include "Phase_Title.h"
#include "Phase_Fade.h"
#include "Input.h"
#include "Sound.h"
#include "Collider3D.h"
#include <vector>
#include <iostream>


namespace FIGHTING_GAME
{
#ifndef _GAME_H_
#define _GAME_H_
	class GAME
	{
	private:
		Phase_Fade* g_Fade;
		Phase_Game* g_Game;
		Phase_Instruction* g_Instruction;
		Phase_Playeredit* g_Playeredit;
		Phase_Result* g_Result;
		Phase_Title* g_Title;

		Renderer* renderer;
		Input* input;
		Sound* sound;
		Camera* camera;
		Light* light;
	public:
		
		//GAME(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		void Run(void);
		void Uninit(void);
		void ChangePhase(MODE GamePhase_now, MODE GamePhase_next);


	};

#endif
}


