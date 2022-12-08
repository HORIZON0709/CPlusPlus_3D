//================================================
//
//3Dゲーム(仮)[title.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "title.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"

#include "object2D.h"
#include "bg.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CTitle::LOGO_WIDTH = 300.0f;	//ロゴの幅
const float CTitle::LOGO_HEIGHT = 150.0f;	//ロゴの高さ

//***************************
//静的メンバ変数
//***************************
CBg* CTitle::m_pBg = nullptr;			//背景
CObject2D* CTitle::m_pLogo = nullptr;	//タイトルロゴ

//================================================
//コンストラクタ
//================================================
CTitle::CTitle() : CMode(MODE::TITLE),
m_bFadeOut(false)
{
}

//================================================
//デストラクタ
//================================================
CTitle::~CTitle()
{
}

//================================================
//初期化
//================================================
HRESULT CTitle::Init()
{
	//メンバ変数の初期化
	m_bFadeOut = false;

	/* 背景 */

	//生成
	m_pBg = CBg::Create();

	//テクスチャの設定
	m_pBg->SetTexture(CTexture::Bg_Title_Tentative);

	//テクスチャ座標の設定
	m_pBg->SetTexUV(1, 0);

	/* タイトルロゴ */

	//生成
	m_pLogo = CObject2D::Create();

	D3DXVECTOR3 pos = D3DXVECTOR3(	//位置設定用
		CRenderer::SCREEN_WIDTH * 0.5f,
		CRenderer::SCREEN_HEIGHT / 3.0f,
		0.0f);

	//位置を設定
	m_pLogo->SetPos(pos);

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetSize(size);

	//明転
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================
//終了
//================================================
void CTitle::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)

	/* タイトルロゴ */

	if (m_pLogo != nullptr)
	{//NULLチェック
		m_pLogo = nullptr;	//nullptrにする
	}

	/* 背景 */

	if (m_pBg != nullptr)
	{//NULLチェック
		m_pBg = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CTitle::Update()
{
	CObject::UpdateAll();	//オブジェクト

	CInput* pInput = CInput::GetKey();	//キーボード情報を取得

	if (pInput->Trigger(CInput::STANDARD_KEY::DECISION))
	{//決定キ―
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);	//暗転
		m_bFadeOut = true;	//暗転した
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//フェードが終わって暗転中の場合
		Change(MODE::GAME);	//モードの設定
	}
}

//================================================
//描画
//================================================
void CTitle::Draw()
{
	CObject::DrawAll();	//オブジェクト
}