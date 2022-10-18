//================================================
//
//制作実践基礎[game.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

//***************************
//インクルード
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CCamera;
class CLight;
class CPolygon3D;
class CPlayer;
class CObjectMesh;

//***************************
//ゲームクラスの定義
//***************************
class CGame : public CMode
{/* CModeの派生クラス */
private: /* 定数の定義 */
	static const int INTERVAL_STRAIGHT;			//直線敵の生成間隔
	static const int FADE_INTERVAL_GAMEOVER;	//フェードまでの間隔(ゲームオーバー時)
	static const int FADE_INTERVAL_GAMECLEAR;	//フェードまでの間隔(ゲームクリア時)

public: /* 静的メンバ関数 */
	static CCamera* GetCamera();		//カメラの情報を取得
	static CLight* GetLight();			//ライトの情報を取得
	static CPolygon3D* GetPolygon3D();	//3Dポリゴンの情報を取得
	static CPlayer* GetPlayer();		//プレイヤーの情報を取得
	static CObjectMesh* GetMesh();		//メッシュの情報を取得
	
public: /* コンストラクタ・デストラクタ */
	CGame();
	~CGame() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画

private: /* 静的メンバ変数 */
	static CCamera* m_pCamera;			//カメラ
	static CLight* m_pLight;			//ライト
	static CPolygon3D* m_pPolygon3D;	//3Dポリゴン
	static CPlayer* m_pPlayer;			//プレイヤー
	static CObjectMesh* m_pMesh;		//メッシュ
	
private: /* メンバ変数 */
	int m_nCntIntervalFade;	//フェードするまでの間隔カウント用

	bool m_bFadeOut;	//暗転したかどうか
	bool m_bWireFrame;	//ワイヤーフレーム表示切り替え
};
#endif