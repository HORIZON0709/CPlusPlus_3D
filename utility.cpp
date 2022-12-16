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
	D3DXVECTOR3* pPosOwn,
	const D3DXVECTOR3 &posOldOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget)
{
	//********** 説明用変数 **********//

	//自身の判定の最大値・最小値(現在の位置)
	D3DXVECTOR3 ownMax = (*pPosOwn + sizeMaxOwn);
	D3DXVECTOR3 ownMin = (*pPosOwn + sizeMinOwn);

	//自身の判定の最大値・最小値(前回の位置)
	D3DXVECTOR3 oldOwnMax = (posOldOwn + sizeMaxOwn);
	D3DXVECTOR3 oldOwnMin = (posOldOwn + sizeMinOwn);

	//対象の判定の最大値・最小値
	D3DXVECTOR3 targetMax = (posTarget + sizeMaxTarget);
	D3DXVECTOR3 targetMin = (posTarget + sizeMinTarget);

	//X軸の判定式
	bool bRightToLeft = (ownMin.x < targetMax.x);	//右から左へ
	bool bLeftToRight = (ownMax.x > targetMin.x);	//左から右へ

	//Y軸の判定式
	bool bTopToBottom = (ownMin.y < targetMax.y);	//上から下へ
	bool bBottomToTop = (ownMax.y > targetMin.y);	//下から上へ

	//Z軸の判定式
	bool bFrontToBack = (ownMin.z < targetMax.z);	//手前から奥へ
	bool bBackToFront = (ownMax.z > targetMin.z);	//奥から手前へ

	//当たり判定の結果
	bool bCollisionResult = false;

	//********** 当たり判定 **********//

	if (bTopToBottom && bBottomToTop)
	{//Y軸で当たっている場合
		if (bFrontToBack && bBackToFront)
		{//Z軸で当たっている場合
			if ((oldOwnMax.x <= targetMin.x) && (ownMax.x > targetMin.x))
			{//自身が対象に「左から右へ向かって当たった」場合
				//押し出す
				pPosOwn->x = (targetMin.x - sizeMaxOwn.x);

				//「当たった」判定にする
				bCollisionResult = true;
			}
			else if ((oldOwnMin.x >= targetMax.x) && (ownMin.x < targetMax.x))
			{//自身が対象に「右から左へ向かって当たった」場合
				//押し出す
				pPosOwn->x = (targetMax.x + sizeMinOwn.x);

				//「当たった」判定にする
				bCollisionResult = true;
			}
		}
		
		if (bLeftToRight && bRightToLeft)
		{//X軸で当たっている場合
			if ((oldOwnMax.z <= targetMin.z) || (ownMax.z > targetMin.z))
			{//自身が対象に「手前から奥へ向かって当たった」場合
				//押し出す
				pPosOwn->z = (targetMin.z - sizeMaxOwn.z);

				//「当たった」判定にする
				bCollisionResult = true;
			}
			else if ((oldOwnMin.z >= targetMax.z) && (ownMin.z < targetMax.z))
			{//自身が対象に「奥から手前へ向かって当たった」場合
				//押し出す
				pPosOwn->z = (targetMax.z + sizeMinOwn.z);

				//「当たった」判定にする
				bCollisionResult = true;
			}
		}
	}

	if (bLeftToRight && bRightToLeft &&
		bFrontToBack && bBackToFront)
	{//X軸、Z軸で当たっている場合
		if ((oldOwnMax.y <= targetMin.y) || (ownMax.y > targetMin.y))
		{//自身が対象に「下から上へ向かって当たった」場合
			//押し出す
			pPosOwn->y = (targetMin.y - sizeMaxOwn.y);

			//「当たった」判定にする
			bCollisionResult = true;
		}
		else if ((oldOwnMin.y >= targetMax.y) || (ownMin.y < targetMax.y))
		{//自身が対象に「上から下へ向かって当たった」場合
			//押し出す
			pPosOwn->y = (targetMax.y + sizeMinOwn.y);

			//「当たった」判定にする
			bCollisionResult = true;
		}
	}

	return bCollisionResult;	//「当たっていない」判定を返す
}