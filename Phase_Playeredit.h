#pragma once
#include "Main.h"
#include "Stage_Playeredit.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sound.h"
#include "Input.h"
#include "Light.h"
namespace FIGHTING_GAME
{
#ifndef _PHASE_EDIT_H_
#define _PHASE_EDIT_H_
	class Phase_Playeredit
	{
	private:
		Stage_Playeredit* stage;
		Renderer* renderer_p;
		Camera* camera_p;
		Sound* sound_p;
		Light* light_p;
		Input* input_p;

	public:
		Phase_Playeredit(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera);
		HRESULT InitPlayereditPhase();
		void Uninit_PlayereditPhase();
		void Update_PlayereditPhase();
		void Draw_PlayereditPhase();
	};
#endif
}