#include "Calculate.h"
namespace FIGHTING_GAME
{
	void Calculate::Four_out_Five_in(D3DXVECTOR3 *pos)
	{
		//小数点4位
		bool isNegative = false; 
		int multiplier;
		if (pos->x < 0)
		{
			isNegative = true;
			pos->x = -pos->x;
		}
		
		multiplier = (int)pow(10, 3);
		pos->x = (float)((int)(pos->x * multiplier + 0.5) / (multiplier * 1.0));
		if (isNegative) 
		{
			pos->x = -pos->x;
			isNegative = false;
		}

		isNegative = false;
		if (pos->y < 0)
		{
			isNegative = true;
			pos->y = -pos->y;
		}
		multiplier = (int)pow(10, 3);
		pos->y = (float)((int)(pos->y * multiplier + 0.5) / (multiplier * 1.0));
		if (isNegative)
		{
			pos->y = -pos->y;
			isNegative = false;
		}

		isNegative = false;
		if (pos->z < 0)
		{
			isNegative = true;
			pos->z = -pos->z;
		}
		multiplier = (int)pow(10, 3);
		pos->z = (float)((int)(pos->z * multiplier + 0.5) / (multiplier * 1.0));
		if (isNegative)
		{
			pos->z = -pos->z;
			isNegative = false;
		}
	}

	float Calculate::Four_out_Five_in(float kyori)
	{
		bool isNegative = false;
		int multiplier;
		if (kyori < 0)
		{
			isNegative = true;
			kyori = -kyori;
		}

		multiplier = (int)pow(10, 3);
		kyori = (float)((int)(kyori * multiplier + 0.5) / (multiplier * 1.0));
		if (isNegative)
		{
			kyori = -kyori;
			isNegative = false;
		}
		return kyori;
	}

	float Calculate::Two_vector_angle(D3DXVECTOR3 *vector1, D3DXVECTOR3 *vector2)
	{
		float ans;
		ans = ((vector1->x*vector2->x)+ (vector1->y*vector2->y)+ (vector1->z*vector2->z))/
			((sqrt(vector1->x*vector1->x+ vector1->y*vector1->y+ vector1->z*vector1->z))*
			(sqrt(vector2->x*vector2->x + vector2->y*vector2->y + vector2->z*vector2->z)));
		ans=this->Four_out_Five_in(ans);
		return ans;
	}
//=============================================================================
// 内積
//=============================================================================
	float Calculate::dotProduct(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2)
	{
#if 0
		float ans = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
#else
		// ダイ?クトＸでは、、、
		float ans = D3DXVec3Dot(v1, v2);
#endif

		return(ans);
	}
//=============================================================================
// 外積
//=============================================================================
	void Calculate::crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *v1, D3DXVECTOR3 *v2)
	{
#if 0
		ret->x = v1->y * v2->z - v1->z * v2->y;
		ret->y = v1->z * v2->x - v1->x * v2->z;
		ret->z = v1->x * v2->y - v1->y * v2->x;
#else
		// ダイ?クトＸでは、、、
		D3DXVec3Cross(ret, v1, v2);
#endif
	}
}