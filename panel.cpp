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
#include "game.h"

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
CPanel::PANEL_INFO CPanel::m_aPanelInfo[GRID_Y][GRID_X] = {};	//パネル情報

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
	m_bPanel(false),
	m_bIsSelect(false)
{
	//メンバ変数のクリア
	memset(&m_aPos, 0, sizeof(m_aPos));
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
	m_bIsSelect = false;

	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//画面の横幅
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//画面の縦幅

	{//パネルの位置を設定する
		D3DXVECTOR3 aPos[MAX_PANEL] =
		{//パネルの位置(固定)
			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.3f, 0.0f),	//1
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.3f, 0.0f),	//2
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.3f, 0.0f),	//3

			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.5f, 0.0f),	//4
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f),	//5
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.5f, 0.0f),	//6

			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.7f, 0.0f),	//7
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.7f, 0.0f),	//8
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.7f, 0.0f)	//9
		};

		for (int Y = 0; Y < GRID_Y; Y++)
		{
			for (int X = 0; X < GRID_X; X++)
			{
				//3×3マスでの位置を保存する
				m_aPos[Y][X] = aPos[X + (Y * 3)];
			}
		}
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

	/* 選択用パネル */

	//生成
	m_pSelect = CObject2D::Create();

	//各情報の設定
	m_pSelect->SetPos(m_aPos[0][0]);
	m_pSelect->SetSize(D3DXVECTOR2(PANEL_SIZE + 20.0f, PANEL_SIZE + 20.0f));
	m_pSelect->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	//描画しない
	m_pSelect->SetIsDraw(false);

	int nTex = CTexture::TEXTURE::Number_Single_1;	//テクスチャ設定用
	int nStage = CStage::STAGE::Stage01;			//ステージ設定用

	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			//生成
			m_aPanelInfo[Y][X].m_pPanel = CObject2D::Create();

			//位置の設定
			m_aPanelInfo[Y][X].m_pPanel->SetPos(m_aPos[Y][X]);

			//サイズの設定
			m_aPanelInfo[Y][X].m_pPanel->SetSize(D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE));

			//テクスチャの設定
			m_aPanelInfo[Y][X].m_pPanel->SetTexture((CTexture::TEXTURE)nTex);

			//次のテクスチャにする
			nTex++;

			//描画しない
			m_aPanelInfo[Y][X].m_pPanel->SetIsDraw(false);

			//ステージを設定
			m_aPanelInfo[Y][X].stage = (CStage::STAGE)nStage;

			if (Y == (GRID_Y - 1) && X == (GRID_X - 1))
			{//空白部分はステージ無し
				m_aPanelInfo[Y][X].stage = CStage::STAGE::NONE;
			}

			//次のステージにする
			nStage++;
		}
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CPanel::Uninit()
{
	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			if (m_aPanelInfo[Y][X].m_pPanel != nullptr)
			{//NULLチェック
				m_aPanelInfo[Y][X].m_pPanel = nullptr;
			}
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

	/* 描画する */

	//背景
	m_pBg->SetIsDraw(m_bPanel);

	//選択用パネル
	m_pSelect->SetIsDraw(m_bPanel);

	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			if (m_aPanelInfo[Y][X].m_pPanel == nullptr)
			{//NULLチェック
				continue;
			}

			/* nullptrではない場合 */

			//パネル
			m_aPanelInfo[Y][X].m_pPanel->SetIsDraw(m_bPanel);

			//現在のステージを取得
			CStage::STAGE stage = CGame::GetStage()->Get();

			if (m_aPanelInfo[Y][X].stage == stage)
			{//現在のステージに該当するパネルを探す
				//色を暗くする
				m_aPanelInfo[Y][X].m_pPanel->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			}
		}
	}

	if (!m_bPanel)
	{//パネル操作をしていない場合
		return;
	}

	/* パネル操作中の場合 */

	//パネルの選択
	SelectPanel();
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
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{//Enterキー
		//選択：非選択の切り替え
		m_bIsSelect = m_bIsSelect ? false : true;
	}

	//選択用パネルの移動
	MoveSelect();

	//パネルのサイズの設定
	SetPanelSize();

	//選択用パネルの色の設定
	SetSelectColor();

	//パネルの移動
	MovePanel();
}

