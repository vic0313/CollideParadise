#include "Character.h"
namespace FIGHTING_GAME
{
	HRESULT Character::InitCharacter()
	{

		return S_OK;
	}
	void Character::UninitCharacter()
	{

	}
	void Character::UpdateCharacter()
	{

	}
	void Character::DrawCharacter()
	{

	}
	void Character::Update_Pos()
	{
		//partpart_bodyのposとcolliderの修正=========================================================================
		part[part_body].pos = pos;
		part[part_body].pos.y += part[part_body].pos_origin.y;
		part[part_body].pos += part[part_body].anime_pos_plus;
		if (abs(part[part_body].pos.x) > 10000|| abs(part[part_body].pos.z) > 10000|| abs(part[part_body].pos.y) > 10000)
		{
			D3DXVECTOR3 pos_test = pos - moveway_xyz;
			pos_test.y+= part[part_body].pos_origin.y;
			part[part_body].pos = pos_test + part[part_body].anime_pos_plus;
		}
		part[part_body].rot = rot;
		part[part_body].rot += part[part_body].anime_rot_plus;
		
		collider->SetCollider3D(part[part_body].collider_index, part[part_body].pos, part[part_body].rot);
		
		//partのposの修正=========================================================================
		for (int i = 1; i < CHARACTERPART_MAX; i++)
		{
			//計算用変数設定
			float partpos_rotXZ = 0;
			float partpos_rotY = 0;
			D3DXVECTOR3 partpos = pos;
			D3DXVECTOR3 partlen = pos;
			float len = 0;
			if (i == part_leftarm_down || i == part_rightarm_down || i == part_lefthend || i == part_righthend || i == part_rightfoot_down || i == part_leftfoot_down
				|| i == part_leftfoot_sole || i == part_rightfoot_sole)
			{
				int parent_num;
				switch (i)
				{
				case part_leftarm_down:
					parent_num = part_leftarm_up;
					break;
				case part_rightarm_down:
					parent_num = part_rightarm_up;
					break;
				case part_lefthend:
					parent_num = part_leftarm_down;
					break;
				case part_righthend:
					parent_num = part_rightarm_down;
					break;
				case part_rightfoot_down:
					parent_num = part_rightfoot_up;
					break;
				case part_leftfoot_down:
					parent_num = part_leftfoot_up;
					break;
				case part_leftfoot_sole:
					parent_num = part_leftfoot_down;
					break;
				case part_rightfoot_sole:
					parent_num = part_rightfoot_down;
					break;
				}
				part[i].rot = part[parent_num].rot;
				part[i].rot += part[i].anime_rot_plus;
				//角度修正
				{
					while (part[i].rot.y > D3DX_PI || part[i].rot.y < (-D3DX_PI))
					{
						if (part[i].rot.y > 0)
						{
							part[i].rot.y -= 2 * D3DX_PI;
						}
						else if (part[i].rot.y < 0)
						{
							part[i].rot.y += 2 * D3DX_PI;
						}
					}
					while (part[i].rot.x > D3DX_PI || part[i].rot.x < (-D3DX_PI))
					{
						if (part[i].rot.x > 0)
						{
							part[i].rot.x -= 2 * D3DX_PI;
						}
						else if (part[i].rot.x < 0)
						{
							part[i].rot.x += 2 * D3DX_PI;
						}
					}
					while (part[i].rot.z > D3DX_PI || part[i].rot.z < (-D3DX_PI))
					{
						if (part[i].rot.z > 0)
						{
							part[i].rot.z -= 2 * D3DX_PI;
						}
						else if (part[i].rot.z < 0)
						{
							part[i].rot.z += 2 * D3DX_PI;
						}
					}
				}

				partpos = part[parent_num].pos;
				partlen = part[i].pos_origin - part[parent_num].pos_origin;
				len = sqrtf((partlen.x*partlen.x) + (partlen.y*partlen.y) + (partlen.z*partlen.z));

				partpos_rotXZ = 0;
				partpos_rotY = -D3DX_PI / 2;
				if (part[parent_num].rot.z != 0)
				{
					if (part[parent_num].rot.z > 0)
					{
						partpos_rotXZ = -D3DX_PI / 2;
					}
					else if (part[parent_num].rot.z < 0)
					{
						partpos_rotXZ = D3DX_PI / 2;
					}

					if (abs(part[parent_num].rot.z) > (D3DX_PI / 2))
					{
						partpos_rotY = abs(part[parent_num].rot.z) - (D3DX_PI / 2);
					}
					else if (abs(part[parent_num].rot.z) < (D3DX_PI / 2))
					{
						partpos_rotY = -((D3DX_PI / 2) - abs(part[parent_num].rot.z));
					}
					else if (abs(part[parent_num].rot.z) == (D3DX_PI / 2))
					{
						partpos_rotY = 0;
					}
				}
				float x_len = abs(len*cosf(abs(partpos_rotY)));
				float y_len = abs(len*sinf(abs(partpos_rotY)));
				float xy_len = 0;
				if (part[parent_num].rot.x != 0)
				{
					if (part[parent_num].rot.z != 0)
					{
						if (abs(part[parent_num].rot.x) < (D3DX_PI / 2))
						{
							xy_len = y_len * cosf((D3DX_PI / 2) - abs(part[parent_num].rot.x));
							xy_len = sqrtf((x_len*x_len) + (xy_len*xy_len));
							partpos_rotXZ = abs(acosf(x_len / xy_len));
							partpos_rotY = abs(acosf(xy_len / len));
							x_len = xy_len;
							if (abs(xy_len - len) < 0.0001f)
							{
								partpos_rotY = 0;
							}
							if (part[parent_num].rot.z > 0 && part[parent_num].rot.z < D3DX_PI / 2)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}

							}
							else if (part[parent_num].rot.z > D3DX_PI / 2 && part[parent_num].rot.z < D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z < 0 && part[parent_num].rot.z >(-D3DX_PI / 2))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z < (-D3DX_PI / 2) && part[parent_num].rot.z > -D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z == (-D3DX_PI / 2))
							{
								partpos_rotXZ = (D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI / 2))
							{
								partpos_rotXZ = -(D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI) || part[parent_num].rot.z == (-D3DX_PI))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = 0;
									partpos_rotY = partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = D3DX_PI;
									partpos_rotY = partpos_rotY;
								}
							}
						}
						else if (abs(part[parent_num].rot.x) > (D3DX_PI / 2) && abs(part[parent_num].rot.x) < D3DX_PI)
						{
							xy_len = y_len * cosf(abs(part[parent_num].rot.x) - (D3DX_PI / 2));
							xy_len = sqrtf((x_len*x_len) + (xy_len*xy_len));
							partpos_rotXZ = abs(acosf(x_len / xy_len));
							partpos_rotY = abs(acosf(xy_len / len));
							x_len = xy_len;
							if (abs(xy_len-len) < 0.0001f)
							{
								partpos_rotY = 0;
							}
							if (part[parent_num].rot.z > 0 && part[parent_num].rot.z < D3DX_PI / 2)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}

							}
							else if (part[parent_num].rot.z > D3DX_PI / 2 && part[parent_num].rot.z < D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z < 0 && part[parent_num].rot.z >(-D3DX_PI / 2))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z < (-D3DX_PI / 2) && part[parent_num].rot.z > -D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
									partpos_rotY = -partpos_rotY;
								}
							}
							else if (part[parent_num].rot.z == (-D3DX_PI / 2))
							{
								partpos_rotXZ = (D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI / 2))
							{
								partpos_rotXZ = -(D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI) || part[parent_num].rot.z == (-D3DX_PI))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = 0;
									partpos_rotY = -partpos_rotY;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = D3DX_PI;
									partpos_rotY = -partpos_rotY;
								}
							}
						}
						else if (abs(part[parent_num].rot.x) == (D3DX_PI / 2))
						{
							partpos_rotXZ = abs(partpos_rotY);
							partpos_rotY = 0;
							x_len = len;
							if (part[parent_num].rot.z > 0 && part[parent_num].rot.z < D3DX_PI / 2)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
								}

							}
							else if (part[parent_num].rot.z > D3DX_PI / 2 && part[parent_num].rot.z < D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
								}
							}
							else if (part[parent_num].rot.z < 0 && part[parent_num].rot.z >(-D3DX_PI / 2))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
								}
							}
							else if (part[parent_num].rot.z < (-D3DX_PI / 2) && part[parent_num].rot.z > -D3DX_PI)
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
								}
							}
							else if (part[parent_num].rot.z == (-D3DX_PI / 2))
							{
								partpos_rotXZ = (D3DX_PI / 2);
							}
							else if (part[parent_num].rot.z == (D3DX_PI / 2))
							{
								partpos_rotXZ = -(D3DX_PI / 2);
							}
							else if (part[parent_num].rot.z == (D3DX_PI) || part[parent_num].rot.z == (-D3DX_PI))
							{
								if (abs(part[parent_num].rot.x < 0))
								{
									partpos_rotXZ = 0;
								}
								else if (abs(part[parent_num].rot.x > 0))
								{
									partpos_rotXZ = D3DX_PI;
								}
							}
						}
						else if (abs(part[parent_num].rot.x) == D3DX_PI)
						{
							partpos_rotXZ = D3DX_PI / 2;
							partpos_rotY = abs(partpos_rotY);
							x_len = abs(len*cosf(abs(partpos_rotY)));

							if (part[parent_num].rot.z > 0 && part[parent_num].rot.z < D3DX_PI / 2)
							{
								partpos_rotXZ = -(D3DX_PI / 2);
								partpos_rotY = partpos_rotY;
							}
							else if (part[parent_num].rot.z > D3DX_PI / 2 && part[parent_num].rot.z < D3DX_PI)
							{
								partpos_rotXZ = -(D3DX_PI / 2);
								partpos_rotY = -partpos_rotY;
							}
							else if (part[parent_num].rot.z < 0 && part[parent_num].rot.z >(-D3DX_PI / 2))
							{
								partpos_rotXZ = (D3DX_PI / 2);
								partpos_rotY = partpos_rotY;
							}
							else if (part[parent_num].rot.z < (-D3DX_PI / 2) && part[parent_num].rot.z > -D3DX_PI)
							{
								partpos_rotXZ = (D3DX_PI / 2);
								partpos_rotY = -partpos_rotY;
							}
							else if (part[parent_num].rot.z == (-D3DX_PI / 2))
							{
								partpos_rotXZ = (D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI / 2))
							{
								partpos_rotXZ = -(D3DX_PI / 2);
								partpos_rotY = 0;
							}
							else if (part[parent_num].rot.z == (D3DX_PI) || part[parent_num].rot.z == (-D3DX_PI))
							{
								partpos_rotXZ = 0;
								partpos_rotY = -partpos_rotY;
							}
						}

						partpos_rotXZ += part[parent_num].rot.y;
						partpos.x -= (x_len * sinf(partpos_rotXZ));
						partpos.z -= (x_len * cosf(partpos_rotXZ));
						partpos.y += len * sinf(partpos_rotY);
					}
					else
					{
						if (part[parent_num].rot.x < 0)
						{
							partpos_rotXZ = D3DX_PI;
						}
						else if (part[parent_num].rot.x > 0)
						{
							partpos_rotXZ = 0;
						}

						if (abs(part[parent_num].rot.x) <= (D3DX_PI / 2))
						{
							y_len = abs(len * sinf((D3DX_PI / 2) - abs(part[parent_num].rot.x)));
							x_len = abs(len * cosf((D3DX_PI / 2) - abs(part[parent_num].rot.x)));
							partpos_rotY = -abs(asinf(y_len / len));
						}
						else if (abs(part[parent_num].rot.x) > (D3DX_PI / 2))
						{
							y_len = abs(len * sinf(abs(part[parent_num].rot.x) - (D3DX_PI / 2)));
							x_len = abs(len * cosf(abs(part[parent_num].rot.x) - (D3DX_PI / 2)));
							partpos_rotY = abs(asinf(y_len / len));
						}
						partpos_rotXZ += part[parent_num].rot.y;
						partpos.x -= (x_len * sinf(partpos_rotXZ));
						partpos.z -= (x_len * cosf(partpos_rotXZ));
						partpos.y += len * sinf(partpos_rotY);
					}
				}
				else
				{
					partpos_rotXZ += part[parent_num].rot.y;
					partpos.x -= (x_len * sinf(partpos_rotXZ));
					partpos.z -= (x_len * cosf(partpos_rotXZ));
					partpos.y += len * sinf(partpos_rotY);

				}

				part[i].pos = partpos;
			}
			else if (i == part_head || i == part_leftarm_up || i == part_rightarm_up || i == part_leftfoot_up || i == part_rightfoot_up)
			{
				Character_Pos_Update_num zoon = No_num;		//XY平面のエリア判定変数
				partpos = part[part_body].pos;				//PARENTはBODY
				part[i].rot = part[part_body].rot;
				part[i].rot += part[i].anime_rot_plus;
				//角度修正
				{
					while (part[i].rot.y > D3DX_PI || part[i].rot.y < (-D3DX_PI))
					{
						if (part[i].rot.y > 0)
						{
							part[i].rot.y -= 2 * D3DX_PI;
						}
						else if (part[i].rot.y < 0)
						{
							part[i].rot.y += 2 * D3DX_PI;
						}
					}
					while (part[i].rot.x > D3DX_PI || part[i].rot.x < (-D3DX_PI))
					{
						if (part[i].rot.x > 0)
						{
							part[i].rot.x -= 2 * D3DX_PI;
						}
						else if (part[i].rot.x < 0)
						{
							part[i].rot.x += 2 * D3DX_PI;
						}
					}
					while (part[i].rot.z > D3DX_PI || part[i].rot.z < (-D3DX_PI))
					{
						if (part[i].rot.z > 0)
						{
							part[i].rot.z -= 2 * D3DX_PI;
						}
						else if (part[i].rot.z < 0)
						{
							part[i].rot.z += 2 * D3DX_PI;
						}
					}
				}
				partlen = part[i].pos_origin - part[part_body].pos_origin;
				len = sqrtf((partlen.x*partlen.x) + (partlen.y*partlen.y) + (partlen.z*partlen.z));
				//
				if (len == 0)
				{
					partpos_rotY = 0;
				}
				else
				{
					partpos_rotY = abs(acos(abs(partlen.x) / len));
				}
				

				switch (i)
				{
				case part_head:
					partpos_rotY = D3DX_PI / 2;
					break;
				case part_leftarm_up:
					break;
				case part_rightarm_up:
					partpos_rotY = (D3DX_PI)-partpos_rotY;
					break;
				case part_leftfoot_up:
					partpos_rotY = (-partpos_rotY);
					break;
				case part_rightfoot_up:
					partpos_rotY = -((D3DX_PI)-partpos_rotY);
					break;
				}
				//
				if (part[part_body].rot.z != 0)
				{
					if (part[part_body].rot.z > 0)
					{
						partpos_rotY += abs(part[part_body].rot.z);
					}
					else if (part[part_body].rot.z < 0)
					{
						partpos_rotY -= abs(part[part_body].rot.z);
					}
					//
					while (partpos_rotY > D3DX_PI || partpos_rotY < (-D3DX_PI))
					{
						if (partpos_rotY > 0)
						{
							partpos_rotY -= 2 * D3DX_PI;
						}
						else if (partpos_rotY < 0)
						{
							partpos_rotY += 2 * D3DX_PI;
						}
					}
				}

				//
				if (partpos_rotY > 0 && partpos_rotY < (D3DX_PI / 2))
				{
					zoon = XY_right_up;
				}
				else if (partpos_rotY > (D3DX_PI / 2) && partpos_rotY < (D3DX_PI))
				{
					zoon = XY_left_up;
					partpos_rotY = D3DX_PI - partpos_rotY;
				}
				else if (partpos_rotY < 0 && partpos_rotY >(-D3DX_PI / 2))
				{
					zoon = XY_right_down;
				}
				else if (partpos_rotY <(-D3DX_PI / 2) && partpos_rotY >(-D3DX_PI))
				{
					zoon = XY_left_down;
					partpos_rotY = -(D3DX_PI + partpos_rotY);
				}
				else if (partpos_rotY == 0)
				{
					zoon = Xo;
					partpos_rotY = 0;
				}
				else if (partpos_rotY == (-D3DX_PI) || partpos_rotY == (D3DX_PI))
				{
					zoon = Xx;
					partpos_rotY = 0;
				}
				else if (partpos_rotY == (D3DX_PI / 2))
				{
					zoon = Yo;
				}
				else if (partpos_rotY == (-D3DX_PI / 2))
				{
					zoon = Yx;
				}
				//
				if (part[part_body].rot.x != 0)
				{
					float y_len = abs(len* sinf(abs(partpos_rotY)));
					float y_len_a = 0;
					if (abs(part[part_body].rot.x) > (D3DX_PI / 2) && abs(part[part_body].rot.x) < D3DX_PI)
					{
						y_len_a = abs(y_len * sinf(abs(part[part_body].rot.x) - D3DX_PI / 2));
						y_len = sqrtf((len*len) - (y_len_a*y_len_a));

					}
					else if (abs(part[part_body].rot.x) < (D3DX_PI / 2) && abs(part[part_body].rot.x) > 0)
					{
						y_len_a = abs(y_len * cosf(abs(part[part_body].rot.x)));
						y_len = sqrtf((len*len) - (y_len_a*y_len_a));
					}
					else if (abs(part[part_body].rot.x) == D3DX_PI)
					{
						y_len = abs(len* cosf(abs(partpos_rotY)));
					}
					else if (abs(part[part_body].rot.x) == (D3DX_PI / 2))
					{
						y_len = len;
					}
					y_len_a = abs(len* cosf(abs(partpos_rotY)));
					//y_lenはBODYのPOSから同じXZ平面　PART[i]までの距離

					if (y_len_a > y_len)
					{
						y_len_a = y_len;
					}
					partpos_rotXZ = acosf(y_len_a / y_len);
					if (y_len == 0)
					{
						partpos_rotXZ = 0;
					}
					switch (zoon)
					{
					case XY_left_up:
						if (part[part_body].rot.x < 0)
						{

							partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
						}
						else if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
						}

						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = acosf(y_len / len);
						}
						else
						{
							partpos_rotY = -(acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					case XY_right_up:
						if (part[part_body].rot.x < 0)
						{
							partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
						}
						else if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
						}

						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = acosf(y_len / len);
						}
						else
						{
							partpos_rotY = -(acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					case XY_left_down:
						if (part[part_body].rot.x < 0)
						{

							partpos_rotXZ = ((D3DX_PI / 2) + partpos_rotXZ);
						}
						else if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = ((D3DX_PI / 2) - partpos_rotXZ);
						}

						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = -acosf(y_len / len);
						}
						else
						{
							partpos_rotY = (acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					case XY_right_down:
						if (part[part_body].rot.x < 0)
						{

							partpos_rotXZ = -((D3DX_PI / 2) + partpos_rotXZ);
						}
						else if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = -((D3DX_PI / 2) - partpos_rotXZ);
						}

						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = -acosf(y_len / len);
						}
						else
						{
							partpos_rotY = (acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					case Xo:
						partpos_rotXZ = -D3DX_PI / 2;
						partpos_rotY = 0;
						break;
					case Xx:
						partpos_rotXZ = D3DX_PI / 2;
						partpos_rotY = 0;
						break;
					case Yo:
						if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = D3DX_PI;
						}
						else if (part[part_body].rot.x < 0)
						{
							partpos_rotXZ = 0;
						}
						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = acosf(y_len / len);
						}
						else
						{
							partpos_rotY = -(acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					case Yx:
						if (part[part_body].rot.x > 0)
						{
							partpos_rotXZ = 0;
						}
						else if (part[part_body].rot.x < 0)
						{
							partpos_rotXZ = D3DX_PI;
						}
						if (abs(part[part_body].rot.x) <= (D3DX_PI / 2))
						{
							partpos_rotY = -acosf(y_len / len);
						}
						else
						{
							partpos_rotY = (acosf(y_len / len));
						}
						if (len == 0)
						{
							partpos_rotY = 0;
						}
						break;
					}

					partpos_rotXZ += part[part_body].rot.y;

					partpos.y += len * sinf(partpos_rotY);
					partpos.x -= y_len * sinf(partpos_rotXZ);
					partpos.z -= y_len * cosf(partpos_rotXZ);


				}
				else
				{
					switch (zoon)
					{
					case XY_left_up:
						partpos_rotXZ = (D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case XY_right_up:
						partpos_rotXZ = (-D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case XY_left_down:
						partpos_rotXZ = (D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case XY_right_down:
						partpos_rotXZ = (-D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case Xo:
						partpos_rotXZ = (-D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case Xx:
						partpos_rotXZ = (D3DX_PI / 2) + part[part_body].rot.y;
						break;
					case Yo:
						partpos_rotXZ += part[part_body].rot.y;
						break;
					case Yx:
						partpos_rotXZ += part[part_body].rot.y;
						break;
					}
					partpos.y += len * sinf(partpos_rotY);
					partpos.x -= abs(len* cosf(abs(partpos_rotY))) * sinf(partpos_rotXZ);
					partpos.z -= abs(len* cosf(abs(partpos_rotY))) * cosf(partpos_rotXZ);
				}
				part[i].pos = partpos;
			}

		}

		//partのcolliderのposの修正=========================================================================
		for (int i = 1; i < CHARACTERPART_MAX; i++)
		{
			if (i == part_leftarm_down || i == part_rightarm_down || i == part_lefthend || i == part_righthend || i == part_rightfoot_down || i == part_leftfoot_down
				|| i == part_leftfoot_sole || i == part_rightfoot_sole)
			{
				int parent_num = 0;
				switch (i)
				{
				case part_leftarm_down:
					parent_num = part_lefthend;
					break;
				case part_rightarm_down:
					parent_num = part_righthend;
					break;
				case part_lefthend:
					parent_num = part_lefthend;
					break;
				case part_righthend:
					parent_num = part_righthend;
					break;
				case part_rightfoot_down:
					parent_num = part_rightfoot_sole;
					break;
				case part_leftfoot_down:
					parent_num = part_leftfoot_sole;
					break;
				case part_rightfoot_sole:
					parent_num = part_rightfoot_sole;
					break;
				case part_leftfoot_sole:
					parent_num = part_leftfoot_sole;
					break;

				}
				D3DXVECTOR3 partpos = part[i].pos + ((part[parent_num].pos - part[i].pos) / 2);
				collider->SetCollider3D(part[i].collider_index, partpos, part[i].rot);
			}
			else if (i == part_head || i == part_leftarm_up || i == part_rightarm_up || i == part_leftfoot_up || i == part_rightfoot_up)
			{
				int parent_num;
				D3DXVECTOR3 partpos = pos;
				switch (i)
				{
				case part_head:
					parent_num = part_head;
					break;
				case part_leftarm_up:
					parent_num = part_leftarm_down;
					break;
				case part_rightarm_up:
					parent_num = part_rightarm_down;
					break;
				case part_leftfoot_up:
					parent_num = part_leftfoot_down;
					break;
				case part_rightfoot_up:
					parent_num = part_rightfoot_down;
					break;
				}
				partpos = part[i].pos + ((part[parent_num].pos - part[i].pos) / 2);
				collider->SetCollider3D(part[i].collider_index, partpos, part[i].rot);
			}
		}
	}

	void Character::Animation_control(void)
	{

	}
	bool Character::Character_RayHitGround(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos, float start_UP)
	{
		bool ans = false;
		switch (map1->Model_data[num].model_num)
		{
		case Num1:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_1, start_UP);
			break;
		case Num2:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_2, start_UP);
			break;
		case Num3:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_3, start_UP);
			break;
		case Num4:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_4, start_UP);
			break;
		case Num5:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_5, start_UP);
			break;
		case Num6:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_6, start_UP);
			break;
		case Num7:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_7, start_UP);
			break;
		case Num8:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_8, start_UP);
			break;
		case Num9:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_9, start_UP);
			break;
		case Num10:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_10, start_UP);
			break;
		case Num11:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_11, start_UP);
			break;
		case Num12:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_12, start_UP);
			break;
		case Num13:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_13, start_UP);
			break;
		case Num14:
			ans = collider->RayHitGround(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_14, start_UP);
			break;
		}

		return ans;
	}
	bool Character::Character_RayHitTop(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos)
	{
		bool ans = false;
		switch (map1->Model_data[num].model_num)
		{
			case Num1:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_1);
				break;
			case Num2:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_2);
				break;
			case Num3:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_3);
				break;
			case Num4:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_4);
				break;
			case Num5:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_5);
				break;
			case Num6:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_6);
				break;
			case Num7:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_7);
				break;
			case Num8:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_8);
				break;
			case Num9:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_9);
				break;
			case Num10:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_10);
				break;
			case Num11:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_11);
				break;
			case Num12:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_12);
				break;
			case Num13:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_13);
				break;
			case Num14:
				ans = collider->RayHitTop(HitPosition, Normal, pos,
					map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_14);
				break;
		}

		return ans;
	}
	bool Character::Character_RayHitWall(int num, D3DXVECTOR3 *HitPosition, D3DXVECTOR3 *Normal, D3DXVECTOR3 pos, D3DXVECTOR3 ray_way)
	{
		bool ans = false;
		switch (map1->Model_data[num].model_num)
		{
		case Num1:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_1, ray_way);
			break;
		case Num2:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_2, ray_way);
			break;
		case Num3:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_3, ray_way);
			break;
		case Num4:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_4, ray_way);
			break;
		case Num5:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_5, ray_way);
			break;
		case Num6:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_6, ray_way);
			break;
		case Num7:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_7, ray_way);
			break;
		case Num8:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_8, ray_way);
			break;
		case Num9:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_9, ray_way);
			break;
		case Num10:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_10, ray_way);
			break;
		case Num11:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_11, ray_way);
			break;
		case Num12:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_12, ray_way);
			break;
		case Num13:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_13, ray_way);
			break;
		case Num14:
			ans = collider->RayHitWall(HitPosition, Normal, pos,
				map1->Model_data[num].scl, map1->Model_data[num].rot, map1->Model_data[num].pos, map1->model_14, ray_way);
			break;
		
		}
		return ans;
	}
	void Character::RotRevise(void)
	{
		while (rot_destine.y > D3DX_PI || rot_destine.y < (-D3DX_PI))
		{
			if (rot_destine.y > 0)
			{
				rot_destine.y -= 2 * D3DX_PI;
			}
			else if (rot_destine.y < 0)
			{
				rot_destine.y += 2 * D3DX_PI;
			}
		}
		while (rot.y > D3DX_PI || rot.y < (-D3DX_PI))
		{
			if (rot.y > 0)
			{
				rot.y -= 2 * D3DX_PI;
			}
			else if (rot.y < 0)
			{
				rot.y += 2 * D3DX_PI;
			}
		}

		float space = 0;		//rot nextとrotの距離
		float way = 0;			//rot回転の方向　1は正時間、-1は逆時間

		if (rot_destine.y > rot.y)
		{
			if (rot_destine.y >= 0 && rot.y < 0)
			{
				float a = rot_destine.y + (float)fabs(rot.y);
				float b = (D3DX_PI - rot_destine.y) + (D3DX_PI + rot.y);
				if (a > b)
				{
					way = -1.0f;
					space = b;
				}
				else
				{
					way = 1.0f;
					space = a;
				}
			}
			else
			{
				space = rot_destine.y - rot.y;
				way = 1.0f;
			}
		}
		else if (rot_destine.y < rot.y)
		{
			if (rot.y >= 0 && rot_destine.y < 0)
			{
				float a = (float)fabs(rot_destine.y) + rot.y;
				float b = (D3DX_PI + rot_destine.y) + (D3DX_PI - rot.y);
				if (a > b)
				{
					way = 1.0f;
					space = b;
				}
				else
				{
					way = -1.0f;
					space = a;
				}
			}
			else
			{
				space = rot.y - rot_destine.y;
				way = -1.0f;
			}
		}

		float	rot_change;
		if (space >= (D3DX_PI * 3 / 4))
		{
			rot_change = GAME_NORMAL_ROT_CHANGE * 4;
		}
		else if (space >= (D3DX_PI / 2))
		{
			rot_change = GAME_NORMAL_ROT_CHANGE * 2;
		}
		else
		{
			rot_change = GAME_NORMAL_ROT_CHANGE;
		}

		if (way > 0)		//順時間
		{
			float rotnext = rot.y + rot_change;
			if (rotnext > D3DX_PI)
			{
				rotnext -= 2 * D3DX_PI;
			}
			else if (rotnext < (-D3DX_PI))
			{
				rotnext += 2 * D3DX_PI;
			}

			if (rotnext > 0 && rot_destine.y < 0)
			{
				if (rotnext < rot_destine.y)
				{
					rot.y = rot_destine.y;
				}
				else
				{
					rot.y = rotnext;
				}
			}
			else
			{
				if (rotnext > rot_destine.y)
				{
					rot.y = rot_destine.y;
				}
				else
				{
					rot.y = rotnext;
				}
			}

		}
		else if (way < 0)
		{
			float rotnext = rot.y - rot_change;
			if (rotnext > D3DX_PI)
			{
				rotnext -= 2 * D3DX_PI;
			}
			else if (rotnext < (-D3DX_PI))
			{
				rotnext += 2 * D3DX_PI;
			}

			if (rotnext < 0 && rot_destine.y > 0)
			{
				if (rotnext > rot_destine.y)
				{
					rot.y = rot_destine.y;
				}
				else
				{
					rot.y = rotnext;
				}
			}
			else
			{
				if (rotnext < rot_destine.y)
				{
					rot.y = rot_destine.y;
				}
				else
				{
					rot.y = rotnext;
				}
			}

		}
		else
		{
			rot.y = rot_destine.y;
		}
	}
	void Character::Character_edge_control()
	{
		if (abs(pos_destine.x) > 10000)
		{
			pos_destine.x = pos.x;
			pos_destine.z = pos.z;
		}

		if (pos_destine.x == (0.0f)&& pos_destine.z == (0.0f)&& pos_destine.y < (1000.0f))
		{
			pos_destine.y = (1000.0f);
			moveway_xyz.x = pos_destine.x - pos.x;
		}

		if (pos_destine.x <= (-2500.0f))
		{
			pos_destine.x = (-2500.0f);
			moveway_xyz.x = pos_destine.x - pos.x;
		}
		else if (pos_destine.x >= (2500.0f))
		{
			pos_destine.x = (2500.0f);
			moveway_xyz.x = pos_destine.x - pos.x;
		}
		if (pos_destine.z <= (-2480.0f))
		{
			pos_destine.z = (-2480.0f);
			moveway_xyz.z = pos_destine.z - pos.z;
		}
		else if (pos_destine.z >= (2480.0f))
		{
			pos_destine.z = (2480.0f);
			moveway_xyz.z = pos_destine.z - pos.z;
		}

		if (pos_destine.y < (-100.0f))
		{
			spd_y = 8;
			HP -= 1;
			if (beAttack == true)
			{
				beAttack = false;
			}
		}
		if (HP <= 0)
		{
			HP = 0;
			spd = 0;
			spd_y = 0;
			dying = true;
			use = false;

		}

	}
	void Character::Character_PosUpdate()
	{
		int ground_model = -1;
		//求めたNEXT　POS、判定するためにcolliderのPOSを修正
		Update_Collider(pos_destine, rot);
		//足の処判定
		for (int i = 0; i < map1->Model_num; i++)
		{
			if (map1->Model_data[i].use != true)continue;
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori.y += (collider_wxhylz.y / 2);
			//move_kyori = map1->Model_data[i].pos - move_kyori;
			move_kyori = map1->Model_data[i].collider_pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			float kyori_p = sqrtf((collider_wxhylz.x*collider_wxhylz.x) + (collider_wxhylz.z + collider_wxhylz.z) + (collider_wxhylz.y + collider_wxhylz.y));
			//if model中心点とplayerposの距離　< modelのr+playerのr  =>BBC判定に進む
			if (kyori > (kyori_p + map1->Model_data[i].collider_radius))continue;
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[i].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (touch_test == true)break;
			}
			
			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							touch_ans = true;
							ground_model = i;
						}
						else
						{
							touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									touch_ans = true;
									ground_model = i;
								}
							}
						}
					}
					else
					{
						if (HitPosition.y > (pos_destine.y - (collider_wxhylz.y / 8))&& HitPosition.y>=0 && spd_y<=0)
						{
							pos_destine.y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							touch_ans = true;
							ground_model = i;
							
						}
					}
				}
				else
				{
					touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos, 10);
					if (touch_test == true)
					{
						if (HitPosition.y <= (pos.y))
						{
							if (spd_y < -20.0f)
							{
								pos_destine.y = HitPosition.y;
								moveway_xyz.y = pos_destine.y - pos.y;
								ground_model = i;
								touch_ans = true;
							}
							
						}
					}
				}
			}
		}
		//足場は回転や移動している処ならば追加判定
		if (ground_model == 27)
		{
			pos_destine.z += 2*cosf(D3DX_PI / 200);
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[ground_model].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[ground_model].collider_index[j]]);
				if (touch_test == true)break;
			}

			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							//ground_y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							ground_model = ground_model;
							touch_ans = true;
						}
						else
						{
							touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									//ground_y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									ground_model = ground_model;
									touch_ans = true;

								}
							}
							else
							{
								touch_ans = false;
								ground_model = -1;
							}
						}
					}

				}
			}
		}
		if (ground_model == 28)
		{
			pos_destine.x -= 2 * cosf(D3DX_PI / 200);
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[ground_model].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[ground_model].collider_index[j]]);
				if (touch_test == true)break;
			}

			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							//ground_y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							ground_model = ground_model;
							touch_ans = true;
						}
						else
						{
							touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									//ground_y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									ground_model = ground_model;
									touch_ans = true;

								}
							}
							else
							{
								touch_ans = false;
								ground_model = -1;
							}
						}
					}

				}
			}
		}
		if (ground_model == 29)
		{
			
			if (pos_destine.x != map1->Model_data[ground_model].pos.x&&pos_destine.z != map1->Model_data[ground_model].pos.z)
			{
				
				if (spd>0.1 &&pos.y == pos_destine.y)
				{
					D3DXVECTOR3 p_m = pos_destine - map1->Model_data[ground_model].pos;
					p_m.y = 0.0f;
					kyorix = D3DXVec3Length(&p_m);
					//D3DXVECTOR3 Z_moveway = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					D3DXVECTOR3 Z_moveway = D3DXVECTOR3(-sinf(map1->Model_data[ground_model].rot.y), 0.0f, -cosf(map1->Model_data[ground_model].rot.y));
					Calculate* math = new Calculate();
					D3DXVECTOR3 zzz = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					 rangex = math->Two_vector_angle(&p_m, &zzz);
					//math->Four_out_Five_in(range);
					delete math; 
					if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z >= map1->Model_data[ground_model].pos.z)
					{
						//rangex = (-D3DX_PI)+abs(rangex);
						rangex = (-D3DX_PI/2) - abs(rangex);

					}else if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = -abs(rangex);

					}
					else if (pos_destine.x < map1->Model_data[ground_model].pos.x&&pos_destine.z >= map1->Model_data[ground_model].pos.z)
					{
						//rangex = D3DX_PI-abs(rangex);
						rangex = (D3DX_PI / 2) + abs(rangex);
					}
					else if (pos_destine.x < map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = abs(rangex);
					}
					else if (pos_destine.x == map1->Model_data[ground_model].pos.x&&pos_destine.z > map1->Model_data[ground_model].pos.z)
					{
						rangex = D3DX_PI;
					}
					else if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = 0;
					}
					rangex = map1->Model_data[ground_model].rot.y- rangex;
					
				}
				else if(pos.y> pos_destine.y )
				{
					D3DXVECTOR3 p_m = pos_destine - map1->Model_data[ground_model].pos;
					p_m.y = 0.0f;
					kyorix = D3DXVec3Length(&p_m);
					//D3DXVECTOR3 Z_moveway = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					D3DXVECTOR3 Z_moveway = D3DXVECTOR3(-sinf(map1->Model_data[ground_model].rot.y), 0.0f, -cosf(map1->Model_data[ground_model].rot.y));
					Calculate* math = new Calculate();
					D3DXVECTOR3 zzz = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					rangex = math->Two_vector_angle(&p_m, &zzz);
					//math->Four_out_Five_in(range);
					delete math;
					if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z >= map1->Model_data[ground_model].pos.z)
					{
						//rangex = (-D3DX_PI) + abs(rangex);
						rangex = (-D3DX_PI/2) - abs(rangex);

					}
					else if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = -abs(rangex);

					}
					else if (pos_destine.x < map1->Model_data[ground_model].pos.x&&pos_destine.z >= map1->Model_data[ground_model].pos.z)
					{
						//rangex = D3DX_PI - abs(rangex);
						rangex = (D3DX_PI / 2) + abs(rangex);
					}
					else if (pos_destine.x < map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = abs(rangex);
					}
					else if (pos_destine.x == map1->Model_data[ground_model].pos.x&&pos_destine.z > map1->Model_data[ground_model].pos.z)
					{
						rangex = D3DX_PI;
					}
					else if (pos_destine.x > map1->Model_data[ground_model].pos.x&&pos_destine.z < map1->Model_data[ground_model].pos.z)
					{
						rangex = 0;
					}
					rangex = map1->Model_data[ground_model].rot.y - rangex;
				}
				if (spd < 1)
				{
					//rot.y += D3DX_PI / 100;
					pos_destine.x = (map1->Model_data[ground_model].pos.x - (kyorix * sinf(map1->Model_data[ground_model].rot.y - rangex)));
					pos_destine.z = (map1->Model_data[ground_model].pos.z - (kyorix * cosf(map1->Model_data[ground_model].rot.y - rangex)));
				}

				bool touch_test = false;
				for (int j = 0; j < map1->Model_data[ground_model].index_max; j++)
				{
					touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[ground_model].collider_index[j]]);
					if (touch_test == true)break;
				}

				if (touch_test == true)
				{
					D3DXVECTOR3 HitPosition;
					D3DXVECTOR3 Normal;
					touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
					if (touch_test == true)
					{
						if (HitPosition.y >= (pos_destine.y))
						{
							if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
							{
								pos_destine.y = HitPosition.y;
								//ground_y = HitPosition.y;
								moveway_xyz.y = pos_destine.y - pos.y;
								ground_model = ground_model;
								touch_ans = true;
							}
							else
							{
								touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos, 10);
								if (touch_test == true)
								{
									if (HitPosition.y <= (pos.y))
									{
										pos_destine.y = HitPosition.y;
										//ground_y = HitPosition.y;
										moveway_xyz.y = pos_destine.y - pos.y;
										ground_model = ground_model;
										touch_ans = true;

									}
								}
								else
								{
									touch_ans = false;
									ground_model = -1;
								}
							}
						}

					}
				}
			}
			
		}
		if (ground_model == 30)
		{
			pos_destine.z += 2 ;
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[ground_model].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[ground_model].collider_index[j]]);
				if (touch_test == true)break;
			}

			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							//ground_y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							ground_model = ground_model;
							touch_ans = true;
						}
						else
						{
							touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									//ground_y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									ground_model = ground_model;
									touch_ans = true;

								}
							}
							else
							{
								touch_ans = false;
								ground_model = -1;
							}
						}
					}

				}
			}
		}
		if (ground_model == 31)
		{
			pos_destine.z -= 4;
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[ground_model].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[ground_model].collider_index[j]]);
				if (touch_test == true)break;
			}

			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							//ground_y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							ground_model = ground_model;
							touch_ans = true;
						}
						else
						{
							touch_test = this->Character_RayHitGround(ground_model, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									//ground_y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									ground_model = ground_model;
									touch_ans = true;

								}
							}
							else
							{
								touch_ans = false;
								ground_model = -1;
							}
						}
					}

				}
			}
		}
		Update_Collider(pos_destine, rot);
		//移動後のPOSを修正
		int touch_num = 0;
		for (int i = 0; i < map1->Model_num; i++)
		{
			if (map1->Model_data[i].use != true)continue;
			if (i == 16)continue;
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori.y += (collider_wxhylz.y / 2);
			move_kyori = map1->Model_data[i].collider_pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			float kyori_p = sqrtf((collider_wxhylz.x*collider_wxhylz.x) + (collider_wxhylz.z + collider_wxhylz.z) + (collider_wxhylz.y + collider_wxhylz.y));
			//if model中心点とplayerposの距離　< modelのr+playerのr  =>BBC判定に進む
			if (kyori > (kyori_p + map1->Model_data[i].collider_radius))continue;
			bool ans_wall[6];
			for (int j = 0; j < 6; j++)
			{
				ans_wall[j] = false;
			}
			//playerの地面判定のcolliderを判定
			for (int j = 0; j < map1->Model_data[i].index_max; j++)
			{
				//Model_data[i]全てのcolliderを判定
				//map1->Model_data[i].collider_index[j]=> stageのmodel第　i　番号の第　ｊ　番号collider
				if (ans_wall[top_Collider] == false)ans_wall[top_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_top]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (ans_wall[down_Collider] == false)ans_wall[down_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (ans_wall[front_Collider] == false)ans_wall[front_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_front]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (ans_wall[behind_Collider] == false)ans_wall[behind_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_behind]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (ans_wall[left_Collider] == false)ans_wall[left_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_left]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (ans_wall[right_Collider] == false)ans_wall[right_Collider]
					= collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_right]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
			}
			//もしカメラのcollider当たったらモデルが透明化
			if (ans_wall[0] == true || ans_wall[1] == true || ans_wall[2] == true || ans_wall[3] == true || ans_wall[4] == true || ans_wall[5] == true)
			{
				//XYZ_pos 修正===============================================================================
				//計算用変数設定
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				D3DXVECTOR3 pos_math = pos_destine;
				float top_y = pos_destine.y + collider_wxhylz.y;
				float test_posy = pos_destine.y + collider_wxhylz.y;
				pos_math.y = test_posy;
				D3DXVECTOR3 move_way = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				bool ans_top = false;
				bool ans_down = false;
				D3DXVECTOR3 Normal_top;
				D3DXVECTOR3 Normal_down;
				D3DXVECTOR3 HitPosition_top = pos_destine;
				D3DXVECTOR3 HitPosition_down = pos_destine;
				//頭から足までRAYCAST
				for (int j = 0; j < 9; j++)
				{
					bool ans_top_part = false;
					pos_math = pos_destine;
					pos_math.y += collider_wxhylz.y ;
					float R = sqrtf(((collider_wxhylz.x / 2)*(collider_wxhylz.x / 2)) + ((collider_wxhylz.z / 2)* (collider_wxhylz.z / 2)));
					switch (j)
					{
					case 1:
						pos_math.x -= sinf((rot.y))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y))*(collider_wxhylz.z / 2);
						break;
					case 2:
						pos_math.x -= sinf((rot.y - (D3DX_PI / 4)))*(R);
						pos_math.z -= cosf((rot.y - (D3DX_PI / 4)))*(R);
						break;
					case 3:
						pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
						break;
					case 4:
						pos_math.x -= sinf((rot.y - ((D3DX_PI * 3) / 4)))*(R);
						pos_math.z -= cosf((rot.y - ((D3DX_PI * 3) / 4)))*(R);
						break;
					case 5:
						pos_math.x -= sinf((rot.y - (D3DX_PI)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y - (D3DX_PI)))*(collider_wxhylz.z / 2);
						break;
					case 6:
						pos_math.x -= sinf((rot.y + (D3DX_PI / 4)))*(R);
						pos_math.z -= cosf((rot.y + (D3DX_PI / 4)))*(R);
						break;
					case 7:
						pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
						break;
					case 8:
						pos_math.x -= sinf((rot.y + ((D3DX_PI * 3) / 4)))*(R);
						pos_math.z -= cosf((rot.y + ((D3DX_PI * 3) / 4)))*(R);
						break;
					}
					ans_top_part = this->Character_RayHitGround(i, &HitPosition, &Normal, pos_math, 0);
					if (ans_top_part == true)
					{
						if (HitPosition.y > pos_destine.y)
						{
							if (HitPosition.y < top_y)
							{
								ans_top = true;
								top_y = HitPosition.y;
								HitPosition_top = HitPosition;
								Normal_top = Normal;
							}
						}
						else
						{
							ans_top_part = false;
						}
					}
				}
				top_y = pos_destine.y + collider_wxhylz.y;
				//足から頭までRAYCAST
				for (int j = 0; j < 9; j++)
				{
					bool ans_down_part = false;
					pos_math = pos_destine;
					float R = sqrtf(((collider_wxhylz.x / 2)*(collider_wxhylz.x / 2)) + ((collider_wxhylz.z / 2)* (collider_wxhylz.z / 2)));
					switch (j)
					{
					case 1:
						pos_math.x -= sinf((rot.y))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y))*(collider_wxhylz.z / 2);
						break;
					case 2:
						pos_math.x -= sinf((rot.y - (D3DX_PI / 4)))*(R);
						pos_math.z -= cosf((rot.y - (D3DX_PI / 4)))*(R);
						break;
					case 3:
						pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
						break;
					case 4:
						pos_math.x -= sinf((rot.y - ((D3DX_PI * 3) / 4)))*(R);
						pos_math.z -= cosf((rot.y - ((D3DX_PI * 3) / 4)))*(R);
						break;
					case 5:
						pos_math.x -= sinf((rot.y - (D3DX_PI)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y - (D3DX_PI)))*(collider_wxhylz.z / 2);
						break;
					case 6:
						pos_math.x -= sinf((rot.y + (D3DX_PI / 4)))*(R);
						pos_math.z -= cosf((rot.y + (D3DX_PI / 4)))*(R);
						break;
					case 7:
						pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
						pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
						break;
					case 8:
						pos_math.x -= sinf((rot.y + ((D3DX_PI * 3) / 4)))*(R);
						pos_math.z -= cosf((rot.y + ((D3DX_PI * 3) / 4)))*(R);
						break;
					}
					ans_down_part=this->Character_RayHitTop(i, &HitPosition, &Normal, pos_math);
					if (ans_down_part == true)
					{
						if (HitPosition.y < (pos_destine.y + collider_wxhylz.y))
						{
							ans_down = true;
							if (HitPosition.y < top_y)
							{
								top_y = HitPosition.y;
								Normal_down = Normal;
								HitPosition_down = HitPosition;
							}
						}
					}
				}
				//RAYCAST用y_pos"test_posy"を判定
				if (ans_down == false)
				{
					test_posy = pos_destine.y;
				}
				else
				{
					if (ans_top == true)
					{
						test_posy = HitPosition_top.y;
						D3DXVECTOR3 aa, bb;
						bb = pos_destine;
						bb.y = test_posy;
						bb = HitPosition_top - bb;
						aa = Normal_top;
						aa.y = 0.0f;
						D3DXVec3Normalize(&aa, &aa);
						Calculate* math = new Calculate();
						float cc = math->dotProduct(&aa, &bb);
						delete math;
						if (cc >= 0)
						{
							bool test = false;
							for (int k = 0; k < 3; k++)
							{
								for (int m = 0; m < 3; m++)
								{
									pos_math = pos;
									switch (m)
									{
									case 0:
										pos_math.y = test_posy;
										break;
									case 1:
										pos_math.y = test_posy - ((HitPosition_top.y - HitPosition_down.y) / 4);
										break;
									case 2:
										pos_math.y = test_posy - ((HitPosition_top.y - HitPosition_down.y) / 3);
										break;
									}

									if (ans_wall[front_Collider] == true && ans_wall[behind_Collider] == false)
									{
										move_way.x = (-sinf(rot.y))*(collider_wxhylz.x * 4);
										move_way.z = (-cosf(rot.y))*(collider_wxhylz.x * 4);
									}
									else if (ans_wall[front_Collider] == false && ans_wall[behind_Collider] == true)
									{
										move_way.x = (-sinf(rot.y + D3DX_PI))*(collider_wxhylz.x * 4);
										move_way.z = (-cosf(rot.y + D3DX_PI))*(collider_wxhylz.x * 4);
									}
									switch (k)
									{
									case 1:
										pos_math.x -= sinf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.x / 2);
										pos_math.z -= cosf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.z / 2);
										break;
									case 2:
										pos_math.x -= sinf(rot.y - (D3DX_PI / 2))*(collider_wxhylz.x / 2);
										pos_math.z -= cosf(rot.y - (D3DX_PI / 2))*(collider_wxhylz.z / 2);
										break;
									}
									test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
									if (test == true)
									{
										bb = Normal;
										bb.y = 0.0f;
										D3DXVec3Normalize(&bb, &bb);
										test_posy = HitPosition.y;
										break;
									}
								}
								if (test == true)
								{
									break;
								}
							}
							if (test == true)
							{
								moveway_xyz.x += bb.x*spd;
								moveway_xyz.z += bb.z*spd;
								pos_destine = pos + moveway_xyz;
							}
							else
							{
								moveway_xyz.x += aa.x*spd;
								moveway_xyz.z += aa.z*spd;
								pos_destine = pos + moveway_xyz;
							}
						}
						else
						{
							moveway_xyz.x += aa.x*spd;
							moveway_xyz.z += aa.z*spd;
							pos_destine = pos + moveway_xyz;
						}
					}
					else
					{
						bool test = false;
						for (int k = 0; k < 3; k++)
						{
							pos_math = pos_destine;
							pos_math.y = pos_destine.y + collider_wxhylz.y;
							if (ans_wall[front_Collider] == true && ans_wall[behind_Collider] == false)
							{
								move_way.x = (-sinf(rot.y))*(collider_wxhylz.x * 4);
								move_way.z = (-cosf(rot.y))*(collider_wxhylz.x * 4);
							}
							else if (ans_wall[front_Collider] == false && ans_wall[behind_Collider] == true)
							{
								move_way.x = (-sinf(rot.y + D3DX_PI))*(collider_wxhylz.x * 4);
								move_way.z = (-cosf(rot.y + D3DX_PI))*(collider_wxhylz.x * 4);
							}
							switch (k)
							{
							case 1:
								pos_math.x -= sinf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.x / 2);
								pos_math.z -= cosf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.z / 2);
								break;
							case 2:
								pos_math.x -= sinf(rot.y - (D3DX_PI / 2))*(collider_wxhylz.x / 2);
								pos_math.z -= cosf(rot.y - (D3DX_PI / 2))*(collider_wxhylz.z / 2);
								break;
							}
							test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
							if (test == true)
							{
								break;
							}
						}
						if (test == false)
						{
							test_posy = HitPosition_down.y;
						}
						else
						{
							test_posy = pos_destine.y + collider_wxhylz.y;
						}
					}
				}
				//頭が当っているかどうかを判定
				if (ans_top == false && ans_down == true && HitPosition_down.y <= (pos_destine.y + collider_wxhylz.y))
				{
					bool test = false;
					for (int k = 0; k < 3; k++)
					{

						pos_math = pos_destine;
						pos_math.y = pos_destine.y + collider_wxhylz.y;
						if (ans_wall[front_Collider] == true && ans_wall[behind_Collider] == false)
						{
							move_way.x = (-sinf(rot.y))*(collider_wxhylz.x / 2);
							move_way.z = (-cosf(rot.y))*(collider_wxhylz.x / 2);
						}
						else if (ans_wall[front_Collider] == false && ans_wall[behind_Collider] == true)
						{
							move_way.x = (-sinf(rot.y + D3DX_PI))*(collider_wxhylz.x / 2);
							move_way.z = (-cosf(rot.y + D3DX_PI))*(collider_wxhylz.x / 2);
						}
						else
						{
							if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
							{
								move_way.x = (-sinf(rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
								move_way.z = (-cosf(rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
							}
							else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
							{
								move_way.x = (-sinf(rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
								move_way.z = (-cosf(rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
							}
						}
						switch (k)
						{
						case 1:
							pos_math.x -= sinf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.x / 2);
							pos_math.z -= cosf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.z / 2);
							break;
						case 2:
							pos_math.x -= sinf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.x / 2);
							pos_math.z -= cosf(rot.y + (D3DX_PI / 2))*(collider_wxhylz.z / 2);
							break;
						}
						test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						if (test == true)
						{
							break;
						}
					}
					if (test == false)
					{
						touch_top_ans = true;
						if (spd_y > 0)
						{
							spd_y = 0;
						}
					}

				}
				//決めたY_POSをRAYCAST
				if (ans_wall[front_Collider] == true && ans_wall[behind_Collider] == false)
				{
					pos_math = pos_destine;
					pos_math.y = test_posy;
					//先ずは当たったMODELの法線を求める
					bool ans_wall_test = false;
					move_way.x = (-sinf(rot.y))*(collider_wxhylz.x * 4);
					move_way.z = (-cosf(rot.y))*(collider_wxhylz.x * 4);
					ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
					if (ans_wall_test == true)
					{
						
						//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
						pos_math = pos_destine;
						pos_math.y = test_posy;
						D3DXVECTOR3 HitPosition_test;
						D3DXVECTOR3 Normal_test;
						move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
						move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
						pos_math.y = test_posy;
						ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						if (ans_wall_test == true)
						{
							touch_num++;
							pos_destine.x = HitPosition.x + (collider_wxhylz.x / 2)*Normal.x;
							pos_destine.z = HitPosition.z + (collider_wxhylz.x / 2)*Normal.z;
							move_way = pos_destine - pos;
							D3DXVec3Normalize(&move_way, &move_way);
							Calculate* math = new Calculate();
							math->Four_out_Five_in(&move_way);
							delete math;
							pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
							pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
							pos_math = pos_destine;
							pos_math.y = test_posy;
							move_way = Normal * (-1)*(collider_wxhylz.x / 2);
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_wall_test == true)
							{
								pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
							}
							moveway_xyz = pos_destine - pos;
							
						}
					}
					else
					{
						//当っていないの場合は他のPOSからRAYCAST
						if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
						{
							move_way.x = (-sinf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.x);
							move_way.z = (-cosf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.z);
						}
						else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
						{
							move_way.x = (-sinf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.x);
							move_way.z = (-cosf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.z);
						}
						
						ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						if (ans_wall_test == true)
						{
							
							pos_math = pos_destine;
							pos_math.y = test_posy;
							D3DXVECTOR3 HitPosition_test;
							D3DXVECTOR3 Normal_test;
							move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
							move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_wall_test == true)
							{
								touch_num++;
								if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
								{
									move_way.x = (-sinf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.x);
									move_way.z = (-cosf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.z);
								}
								else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
								{
									move_way.x = (-sinf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.x);
									move_way.z = (-cosf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.z);
								}
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								move_way = pos_math - pos;
								move_way.y = 0.0f;
								D3DXVec3Normalize(&move_way, &move_way);
								pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
								pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);

								pos_math = pos_destine;
								pos_math.y = test_posy;
								move_way = Normal * (-1)*(collider_wxhylz.x / 2);
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_wall_test == true)
								{
									pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								}
								moveway_xyz = pos_destine - pos;
								
							}
							else
							{
								//当っていないの場合は他のPOSからRAYCAST
								if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
								{
									pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
									pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
								}
								else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
								{
									pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
									pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
								}
								move_way.x = (-sinf(rot.y))*(collider_wxhylz.x);
								move_way.z = (-cosf(rot.y))*(collider_wxhylz.z);
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_wall_test == true)
								{
									D3DXVECTOR3 pos_math2 = pos_math;
									pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
									move_way = pos_math - pos_math2;
									pos_destine.x += move_way.x;
									pos_destine.z += move_way.z;
									moveway_xyz = pos_destine - pos;
									
								}
							}
						}
						else
						{
							//当っていないの場合は他のPOSからRAYCAST
							if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
							{
								move_way.x = (-sinf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.x);
								move_way.z = (-cosf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.z);
							}
							else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
							{
								move_way.x = (-sinf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.x);
								move_way.z = (-cosf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.z);
							}
							//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
							if (ans_wall_test == true)
							{
								ans_wall_test = false;
								D3DXVECTOR3 HitPosition_test;
								D3DXVECTOR3 Normal_test;
								move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
								move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_wall_test == true)
								{
									touch_num++;
									pos_math = pos_destine;
									pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
									move_way = pos_math - pos;
									move_way.y = 0;
									D3DXVec3Normalize(&move_way, &move_way);
									pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
									pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
									pos_math = pos_destine;
									pos_math.y = test_posy;
									move_way = Normal * (-1)*(collider_wxhylz.x / 2);
									ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									if (ans_wall_test == true)
									{
										pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
										pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
									}
									moveway_xyz = pos_destine - pos;
									
								}
								else
								{
									//当っていないの場合は他のPOSからRAYCAST
									if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
									{
										pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x/2);
										pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z/2);
									}
									else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
									{
										pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x/2);
										pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z/2);
									}
									move_way.x = (-sinf(rot.y))*(collider_wxhylz.x);
									move_way.z = (-cosf(rot.y))*(collider_wxhylz.z);
									ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									if (ans_wall_test == true)
									{
										touch_num++;
										D3DXVECTOR3 pos_math2= pos_math;
										pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
										pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
										move_way = pos_math - pos_math2;
										pos_destine.x += move_way.x;
										pos_destine.z += move_way.z;
										moveway_xyz = pos_destine - pos;
										
									}
								}
							}
							
						}
					}
				}
				else if (ans_wall[behind_Collider] == true && ans_wall[front_Collider] == false)
				{
					pos_math = pos_destine;
					pos_math.y = test_posy;
					move_way.x = (-sinf(rot.y + D3DX_PI))*(collider_wxhylz.x * 2);
					move_way.z = (-cosf(rot.y + D3DX_PI))*(collider_wxhylz.x * 2);
					bool ans_wall_test = false;
					ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
					if (ans_wall_test == true)
					{
						
						D3DXVECTOR3 HitPosition_test;
						D3DXVECTOR3 Normal_test;
						move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
						move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
						ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						if (ans_wall_test == true)
						{
							touch_num++;
							D3DXVECTOR3 length_test = pos_math - HitPosition;
							float length = D3DXVec3Length(&length_test);
							length_test = pos_math - HitPosition_test;
							float length_2 = D3DXVec3Length(&length_test);
							length = (((collider_wxhylz.x / 2)*length) / length_2) - length;
							move_way = moveway_xyz;
							move_way.y = 0.0f;
							D3DXVec3Normalize(&move_way, &move_way);
							pos_destine.x = pos_destine.x + (length*move_way.x);
							pos_destine.z = pos_destine.z + (length*move_way.z);
							pos_math = pos_destine;
							pos_math.y = test_posy;
							move_way = Normal * (-1)*(collider_wxhylz.x / 2);
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_wall_test == true)
							{
								pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
							}
							moveway_xyz = pos_destine - pos;
							
						}
					}
					else
					{
						//if建物の角度は45度以下があるならばans_wall[left_Collider]とans_wall[right_Collider]は false の判定は追加する
						if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
						{
							move_way.x = (-sinf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.x / 2);
							move_way.z = (-cosf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.z / 2);
						}
						else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
						{
							move_way.x = (-sinf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.x / 2);
							move_way.z = (-cosf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.z / 2);
						}
						ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						if (ans_wall_test == true)
						{
							
							ans_wall_test = false;
							D3DXVECTOR3 HitPosition_test;
							D3DXVECTOR3 Normal_test;
							move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
							move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
							pos_math = pos_destine;
							pos_math.y = test_posy;
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_wall_test == true)
							{
								touch_num++;
								pos_math = pos_destine;
								pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								move_way = pos_math - pos;
								move_way.y = 0.0f;
								D3DXVec3Normalize(&move_way, &move_way);
								pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
								pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
								pos_math = pos_destine;
								pos_math.y = test_posy;
								move_way = Normal * (-1)*(collider_wxhylz.x / 2);
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_wall_test == true)
								{
									pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								}
								moveway_xyz = pos_destine - pos;
								
							}
						}
						else
						{
							//当っていないの場合は他のPOSからRAYCAST
							pos_math = pos_destine;
							pos_math.y = test_posy;
							if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
							{
								move_way.x = (-sinf((rot.y - ((D3DX_PI * 3) / 4))))*(collider_wxhylz.x / 2);
								move_way.z = (-cosf((rot.y - ((D3DX_PI * 3) / 4))))*(collider_wxhylz.z / 2);
							}
							else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
							{
								move_way.x = (-sinf((rot.y + ((D3DX_PI * 3) / 4))))*(collider_wxhylz.x / 2);
								move_way.z = (-cosf((rot.y + ((D3DX_PI * 3) / 4))))*(collider_wxhylz.z / 2);
							}
							//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
							D3DXVECTOR3 HitPosition_test;
							D3DXVECTOR3 Normal_test;
							move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
							move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
							ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_wall_test == true)
							{
								touch_num++;
								pos_math = pos_destine;
								pos_math.x = HitPosition.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_math.z = HitPosition.z + (collider_wxhylz.x / 2)*Normal.z;
								move_way = pos_math - pos;
								move_way.y = 0.0f;
								D3DXVec3Normalize(&move_way, &move_way);
								pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
								pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
								pos_math = pos_destine;
								pos_math.y = test_posy;
								move_way = Normal * (-1)*(collider_wxhylz.x / 2);
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_wall_test == true)
								{
									pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								}
								moveway_xyz = pos_destine - pos;
								
							}
						}

					}
				}
				else
				{
					if (i == ground_model && ans_wall[behind_Collider] == true && ans_wall[front_Collider] == true)
					{
						bool ans_front = false;
						//bool ans_behind = false;
						pos_math = pos_destine;
						pos_math.y = test_posy;
						//先ずは当たったMODELの法線を求める
						move_way.x = (-sinf(rot.y))*(collider_wxhylz.x * 4);
						move_way.z = (-cosf(rot.y))*(collider_wxhylz.x * 4);
						ans_front = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
 						if (ans_front == true)
						{
							touch_num++;
							//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
							pos_math = pos_destine;
							pos_math.y = test_posy;
							D3DXVECTOR3 HitPosition_test;
							D3DXVECTOR3 Normal_test;
							move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
							move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
							pos_math.y = test_posy;
							ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
							if (ans_front == true)
							{
								pos_destine.x = HitPosition.x + (collider_wxhylz.x / 2)*Normal.x;
								pos_destine.z = HitPosition.z + (collider_wxhylz.x / 2)*Normal.z;
								move_way = pos_destine - pos;
								D3DXVec3Normalize(&move_way, &move_way);
								Calculate* math = new Calculate();
								math->Four_out_Five_in(&move_way);
								delete math;
								pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
								pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
								pos_math = pos_destine;
								pos_math.y = test_posy;
								move_way = Normal * (-1)*(collider_wxhylz.x / 2);
								ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_front == true)
								{
									pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
								}
								moveway_xyz = pos_destine - pos;

							}
						}
						else
						{
							//当っていないの場合は他のPOSからRAYCAST
							if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
							{
								move_way.x = (-sinf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.x);
								move_way.z = (-cosf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.z);
							}
							else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
							{
								move_way.x = (-sinf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.x);
								move_way.z = (-cosf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.z);
							}

							ans_front = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
							if (ans_front == true)
							{
								touch_num++;
								pos_math = pos_destine;
								pos_math.y = test_posy;
								D3DXVECTOR3 HitPosition_test;
								D3DXVECTOR3 Normal_test;
								move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
								move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
								ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
								if (ans_front == true)
								{
									if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
									{
										move_way.x = (-sinf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.x);
										move_way.z = (-cosf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.z);
									}
									else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
									{
										move_way.x = (-sinf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.x);
										move_way.z = (-cosf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.z);
									}
									ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
									pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
									move_way = pos_math - pos;
									move_way.y = 0.0f;
									D3DXVec3Normalize(&move_way, &move_way);
									pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
									pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);

									pos_math = pos_destine;
									pos_math.y = test_posy;
									move_way = Normal * (-1)*(collider_wxhylz.x / 2);
									ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									if (ans_front == true)
									{
										pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
										pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
									}
									moveway_xyz = pos_destine - pos;

								}
								else
								{
									//当っていないの場合は他のPOSからRAYCAST
									if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
									{
										pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
										pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
									}
									else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
									{
										pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
										pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
									}
									move_way.x = (-sinf(rot.y))*(collider_wxhylz.x);
									move_way.z = (-cosf(rot.y))*(collider_wxhylz.z);
									ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									if (ans_front == true)
									{
										D3DXVECTOR3 pos_math2 = pos_math;
										pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
										pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
										move_way = pos_math - pos_math2;
										pos_destine.x += move_way.x;
										pos_destine.z += move_way.z;
										moveway_xyz = pos_destine - pos;

									}
								}
							}
							else
							{
								//当っていないの場合は他のPOSからRAYCAST
								if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
								{
									move_way.x = (-sinf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.x);
									move_way.z = (-cosf((rot.y - (D3DX_PI / 4))))*(collider_wxhylz.z);
								}
								else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
								{
									move_way.x = (-sinf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.x);
									move_way.z = (-cosf((rot.y + (D3DX_PI / 4))))*(collider_wxhylz.z);
								}
								//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
								ans_front = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
								if (ans_front == true)
								{
									touch_num++;
									ans_front = false;
									D3DXVECTOR3 HitPosition_test;
									D3DXVECTOR3 Normal_test;
									move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
									move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
									ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
									if (ans_front == true)
									{
										pos_math = pos_destine;
										pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
										pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
										move_way = pos_math - pos;
										move_way.y = 0;
										D3DXVec3Normalize(&move_way, &move_way);
										pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
										pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
										pos_math = pos_destine;
										pos_math.y = test_posy;
										move_way = Normal * (-1)*(collider_wxhylz.x / 2);
										ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
										if (ans_front == true)
										{
											pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
											pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
										}
										moveway_xyz = pos_destine - pos;

									}
									else
									{
										//当っていないの場合は他のPOSからRAYCAST
										if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
										{
											pos_math.x -= sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
											pos_math.z -= cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
										}
										else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
										{
											pos_math.x -= sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
											pos_math.z -= cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z / 2);
										}
										move_way.x = (-sinf(rot.y))*(collider_wxhylz.x);
										move_way.z = (-cosf(rot.y))*(collider_wxhylz.z);
										ans_front = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
										if (ans_front == true)
										{
											D3DXVECTOR3 pos_math2 = pos_math;
											pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
											pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
											move_way = pos_math - pos_math2;
											pos_destine.x += move_way.x;
											pos_destine.z += move_way.z;
											moveway_xyz = pos_destine - pos;

										}
									}
								}

							}
						}
						//if (touch_num==0)
						//{
						//	pos_math = pos_destine;
						//	pos_math.y = test_posy;
						//	move_way.x = (-sinf(rot.y + D3DX_PI))*(collider_wxhylz.x * 2);
						//	move_way.z = (-cosf(rot.y + D3DX_PI))*(collider_wxhylz.x * 2);
						//	bool ans_wall_test = false;
						//	ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						//	if (ans_wall_test == true)
						//	{
						//		touch_num++;
						//		D3DXVECTOR3 HitPosition_test;
						//		D3DXVECTOR3 Normal_test;
						//		move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
						//		move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
						//		ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//		if (ans_wall_test == true)
						//		{
						//			D3DXVECTOR3 length_test = pos_math - HitPosition;
						//			float length = D3DXVec3Length(&length_test);
						//			length_test = pos_math - HitPosition_test;
						//			float length_2 = D3DXVec3Length(&length_test);
						//			length = (((collider_wxhylz.x / 2)*length) / length_2) - length;
						//			move_way = moveway_xyz;
						//			move_way.y = 0.0f;
						//			D3DXVec3Normalize(&move_way, &move_way);
						//			pos_destine.x = pos_destine.x + (length*move_way.x);
						//			pos_destine.z = pos_destine.z + (length*move_way.z);
						//			pos_math = pos_destine;
						//			pos_math.y = test_posy;
						//			move_way = Normal * (-1)*(collider_wxhylz.x / 2);
						//			ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//			if (ans_wall_test == true)
						//			{
						//				pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
						//				pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
						//			}
						//			moveway_xyz = pos_destine - pos;

						//		}
						//	}
						//	else
						//	{
						//		//if建物の角度は45度以下があるならばans_wall[left_Collider]とans_wall[right_Collider]は false の判定は追加する
						//		if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
						//		{
						//			move_way.x = (-sinf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.x / 2);
						//			move_way.z = (-cosf((rot.y - (D3DX_PI / 2))))*(collider_wxhylz.z / 2);
						//		}
						//		else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
						//		{
						//			move_way.x = (-sinf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.x / 2);
						//			move_way.z = (-cosf((rot.y + (D3DX_PI / 2))))*(collider_wxhylz.z / 2);
						//		}
						//		ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						//		if (ans_wall_test == true)
						//		{
						//			touch_num++;
						//			ans_wall_test = false;
						//			D3DXVECTOR3 HitPosition_test;
						//			D3DXVECTOR3 Normal_test;
						//			move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
						//			move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
						//			pos_math = pos_destine;
						//			pos_math.y = test_posy;
						//			ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//			if (ans_wall_test == true)
						//			{
						//				pos_math = pos_destine;
						//				pos_math.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
						//				pos_math.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
						//				move_way = pos_math - pos;
						//				move_way.y = 0.0f;
						//				D3DXVec3Normalize(&move_way, &move_way);
						//				pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
						//				pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
						//				pos_math = pos_destine;
						//				pos_math.y = test_posy;
						//				move_way = Normal * (-1)*(collider_wxhylz.x / 2);
						//				ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//				if (ans_wall_test == true)
						//				{
						//					pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
						//					pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
						//				}
						//				moveway_xyz = pos_destine - pos;

						//			}
						//		}
						//		else
						//		{
						//			//当っていないの場合は他のPOSからRAYCAST
						//			pos_math = pos_destine;
						//			pos_math.y = test_posy;
						//			if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
						//			{
						//				move_way.x = (-sinf((rot.y - ((D3DX_PI * 3) / 4))))*(collider_wxhylz.x / 2);
						//				move_way.z = (-cosf((rot.y - ((D3DX_PI * 3) / 4))))*(collider_wxhylz.z / 2);
						//			}
						//			else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
						//			{
						//				move_way.x = (-sinf((rot.y + ((D3DX_PI * 3) / 4))))*(collider_wxhylz.x / 2);
						//				move_way.z = (-cosf((rot.y + ((D3DX_PI * 3) / 4))))*(collider_wxhylz.z / 2);
						//			}
						//			//法線をもらった後、MODELはキャラの半径の中がどうかを確認する
						//			ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						//			D3DXVECTOR3 HitPosition_test;
						//			D3DXVECTOR3 Normal_test;
						//			move_way.x = (-Normal.x)*(collider_wxhylz.x / 2);
						//			move_way.z = (-Normal.z)*(collider_wxhylz.x / 2);
						//			ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//			if (ans_wall_test == true)
						//			{
						//				touch_num++;
						//				pos_math = pos_destine;
						//				pos_math.x = HitPosition.x + (collider_wxhylz.x / 2)*Normal.x;
						//				pos_math.z = HitPosition.z + (collider_wxhylz.x / 2)*Normal.z;
						//				move_way = pos_math - pos;
						//				move_way.y = 0.0f;
						//				D3DXVec3Normalize(&move_way, &move_way);
						//				pos_destine.x = pos.x + (((float)fabs(spd))*move_way.x);
						//				pos_destine.z = pos.z + (((float)fabs(spd))*move_way.z);
						//				pos_math = pos_destine;
						//				pos_math.y = test_posy;
						//				move_way = Normal * (-1)*(collider_wxhylz.x / 2);
						//				ans_wall_test = this->Character_RayHitWall(i, &HitPosition_test, &Normal_test, pos_math, move_way);
						//				if (ans_wall_test == true)
						//				{
						//					pos_destine.x = HitPosition_test.x + (collider_wxhylz.x / 2)*Normal.x;
						//					pos_destine.z = HitPosition_test.z + (collider_wxhylz.x / 2)*Normal.z;
						//				}
						//				moveway_xyz = pos_destine - pos;

						//			}
						//		}

						//	}
						//}
					}
					else
					{
						pos_math = pos_destine;
						pos_math.y = test_posy;
						if (ans_wall[left_Collider] == true && ans_wall[right_Collider] == false)
						{
							move_way.x = -sinf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.x);
							move_way.z = -cosf((rot.y - (D3DX_PI / 2)))*(collider_wxhylz.z);
						}
						else if (ans_wall[right_Collider] == true && ans_wall[left_Collider] == false)
						{
							move_way.x = -sinf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.x);
							move_way.z = -cosf((rot.y + (D3DX_PI / 2)))*(collider_wxhylz.z);
						}
						bool ans_wall_test = false;
						ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
						if (ans_wall_test == true)
						{
							if (abs(HitPosition.x) < 10000 && abs(HitPosition.z) < 10000)
							{
								touch_num++;
								move_way = -Normal;
								ans_wall_test = this->Character_RayHitWall(i, &HitPosition, &Normal, pos_math, move_way);
								move_way = Normal;
								pos_destine.x = HitPosition.x + ((move_way.x)*(collider_wxhylz.z));
								pos_destine.z = HitPosition.z + ((move_way.z)*(collider_wxhylz.z));
							}
							

						}
					}
					
				}
				moveway_xyz = pos_destine - pos;
			}
		}
		if (touch_num > 0)
		{
			if (beAttack == true)
			{
				beAttack = false;
				spd = 0;
			}
			if (touch_num > 1)
			{
				pos_destine.x = pos.x;
				pos_destine.z = pos.z;
				moveway_xyz = pos_destine - pos;
			}
		}
		//y_pos 再修正
		for (int i = 0; i < map1->Model_num; i++)
		{
			if (map1->Model_data[i].use != true)continue;
			D3DXVECTOR3 move_kyori = collider->g_Collider3D[collider_c[Character_collider_stand]].pos;
			move_kyori.y += (collider_wxhylz.y / 2);
			//move_kyori = map1->Model_data[i].pos - move_kyori;
			move_kyori = map1->Model_data[i].collider_pos - move_kyori;
			float kyori = D3DXVec3Length(&move_kyori);
			float kyori_p = sqrtf((collider_wxhylz.x*collider_wxhylz.x) + (collider_wxhylz.z + collider_wxhylz.z) + (collider_wxhylz.y + collider_wxhylz.y));
			//if model中心点とplayerposの距離　< modelのr+playerのr  =>BBC判定に進む
			if (kyori > (kyori_p + map1->Model_data[i].collider_radius))continue;
			bool touch_test = false;
			for (int j = 0; j < map1->Model_data[i].index_max; j++)
			{
				touch_test = collider->CheckHitOBB(&collider->g_Collider3D[collider_c[Character_collider_stand]], &stage_collider->g_Collider3D[map1->Model_data[i].collider_index[j]]);
				if (touch_test == true)break;
			}

			if (touch_test == true)
			{
				D3DXVECTOR3 HitPosition;
				D3DXVECTOR3 Normal;
				touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos_destine, (collider_wxhylz.y));
				if (touch_test == true)
				{
					if (HitPosition.y >= (pos_destine.y))
					{
						if (HitPosition.y < (pos_destine.y + (collider_wxhylz.y / 4)))
						{
							pos_destine.y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							touch_ans = true;
							ground_model = i;
						}
						else
						{
							touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos, 10);
							if (touch_test == true)
							{
								if (HitPosition.y <= (pos.y))
								{
									pos_destine.y = HitPosition.y;
									moveway_xyz.y = pos_destine.y - pos.y;
									touch_ans = true;
									ground_model = i;
								}
							}
						}
					}
					else
					{
						if (HitPosition.y > (pos_destine.y - (collider_wxhylz.y / 8)) && HitPosition.y >= 0 && spd_y <= 0)
						{
							pos_destine.y = HitPosition.y;
							moveway_xyz.y = pos_destine.y - pos.y;
							touch_ans = true;
							ground_model = i;

						}
					}
				}
				else
				{
					touch_test = this->Character_RayHitGround(i, &HitPosition, &Normal, pos, 10);
					if (touch_test == true)
					{
						if (HitPosition.y <= (pos.y))
						{
							if (spd_y < -20.0f)
							{
								pos_destine.y = HitPosition.y;
								moveway_xyz.y = pos_destine.y - pos.y;
								ground_model = i;
								touch_ans = true;
							}

						}
					}
				}
			}
		}
	}
	void Character::Update_Collider(D3DXVECTOR3 pos_in, D3DXVECTOR3 rot_in)
	{
		D3DXVECTOR3 pos_in_change = pos_in;
		pos_in_change.y += (collider_wxhylz.y);
		collider->SetCollider3D(collider_c[Character_collider_top], pos_in_change, rot_in);
		collider->SetCollider3D(collider_c[Character_collider_stand], pos_in, rot_in);
		pos_in_change = pos_in;
		pos_in_change.y += (collider_wxhylz.y / 2);
		pos_in_change.x -= sinf(rot_in.y)*(collider_wxhylz.z / 2);
		pos_in_change.z -= cosf(rot_in.y)*(collider_wxhylz.z / 2);
		collider->SetCollider3D(collider_c[Character_collider_front], pos_in_change, rot_in);
		pos_in_change = pos_in;
		pos_in_change.y += (collider_wxhylz.y / 2);
		pos_in_change.x -= sinf((rot_in.y + D3DX_PI))*(collider_wxhylz.z / 2);
		pos_in_change.z -= cosf((rot_in.y + D3DX_PI))*(collider_wxhylz.z / 2);
		collider->SetCollider3D(collider_c[Character_collider_behind], pos_in_change, rot_in);
		pos_in_change = pos_in;
		pos_in_change.y += (collider_wxhylz.y / 2);
		pos_in_change.x -= sinf((rot_in.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
		pos_in_change.z -= cosf((rot_in.y - (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
		collider->SetCollider3D(collider_c[Character_collider_left], pos_in_change, rot_in);
		pos_in_change = pos_in;
		pos_in_change.y += (collider_wxhylz.y / 2);
		pos_in_change.x -= sinf((rot_in.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
		pos_in_change.z -= cosf((rot_in.y + (D3DX_PI / 2)))*(collider_wxhylz.x / 2);
		collider->SetCollider3D(collider_c[Character_collider_right], pos_in_change, rot_in);
	}
}