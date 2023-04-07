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

#include "stage.h"

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
	static const int MAX_PANEL = 8;	//パネルの最大数
	static const int GRID_X = 3;	//マス目の数(X軸)
	static const int GRID_Y = 3;	//マス目の数(Y軸)

	static const float PANEL_SIZE;	//パネルのサイズ

private: /* 構造体の定義 */
	struct PANEL_INFO	//パネル情報
	{
		CObject2D* m_pPanel;	//パネルのポインタ
		D3DXVECTOR3 pos;		//パネルの位置
		CStage::STAGE stage;	//ステージ
	};

public: /* 静的メンバ関数 */
	static CPanel* Create();	//生成

private: /* 静的メンバ変数 */
	static PANEL_INFO m_aPanelInfo[MAX_PANEL];	//パネル情報

public: /* コンストラクタ・デストラクタ */
	CPanel();
	~CPanel();

public: /* メンバ関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	bool GetIsPanel();	//パネル操作中かどうかを取得

private:
	void SelectPanel();	//パネルの選択

	/*
		パネルのサイズの設定
		bool bIsSelect ---> 選択中かどうか
	*/
	void SetPanelSize(bool bIsSelect);

	/*
		選択用の色の設定
		bool bIsSelect ---> 選択中かどうか
	*/
	void SetSelectColor(bool bIsSelect);

private: /* メンバ変数 */
	CObject2D* m_pBg;		//背景
	CObject2D* m_pSelect;	//選択用

	D3DXVECTOR3 m_aPos[GRID_Y][GRID_X];	//パネルの位置

	int m_nPosX;	//位置(X軸)
	int m_nPosY;	//位置(Y軸)

	bool m_bPanel;		//パネル操作中かどうか
	bool m_bIsSelect;	//選択中かどうか
};

#endif