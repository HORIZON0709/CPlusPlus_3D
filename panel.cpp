//================================================
//
//3Dゲーム(仮)[panel.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "panel.h"
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "input.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPanel::PANEL_SIZE = 100.0f;	//パネルのサイズ

//================================================
//生成
//================================================
CPanel* CPanel::Create()
{
	CPanel* pPanel = nullptr;	//ポインタ

	if (pPanel != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pPanel = new CPanel;	//メモリの動的確保

	pPanel->Init();	//初期化

	return pPanel;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CPanel::CPanel() :
	m_pBg(nullptr),
	m_bPanel(false)
{
	//メンバ変数のクリア
	memset(m_apPanel, 0, sizeof(m_apPanel));
}

//================================================
//デストラクタ
//================================================
CPanel::~CPanel()
{
}

//================================================
//初期化
//================================================
HRESULT CPanel::Init()
{
	//メンバ変数の初期化
	m_bPanel = false;

	//背景の生成
	m_pBg = CObject2D::Create();

	//各情報の設定
	m_pBg->SetPos(D3DXVECTOR3(CRenderer::SCREEN_WIDTH * 0.5f, CRenderer::SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pBg->SetSize(D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT));
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//描画しない
	m_pBg->SetIsDraw(false);

	float fWidth = CRenderer::SCREEN_WIDTH;		//画面の横幅
	float fHeight = CRenderer::SCREEN_HEIGHT;	//画面の縦幅

	D3DXVECTOR3 aPos[MAX_PANEL] =
	{//パネルの位置
		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.3f, 0.0f),	//1
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.3f, 0.0f),	//2
		D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.3f, 0.0f),	//3

		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.5f, 0.0f),	//4
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f),	//5
		D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.5f, 0.0f),	//6

		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.7f, 0.0f),	//7
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.7f, 0.0f)	//8
	};

	int nTex = CTexture::TEXTURE::Number_Single_1;	//テクスチャ設定用

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//パネルの生成
		m_apPanel[i] = CObject2D::Create();

		//位置の設定
		m_apPanel[i]->SetPos(aPos[i]);

		//サイズの設定
		m_apPanel[i]->SetSize(D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE));

		//テクスチャの設定
		m_apPanel[i]->SetTexture((CTexture::TEXTURE)nTex);

		//次のテクスチャにする
		nTex++;

		//描画しない
		m_apPanel[i]->SetIsDraw(false);
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CPanel::Uninit()
{
	for (int i = 0; i < MAX_PANEL; i++)
	{
		if (m_apPanel[i] != nullptr)
		{//NULLチェック
			m_apPanel[i] = nullptr;
		}
	}

	if (m_pBg != nullptr)
	{//NULLチェック
		m_pBg = nullptr;
	}
}

//================================================
//更新
//================================================
void CPanel::Update()
{
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_F3))
	{//F3キー
		//表示:非表示の切り替え
		m_bPanel = m_bPanel ? false : true;
	}

	/* 描画する */

	//背景
	m_pBg->SetIsDraw(m_bPanel);

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//パネル
		m_apPanel[i]->SetIsDraw(m_bPanel);
	}
}

//================================================
//描画
//================================================
void CPanel::Draw()
{
}

//================================================
//パネル操作中かどうかを取得
//================================================
bool CPanel::GetIsPanel()
{
	return m_bPanel;
}