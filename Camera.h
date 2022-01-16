#pragma once
#include "Main.h"
#include "Renderer.h"
#include "Input.h"

namespace FIGHTING_GAME
{
#ifndef _CAMERA_H_
#define _CAMERA_H_
	class Camera
	{
	private:
#define	CAMERA_MOVE			(5.0f)
#define GAME_NORMAL_AT_LEN	(100.0f)
#define GAME_NORMAL_CAMERAPOS_Y	(200.0f)
#define GAME_NORMAL_POS_LEN	(300.0f)
#define GAME_NORMAL_ROT_CHANGE (D3DX_PI/40)
		Renderer* camera_renderer;
		Input* camera_input;
		
	public:
		D3DXVECTOR3			pos;			// �J�����̎��_(�ʒu)
		D3DXVECTOR3			at_pos;				// �J�����̒����_
		D3DXVECTOR3			at_pause;				// �J�����̒����_
		D3DXVECTOR3			playerpos;
		D3DXVECTOR3			rot;			// �J�����̉�]
		D3DXVECTOR3			playerrot;
		float			at_roty;			// �J�����̉�]
		float			at_rotxz;
		float			xyrot_MAX;
		float				len;			// �J�����̎��_�ƒ����_�̋���
		float				len_noy;			// �J�����̎��_�ƒ����_�̋���
		float				spd;
		D3DXMATRIX			mtxView;		// �r���[�}�g���b�N�X
		D3DXMATRIX			mtxInvView;		// �r���[�}�g���b�N�X
		D3DXMATRIX			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

		

		float mouse_move_x = 0.0f;								//�}�I�X�̈ړ��ʗp
		float  mouse_move_y = 0.0f;								//�}�I�X�̈ړ��ʗp
		int buffertime = 0;							//�����ŏ�K�̃v���O�����̓Q�[������Ȃ��̎��APAUSE�����s��BUFFERTIME
		int	g_ViewPortType = TYPE_FULL_SCREEN;
		

		

		Camera(Renderer* renderer, Input* input);
		void InitCamera();
		void UninitCamera(void);
		void UpdateCamera();

		void Camera_title(void);
		void Camera_instruction(void);
		void Camera_playeredit(void);
		void Camera_result(void);
		void Camera_game_normal(void);
		void Camera_game_camera_free(void);
		void Camera_game_lock_on(void);


		void SetCamera();

		void SetViewPort(int type);
		void SetPlayerDate(D3DXVECTOR3	player_pos, D3DXVECTOR3 player_rot);
	};

#endif
}