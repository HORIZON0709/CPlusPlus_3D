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

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CObjectX::MOVE_SPEED = 2.0f;	//移動速度

const int CObjectX::MAX_WORD = 256;		//最大文字数

const char* CObjectX::FILE_NAME = "data/TEXT/model.txt";	//読み込むファイル名

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
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_pFileName("\0"),
	m_nIdx(0)
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
	//メンバ変数の初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_numMat = 0;
	m_pFileName = "\0";
	m_nIdx = 0;
	
	//読み込み
	Load();

	//頂点数の取得
	int nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	BYTE *pVtxBuff;	//頂点バッファへのポインタ

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int j = 0; j < nNumVtx; j++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		/* 頂点座標を比較し、モデルの最大値・最小値を取得 */

		//***** 最大 *****//

		if (vtx.x > m_vtxMax.x)
		{//X
			m_vtxMax.x = vtx.x;
		}

		if (vtx.y > m_vtxMax.y)
		{//Y
			m_vtxMax.y = vtx.y;
		}

		if (vtx.z > m_vtxMax.z)
		{//Z
			m_vtxMax.z = vtx.z;
		}

		//***** 最小 *****//

		if (vtx.x < m_vtxMin.x)
		{//X
			m_vtxMin.x = vtx.x;
		}

		if (vtx.y < m_vtxMin.y)
		{//Y
			m_vtxMin.y = vtx.y;
		}

		if (vtx.z < m_vtxMin.z)
		{//Z
			m_vtxMin.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//================================================
//終了
//================================================
void CObjectX::Uninit()
{
	//メッシュの解放
	if (m_pMesh != nullptr)
	{
		m_pMesh = nullptr;
	}

	//マテリアルの解放
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat = nullptr;
	}
}

//================================================
//更新
//================================================
void CObjectX::Update()
{
	//移動
	Move();

	D3DXVECTOR3 axis;					//回転軸
	D3DXVECTOR3 inverseVec = -m_move;	//move値を反対にする

	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//外積で回転軸を算出
	D3DXVec3Cross(&axis, &inverseVec, &vecY);
	
	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//クオータニオン計算用

	//回転軸と回転角度を指定
	D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);
	
	// クオータニオンを適用
	m_quaternion *= quaternion;
	
	// クオータニオンのノーマライズ
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量を0にする
}

//================================================
//描画
//================================================
void CObjectX::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

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

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを保持
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int i = 0; i < (int)m_numMat; i++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(i);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
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
//移動
//================================================
void CObjectX::Move()
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

//================================================
//影の描画
//================================================
void CObjectX::DrawShadow()
{
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, nor;

	D3DMATERIAL9 matDef;	//現在のマテリアル保存用
	D3DXMATERIAL* pMat;		//マテリアルデータへのポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	//ライトの方向を設定
	vecLight = D3DXVECTOR4(-1.0f, 0.8f, 0.0f, 0.0f);

	//位置を設定
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線を設定
	nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//法線と平面の1点から平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &nor);

	//ライトと平面から影行列を作成
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//ワールドマトリックスとシャドウマトリックスを掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを保持
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	D3DMATERIAL9 mat = pMat->MatD3D;

	//色を黒に設定
	mat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	mat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//マテリアルの設定
	pDevice->SetMaterial(&mat);

	for (int i = 0; i < (int)m_numMat; i++)
	{
		//モデルパーツの描画
		m_pMesh->DrawSubset(i);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//================================================
//読み込み
//================================================
void CObjectX::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ファイルを開く
	FILE *pFile = fopen(FILE_NAME, "r");
	
	if (pFile == nullptr)
	{//ファイルが開けなかった場合
		assert(false);
	}

	/* ファイルが開けた場合 */

	char aText[MAX_WORD];	//テキスト格納用

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//テキストの最初の行を読み込むまで繰り返す
		fgets(aText, MAX_WORD, pFile);		//1行丸ごと読み込む
	}

	while (strcmp(&aText[0], "END_SCRIPT") != 0)
	{//テキストの最終行を読み込むまで繰り返す
		//文字を読み込む
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//ブロックコメント
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//コメント
			//1行全て読み込む
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
		{//ファイル名
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			char aFileName[MAX_WORD];	//ファイル名読み込み用

			//Xファイルのパスを読み込む
			fscanf(pFile, "%s", &aFileName[0]);

			//読み込んだファイル名を代入
			m_pFileName = &aFileName[0];
		}
		else if (strcmp(&aText[0], "MODELSET") == 0)
		{//モデルのセット
			//設定
			Set(pFile, &aText[0]);
		}
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		m_pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	//ファイルを閉じる
	fclose(pFile);
}

//================================================
//設定
//================================================
void CObjectX::Set(FILE *pFile, char aText[])
{
	while (strcmp(&aText[0], "END_MODELSET") != 0)
	{//モデルのセットが終わるまで繰り返す
		//文字を読み込む
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//ブロックコメント
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//コメント
			//1行全て読み込む
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "INDEX") == 0)
		{//インデックス数
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//インデックス数を読み込む
			fscanf(pFile, "%d", &m_nIdx);
		}
		else if (strcmp(&aText[0], "POS") == 0)
		{//位置
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//位置を読み込む
			fscanf(pFile, "%f", &m_pos.x);	//X軸
			fscanf(pFile, "%f", &m_pos.y);	//Y軸
			fscanf(pFile, "%f", &m_pos.z);	//Z軸
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//向き
			//「＝」を読み込む
			fscanf(pFile, "%s", &aText[0]);

			//向きを読み込む
			fscanf(pFile, "%f", &m_rot.x);	//X軸
			fscanf(pFile, "%f", &m_rot.y);	//Y軸
			fscanf(pFile, "%f", &m_rot.z);	//Z軸
		}
	}
}