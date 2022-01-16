#pragma once
#include "Main.h"
#include "Stage_Instruction.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sound.h"
#include "Input.h"
#include "Light.h"
namespace FIGHTING_GAME
{
#ifndef _PHASE_INSTRUCTION_H_
#define _PHASE_INSTRUCTION_H_
	class Phase_Instruction 
	{
	private:
		Stage_Instruction* stage;
		Renderer* renderer_i;
		Camera* camera_i;
		Sound* sound_i;
		Light* light_i;
		Input* input_i;
	public:
		Phase_Instruction(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera);
		HRESULT InitInstructionPhase();
		void Uninit_InstructionPhase();
		void Update_InstructionPhase();
		void Draw_InstructionPhase();
	};
#endif
}