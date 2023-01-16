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
public: /* 定数の定義 */
	static const char* s_apFileName[];	//ファイルパス
private:
	static const int MAX_WORD;		//最大文字数
	static const int NUM_PARTS = 2;	//パーツ数

	static const char* FILE_NAME;	//ファイル名

private: /* 構造体の定義 */
	struct PARTS_SET	//パーツ情報
	{
		int nIndex;			//インデックス数
		int nParent;		//親パーツ番号
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
	};

	struct CHARACTER_SET	//キャラクター情報
	{
		int nNumParts;					//パーツ数
		PARTS_SET aPartsSet[NUM_PARTS];	//パーツ情報
	};

public: /* 静的メンバ関数 */
	static CModel* Create();	//生成

public: /* 静的メンバ変数 */
	static CHARACTER_SET m_characterSet;	//キャラクター情報

public: /* コンストラクタ・デストラクタ */
	CModel();
	~CModel();

public: /* メンバ関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	D3DXMATRIX GetMtxWorld();	//ワールドマトリックスの取得

public: /* vtx */
	D3DXVECTOR3 GetVtxMax();	//頂点の最大値を取得
	D3DXVECTOR3 GetVtxMin();	//頂点の最小値を取得

private:
	void DrawShadow();	//影の描画
	void Load();		//読み込み

	/*
		キャラクター設定
		FILE* pFile ---> ファイルポインタ
		char aText[] ---> テキスト格納用
	*/
	void Set_CharacterSet(FILE* pFile, char aText[]);

	/*
		パーツ設定
		FILE* pFile ---> ファイルポインタ
		char aText[] ---> テキスト格納用
	*/
	void Set_PartsSet(FILE* pFile, char aText[]);

private: /* メンバ変数 */
	D3DXVECTOR3 m_vtxMax;	//最大値
	D3DXVECTOR3 m_vtxMin;	//最小値

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報のポインタ

	DWORD m_numMat;	//マテリアル情報の数

	int m_nNumModel;	//モデル数
};

#endif