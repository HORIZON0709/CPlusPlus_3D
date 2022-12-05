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
#include "input.h"

#include "object2D.h"
#include "object3D.h"
//#include "objectMesh.h"
#include "objectX.h"

#include "camera.h"
#include "light.h"
#include "polygon3D.h"
#include "player.h"

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
CCamera* CGame::m_pCamera = nullptr;		//カメラ
CLight* CGame::m_pLight = nullptr;			//ライト
CPolygon3D* CGame::m_pPolygon3D = nullptr;	//3Dポリゴン
CPlayer* CGame::m_pPlayer = nullptr;		//プレイヤー
CObjectMesh* CGame::m_pMesh = nullptr;		//メッシュ
CObjectX* CGame::m_pObjX = nullptr;			//Xモデル

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
//3Dポリゴン情報を取得
//================================================
CPolygon3D* CGame::GetPolygon3D()
{
	return m_pPolygon3D;
}

//================================================
//プレイヤー情報を取得
//================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//メッシュ情報を取得
//================================================
CObjectMesh* CGame::GetMesh()
{
	return m_pMesh;
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

	/* 3Dポリゴン */

	if (m_pPolygon3D == nullptr)
	{//NULLチェック
		m_pPolygon3D = CPolygon3D::Create();	//生成
	}

	/* プレイヤー */

	if (m_pPlayer == nullptr)
	{//NULLチェック
		m_pPlayer = CPlayer::Create();	//生成
	}

	/* メッシュ */

	/*if (m_pMesh == nullptr)
	{
		m_pMesh = CObjectMesh::Create();
	}*/

	/* Xモデル */

	//if (m_pObjX== nullptr)
	//{//NULLチェック
	//	m_pObjX = CObjectX::Create();	//生成
	//}

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
	CObjectX::ReleaseAll();		//全ての解放(X)
	//CObjectMesh::ReleaseAll();		//全ての解放(Mesh)

	/* カメラ */

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Uninit();	//終了
		delete m_pCamera;		//メモリの解放
		m_pCamera = nullptr;	//nullptrにする
	}

	/* ライト */

	if (m_pLight != nullptr)
	{//NULLチェック
		m_pLight->Uninit();	//終了
		delete m_pLight;	//メモリの解放
		m_pLight = nullptr;	//nullptrにする
	}

	/* 3Dポリゴン */

	m_pPolygon3D = nullptr;	//nullptrにする

	/* プレイヤー */

	m_pPlayer = nullptr;	//nullptrにする

	/* メッシュ */

	m_pMesh = nullptr;	//nullptrにする

	/* Xモデル */

	m_pObjX = nullptr;	//nullptrにする
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

	if (m_pLight != nullptr)
	{//NULLチェック
		m_pLight->Update();	//ライト
	}

	//ワイヤーフレームの切り替え
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

	//if (CApplication::GetInput()->GetKey()->Trigger(CInput::DECISION))
	//{//Enterキー押下
	//	m_nCntIntervalFade++;	//カウントアップ

	//	if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMEOVER == 0))
	//	{//暗転していない & カウントが一定数を超えた
	//		//暗転
	//		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

	//		//暗転した
	//		m_bFadeOut = true;
	//	}

	//	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	//	{//暗転した & 現在フェードしていない
	//		Change(MODE::RESULT);	//モードの設定
	//	}
	//}
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