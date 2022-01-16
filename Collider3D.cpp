#include "Collider3D.h"
namespace FIGHTING_GAME
{
	Collider3D::Collider3D(Renderer* renderer, Collider3D_Tag tag)
	{
		math = new Calculate();
		collider_renderer = renderer;
		switch (tag)
		{
		case Player_object:
			g_Collider3D = new COLLIDER3D[PLAYERCOLLIDER_MAX];
			ColliderMax = PLAYERCOLLIDER_MAX;
			break;
		case Enemy_object:
			g_Collider3D = new COLLIDER3D[ENEMY_COLLIDER3D_MAX];
			ColliderMax = ENEMY_COLLIDER3D_MAX;
			break;
		case Stage_object:
			g_Collider3D = new COLLIDER3D[STAGE_COLLIDER3D_MAX];
			ColliderMax = STAGE_COLLIDER3D_MAX;
			break;
		case BigSwordWeapon_object:
			g_Collider3D = new COLLIDER3D[BIGSWORD_COLLIDER3D_MAX];
			ColliderMax = BIGSWORD_COLLIDER3D_MAX;
			break;
		case EnemyWeapon:
			g_Collider3D = new COLLIDER3D[ENEMYWEAPON_COLLIDER3D_MAX];
			ColliderMax = ENEMYWEAPON_COLLIDER3D_MAX;
		default:
			break;
		}
		g_TextureName =  "data/TEXTURE/white.jpg" ;
		g_VertexBuffer = NULL;
		g_VertexBuffercircle = NULL;
		g_Texture =  NULL ;
	}

