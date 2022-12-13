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
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget)
{
	D3DXVECTOR3 ownMax = D3DXVECTOR3(	//自身の判定の最大値
		posOwn.x + sizeMaxOwn.x,
		posOwn.y + sizeMaxOwn.y,
		posOwn.z + sizeMaxOwn.z
		);

	D3DXVECTOR3 ownMin = D3DXVECTOR3(	//自身の判定の最小値
		posOwn.x + sizeMinOwn.x,
		posOwn.y + sizeMinOwn.y,
		posOwn.z + sizeMinOwn.z
	);

	D3DXVECTOR3 targetMax = D3DXVECTOR3(	//対象の判定の最大値
		posTarget.x + sizeMaxTarget.x,
		posTarget.y + sizeMaxTarget.y,
		posTarget.z + sizeMaxTarget.z
	);

	D3DXVECTOR3 targetMin = D3DXVECTOR3(	//対象の判定の最小値
		posTarget.x + sizeMinTarget.x,
		posTarget.y + sizeMinTarget.y,
		posTarget.z + sizeMinTarget.z
	);

	{//********** X軸 **********//

		bool bRightAndLeft = (ownMax.x > targetMin.x);
		bool bLeftAndRight = (ownMin.x < targetMax.x);

		if (bRightAndLeft || bLeftAndRight)
		{
			return true;
		}
	}

	{//********** Y軸 **********//

		bool bTopAndBottom = (ownMax.y > targetMin.y);
		bool bBottomAndTop = (ownMin.y < targetMax.y);

		if (bTopAndBottom || bBottomAndTop)
		{
			return true;
		}
	}

	{//********** Z軸 **********//

		bool bFrontAndBack = (ownMax.z > targetMin.z);
		bool bBackAndFront = (ownMin.z < targetMax.z);

		if (bFrontAndBack || bBackAndFront)
		{
			return true;
		}
	}

	return false;
}