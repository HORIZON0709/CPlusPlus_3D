//================================================
//
//3Dゲーム(仮)[player.cpp]
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
#include "utility.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPlayer::MOVE_SPEED = 1.5f;		//移動速度
const float CPlayer::ROT_SMOOTHNESS = 0.5f;	//回転の滑らかさ

//***************************
//静的メンバ変数
//***************************
CPlayer::KEY_SET CPlayer::m_aKeySet[NUM_KEYSET] =
{
	/* KEY : 0 / 2 */
	{ 45,	//フレーム数
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,0.18f,0.0f),	//向き(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,-1.82f,0.0f),	//向き(ROT)
		}
	},
	
	/* KEY : 1 / 2 */
	{ 45,	//フレーム数
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,-0.18f,0.0f),	//向き(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//位置(POS)
		D3DXVECTOR3(0.0f,1.82f,0.0f),	//向き(ROT)
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
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nNumKey(0),
	m_nCurrentKey(0),
	m_nCntMotion(0),
	m_bPressKey(false)
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

	//頂点の最大値と最小値を設定
	SetVtxMaxAndMin();

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;
	m_bPressKey = false;

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

	//CollisionModel(m_pos,m_pModelTarget->GetPos(),)

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

#ifdef _DEBUG
	//各情報を表示
	CDebugProc::Print("\n《 Player 》\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("m_vec:[%f,%f,%f]\n", m_vec.x, m_vec.y, m_vec.z);

	CDebugProc::Print("m_vtxMax:[%f,%f,%f]\n", m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	CDebugProc::Print("m_vtxMin:[%f,%f,%f]\n", m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
#endif // _DEBUG
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

	if (pKeyboard->GetPress(DIK_D))
	{//Dキー押下中
		if (pKeyboard->GetPress(DIK_W))
		{//右前
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//移動方向を設定
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//右後ろ
			m_vec = D3DXVECTOR3(1.0f, 0.0f, -1.0f);	//移動方向を設定
		}
		else
		{//右
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	//移動方向を設定
		}

		//キー押下中
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//Aキー押下中
		if (pKeyboard->GetPress(DIK_W))
		{//左前
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//移動方向を設定
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//左後ろ
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);	//移動方向を設定
		}
		else
		{//左
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);	//移動方向を設定
		}

		//キー押下中
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//Wキー押下中
		m_vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//移動方向を設定

		//キー押下中
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//Sキー押下中
		m_vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//移動方向を設定

		//キー押下中
		m_bPressKey = true;
	}

	//********** ↓ 移動方向 ↓ **********//

	//ベクトルの大きさを1にする
	D3DXVec3Normalize(&m_vec, &m_vec);

	//2方向の単位ベクトルから角度を求める
	m_rotDest.y = atan2f(-m_vec.x, -m_vec.z);

	//現在の向きと目的の向きの差分を計算
	float fDif = m_rotDest.y - m_rot.y;

	//角度の正規化
	NormalizeAngle(&fDif);

	//現在の向きを更新
	m_rot.y += fDif * ROT_SMOOTHNESS;

	//角度の正規化
	NormalizeAngle(&m_rot.y);

	//********** ↓ 移動量 ↓ **********//

	if (!m_bPressKey)
	{//移動キーが押されていない場合
		return;
	}

	/* 移動キーが押されている場合 */

	//移動量に代入(移動ベクトル * 移動速度)
	m_move = m_vec * MOVE_SPEED;

	//現在の位置を、前回の位置として保存
	m_posOld = m_pos;

	//現在の位置に移動量を加算
	m_pos += m_move;

	//移動量を0にする
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//「キー押下されていない」にする
	m_bPressKey = false;
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
		float fRelativeValue = (float)m_nCntMotion / (float)m_aKeySet[m_nCurrentKey].nFrame;

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

		//現在値に代入(開始値 + (差分 * 相対値))
		posPre = m_aKeySet[m_nCurrentKey].aKey[i].pos + pos;
		rotPre = m_aKeySet[m_nCurrentKey].aKey[i].rot + rot;

		//角度の正規化
		NormalizeAngle(&rotPre.x);	
		NormalizeAngle(&rotPre.y);
		NormalizeAngle(&rotPre.z);

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

//================================================
//頂点の最大値と最小値を設定
//================================================
void CPlayer::SetVtxMaxAndMin()
{
	//各パーツの頂点の最大値と最小値を格納する配列
	D3DXVECTOR3 aVtxMax[MAX_PARTS] = {};
	D3DXVECTOR3 aVtxMin[MAX_PARTS] = {};

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//各パーツから、頂点の最大値と最小値を取得
		aVtxMax[i] = m_apModel[i]->GetVtxMax();
		aVtxMin[i] = m_apModel[i]->GetVtxMin();
	}

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if ((i + 1) >= MAX_PARTS)
		{//パーツ数の次のカウントが、最大パーツ数を超える場合
			break;
		}

		//********** 最大値 **********//

		if (aVtxMax[i] > aVtxMax[i + 1])
		{//[ 現在のパーツの最大値 > 次のパーツの最大値]
			m_vtxMax = aVtxMax[i];	//現在のパーツの最大値を設定
		}
		else if (aVtxMax[i] < aVtxMax[i + 1])
		{//[ 現在のパーツの最大値 < 次のパーツの最大値]
			m_vtxMax = aVtxMax[i + 1];	//次のパーツの最大値を設定
		}

		//********** 最小値 **********//

		if (aVtxMin[i] < aVtxMin[i + 1])
		{//[ 現在のパーツの最小値 < 次のパーツの最小値]
			m_vtxMin = aVtxMin[i];	//現在のパーツの最小値を設定
		}
		else if (aVtxMin[i] > aVtxMin[i + 1])
		{//[ 現在のパーツの最小値 > 次のパーツの最小値]
			m_vtxMin = aVtxMin[i + 1];	//現在のパーツの最小値を設定
		}
	}
}