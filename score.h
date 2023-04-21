//================================================
//
//制作実践基礎[score.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//前方宣言
//***************************
class CNumber;

//***************************
//スコアクラスの定義
//***************************
class CScore : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	static const int MAX_DIGIT = 8;	//最大桁数

public: /* 静的メンバ関数 */
	static CScore* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CScore();
	~CScore()override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* メンバ関数 */
	/*
		スコアのセット
		int nScore ---> スコア
	*/
	void SetScore(int nScore);

	/*
		スコア加算
		int nValue ---> 加算する値
	*/
	void AddScore(int nValue);

	int GetCurrentScore();	//現在のスコアの取得
private:
	void ChangeTexUV();	//現在のスコアに応じたテクスチャ座標の変更

private: /* メンバ変数 */
	CNumber* m_apNumber[MAX_DIGIT];	//桁数分用意
	int m_nScore;					//スコア
};
#endif