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
#include "objectMesh.h"

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
CPlayer::CPlayer()
{
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
	CObjectX::Init();	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObjectX::SetPos(pos);

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CPlayer::Update()
{
	CObjectX::Update();	//親クラス

	//移動
	Move();
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	CObjectX::Draw();	//親クラス
}

//================================================
//移動
//================================================
void CPlayer::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	D3DXVECTOR3 pos = CObjectX::GetPos();	//位置を取得
	D3DXVECTOR3 move = CObjectX::GetMove();	//移動量を取得

	if (pKeyboard->GetPress(DIK_D))
	{//右
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//右前
			move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//右後ろ
			move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z軸方向
		}
		else
		{//右
			move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//左
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//左前
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//左後ろ
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z軸方向
		}
		else
		{//左
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//前
		move.z += cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Z軸方向
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//後ろ
		move.z += cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Z軸方向
	}

	pos += move;	//位置に移動量を加算

	CObjectX::SetPos(pos);	//位置を更新
}