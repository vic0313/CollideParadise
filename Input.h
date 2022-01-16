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
		LPDIRECTINPUT8			g_pDInput ;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
		LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard ;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
		BYTE					g_keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		BYTE					g_keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
		//--------------------------------- mouse
		LPDIRECTINPUTDEVICE8 pMouse ; // mouse

		DIMOUSESTATE2   mouseState;		// �}�E�X�̃_�C���N�g�ȏ��
		DIMOUSESTATE2   mouseTrigger;	// �����ꂽ�u�Ԃ���ON

		//--------------------------------- game pad
		LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// �p�b�h�f�o�C�X

		DWORD	padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
		DWORD	padTrigger[GAMEPADMAX];
		int		padCount;			// ���o�����p�b�h�̐�
		
		//*****************************************************************************
		// �v���g�^�C�v�錾
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
		HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow ); // �}�E�X�̏�����
		void UninitMouse();						// �}�E�X�̏I������
		HRESULT UpdateMouse();					// �}�E�X�̍X�V����

		BOOL IsMouseLeftPressed();      // ���N���b�N�������
		BOOL IsMouseLeftTriggered();    // ���N���b�N�����u��
		BOOL IsMouseRightPressed();     // �E�N���b�N�������
		BOOL IsMouseRightTriggered();   // �E�N���b�N�����u��
		BOOL IsMouseCenterPressed();    // ���N���b�N�������
		BOOL IsMouseCenterTriggered();  // ���N���b�N�����u��
		long GetMouseX();               // �}�E�X��X�����ɓ��������Βl
		long GetMouseY();               // �}�E�X��Y�����ɓ��������Βl
		long GetMouseZ();               // �}�E�X�z�C�[�������������Βl

		//---------------------------- game pad
		HRESULT InitializePad();			// �p�b�h������
		//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
		void UpdatePad();
		void UninitPad();

		BOOL IsButtonPressed(int padNo, DWORD button );
		BOOL IsButtonTriggered(int padNo, DWORD button );
	};

#endif
}