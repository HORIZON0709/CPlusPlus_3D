//================================================
//
//制作実践基礎[model.h]
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
private: /* 定数の定義 */
	static const int MAX_WORD;		//最大文字数
	static const char* FILE_NAME;	//読み込むファイル名

public: /* 静的メンバ関数 */
	static CModel* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CModel();
	~CModel();

public: /* メンバ関数 */
	HRESULT Init(const char* aFileName);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
 
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

private:
	void DrawShadow();	//影の描画

	void Load(const char* aFileName);	//読み込み

	/*
		設定
		FILE *pFile ---> ファイルポインタ
		char aText[] ---> テキスト格納用
	*/
	void Set(FILE *pFile, char aText[]);

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_vtxMax;	//最大値
	D3DXVECTOR3 m_vtxMin;	//最小値

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報のポインタ

	DWORD m_numMat;	//マテリアル情報の数

	char* m_pFileName;	//ファイル名

	int m_nIdx;	//インデックス数

	CModel* m_pParent;	//親モデルへのポインタ
};

#endif