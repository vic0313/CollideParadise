#pragma once
#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#include <vector>
#include <iostream>

#pragma warning(pop)
//*****************************************************************************
// ライブラリのリンク
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
#include "xaudio2.h"						// サウンド処理で必要


namespace FIGHTING_GAME
{
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)

// game pad用設定値
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

	// プログラム分けするときに使う
#define	USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE											// 宣言するとマウスで操作可能になる
#define	USE_PAD												// 宣言するとパッドで操作可能になる


/* game pad情報 */
#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット
//*****************************************************************************
// GAMEマクロ定義
//*****************************************************************************

#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標

#define FIELD_W			(3000.0f)			// フィールドの広さ
#define FIELD_H			(3000.0f)			// フィールドの広さ
#define FIELD_TOP		( FIELD_H/2)		// フィールドの上
#define FIELD_DOWN		(-FIELD_H/2)		// フィールドの下
#define FIELD_LEFT		(-FIELD_W/2)		// フィールドの左
#define FIELD_RIGHT		( FIELD_W/2)		// フィールドの右

#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"FIGHTING GAME"	// ウインドウのキャプション名
//*****************************************************************************
// Lightマクロ定義
//*****************************************************************************
#define LIGHT_MAX		(10)
//*****************************************************************************
// Modelマクロ定義
//*****************************************************************************
//#define MODEL_FILENAME		"data/MODEL/miku_01.obj"
#define	VALUE_MOVE_MODEL	(0.50f)					// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)					// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)					// 回転慣性係数
#define	SCALE_MODEL			(10.0f)					// 回転慣性係数
//*****************************************************************************
// Cameraマクロ定義
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

#define	VIEW_ANGLE		(D3DXToRadian(55.0f))							// ビュー平面の視野角
	/*****/
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(80.0f)			// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(200.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

#define VALUE_MOVE_CAMERA_GAMEPDA_X (2.0f)
#define VALUE_MOVE_CAMERA_GAMEPDA_Y (2.0f)

//*****************************************************************************
// Fadeマクロ定義
//*****************************************************************************
#define Fade_TEXTURE_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define Fade_TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define Fade_TEXTURE_MAX					(1)				// テクスチャの数

#define	FADE_RATE					(0.02f)			// フェード係数
#define	FADE_FILE_MAX					(1)			// フェード係数


