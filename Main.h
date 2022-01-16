#pragma once
#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#include <vector>
#include <iostream>

#pragma warning(pop)
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v


namespace FIGHTING_GAME
{
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)

// game pad�p�ݒ�l
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

	// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD										// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE											// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD												// �錾����ƃp�b�h�ő���\�ɂȂ�


/* game pad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g
//*****************************************************************************
// GAME�}�N����`
//*****************************************************************************

#define SCREEN_WIDTH	(960)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)			// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define FIELD_W			(3000.0f)			// �t�B�[���h�̍L��
#define FIELD_H			(3000.0f)			// �t�B�[���h�̍L��
#define FIELD_TOP		( FIELD_H/2)		// �t�B�[���h�̏�
#define FIELD_DOWN		(-FIELD_H/2)		// �t�B�[���h�̉�
#define FIELD_LEFT		(-FIELD_W/2)		// �t�B�[���h�̍�
#define FIELD_RIGHT		( FIELD_W/2)		// �t�B�[���h�̉E

#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"FIGHTING GAME"	// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// Light�}�N����`
//*****************************************************************************
#define LIGHT_MAX		(10)
//*****************************************************************************
// Model�}�N����`
//*****************************************************************************
//#define MODEL_FILENAME		"data/MODEL/miku_01.obj"
#define	VALUE_MOVE_MODEL	(0.50f)					// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)					// �ړ������W��
#define	VALUE_ROTATE_MODEL	(PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)					// ��]�����W��
#define	SCALE_MODEL			(10.0f)					// ��]�����W��
//*****************************************************************************
// Camera�}�N����`
//*****************************************************************************

#define	CameraPosX_MAX	(1490.0f)
#define	CameraPosX_MIN	(-1490.0f)
#define	CameraPosZ_MAX	(1490.0f)
#define	CameraPosZ_MIN	(-1490.0f)
#define	CameraPosY_MAX	(630.0f)
#define	CameraPosY_MIN	(50.0f)

#define	CameraAtPosY_MAX	(100.0f)
#define	CameraAtPosY_MIN	(1.0f)

#define LENMAX		(300.0f);
#define	LENMIN		(100.0f);

#define	VIEW_ANGLE		(D3DXToRadian(55.0f))							// �r���[���ʂ̎���p
	/*****/
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(80.0f)			// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(200.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(2.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

#define VALUE_MOVE_CAMERA_GAMEPDA_X (2.0f)
#define VALUE_MOVE_CAMERA_GAMEPDA_Y (2.0f)

//*****************************************************************************
// Fade�}�N����`
//*****************************************************************************
#define Fade_TEXTURE_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define Fade_TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define Fade_TEXTURE_MAX					(1)				// �e�N�X�`���̐�

#define	FADE_RATE					(0.02f)			// �t�F�[�h�W��
#define	FADE_FILE_MAX					(1)			// �t�F�[�h�W��


