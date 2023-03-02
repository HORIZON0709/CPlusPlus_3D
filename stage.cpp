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
#include "game.h"
#include "objectX.h"
#include "object3D.h"
#include "gimmick.h"
#include "item.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const char* CStage::s_apFileName[] =
{//ステージのパス
	"data/TEXT/Stage_01.txt",	//ステージ01
	"data/TEXT/Stage_02.txt",	//ステージ01
};

static_assert(sizeof(CStage::s_apFileName) / sizeof(CStage::s_apFileName[0]) == CStage::STAGE::MAX, "aho");

const float CStage::FLOAR_SIZE = 1000.0f;				//床のサイズ
const float CStage::WALL_WIDTH = FLOAR_SIZE;			//壁の幅
const float CStage::WALL_HEIGHT = FLOAR_SIZE * 0.5f;	//壁の高さ

const int CStage::MAX_WORD = 256;	//最大文字数

//***************************
//静的メンバ変数
//***************************
CGimmick* CStage::m_apGimmick[MAX_GIMMICK] = {};	//ギミックのポインタ
CItem* CStage::m_pItem = nullptr;					//アイテムのポインタ

//================================================
//生成
//================================================
CStage* CStage::Create(const STAGE &stage)
{
	CStage* pStage = nullptr;	//ポインタ

	if (pStage != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pStage = new CStage;	//メモリの動的確保

	pStage->Init(stage, s_apFileName[stage]);	//初期化

	return pStage;	//動的確保したものを返す
}

//================================================
//ギミック情報の取得
//================================================
CGimmick* CStage::GetGimmick(int nIdx)
{
	return m_apGimmick[nIdx];
}

//================================================
//アイテム情報の取得
//================================================
CItem* CStage::GetItem()
{
	return m_pItem;
}

//================================================
//コンストラクタ
//================================================
CStage::CStage() :
	m_pFloar(nullptr),
	m_stage(STAGE::NONE),
	m_stageNext(STAGE::NONE),
	m_nNumModel(0),
	m_nCntModelSet(0)
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
HRESULT CStage::Init(const STAGE &stage, const char* pStage)
{
	//メンバ変数の初期化
	m_stage = stage;
	m_stageNext = STAGE::NONE;
	m_nNumModel = 0;
	m_nCntModelSet = 0;

	//床の生成
	m_pFloar = CObject3D::Create();

	//床の設定
	m_pFloar->SetSize(D3DXVECTOR3(FLOAR_SIZE, 0.0f, FLOAR_SIZE));
	m_pFloar->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));

	for (int i = 0; i < DIRECTION::DIR_MAX; i++)
	{
		//壁の生成
		m_apWall[i] = CObject3D::Create();
	}

	//壁の設定
	SetWall();

	//読み込み
	Load(pStage);

	return S_OK;
}

//================================================
//終了
//================================================
void CStage::Uninit()
{
	if (m_pItem != nullptr)
	{//NULLチェック
		m_pItem->SetDeathFlag();	//死亡フラグの設定
		m_pItem = nullptr;			//nullptrにする
	}

	for (int i = 0; i < MAX_GIMMICK; i++)
	{
		if (m_apGimmick[i] != nullptr)
		{//NULLチェック
			m_apGimmick[i]->SetDeathFlag();	//死亡フラグの設定
			m_apGimmick[i] = nullptr;		//nullptrにする
		}
	}

	for (int i = 0; i < m_nNumModel; i++)
	{
		if (m_apModel[i] != nullptr)
		{//NULLチェック
			m_apModel[i]->SetDeathFlag();	//死亡フラグの設定
			m_apModel[i] = nullptr;			//nullptrにする
		}
	}

	for (int i = 0; i < DIRECTION::DIR_MAX; i++)
	{
		if (m_apWall[i] != nullptr)
		{//NULLチェック
			m_apWall[i]->SetDeathFlag();	//死亡フラグの設定
			m_apWall[i] = nullptr;			//nullptrにする
		}
	}

	if (m_pFloar != nullptr)
	{//NULLチェック
		m_pFloar->SetDeathFlag();	//死亡フラグの設定
		m_pFloar = nullptr;			//nullptrにする
	}
}

//================================================
//ステージの設定
//================================================
CStage* CStage::Set()
{
	if (m_stageNext == STAGE::NONE)
	{//次のステージが決まっていない
		return this;
	}

	//現在のステージを終了
	Uninit();

	m_stage = m_stageNext;		//ステージを変更
	m_stageNext = STAGE::NONE;	//何もない状態にする

	return Create(m_stage);	//変更後のステージを生成して返す
}

//================================================
//ステージの取得
//================================================
CStage::STAGE CStage::Get()
{
	return m_stage;
}

//================================================
//ステージの変更
//================================================
void CStage::Change(const STAGE &stage)
{
	assert(stage > STAGE::NONE && stage < STAGE::MAX);
	
	m_stageNext = stage;
}

