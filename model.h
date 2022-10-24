//================================================
//
//制作実践基礎[model.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//プレイヤークラスの定義
//***************************
class CModel
{/* 基本クラス */
private: /* 定数の定義 */

public: /* 静的メンバ関数 */
	static CModel* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CModel();
	~CModel();

public: /* メンバ関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
 
	/*
		親の設定
		CModel* pModel ---> モデルのポインタ
	*/
	void SetParent(CModel* pModel);

private: /* メンバ変数 */
	CModel* m_pParent;	//親モデルのポインタ
};

#endif