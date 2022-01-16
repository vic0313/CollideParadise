#include "Phase_Fade.h"
namespace FIGHTING_GAME
{

	Phase_Fade::Phase_Fade(Renderer *renderer, Sound* sound)
	{
		fade_renderer = renderer;
		fade_sound= sound;

		g_TexturName_fade[0] = {"data/TEXTURE/fade_black.png"};
		ID3D11Device *pDevice = fade_renderer->GetDevice();

		//テクスチャ生成
		for (int i = 0; i < Fade_TEXTURE_MAX; i++)
		{
			g_Texture_fade[i] = NULL;
			D3DX11CreateShaderResourceViewFromFile(fade_renderer->GetDevice(),
				g_TexturName_fade[i],
				NULL,
				NULL,
				&g_Texture_fade[i],
				NULL);
		}


		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D_BASE) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		fade_renderer->GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer_fade);


		// プレイヤーの初期化
		g_Use = true;
		g_w = Fade_TEXTURE_WIDTH;
		g_h = Fade_TEXTURE_HEIGHT;
		g_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Fade = FADE_IN;
		g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	}
	

	void Phase_Fade::Update_FadePhase()
	{
		
		if ( g_Fade != FADE_NONE)
		{// フェード処理中
			if ( g_Fade == FADE_OUT)
			{// フェードアウト処理
				 g_Color.a += FADE_RATE;		// α値を加算して画面を消していく
				if ( g_Color.a >= 1.0f)
				{
					if (g_ModeNext == MODE_TITLE || g_ModeNext == MODE_GAME || g_ModeNext == MODE_RESULT)
					{
						// 鳴っている曲を全部止める
						fade_sound->StopSound();
					}
					
					
					

					// フェードイン処理に切り替え
					 g_Color.a = 1.0f;
					this->SetFade(FADE_IN,  g_ModeNext);

					
					GameDate::ChangePhaseCheck = MODE_CHANGER_ALREADY;
				}

			}
			else if ( g_Fade == FADE_IN)
			{// フェードイン処理
				 g_Color.a -= FADE_RATE;		// α値を減算して画面を浮き上がらせる
				if ( g_Color.a <= 0.0f)
				{
					// フェード処理終了
					 g_Color.a = 0.0f;
					this->SetFade(FADE_NONE,  g_ModeNext);
				}

			}
		}

#ifdef _DEBUG	// デバッグ情報を表示する
		//char *str = GetDebugStr();
		//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);

#endif
	}

	void Phase_Fade::Draw_FadePhase()
	{

	if ( g_Fade == FADE_NONE) return;	// フェードしないのなら描画しない

	fade_renderer->Draw_2DPlane_NOZ(g_VertexBuffer_fade, g_Texture_fade[0], (g_w/2), (g_h/2), g_w, g_h, 0.0f, 0.0f, 1.0f, 1.0f,g_Color);

	}
	void Phase_Fade::Uninit_FadePhase()
	{
		if ( g_VertexBuffer_fade)
		{
			 g_VertexBuffer_fade->Release();
			 g_VertexBuffer_fade = NULL;
		}

		for (int i = 0; i < Fade_TEXTURE_MAX; i++)
		{
			if ( g_Texture_fade[i])
			{
				 g_Texture_fade[i]->Release();
				 g_Texture_fade[i] = NULL;
			}
		}
	}

	//=============================================================================
	// フェードの状態設定
	//=============================================================================
	void Phase_Fade::SetFade(FADE fade, MODE modeNext)
	{
		 g_Fade = fade;
		 g_ModeNext = modeNext;
	}

	

}