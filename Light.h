#pragma once
#include "Main.h"
#include "Renderer.h"
namespace FIGHTING_GAME
{
#ifndef _LIGHT_H_
#define _LIGHT_H_
	class Light 
	{
	private:
		LIGHT_BASE light_Light[LIGHT_MAX];
		FOG_BASE fog_Light ;
		Renderer* light_renderer;
		D3DXVECTOR3 player_pos;
	public:
		

		Light(Renderer* renderer);
		HRESULT InitLight();
		void UpdateLight( );

		void SetLightData(int index, LIGHT_BASE* LIGHT_BASE);
		void SetFogData( FOG_BASE* FOG_BASE);
	};
#endif
}