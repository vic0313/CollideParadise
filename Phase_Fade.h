#pragma once

#include "Main.h"
#include "Renderer.h"
#include "Sound.h"
#include "Main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

namespace FIGHTING_GAME
{
	class Phase_Fade
	{
	private:
		Renderer* fade_renderer;
		Sound* fade_sound;
	public:
		ID3D11Buffer				*g_VertexBuffer_fade;		// ���_���
		ID3D11ShaderResourceView	*g_Texture_fade[Fade_TEXTURE_MAX];	// �e�N�X�`�����
		char *g_TexturName_fade[FADE_FILE_MAX];
		bool					g_Use;						// true:�g���Ă���  false:���g�p
		float					g_w, g_h;					// ���ƍ���
		D3DXVECTOR3				g_Pos;						// �|���S���̍��W
		FADE					g_Fade = FADE_IN;			// �t�F�[�h�̏��
		MODE					g_ModeNext;					// ���̃��[�h
		D3DXCOLOR				g_Color;					// �t�F�[�h�̃J���[�i���l�j

		Phase_Fade(Renderer *renderer, Sound* sound);

		void Update_FadePhase();
		void Draw_FadePhase();
		void Uninit_FadePhase();

		void SetFade(FADE fade, MODE modeNext);
	};
	
}