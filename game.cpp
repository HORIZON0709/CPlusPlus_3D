//================================================
//
//制作実践基礎[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"

#include "camera.h"
#include "score.h"
#include "player_3D.h"
#include "enemy_curve.h"
#include "enemy_boss.h"
#include "bg_3D.h"

#include <assert.h>
#include <time.h>

//***************************
//定数の定義
//***************************
const int CGame::INTERVAL_STRAIGHT = 120;		//直線敵の生成間隔
const int CGame::FADE_INTERVAL_PARTCHANGE = 60;	//フェードまでの間隔(パート切り替え時)
const int CGame::FADE_INTERVAL_GAMEOVER = 60;	//フェードまでの間隔(ゲームオーバー時)
const int CGame::FADE_INTERVAL_GAMECLEAR = 180;	//フェードまでの間隔(ゲームクリア時)

//***************************
//静的メンバ変数
//***************************
CCamera* CGame::m_pCamera = nullptr;					//カメラ
CScore* CGame::m_pScore = nullptr;						//スコア
CPlayer3D* CGame::m_pPlayer3D = nullptr;				//プレイヤー(3D)
CEnemy3D* CGame::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//敵(3D)
CBg3D* CGame::m_pBg3D = nullptr;						//背景(3D)

/*
	ゲームパートの判別
	false ---> 通常パート
	true ---> ボスパート
*/
bool CGame::m_bGamePart = false;

//================================================
//カメラ情報を取得
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//スコア情報を取得
//================================================
CScore* CGame::GetScore()
{
	return m_pScore;
}

//================================================
//プレイヤー(3D)情報を取得
//================================================
CPlayer3D* CGame::GetPlayer3D()
{
	return m_pPlayer3D;
}

//================================================
//敵(3D)情報を取得
//================================================
CEnemy3D* CGame::GetEnemy3D(const int nIdx)
{
	return m_apEnemy3D[nIdx];
}

//================================================
//背景(3D)情報を取得
//================================================
CBg3D* CGame::GetBg3D()
{
	return m_pBg3D;
}

//================================================
//ゲームパートの切り替え
//================================================
void CGame::ChangeGamePart()
{
	/* 通常敵を解放 */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apEnemy3D[i] = nullptr;	//nullptrにする
	}

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		CObject* pObject = CObject::GetObjects(i);	//オブジェクト情報の取得

		if (pObject == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrでは無い場合 */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//オブジェクトの種類の取得

		if (type != CObject::OBJ_TYPE::ENEMY)
		{//敵では無い場合
			continue;
		}

		/* 敵のオブジェクトだった場合 */

		//nullptrにする
		CObject::SetObject(i, nullptr);
	}

	m_pCamera->Init();	//カメラの初期化

	m_pBg3D->Init();	//背景(3D)の初期化

	m_pPlayer3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//初期位置に戻す

	//***** ボスの生成 *****//

	if (m_apEnemy3D[0] != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* 通常敵が全て解放できていた場合 */

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyBoss::START_POS_X, CEnemyBoss::START_POS_Y, 0.0f);

	//ボスを生成する
	m_apEnemy3D[0] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::BOSS, pos);

	m_bGamePart = true;	//ボスパートに切り替え

	//明転
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);
}

//================================================
//ゲームパートの取得
//================================================
bool CGame::GetGamePart()
{
	return m_bGamePart;
}

//================================================
//コンストラクタ
//================================================
CGame::CGame() : CMode(MODE::GAME),
m_nCntStraight(0),
m_nCntIntervalFade(0),
m_bFadeOut(false)
{
}

//================================================
//デストラクタ
//================================================
CGame::~CGame()
{
}

//================================================
//初期化
//================================================
HRESULT CGame::Init()
{
	srand((unsigned)time(NULL));	//ランダム種子の初期化

	m_bGamePart = false;	//通常パート

	//メンバ変数の初期化
	m_nCntStraight = 0;
	m_nCntIntervalFade = 0;
	m_bFadeOut = false;

	/* 生成 */

	if (m_pCamera == nullptr)
	{//NULLチェック
		m_pCamera = new CCamera;	//カメラ
		m_pCamera->Init();			//初期化
	}

	m_pScore = CScore::Create();	//スコア

	m_pBg3D = CBg3D::Create();	//背景(3D)

	m_pPlayer3D = CPlayer3D::Create();	//プレイヤー(3D)

	//明転
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================
//終了
//================================================
void CGame::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)
	CObject3D::ReleaseAll();	//全ての解放(3D)

	/* カメラ */

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Uninit();	//終了
		delete m_pCamera;		//メモリの解放
		m_pCamera = nullptr;	//nullptrにする
	}

	/* スコア */

	if (m_pScore != nullptr)
	{//NULLチェック
		m_pScore = nullptr;	//nullptrにする
	}

	/* 背景(3D) */

	if (m_pScore != nullptr)
	{//NULLチェック
		m_pBg3D = nullptr;	//nullptrにする
	}

	/* プレイヤー(3D) */
	if (m_pScore != nullptr)
	{//NULLチェック
		m_pPlayer3D = nullptr;	//nullptrにする
	}

	/* 敵(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apEnemy3D[i] = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CGame::Update()
{
	CObject::UpdateAll();	//オブジェクト

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Update();	//カメラ
	}

	if (m_pPlayer3D->GetObjType() != CObject::OBJ_TYPE::PLAYER)
	{//プレイヤーが死亡したら
		m_nCntIntervalFade++;	//カウントアップ

		if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMEOVER == 0))
		{//暗転していない & カウントが一定数を超えた
			//暗転
			CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

			//暗転した
			m_bFadeOut = true;
		}

		if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
		{//暗転した & 現在フェードしていない
			Change(MODE::RESULT);	//モードの設定
		}
	}

	if (m_bGamePart)
	{//ボスパートの場合
		UpdateBossPart();	//ボスパートの更新
		return;
	}

	/* 通常パートの場合 */

	UpdateNormalPart();	//通常パートの更新
}

