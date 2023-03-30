//================================================
//
//3Dゲーム(仮)[panel.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PANEL_H_
#define _PANEL_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CObject2D;

//***************************
//プレイヤークラスの定義
//***************************
class CPanel
{/* 基本クラス */
private: /* 定数の定義 */

public: /* 静的メンバ関数 */
	static CPanel* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CPanel();
	~CPanel();

public: /* メンバ関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private:

private: /* メンバ変数 */
	CObject2D* m_pBg;			//背景
	CObject2D* m_apPanel[8];	//ステージ数分のポリゴン

	bool m_bPanel;
	
};

#endif