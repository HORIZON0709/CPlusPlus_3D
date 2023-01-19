//================================================
//
//3Dゲーム(仮)[stage.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//ステージクラスの定義
//***************************
class CStage
{/* 基本クラス */
private: /* 定数の定義 */
	static const int MAX_WORD;	//最大文字数

	static const char* FILE_NAME;	//ファイル名

public: /* 静的メンバ関数 */
	static CStage* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CStage();
	~CStage();

public: /* オーバーライド関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private:
	void Load();	//読み込み

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
};

#endif