//================================================
//
//3Dゲーム(仮)[objectX.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//***************************
//インクルード
//***************************
#include "object.h"

#include <stdio.h>

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

public: /* Move */
	/*
		移動量を設定
		const D3DXVECTOR3 &move ---> 任意の移動量
	*/
	void SetMove(const D3DXVECTOR3 &move);

	//移動量を取得
	D3DXVECTOR3 GetMove();

public: /* Rot */
	/*
		向きを設定
		const D3DXVECTOR3 &rot ---> 任意の向き
	*/
	void Setrot(const D3DXVECTOR3 &rot);

	//向きを取得
	D3DXVECTOR3 GetRot();

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_rot;	//向き
	
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
};

#endif