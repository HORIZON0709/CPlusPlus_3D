//================================================
//
//3Dゲーム(仮)[item.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "item.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "model.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CItem::ROTATION_SPEED = 0.05f;	//回転速度

//================================================
//生成
//================================================
CItem* CItem::Create()
{
	CItem* pItem = nullptr;	//ポインタ

	if (pItem != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pItem = new CItem;	//メモリの動的確保

	pItem->Init();	//初期化

	return pItem;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CItem::CItem() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_bPressKey(false)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));

	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::ITEM);
}

//================================================
//デストラクタ
//================================================
CItem::~CItem()
{
}

//================================================
//初期化
//================================================
HRESULT CItem::Init()
{
	//モデルの生成
	m_pModel = CModel::Create(CModel::XFILE::Coin01);

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bPressKey = false;

	return S_OK;
}

//================================================
//終了
//================================================
void CItem::Uninit()
{
}

//================================================
//更新
//================================================
void CItem::Update()
{
	//回転
	m_rot.y += ROTATION_SPEED;

	//角度の正規化
	NormalizeAngle(&m_rot.y);

#ifdef _DEBUG
	//各情報を表示
	CDebugProc::Print("\n《 Item 》\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);

#endif // _DEBUG
}

//================================================
//描画
//================================================
void CItem::Draw()
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