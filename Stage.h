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
			D3DXVECTOR3			rot;				// ���f���̌���(��])
			D3DXVECTOR3			rot_move;			// ���f���̌���(��])
			D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
			Stage_Model_Num		model_num;				// ���f�����
			D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
			int					shadowIdx;			// �e�̃C���f�b�N�X�ԍ�
			int					*collider_index;
			float				collider_radius;
			int					index_max;
		};
		class TwoDPlane_single_data
		{
		public:
			int PlaneType;
			D3DXCOLOR col;
			ID3D11Buffer	*vertexBuffer;	// ���_�o�b�t�@
			ID3D11Buffer	*indexBuffer;	// �C���f�b�N�X�o�b�t�@
			ID3D11ShaderResourceView	*g_Texture;
			int				texnum;
			D3DXMATRIX		mtxWorld;					// ���[���h�}�g���b�N�X
			D3DXVECTOR3		pos;						// �|���S���\���ʒu�̒��S���W
			D3DXVECTOR3		rot;						// �|���S���̉�]�p
			MATERIAL_BASE	material;					// �}�e���A��
			VERTEX_3D_BASE		*g_Vertex;
			bool			use;
			bool			cameracheck;	//true�Ȃ�΁APLAYER�̑O�ł�
			bool			DrawCheck;		//TRUE�Ȃ�΁A�J�����͈̔͊O
		};
		class TwoDPlane_plural_data
		{
		public:
			int PlaneType;
			D3DXCOLOR col;
			ID3D11Buffer	*vertexBuffer;	// ���_�o�b�t�@
			ID3D11Buffer	*indexBuffer;	// �C���f�b�N�X�o�b�t�@
			ID3D11ShaderResourceView	*g_Texture;
			int				texnum;
			D3DXMATRIX		mtxWorld;					// ���[���h�}�g���b�N�X
			D3DXVECTOR3		pos;						// �|���S���\���ʒu�̒��S���W
			D3DXVECTOR3		rot;						// �|���S���̉�]�p
			MATERIAL_BASE	material;					// �}�e���A��
			int				nNumBlockX, nNumBlockZ, nNumBlockY;		// �u���b�N��
			int				nNumVertex;					// �����_��	
			int				nNumVertexIndex;			// ���C���f�b�N�X��
			int				nNumPolygon;				// ���|���S����
			float			fBlockSizeX, fBlockSizeZ, fBlockSizeY;	// �u���b�N�T�C�Y
			int				yblock;
			float			fBlockSizeY_X;				//�E��������SLOPE
			float			fBlockSizeY_Z;				//�㉺������SLOPE
			VERTEX_3D_BASE		*g_Vertex;
			bool			use;
			bool			cameracheck;	//true�Ȃ�΁APLAYER�̑O�ł�
			bool			DrawCheck;		//TRUE�Ȃ�΁A�J�����͈̔͊O
		};
		class TwoDPlane_NOZ_data
		{
		public:
			int PlaneType;
			bool					g_Use;						// true:�g���Ă���  false:���g�p
			float					g_w, g_h;					// ���ƍ���
			float					window_w, window_h;						// �|���S���̍��W
			ID3D11Buffer			*g_vertexBuffer;
			ID3D11ShaderResourceView	*g_Texture;
			D3DXMATRIX				mtxWorld;
			D3DXVECTOR3 scl;			// �X�P�[��
			MATERIAL_BASE	material;		// �}�e���A��
			D3DXCOLOR				g_Color;
			char* TextureName;
		};
		class TwoDPlane_All2D_data
		{
		public:
			int PlaneType;
			D3DXVECTOR3		pos;			// �ʒu
			D3DXVECTOR3		rot;			// ��]
			D3DXVECTOR3		scale;			// �X�P�[��
			D3DXVECTOR3		move;			// �ړ���
			MATERIAL_BASE	material;		// �}�e���A��
			ID3D11Buffer	*g_vertexBuffer;
			float			fSizeX;			// ��
			float			fSizeY;			// ����
			int				nIdxShadow;		// �eID
			int				nLife;			// ����
			bool			bUse;			// �g�p���Ă��邩�ǂ���
			D3DXMATRIX g_mtxView;
			ID3D11ShaderResourceView	*g_Texture;
			D3DXMATRIX				g_mtxWorldParticle;// ���[���h�}�g���b�N�X
			D3DXVECTOR3				g_posBase;// �r���{�[�h�����ʒu
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