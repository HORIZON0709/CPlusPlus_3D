//================================================
//
//3Dゲーム(仮)[item.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//前方宣言
//***************************
class CModel;

//***************************
//アイテムクラスの定義
//***************************
class CItem : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	static const float ROTATION_SPEED;	//回転速度

public: /* 静的メンバ関数 */
	static CItem* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CItem();
	~CItem() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	CModel* m_pModel;	//モデルのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き

	bool m_bPressKey;	//キー押下中かどうか
};

#endif