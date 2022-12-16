//================================================
//
//3Dゲーム(仮)[gimmick.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//前方宣言
//***************************
class CModel;

//***************************
//プレイヤークラスの定義
//***************************
class CGimmick : public CObject
{/* CObjectXの派生クラス */
private: /* 定数の定義 */
	static const float MOVE_SPEED;		//移動速度
	static const float ROT_SMOOTHNESS;	//回転の滑らかさ
	static const float ROTATION_SPEED;	//回転速度

public: /* 静的メンバ関数 */
	static CGimmick* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CGimmick();
	~CGimmick() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void Move();				//移動
	void RotationQuaternion();	//クォータニオンによる回転

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

public: /* Pos */
	/*
		位置を設定
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//位置を取得
	D3DXVECTOR3 GetPos();

public: /* vtx */
	D3DXVECTOR3 GetVtxMax();	//頂点の最大値を取得
	D3DXVECTOR3 GetVtxMin();	//頂点の最小値を取得

private: /* メンバ変数 */
	CModel* m_pModel;	//モデルのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_vec;		//方向ベクトル
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き
	D3DXVECTOR3 m_vtxMax;	//頂点の最大値
	D3DXVECTOR3 m_vtxMin;	//頂点の最小値

	D3DXQUATERNION m_quaternion;	//クォータニオン

	bool m_bPressKey;	//キー押下中かどうか
	bool m_bMove;		//移動するかどうか
	bool m_bRotation;	//回転するかどうか
};

#endif