//*****************************************************************************
//�񝨒�`
//*****************************************************************************
	typedef enum
	{
		MODE_NO_CHANGE = 0,
		MODE_TITLE ,							// 1.�^�C�g�����
		MODE_INSTRUCTION,						// 2.�Q�[���������
		MODE_PLAYEREDIT,						// 3.�v���C���̕ҏW
		MODE_GAME,								// 4.�Q�[�����
		MODE_RESULT,							// 5.���U���g���
		MODE_CHANGER_ALREADY,
		MODE_MAX
	} MODE;
	typedef enum
	{
		FADE_NONE = 0,		// �����Ȃ����
		FADE_IN,			// �t�F�[�h�C������
		FADE_OUT,			// �t�F�[�h�A�E�g����
		FADE_MAX
	} FADE;
	enum LIGHT_TYPE
	{
		LIGHT_TYPE_NONE,		//���C�g����
		LIGHT_TYPE_DIRECTIONAL,	//�f�B���N�V���i�����C�g
		LIGHT_TYPE_POINT,		//�|�C���g���C�g

		LIGHT_TYPE_NUM
	};
	enum BLEND_MODE
	{
		BLEND_MODE_NONE,		//�u�����h����
		BLEND_MODE_ALPHABLEND,	//���u�����h
		BLEND_MODE_ADD,			//���Z�u�����h
		BLEND_MODE_SUBTRACT,	//���Z�u�����h

		BLEDD_MODE_NUM
	};
	enum CULL_MODE
	{
		CULL_MODE_NONE,			//�J�����O����
		CULL_MODE_FRONT,		//�\�̃|���S����`�悵�Ȃ�(CW)
		CULL_MODE_BACK,			//���̃|���S����`�悵�Ȃ�(CCW)

		CULL_MODE_NUM
	};
	enum
	{
		SOUND_LABEL_BGM_sample000,	// BGM0
		SOUND_LABEL_BGM_sample001,	// BGM1
		SOUND_LABEL_BGM_sample002,	// BGM2
		SOUND_LABEL_BGM_sample003,	// BGM2
		SOUND_LABEL_BGM_sample004,	// BGM2
		SOUND_LABEL_BGM_sample005,	// BGM2
		SOUND_LABEL_SE_bomb000,		// ������
		SOUND_LABEL_SE_defend000,	// 
		SOUND_LABEL_SE_defend001,	// 
		SOUND_LABEL_SE_hit000,		// 
		SOUND_LABEL_SE_laser000,	// 
		SOUND_LABEL_SE_lockon000,	// 
		SOUND_LABEL_SE_shot000,		// 
		SOUND_LABEL_SE_shot001,		// 
		SOUND_LABEL_MAX,
	};
	enum {
		TYPE_FULL_SCREEN,
		TYPE_LEFT_HALF_SCREEN,
		TYPE_RIGHT_HALF_SCREEN,
		TYPE_UP_HALF_SCREEN,
		TYPE_DOWN_HALF_SCREEN,
		TYPE_NONE,
	};
	
	typedef enum
	{
		GAMETYPE_NOSET = 0,		// �����Ȃ����
		GAMETYPE_ONE,
		GAMETYPE_MAX
	} GAMETYPE;
	enum Collider3DType
	{
		Collider3DType_box = 0,
	};
	enum Collider3D_Tag
	{
		collider3DTag_none = 0,
		Player_object,
		Player_Part_object,
		Player_Attack_object,
		Enemy_object,
		Enemy_Part_object,
		Stage_object,
		BigSwordWeapon_object,
		EnemyWeapon,
	};
	enum Game_Mode
	{
		normal = 0,
		camera_free,
		camera_lock_on,
		pasue,
	};
	enum Draw_Type
	{
		Draw_normal = 0,//MODEL   NO COLLIDER
		Draw_Both,//MODEL+COLLIDER
		Draw_ColliderOnly,
	};
	enum Stage_Model_Num
	{
		Num1 = 0,//MODEL   NO COLLIDER
		Num2,//MODEL+COLLIDER
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num10,
		Num11,
		Num12,
		Num13,
		Num14,
		Num15,
		Num16,
	};

	
