//================================================
//
//制作実践基礎[player.h]
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

public: /* 静的メンバ関数 */
	static CPlayer* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CPlayer();
	~CPlayer() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void Move();	//移動量

private: /* メンバ変数 */
	CModel* m_pModel;	//モデルのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_rot;	//向き
};

#endif