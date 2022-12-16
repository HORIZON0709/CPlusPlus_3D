//================================================
//
//3Dゲーム(仮)[utility.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//プロトタイプ宣言
//***************************
/*
	角度の正規化
	float *pAngle ---> 角度
*/
void NormalizeAngle(float* pAngle); 

/*
	当たり判定(モデル同士)
	D3DXVECTOR3* pPosOwn ---> 自身の現在の位置
	const D3DXVECTOR3 &posOldOwn ---> 自身の前回の位置
	const D3DXVECTOR3 &posTarget ---> 対象の位置
	const D3DXVECTOR3 &sizeMaxOwn ---> 自身のサイズの最大値
	const D3DXVECTOR3 &sizeMinOwn ---> 自身のサイズの最小値
	const D3DXVECTOR3 &sizeMaxTarget ---> 対象のサイズの最大値
	const D3DXVECTOR3 &sizeMinTarget ---> 対象のサイズの最小値
*/
bool CollisionModel(
	D3DXVECTOR3* pPosOwn,
	const D3DXVECTOR3 &posOldOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget);

#endif