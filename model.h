//================================================
//
//3Dゲーム(仮)[model.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//プレイヤークラスの定義
//***************************
class CModel
{/* 基本クラス */
public: /* 列挙型の定義 */
	enum XFILE //Xファイルのパス
	{
		NONE = -1,

		/* デバッグ */
		chair = 0,				//椅子
		table,					//机
		Stage_Debug_Obstade,	//ステージデバッグ用の障害物(立方体)
		Coin01,					//コイン
		Fish_Body,				//魚の胴体
		Fish_Tail,				//魚の尾ひれ

		MAX
	};

public: /* 定数の定義 */
	static const char* s_apFileName[];	//ファイルパス
private:
	static const int MAX_WORD;		//最大文字数

public: /* 静的メンバ関数 */
	/*
		生成
		XFILE xFile ---> 読み込むXファイル
	*/
	static CModel* Create(XFILE xFile);

public: /* コンストラクタ・デストラクタ */
	CModel();
	~CModel();

public: /* メンバ関数 */
	HRESULT Init(XFILE xFile);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
 
	void LoadAll();			//全ての読み込み
	void Load(XFILE xFile);	//指定の読み込み

	/*
		親の設定
		CModel* pModel ---> モデルのポインタ
	*/
	void SetParent(CModel* pModel);

	D3DXMATRIX GetMtxWorld();	//ワールドマトリックスの取得
public: /* Pos */
	/*
		位置を設定
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//位置を取得
	D3DXVECTOR3 GetPos();

public: /* Rot */
	/*
		向きを設定
		const D3DXVECTOR3 &rot ---> 任意の向き
	*/
	void SetRot(const D3DXVECTOR3 &rot);

	//向きを取得
	D3DXVECTOR3 GetRot();

public: /* vtx */
	D3DXVECTOR3 GetVtxMax();	//頂点の最大値を取得
	D3DXVECTOR3 GetVtxMin();	//頂点の最小値を取得

private:
	void DrawShadow();	//影の描画

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_vtxMax;	//最大値
	D3DXVECTOR3 m_vtxMin;	//最小値

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報のポインタ

	DWORD m_numMat;	//マテリアル情報の数

	int m_nIdx;	//インデックス数

	CModel* m_pParent;	//親モデルへのポインタ
};

#endif