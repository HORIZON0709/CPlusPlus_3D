//================================================
//
//3Dゲーム(仮)[utility.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "utility.h"

//================================================
//角度の正規化
//================================================
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{//角度が[3.14]以上の場合
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{//角度が[-3.14]以下の場合
		*pAngle += D3DX_PI * 2.0f;
	}
}

//================================================
//当たり判定(モデル同士)
//================================================
bool CollisionModel(
	const D3DXVECTOR3 &posOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeOwn,
	const D3DXVECTOR3 &sizeTarget)
{
	

	return false;
}