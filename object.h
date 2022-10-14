//================================================
//
//制作実践基礎[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//オブジェクトクラスの定義
//***************************
class CObject
{/* 基本クラス */
public: /* 列挙型の定義 */
	enum OBJ_TYPE
	{/* オブジェクトの種類 */
		NONE = -1,
		PLAYER = 0,	//プレイヤー
		ENEMY,		//敵
		BULLET,		//弾
		EXPLOSION,	//爆発
		BG,			//背景
		ITEM,		//アイテム
		SCORE,		//スコア
		NUMBER,		//ナンバー
		MAX
	};

public: /* 静的メンバ関数 */
	static void ReleaseAll();	//全ての解放
	static void UpdateAll();	//全ての更新
	static void DrawAll();		//全ての描画

public: /* コンストラクタ・デストラクタ */
	CObject();
	virtual ~CObject();

public: /* 純粋仮想関数 */
	virtual HRESULT Init() = 0;	//初期化
	virtual void Uninit() = 0;	//終了
	virtual void Update() = 0;	//更新
	virtual void Draw() = 0;	//描画

public: /* メンバ関数 */
	void Release();	//解放

public:	/* ObjType */
	/*
		タイプの設定
		const OBJ_TYPE &type ---> 任意のタイプ
	*/
	void SetObjType(const OBJ_TYPE &type);

	//タイプの取得
	OBJ_TYPE GetObjType();

private: /* 静的メンバ変数 */
	static CObject* m_pTop;		//先頭のオブジェクトのポインタ
	static CObject* m_pCurrent;	//現在(一番後ろ)のオブジェクトのポインタ

	static int m_nNumAll;	//オブジェクトの総数
	
private: /* メンバ変数 */
	CObject* m_pPrev;	//前のオブジェクトへのポインタ
	CObject* m_pNext;	//次のオブジェクトへのポインタ

	CObject::OBJ_TYPE objType;	//種類

	bool m_bDeath;	//死亡フラグ
};

#endif