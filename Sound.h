#include "Main.h"
namespace FIGHTING_GAME
{

#ifndef _SOUND_H_
#define _SOUND_H_
	class Sound :GameDate
	{
	private:
		//*****************************************************************************
		// �p�����[�^�\���̒�`
		//*****************************************************************************
		typedef struct
		{
			char *pFilename;	// �t�@�C����
			int nCntLoop;		// ���[�v�J�E���g
		} SOUNDPARAM;
		//*****************************************************************************
		// �v���g�^�C�v�錾
		//*****************************************************************************
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
		//*****************************************************************************
		// �O���[�o���ϐ�
		//*****************************************************************************
		IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
		IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
		IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
		BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
		DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

		// �e���f�ނ̃p�����[�^
		SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
		{
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra08.wav", -1 },	// BGM0
			{ (char*)"data/BGM/bgm_maoudamashii_neorock49 .wav", -1 },	// BGM1
			{ (char*)"data/BGM/bgm_maoudamashii_neorock52.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra20.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra26.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_acoustic32.wav", -1 },	// BGM2

			{ (char*)"data/SE/bomb000.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/defend000.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/defend001.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/hit000.wav", 0 },			// �e���ˉ�
			{ (char*)"data/SE/laser000.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/lockon000.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/shot000.wav", 0 },		// �e���ˉ�
			{ (char*)"data/SE/shot001.wav", 0 },		// �q�b�g��
		};
	public:
		Sound(HWND hWnd);
		bool InitSound(HWND hWnd);
		void UninitSound(void);
		void PlaySound(int label);
		void StopSound(int label);
		void StopSound(void);
	};
#endif


}