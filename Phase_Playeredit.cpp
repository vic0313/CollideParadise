#include "Phase_Playeredit.h"
namespace FIGHTING_GAME
{

	Phase_Playeredit::Phase_Playeredit(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera)
	{
		renderer_p = g_renderer;
		sound_p = g_sound;
		input_p = g_input;
		light_p = g_light;
		camera_p = g_camera;

		
		
	}
	HRESULT Phase_Playeredit::InitPlayereditPhase()
	{
		renderer_p->SetLightEnable(true);
		renderer_p->SetCullingMode(CULL_MODE_BACK);
		stage = new Stage_Playeredit(renderer_p, input_p);
		stage->InitStage();
		camera_p->g_ViewPortType = TYPE_FULL_SCREEN;
		camera_p->InitCamera();

		//sound_p->PlaySound(SOUND_LABEL_BGM_sample000);
		return S_OK;
	}
	void Phase_Playeredit::Update_PlayereditPhase()
	{
		light_p->UpdateLight();
		stage->UpdateStage();
	}
	void Phase_Playeredit::Draw_PlayereditPhase()
	{
		//STAGEの描画
		stage->DrawStage();
		//プレイヤの描画
		//エネミーの描画
		//パーティクルの描画
		//UIの描画
	}
	void Phase_Playeredit::Uninit_PlayereditPhase()
	{
		stage->UninitStage();
		delete stage;
	}
}