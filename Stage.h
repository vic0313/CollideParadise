#include "Main.h"

namespace FIGHTING_GAME
{
#ifndef _STAGE_H_
#define _STAGE_H_


	class Stage
	{
	protected:
		
		enum Type_2Dplane
		{
			STAGE_2DPLANE_SINGLE = 0,
			STAGE_2DPLANE_PLURAL,
			STAGE_2DPLANE_NOZ,
			STAGE_2DPLANE_ALLZ,
		};
		class ThreeDModel_data
		{
		public:
			int					color_a;
			bool				use;
			D3DXVECTOR3			pos;
			D3DXVECTOR3			collider_pos;
			D3DXVECTOR3			rot;				// モデルの向き(回転)
			D3DXVECTOR3			rot_move;			// モデルの向き(回転)
			D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
			Stage_Model_Num		model_num;				// モデル情報
			D3DXMATRIX			mtxWorld;			// ワールドマトリックス
			int					shadowIdx;			// 影のインデックス番号
			int					*collider_index;
			float				collider_radius;
			int					index_max;
		};
		class TwoDPlane_single_data
		{
		public:
			int PlaneType;
			D3DXCOLOR col;
			ID3D11Buffer	*vertexBuffer;	// 頂点バッファ
			ID3D11Buffer	*indexBuffer;	// インデックスバッファ
			ID3D11ShaderResourceView	*g_Texture;
			int				texnum;
			D3DXMATRIX		mtxWorld;					// ワールドマトリックス
			D3DXVECTOR3		pos;						// ポリゴン表示位置の中心座標
			D3DXVECTOR3		rot;						// ポリゴンの回転角
			MATERIAL_BASE	material;					// マテリアル
			VERTEX_3D_BASE		*g_Vertex;
			bool			use;
			bool			cameracheck;	//trueならば、PLAYERの前です
			bool			DrawCheck;		//TRUEならば、カメラの範囲外
		};
		class TwoDPlane_plural_data
		{
		public:
			int PlaneType;
			D3DXCOLOR col;
			ID3D11Buffer	*vertexBuffer;	// 頂点バッファ
			ID3D11Buffer	*indexBuffer;	// インデックスバッファ
			ID3D11ShaderResourceView	*g_Texture;
			int				texnum;
			D3DXMATRIX		mtxWorld;					// ワールドマトリックス
			D3DXVECTOR3		pos;						// ポリゴン表示位置の中心座標
			D3DXVECTOR3		rot;						// ポリゴンの回転角
			MATERIAL_BASE	material;					// マテリアル
			int				nNumBlockX, nNumBlockZ, nNumBlockY;		// ブロック数
			int				nNumVertex;					// 総頂点数	
			int				nNumVertexIndex;			// 総インデックス数
			int				nNumPolygon;				// 総ポリゴン数
			float			fBlockSizeX, fBlockSizeZ, fBlockSizeY;	// ブロックサイズ
			int				yblock;
			float			fBlockSizeY_X;				//右左向けのSLOPE
			float			fBlockSizeY_Z;				//上下向けのSLOPE
			VERTEX_3D_BASE		*g_Vertex;
			bool			use;
			bool			cameracheck;	//trueならば、PLAYERの前です
			bool			DrawCheck;		//TRUEならば、カメラの範囲外
		};
		class TwoDPlane_NOZ_data
		{
		public:
			int PlaneType;
			bool					g_Use;						// true:使っている  false:未使用
			float					g_w, g_h;					// 幅と高さ
			float					window_w, window_h;						// ポリゴンの座標
			ID3D11Buffer			*g_vertexBuffer;
			ID3D11ShaderResourceView	*g_Texture;
			D3DXMATRIX				mtxWorld;
			D3DXVECTOR3 scl;			// スケール
			MATERIAL_BASE	material;		// マテリアル
			D3DXCOLOR				g_Color;
			char* TextureName;
		};
		class TwoDPlane_All2D_data
		{
		public:
			int PlaneType;
			D3DXVECTOR3		pos;			// 位置
			D3DXVECTOR3		rot;			// 回転
			D3DXVECTOR3		scale;			// スケール
			D3DXVECTOR3		move;			// 移動量
			MATERIAL_BASE	material;		// マテリアル
			ID3D11Buffer	*g_vertexBuffer;
			float			fSizeX;			// 幅
			float			fSizeY;			// 高さ
			int				nIdxShadow;		// 影ID
			int				nLife;			// 寿命
			bool			bUse;			// 使用しているかどうか
			D3DXMATRIX g_mtxView;
			ID3D11ShaderResourceView	*g_Texture;
			D3DXMATRIX				g_mtxWorldParticle;// ワールドマトリックス
			D3DXVECTOR3				g_posBase;// ビルボード発生位置
			//bool			usecheck;
		};
	public:
		virtual HRESULT InitStage();
		virtual void UninitStage();
		virtual void UpdateStage();
		virtual void DrawStage();
	
	};
#endif
}