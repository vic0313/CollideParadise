#include "Phase_Instruction.h"
namespace FIGHTING_GAME
{

	Phase_Instruction::Phase_Instruction(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera)
	{
		renderer_i = g_renderer;
		sound_i = g_sound;
		input_i = g_input;
		light_i = g_light;
		camera_i = g_camera;
		

		
	}
	HRESULT Phase_Instruction::InitInstructionPhase()
	{
		renderer_i->SetLightEnable(true);
		renderer_i->SetCullingMode(CULL_MODE_BACK);
		
		stage = new Stage_Instruction(renderer_i, input_i);
		stage->InitStage();
		camera_i->g_ViewPortType = TYPE_FULL_SCREEN;
		camera_i->InitCamera();
		//sound_i->PlaySound(SOUND_LABEL_BGM_sample000);

		return S_OK;
	}
	void Phase_Instruction::Update_InstructionPhase()
	{
		light_i->UpdateLight();
		stage->UpdateStage();
		if (input_i->GetKeyboardTrigger(DIK_RETURN))
		{
			GameDate::ChangePhaseCheck = MODE_GAME;
		}
	}
	void Phase_Instruction::Draw_InstructionPhase()
	{
		//STAGEの描画
		stage->DrawStage();
		//プレイヤの描画
		//エネミーの描画
		//パーティクルの描画
		//UIの描画
		
	}
	void Phase_Instruction::Uninit_InstructionPhase()
	{
		stage->UninitStage();
		delete stage;
	}
}