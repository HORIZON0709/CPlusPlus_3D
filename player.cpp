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
#include "gimmick.h"
#include "line.h"
#include "item.h"

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

CLine* CPlayer::m_apLine[MAX_LINE] = {};	//ラインのポインタ

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
	m_pTargetGimmick(nullptr),
	m_pTargetItem(nullptr),
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
	m_bPressKey(false),
	m_bCollision(false),
	m_bGetItem(false)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	memset(m_apModel, 0, sizeof(m_apModel));

	for (int i = 0; i < NUM_VTX_3D; i++)
	{
		m_aPosVtx[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

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
	m_apModel[0] = CModel::Create(CModel::XFILE::Fish_Body);
	m_apModel[1] = CModel::Create(CModel::XFILE::Fish_Tail);

	//親モデルの設定
	m_apModel[1]->SetParent(m_apModel[0]);

	//頂点の最大値と最小値を設定
	SetVtxMaxAndMin();

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	/*
		頂点の最大値・最小値から、モデルの範囲を表す頂点の位置を設定する
		コメント ---> 正面から見た頂点の位置
	*/
	/* 左側 */
	m_aPosVtx[0] = m_vtxMin;										//手前の下側(最小値)
	m_aPosVtx[1] = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);	//奥の下側
	m_aPosVtx[2] = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);	//手前の上側
	m_aPosVtx[3] = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);	//奥の上側

	/* 右側 */
	m_aPosVtx[4] = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);	//手前の下側
	m_aPosVtx[5] = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);	//奥の下側
	m_aPosVtx[6] = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);	//手前の上側
	m_aPosVtx[7] = m_vtxMax;										//奥の上側(最大値)

	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;
	m_bPressKey = false;
	m_bCollision = false;
	m_bGetItem = false;

	for (int i = 0; i < MAX_LINE; i++)
	{
		m_apLine[i] = CLine::Create();
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_apLine[i] != nullptr)
		{
			m_apLine[i]->Uninit();
			delete m_apLine[i];
			m_apLine[i] = nullptr;
		}
	}
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

	//当たり判定
	Collision();

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

	if (m_bGetItem)
	{
		m_pTargetItem->Release();
		m_pTargetItem = nullptr;
	}