//================================================
//読み込み
//================================================
void CStage::Load(const char* pStage)
{
	//ファイルを開く
	FILE* pFile = fopen(pStage, "r");
	
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
			m_nCntModelSet++;
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	for (int i = 0, nNumModel = 0, nNumGimmick = 0; i < m_nCntModelSet; i++)
	{
		//インデックス数
		int nIndex = m_aModelSetInfo[i].nIndex;

		switch (m_aModelSetInfo[i].type)
		{
		case MODEL_TYPE::TYPE_OBJECT:	//オブジェクト
			//生成
			m_apModel[nNumModel] = CObjectX::Create(&aFileName[nIndex][0]);

			//位置・向きの設定
			m_apModel[nNumModel]->SetPos(m_aModelSetInfo[i].pos);
			m_apModel[nNumModel]->SetRot(m_aModelSetInfo[i].rot);

			//カウントアップ
			nNumModel++;
			break;

		case MODEL_TYPE::TYPE_GIMMICK:	//ギミック
			//生成
			m_apGimmick[nNumGimmick] = CGimmick::Create(&aFileName[nIndex][0]);

			//位置・向きの設定
			m_apGimmick[nNumGimmick]->SetPos(m_aModelSetInfo[i].pos);
			m_apGimmick[nNumGimmick]->SetRot(m_aModelSetInfo[i].rot);

			//カウントアップ
			nNumGimmick++;
			break;

		case MODEL_TYPE::TYPE_ITEM:	//アイテム
			//生成
			m_pItem = CItem::Create(&aFileName[nIndex][0]);
			
			//位置・向きの設定
			m_pItem->SetPos(m_aModelSetInfo[i].pos);
			m_pItem->SetRot(m_aModelSetInfo[i].rot);
			break;

		case MODEL_TYPE::TYPE_NONE:	//その他
		case MODEL_TYPE::TYPE_MAX:
		default:
			assert(false);
			break;
		}
	}
}

//================================================
//モデルセット設定
//================================================
void CStage::Set_ModelSet(FILE* pFile)
{
	char aText[MAX_WORD] = {};	//テキスト格納用

	//ポインタに代入
	MODELSET_INFO* pInfo = &m_aModelSetInfo[m_nCntModelSet];

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
		else if (strcmp(&aText[0], "MODEL_TYPE") == 0)
		{//モデルタイプ
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			int nType = 0;	//タイプ読み込み用

			//モデルタイプを読み込む
			fscanf(pFile, "%d", &nType);

			switch (nType)
			{
			case 0:	//オブジェクト
				pInfo->type = MODEL_TYPE::TYPE_OBJECT;
				break;

			case 1:	//ギミック
				pInfo->type = MODEL_TYPE::TYPE_GIMMICK;
				break;

			case 2:	//アイテム
				pInfo->type = MODEL_TYPE::TYPE_ITEM;
				break;

			default:	//その他
				assert(false);
				break;
			}
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

//================================================
//壁の設定
//================================================
void CStage::SetWall()
{
	//説明用変数
	float fFloarSizeHalf = (FLOAR_SIZE * 0.5f);		//床サイズの半分
	float fWallHeightHalf = (WALL_HEIGHT * 0.5f);	//壁の高さの半分

	//********** 左 **********//

	//生成する方向
	DIRECTION dir = DIRECTION::DIR_LEFT;

	//サイズ
	m_apWall[dir]->SetSize(D3DXVECTOR3(WALL_HEIGHT, 0.0f, WALL_WIDTH));

	//位置
	D3DXVECTOR3 pos = D3DXVECTOR3(
		m_pFloar->GetPos().x - fFloarSizeHalf,
		m_pFloar->GetPos().y + fWallHeightHalf,
		0.0f);
	m_apWall[dir]->SetPos(pos);

	//向き
	m_apWall[dir]->SetRot(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f));

	//色
	m_apWall[dir]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//********** 奥 **********//

	//生成する方向
	dir = DIRECTION::DIR_BACK;

	//サイズ
	m_apWall[dir]->SetSize(D3DXVECTOR3(WALL_WIDTH, 0.0f, WALL_HEIGHT));

	//位置
	pos = D3DXVECTOR3(
		0.0f,
		m_pFloar->GetPos().y + fWallHeightHalf,
		m_pFloar->GetPos().z + fFloarSizeHalf);
	m_apWall[dir]->SetPos(pos);

	//向き
	m_apWall[dir]->SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));

	//色
	m_apWall[dir]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//********** 右 **********//

	//生成する方向
	dir = DIRECTION::DIR_RIGHT;

	//サイズ
	m_apWall[dir]->SetSize(D3DXVECTOR3(WALL_HEIGHT, 0.0f, WALL_WIDTH));

	//位置
	pos = D3DXVECTOR3(
		m_pFloar->GetPos().x + fFloarSizeHalf,
		m_pFloar->GetPos().y + fWallHeightHalf,
		0.0f);
	m_apWall[dir]->SetPos(pos);

	//向き
	m_apWall[dir]->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));

	//色
	m_apWall[dir]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//********** 手前 **********//

	//生成する方向
	dir = DIRECTION::DIR_FRONT;

	//サイズ
	m_apWall[dir]->SetSize(D3DXVECTOR3(WALL_WIDTH, 0.0f, WALL_HEIGHT));

	//位置
	pos = D3DXVECTOR3(
		0.0f,
		m_pFloar->GetPos().y + fWallHeightHalf,
		m_pFloar->GetPos().z - fFloarSizeHalf);
	m_apWall[dir]->SetPos(pos);

	//向き
	m_apWall[dir]->SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));

	//色
	m_apWall[dir]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
}