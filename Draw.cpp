#include "Renderer.h"

namespace FIGHTING_GAME
{
	
	void Renderer::Draw_3DModel(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL model,bool fuchi, int	color_a)
	{
		
		this->SetCullingMode(CULL_MODE_NONE);
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		this->SetWorldMatrix(&mtxWorld);
		//����� LOCK ON
		if (fuchi == true)
		{
			this->SetFuchi(1);
		}
		else
		{
			this->SetFuchi(0);
		}
		this->DrawModel(&model, color_a);

		// �J�����O�ݒ��߂�
		this->SetCullingMode(CULL_MODE_BACK);
	}
	
	void Renderer::Draw_3DModel_Part(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL* model)
	{
		this->SetCullingMode(CULL_MODE_NONE);
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		
		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorld_parent);
		// ��
		// g_Player.mtxWorld���w���Ă���
		
		// ���[���h�}�g���b�N�X�̐ݒ�
		this->SetWorldMatrix(&mtxWorld);

		// ���f���`��
		this->DrawModel(model,0);

		// �J�����O�ݒ��߂�
		this->SetCullingMode(CULL_MODE_BACK);
	}
	void Renderer::Draw_2DPlane_plural(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		int	nNumVertexIndex,D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld)
	{
		// ���C�e�B���O�I�t
		this->SetLightEnable(false);
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		this->GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// �v���~�e�B�u�g�|���W�ݒ�
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �e�N�X�`���ݒ�
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		// �}�e���A���ݒ�
		this->SetMaterial(&material);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		this->SetWorldMatrix(&mtxWorld);


		// �|���S���̕`��
		this->GetDeviceContext()->DrawIndexed(nNumVertexIndex, 0, 0);

		// ���C�e�B���O�I��
		this->SetLightEnable(true);
	}
	void Renderer::Draw_2DPlane_single(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		int	nNumVertexIndex, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, D3DXMATRIX	mtxWorld)
	{
		// ���C�e�B���O�I�t
		this->SetLightEnable(false);
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �e�N�X�`���ݒ�
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		this->SetWorldMatrix(&mtxWorld);

		// �}�e���A���ݒ�
		this->SetMaterial(&material);

		// �|���S���`��

		GetDeviceContext()->Draw(4, 0);
		// ���C�e�B���O�I��
		this->SetLightEnable(true);
	}

	void Renderer::Draw_2DPlane_NOZ(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, float px, float py, float pw, float ph, float tw, float th
		, float tx, float ty, D3DXCOLOR	color)
	{
		// ���C�g�𖳌�������
		this->SetLightEnable(false);
		// Z��r�Ȃ�
		//this->SetDepthEnable(false);
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �}�g���N�X�ݒ�
		this->SetWorldViewProjection2D();

		// �v���~�e�B�u�g�|���W�ݒ�
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �}�e���A���ݒ�
		MATERIAL_BASE material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		this->SetMaterial(&material);

		// �e�N�X�`���ݒ�
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		this->SetSpriteColor(vertexBuffer, px, py, pw, ph, tw, th, tx,ty, color);

		this->GetDeviceContext()->Draw(4, 0);

		//���C�g��L���ɂ���
		this->SetLightEnable(true);
		// Z��r�L��
		//this->SetDepthEnable(true);
	}

	void Renderer::Draw_2DPlane_All2D(ID3D11Buffer *vertexBuffer, D3DXMATRIX mtxWorldParticle, D3DXMATRIX g_camera_mtxView, D3DXVECTOR3 scale, D3DXVECTOR3 pos,
		MATERIAL_BASE material,ID3D11ShaderResourceView	*g_Texture)
	{
		// ���C�e�B���O�𖳌���
		this->SetLightEnable(false);

		// ���Z�����ɐݒ�
		this->SetBlendState(BLEND_MODE_ADD);
		
		// Z��r����
		this->SetDepthEnable(false);

		// �t�H�O����
		//SetFogEnable(false);

		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


		// �e�N�X�`���ݒ�
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorldParticle);

		// �r���[�}�g���b�N�X���擾
		mtxView = g_camera_mtxView;

		mtxWorldParticle._11 = mtxView._11;
		mtxWorldParticle._12 = mtxView._21;
		mtxWorldParticle._13 = mtxView._31;
		mtxWorldParticle._21 = mtxView._12;
		mtxWorldParticle._22 = mtxView._22;
		mtxWorldParticle._23 = mtxView._32;
		mtxWorldParticle._31 = mtxView._13;
		mtxWorldParticle._32 = mtxView._23;
		mtxWorldParticle._33 = mtxView._33;

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, scale.x,scale.y, scale.z);
		D3DXMatrixMultiply(&mtxWorldParticle, &mtxWorldParticle, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y,pos.z);
		D3DXMatrixMultiply(&mtxWorldParticle, &mtxWorldParticle, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		this->SetWorldMatrix(&mtxWorldParticle);

		// �}�e���A���ݒ�
		this->SetMaterial(&material);

		// �|���S���̕`��
		this->GetDeviceContext()->Draw(4, 0);


		// ���C�e�B���O��L����
		this->SetLightEnable(true);
		// �ʏ�u�����h�ɖ߂�
		this->SetBlendState(BLEND_MODE_ALPHABLEND);
		// Z��r�L��
		this->SetDepthEnable(true);
		// �t�H�O�L��
		//SetFogEnable(true);
	}

	void Renderer::Draw_Collider_box(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld, Collider3D_Tag tag,
		float wx, float hy, float lz, float r)
	{
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		D3DXMatrixIdentity(&mtxWorld);
		
		D3DXMatrixScaling(&mtxScl,wx,hy, lz);
		
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.5f); // set color
		switch (tag)
		{
		case Stage_object:
			material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.5f);
			break;
		case Player_object:
			material.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.5f);
			break;
		case Player_Part_object:
			material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.5f);
			break;
		case Enemy_object:
			material.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.5f);
			break;
		case Enemy_Part_object:
			material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.5f);
			break;
		}
		this->SetMaterial(&material);

		// �|���S���`��
		
		for (int i = 0; i < 7; i++) {
			GetDeviceContext()->Draw(2, i);
		}
		for (int i = 8; i < 23; i++) {
			GetDeviceContext()->Draw(2, i);
		}
		GetDeviceContext()->Draw(2, 24);
			
		// ���C�e�B���O��L��
		SetLightEnable(true);
	}
	//=============================================================================
