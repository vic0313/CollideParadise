#include "Light.h"
namespace FIGHTING_GAME
{
	Light::Light(Renderer* renderer)
	{
		light_renderer = renderer;
		
	}
	HRESULT Light::InitLight()
	{
		//light_Light[LIGHT_MAX] = LIGHT_BASE[LIGHT_MAX]();
		//fog_Light = new FOG_BASE();

		//ライト初期化
		for (int i = 1; i < LIGHT_MAX; i++)
		{

			light_Light[i].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			light_Light[i].Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			light_Light[i].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			light_Light[i].Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			light_Light[i].Attenuation = 1000.0f;	// 減衰距離
			light_Light[i].Type = LIGHT_TYPE_NONE;	// ライトのタイプ
			light_Light[i].Enable = false;			// ON / OFF
			light_renderer->SetLight(i, &light_Light[i]);
		}

		//並行光源の設定(世界を照えらす光)
		light_Light[0].Direction = D3DXVECTOR3(0.5f, -0.5f, 0.0f);		//光の向き
		light_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//光の色
		light_Light[0].Type = LIGHT_TYPE_DIRECTIONAL;					//並行光源
		light_Light[0].Enable = true;									//このライトをON
		light_renderer->SetLight(0, &light_Light[0]);									//これで設定している


		// フォグの初期化(霧の効果)
		fog_Light.FogStart = 30.0f;								//視点からこの距離離れるとフォグがかかり始める
		fog_Light.FogEnd = 1000.0f;									//ここまで離れるとフォグの色で見えなくなる
		fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
		light_renderer->SetFog(&fog_Light);
		light_renderer->SetFogEnable(false);
		return S_OK;
	}
	void Light::UpdateLight()
	{
		
		//LIGHT_BASE* LIGHT = new LIGHT_BASE[LIGHT_MAX];
		//FOG_BASE* FOG = new FOG_BASE();
		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
		{
			// フォグの初期化(霧の効果)
			fog_Light.FogStart = 500.0f;								//視点からこの距離離れるとフォグがかかり始める
			fog_Light.FogEnd = 1000.0f;									//ここまで離れるとフォグの色で見えなくなる
			fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
			light_renderer->SetFog(&fog_Light);
			light_renderer->SetFogEnable(false);
		}
		break;
		case MODE_INSTRUCTION:
		{
			// フォグの初期化(霧の効果)
			fog_Light.FogStart = 500.0f;								//視点からこの距離離れるとフォグがかかり始める
			fog_Light.FogEnd = 1000.0f;									//ここまで離れるとフォグの色で見えなくなる
			fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
			light_renderer->SetFog(&fog_Light);
			light_renderer->SetFogEnable(false);
		}
		break;
		case MODE_PLAYEREDIT:
		{
				// フォグの初期化(霧の効果)
				fog_Light.FogStart = 5000.0f;								//視点からこの距離離れるとフォグがかかり始める
				fog_Light.FogEnd = 5000.0f;									//ここまで離れるとフォグの色で見えなくなる
				fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
				light_renderer->SetFog(&fog_Light);
				light_renderer->SetFogEnable(false);
			

		}
		break;
		case MODE_GAME:
		{
			// フォグの初期化(霧の効果)
			fog_Light.FogStart = 30.0f;								//視点からこの距離離れるとフォグがかかり始める
			fog_Light.FogEnd = 1500.0f;									//ここまで離れるとフォグの色で見えなくなる
			fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
			light_renderer->SetFog(&fog_Light);
			light_renderer->SetFogEnable(true);
		}
		break;
		case MODE_RESULT:
		{
			// フォグの初期化(霧の効果)
			fog_Light.FogStart = 30.0f;								//視点からこの距離離れるとフォグがかかり始める
			fog_Light.FogEnd = 300.0f;									//ここまで離れるとフォグの色で見えなくなる
			fog_Light.FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//フォグの色
			light_renderer->SetFog(&fog_Light);
			light_renderer->SetFogEnable(false);
		}
		break;

		default:
			break;
		}

	}

	void Light::SetLightData(int index, LIGHT_BASE* LIGHT_BASE)
	{
		
		light_renderer->SetLight(index, LIGHT_BASE);
	}
	void Light::SetFogData( FOG_BASE* FOG_BASE)
	{
		light_renderer->SetFog(FOG_BASE);
	}

	//LIGHT Light::*GetLightData(int index)
	//{
	//	return(&g_light_Light[index]);
	//}
}