//================================================
//
//3Dゲーム(仮)[game.cpp]
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
#include "input.h"

#include "object2D.h"

#include "camera.h"
#include "light.h"
#include "player.h"
#include "item.h"
#include "stage.h"
#include "panel.h"

#include <assert.h>
#include <time.h>

//***************************
//定数の定義
//***************************
const int CGame::INTERVAL_STRAIGHT = 120;		//直線敵の生成間隔
const int CGame::FADE_INTERVAL_GAMEOVER = 60;	//フェードまでの間隔(ゲームオーバー時)
const int CGame::FADE_INTERVAL_GAMECLEAR = 180;	//フェードまでの間隔(ゲームクリア時)

//***************************
//静的メンバ変数
//***************************
CCamera* CGame::m_pCamera = nullptr;	//カメラ
CLight* CGame::m_pLight = nullptr;		//ライト
CPlayer* CGame::m_pPlayer = nullptr;	//プレイヤー
CStage* CGame::m_pStage = nullptr;		//ステージ
CPanel* CGame::m_pPanel = nullptr;		//パネル

//================================================
//カメラ情報を取得
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//ライト情報を取得
//================================================
CLight* CGame::GetLight()
{
	return m_pLight;
}

//================================================
//プレイヤー情報を取得
//================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//ステージ情報を取得
//================================================
CStage* CGame::GetStage()
{
	return m_pStage;
}

//================================================
//パネル情報を取得
//================================================
CPanel* CGame::GetPanel()
{
	return m_pPanel;
}

//================================================
//コンストラクタ
//================================================
CGame::CGame() : 
	CMode(MODE::GAME),
	m_nCntIntervalFade(0),
	m_bFadeOut(false),
	m_bWireFrame(false)
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

	//メンバ変数の初期化
	m_nCntIntervalFade = 0;
	m_bFadeOut = false;
	m_bWireFrame = false;

	//***** 生成 *****//

	/* カメラ */

	if (m_pCamera == nullptr)
	{//NULLチェック
		m_pCamera = new CCamera;	//動的確保
		m_pCamera->Init();			//初期化
	}

	/* ライト */

	if (m_pLight == nullptr)
	{//NULLチェック
		m_pLight = new CLight;	//動的確保
		m_pLight->Init();		//初期化
	}

	/* プレイヤー */

	if (m_pPlayer == nullptr)
	{//NULLチェック
		m_pPlayer = CPlayer::Create();	//生成
	}

	/* ステージ */

	if (m_pStage == nullptr)
	{//NULLチェック
		m_pStage = CStage::Create(CStage::STAGE::Stage01);	//生成
	}

	/* パネル */

	if (m_pPanel == nullptr)
	{//NULLチェック
		m_pPanel = CPanel::Create();	//生成
	}

	//明転した
	m_bFadeOut = false;

	//明転
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================\
//終了
//================================================
void CGame::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)
	CObjectX::ReleaseAll();		//全ての解放(Xモデル)

	/* パネル */

	if (m_pPanel == nullptr)
	{
		m_pPanel->Uninit();	//終了
		delete m_pPanel;	//メモリの解放
		m_pPanel = nullptr;	//nullptrにする
	}

	/* ステージ */

	if (m_pStage != nullptr)
	{//NULLチェック
		m_pStage->UninitAll();	//全ての終了
		delete m_pStage;		//メモリの解放
		m_pStage = nullptr;		//nullptrにする
	}

	/* プレイヤー */

	m_pPlayer = nullptr;	//nullptrにする

	/* ライト */

	if (m_pLight != nullptr)
	{//NULLチェック
		m_pLight->Uninit();	//終了
		delete m_pLight;	//メモリの解放
		m_pLight = nullptr;	//nullptrにする
	}

	/* カメラ */

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Uninit();	//終了
		delete m_pCamera;		//メモリの解放
		m_pCamera = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CGame::Update()
{
	//ワイヤーフレームの切り替え
	SwitchWireFrame();

	CObject::UpdateAll();	//オブジェクト

	if (m_pPanel != nullptr)
	{//NULLチェック
		m_pPanel->Update();	//パネル
	}

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Update();	//カメラ
	}

	if (m_pLight != nullptr)
	{//NULLチェック
		m_pLight->Update();	//ライト
	}

	if (m_pStage != nullptr)
	{//NULLチェック
		m_pStage = m_pStage->Set();	//ステージ
	}

	if (CApplication::GetInput()->GetKey()->Trigger(CInput::DECISION))
	{//Enterキー押下
		m_nCntIntervalFade = FADE_INTERVAL_GAMEOVER + 1;	//カウントアップ
	}

	if (!m_bFadeOut && (m_nCntIntervalFade > FADE_INTERVAL_GAMEOVER))
	{//暗転していない & カウントが一定数を超えた
		//暗転
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

		//暗転した
		m_bFadeOut = true;
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//暗転した & 現在フェードしていない
		//Change(MODE::RESULT);	//モードの設定

		//ステージ切り替え
		m_pStage->Change(CStage::STAGE::Stage02);

		//カウントリセット
		m_nCntIntervalFade = 0;

		//明転した
		m_bFadeOut = false;

		//明転
		CApplication::GetFade()->Set(CFade::STATE::FADE_IN);
	}
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
//ワイヤーフレームの切り替え
//================================================
void CGame::SwitchWireFrame()
{
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_F2))
	{//F2キー
		//表示:非表示の切り替え
		m_bWireFrame = m_bWireFrame ? false : true;

		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		if (m_bWireFrame)
		{//表示中
			//ワイヤーフレームモードの設定
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{//非表示中
			//元に戻す
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}
}