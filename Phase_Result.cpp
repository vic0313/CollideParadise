#include "Phase_Result.h"
namespace FIGHTING_GAME
{

	Phase_Result::Phase_Result(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera)
	{
		renderer_r = g_renderer;
		sound_r = g_sound;
		input_r = g_input;
		light_r = g_light;
		camera_r = g_camera;
	}
	HRESULT Phase_Result::InitResultPhase()
	{
		renderer_r->SetLightEnable(true);
		renderer_r->SetCullingMode(CULL_MODE_BACK);
		stage = new Stage_Result(renderer_r);
		stage->InitStage();
		camera_r->g_ViewPortType = TYPE_FULL_SCREEN;
		camera_r->InitCamera();
		sound_r->PlaySound(SOUND_LABEL_BGM_sample005);
		return S_OK;
	}
	void Phase_Result::Update_ResultPhase()
	{
		light_r->UpdateLight();
		stage->UpdateStage();
		if (input_r->GetKeyboardTrigger(DIK_RETURN))
		{
			GameDate::ChangePhaseCheck = MODE_PLAYEREDIT;
		}
	}
	void Phase_Result::Draw_ResultPhase()
	{
		//STAGEの描画
		stage->DrawStage();
		//プレイヤの描画
		//エネミーの描画
		//パーティクルの描画
		//UIの描画
	}
	void Phase_Result::Uninit_ResultPhase()
	{
		stage->UninitStage();
		delete stage;
	}
}