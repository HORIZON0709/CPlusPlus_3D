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
#include "objectX.h"

//***************************
//プレイヤークラスの定義
//***************************
class CPlayer : public CObjectX
{/* CObjectXの派生クラス */
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

private: /* メンバ変数 */
	
};

#endif