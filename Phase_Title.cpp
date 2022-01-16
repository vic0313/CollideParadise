#include "Phase_Title.h"
namespace FIGHTING_GAME
{

	Phase_Title::Phase_Title(Renderer* g_renderer, Input* g_input, Sound* g_sound, Light* g_light, Camera* g_camera)
	{
		renderer_t = g_renderer;
		sound_t = g_sound;
		input_t = g_input;
		light_t = g_light;
		camera_t = g_camera;
	}
	HRESULT Phase_Title::InitTitlePhase()
	{
		renderer_t->SetLightEnable(true);
		renderer_t->SetCullingMode(CULL_MODE_BACK);
		stage = new Stage_Title(renderer_t);
		stage->InitStage();
		camera_t->g_ViewPortType = TYPE_FULL_SCREEN;
		camera_t->InitCamera();

		sound_t->PlaySound(SOUND_LABEL_BGM_sample000);
		return S_OK;
	}
	void Phase_Title::Update_TitlePhase()
	{
		light_t->UpdateLight();
		stage->UpdateStage();
		camera_t->UpdateCamera();
		if (input_t->GetKeyboardTrigger(DIK_RETURN))
		{
			GameDate::ChangePhaseCheck = MODE_PLAYEREDIT;
		}
	}
	void Phase_Title::Draw_TitlePhase()
	{
		//STAGEの描画
		stage->DrawStage();
		//プレイヤの描画
		
		//エネミーの描画
		//パーティクルの描画
		//UIの描画
	}
	void Phase_Title::Uninit_TitlePhase()
	{
		stage->UninitStage();
		delete stage;
	}

	
}