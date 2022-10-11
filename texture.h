//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// Author : KIshimoto Eiji
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		NONE = -1,	//使用しない

		/* プレイヤー */
		player000 = 0,	//モチモチの余さん(仮)

		/* 弾 */
		bullet000,	//桜のサークル(仮)
		bullet001,	//スラックのアイコン(仮)
		bullet002,	//配布の弾(仮)
		bullet003,	//気弾(青白)
		bullet004,	//気弾(赤黒)
		bullet005,	//火球(赤黒)

		/* 爆発 */
		explosion000,	//配布の爆発アニメーション画像(仮)
		explosion001,	//爆発アニメーション画像(分割数 : 縦8 * 横5)
		explosion002,	//爆発アニメーション画像(分割数 : 縦10 * 横5)

		/* 敵 */
		enemy000,	//全部違うネタ画像のやつ(仮)
		enemy001,	//配布のカニ(仮)
		enemy002,	//ボス
		enemy003,	//髑髏

		/* 背景 */
		bg000,	//何かユニバース(仮)
		bg001,	//仮背景：タイトル
		bg002,	//仮背景：リザルト

		/* アイテム */
		item000,	//三角形(仮)
		item001,	//通常弾に変更(赤)
		item002,	//二連弾に変更(緑)
		item003,	//三連各散弾に変更(青)

		/* ナンバー */
		number000,	//0～9の数字(横並び)

		MAX
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