#ifdef _DEBUG
	//各情報を表示
	CDebugProc::Print("\n《 Player 》\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("m_vec:[%f,%f,%f]\n", m_vec.x, m_vec.y, m_vec.z);

	D3DXVECTOR3 size = m_vtxMax - m_vtxMin;

	CDebugProc::Print("size:[%f,%f,%f]\n", size.x, size.y, size.z);

	if (m_bCollision)
	{//対象のオブジェクトに当たっている場合
		CDebugProc::Print("Collision:[true]\n", m_bCollision);
	}
	else
	{//当たっていない場合
		CDebugProc::Print("Collision:[false]\n", m_bCollision);
	}

	//ラインの設定まとめ
	SetLines();

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

	for (int i = 0; i < MAX_LINE; i++)
	{
		//ラインの描画
		m_apLine[i]->Draw();
	}
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CPlayer::GetPos()
{
	return m_pos;
}

//================================================
//移動
//================================================
void CPlayer::Move()
{
	//キーボード情報を取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_R))
	{
		m_pos.y += 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_F))
	{
		m_pos.y -= 0.5f;
	}

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
//当たり判定
//================================================
void CPlayer::Collision()
{
	//当たり判定対象のギミック情報を取得
	m_pTargetGimmick = CGame::GetGimmick();

	D3DXMATRIX mtxRotOwn;	//計算用マトリックス

	//向きからヨー・ピッチ・ロールを指定し、マトリックスを作成
	D3DXMatrixRotationYawPitchRoll(&mtxRotOwn, m_rot.y, m_rot.x, m_rot.z);

	D3DXVECTOR3 posVtx[NUM_VTX_3D] = {};	//保存用配列

	for (int i = 0; i < NUM_VTX_3D; i++)
	{
		//マトリックスを変換して回転させた後の頂点の位置を保存する
		D3DXVec3TransformCoord(&posVtx[i], &m_aPosVtx[i], &mtxRotOwn);
	}

	//***** 回転後の各頂点の位置を比較し、最大値・最小値を設定する ******//

	//頂点の最大値・最小値設定用
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	for (int i = 0; i < NUM_VTX_3D; i++)
	{
		/* 最大値 */

		if (posVtx[i].x > vtxMax.x)
		{//X座標
			vtxMax.x = posVtx[i].x;	//最大値を設定
		}

		if (posVtx[i].y > vtxMax.y)
		{//Y座標
			vtxMax.y = posVtx[i].y;	//最大値を設定
		}

		if (posVtx[i].z > vtxMax.z)
		{//Z座標
			vtxMax.z = posVtx[i].z;	//最大値を設定
		}
		
		/* 最小値 */

		if (posVtx[i].x < vtxMin.x)
		{//X座標
			vtxMin.x = posVtx[i].x;	//最小値を設定
		}

		if (posVtx[i].y < vtxMin.y)
		{//Y座標
			vtxMin.y = posVtx[i].y;	//最小値を設定
		}

		if (posVtx[i].z < vtxMin.z)
		{//Z座標
			vtxMin.z = posVtx[i].z;	//最小値を設定
		}
	}

	//***** サイズを設定する *****//

	//自身
	D3DXVECTOR3 sizeOwn = (vtxMax - vtxMin);

	//対象
	D3DXVECTOR3 sizeTarget = (m_pTargetGimmick->GetVtxMax() - m_pTargetGimmick->GetVtxMin());

	//モデル同士の当たり判定
	m_bCollision = CollisionModel(
		&m_pos,					//自身の現在の位置
		m_posOld,				//自身の前回の位置
		m_pTargetGimmick->GetPos(),	//対象の位置
		sizeOwn,				//自身のサイズ
		sizeTarget				//対象のサイズ
	);

	if (m_bGetItem)
	{
		return;
	}

	//アイテム所法を取得
	m_pTargetItem = CGame::GetItem();

	//サイズを設定
	sizeTarget = (m_pTargetItem->GetVtxMax() - m_pTargetItem->GetVtxMin());

	//当たり判定
	m_bGetItem = CollisionModel(
		&m_pos,					//自身の現在の位置
		m_posOld,				//自身の前回の位置
		m_pTargetItem->GetPos(),	//対象の位置
		sizeOwn,				//自身のサイズ
		sizeTarget				//対象のサイズ
	);
}

//================================================
//頂点の最大値と最小値を設定
//================================================
void CPlayer::SetVtxMaxAndMin()
{
	//頂点の最大数・最小値を初期化
	m_vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	m_vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//各パーツの頂点の最大値・最小値を格納する配列
	D3DXVECTOR3 aVtxMax[MAX_PARTS] = {};
	D3DXVECTOR3 aVtxMin[MAX_PARTS] = {};

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//各パーツから頂点の最大値・最小値を取得
		aVtxMax[i] = m_apModel[i]->GetVtxMax();
		aVtxMin[i] = m_apModel[i]->GetVtxMin();
	}

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//********** 最大値 **********//

		/* 各パーツの最大値が、現在の最大値より大きい場合、最大値を設定する */

		if (aVtxMax[i].x > m_vtxMax.x)
		{//X座標
			m_vtxMax.x = aVtxMax[i].x;	//最大値を設定
		}

		if (aVtxMax[i].y > m_vtxMax.y)
		{//Y座標
			m_vtxMax.y = aVtxMax[i].y;	//最大値を設定
		}

		if (aVtxMax[i].z> m_vtxMax.z)
		{//Z座標
			m_vtxMax.z = aVtxMax[i].z;	//最大値を設定
		}
		
		//********** 最小値 **********//

		/* 各パーツの最小値が、現在の最小値より小さい場合、最小値を設定する */

		if (aVtxMin[i].x < m_vtxMin.x)
		{//X座標
			m_vtxMin.x = aVtxMin[i].x;	//最小値を設定
		}

		if (aVtxMin[i].y < m_vtxMin.y)
		{//Y座標
			m_vtxMin.y = aVtxMin[i].y;	//最小値を設定
		}

		if (aVtxMin[i].z < m_vtxMin.z)
		{//Z座標
			m_vtxMin.z = aVtxMin[i].z;	//最小値を設定
		}
	}
}

//================================================
//ラインの設定まとめ
//================================================
void CPlayer::SetLines()
{
	//色(全ての線で同じ色)
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//何番目か
	int nNum = 0;

	//********** 上部左側 **********//

	//始点・終点
	D3DXVECTOR3 start = m_aPosVtx[3];
	D3DXVECTOR3 end = m_aPosVtx[2];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部手前側 **********//

	//始点・終点
	start = m_aPosVtx[2];
	end = m_aPosVtx[6];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部右側 **********//

	//始点・終点
	start = m_aPosVtx[6];
	end = m_aPosVtx[7];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部奥側 **********//

	//始点・終点
	start = m_aPosVtx[7];
	end = m_aPosVtx[3];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部左側 **********//

	//始点・終点
	start = m_aPosVtx[1];
	end = m_aPosVtx[0];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部手前側 **********//

	//始点・終点
	start = m_aPosVtx[0];
	end = m_aPosVtx[4];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部右側 **********//

	//始点・終点
	start = m_aPosVtx[4];
	end = m_aPosVtx[5];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部奥側 **********//

	//始点・終点
	start = m_aPosVtx[5];
	end = m_aPosVtx[1];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 手前左側 **********//

	//始点・終点
	start = m_aPosVtx[2];
	end = m_aPosVtx[0];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 手前右側 **********//

	//始点・終点
	start = m_aPosVtx[6];
	end = m_aPosVtx[4];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 奥左側 **********//

	//始点・終点
	start = m_aPosVtx[3];
	end = m_aPosVtx[1];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 奥右側 **********//

	//始点・終点
	start = m_aPosVtx[7];
	end = m_aPosVtx[5];

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める
}