#pragma once
#include "Main.h"
#include <cmath>
namespace FIGHTING_GAME
{
#ifndef _CALCULATE_H_
#define _CALCULATE_H_
	class Calculate
	{
	public:
		void Four_out_Five_in(D3DXVECTOR3 *pos);
		float Four_out_Five_in(float kyori);
		float Two_vector_angle(D3DXVECTOR3 *vector1, D3DXVECTOR3 *vector2);
		float dotProduct(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2);
		void crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *v1, D3DXVECTOR3 *v2);

	};
#endif
}
