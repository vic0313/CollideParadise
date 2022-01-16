#pragma once

#include "Main.h"
#include "Renderer.h"
#include "Sound.h"
#include "Main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

namespace FIGHTING_GAME
{
	class Phase_Fade
	{
	private:
		Renderer* fade_renderer;
		Sound* fade_sound;
	public:
		ID3D11Buffer				*g_VertexBuffer_fade;		// 頂点情報
		ID3D11ShaderResourceView	*g_Texture_fade[Fade_TEXTURE_MAX];	// テクスチャ情報
		char *g_TexturName_fade[FADE_FILE_MAX];
		bool					g_Use;						// true:使っている  false:未使用
		float					g_w, g_h;					// 幅と高さ
		D3DXVECTOR3				g_Pos;						// ポリゴンの座標
		FADE					g_Fade = FADE_IN;			// フェードの状態
		MODE					g_ModeNext;					// 次のモード
		D3DXCOLOR				g_Color;					// フェードのカラー（α値）

		Phase_Fade(Renderer *renderer, Sound* sound);

		void Update_FadePhase();
		void Draw_FadePhase();
		void Uninit_FadePhase();

		void SetFade(FADE fade, MODE modeNext);
	};
	
}