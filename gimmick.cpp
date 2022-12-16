//================================================
//
//3Dゲーム(仮)[gimmick.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "gimmick.h"
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
const float CGimmick::MOVE_SPEED = 1.5f;		//移動速度
const float CGimmick::ROT_SMOOTHNESS = 0.5f;	//回転の滑らかさ
const float CGimmick::ROTATION_SPEED = 0.25f;	//回転速度

//================================================
//生成
//================================================
CGimmick* CGimmick::Create()
{
	CGimmick* pGimmick = nullptr;	//ポインタ

	if (pGimmick != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pGimmick = new CGimmick;	//メモリの動的確保

	pGimmick->Init();	//初期化

	return pGimmick;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CGimmick::CGimmick() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_quaternion(D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f)),
	m_bPressKey(false),
	m_bMove(false),
	m_bRotation(false)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));

	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::GIMMICK);
}

//================================================
//デストラクタ
//================================================
CGimmick::~CGimmick()
{
}

//================================================
//初期化
//================================================
HRESULT CGimmick::Init()
{
	//モデルの生成
	m_pModel = CModel::Create(CModel::XFILE::Stage_Debug_Obstade);

	//頂点の最大値・最小値を取得
	m_vtxMax = m_pModel->GetVtxMax();
	m_vtxMin = m_pModel->GetVtxMin();

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_bPressKey = false;
	m_bMove = false;
	m_bRotation = false;

	return S_OK;
}

//================================================
//終了
//================================================
void CGimmick::Uninit()
{
}

//================================================
//更新
//================================================
void CGimmick::Update()
{
	if (m_bMove)
	{//移動アリの場合
		//移動
		Move();

		if (m_bRotation)
		{//回転アリの場合
			//クォータニオンによる回転
			RotationQuaternion();
		}
	}

	//移動量を0にする
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#ifdef _DEBUG
	//各情報を表示
	CDebugProc::Print("\n《 Gimmick 》\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_quaternion:[%f,%f,%f,%f]\n", m_quaternion.x, m_quaternion.y, m_quaternion.z, m_quaternion.w);
#endif // _DEBUG
}

//================================================
//描画
//================================================
void CGimmick::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	/*D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);*/

	//クォータニオンを使用した姿勢の設定
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);	//クオータニオンによる行列回転
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);	//行列掛け算関数(第2引数×第3引数を第1引数に格納)

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
void CGimmick::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_K))
	{//Dキー押下中
		if (pKeyboard->GetPress(DIK_U))
		{//右前
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//移動方向を設定
		}
		else if (pKeyboard->GetPress(DIK_J))
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
	else if (pKeyboard->GetPress(DIK_H))
	{//Aキー押下中
		if (pKeyboard->GetPress(DIK_U))
		{//左前
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//移動方向を設定
		}
		else if (pKeyboard->GetPress(DIK_J))
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
	else if (pKeyboard->GetPress(DIK_U))
	{//Wキー押下中
		m_vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//移動方向を設定

		//キー押下中
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_J))
	{//Sキー押下中
		m_vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//移動方向を設定

		//キー押下中
		m_bPressKey = true;
	}

	//********** ↓ 移動方向 ↓ **********//

	////ベクトルの大きさを1にする
	//D3DXVec3Normalize(&m_vec, &m_vec);

	////2方向の単位ベクトルから角度を求める
	//m_rotDest.y = atan2f(-m_vec.x, -m_vec.z);

	////現在の向きと目的の向きの差分を計算
	//float fDif = m_rotDest.y - m_rot.y;

	////角度の正規化
	//NormalizeAngle(&fDif);

	////現在の向きを更新
	//m_rot.y += fDif * ROT_SMOOTHNESS;

	////角度の正規化
	//NormalizeAngle(&m_rot.y);

	//********** ↓ 移動量 ↓ **********//

	if (!m_bPressKey)
	{//移動キーが押されていない場合
		return;
	}

	/* 移動キーが押されている場合 */

	//移動量に代入(移動ベクトル * 移動速度)
	m_move = m_vec * MOVE_SPEED;

	//位置に移動量を加算
	m_pos += m_move;

	//「キー押下されていない」にする
	m_bPressKey = false;
}

//================================================
//クォータニオンによる回転
//================================================
void CGimmick::RotationQuaternion()
{
	D3DXVECTOR3 axis;					//回転軸
	D3DXVECTOR3 inverseVec = -m_move;	//move値を反対にする

	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//外積で回転軸を算出
	D3DXVec3Cross(&axis, &inverseVec, &vecY);
	
	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//クオータニオン計算用

	//回転軸と回転角度を指定
	D3DXQuaternionRotationAxis(&quaternion, &axis, ROTATION_SPEED);
	
	// クオータニオンを適用
	m_quaternion *= quaternion;
	
	// クオータニオンのノーマライズ
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);
}

//================================================
//移動の有無を設定
//================================================
void CGimmick::SetFlagOfMove(bool bMove)
{
	m_bMove = bMove;
}

//================================================
//回転の有無を設定
//================================================
void CGimmick::SetFlagOfRotation(bool bRotation)
{
	m_bRotation = bRotation;
}

//================================================
//位置を設定
//================================================
void CGimmick::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CGimmick::GetPos()
{
	return m_pos;
}

//================================================
//頂点の最大値を取得
//================================================
D3DXVECTOR3 CGimmick::GetVtxMax()
{
	return m_vtxMax;
}

//================================================
//頂点の最小値を取得
//================================================
D3DXVECTOR3 CGimmick::GetVtxMin()
{
	return m_vtxMin;
}