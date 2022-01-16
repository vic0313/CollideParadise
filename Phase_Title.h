#pragma once
#include "Main.h"
#include "Stage_Title.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sound.h"
#include "Input.h"
#include "Light.h"
namespace FIGHTING_GAME
{
#ifndef _PHASE_TITLE_H_
#define _PHASE_TITLE_H_
	class Phase_Title
	{
	private:
		Stage_Title* stage;

		Renderer* renderer_t;
		Camera* camera_t;
		Sound* sound_t;
		Light* light_t;
		Input* input_t;
		
	public:
		Phase_Title(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera);
		
		HRESULT InitTitlePhase();
		void Uninit_TitlePhase();
		void Update_TitlePhase();
		void Draw_TitlePhase();

	};
#endif
}