// �`�揈��
//=============================================================================
	void Renderer::DrawModel(DX11_MODEL *Model, int	color_a)
	{

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &Model->VertexBuffer, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		this->GetDeviceContext()->IASetIndexBuffer(Model->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// �v���~�e�B�u�g�|���W�ݒ�
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		for (unsigned short i = 0; i < Model->SubsetNum; i++)
		{
			if (color_a == 1)
			{
				Model->SubsetArray[i].Material.Material.Diffuse.a = 0.3f;
			}
			else
			{
				Model->SubsetArray[i].Material.Material.Diffuse.a = 1.0f;
			}
			
			// �}�e���A���ݒ�
			this->SetMaterial(&Model->SubsetArray[i].Material.Material);

			// �e�N�X�`���ݒ�
			this->GetDeviceContext()->PSSetShaderResources(0, 1, &Model->SubsetArray[i].Material.Texture);

			// �|���S���`��
			this->GetDeviceContext()->DrawIndexed(Model->SubsetArray[i].IndexNum, Model->SubsetArray[i].StartIndex, 0);

			
		}
		
	}


	void Renderer::LoadModel(char *FileName, DX11_MODEL *Model)
	{
		MODEL model;

		this->LoadObj(FileName, &model, Model);

		// ���_�o�b�t�@����
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D_BASE) * model.VertexNum;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = model.VertexArray;

			this->GetDevice()->CreateBuffer(&bd, &sd, &Model->VertexBuffer);
		}


		// �C���f�b�N�X�o�b�t�@����
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * model.IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = model.IndexArray;

			this->GetDevice()->CreateBuffer(&bd, &sd, &Model->IndexBuffer);
		}

		// �T�u�Z�b�g�ݒ�
		{
			Model->SubsetArray = new DX11_SUBSET[model.SubsetNum];
			Model->SubsetNum = model.SubsetNum;

			for (unsigned short i = 0; i < model.SubsetNum; i++)
			{
				Model->SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
				Model->SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;

				Model->SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;

				D3DX11CreateShaderResourceViewFromFile(this->GetDevice(),
					model.SubsetArray[i].Material.TextureName,
					NULL,
					NULL,
					&Model->SubsetArray[i].Material.Texture,
					NULL);
			}
		}

		delete[] model.VertexArray;
		delete[] model.IndexArray;
		delete[] model.SubsetArray;


	}
	//=============================================================================
	// �I������
	//=============================================================================
	void Renderer::UnloadModel(DX11_MODEL *Model)
	{

		if (Model->VertexBuffer)		Model->VertexBuffer->Release();
		if (Model->IndexBuffer)		Model->IndexBuffer->Release();
		if (Model->SubsetArray)		delete[] Model->SubsetArray;
	}


	//���f���Ǎ�////////////////////////////////////////////
	void Renderer::LoadObj(char *FileName, MODEL *Model, DX11_MODEL *D3DXModel)
	{

		D3DXVECTOR3	*positionArray;
		D3DXVECTOR3	*normalArray;
		D3DXVECTOR2	*texcoordArray;

		unsigned short	positionNum = 0;
		unsigned short	normalNum = 0;
		unsigned short	texcoordNum = 0;
		unsigned short	vertexNum = 0;
		unsigned short	indexNum = 0;
		unsigned short	in = 0;
		unsigned short	subsetNum = 0;

		MODEL_MATERIAL	*materialArray = new MODEL_MATERIAL();
		unsigned short	materialNum = 0;

		char str[256];
		char *s;
		char c;


		FILE *file;
		file = fopen(FileName, "rt");
		if (file == NULL)
		{
			printf("�G���[:LoadModel %s \n", FileName);
			return;
		}



		//�v�f���J�E���g
		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;

			if (strcmp(str, "v") == 0)
			{
				positionNum++;
			}
			else if (strcmp(str, "vn") == 0)
			{
				normalNum++;
			}
			else if (strcmp(str, "vt") == 0)
			{
				texcoordNum++;
			}
			else if (strcmp(str, "usemtl") == 0)
			{
				subsetNum++;
			}
			else if (strcmp(str, "f") == 0)
			{
				in = 0;

				do
				{
					fscanf(file, "%s", str);
					vertexNum++;
					in++;
					c = fgetc(file);
				} while (c != '\n' && c != '\r');

				//�l�p�͎O�p�ɕ���
				if (in == 4)
					in = 6;

				indexNum += in;
			}
		}


		//�������m��
		positionArray = new D3DXVECTOR3[positionNum];
		normalArray = new D3DXVECTOR3[normalNum];
		texcoordArray = new D3DXVECTOR2[texcoordNum];


		Model->VertexArray = new VERTEX_3D_BASE[vertexNum];
		Model->VertexNum = vertexNum;

		Model->IndexArray = new unsigned short[indexNum];
		Model->IndexNum = indexNum;

		Model->SubsetArray = new SUBSET[subsetNum];
		Model->SubsetNum = subsetNum;




		//�v�f�Ǎ�
		D3DXVECTOR3 *position = positionArray;
		D3DXVECTOR3 *normal = normalArray;
		D3DXVECTOR2 *texcoord = texcoordArray;

		unsigned short vc = 0;
		unsigned short ic = 0;
		unsigned short sc = 0;

		//MeshCollider
		D3DXModel->VertexNum = positionNum;
		D3DXModel->IndexNum = indexNum;
		D3DXModel->Vertexlist = new D3DXVECTOR3[positionNum];
		D3DXModel->Indexlist = new unsigned short[indexNum];

		fseek(file, 0, SEEK_SET);

		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;

			if (strcmp(str, "mtllib") == 0)
			{
				//�}�e���A���t�@�C��
				fscanf(file, "%s", str);

				char path[256];
				strcpy(path, "data/model/");
				strcat(path, str);

				LoadMaterial(path, &materialArray, &materialNum);
			}
			else if (strcmp(str, "o") == 0)
			{
				//�I�u�W�F�N�g��
				fscanf(file, "%s", str);
			}
			else if (strcmp(str, "v") == 0)
			{
				//���_���W
				fscanf(file, "%f", &position->x);
				fscanf(file, "%f", &position->y);
				fscanf(file, "%f", &position->z);
				position->x *= SCALE_MODEL;
				position->y *= SCALE_MODEL;
				position->z *= SCALE_MODEL;
				position++;
			}
			else if (strcmp(str, "vn") == 0)
			{
				//�@��
				fscanf(file, "%f", &normal->x);
				fscanf(file, "%f", &normal->y);
				fscanf(file, "%f", &normal->z);
				normal++;
			}
			else if (strcmp(str, "vt") == 0)
			{
				//�e�N�X�`�����W
				fscanf(file, "%f", &texcoord->x);
				fscanf(file, "%f", &texcoord->y);
				texcoord->y = 1.0f - texcoord->y;
				texcoord++;
			}
			else if (strcmp(str, "usemtl") == 0)
			{
				//�}�e���A��
				fscanf(file, "%s", str);

				if (sc != 0)
					Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;

				Model->SubsetArray[sc].StartIndex = ic;


				for (unsigned short i = 0; i < materialNum; i++)
				{
					if (strcmp(str, materialArray[i].Name) == 0)
					{
						Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
						strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
						strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);

						break;
					}
				}

				sc++;

			}
			else if (strcmp(str, "f") == 0)
			{
				//��
				in = 0;

				do
				{
					fscanf(file, "%s", str);

					s = strtok(str, "/");
					Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
					D3DXModel->Indexlist[ic] = atoi(s) - 1;

					if (s[strlen(s) + 1] != '/')
					{
						//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
						s = strtok(NULL, "/");
						Model->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
					}
					s = strtok(NULL, "/");
					Model->VertexArray[vc].Normal = normalArray[atoi(s) - 1];

					Model->VertexArray[vc].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					Model->IndexArray[ic] = vc;
					ic++;
					vc++;

					in++;
					c = fgetc(file);
				} while (c != '\n' && c != '\r');

				//�l�p�͎O�p�ɕ���
				if (in == 4)
				{
					Model->IndexArray[ic] = vc - 4;
					D3DXModel->Indexlist[ic] = D3DXModel->Indexlist[ic - 4]; // point 1
					ic++;
					Model->IndexArray[ic] = vc - 2;
					D3DXModel->Indexlist[ic] = D3DXModel->Indexlist[ic - 3]; // point 3 -> 4 1 3 to make triangle face
					ic++;
				}
			}
		}


		if (sc != 0)
			Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;

		for (int i = 0; i < positionNum; i++) {
			D3DXModel->Vertexlist[i] = positionArray[i];
		}
		//for (int i = 0; i < indexNum; i++) {
		//	D3DXModel->Indexlist[i] = Model->IndexArray[i];
		//}


		delete[] positionArray;
		delete[] normalArray;
		delete[] texcoordArray;
		delete[] materialArray;

		fclose(file);
	}

	//�}�e���A���ǂݍ���///////////////////////////////////////////////////////////////////
	void Renderer::LoadMaterial(char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum)
	{
		char str[256];

		FILE *file;
		file = fopen(FileName, "rt");
		if (file == NULL)
		{
			printf("�G���[:LoadMaterial %s \n", FileName);
			return;
		}

		MODEL_MATERIAL *materialArray;
		unsigned short materialNum = 0;

		//�v�f���J�E���g
		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;


			if (strcmp(str, "newmtl") == 0)
			{
				materialNum++;
			}
		}


		//�������m��
		materialArray = new MODEL_MATERIAL[materialNum];
		ZeroMemory(materialArray, sizeof(MODEL_MATERIAL)*materialNum);

		//�v�f�Ǎ�
		int mc = -1;

		fseek(file, 0, SEEK_SET);

		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;


			if (strcmp(str, "newmtl") == 0)
			{
				//�}�e���A����
				mc++;
				fscanf(file, "%s", materialArray[mc].Name);
				strcpy(materialArray[mc].TextureName, "");
			}
			else if (strcmp(str, "Ka") == 0)
			{
				//�A���r�G���g
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.r);
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.g);
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.b);
				materialArray[mc].Material.Ambient.a = 1.0f;
			}
			else if (strcmp(str, "Kd") == 0)
			{
				//�f�B�t���[�Y
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.r);
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.g);
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.b);
				materialArray[mc].Material.Diffuse.a = 1.0f;
			}
			else if (strcmp(str, "Ks") == 0)
			{
				//�X�y�L����
				fscanf(file, "%f", &materialArray[mc].Material.Specular.r);
				fscanf(file, "%f", &materialArray[mc].Material.Specular.g);
				fscanf(file, "%f", &materialArray[mc].Material.Specular.b);
				materialArray[mc].Material.Specular.a = 1.0f;
			}
			else if (strcmp(str, "Ns") == 0)
			{
				//�X�y�L�������x
				fscanf(file, "%f", &materialArray[mc].Material.Shininess);
			}
			else if (strcmp(str, "d") == 0)
			{
				//�A���t�@
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.a);
			}
			else if (strcmp(str, "map_Kd") == 0)
			{
				//�e�N�X�`��
				fscanf(file, "%s", str);

				char path[256];
				strcpy(path, "data/model/");
				strcat(path, str);

				strcat(materialArray[mc].TextureName, path);
			}
		}


		*MaterialArray = materialArray;
		*MaterialNum = materialNum;

		fclose(file);
	}

}