//================================================
//選択用パネルの移動
//================================================
void CPanel::MoveSelect()
{
	if (m_bIsSelect)
	{//選択中の場合
		return;
	}

	/* 選択中ではない場合 */

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

		if (m_nPosY >= GRID_Y)
		{//2より大きく(3以上)になった場合
			m_nPosY = GRID_Y - 1;	//2に固定
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

		if (m_nPosX >= GRID_X)
		{//2より大きく(3以上)になった場合
			m_nPosX = GRID_X - 1;	//2に固定
		}
	}

	//選択用パネルの位置の設定
	m_pSelect->SetPos(m_aPos[m_nPosY][m_nPosX]);
}

//================================================
//パネルのサイズの設定
//================================================
void CPanel::SetPanelSize()
{
	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			if (m_aPanelInfo[Y][X].stage == CStage::STAGE::NONE)
			{//ステージが無い場合
				continue;
			}

			/* ステージがある場合 */

			//ポインタを取得
			CObject2D* pPanel = m_aPanelInfo[Y][X].m_pPanel;

			if (pPanel == nullptr)
			{//NULLチェック
				continue;
			}

			/* nullptrではない場合 */

			//位置を取得
			D3DXVECTOR3 posPanel = pPanel->GetPos();		//パネル
			D3DXVECTOR3 posSelect = m_pSelect->GetPos();	//選択用パネル

			if (posPanel != posSelect)
			{//同じ位置にいない場合
				continue;
			}

			/* 同じ位置にある場合 */

			//サイズ設定用
			D3DXVECTOR2 size = D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE);

			if (m_bIsSelect)
			{//選択中の場合
				//サイズを少し大きくする
				size = D3DXVECTOR2(PANEL_SIZE + 10.0f, PANEL_SIZE + 10.0f);
			}

			//サイズの設定
			pPanel->SetSize(size);
		}
	}
}

//================================================
//選択用パネルの色の設定
//================================================
void CPanel::SetSelectColor()
{
	if (m_pSelect == nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrではない場合 */

	//色設定用
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	if (m_bIsSelect)
	{//選択中の場合
		//色を変える
		col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	}

	//色の設定
	m_pSelect->SetCol(col);
}

//================================================
//パネルの移動
//================================================
void CPanel::MovePanel()
{
	if (!m_bIsSelect)
	{//選択中ではない場合
		return;
	}

	/* 選択中の場合 */

	//現在位置の番号を保存
	int nPosX = m_nPosX;	//X
	int nPosY = m_nPosY;	//Y

	if (m_aPanelInfo[nPosX][nPosY].stage == CStage::STAGE::NONE)
	{//選択したパネルに、該当するステージが無い場合
		return;
	}

	bool bCanMove = false;	//移動できるかどうか

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_D))
	{//Dキー
		nPosX++;	//+1する

		if (nPosX >= GRID_X)
		{//2より大きく(3以上)になった場合
			nPosX = (GRID_X - 1);	//2に固定
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_A))
	{//Aキー
		nPosX--;	//-1する

		if (nPosX < 0)
		{//0未満(-1以下)になった場合
			nPosX = 0;	//0に固定
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_W))
	{//Wキー
		nPosY--;	//-1する

		if (nPosY < 0)
		{//0未満(-1以下)になった場合
			nPosY = 0;	//0に固定
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_S))
	{//Sキー
		nPosY++;	//+1する

		if (nPosY >= GRID_Y)
		{//2より大きく(3以上)になった場合
			nPosY = (GRID_Y - 1);	//2に固定
		}
	}

	if (m_aPanelInfo[nPosY][nPosX].stage == CStage::STAGE::NONE)
	{//移動先にステージが無い場合
		//移動できる
		bCanMove = true;
	}

	if (bCanMove)
	{//移動できる場合
		//移動先のステージ情報を保存
		CStage::STAGE stageDest = m_aPanelInfo[nPosY][nPosX].stage;

		//ステージ情報を入れ替える
		m_aPanelInfo[nPosY][nPosX].stage = m_aPanelInfo[m_nPosY][m_nPosX].stage;
		m_aPanelInfo[m_nPosY][m_nPosX].stage = stageDest;

		//位置を入れ替える
		m_aPanelInfo[nPosY][nPosX].m_pPanel->SetPos(m_aPos[m_nPosY][m_nPosX]);
		m_aPanelInfo[m_nPosY][m_nPosX].m_pPanel->SetPos(m_aPos[nPosY][nPosX]);

		//選択されていない状態にする
		m_bIsSelect = false;

		//移動完了
		bCanMove = false;
	}
}