//================================================
//描画
//================================================
void CGame::Draw()
{
	//カメラの設定
	m_pCamera->Set();

	CObject::DrawAll();	//オブジェクト
}

//================================================
//直線敵の生成
//================================================
void CGame::CreateEnemyStraight(const float fPosY)
{
	//カメラ情報の取得
	D3DXMATRIX mtxCamera = m_pCamera->GetMatrixView();

	//カメラの視点の位置を取得
	D3DXVECTOR3 posV = m_pCamera->GetPosV();

	//位置を反映
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//カメラの画角の右の限界を設定
	float fRimitRight = (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));

	//先頭が生成される位置を設定
	float fPosFirst = (fRimitRight + 100.0f);

	int nNumCreate = 5;	//一度に生成する数

	for (int i = 0,nCnt = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (nCnt == nNumCreate)
		{//設定数分全て生成したら
			break;
		}

		/* 設定数分全て生成していない場合 */

		if (m_apEnemy3D[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		//位置を設定
		D3DXVECTOR3 pos = D3DXVECTOR3(fPosFirst + (i * 100.0f), fPosY, 0.0f);

		//生成
		m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::STRAIGHT, pos);

		nCnt++;	//生成したらカウント
	}
}

//================================================
//通常パートの更新
//================================================
void CGame::UpdateNormalPart()
{
	if (m_bGamePart)
	{//ボスパートの場合
		return;
	}

	/* 通常パートの場合 */

	if (m_pCamera->GetPosV().x >= 500.0f)
	{//カメラが一定距離まで進んだら
		m_nCntIntervalFade++;	//カウントアップ

		if (!m_bFadeOut && (m_nCntIntervalFade >= FADE_INTERVAL_PARTCHANGE))
		{//暗転していない & カウントが一定数を超えた
			//暗転
			CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

			//暗転した
			m_bFadeOut = true;
		}
		
		if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
		{//暗転した & 現在フェードしていない
			//ゲームパート切り替え
			ChangeGamePart();

			//カウントを初期化(ボスパートでは使用しない)
			m_nCntStraight = 0;

			//明転した
			m_bFadeOut = false;
			return;
		}
	}

	if (m_pCamera->GetPosV().x < 450.0f)
	{//カメラが一定距離の手前に来るまで
		m_nCntStraight++;	//カウントアップ

		if (m_nCntStraight % INTERVAL_STRAIGHT != 0)
		{//一定間隔までカウントしていない
			return;
		}
		
		/* 一定間隔までカウントした場合 */

		float aPosY[5] =
		{//ランダムで生成したい高さ(上から)
			200.0f,
			100.0f,
			0.0f,
			-100.0f,
			-200.0f
		};

		int nRandam = rand() % 5;	//ランダム

		//直線敵の生成
		CreateEnemyStraight(aPosY[nRandam]);
	}
}

//================================================
//ボスパートの更新
//================================================
void CGame::UpdateBossPart()
{
	if (!m_bGamePart)
	{//通常パートの場合
		return;
	}

	/* ボスパートの場合 */

	//ボスの型にキャスト
	CEnemyBoss* pBoss = (CEnemyBoss*)m_apEnemy3D[0];

	//ボスの体力が尽きたかどうか
	bool bBossAlive = (pBoss->GetLife() <= 0);

	if (!bBossAlive)
	{//ボスが死んでない場合
		return;
	}

	/* ボスが死んだ場合 */

	m_nCntIntervalFade++;	//カウントアップ

	if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMECLEAR == 0))
	{//暗転していない & カウントが一定数を超えた
		//暗転
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

		//暗転した
		m_bFadeOut = true;
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//暗転した & 現在フェードしていない
		Change(MODE::RESULT);	//モードの設定
	}
}