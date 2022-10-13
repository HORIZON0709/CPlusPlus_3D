//================================================
//
//制作実践基礎[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "object.h"
#include "renderer.h"

//***************************
//静的メンバ変数
//***************************
CObject* CObject::m_pTop = nullptr;		//先頭のオブジェクトのポインタ
CObject* CObject::m_pCurrent = nullptr;	//現在のオブジェクトのポインタ

int CObject::m_nNumAll = 0;	//最大数

//================================================
//全ての解放
//================================================
void CObject::ReleaseAll()
{
	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULLチェック
	//		continue;
	//	}

	//	/* nullptrではない場合 */

	//	m_apObject[i]->Release();	//解放
	//}
}

//================================================
//全ての更新
//================================================
void CObject::UpdateAll()
{

	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULLチェック
	//		continue;
	//	}

	//	/* nullptrではない場合 */

	//	m_apObject[i]->Update();	//更新
	//}
}

//================================================
//全ての描画
//================================================
void CObject::DrawAll()
{
	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULLチェック
	//		continue;
	//	}

	//	/* nullptrではない場合 */

	//	m_apObject[i]->Draw();	//描画
	//}
}

//================================================
//オブジェクト情報の取得
//================================================
CObject* CObject::GetObjects(int nIdx)
{
	//return m_apObject[nIdx];
}

//================================================
//オブジェクト情報の設定
//================================================
void CObject::SetObject(int nIdx, void* pObject)
{
	//m_apObject[nIdx] = (CObject*)pObject;
}

//================================================
//コンストラクタ
//================================================
CObject::CObject()
{
	if (m_pTop == nullptr)
	{//オブジェクトが一つも無い場合
		//自身を先頭として登録
		m_pTop = this;

		//末尾に自身(先頭)を入れる
		m_pCurrent = m_pTop;
		return;
	}

	/* オブジェクトが1つ以上ある場合 */

	//末尾の次に自身を入れる
	m_pCurrent->m_pNext = this;

	//自身が一番後ろになる
	this->m_pPrev = m_pCurrent;

	//末尾に自身(先頭)を入れる
	m_pCurrent = m_pTop;

	//総数を一つ増やす
	m_nNumAll++;
}

//================================================
//デストラクタ
//================================================
CObject::~CObject()
{
}

//================================================
//解放
//================================================
void CObject::Release()
{
	if (this == nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrではない場合 */

	if (this->m_pPrev != nullptr)
	{//自身の一つ前が存在している場合
		//「自身の一つ前が持つ、一つ後の情報」に、「自身の一つ後の情報」を接続
		this->m_pPrev->m_pNext = this->m_pNext;
	}

	if (this->m_pNext != nullptr)
	{//自身の一つ後が存在している場合
		//「自身の一つ後が持つ、一つ前の情報」に、「自身の一つ前の情報」を接続
		this->m_pNext->m_pPrev = this->m_pPrev;
	}

	if (this->m_pPrev == nullptr)
	{//自身の一つ前に何も無い場合(自身が先頭)
		//先頭に、自身の一つ後の情報を設定
		m_pTop = this->m_pNext;
	}

	if (this->m_pNext == nullptr)
	{//自身の一つ後に何も無い場合(自身が末尾)
		//末尾に、自身の一つ前の情報を設定
		m_pCurrent = this->m_pPrev;  
	}

	//終了
	this->Uninit();

	//メモリの解放
	delete this;

	//総数を一つ減らす
	m_nNumAll--;
}

//================================================
//タイプの設定
//================================================
void CObject::SetObjType(const CObject::OBJ_TYPE &type)
{
	objType = type;
}

//================================================
//タイプの取得
//================================================
CObject::OBJ_TYPE CObject::GetObjType()
{
	return objType;
}