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
//前方宣言
//***************************
class CModel;

//***************************
//オブジェクトクラスの定義
//***************************
class CObjectX : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	static const float ROTATION_SPEED;	//回転速度
	static const float MOVE_SPEED;		//移動速度

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

public: /* bool判定系 */
	/*
		移動の有無を設定
		bool bMove ---> 移動するかしないか
	*/
	void SetFlagOfMove(bool bMove);

	/*
		回転の有無を設定
		bool bRotation ---> 回転するかどうか
	*/
	void SetFlagOfRotation(bool bRotation);

private: /* メンバ関数 */
	void Move();				//移動
	void RotationQuaternion();

private: /* メンバ変数 */
	CModel* m_pModel;	//モデルのポインタ

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_vec;		//方向ベクトル

	D3DXQUATERNION m_quaternion;	//クォータニオン

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	bool m_bPressKey;	//キー押下中かどうか
	bool m_bMove;		//移動するかどうか
	bool m_bRotation;	//回転するかどうか
};

#endif