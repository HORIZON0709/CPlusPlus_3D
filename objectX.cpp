//================================================
//
//3Dゲーム(仮)[objectX.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "objectX.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "model.h"

#include "debug_proc.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CObjectX::ROTATION_SPEED = 0.25f;	//回転速度
const float CObjectX::MOVE_SPEED = 5.0f;		//移動速度

//================================================
//生成
//================================================
CObjectX* CObjectX::Create()
{
	CObjectX* pObjectX = nullptr;	//ポインタ

	if (pObjectX != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pObjectX = new CObjectX;	//メモリの動的確保

	pObjectX->Init();	//初期化

	return pObjectX;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CObjectX::CObjectX() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_quaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),
	m_bPressKey(false),
	m_bMove(false),
	m_bRotation(false)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//デストラクタ
//================================================
CObjectX::~CObjectX()
{
}

//================================================
//初期化
//================================================
HRESULT CObjectX::Init()
{
	//モデルの生成
	m_pModel = CModel::Create(CModel::XFILE::Stage_Debug_Obstade);

	//メンバ変数の初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_bPressKey = false;
	m_bMove = false;
	m_bRotation = false;
	
	return S_OK;
}

//================================================
//終了
//================================================
void CObjectX::Uninit()
{
}

//================================================
//更新
//================================================
void CObjectX::Update()
{
#ifdef _DEBUG
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

	//各情報を表示
	CDebugProc::Print("\n《 ObjectX 》\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_quaternion:[%f,%f,%f,%f]\n", m_quaternion.x, m_quaternion.y, m_quaternion.z, m_quaternion.w);
#endif // _DEBUG
}

//================================================
//描画
//================================================
void CObjectX::Draw()
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

	//モデルの影を描画
	//DrawShadow();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モデルの描画
	m_pModel->Draw();
}

//================================================
//位置を設定
//================================================
void CObjectX::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CObjectX::GetPos()
{
	return m_pos;
}

//================================================
//移動量を設定
//================================================
void CObjectX::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//移動量を取得
//================================================
D3DXVECTOR3 CObjectX::GetMove()
{
	return m_move;
}

//================================================
//移動の有無を設定
//================================================
void CObjectX::SetFlagOfMove(bool bMove)
{
	m_bMove = bMove;
}

//================================================
//回転の有無を設定
//================================================
void CObjectX::SetFlagOfRotation(bool bRotation)
{
	m_bRotation = bRotation;
}

//================================================
//移動
//================================================
void CObjectX::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_K))
	{//Kキー押下中
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
void CObjectX::RotationQuaternion()
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