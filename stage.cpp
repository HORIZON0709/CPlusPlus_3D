//================================================
//
//3Dゲーム(仮)[stage.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "stage.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const int CStage::MAX_WORD = 256;	//最大文字数

const char* CStage::FILE_NAME = "data/TEXT/model.txt";	//ファイル名

//================================================
//生成
//================================================
CStage* CStage::Create(char* pFileName)
{
	CStage* pObjectX = nullptr;	//ポインタ

	if (pObjectX != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pObjectX = new CStage;	//メモリの動的確保

	pObjectX->Init();	//初期化

	return pObjectX;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CStage::CStage() :
	m_pFloar(nullptr),
	m_nNumModel(0),
	m_nCntSet(0)
{
	//メンバ変数のクリア
	memset(m_apWall, 0, sizeof(m_apWall));
	memset(m_apModel, 0, sizeof(m_apModel));
}

//================================================
//デストラクタ
//================================================
CStage::~CStage()
{
}

//================================================
//初期化
//================================================
HRESULT CStage::Init()
{
	//読み込み
	Load();
	
	return S_OK;
}

//================================================
//終了
//================================================
void CStage::Uninit()
{
}

//================================================
//更新
//================================================
void CStage::Update()
{
}

//================================================
//読み込み
//================================================
void CStage::Load()
{
	//ファイルを開く
	FILE* pFile = fopen(FILE_NAME, "r");
	
	if (pFile == nullptr)
	{//ファイルが開けなかった場合
		assert(false);
	}

	/* ファイルが開けた場合 */

	char aText[MAX_WORD] = {};	//テキスト格納用

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//テキストの最初の行を読み込むまで繰り返す
		fgets(aText, MAX_WORD, pFile);	//1行丸ごと読み込む
	}

	char aFileName[MAX_MODEL][MAX_WORD] = {};	//ファイルパス読み込み用

	int nCntFile = 0;	//ファイル数カウント

	while (strcmp(&aText[0], "END_SCRIPT") != 0)
	{//テキストの最終行を読み込むまで繰り返す
		//文字を読み込む
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//ブロックコメント
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//コメント
			//1行全て読み込む
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "NUM_MODEL") == 0)
		{//モデル数
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//モデル数を読み込む
			fscanf(pFile, "%d", &m_nNumModel);
		}
		else if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
		{//ファイル名
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//Xファイルのパスを読み込む
			fscanf(pFile, "%s", &aFileName[nCntFile][0]);

			//カウントを増加
			nCntFile++;
		}
		else if (strcmp(&aText[0], "MODELSET") == 0)
		{//モデルセット
			//モデル設定
			Set_ModelSet(pFile);

			//カウントアップ
			m_nCntSet++;
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}

//================================================
//モデルセット設定
//================================================
void CStage::Set_ModelSet(FILE* pFile)
{
	char aText[MAX_WORD] = {};	//テキスト格納用

	//ポインタに代入
	MODELSET_INFO* pInfo = &m_aModelSetInfo[m_nCntSet];

	while (strcmp(&aText[0], "END_MODELSET") != 0)
	{//モデルセットが終わるまで繰り返す
		//文字を読み込む
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//ブロックコメント
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//コメント
			//1行全て読み込む
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "INDEX") == 0)
		{//インデックス数
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//インデックス数を読み込む
			fscanf(pFile, "%d", &pInfo->nIndex);
		}
		else if (strcmp(&aText[0], "POS") == 0)
		{//位置
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//位置を読み込む
			fscanf(pFile, "%f", &pInfo->pos.x);
			fscanf(pFile, "%f", &pInfo->pos.y);
			fscanf(pFile, "%f", &pInfo->pos.z);
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//向き
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//向きを読み込む
			fscanf(pFile, "%f", &pInfo->rot.x);
			fscanf(pFile, "%f", &pInfo->rot.y);
			fscanf(pFile, "%f", &pInfo->rot.z);
		}
	}
}