#pragma once
#include "Main.h"
#include "Stage_Result.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sound.h"
#include "Input.h"
#include "Light.h"
namespace FIGHTING_GAME
{
#ifndef _PHASE_RESULT_H_
#define _PHASE_RESULT_H_
	class Phase_Result 
	{
	private:
		Stage_Result* stage;

		Renderer* renderer_r;
		Camera* camera_r;
		Sound* sound_r;
		Light* light_r;
		Input* input_r;
	public:

		Phase_Result(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* light_g, Camera* camera_g);
		HRESULT InitResultPhase();
		void Uninit_ResultPhase();
		void Update_ResultPhase();
		void Draw_ResultPhase();
	};
#endif
}