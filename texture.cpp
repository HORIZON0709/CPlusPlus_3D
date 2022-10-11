//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// Author : KIshimoto Eiji
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "renderer.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::s_FileName[] =
{// テクスチャのパス
	/* プレイヤー */
	"data/TEXTURE/player000.jpg",	//モチモチの余さん(仮)

	/* 弾 */
	"data/TEXTURE/bullet000.png",	//桜のサークル(仮)
	"data/TEXTURE/bullet001.png",	//スラックのアイコン(仮)
	"data/TEXTURE/bullet002.png",	//配布の弾(仮)
	"data/TEXTURE/bullet003.png",	//気弾(青白)
	"data/TEXTURE/bullet004.png",	//気弾(赤黒)
	"data/TEXTURE/bullet005.png",	//火球(赤黒)

	/* 爆発 */
	"data/TEXTURE/explosion000.png",	//配布の爆発アニメーション画像
	"data/TEXTURE/explosion001.png",	//爆発アニメーション画像(分割数 : 縦8 * 横5)
	"data/TEXTURE/explosion002.png",	//爆発アニメーション画像(分割数 : 縦10 * 横5)

	/* 敵 */
	"data/TEXTURE/enemy000.png",	//全部違うネタ画像のやつ(仮)
	"data/TEXTURE/enemy001.png",	//配布のカニ(仮)
	"data/TEXTURE/enemy002.png",	//ボス
	"data/TEXTURE/enemy003.png",	//髑髏

	/* 背景 */
	"data/TEXTURE/bg000.jpeg",	//何かユニバース(仮)
	"data/TEXTURE/bg001.png",	//仮背景：タイトル
	"data/TEXTURE/bg003.png",	//仮背景：リザルト

	/* アイテム */
	"data/TEXTURE/item000.png",	//三角形(仮)
	"data/TEXTURE/item001.png",	//通常弾に変更
	"data/TEXTURE/item002.png",	//二連弾に変更
	"data/TEXTURE/item003.png",	//三連各散弾に変更

	/* ナンバー */
	"data/TEXTURE/number000.png"	//0～9の数字(横並び)
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < MAX);

	// 読み込み
	Load(inTexture);

	return s_pTexture[inTexture];
}
