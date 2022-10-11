//================================================
//
//制作実践基礎[result.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//***************************
//インクルード
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CBg;

//***************************
//リザルトクラスの定義
//***************************
class CResult : public CMode
{/* CModeの派生クラス */
public: /* コンストラクタ・デストラクタ */
	CResult();
	~CResult() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* 静的メンバ変数 */
	static CBg* m_pBg;	//背景

private: /* メンバ変数 */
	bool m_bFadeOut;	//暗転したかどうか
};
#endif