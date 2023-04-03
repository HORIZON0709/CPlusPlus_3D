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

//***************************
//静的メンバ変数
//***************************
CPanel::PANEL_INFO CPanel::m_aPanelInfo[MAX_PANEL] = {};	//パネル情報

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
	m_pSelect(nullptr),
	m_nPosX(0),
	m_nPosY(0),
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
	m_nPosX = 0;
	m_nPosY = 0;
	m_bPanel = false;

	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//画面の横幅
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//画面の縦幅

	for (int i = 0; i < MAX_PANEL; i++)
	{//パネル情報の初期化
		m_aPanelInfo[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aPanelInfo[i].stage = CStage::STAGE::NONE;
	}

	/* 背景 */

	//生成
	m_pBg = CObject2D::Create();

	//各情報の設定
	m_pBg->SetPos(D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f));
	m_pBg->SetSize(D3DXVECTOR2(fWidth, fHeight));
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//描画しない
	m_pBg->SetIsDraw(false);

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

	/* 選択用 */

	//生成
	m_pSelect = CObject2D::Create();

	//各情報の設定
	m_pSelect->SetPos(aPos[0]);
	m_pSelect->SetSize(D3DXVECTOR2(PANEL_SIZE + 20.0f, PANEL_SIZE + 20.0f));
	m_pSelect->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	//描画しない
	m_pSelect->SetIsDraw(false);

	/* パネル */

	int nTex = CTexture::TEXTURE::Number_Single_1;	//テクスチャ設定用

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//生成
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

	if (m_pSelect != nullptr)
	{//NULLチェック
		m_pSelect = nullptr;
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

	if (!m_bPanel)
	{//パネル操作をしていない場合
		return;
	}

	/* パネル操作中の場合 */

	//パネルの選択
	SelectPanel();

	/* 描画する */

	//背景
	m_pBg->SetIsDraw(m_bPanel);

	//選択用
	m_pSelect->SetIsDraw(m_bPanel);

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

//================================================
//パネルの選択
//================================================
void CPanel::SelectPanel()
{
	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//画面の横幅
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//画面の縦幅

	D3DXVECTOR3 aPos[GRID_Y][GRID_X] = {};	//パネルの位置

	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			//位置を設定
			aPos[Y][X] = D3DXVECTOR3(fWidth * (0.3f + (0.1f * (X + 1))), fHeight * ((0.2f * (Y + 1)) + 0.1f), 0.0f);
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_W))
	{//Wキー押下
		m_nPosY--;	//-1する

		if (m_nPosY < 0)
		{//0未満(-1以下)になった場合
			m_nPosY = 0;	//0に固定
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_S))
	{//Sキー押下
		m_nPosY++;	//+1する

		if (m_nPosY > 2)
		{//2より大きく(3以上)になった場合
			m_nPosY = 2;	//2に固定
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_A))
	{//Aキー押下
		m_nPosX--;	//-1する

		if (m_nPosX < 0)
		{//0未満(-1以下)になった場合
			m_nPosX = 0;	//0に固定
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_D))
	{//Dキー押下
		m_nPosX++;	//+1する

		if (m_nPosX > 2)
		{//2より大きく(3以上)になった場合
			m_nPosX = 2;	//2に固定
		}
	}

	//選択用の位置の設定
	m_pSelect->SetPos(aPos[m_nPosY][m_nPosX]);
}