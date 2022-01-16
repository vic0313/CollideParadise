#include "Main.h"
namespace FIGHTING_GAME
{

#ifndef _SOUND_H_
#define _SOUND_H_
	class Sound :GameDate
	{
	private:
		//*****************************************************************************
		// パラメータ構造体定義
		//*****************************************************************************
		typedef struct
		{
			char *pFilename;	// ファイル名
			int nCntLoop;		// ループカウント
		} SOUNDPARAM;
		//*****************************************************************************
		// プロトタイプ宣言
		//*****************************************************************************
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
		//*****************************************************************************
		// グローバル変数
		//*****************************************************************************
		IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
		IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
		IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
		BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
		DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

		// 各音素材のパラメータ
		SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
		{
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra08.wav", -1 },	// BGM0
			{ (char*)"data/BGM/bgm_maoudamashii_neorock49 .wav", -1 },	// BGM1
			{ (char*)"data/BGM/bgm_maoudamashii_neorock52.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra20.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_orchestra26.wav", -1 },	// BGM2
			{ (char*)"data/BGM/bgm_maoudamashii_acoustic32.wav", -1 },	// BGM2

			{ (char*)"data/SE/bomb000.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/defend000.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/defend001.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/hit000.wav", 0 },			// 弾発射音
			{ (char*)"data/SE/laser000.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/lockon000.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/shot000.wav", 0 },		// 弾発射音
			{ (char*)"data/SE/shot001.wav", 0 },		// ヒット音
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