	HRESULT Collider3D::InitCollider3D()
	{
		Collidernum = 0;
		// ���_�o�b�t�@�̍쐬
		this->MakeVertexCollider3D();
		// �e�N�X�`������
		D3DX11CreateShaderResourceViewFromFile(collider_renderer->GetDevice(),
			g_TextureName,
			NULL,
			NULL,
			&g_Texture,
			NULL);
		
		
		// ���[�N������
		for (int i = 0; i < ColliderMax; i++)
		{
			ZeroMemory(&g_Collider3D[i].material, sizeof(g_Collider3D[i].material));
			g_Collider3D[i].material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


			g_Collider3D[i].normalDirect[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			g_Collider3D[i].normalDirect[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_Collider3D[i].normalDirect[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

			g_Collider3D[i].Use = false;
			g_Collider3D[i].draw_check = false;
			g_Collider3D[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Collider3D[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Collider3D[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_Collider3D[i].type = Collider3DType_box;
			g_Collider3D[i].tag = collider3DTag_none;
			g_Collider3D[i].wx = 0.0f;
			g_Collider3D[i].hy = 0.0f;
			g_Collider3D[i].lz = 0.0f;
			g_Collider3D[i].r = 0.0f;
		}
		return S_OK;
	}

	void Collider3D::UninitCollider3D(void)
	{
		// ���_�o�b�t�@�̉��
		if (g_VertexBuffer)
		{
			g_VertexBuffer->Release();
			g_VertexBuffer = NULL;
		}
		if (g_VertexBuffercircle)
		{
			g_VertexBuffercircle->Release();
			g_VertexBuffercircle = NULL;
		}
		// �e�N�X�`���̉��
		g_Texture->Release();
		g_Texture = NULL;
		delete[] g_Collider3D;
		delete math;

	}

	void Collider3D::UpdateCollider3D()
	{
		
	}

	void Collider3D::DrawCollider3D()
	{
		for (int i = 0; i < ColliderMax; i++)
		{
			if (g_Collider3D[i].Use==true&& g_Collider3D[i].draw_check == true)
			{
				if (g_Collider3D[i].type == Collider3DType_box)
				{
					collider_renderer->Draw_Collider_box(this->g_VertexBuffer, this->g_Texture, g_Collider3D[i].material,
						g_Collider3D[i].rot, g_Collider3D[i].pos, g_Collider3D[i].mtxWorld, g_Collider3D[i].tag,
						g_Collider3D[i].wx, g_Collider3D[i].hy, g_Collider3D[i].lz, g_Collider3D[i].r);
				}
			}
		}
	}

	HRESULT Collider3D::MakeVertexCollider3D()
	{
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D_BASE) * 26;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		collider_renderer->GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

		{//���_�o�b�t�@�̒��g�𖄂߂�
			D3D11_MAPPED_SUBRESOURCE msr;
			collider_renderer->GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D_BASE* vertex = (VERTEX_3D_BASE*)msr.pData;

			//�n�ʂ̃|���S��
			vertex[0] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////��
			vertex[1] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[2] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[3] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[4] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////�O
			vertex[5] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[6] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[7] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[8] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////��
			vertex[9] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[10] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[11] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[12] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(1.0f, 0.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////�E
			vertex[13] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(1.0f, 0.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[14] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(1.0f, 0.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[15] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(1.0f, 0.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[16] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 1.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////��
			vertex[17] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 1.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[18] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 1.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[19] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 0.0f, 1.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[20] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) };////��
			vertex[21] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) };
			vertex[22] = { D3DXVECTOR3(-COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) };
			vertex[23] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[24] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE,  COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };
			vertex[25] = { D3DXVECTOR3(COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE, -COLLIDER3D_RENDER_SIZE), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) };

			collider_renderer->GetDeviceContext()->Unmap(g_VertexBuffer, 0);
		}

		return S_OK;
	}

//=============================================================================
// collider�̍쐬
//=============================================================================
	int Collider3D::CreateCollider3DBox( D3DXVECTOR3 pos, D3DXVECTOR3 rot, float wx, float hy, float lz, Collider3DType type, Collider3D_Tag tag)
	{
		g_Collider3D[Collidernum].Use = true;
		g_Collider3D[Collidernum].draw_check = true;
		g_Collider3D[Collidernum].pos = pos;
		g_Collider3D[Collidernum].rot = rot;
		g_Collider3D[Collidernum].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Collider3D[Collidernum].type = type;
		g_Collider3D[Collidernum].wx = wx;
		g_Collider3D[Collidernum].hy = hy;
		g_Collider3D[Collidernum].lz = lz;
		g_Collider3D[Collidernum].tag = tag;
		D3DXVECTOR3 rr = D3DXVECTOR3(wx / 2, hy / 2, lz / 2);
		g_Collider3D[Collidernum].r = D3DXVec3Length(&rr);
		Collidernum++;
		return (Collidernum - 1);

	}
//=============================================================================
// �F�X�̐ݒ�
//=============================================================================
	void Collider3D::SetCollider3D(int Collidernum, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
	{
		g_Collider3D[Collidernum].pos = pos;
		g_Collider3D[Collidernum].rot = rot;

	}

	void Collider3D::SetCollider3D_scl(int Collidernum, D3DXVECTOR3 scl)
	{
		g_Collider3D[Collidernum].wx = scl.x;
		g_Collider3D[Collidernum].hy = scl.y;
		g_Collider3D[Collidernum].lz = scl.z;

	}
	
	void Collider3D::SetCollider3D_use(int Collidernum, bool use)
	{
		g_Collider3D[Collidernum].Use = use;

	}

//==========================================================================
// OBB�ɂ�铖���蔻�菈��
//==========================================================================

	bool Collider3D::CheckHitOBB(COLLIDER3D *col_1, COLLIDER3D *col_2)
	{
		COLLIDER3D* col1 = col_1;
		COLLIDER3D* col2 = col_2;

		D3DXMATRIX RotateMtx1;
		D3DXMATRIX RotateMtx2;

		D3DXMatrixRotationYawPitchRoll(&RotateMtx1, col1->rot.y, col1->rot.x, col1->rot.z);
		D3DXMatrixRotationYawPitchRoll(&RotateMtx2, col2->rot.y, col2->rot.x, col2->rot.z);

		col1->normalDirect[0] = D3DXVECTOR3(RotateMtx1._11, RotateMtx1._12, RotateMtx1._13);
		col1->normalDirect[1] = D3DXVECTOR3(RotateMtx1._21, RotateMtx1._22, RotateMtx1._23);
		col1->normalDirect[2] = D3DXVECTOR3(RotateMtx1._31, RotateMtx1._32, RotateMtx1._33);
		col2->normalDirect[0] = D3DXVECTOR3(RotateMtx2._11, RotateMtx2._12, RotateMtx2._13);
		col2->normalDirect[1] = D3DXVECTOR3(RotateMtx2._21, RotateMtx2._22, RotateMtx2._23);
		col2->normalDirect[2] = D3DXVECTOR3(RotateMtx2._31, RotateMtx2._32, RotateMtx2._33);
		// �e�����x�N�g���̊m��
		// �iN***:�W���������x�N�g���j

		D3DXVECTOR3 NAe1 = col1->normalDirect[0], Ae1 = NAe1 * col1->wx * 0.5f;
		D3DXVECTOR3 NAe2 = col1->normalDirect[1], Ae2 = NAe2 * col1->hy * 0.5f;
		D3DXVECTOR3 NAe3 = col1->normalDirect[2], Ae3 = NAe3 * col1->lz * 0.5f;
		D3DXVECTOR3 NBe1 = col2->normalDirect[0], Be1 = NBe1 * col2->wx * 0.5f;
		D3DXVECTOR3 NBe2 = col2->normalDirect[1], Be2 = NBe2 * col2->hy * 0.5f;
		D3DXVECTOR3 NBe3 = col2->normalDirect[2], Be3 = NBe3 * col2->lz * 0.5f;
		D3DXVECTOR3 Interval = col1->pos - col2->pos;

		// ������ : Ae1
		FLOAT rA = D3DXVec3Length(&Ae1);
		FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
		FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
		if (L > rA + rB)
			return false; // �Փ˂��Ă��Ȃ�

		 // ������ : Ae2
		rA = D3DXVec3Length(&Ae2);
		rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe2));
		if (L > rA + rB)
			return false;

		// ������ : Ae3
		rA = D3DXVec3Length(&Ae3);
		rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe3));
		if (L > rA + rB)
			return false;

		// ������ : Be1
		rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be1);
		L = fabs(D3DXVec3Dot(&Interval, &NBe1));
		if (L > rA + rB)
			return false;

