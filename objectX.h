//================================================
//
//3Dゲーム(仮)[objectX.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//***************************
//インクルード
//***************************
#include "object.h"

#include <stdio.h>

//***************************
//前方宣言
//***************************
class CModel;

//***************************
//オブジェクトクラスの定義
//***************************
class CObjectX : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	static const float MOVE_SPEED;	//移動速度

	static const int MAX_WORD;		//最大文字数

	static const char* FILE_NAME;	//読み込むファイル名

public: /* 静的メンバ関数 */
	static CObjectX* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CObjectX();
	~CObjectX() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* Pos */
	/*
		位置を設定
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//位置を取得
	D3DXVECTOR3 GetPos();

public: /* Move */
	/*
		移動量を設定
		const D3DXVECTOR3 &move ---> 任意の移動量
	*/
	void SetMove(const D3DXVECTOR3 &move);

	//移動量を取得
	D3DXVECTOR3 GetMove();

public: /* Collision */
	/*
		当たり判定
		OBJ_TYPE myType ---> 自身のタイプ
		OBJ_TYPE targetType ---> 判定を取る対象のタイプ
	*/
	//bool Collision(OBJ_TYPE myType, OBJ_TYPE targetType);

private: /* メンバ関数 */
	void Move();		//移動
	void DrawShadow();	//影の描画
	void Load();		//読み込み

	/*
		設定
		FILE *pFile ---> ファイルポインタ
		char aText[] ---> テキスト格納用
	*/
	void Set(FILE *pFile, char aText[]);

private: /* メンバ変数 */
	CModel* m_pModel;	//モデルのポインタ

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//現在の向き
	D3DXVECTOR3 m_rotDest;	//目的の向き
	D3DXVECTOR3 m_vtxMax;	//最大値
	D3DXVECTOR3 m_vtxMin;	//最小値

	D3DXQUATERNION m_quaternion;	//クォータニオン

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPD3DXMESH m_pMesh;			//メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報のポインタ

	DWORD m_numMat;	//マテリアル情報の数

	char* m_pFileName;	//ファイル名

	int m_nIdx;	//インデックス数
};

#endif