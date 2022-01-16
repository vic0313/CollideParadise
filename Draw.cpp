#include "Renderer.h"

namespace FIGHTING_GAME
{
	
	void Renderer::Draw_3DModel(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL model,bool fuchi, int	color_a)
	{
		
		this->SetCullingMode(CULL_MODE_NONE);
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		this->SetWorldMatrix(&mtxWorld);
		//縁取り LOCK ON
		if (fuchi == true)
		{
			this->SetFuchi(1);
		}
		else
		{
			this->SetFuchi(0);
		}
		this->DrawModel(&model, color_a);

		// カリング設定を戻す
		this->SetCullingMode(CULL_MODE_BACK);
	}
	
	void Renderer::Draw_3DModel_Part(D3DXMATRIX mtxWorld, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos, DX11_MODEL* model)
	{
		this->SetCullingMode(CULL_MODE_NONE);
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		
		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorld_parent);
		// ↑
		// g_Player.mtxWorldを指している
		
		// ワールドマトリックスの設定
		this->SetWorldMatrix(&mtxWorld);

		// モデル描画
		this->DrawModel(model,0);

		// カリング設定を戻す
		this->SetCullingMode(CULL_MODE_BACK);
	}
	void Renderer::Draw_2DPlane_plural(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		int	nNumVertexIndex,D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld)
	{
		// ライティングオフ
		this->SetLightEnable(false);
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		this->GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// プリミティブトポロジ設定
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// テクスチャ設定
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		// マテリアル設定
		this->SetMaterial(&material);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		this->SetWorldMatrix(&mtxWorld);


		// ポリゴンの描画
		this->GetDeviceContext()->DrawIndexed(nNumVertexIndex, 0, 0);

		// ライティングオン
		this->SetLightEnable(true);
	}
	void Renderer::Draw_2DPlane_single(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		int	nNumVertexIndex, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, D3DXMATRIX	mtxWorld)
	{
		// ライティングオフ
		this->SetLightEnable(false);
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// テクスチャ設定
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		this->SetWorldMatrix(&mtxWorld);

		// マテリアル設定
		this->SetMaterial(&material);

		// ポリゴン描画

		GetDeviceContext()->Draw(4, 0);
		// ライティングオン
		this->SetLightEnable(true);
	}

	void Renderer::Draw_2DPlane_NOZ(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, float px, float py, float pw, float ph, float tw, float th
		, float tx, float ty, D3DXCOLOR	color)
	{
		// ライトを無効化する
		this->SetLightEnable(false);
		// Z比較なし
		//this->SetDepthEnable(false);
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// マトリクス設定
		this->SetWorldViewProjection2D();

		// プリミティブトポロジ設定
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// マテリアル設定
		MATERIAL_BASE material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		this->SetMaterial(&material);

		// テクスチャ設定
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		this->SetSpriteColor(vertexBuffer, px, py, pw, ph, tw, th, tx,ty, color);

		this->GetDeviceContext()->Draw(4, 0);

		//ライトを有効にする
		this->SetLightEnable(true);
		// Z比較有効
		//this->SetDepthEnable(true);
	}

	void Renderer::Draw_2DPlane_All2D(ID3D11Buffer *vertexBuffer, D3DXMATRIX mtxWorldParticle, D3DXMATRIX g_camera_mtxView, D3DXVECTOR3 scale, D3DXVECTOR3 pos,
		MATERIAL_BASE material,ID3D11ShaderResourceView	*g_Texture)
	{
		// ライティングを無効に
		this->SetLightEnable(false);

		// 加算合成に設定
		this->SetBlendState(BLEND_MODE_ADD);
		
		// Z比較無し
		this->SetDepthEnable(false);

		// フォグ無効
		//SetFogEnable(false);

		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		this->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


		// テクスチャ設定
		this->GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorldParticle);

		// ビューマトリックスを取得
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

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, scale.x,scale.y, scale.z);
		D3DXMatrixMultiply(&mtxWorldParticle, &mtxWorldParticle, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y,pos.z);
		D3DXMatrixMultiply(&mtxWorldParticle, &mtxWorldParticle, &mtxTranslate);

		// ワールドマトリックスの設定
		this->SetWorldMatrix(&mtxWorldParticle);

		// マテリアル設定
		this->SetMaterial(&material);

		// ポリゴンの描画
		this->GetDeviceContext()->Draw(4, 0);


		// ライティングを有効に
		this->SetLightEnable(true);
		// 通常ブレンドに戻す
		this->SetBlendState(BLEND_MODE_ALPHABLEND);
		// Z比較有効
		this->SetDepthEnable(true);
		// フォグ有効
		//SetFogEnable(true);
	}

	void Renderer::Draw_Collider_box(ID3D11Buffer *vertexBuffer, ID3D11ShaderResourceView	*g_Texture, MATERIAL_BASE material,
		D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXMATRIX	mtxWorld, Collider3D_Tag tag,
		float wx, float hy, float lz, float r)
	{
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		D3DXMatrixIdentity(&mtxWorld);
		
		D3DXMatrixScaling(&mtxScl,wx,hy, lz);
		
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
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

		// ポリゴン描画
		
		for (int i = 0; i < 7; i++) {
			GetDeviceContext()->Draw(2, i);
		}
		for (int i = 8; i < 23; i++) {
			GetDeviceContext()->Draw(2, i);
		}
		GetDeviceContext()->Draw(2, 24);
			
		// ライティングを有効
		SetLightEnable(true);
	}
	//=============================================================================
