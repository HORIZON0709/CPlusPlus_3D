//================================================
//
//制作実践基礎[objectMesh.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "objectMesh.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const int CObjectMesh::NUM_BLK_X = 10;	//ブロック数(X軸)
const int CObjectMesh::NUM_BLK_Z = 10;	//ブロック数(Z軸)

const int CObjectMesh::NUM_VTX_X = (NUM_BLK_X + 1);	//頂点数(X軸)
const int CObjectMesh::NUM_VTX_Z = (NUM_BLK_Z + 1);	//頂点数(Z軸)

const float CObjectMesh::MESH_SIZE = 50.0f;	//メッシュのサイズ

//================================================
//生成
//================================================
CObjectMesh* CObjectMesh::Create()
{
	CObjectMesh* pObjectMesh = nullptr;	//ポインタ

	if (pObjectMesh != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pObjectMesh = new CObjectMesh;	//メモリの動的確保

	pObjectMesh->Init();	//初期化

	return pObjectMesh;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CObjectMesh::CObjectMesh() : CObject::CObject(CObject::PRIORITY::PRIO_MESH),
	m_pVtxBuff(nullptr),
	m_pIdxBuff(nullptr),
	m_texture(CTexture::TEXTURE::NONE),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fWidth(0.0f),
	m_fHeight(0.0f),
	m_nNumVtx(0),
	m_nNumIdx(0),
	m_nNumPol(0)
{
	//メンバ変数のクリア
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//デストラクタ
//================================================
CObjectMesh::~CObjectMesh()
{
	/* 解放漏れの確認 */
	assert(m_pVtxBuff == nullptr);
	assert(m_pIdxBuff == nullptr);
}

//================================================
//初期化
//================================================
HRESULT CObjectMesh::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//メンバ変数の初期設定
	m_texture = CTexture::TEXTURE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = MESH_SIZE;
	m_fHeight = MESH_SIZE;

	m_nNumVtx = AskVtx();	//頂点数
	m_nNumIdx = AskIdx();	//インデックス数
	m_nNumPol = AskPol();	//ポリゴン数

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(CObject3D::VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(CObject3D::VERTEX_3D) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//***** 頂点情報の初期化 *****//

	CObject3D::VERTEX_3D* pVtx = nullptr;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < m_nNumVtx; i++)
	{
		float fX = (float)(((i % NUM_VTX_X) - (NUM_BLK_X * 0.5f)) * MESH_SIZE);			//X座標
		float fZ = (float)(((i / NUM_VTX_X) - (NUM_BLK_X * 0.5f)) * MESH_SIZE * -1.0f);	//Z座標

		//頂点座標の設定
		pVtx[i].pos = D3DXVECTOR3(fX, 0.0f, fZ);

		//各頂点の法線の設定
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		float fU = (float)(i % NUM_VTX_X);	//U座標
		float fV = (float)(i / NUM_VTX_X);	//V座標

		//テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(fU, fV);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//***** インデックス情報の初期化 *****//

	WORD* pIdx = nullptr;	//インデックス情報へのポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (int z = 0, n = 0; z < NUM_BLK_Z; z++)
	{
		for (int x = 0; x < NUM_VTX_X; x++)
		{
			n = (x * 2) + ((z * 2) * NUM_VTX_X) + (z * 2);	//短くする

			pIdx[n] = (WORD)(x + (z * NUM_VTX_X) + NUM_VTX_X);
			pIdx[n + 1] = (WORD)(x + (z * NUM_VTX_X));
		}

		if ((n + 1) < m_nNumIdx)
		{//下にまだ段が続いている時
			n = (NUM_VTX_X * 2) + (((NUM_BLK_X + 2) * 2) * z);	//短くする

			pIdx[n] = pIdx[n - 1];
			pIdx[n + 1] = (WORD)((NUM_VTX_X * 2) + (z * NUM_VTX_X));
		}
	}

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//================================================
//終了
//================================================
void CObjectMesh::Uninit()
{
	//頂点バッファの解放
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの解放
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//================================================
//更新
//================================================
void CObjectMesh::Update()
{
}

//================================================
//描画
//================================================
void CObjectMesh::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	
	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CApplication::GetTexture();	//テクスチャを取得

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0, 0,
		m_nNumVtx,	//頂点数
		0,			//描画する最初の頂点インデックス
		m_nNumPol);	//描画するプリミティブ数
	
	//ライトを付ける
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//================================================
//位置を設定
//================================================
void CObjectMesh::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CObjectMesh::GetPos()
{
	return m_pos;
}

//================================================
//向きを設定
//================================================
void CObjectMesh::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//================================================
//向きを取得
//================================================
D3DXVECTOR3 CObjectMesh::GetRot()
{
	return m_rot;
}

//================================================
//頂点数を求める
//================================================
int CObjectMesh::AskVtx()
{
	// (X軸の頂点数) * (Z軸の頂点数) ---> [頂点数] = [ブロック数] + 1
	int nVtx = NUM_VTX_X * NUM_VTX_Z;

	return nVtx;	//求めた頂点数を返す
}

//================================================
//インデックス数を求める
//================================================
int CObjectMesh::AskIdx(void)
{
	// (X軸の1段目の頂点数) * (Z軸のブロック数分) + (縮退ポリゴン用の頂点数)
	int nIdx = (NUM_VTX_X * 2) * NUM_BLK_Z + ((NUM_BLK_Z - 1) * 2);

	return nIdx;	//求めたインデックス数を返す
}

//================================================
//ポリゴン数を求める
//================================================
int CObjectMesh::AskPol(void)
{
	// [(X軸のブロック数) * (Z軸のブロック数) * (ブロック一つにつきポリゴン2つ)] + (縮退ポリゴン)
	int nPol = (NUM_BLK_X * NUM_BLK_Z * 2) + ((NUM_BLK_Z - 1) * 4);

	return nPol;	//求めたポリゴン数を返す
}