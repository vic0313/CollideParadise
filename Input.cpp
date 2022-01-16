#include "Input.h"
namespace FIGHTING_GAME
{
	Input::Input(HINSTANCE hInst, HWND hWnd )
	{
		g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
		g_pDIDevKeyboard = NULL;
		pMouse = NULL;
		padCount = 0;
		//pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };

		HRESULT hr;

		if (! g_pDInput)
		{
			// DirectInputオブジェクトの作成
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)& g_pDInput, NULL);
		}

		// キーボードの初期化
		this->InitKeyboard(hInst, hWnd);

		// マウスの初期化
		this->InitializeMouse(hInst, hWnd);

		// パッドの初期化
		this->InitializePad();
	}

	//=============================================================================
	// 入力処理の終了処理
	//=============================================================================
	void Input::UninitInput()
	{
		// キーボードの終了処理
		UninitKeyboard();

		// マウスの終了処理
		UninitMouse();

		// パッドの終了処理
		UninitPad();

		if ( g_pDInput)
		{
			 g_pDInput->Release();
			 g_pDInput = NULL;
		}
	}
	//=============================================================================
	// 入力処理の更新処理
	//=============================================================================
	void Input::UpdateInput()
	{
		// キーボードの更新
		UpdateKeyboard();

		// マウスの更新
		UpdateMouse();

		// パッドの更新
		UpdatePad();

	}
	//=============================================================================
	// キーボードの初期化
	//=============================================================================
	HRESULT Input::InitKeyboard(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		// デバイスオブジェクトを作成
		hr =  g_pDInput->CreateDevice(GUID_SysKeyboard, & g_pDIDevKeyboard, NULL);
		if (FAILED(hr) ||  g_pDIDevKeyboard == NULL)
		{
			MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
			return hr;
		}

		// データフォーマットを設定
		hr =  g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr =  g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// キーボードへのアクセス権を獲得(入力制御開始)
		 g_pDIDevKeyboard->Acquire();

		return S_OK;
	}

	//=============================================================================
	// キーボードの終了処理
	//=============================================================================
	void Input::UninitKeyboard()
	{
		if ( g_pDIDevKeyboard)
		{
			  g_pDIDevKeyboard->Release();
			  g_pDIDevKeyboard = NULL;
		}
	}

	//=============================================================================
	// キーボードの更新
	//=============================================================================
	HRESULT Input::UpdateKeyboard()
	{
		HRESULT hr;
		BYTE keyStateOld[256];

		// 前回のデータを保存
		memcpy(keyStateOld,  g_keyState, NUM_KEY_MAX);

		// デバイスからデータを取得
		hr =  g_pDIDevKeyboard->GetDeviceState(sizeof( g_keyState),  g_keyState);
		if (SUCCEEDED(hr))
		{
			for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
			{
				 g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^  g_keyState[cnt]) &  g_keyState[cnt];
				 g_keyStateRelease[cnt] = (keyStateOld[cnt] ^  g_keyState[cnt]) & ~ g_keyState[cnt];
				 g_keyStateRepeat[cnt] =  g_keyStateTrigger[cnt];

				if ( g_keyState[cnt])
				{
					 g_keyStateRepeatCnt[cnt]++;
					if ( g_keyStateRepeatCnt[cnt] >= 20)
					{
						 g_keyStateRepeat[cnt] =  g_keyState[cnt];
					}
				}
				else
				{
					 g_keyStateRepeatCnt[cnt] = 0;
					 g_keyStateRepeat[cnt] = 0;
				}
			}
		}
		else
		{
			// キーボードへのアクセス権を取得
			 g_pDIDevKeyboard->Acquire();
		}

		return S_OK;
	}

	//=============================================================================
	// キーボードのプレス状態を取得
	//=============================================================================
	bool Input::GetKeyboardPress(int key )
	{
		return ( g_keyState[key] & 0x80) ? true : false;
	}

	//=============================================================================
	// キーボードのトリガー状態を取得
	//=============================================================================
	bool Input::GetKeyboardTrigger(int key )
	{
		return ( g_keyStateTrigger[key] & 0x80) ? true : false;
	}

	//=============================================================================
	// キーボードのリピート状態を取得
	//=============================================================================
	bool Input::GetKeyboardRepeat(int key )
	{
		return ( g_keyStateRepeat[key] & 0x80) ? true : false;
	}

	//=============================================================================
	// キーボードのリリ－ス状態を取得
	//=============================================================================
	bool Input::GetKeyboardRelease(int key )
	{
		return ( g_keyStateRelease[key] & 0x80) ? true : false;
	}


	//=============================================================================
	// マウス関係の処理
	//=============================================================================
	// マウスの初期化
	HRESULT Input::InitializeMouse(HINSTANCE hInst, HWND hWindow )
	{
		HRESULT result;
		// デバイス作成
		result =  g_pDInput->CreateDevice(GUID_SysMouse, & pMouse, NULL);
		if (FAILED(result) ||  pMouse == NULL)
		{
			MessageBox(hWindow, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}
		// データフォーマット設定
		result =  pMouse->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(result))
		{
			MessageBox(hWindow, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}
		// 他のアプリと協調モードに設定
		result =  pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(result))
		{
			MessageBox(hWindow, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}

		// デバイスの設定
		DIPROPDWORD prop;

		prop.diph.dwSize = sizeof(prop);
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwObj = 0;
		prop.diph.dwHow = DIPH_DEVICE;
		prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

		result =  pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
		if (FAILED(result))
		{
			MessageBox(hWindow, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}

		// アクセス権を得る
		 pMouse->Acquire();
		return result;
	}
	//---------------------------------------------------------
	void Input::UninitMouse()
	{
		if ( pMouse)
		{
			 pMouse->Unacquire();
			 pMouse->Release();
			 pMouse = NULL;
		}

	}
	//-----------------------------------------------------------
	HRESULT Input::UpdateMouse()
	{
		HRESULT result;
		// 前回の値保存
		DIMOUSESTATE2 lastMouseState =  mouseState;
		// データ取得
		result =  pMouse->GetDeviceState(sizeof( mouseState), & mouseState);
		if (SUCCEEDED(result))
		{
			 mouseTrigger.lX =  mouseState.lX;
			 mouseTrigger.lY =  mouseState.lY;
			 mouseTrigger.lZ =  mouseState.lZ;
			// マウスのボタン状態
			for (int i = 0; i < 8; i++)
			{
				 mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
					 mouseState.rgbButtons[i]) &  mouseState.rgbButtons[i]);
			}
		}
		else	// 取得失敗
		{
			// アクセス権を得てみる
			result =  pMouse->Acquire();
		}
		return result;

	}

	//----------------------------------------------
	BOOL Input::IsMouseLeftPressed()
	{
		return (BOOL)( mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
	}
	BOOL Input::IsMouseLeftTriggered()
	{
		return (BOOL)( mouseTrigger.rgbButtons[0] & 0x80);
	}
	BOOL Input::IsMouseRightPressed()
	{
		return (BOOL)( mouseState.rgbButtons[1] & 0x80);
	}
	BOOL Input::IsMouseRightTriggered()
	{
		return (BOOL)( mouseTrigger.rgbButtons[1] & 0x80);
	}
	BOOL Input::IsMouseCenterPressed()
	{
		return (BOOL)( mouseState.rgbButtons[2] & 0x80);
	}
	BOOL Input::IsMouseCenterTriggered()
	{
		return (BOOL)( mouseTrigger.rgbButtons[2] & 0x80);
	}
	//------------------
	long Input::GetMouseX()
	{
		return  mouseState.lX;
	}
	long Input::GetMouseY()
	{
		return  mouseState.lY;
	}
	long Input::GetMouseZ()
	{
		return  mouseState.lZ;
	}
	//================================================= game pad
	//---------------------------------------- コールバック関数
	
	//
	BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID , Input input);

	BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID , Input input)
	{
		
		HRESULT result;

		result = input.g_pDInput->CreateDevice(lpddi->guidInstance, &input.pGamePad[input.padCount++], NULL);
		return DIENUM_CONTINUE;	// 次のデバイスを列挙

	}
	//---------------------------------------- 初期化
	HRESULT Input::InitializePad()			// パッド初期化
	{
		HRESULT		result;
		int			i;

		 padCount = 0;
		// ジョイパッドを探す
		 g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
		// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

		for (i = 0; i <  padCount; i++) {
			// ジョイスティック用のデータ・フォーマットを設定
			result =  pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(result))
				return false; // データフォーマットの設定に失敗

			// モードを設定（フォアグラウンド＆非排他モード）
	//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	//		if ( FAILED(result) )
	//			return false; // モードの設定に失敗

			// 軸の値の範囲を設定
			// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
			// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
			// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
			DIPROPRANGE				diprg;
			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize = sizeof(diprg);
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin = RANGE_MIN;
			diprg.lMax = RANGE_MAX;
			// X軸の範囲を設定
			diprg.diph.dwObj = DIJOFS_X;
			 pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
			// Y軸の範囲を設定
			diprg.diph.dwObj = DIJOFS_Y;
			 pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

			// 各軸ごとに、無効のゾーン値を設定する。
			// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
			// 指定する値は、10000に対する相対値(2000なら20パーセント)。
			DIPROPDWORD				dipdw;
			dipdw.diph.dwSize = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
			dipdw.diph.dwHow = DIPH_BYOFFSET;
			dipdw.dwData = DEADZONE;
			//X軸の無効ゾーンを設定
			dipdw.diph.dwObj = DIJOFS_X;
			 pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
			//Y軸の無効ゾーンを設定
			dipdw.diph.dwObj = DIJOFS_Y;
			 pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

			//ジョイスティック入力制御開始
			 pGamePad[i]->Acquire();
		}

		return true;

	}
	//------------------------------------------- 終了処理
	void Input::UninitPad()
	{
		for (int i = 0; i < GAMEPADMAX; i++) {
			if ( pGamePad[i])
			{
				 pGamePad[i]->Unacquire();
				 pGamePad[i]->Release();
			}
		}

	}

	//------------------------------------------ 更新
	void Input::UpdatePad()
	{
		HRESULT			result;
		DIJOYSTATE2		dijs;
		int				i;

		for (i = 0; i <  padCount; i++)
		{
			DWORD lastPadState;
			lastPadState =  padState[i];
			 padState[i] = 0x00000000l;	// 初期化

			result =  pGamePad[i]->Poll();	// ジョイスティックにポールをかける
			if (FAILED(result)) {
				result =  pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result =  pGamePad[i]->Acquire();
			}

			result =  pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
				result =  pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result =  pGamePad[i]->Acquire();
			}

			// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
			//* y-axis (forward)
			if (dijs.lY < 0)					 padState[i] |= BUTTON_UP;
			//* y-axis (backward)
			if (dijs.lY > 0)					 padState[i] |= BUTTON_DOWN;
			//* x-axis (left)
			if (dijs.lX < 0)					 padState[i] |= BUTTON_LEFT;
			//* x-axis (right)
			if (dijs.lX > 0)					 padState[i] |= BUTTON_RIGHT;
			//* Ａボタン
			if (dijs.rgbButtons[0] & 0x80)	 padState[i] |= BUTTON_A;
			//* Ｂボタン
			if (dijs.rgbButtons[1] & 0x80)	 padState[i] |= BUTTON_B;
			//* Ｃボタン
			if (dijs.rgbButtons[2] & 0x80)	 padState[i] |= BUTTON_C;
			//* Ｘボタン
			if (dijs.rgbButtons[3] & 0x80)	 padState[i] |= BUTTON_X;
			//* Ｙボタン
			if (dijs.rgbButtons[4] & 0x80)	 padState[i] |= BUTTON_Y;
			//* Ｚボタン
			if (dijs.rgbButtons[5] & 0x80)	 padState[i] |= BUTTON_Z;
			//* Ｌボタン
			if (dijs.rgbButtons[6] & 0x80)	 padState[i] |= BUTTON_L;
			//* Ｒボタン
			if (dijs.rgbButtons[7] & 0x80)	 padState[i] |= BUTTON_R;
			//* ＳＴＡＲＴボタン
			if (dijs.rgbButtons[8] & 0x80)	 padState[i] |= BUTTON_START;
			//* Ｍボタン
			if (dijs.rgbButtons[9] & 0x80)	 padState[i] |= BUTTON_M;

			// Trigger設定
			 padTrigger[i] = ((lastPadState ^  padState[i])	// 前回と違っていて
				&  padState[i]);					// しかも今ONのやつ

		}

	}
	//----------------------------------------------- 検査
	BOOL Input::IsButtonPressed(int padNo, DWORD button )
	{
		return (button &  padState[padNo]);
	}

	BOOL Input::IsButtonTriggered(int padNo, DWORD button )
	{
		return (button &  padTrigger[padNo]);
	}




}