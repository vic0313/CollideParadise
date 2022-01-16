#include "Phase_Fade.h"
namespace FIGHTING_GAME
{

	Phase_Fade::Phase_Fade(Renderer *renderer, Sound* sound)
	{
		fade_renderer = renderer;
		fade_sound= sound;

		g_TexturName_fade[0] = {"data/TEXTURE/fade_black.png"};
		ID3D11Device *pDevice = fade_renderer->GetDevice();

		//�e�N�X�`������
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


		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D_BASE) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		fade_renderer->GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer_fade);


		// �v���C���[�̏�����
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
		{// �t�F�[�h������
			if ( g_Fade == FADE_OUT)
			{// �t�F�[�h�A�E�g����
				 g_Color.a += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
				if ( g_Color.a >= 1.0f)
				{
					if (g_ModeNext == MODE_TITLE || g_ModeNext == MODE_GAME || g_ModeNext == MODE_RESULT)
					{
						// ���Ă���Ȃ�S���~�߂�
						fade_sound->StopSound();
					}
					
					
					

					// �t�F�[�h�C�������ɐ؂�ւ�
					 g_Color.a = 1.0f;
					this->SetFade(FADE_IN,  g_ModeNext);

					
					GameDate::ChangePhaseCheck = MODE_CHANGER_ALREADY;
				}

			}
			else if ( g_Fade == FADE_IN)
			{// �t�F�[�h�C������
				 g_Color.a -= FADE_RATE;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
				if ( g_Color.a <= 0.0f)
				{
					// �t�F�[�h�����I��
					 g_Color.a = 0.0f;
					this->SetFade(FADE_NONE,  g_ModeNext);
				}

			}
		}

#ifdef _DEBUG	// �f�o�b�O����\������
		//char *str = GetDebugStr();
		//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);

#endif
	}

	void Phase_Fade::Draw_FadePhase()
	{

	if ( g_Fade == FADE_NONE) return;	// �t�F�[�h���Ȃ��̂Ȃ�`�悵�Ȃ�

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
	// �t�F�[�h�̏�Ԑݒ�
	//=============================================================================
	void Phase_Fade::SetFade(FADE fade, MODE modeNext)
	{
		 g_Fade = fade;
		 g_ModeNext = modeNext;
	}

	

}