// 描画処理
//=============================================================================
	void Renderer::DrawModel(DX11_MODEL *Model, int	color_a)
	{

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D_BASE);
		UINT offset = 0;
		this->GetDeviceContext()->IASetVertexBuffers(0, 1, &Model->VertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		this->GetDeviceContext()->IASetIndexBuffer(Model->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// プリミティブトポロジ設定
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
			
			// マテリアル設定
			this->SetMaterial(&Model->SubsetArray[i].Material.Material);

			// テクスチャ設定
			this->GetDeviceContext()->PSSetShaderResources(0, 1, &Model->SubsetArray[i].Material.Texture);

			// ポリゴン描画
			this->GetDeviceContext()->DrawIndexed(Model->SubsetArray[i].IndexNum, Model->SubsetArray[i].StartIndex, 0);

			
		}
		
	}


	void Renderer::LoadModel(char *FileName, DX11_MODEL *Model)
	{
		MODEL model;

		this->LoadObj(FileName, &model, Model);

		// 頂点バッファ生成
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


		// インデックスバッファ生成
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

		// サブセット設定
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
	// 終了処理
	//=============================================================================
	void Renderer::UnloadModel(DX11_MODEL *Model)
	{

		if (Model->VertexBuffer)		Model->VertexBuffer->Release();
		if (Model->IndexBuffer)		Model->IndexBuffer->Release();
		if (Model->SubsetArray)		delete[] Model->SubsetArray;
	}


	//モデル読込////////////////////////////////////////////
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
			printf("エラー:LoadModel %s \n", FileName);
			return;
		}



		//要素数カウント
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

				//四角は三角に分割
				if (in == 4)
					in = 6;

				indexNum += in;
			}
		}


		//メモリ確保
		positionArray = new D3DXVECTOR3[positionNum];
		normalArray = new D3DXVECTOR3[normalNum];
		texcoordArray = new D3DXVECTOR2[texcoordNum];


		Model->VertexArray = new VERTEX_3D_BASE[vertexNum];
		Model->VertexNum = vertexNum;

		Model->IndexArray = new unsigned short[indexNum];
		Model->IndexNum = indexNum;

		Model->SubsetArray = new SUBSET[subsetNum];
		Model->SubsetNum = subsetNum;




		//要素読込
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
				//マテリアルファイル
				fscanf(file, "%s", str);

				char path[256];
				strcpy(path, "data/model/");
				strcat(path, str);

				LoadMaterial(path, &materialArray, &materialNum);
			}
			else if (strcmp(str, "o") == 0)
			{
				//オブジェクト名
				fscanf(file, "%s", str);
			}
			else if (strcmp(str, "v") == 0)
			{
				//頂点座標
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
				//法線
				fscanf(file, "%f", &normal->x);
				fscanf(file, "%f", &normal->y);
				fscanf(file, "%f", &normal->z);
				normal++;
			}
			else if (strcmp(str, "vt") == 0)
			{
				//テクスチャ座標
				fscanf(file, "%f", &texcoord->x);
				fscanf(file, "%f", &texcoord->y);
				texcoord->y = 1.0f - texcoord->y;
				texcoord++;
			}
			else if (strcmp(str, "usemtl") == 0)
			{
				//マテリアル
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
				//面
				in = 0;

				do
				{
					fscanf(file, "%s", str);

					s = strtok(str, "/");
					Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
					D3DXModel->Indexlist[ic] = atoi(s) - 1;

					if (s[strlen(s) + 1] != '/')
					{
						//テクスチャ座標が存在しない場合もある
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

				//四角は三角に分割
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

	//マテリアル読み込み///////////////////////////////////////////////////////////////////
	void Renderer::LoadMaterial(char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum)
	{
		char str[256];

		FILE *file;
		file = fopen(FileName, "rt");
		if (file == NULL)
		{
			printf("エラー:LoadMaterial %s \n", FileName);
			return;
		}

		MODEL_MATERIAL *materialArray;
		unsigned short materialNum = 0;

		//要素数カウント
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


		//メモリ確保
		materialArray = new MODEL_MATERIAL[materialNum];
		ZeroMemory(materialArray, sizeof(MODEL_MATERIAL)*materialNum);

		//要素読込
		int mc = -1;

		fseek(file, 0, SEEK_SET);

		while (true)
		{
			fscanf(file, "%s", str);

			if (feof(file) != 0)
				break;


			if (strcmp(str, "newmtl") == 0)
			{
				//マテリアル名
				mc++;
				fscanf(file, "%s", materialArray[mc].Name);
				strcpy(materialArray[mc].TextureName, "");
			}
			else if (strcmp(str, "Ka") == 0)
			{
				//アンビエント
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.r);
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.g);
				fscanf(file, "%f", &materialArray[mc].Material.Ambient.b);
				materialArray[mc].Material.Ambient.a = 1.0f;
			}
			else if (strcmp(str, "Kd") == 0)
			{
				//ディフューズ
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.r);
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.g);
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.b);
				materialArray[mc].Material.Diffuse.a = 1.0f;
			}
			else if (strcmp(str, "Ks") == 0)
			{
				//スペキュラ
				fscanf(file, "%f", &materialArray[mc].Material.Specular.r);
				fscanf(file, "%f", &materialArray[mc].Material.Specular.g);
				fscanf(file, "%f", &materialArray[mc].Material.Specular.b);
				materialArray[mc].Material.Specular.a = 1.0f;
			}
			else if (strcmp(str, "Ns") == 0)
			{
				//スペキュラ強度
				fscanf(file, "%f", &materialArray[mc].Material.Shininess);
			}
			else if (strcmp(str, "d") == 0)
			{
				//アルファ
				fscanf(file, "%f", &materialArray[mc].Material.Diffuse.a);
			}
			else if (strcmp(str, "map_Kd") == 0)
			{
				//テクスチャ
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