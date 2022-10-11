//================================================
//
//制作実践基礎[objectX.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//オブジェクトクラスの定義
//***************************
class CObjectX : public CObject
{/* CObjectの派生クラス */
public: /* 静的メンバ関数 */
	static CObjectX* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CObjectX();
	~CObjectX() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* Pos */
	/*
		位置を設定
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//位置を取得
	D3DXVECTOR3 GetPos();

public: /* Collision */
	/*
		当たり判定
		OBJ_TYPE myType ---> 自身のタイプ
		OBJ_TYPE targetType ---> 判定を取る対象のタイプ
	*/
	bool Collision(OBJ_TYPE myType, OBJ_TYPE targetType);

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き
	D3DXVECTOR3 m_vtxMax;	//最大値
	D3DXVECTOR3 m_vtxMin;	//最小値

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報のポインタ

	DWORD m_numMat;	//マテリアル情報の数

	int m_nIdxUse;	//使用するモデルのインデックス数
};

#endif