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

public: /* 定数の定義 */
	static const int MAX_OBJECT = 128;		//ポリゴンの最大数
	//static const int MAX_NUM_PRIORITY = 5;	//優先順位の最大数

public: /* 静的メンバ関数 */
	static void ReleaseAll();	//全ての解放
	static void UpdateAll();	//全ての更新
	static void DrawAll();		//全ての描画

	/*
		オブジェクト情報の取得
		const int &nIdx ---> インデックス数
	*/
	static CObject* GetObjects(const int &nIdx);

	/*
		オブジェクト情報の設定
		const int &nIdx ---> インデックス数
		void* pObject ---> 任意の型のオブジェクト
	*/
	static void SetObject(const int &nIdx, void* pObject);

public: /* コンストラクタ・デストラクタ */
	CObject();
	//explicit CObject(const int &nPriority = 3);	//デフォルト引数(引数に値を設定しない場合は「3」になる)
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

	/*
		タイプの取得
	*/
	OBJ_TYPE GetObjType();

private: /* 静的メンバ変数 */
	static CObject* m_apObject[MAX_OBJECT];	//ポインタ
	//static CObject* m_apObject[MAX_NUM_PRIORITY][MAX_OBJECT];	//ポインタ(優先順位付き)

	static int m_nNumAll;					//最大数
	
private: /* メンバ変数 */
	int m_nID;					//格納先の番号
	CObject::OBJ_TYPE objType;	//種類
};

#endif