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
#include "objectX.h"

//***************************
//前方宣言
//***************************
class CLine;

//***************************
//アイテムクラスの定義
//***************************
class CItem : public CObjectX
{/* CObjectXの派生クラス */
private: /* 定数の定義 */
	static const float ROTATION_SPEED;	//回転速度

	static const int MAX_LINE = 12;	//ラインの最大数

public: /* 静的メンバ関数 */
	static CItem* Create(char* pFileName);	//生成

public: /* 静的メンバ変巣 */
	static CLine* m_apLine[MAX_LINE];	//ラインのポインタ

public: /* コンストラクタ・デストラクタ */
	CItem();
	~CItem() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* メンバ関数 */
	void SetLines();	//ラインの設定まとめ

private: /* メンバ変数 */
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き
};

#endif