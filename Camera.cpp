#include "Camera.h"
namespace FIGHTING_GAME
{
	Camera::Camera(Renderer* renderer, Input* input)
	{
		camera_renderer= renderer;
		camera_input = input;
	}
	void Camera::InitCamera()
	{
		// 視点と注視点の距離を計算
		float vx, vz,vy;
		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
			//pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			pos = D3DXVECTOR3(0.0f, 0.0, -100.0f);
			at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case MODE_INSTRUCTION:
			//pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			pos = D3DXVECTOR3(0.0f, GAME_NORMAL_AT_LEN, GAME_NORMAL_CAMERAPOS_Y);
			at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case MODE_PLAYEREDIT:
			//pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			pos = D3DXVECTOR3(0.0f, GAME_NORMAL_AT_LEN, GAME_NORMAL_CAMERAPOS_Y);
			at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case MODE_GAME:
			//pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			pos = D3DXVECTOR3(0.0f, GAME_NORMAL_AT_LEN, GAME_NORMAL_CAMERAPOS_Y);
			at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case MODE_RESULT:
			//pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			pos = D3DXVECTOR3(0.0f, GAME_NORMAL_AT_LEN, GAME_NORMAL_CAMERAPOS_Y);
			at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}
		rot.y = 0.0f;
		
		vx = pos.x - at_pos.x;
		vz = pos.z - at_pos.z;
		vy = pos.y - at_pos.y;
		len = sqrtf(vx * vx + vz * vz + vy * vy);
		len_noy = sqrtf(vx * vx + vz * vz);
		D3DXVECTOR3 plong = at_pos - pos;
		plong.y = 0.0f;
		D3DXVECTOR3 pl = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		float result = acosf(len_noy/D3DXVec3Dot(&pl, &plong));
		if (plong.x > 0)
		{
			result = (-result);
		}
		else if (plong.x == 0)
		{
			if (plong.z < 0)
			{
				result = D3DX_PI;
			}
			else if (plong.z > 0)
			{
				result = 0.0f;
			}
		}
		
		at_roty = result;
		at_rotxz = 0.0f;
	}
	void Camera::UpdateCamera()
	{
		switch (GameDate::GamePhase_now)
		{
		case MODE_TITLE:
			this->Camera_title();
			break;
		case MODE_INSTRUCTION:
			this->Camera_instruction();
			break;
		case MODE_PLAYEREDIT:
			this->Camera_playeredit();
			break;
		case MODE_RESULT:
			this->Camera_result();
			break;
		case MODE_GAME:
			switch (GameDate::GameMode)
			{
			case normal:
				this->Camera_game_normal();
				break;
			case camera_free:
				this->Camera_game_camera_free();
				break;
			case camera_lock_on:
				this->Camera_game_lock_on();
				break;
			case pasue:
				break;
			}
			break;
		}
	}
	void Camera::UninitCamera(void)
	{

	}