		// ������ : Be2
		rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be2);
		L = fabs(D3DXVec3Dot(&Interval, &NBe2));
		if (L > rA + rB)
			return false;

		// ������ : Be3
		rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NBe3));
		if (L > rA + rB)
			return false;

		// ������ : C11
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &NAe1, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C12
		D3DXVec3Cross(&Cross, &NAe1, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C13
		D3DXVec3Cross(&Cross, &NAe1, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C21
		D3DXVec3Cross(&Cross, &NAe2, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C22
		D3DXVec3Cross(&Cross, &NAe2, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C23
		D3DXVec3Cross(&Cross, &NAe2, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C31
		D3DXVec3Cross(&Cross, &NAe3, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C32
		D3DXVec3Cross(&Cross, &NAe3, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// ������ : C33
		D3DXVec3Cross(&Cross, &NAe3, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			return false;

		// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
		return true;
	}

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	FLOAT Collider3D::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
	{
		// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
		// ������Sep�͕W��������Ă��邱��
		FLOAT r1 = fabs(D3DXVec3Dot(Sep, e1));
		FLOAT r2 = fabs(D3DXVec3Dot(Sep, e2));
		FLOAT r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
		return r1 + r2 + r3;
	}
	//                      rect         point
	
//=============================================================================
// RAYCAST���菈��
//=============================================================================

	bool Collider3D::RayHitGround( D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL model,float start_UP)
	{
		//�n�ʂ̐G�锻��
		D3DXVECTOR3 start = pos;
		D3DXVECTOR3 end = pos;
		D3DXVECTOR3 HitPositionTemp;
		D3DXVECTOR3 NormalTemp;
		D3DXMATRIX  mtxScl, mtxRot, mtxTranslate, mtxWorld;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);
		 //�X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, model_scl.x, model_scl.y, model_scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model_rot.y, model_rot.x, model_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		// �ړ��𔽉f
		
		D3DXMatrixTranslation(&mtxTranslate, model_pos.x, model_pos.y, model_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		// �����ォ��A�Y�h�[���Ɖ��փ��C���΂�
		start.y += start_UP;
		end.y -= 1000.0f;
		for (int i = 0; i < model.IndexNum; i += 3) {
			D3DXVECTOR3 p0, p1, p2;
			p0 = model.Vertexlist[model.Indexlist[i]];
			p1 = model.Vertexlist[model.Indexlist[i + 1]];
			p2 = model.Vertexlist[model.Indexlist[i + 2]];
			D3DXVec3TransformCoord(&p0, &p0, &mtxWorld);
			D3DXVec3TransformCoord(&p1, &p1, &mtxWorld);
			D3DXVec3TransformCoord(&p2, &p2, &mtxWorld);
			bool ans = RayCast(p0, p2, p1, start, end, &HitPositionTemp, &NormalTemp);
			if (ans) 
			{
				D3DXVECTOR3 y_vector = D3DXVECTOR3(0.0f,1.0f,0.0f);
				float dd= math->dotProduct(&y_vector, &NormalTemp);
				
				if (dd > 0)
				{
					math->Four_out_Five_in(&HitPositionTemp);
					math->Four_out_Five_in(&NormalTemp);
					*HitPosition = HitPositionTemp;
					*Normal = NormalTemp;
					return true;
				}
			}
		}
		return false;
	}

	bool Collider3D::RayHitTop(D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL	model)
	{
		//�n�ʂ̐G�锻��
		D3DXVECTOR3 start = pos;
		D3DXVECTOR3 end = pos;
		D3DXVECTOR3 HitPositionTemp;
		D3DXVECTOR3 NormalTemp;
		D3DXMATRIX  mtxScl, mtxRot, mtxTranslate, mtxWorld;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);
		//�X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, model_scl.x, model_scl.y, model_scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model_rot.y, model_rot.x, model_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		// �ړ��𔽉f

		D3DXMatrixTranslation(&mtxTranslate, model_pos.x, model_pos.y, model_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		// �����ォ��A�Y�h�[���Ɖ��փ��C���΂�
		end.y += 1000.0f;
		for (int i = 0; i < model.IndexNum; i += 3) {
			D3DXVECTOR3 p0, p1, p2;
			p0 = model.Vertexlist[model.Indexlist[i]];
			p1 = model.Vertexlist[model.Indexlist[i + 1]];
			p2 = model.Vertexlist[model.Indexlist[i + 2]];
			D3DXVec3TransformCoord(&p0, &p0, &mtxWorld);
			D3DXVec3TransformCoord(&p1, &p1, &mtxWorld);
			D3DXVec3TransformCoord(&p2, &p2, &mtxWorld);
			bool ans = RayCast(p0, p2, p1, start, end, &HitPositionTemp, &NormalTemp);
			if (ans)
			{
				//D3DXVECTOR3 y_vector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				//float dd = math->dotProduct(&y_vector, &NormalTemp);
				if (NormalTemp.y <= 0)
				{
					math->Four_out_Five_in(&HitPositionTemp);
					math->Four_out_Five_in(&NormalTemp);
					*HitPosition = HitPositionTemp;
					*Normal = NormalTemp;
					return true;
				}
			}
		}
		return false;
	}

	bool Collider3D::RayHitWall(D3DXVECTOR3 * HitPosition, D3DXVECTOR3 * Normal, D3DXVECTOR3 pos, D3DXVECTOR3 model_scl, D3DXVECTOR3 model_rot, D3DXVECTOR3 model_pos, DX11_MODEL	model, D3DXVECTOR3 move_way)
	{
		//�n�ʂ̐G�锻��
		D3DXVECTOR3 start = pos;
		D3DXVECTOR3 end = pos;
		D3DXVECTOR3 HitPositionTemp;
		D3DXVECTOR3 NormalTemp;
		D3DXMATRIX  mtxScl, mtxRot, mtxTranslate, mtxWorld;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);
		//�X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, model_scl.x, model_scl.y, model_scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, model_rot.y, model_rot.x, model_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		// �ړ��𔽉f

		D3DXMatrixTranslation(&mtxTranslate, model_pos.x, model_pos.y, model_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		// �����ォ��A�Y�h�[���Ɖ��փ��C���΂�
		//start -= move_way;
		end += (move_way);
		for (int i = 0; i < model.IndexNum; i += 3) {
			D3DXVECTOR3 p0, p1, p2;
			p0 = model.Vertexlist[model.Indexlist[i]];
			p1 = model.Vertexlist[model.Indexlist[i + 1]];
			p2 = model.Vertexlist[model.Indexlist[i + 2]];
			D3DXVec3TransformCoord(&p0, &p0, &mtxWorld);
			D3DXVec3TransformCoord(&p1, &p1, &mtxWorld);
			D3DXVec3TransformCoord(&p2, &p2, &mtxWorld);
			bool ans = RayCast(p0, p2, p1, start,  end, &HitPositionTemp, &NormalTemp);
			if (NormalTemp.y > 0.7)continue;
			if (ans )
			{
				NormalTemp.y = 0.0f;
				D3DXVec3Normalize(&NormalTemp, &NormalTemp);
				float angle = math->Two_vector_angle(&NormalTemp, &move_way);
				if (angle >0)continue;
				math->Four_out_Five_in(&HitPositionTemp);
				math->Four_out_Five_in(&NormalTemp);
				*HitPosition = HitPositionTemp;
				*Normal = NormalTemp;
				return true;
			}
		}
		return false;
	}

	bool Collider3D::RayCast(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 * hit, D3DXVECTOR3 *normal)
	{
		D3DXVECTOR3		nor;		// �|���S���̖@��
		D3DXVECTOR3		vec1;
		D3DXVECTOR3		vec2;
		D3DXVECTOR3		vec_test;
		float			d1, d2;
		
		{	// �|���S���̊O�ς��Ƃ��Ė@�������߂�(�Œ蕨�Ȃ�\��Init()�ōs���Ă����Ɨǂ�)
			vec1 = p1 - p0;
			vec2 = p2 - p0;
			math->crossProduct(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);		// �v�Z���₷���悤�ɖ@�����m�[�}���C�Y���Ă���
			*normal = nor;						// ���߂��@�������Ă���
			if (nor.x == 0.0f && nor.y == 0.0f &&nor.z == 0.0f) return false; // ���s
		}
		// �|���S�����ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�i�s�p�Ȃ�{�A�݊p�Ȃ�[�A���p�Ȃ�O�j
		vec1 = pos0 - p0;
		vec2 = pos1 - p0;
		{	// ���߂��|���S���̖@���ƂQ�̃x�N�g?�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j�̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
			d1 = math->dotProduct(&vec1, &nor);
			d2 = math->dotProduct(&vec2, &nor);
			if ((d1 * d2) > 0.0f)
			{
				// �������Ă���\���͖���
				return(false);
			}
		}


		{	// �|���S���Ɛ����̌�_�����߂�
			d1 = (float)fabs(d1);
			d2 = (float)fabs(d2);
			if((d1+d2)==0)return(false);
			float a = d1 / (d1 + d2);							// ������

			D3DXVECTOR3		vec3 = (1 - a) * vec1 + a * vec2;	// p0�����_�ւ̃x�N�g?
			D3DXVECTOR3		p3 = p0 + vec3;						// ��_
			*hit = p3;											// ���߂���_�����Ă���
			{	// ���߂���_���|���S���̒��ɂ��邩���ׂ�

				// �|���S���̊e�ӂ̃x�N�g?
				D3DXVECTOR3		v1 = p1 - p0;
				D3DXVECTOR3		v2 = p2 - p1;
				D3DXVECTOR3		v3 = p0 - p2;

				// �e���_�ƌ�_�Ƃ̃x�N�g?
				D3DXVECTOR3		v4 = p3 - p1;
				D3DXVECTOR3		v5 = p3 - p2;
				D3DXVECTOR3		v6 = p3 - p0;

				// �O�ςŊe�ӂ̖@�������߂āA�|���S���̖@���Ƃ̓��ς��Ƃ���??���`�F�b�N����
				D3DXVECTOR3		n1, n2, n3;

				math->crossProduct(&n1, &v4, &v1);
				if (math->dotProduct(&n1, &nor) < 0.0f)
				{
					return(false); // �������Ă��Ȃ�
				}

				math->crossProduct(&n2, &v5, &v2);
				float gg = math->dotProduct(&n2, &nor);
				if (math->dotProduct(&n2, &nor) < 0.0f)  // �������Ă��Ȃ�
				{
					return(false);
				}

				math->crossProduct(&n3, &v6, &v3);
				if (math->dotProduct(&n3, &nor) < 0.0f)  // �������Ă��Ȃ�
				{
					return(false);
				}
			}
		}


		return(true);	// �������Ă���I(hit�ɂ͓������Ă����_�������Ă���Bnormal�ɂ͖@���������Ă���)
	}
	bool Collider3D::RayCast_Top(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 * hit, D3DXVECTOR3 *normal)
	{
		D3DXVECTOR3		nor;		// �|���S���̖@��
		D3DXVECTOR3		vec1;
		D3DXVECTOR3		vec2;
		D3DXVECTOR3		vec_test;
		float			d1, d2;

		{	// �|���S���̊O�ς��Ƃ��Ė@�������߂�(�Œ蕨�Ȃ�\��Init()�ōs���Ă����Ɨǂ�)
			vec1 = p1 - p0;
			vec2 = p2 - p0;
			math->crossProduct(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);		// �v�Z���₷���悤�ɖ@�����m�[�}���C�Y���Ă���
			*normal = nor;						// ���߂��@�������Ă���
			if (nor.x == 0.0f && nor.y == 0.0f &&nor.z == 0.0f) return false; // ���s
		}
		
		// �|���S�����ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�i�s�p�Ȃ�{�A�݊p�Ȃ�[�A���p�Ȃ�O�j
		vec1 = pos0 - p0;
		vec2 = pos1 - p0;
		{	// ���߂��|���S���̖@���ƂQ�̃x�N�g?�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j�̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
			d1 = math->dotProduct(&vec1, &nor);
			d2 = math->dotProduct(&vec2, &nor);
			if ((d1 * d2) > 0.0f)
			{
				// �������Ă���\���͖���
				return(false);
			}
		}


		{	// �|���S���Ɛ����̌�_�����߂�
			d1 = (float)fabs(d1);
			d2 = (float)fabs(d2);
			float a = d1 / (d1 + d2);							// ������

			D3DXVECTOR3		vec3 = (1 - a) * vec1 + a * vec2;	// p0�����_�ւ̃x�N�g?
			D3DXVECTOR3		p3 = p0 + vec3;						// ��_
			*hit = p3;											// ���߂���_�����Ă���
			{	// ���߂���_���|���S���̒��ɂ��邩���ׂ�

				// �|���S���̊e�ӂ̃x�N�g?
				D3DXVECTOR3		v1 = p1 - p0;
				D3DXVECTOR3		v2 = p2 - p1;
				D3DXVECTOR3		v3 = p0 - p2;

				// �e���_�ƌ�_�Ƃ̃x�N�g?
				D3DXVECTOR3		v4 = p3 - p1;
				D3DXVECTOR3		v5 = p3 - p2;
				D3DXVECTOR3		v6 = p3 - p0;

				// �O�ςŊe�ӂ̖@�������߂āA�|���S���̖@���Ƃ̓��ς��Ƃ���??���`�F�b�N����
				D3DXVECTOR3		n1, n2, n3;

				math->crossProduct(&n1, &v4, &v1);
				if (math->dotProduct(&n1, &nor) < 0.0f)
				{
					return(false); // �������Ă��Ȃ�
				}

				math->crossProduct(&n2, &v5, &v2);
				if (math->dotProduct(&n2, &nor) < 0.0f)  // �������Ă��Ȃ�
				{
					return(false);
				}

				math->crossProduct(&n3, &v6, &v3);
				if (math->dotProduct(&n3, &nor) < 0.0f)  // �������Ă��Ȃ�
				{
					
					return(false);
				}
			}
		}


		return(true);	// �������Ă���I(hit�ɂ͓������Ă����_�������Ă���Bnormal�ɂ͖@���������Ă���)
	}

}