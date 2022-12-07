//================================================
//
//3Dゲーム(仮)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
class CPlayer : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	static const float MOVE_SPEED;	//移動速度
	
	static const int MAX_PARTS = 2;	//最大パーツ数
	static const int NUM_KEYSET = 2;	//キーセット数

private: /* 構造体の定義 */
	struct KEY //キー要素
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
	};

	struct KEY_SET //キー情報
	{
		int nFrame;				//フレーム数
		KEY aKey[MAX_PARTS];	//キー要素
	};

public: /* 静的メンバ関数 */
	static CPlayer* Create();	//生成

private: /* 静的メンバ変数 */
	static KEY_SET m_aKeySet[NUM_KEYSET];	//キー情報

public: /* コンストラクタ・デストラクタ */
	CPlayer();
	~CPlayer() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void Move();	//移動
	void Motion();	//モーション

private: /* メンバ変数 */
	CModel* m_apModel[MAX_PARTS];	//モデルのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き

	int m_nNumKey;		//キーの総数
	int m_nCurrentKey;	//現在のキー番号
	int m_nCntMotion;	//モーションカウンター
};

#endif