//============================================================================
// CameraのUPDATE
//=============================================================================

	void  Camera::Camera_title(void)
	{
		pos = D3DXVECTOR3(0.0f, 0.0, -30.0f);
		at_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	void Camera::Camera_instruction(void)
	{

	}
	void Camera::Camera_playeredit(void)
	{

	}
	void Camera::Camera_result(void)
	{

	}
	void Camera::Camera_game_normal(void)
	{
		D3DXVECTOR3 rot_calculate = (at_pos - pos);
		
		at_pos = playerpos;
		at_pos.x -= sinf(rot.y)*GAME_NORMAL_AT_LEN;
		at_pos.z -= cosf(rot.y)*GAME_NORMAL_AT_LEN;
		pos= playerpos;
		pos.y += GAME_NORMAL_CAMERAPOS_Y;
		pos.x += sinf(rot.y)*GAME_NORMAL_POS_LEN;
		pos.z += cosf(rot.y)*GAME_NORMAL_POS_LEN;
		
		HWND titlecheck = GetActiveWindow();		//このプログラムのTITLE
		HWND OK = GetForegroundWindow();			//最上のプログラムのTITLE

		if (OK == titlecheck)
		{
			POINT point, pointwindow;
			GetCursorPos(&point);			//今モニター上、mouseの座標
			RECT rect;
			GetWindowRect(titlecheck, &rect);
			pointwindow.x = rect.left + (rect.right - rect.left) / 2;
			pointwindow.y = rect.top + (rect.bottom - rect.top) / 2;
			mouse_move_x = float(point.x - pointwindow.x);
			mouse_move_y = float(point.y - pointwindow.y);
			SetCursorPos(pointwindow.x, pointwindow.y);			//mouseの座標reset
		}
		rot.y += (D3DX_PI * (mouse_move_x / 2000));
	}
	void Camera::Camera_game_camera_free(void)
	{
		HWND titlecheck = GetActiveWindow();		//このプログラムのTITLE
		HWND OK = GetForegroundWindow();			//最上のプログラムのTITLE

		if (OK == titlecheck)
		{
			POINT point, pointwindow;
			GetCursorPos(&point);			//今モニター上、mouseの座標
			RECT rect;
			GetWindowRect(titlecheck, &rect);
			pointwindow.x = rect.left + (rect.right - rect.left) / 2;
			pointwindow.y = rect.top + (rect.bottom - rect.top) / 2;
			mouse_move_x = float(point.x - pointwindow.x);
			mouse_move_y = float(point.y - pointwindow.y);
			SetCursorPos(pointwindow.x, pointwindow.y);			//mouseの座標reset
		}

		at_roty += (D3DX_PI * (mouse_move_x / 2000));
		at_rotxz -= (D3DX_PI * (mouse_move_y / 2000));

		if (at_rotxz >= (D3DX_PI * 3 / 4))
		{
			at_rotxz = D3DX_PI * 3 / 4;
		}
		else if (at_rotxz <= (-D3DX_PI * 3 / 4))
		{
			at_rotxz = -D3DX_PI * 3 / 4;
		}

		spd *= 0.4f;

		// 移動処理
		if (camera_input->GetKeyboardPress(DIK_A))
		{
			spd = CAMERA_MOVE;
			rot.y = D3DX_PI / 2;
		}
		if (camera_input->GetKeyboardPress(DIK_D))
		{
			spd = CAMERA_MOVE;
			rot.y = -D3DX_PI / 2;
		}
		if (camera_input->GetKeyboardPress(DIK_W))
		{
			spd = CAMERA_MOVE;
			rot.y = 0.0f;
		}
		if (camera_input->GetKeyboardPress(DIK_S))
		{
			spd = CAMERA_MOVE;
			rot.y = D3DX_PI;
		}
		if (camera_input->GetKeyboardPress(DIK_W) && camera_input->GetKeyboardPress(DIK_A))
		{
			spd = CAMERA_MOVE;
			rot.y = (D3DX_PI) / 4;
		}
		else if (camera_input->GetKeyboardPress(DIK_W) && camera_input->GetKeyboardPress(DIK_D))
		{
			spd = CAMERA_MOVE;
			rot.y = -(D3DX_PI) / 4;
		}
		if (camera_input->GetKeyboardPress(DIK_S) && camera_input->GetKeyboardPress(DIK_A))
		{
			spd = CAMERA_MOVE;
			rot.y = (D3DX_PI * 3) / 4;
		}
		else if (camera_input->GetKeyboardPress(DIK_S) && camera_input->GetKeyboardPress(DIK_D))
		{
			spd = CAMERA_MOVE;
			rot.y = -(D3DX_PI * 3) / 4;
		}

		pos.x -= sinf(at_roty - rot.y) * spd;
		pos.z -= cosf(at_roty - rot.y) * spd;
		at_pos.x = pos.x - sinf(at_roty) * len_noy;
		at_pos.z = pos.z - cosf(at_roty) * len_noy;


		if (camera_input->GetKeyboardPress(DIK_Z))
		{
			pos.y += CAMERA_MOVE;
			//at_pos.y += CAMERA_MOVE;
		}
		else if (camera_input->GetKeyboardPress(DIK_C))
		{
			pos.y -= CAMERA_MOVE;
			//at_pos.y -= CAMERA_MOVE;
		}
		at_pos.y = pos.y + tanf(at_rotxz)*len_noy;
	}
	void Camera::Camera_game_lock_on(void)
	{

	}
//= ============================================================================
// ビューポートの設定
//=============================================================================
	void Camera::SetCamera()
	{
		// ビューマトリックス設定
		D3DXMatrixLookAtLH(&mtxView, &pos, &at_pos, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		camera_renderer->SetViewMatrix(&mtxView);

		float det;
		D3DXMatrixInverse(&mtxInvView, &det, &mtxView);

		// プロジェクションマトリックス設定
		D3DXMatrixPerspectiveFovLH(&mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

		camera_renderer->SetProjectionMatrix(&mtxProjection);
	}

	void Camera::SetViewPort(int type)
	{
		ID3D11DeviceContext *g_ImmediateContext = camera_renderer->GetDeviceContext();
		D3D11_VIEWPORT vp;

		g_ViewPortType = type;

		// ビューポート設定
		switch (g_ViewPortType)
		{
		case TYPE_FULL_SCREEN:
			vp.Width = (FLOAT)SCREEN_WIDTH;
			vp.Height = (FLOAT)SCREEN_HEIGHT;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			break;

		case TYPE_LEFT_HALF_SCREEN:
			vp.Width = (FLOAT)SCREEN_WIDTH / 2;
			vp.Height = (FLOAT)SCREEN_HEIGHT;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			break;

		case TYPE_RIGHT_HALF_SCREEN:
			vp.Width = (FLOAT)SCREEN_WIDTH / 2;
			vp.Height = (FLOAT)SCREEN_HEIGHT;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = (FLOAT)SCREEN_WIDTH / 2;
			vp.TopLeftY = 0;
			break;

		case TYPE_UP_HALF_SCREEN:
			vp.Width = (FLOAT)SCREEN_WIDTH;
			vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			break;

		case TYPE_DOWN_HALF_SCREEN:
			vp.Width = (FLOAT)SCREEN_WIDTH;
			vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = (FLOAT)SCREEN_HEIGHT / 2;
			break;
		}
		g_ImmediateContext->RSSetViewports(1, &vp);
	}

	void Camera::SetPlayerDate(D3DXVECTOR3	player_pos, D3DXVECTOR3 player_rot)
	{
		playerpos = player_pos;
		playerrot = player_rot;
	}



}