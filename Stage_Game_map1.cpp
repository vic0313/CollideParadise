#include "Stage_Game_map1.h"

namespace FIGHTING_GAME
{
	Stage_Game_map1::Stage_Game_map1(Renderer* renderer,Collider3D* collider)
	{
		renderer_map1 = renderer;
		Model_num=0;
		map1_collider = collider;
		
		Model_data = new ThreeDModel_data[GAME_MAP1_MODELMAX];
		for (int i = 0; i < GAME_MAP1_MODELMAX; i++)
		{
			Model_data[i].collider_index = new int[1];
			Model_data[i].index_max = 1;

		}

	}
	HRESULT Stage_Game_map1::InitStage()
	{
		//Model
		renderer_map1->LoadModel(GAMEMODEL_1, &model_1);
		renderer_map1->LoadModel(GAMEMODEL_2, &model_2);
		renderer_map1->LoadModel(GAMEMODEL_3, &model_3);
		renderer_map1->LoadModel(GAMEMODEL_4, &model_4);
		renderer_map1->LoadModel(GAMEMODEL_5, &model_5);
		renderer_map1->LoadModel(GAMEMODEL_6, &model_6);
		renderer_map1->LoadModel(GAMEMODEL_7, &model_7);
		renderer_map1->LoadModel(GAMEMODEL_8, &model_8);
		renderer_map1->LoadModel(GAMEMODEL_9, &model_9);
		renderer_map1->LoadModel(GAMEMODEL_10, &model_10);
		renderer_map1->LoadModel(GAMEMODEL_11, &model_11);
		renderer_map1->LoadModel(GAMEMODEL_12, &model_12);
		renderer_map1->LoadModel(GAMEMODEL_13, &model_13);
		renderer_map1->LoadModel(GAMEMODEL_14, &model_14);
		renderer_map1->LoadModel(GAMEMODEL_15, &model_15);
		renderer_map1->LoadModel(GAMEMODEL_16, &model_16);
		{
			//delete[] Model_data[Model_num].collider_index;
			//Model_data[Model_num].index_max = 2;
			//Model_data[Model_num].collider_index=new int[Model_data[Model_num].index_max];
			D3DXVECTOR3 rr = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//1
			{
				rr = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);

				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num15);
			}
			//2
			{
				rr = D3DXVECTOR3(3000.0f, 100.0f, 3000.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num1);

			}
			//3
			{
				delete[] Model_data[Model_num].collider_index;
				Model_data[Model_num].index_max = 20;
				Model_data[Model_num].collider_index = new int[Model_data[Model_num].index_max];
				float gg = D3DX_PI;
				rr = D3DXVECTOR3(155.0f, 200.0f, 190.0f);
				for (int i = 0; i < Model_data[Model_num].index_max; i++)
				{
					D3DXVECTOR3 dd = D3DXVECTOR3(1950.0f, 0.0f, 1900.0f);

					if (i == 0)
					{
						dd.x -= sinf(D3DX_PI) * 400;
						dd.z -= cosf(D3DX_PI) * 400;
					}
					else
					{
						gg -= (2 * D3DX_PI) / Model_data[Model_num].index_max;
						dd.z -= cosf(gg) * 400;
						dd.x -= sinf(gg) * 400;
					}
					Model_data[Model_num].collider_index[i] = map1_collider->CreateCollider3DBox(dd, D3DXVECTOR3(0.0f, gg, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				}
				rr = D3DXVECTOR3(500.0f, 200.0f, 500.0f);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1950.0f, 0.0f, 1900.0f);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num3);

			}
			//4
			{
				delete[] Model_data[Model_num].collider_index;
				Model_data[Model_num].index_max = 3;
				Model_data[Model_num].collider_index = new int[Model_data[Model_num].index_max];
				for (int i = 0; i < Model_data[Model_num].index_max; i++)
				{

					D3DXVECTOR3 dd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					switch (i)
					{
					case 0:
						dd = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
						rr = D3DXVECTOR3(500.0f, 200.0f, 500.0f);
						break;
					case 1:
						dd = D3DXVECTOR3(-187.5f, 250.0f, 2000.0f);
						rr = D3DXVECTOR3(125.0f, 300.0f, 500.0f);
						break;
					case 2:
						dd = D3DXVECTOR3(187.5f, 250.0f, 2000.0f);
						rr = D3DXVECTOR3(125.0f, 300.0f, 500.0f);
						break;
					}
					Model_data[Model_num].collider_index[i] = map1_collider->CreateCollider3DBox(dd, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				}
				rr = D3DXVECTOR3(500.0f, 500.0f, 500.0f);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, 250.0f, 2000.0f);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num5);

			}
			//5
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 400.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1270.0f, 99.0f, -100.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(1270.0f, 99.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num4);

			}
			//6
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 400.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, 0.0f, 1550.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 1550.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num4);
			}
			//7
			{
				rr = D3DXVECTOR3(500.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1097.33f, 17.3943f, 1641.37f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(-1097.33f, 42.3943f, 1641.37f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num6);
			}
			//8
			{
				rr = D3DXVECTOR3(500.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1280.35f, 88.223f, 1958.39f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(-1280.35f, 113.223f, 1958.39f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num6);
			}
			//9
			{
				rr = D3DXVECTOR3(500.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1614.5f, 158.227f, 1780.09f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(-1614.5f, 183.227f, 1780.09f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num6);
			}
			//10
			{
				rr = D3DXVECTOR3(500.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1829.3f, 220.956f, 1449.93f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(-1829.3f, 245.956f, 1449.93f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num6);
			}
			//11
			{
				rr = D3DXVECTOR3(500.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1709.81f, 284.881f, 1120.61f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(-1709.81f, 309.881f, 1120.61f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num6);
			}
			//12
			{
				rr = D3DXVECTOR3(1000.0f, 50.0f, 1800.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1867.62f, 374.117f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num7);
			}
			//13
			{
				rr = D3DXVECTOR3(800.0f, 50.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-999.98f, 696.02f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI/12)), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num8);
			}
			//14
			{
				rr = D3DXVECTOR3(750.0f, 1000.0f, 500.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1477.82f, 400.0f, -1748.39f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num13);
			}
			//15
			{
				delete[] Model_data[Model_num].collider_index;
				Model_data[Model_num].index_max = 7;
				Model_data[Model_num].collider_index = new int[Model_data[Model_num].index_max];
				for (int i = 0; i < Model_data[Model_num].index_max; i++)
				{

					D3DXVECTOR3 dd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					switch (i)
					{
					case 0:
						dd = D3DXVECTOR3(-1602.82f, -25.0f, -1748.39f);
						rr = D3DXVECTOR3(1000.0f, 150.0f, 1000.0f);
						//root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						break;
					case 1:
						dd = D3DXVECTOR3(-1694.0f, 50.0f, -1373.4f);
						rr = D3DXVECTOR3(583.095f, 350.0f, 250.0f);
						root = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI/5.8f);
						break;
					case 2:
						dd = D3DXVECTOR3(-1977.82f, 200.0f, -1748.39f);
						rr = D3DXVECTOR3(250.0f, 300.0f, 1000.0f);
						//root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						break;
					case 3:
						dd = D3DXVECTOR3(-1977.82f, 350.0f, -1839.39f);
						rr = D3DXVECTOR3(250.0f, 350.0f, 583.095f);
						root = D3DXVECTOR3(D3DX_PI / 5.8f, 0.0f, 0.0f);
						break;
					case 4:
						dd = D3DXVECTOR3(-1602.82f, 350.0f, -2123.39f);
						rr = D3DXVECTOR3(1000.0f, 600.0f, 250.0f);
						//root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						break;
					case 5:
						dd = D3DXVECTOR3(-1535.5f, 613.0f, -2123.39f);
						rr = D3DXVECTOR3(583.095f, 350.0f, 250.0f);
						root = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 6.77f);
						break;
					case 6:
						dd = D3DXVECTOR3(-1227.82f, 475.0f, -1873.39f);
						rr = D3DXVECTOR3(250.0f, 850.0f, 750.0f);
						//root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						break;
					//case 7:
					//	dd = D3DXVECTOR3(-1602.82f, 400.0f, -1748.39f);
					//	rr = D3DXVECTOR3(500.0f, 1000.0f, 500.0f);
					//	//root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					//	break;
					}
					
					Model_data[Model_num].collider_index[i] = map1_collider->CreateCollider3DBox(dd, root, rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				}
				rr = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1602.82f, 374.996f, -1748.39f);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num9);

			}
			//16
			{
				delete[] Model_data[Model_num].collider_index;
				Model_data[Model_num].index_max = 7;
				Model_data[Model_num].collider_index = new int[Model_data[Model_num].index_max];
				for (int i = 0; i < Model_data[Model_num].index_max; i++)
				{

					D3DXVECTOR3 dd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 root = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					switch (i)
					{
					case 0:
						dd = D3DXVECTOR3(1136.04f, 250.0f, -1925.19f);
						rr = D3DXVECTOR3(375.0f, 700.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, 0.0f);
						break;
					case 1:
						dd = D3DXVECTOR3(1931.54f, 250.0f, -1129.69f);
						rr = D3DXVECTOR3(375.0f, 700.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, 0.0f);
						break;
					case 2:
						dd = D3DXVECTOR3(1533.79f, 512.5f, -1527.44f);
						rr = D3DXVECTOR3(1500.0f, 175.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, 0.0f);
						break;
					case 3:
						dd = D3DXVECTOR3(1350.29f, 410.0f, -1710.44f);
						rr = D3DXVECTOR3(256.5f, 200.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, D3DX_PI / 4.2f);
						break;
					case 4:
						dd = D3DXVECTOR3(1715.29f, 410.0f, -1345.44f);
						rr = D3DXVECTOR3(256.5f, 200.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, -D3DX_PI / 4.2f);
						break;
					case 5:
						dd = D3DXVECTOR3(1235.0f, 100.0f, -1824.0f);
						rr = D3DXVECTOR3(500.0f, 200.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, D3DX_PI / 2.4f);
						break;
					case 6:
						dd = D3DXVECTOR3(1833.29f, 100.0f, -1226.44f);
						rr = D3DXVECTOR3(500.0f, 200.0f, 1000.0f);
						root = D3DXVECTOR3(0.0f, -D3DX_PI / 4, -D3DX_PI / 2.4f);
						break;
					}

					Model_data[Model_num].collider_index[i] = map1_collider->CreateCollider3DBox(dd, root, rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				}
				rr = D3DXVECTOR3(1000.0f, 700.0f, 1500.0f);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1533.79f, 325.0f, -1527.44f);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num10);

			}
			//17
			{
				rr = D3DXVECTOR3(800.0f, 200.0f, 800.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1024.19f, 0.0f, 593.828f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num11);
			}
			//18
			{
				delete[] Model_data[Model_num].collider_index;
				Model_data[Model_num].index_max = 8;
				Model_data[Model_num].collider_index = new int[Model_data[Model_num].index_max];
				float gg = (D3DX_PI*7) /8;
				rr = D3DXVECTOR3(382.0f, 1000.0f, 424.0f);
				for (int i = 0; i < Model_data[Model_num].index_max; i++)
				{
					D3DXVECTOR3 dd = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
					if (i == 0)
					{
						dd.x -= sinf(gg) * 250;
						dd.z -= cosf(gg) * 250;
						
					}
					else
					{
						gg -= (2 * D3DX_PI) / Model_data[Model_num].index_max;
						dd.z -= cosf(gg) * 250;
						dd.x -= sinf(gg) * 250;
					}
					Model_data[Model_num].collider_index[i] = map1_collider->CreateCollider3DBox(dd, D3DXVECTOR3(0.0f, gg, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				}
				rr = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num12);

			}
			
			//19
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-800.0f, 760.0f, -1850.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//20
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-500.0f, 710.0f, -1600.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//21
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-500.0f, 710.0f, -2100.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//22
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-200.0f, 660.0f, -1350.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//23
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-200.0f, 660.0f, -1850.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//24
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-200.0f, 660.0f, -2350.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//25
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(100.0f, 610.0f, -1650.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//26
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(100.0f, 610.0f, -2100.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//27
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(400.0f, 560.0f, -1850.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//28
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1000.0f, 135.0f, 500.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//28
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1000.0f, 135.0f, -200.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//29
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-700.0f, 230.0f, 150.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//30
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1800.0f, 200.0f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}
			//31
			{
				rr = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(2200.0f, 350.0f, 1700.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num14);
			}

			//32
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-700.0f, 500.0f, 150.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//33
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, 1060.0f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//34
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(2250.0f, 160.0f, 2200.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//35
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1024.19f, 160.0f, 593.828f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//36
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1867.62f, 524.117f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//37
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-1477.82f, 1100.0f, -1748.39f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//38
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(1533.79f, 755.0f, -1527.44f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}
			//39
			{
				rr = D3DXVECTOR3(90.0f, 90.0f, 90.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(-200.0f, 830.0f, -1850.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num16);
			}

			//40 壁
			{
				rr = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				Model_data[Model_num].collider_pos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
				Model_data[Model_num].collider_index[0] = map1_collider->CreateCollider3DBox(Model_data[Model_num].collider_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), rr.x, rr.y, rr.z, Collider3DType_box, Stage_object);
				Model_data[Model_num].collider_radius = D3DXVec3Length(&rr);
				this->SetModel(true, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Num2);
			}
		}

		
		//2DPlane


		return S_OK;
	}
	void Stage_Game_map1::UpdateStage()
	{
		/*Model_data[0].rot.y += D3DX_PI / 200;
		while (Model_data[0].rot.y > D3DX_PI || Model_data[0].rot.y < (-D3DX_PI))
		{
			if (Model_data[0].rot.y > 0)
			{
				Model_data[0].rot.y -= 2 * D3DX_PI;
			}
			else if (Model_data[0].rot.y < 0)
			{
				Model_data[0].rot.y += 2 * D3DX_PI;
			}
		}*/
		//回転のブロック
		int num = 27;
		{
			
			Model_data[num].rot.x += D3DX_PI / 200;
			//角度修正
			{
				while (Model_data[num].rot.y > D3DX_PI || Model_data[num].rot.y < (-D3DX_PI))
				{
					if (Model_data[num].rot.y > 0)
					{
						Model_data[num].rot.y -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.y < 0)
					{
						Model_data[num].rot.y += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.x > D3DX_PI || Model_data[num].rot.x < (-D3DX_PI))
				{
					if (Model_data[num].rot.x > 0)
					{
						Model_data[num].rot.x -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.x < 0)
					{
					Model_data[num].rot.x += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.z > D3DX_PI || Model_data[num].rot.z < (-D3DX_PI))
				{
					if (Model_data[num].rot.z > 0)
					{
						Model_data[num].rot.z -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.z < 0)
					{
						Model_data[num].rot.z += 2 * D3DX_PI;
					}
				}
			}
			map1_collider->SetCollider3D(Model_data[num].collider_index[0], Model_data[num].pos, Model_data[num].rot);

			num = 28;
			Model_data[num].rot.z += D3DX_PI / 200;
			//角度修正
			{
				while (Model_data[num].rot.y > D3DX_PI || Model_data[num].rot.y < (-D3DX_PI))
				{
					if (Model_data[num].rot.y > 0)
					{
						Model_data[num].rot.y -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.y < 0)
					{
						Model_data[num].rot.y += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.x > D3DX_PI || Model_data[num].rot.x < (-D3DX_PI))
				{
					if (Model_data[num].rot.x > 0)
					{
						Model_data[num].rot.x -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.x < 0)
					{
						Model_data[num].rot.x += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.z > D3DX_PI || Model_data[num].rot.z < (-D3DX_PI))
				{
					if (Model_data[num].rot.z > 0)
					{
						Model_data[num].rot.z -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.z < 0)
					{
						Model_data[num].rot.z += 2 * D3DX_PI;
					}
				}
			}
			map1_collider->SetCollider3D(Model_data[num].collider_index[0], Model_data[num].pos, Model_data[num].rot);

			num = 29;
			Model_data[num].rot.y += D3DX_PI / 200;
			//角度修正
			{
				while (Model_data[num].rot.y > D3DX_PI || Model_data[num].rot.y < (-D3DX_PI))
				{
					if (Model_data[num].rot.y > 0)
					{
						Model_data[num].rot.y -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.y < 0)
					{
						Model_data[num].rot.y += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.x > D3DX_PI || Model_data[num].rot.x < (-D3DX_PI))
				{
					if (Model_data[num].rot.x > 0)
					{
						Model_data[num].rot.x -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.x < 0)
					{
						Model_data[num].rot.x += 2 * D3DX_PI;
					}
				}
				while (Model_data[num].rot.z > D3DX_PI || Model_data[num].rot.z < (-D3DX_PI))
				{
					if (Model_data[num].rot.z > 0)
					{
						Model_data[num].rot.z -= 2 * D3DX_PI;
					}
					else if (Model_data[num].rot.z < 0)
					{
						Model_data[num].rot.z += 2 * D3DX_PI;
					}
				}
			}
			map1_collider->SetCollider3D(Model_data[num].collider_index[0], Model_data[num].pos, Model_data[num].rot);
		}
		//移動のブロック
		{
			num = 30;
			Model_data[num].pos.z += 2;
			if (Model_data[num].pos.z > 900.0f)
			{
				Model_data[num].use = false;
				map1_collider->SetCollider3D_use(Model_data[num].collider_index[0],false);
				if (Model_data[num].pos.z > 1000.0f)
				{
					Model_data[num].use = true;
					map1_collider->SetCollider3D_use(Model_data[num].collider_index[0], true);
					Model_data[num].pos = D3DXVECTOR3(1800.0f, 200.0f, 0.0f);
				}
				
			}
			Model_data[num].collider_pos = Model_data[num].pos;
			map1_collider->SetCollider3D(Model_data[num].collider_index[0], Model_data[num].pos, Model_data[num].rot);
		}
		//移動のブロック
		{
			num = 31;
			Model_data[num].pos.z -= 4;
			if (Model_data[num].pos.z < -600.0f)
			{
				Model_data[num].use = false;
				map1_collider->SetCollider3D_use(Model_data[num].collider_index[0], false);
				if (Model_data[num].pos.z < -700.0f)
				{
					Model_data[num].use = true;
					map1_collider->SetCollider3D_use(Model_data[num].collider_index[0], true);
					Model_data[num].pos = D3DXVECTOR3(2200.0f, 350.0f, 1700.0f);
				}

			}
			Model_data[num].collider_pos = Model_data[num].pos;
			map1_collider->SetCollider3D(Model_data[num].collider_index[0], Model_data[num].pos, Model_data[num].rot);
		}
		//スタのブロック
		for(num=32;num< (Model_num-1);num++)
		{
			Model_data[num].rot.y -= D3DX_PI / 100;
		}

		//material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.5f); // set color
	}
	void Stage_Game_map1::DrawStage()
	{
		if (GameDate::DrawType == Draw_normal || GameDate::DrawType == Draw_Both)
		{
			for (int i = 0; i < GAME_MAP1_MODELMAX; i++)
			{
				if (Model_data[i].color_a == 0 && Model_data[i].use==true)
				{
					
					switch (Model_data[i].model_num)
					{
					case Num1:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_1, false, Model_data[i].color_a);
						break;
					case Num2:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_2, false, Model_data[i].color_a);
						break;
					case Num3:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_3, false, Model_data[i].color_a);
						break;
					case Num4:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_4, false, Model_data[i].color_a);
						break;
					case Num5:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_5, false, Model_data[i].color_a);
						break;
					case Num6:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_6, false, Model_data[i].color_a);
						break;
					case Num7:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_7, false, Model_data[i].color_a);
						break;
					case Num8:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_8, false, Model_data[i].color_a);
						break;
					case Num9:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_9, false, Model_data[i].color_a);
						break;
					case Num10:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_10, false, Model_data[i].color_a);
						break;
					case Num11:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_11, false, Model_data[i].color_a);
						break;
					case Num12:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_12, false, Model_data[i].color_a);
						break;
					case Num13:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_13, false, Model_data[i].color_a);
						break;
					case Num14:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_14, false, Model_data[i].color_a);
						break;
					case Num15:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_15, false, Model_data[i].color_a);
						break;
					case Num16:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_16, false, Model_data[i].color_a);
						break;
					}
				}
			}

			for (int i = 0; i < GAME_MAP1_MODELMAX; i++)
			{
				if (Model_data[i].color_a == 1 && Model_data[i].use == true)
				{
					switch (Model_data[i].model_num)
					{
					case Num1:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_1, false, Model_data[i].color_a);
						break;
					case Num2:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_2, false, Model_data[i].color_a);
						break;
					case Num3:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_3, false, Model_data[i].color_a);
						break;
					case Num4:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_4, false, Model_data[i].color_a);
						break;
					case Num5:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_5, false, Model_data[i].color_a);
						break;
					case Num6:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_6, false, Model_data[i].color_a);
						break;
					case Num7:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_7, false, Model_data[i].color_a);
						break;
					case Num8:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_8, false, Model_data[i].color_a);
						break;
					case Num9:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_9, false, Model_data[i].color_a);
						break;
					case Num10:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_10, false, Model_data[i].color_a);
						break;
					case Num11:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_11, false, Model_data[i].color_a);
						break;
					case Num12:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_12, false, Model_data[i].color_a);
						break;
					case Num13:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_13, false, Model_data[i].color_a);
						break;
					case Num14:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_14, false, Model_data[i].color_a);
						break;
					case Num15:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_15, false, Model_data[i].color_a);
						break;
					case Num16:
						renderer_map1->Draw_3DModel(Model_data[i].mtxWorld, Model_data[i].scl, Model_data[i].rot, Model_data[i].pos, model_16, false, Model_data[i].color_a);
						break;
					}
				}


			}
		}
	}

	void Stage_Game_map1::UninitStage()
	{
		renderer_map1->UnloadModel(&model_1);
		renderer_map1->UnloadModel(&model_2);
		renderer_map1->UnloadModel(&model_3);
		renderer_map1->UnloadModel(&model_4);
		renderer_map1->UnloadModel(&model_5);
		renderer_map1->UnloadModel(&model_6);
		renderer_map1->UnloadModel(&model_7);
		renderer_map1->UnloadModel(&model_8);
		renderer_map1->UnloadModel(&model_9);
		renderer_map1->UnloadModel(&model_10);
		renderer_map1->UnloadModel(&model_11);
		renderer_map1->UnloadModel(&model_12);
		renderer_map1->UnloadModel(&model_13);
		renderer_map1->UnloadModel(&model_14);
		renderer_map1->UnloadModel(&model_15);
		renderer_map1->UnloadModel(&model_16);
		delete[] Model_data;
	}
	void Stage_Game_map1::SetModel(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl, Stage_Model_Num num)
	{
		Model_data[Model_num].use= use;
		Model_data[Model_num].pos = pos;
		Model_data[Model_num].rot = rot;
		Model_data[Model_num].rot_move = rot_move;
		Model_data[Model_num].scl = scl;
		Model_data[Model_num].model_num = num;
		Model_data[Model_num].color_a = 0;
		this->Model_num++;
	}
	void Stage_Game_map1::SetCollider(bool	use, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 rot_move, D3DXVECTOR3 scl)
	{
		Model_data[Model_num].use = use;
		Model_data[Model_num].pos = pos;
		Model_data[Model_num].rot = rot;
		Model_data[Model_num].rot_move = rot_move;
		Model_data[Model_num].scl = scl;


		this->Model_num++;
	}
	void Stage_Game_map1::Set2DPlane()
	{
		
	}
}