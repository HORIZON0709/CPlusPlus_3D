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
//前方宣言
//***************************
class CObject3D;
class CObjectX;

//***************************
//ステージクラスの定義
//***************************
class CStage
{/* 基本クラス */
private: /* 定数の定義 */
	static const int NUM_WALL = 4;		//壁の数
	static const int MAX_MODEL = 16;	//モデルの最大数

	static const int MAX_WORD;	//最大文字数

	static const char* FILE_NAME;	//ファイル名

private: /* 構造体の定義 */
	struct MODELSET_INFO	//モデル配置に必要な情報
	{
		char* pFileName;	//ファイル名
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
	};

public: /* 静的メンバ関数 */
	/*
		生成
		char* pFileName ---> ファイル名
	*/
	static CStage* Create(char* pFileName);	//生成

public: /* コンストラクタ・デストラクタ */
	CStage();
	~CStage();

public: /* オーバーライド関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新

private:
	void Load();	//読み込み

	/*
		モデルセット設定
		FILE* pFile ---> ファイルポインタ
		char aText[] ---> テキスト格納用
	*/
	void Set_ModelSet(FILE* pFile, char aText[]);

private: /* メンバ変数 */
	MODELSET_INFO m_aModelSetInfo[MAX_MODEL];	//モデル設置に必要な情報

	CObject3D* m_pFloar;			//3Dポリゴンの床のポインタ
	CObject3D* m_apWall[NUM_WALL];	//3Dポリゴンの壁(四方)のポインタ
	CObjectX* m_apModel[MAX_MODEL];	//モデルのポインタ

	int m_nNumModel;	//モデル数
};

#endif