//================================================
//
//制作実践基礎[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "player.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
//#include "objectMesh.h"
#include "model.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPlayer::MOVE_SPEED = 3.0f;	//移動速度

//================================================
//生成
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//ポインタ

	if (pPlayer != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pPlayer = new CPlayer;	//メモリの動的確保

	pPlayer->Init();	//初期化

	return pPlayer;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer() :
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));

	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//初期化
//================================================
HRESULT CPlayer::Init()
{
	//モデルの生成
	m_pModel = CModel::Create();

	//親モデルの設定
	//CModel::SetParent(m_pModel);

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
}

//================================================
//更新
//================================================
void CPlayer::Update()
{
	//移動
	Move();

	//D3DXVECTOR3 pos = CObjectX::GetPos();	//位置を取得

	////メッシュとの当たり判定
	//CGame::GetMesh()->Collision(&pos);

	//CObjectX::SetPos(pos);
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モデルの描画
	m_pModel->Draw();
}

//================================================
//移動
//================================================
void CPlayer::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_D))
	{//右
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//右前
			m_move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			m_move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//右後ろ
			m_move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			m_move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z軸方向
		}
		else
		{//右
			m_move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//左
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//左前
			m_move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			m_move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//左後ろ
			m_move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			m_move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z軸方向
		}
		else
		{//左
			m_move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//前
		m_move.z += cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Z軸方向
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//後ろ
		m_move.z += cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Z軸方向
	}

	m_pos += m_move;	//位置に移動量を加算
}