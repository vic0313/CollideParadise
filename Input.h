#pragma once
#include "Main.h"

namespace FIGHTING_GAME
{
#ifndef _INPUT_H_
#define _INPUT_H_
	class Input 
	{
	public:
		//------------------------------- keyboard
		LPDIRECTINPUT8			g_pDInput ;					// IDirectInput8インターフェースへのポインタ
		LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard ;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
		BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
		BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
		//--------------------------------- mouse
		LPDIRECTINPUTDEVICE8 pMouse ; // mouse

		DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
		DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON

		//--------------------------------- game pad
		LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// パッドデバイス

		DWORD	padState[GAMEPADMAX];	// パッド情報（複数対応）
		DWORD	padTrigger[GAMEPADMAX];
		int		padCount;			// 検出したパッドの数
		
		//*****************************************************************************
		// プロトタイプ宣言
		//*****************************************************************************
		Input(HINSTANCE hInst, HWND hWnd );
		void UninitInput();
		void UpdateInput();
		//---------------------------- keyboard
		HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd );
		void UninitKeyboard();
		HRESULT UpdateKeyboard();

		bool GetKeyboardPress(int nKey );
		bool GetKeyboardTrigger(int nKey );
		bool GetKeyboardRepeat(int nKey );
		bool GetKeyboardRelease(int nKey );

		//---------------------------- mouse
		HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow ); // マウスの初期化
		void UninitMouse();						// マウスの終了処理
		HRESULT UpdateMouse();					// マウスの更新処理

		BOOL IsMouseLeftPressed();      // 左クリックした状態
		BOOL IsMouseLeftTriggered();    // 左クリックした瞬間
		BOOL IsMouseRightPressed();     // 右クリックした状態
		BOOL IsMouseRightTriggered();   // 右クリックした瞬間
		BOOL IsMouseCenterPressed();    // 中クリックした状態
		BOOL IsMouseCenterTriggered();  // 中クリックした瞬間
		long GetMouseX();               // マウスがX方向に動いた相対値
		long GetMouseY();               // マウスがY方向に動いた相対値
		long GetMouseZ();               // マウスホイールが動いた相対値

		//---------------------------- game pad
		HRESULT InitializePad();			// パッド初期化
		//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
		void UpdatePad();
		void UninitPad();

		BOOL IsButtonPressed(int padNo, DWORD button );
		BOOL IsButtonTriggered(int padNo, DWORD button );
	};

#endif
}