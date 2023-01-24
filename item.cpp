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
#include "line.h"
#include "objectX.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CItem::ROTATION_SPEED = 0.05f;	//回転速度

//***************************
//静的メンバ変数
//***************************
CLine* CItem::m_apLine[MAX_LINE] = {};	//ラインのポインタ

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
	m_pModel = CObjectX::Create("data/MODEL/Coin01.x");

	//頂点の最大値・最小値を設定
	m_vtxMax = m_pModel->GetVtxMax();
	m_vtxMin = m_pModel->GetVtxMin();

	//メンバ変数の初期化
	m_pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bPressKey = false;

	for (int i = 0; i < MAX_LINE; i++)
	{
		m_apLine[i] = CLine::Create();
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CItem::Uninit()
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

	//ラインの設定まとめ
	SetLines();

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

	for (int i = 0; i < MAX_LINE; i++)
	{
		//ラインの描画
		m_apLine[i]->Draw();
	}
}

//================================================
//ラインの設定まとめ
//================================================
void CItem::SetLines()
{
	//色(全ての線で同じ色)
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//何番目か
	int nNum = 0;

	//********** 上部左側 **********//

	//始点・終点
	D3DXVECTOR3 start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);
	D3DXVECTOR3 end = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部手前側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部右側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 上部奥側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部左側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部手前側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部右側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 下部奥側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 手前左側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 手前右側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 奥左側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める

	//********** 奥右側 **********//

	//始点・終点
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);

	//設定
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//次に進める
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CItem::GetPos()
{
	return m_pos;
}

//================================================
//頂点の最大値を取得
//================================================
D3DXVECTOR3 CItem::GetVtxMax()
{
	return m_vtxMax;
}

//================================================
//頂点の最小値を取得
//================================================
D3DXVECTOR3 CItem::GetVtxMin()
{
	return m_vtxMin;
}