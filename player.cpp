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
#include "model.h"

#include "debug_proc.h"

#include <assert.h>

//***************************
//namespaceの定義
//***************************
namespace Utility	//便利関数
{
/*
	角度の正規化
	float *pAngle ---> 角度
*/
void NormalizeAngle(float* pAngle);
} //namespaceはここまで

//***************************
//定数の定義
//***************************
const float CPlayer::MOVE_SPEED = 1.5f;	//移動速度

//***************************
//静的メンバ変数
//***************************
CPlayer::KEY_SET CPlayer::m_aKeySet[NUM_KEYSET] =
{
	/* KEY : 0 / 2 */
	{ 45,	//フレーム数
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,0.09f,0.0f),	//向き(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,-0.91f,0.0f),	//向き(ROT)
		}
	},
	
	/* KEY : 1 / 2 */
	{ 45,	//フレーム数
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,-0.09f,0.0f),	//向き(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,0.91f,0.0f),	//向き(ROT)
		}
	},
};

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
CPlayer::CPlayer() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nNumKey(0),
	m_nCurrentKey(0),
	m_nCntMotion(0)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	memset(m_apModel, 0, sizeof(m_apModel));

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
	/*for (int i = 0; i < MAX_PARTS; i++)
	{
		m_apModel[i] = CModel::Create();
	}*/

	m_apModel[0] = CModel::Create(CModel::XFILE::Fish_Body);
	m_apModel[1] = CModel::Create(CModel::XFILE::Fish_Tail);

	//親モデルの設定
	m_apModel[1]->SetParent(m_apModel[0]);

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;

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

	//モーション
	Motion();

	CDebugProc::Print("\n");
	CDebugProc::Print("m_rot : [%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);

	D3DXVECTOR3 aRot[2] =
	{
		m_apModel[0]->GetRot(),
		m_apModel[1]->GetRot(),
	};

	CDebugProc::Print("m_apModel[0]->GetRot() : [%f,%f,%f]\n", aRot[0].x, aRot[0].y, aRot[0].z);
	CDebugProc::Print("m_apModel[1]->GetRot() : [%f,%f,%f]\n", aRot[1].x, aRot[1].y, aRot[1].z);
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

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//モデルの描画
		m_apModel[i]->Draw();
	}
}

//================================================
//移動
//================================================
void CPlayer::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	//向きを変える(急ごしらえ)
	if (pKeyboard->GetPress(DIK_Q))
	{
		m_rot.y += 0.01f;
	}
	else if (pKeyboard->GetPress(DIK_E))
	{
		m_rot.y -= 0.01f;
	}

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

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量を0にする
}

//================================================
//モーション
//================================================
void CPlayer::Motion()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_apModel[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		//相対値を計算(モーションカウンター / 再生フレーム数)
		float fRelativeValue = (float)(m_nCntMotion / m_aKeySet[i].nFrame);

		//次のキー番号(計算用)
		int nNextKey = (m_nCurrentKey + 1) % m_nNumKey;

		//差分(終了値 - 開始値)
		D3DXVECTOR3 posDif = (m_aKeySet[nNextKey].aKey[i].pos - m_aKeySet[m_nCurrentKey].aKey[i].pos);
		D3DXVECTOR3 rotDif = (m_aKeySet[nNextKey].aKey[i].rot - m_aKeySet[m_nCurrentKey].aKey[i].rot);

		//差分 * 相対値
		D3DXVECTOR3 pos = D3DXVECTOR3(	//位置
			posDif.x * fRelativeValue,
			posDif.y * fRelativeValue,
			posDif.z * fRelativeValue);

		D3DXVECTOR3 rot = D3DXVECTOR3(	//向き
			rotDif.x * fRelativeValue,
			rotDif.y * fRelativeValue,
			rotDif.z * fRelativeValue);

		//位置・向きの現在値を取得
		D3DXVECTOR3 posPre = m_apModel[i]->GetPos();
		D3DXVECTOR3 rotPre = m_apModel[i]->GetRot();

		//現在値に加算(開始値 + (差分 * 相対値))
		if (m_nCurrentKey < nNextKey)
		{//キーが進む時
			posPre += m_aKeySet[m_nCurrentKey].aKey[i].pos + pos;
			rotPre += m_aKeySet[m_nCurrentKey].aKey[i].rot + rot;
		}
		else if (m_nCurrentKey > nNextKey)
		{//初めのキー番号に戻る時
			posPre += m_aKeySet[m_nCurrentKey].aKey[i].pos - pos;
			rotPre += m_aKeySet[m_nCurrentKey].aKey[i].rot - rot;
		}

		//角度の正規化
		Utility::NormalizeAngle(&rotPre.x);	
		Utility::NormalizeAngle(&rotPre.y);
		Utility::NormalizeAngle(&rotPre.z);

		//位置・向きを反映
		m_apModel[i]->SetPos(posPre);
		m_apModel[i]->SetRot(rotPre);
	}

	m_nCntMotion++;	//モーションカウンターを進める

	if (m_nCntMotion < m_aKeySet[m_nCurrentKey].nFrame)
	{//モーションカウンターが再生フレーム数に達していない場合
		return;
	}

	/* 再生フレーム数に達した場合 */

	m_nCurrentKey++;	//現在のキー番号を一つ進める
	m_nCntMotion = 0;	//モーションカウンターを初期化

	if (m_nCurrentKey == m_nNumKey)
	{//現在のキー番号が、キーの総数に達したら
		m_nCurrentKey = 0;	//現在のキー番号を0に戻す
	}
}

namespace Utility
{
//------------------------------------------------
//角度の正規化
//------------------------------------------------
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{//角度が[3.14]以上の場合
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{//角度が[-3.14]以下の場合
		*pAngle += D3DX_PI * 2.0f;
	}
}
} //namespaceはここまで