//*****************************************************************************
//�N���X��`
//*****************************************************************************
	

	class GameDate
	{
	public:
		static MODE GamePhase_now;
		static MODE ChangePhaseCheck;
		static Draw_Type DrawType;
		static Game_Mode GameMode;
	};
	
	

	class INTERPOLATION_DATA_BASE
	{
	public:
		D3DXVECTOR3 pos;		// ���_���W
		D3DXVECTOR3 rot;		// ��]
		D3DXVECTOR3 scl;		// �g��k��
		float		frame;		// ���s�t���[���� ( dt = 1.0f/frame )
		int			Array_long;
	};
	//*****************************************************************************
	// Renderer�\����
	//*****************************************************************************
	// ���_�\����
	class VERTEX_3D_BASE
	{
	public:
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXCOLOR  Diffuse;
		D3DXVECTOR2 TexCoord;
	};
	//// �}�e���A���\����
	class MATERIAL_BASE
	{
	public:
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		int			noTexSampling;
	};
	// ���C�g�\����
	class LIGHT_BASE
	{
	public:
		D3DXVECTOR3 Direction;	// ���C�g�̕���
		D3DXVECTOR3 Position;	// ���C�g�̈ʒu
		D3DXCOLOR	Diffuse;	// �g�U���̐F
		D3DXCOLOR   Ambient;	// �����̐F
		float		Attenuation;// ������
		int			Type;		// ���C�g��ʁE�L���t���O
		int			Enable;		// ���C�g��ʁE�L���t���O
	};
	// �t�H�O�\����
	class FOG_BASE
	{
	public:
		float		FogStart;	// �t�H�O�̊J�n����
		float		FogEnd;		// �t�H�O�̍ő勗��
		D3DXCOLOR	FogColor;	// �t�H�O�̐F
	};
	// ���C�g�p�t���O�\����
	class LIGHTFLAGS_BASE
	{
	public:
		int			Type;		//���C�g�^�C�v�ienum LIGHT_TYPE�j
		int			Dummy[3];
	};
	// �}�e���A���p�萔�o�b�t�@�\����
	class MATERIAL_CBUFFER_BASE
	{
	public:
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		int			noTexSampling;
		float		Dummy[2];				// 16byte���E�p
	};
	// ���C�g�p�萔�o�b�t�@�\����
	class LIGHT_CBUFFER_BASE
	{
	public:
		D3DXVECTOR4 Direction[LIGHT_MAX];	// ���C�g�̕���
		D3DXVECTOR4 Position[LIGHT_MAX];	// ���C�g�̈ʒu
		D3DXCOLOR	Diffuse[LIGHT_MAX];		// �g�U���̐F
		D3DXCOLOR   Ambient[LIGHT_MAX];		// �����̐F
		D3DXVECTOR4	Attenuation[LIGHT_MAX];	// ������
		LIGHTFLAGS_BASE	Flags[LIGHT_MAX];		// ���C�g���
		int			Enable;					// ���C�e�B���O�L���E�����t���O
		int			Dummy[3];				// 16byte���E�p
	};
	// �t�H�O�p�萔�o�b�t�@�\����
	class FOG_CBUFFER_BASE
	{
	public:
		D3DXVECTOR4 Fog;					// �t�H�O��
		D3DXCOLOR	FogColor;				// �t�H�O�̐F
		int			Enable;					// �t�H�O�L���E�����t���O
		float		Dummy[3];				// 16byte���E�p
	};
	// �����p�o�b�t�@
	class FUCHI
	{
	public:
		int			fuchi;
		int			fill[3];
	};
	//*****************************************************************************
	// Model�\����
	//*****************************************************************************
	// �}�e���A���\����
	class DX11_MODEL_MATERIAL
	{
	public:
		MATERIAL_BASE					Material;
		ID3D11ShaderResourceView	*Texture;
	};
	// �`��T�u�Z�b�g�\����
	class DX11_SUBSET
	{
	public:
		unsigned short	StartIndex;
		unsigned short	IndexNum;
		DX11_MODEL_MATERIAL	Material;
	};
	class DX11_MODEL
	{
	public:
		ID3D11Buffer*	VertexBuffer;
		ID3D11Buffer*	IndexBuffer;

		DX11_SUBSET		*SubsetArray;
		unsigned short	SubsetNum;

		// Mesh collider
		D3DXVECTOR3     *Vertexlist; // store vertex position
		unsigned short  *Indexlist;  // store index data
		unsigned short	VertexNum;
		unsigned short	IndexNum;
	};
	// �}�e���A���\����
	class MODEL_MATERIAL
	{
	public:
		char						Name[256];
		MATERIAL_BASE					Material;
		char						TextureName[256];
	};
	// �`��T�u�Z�b�g�\����
	class SUBSET
	{
	public:
		unsigned short	StartIndex;
		unsigned short	IndexNum;
		MODEL_MATERIAL	Material;
	};
	// ���f���\����
	class MODEL
	{
	public:
		VERTEX_3D_BASE	*VertexArray;
		unsigned short	VertexNum;
		unsigned short	*IndexArray;
		unsigned short	IndexNum;
		SUBSET			*SubsetArray;
		unsigned short	SubsetNum;
		unsigned short	 PointNum;
	};

	
	

	
	
	
}
	