//*****************************************************************************
//列舉定義
//*****************************************************************************
	typedef enum
	{
		MODE_NO_CHANGE = 0,
		MODE_TITLE ,							// 1.タイトル画面
		MODE_INSTRUCTION,						// 2.ゲーム説明画面
		MODE_PLAYEREDIT,						// 3.プレイヤの編集
		MODE_GAME,								// 4.ゲーム画面
		MODE_RESULT,							// 5.リザルト画面
		MODE_CHANGER_ALREADY,
		MODE_MAX
	} MODE;
	typedef enum
	{
		FADE_NONE = 0,		// 何もない状態
		FADE_IN,			// フェードイン処理
		FADE_OUT,			// フェードアウト処理
		FADE_MAX
	} FADE;
	enum LIGHT_TYPE
	{
		LIGHT_TYPE_NONE,		//ライト無し
		LIGHT_TYPE_DIRECTIONAL,	//ディレクショナルライト
		LIGHT_TYPE_POINT,		//ポイントライト

		LIGHT_TYPE_NUM
	};
	enum BLEND_MODE
	{
		BLEND_MODE_NONE,		//ブレンド無し
		BLEND_MODE_ALPHABLEND,	//αブレンド
		BLEND_MODE_ADD,			//加算ブレンド
		BLEND_MODE_SUBTRACT,	//減算ブレンド

		BLEDD_MODE_NUM
	};
	enum CULL_MODE
	{
		CULL_MODE_NONE,			//カリング無し
		CULL_MODE_FRONT,		//表のポリゴンを描画しない(CW)
		CULL_MODE_BACK,			//裏のポリゴンを描画しない(CCW)

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
		SOUND_LABEL_SE_bomb000,		// 爆発音
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
		GAMETYPE_NOSET = 0,		// 何もない状態
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
//クラス定義
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
		D3DXVECTOR3 pos;		// 頂点座標
		D3DXVECTOR3 rot;		// 回転
		D3DXVECTOR3 scl;		// 拡大縮小
		float		frame;		// 実行フレーム数 ( dt = 1.0f/frame )
		int			Array_long;
	};
	//*****************************************************************************
	// Renderer構造体
	//*****************************************************************************
	// 頂点構造体
	class VERTEX_3D_BASE
	{
	public:
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXCOLOR  Diffuse;
		D3DXVECTOR2 TexCoord;
	};
	//// マテリアル構造体
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
	// ライト構造体
	class LIGHT_BASE
	{
	public:
		D3DXVECTOR3 Direction;	// ライトの方向
		D3DXVECTOR3 Position;	// ライトの位置
		D3DXCOLOR	Diffuse;	// 拡散光の色
		D3DXCOLOR   Ambient;	// 環境光の色
		float		Attenuation;// 減衰率
		int			Type;		// ライト種別・有効フラグ
		int			Enable;		// ライト種別・有効フラグ
	};
	// フォグ構造体
	class FOG_BASE
	{
	public:
		float		FogStart;	// フォグの開始距離
		float		FogEnd;		// フォグの最大距離
		D3DXCOLOR	FogColor;	// フォグの色
	};
	// ライト用フラグ構造体
	class LIGHTFLAGS_BASE
	{
	public:
		int			Type;		//ライトタイプ（enum LIGHT_TYPE）
		int			Dummy[3];
	};
	// マテリアル用定数バッファ構造体
	class MATERIAL_CBUFFER_BASE
	{
	public:
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		int			noTexSampling;
		float		Dummy[2];				// 16byte境界用
	};
	// ライト用定数バッファ構造体
	class LIGHT_CBUFFER_BASE
	{
	public:
		D3DXVECTOR4 Direction[LIGHT_MAX];	// ライトの方向
		D3DXVECTOR4 Position[LIGHT_MAX];	// ライトの位置
		D3DXCOLOR	Diffuse[LIGHT_MAX];		// 拡散光の色
		D3DXCOLOR   Ambient[LIGHT_MAX];		// 環境光の色
		D3DXVECTOR4	Attenuation[LIGHT_MAX];	// 減衰率
		LIGHTFLAGS_BASE	Flags[LIGHT_MAX];		// ライト種別
		int			Enable;					// ライティング有効・無効フラグ
		int			Dummy[3];				// 16byte境界用
	};
	// フォグ用定数バッファ構造体
	class FOG_CBUFFER_BASE
	{
	public:
		D3DXVECTOR4 Fog;					// フォグ量
		D3DXCOLOR	FogColor;				// フォグの色
		int			Enable;					// フォグ有効・無効フラグ
		float		Dummy[3];				// 16byte境界用
	};
	// 縁取り用バッファ
	class FUCHI
	{
	public:
		int			fuchi;
		int			fill[3];
	};
	//*****************************************************************************
	// Model構造体
	//*****************************************************************************
	// マテリアル構造体
	class DX11_MODEL_MATERIAL
	{
	public:
		MATERIAL_BASE					Material;
		ID3D11ShaderResourceView	*Texture;
	};
	// 描画サブセット構造体
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
	// マテリアル構造体
	class MODEL_MATERIAL
	{
	public:
		char						Name[256];
		MATERIAL_BASE					Material;
		char						TextureName[256];
	};
	// 描画サブセット構造体
	class SUBSET
	{
	public:
		unsigned short	StartIndex;
		unsigned short	IndexNum;
		MODEL_MATERIAL	Material;
	};
	// モデル構造体
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
	