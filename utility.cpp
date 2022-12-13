//================================================
//
//3D�Q�[��(��)[utility.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "utility.h"

//================================================
//�p�x�̐��K��
//================================================
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{//�p�x��[3.14]�ȏ�̏ꍇ
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{//�p�x��[-3.14]�ȉ��̏ꍇ
		*pAngle += D3DX_PI * 2.0f;
	}
}

//================================================
//�����蔻��(���f�����m)
//================================================
bool CollisionModel(
	const D3DXVECTOR3 &posOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget)
{
	D3DXVECTOR3 ownMax = D3DXVECTOR3(	//���g�̔���̍ő�l
		posOwn.x + sizeMaxOwn.x,
		posOwn.y + sizeMaxOwn.y,
		posOwn.z + sizeMaxOwn.z
		);

	D3DXVECTOR3 ownMin = D3DXVECTOR3(	//���g�̔���̍ŏ��l
		posOwn.x + sizeMinOwn.x,
		posOwn.y + sizeMinOwn.y,
		posOwn.z + sizeMinOwn.z
	);

	D3DXVECTOR3 targetMax = D3DXVECTOR3(	//�Ώۂ̔���̍ő�l
		posTarget.x + sizeMaxTarget.x,
		posTarget.y + sizeMaxTarget.y,
		posTarget.z + sizeMaxTarget.z
	);

	D3DXVECTOR3 targetMin = D3DXVECTOR3(	//�Ώۂ̔���̍ŏ��l
		posTarget.x + sizeMinTarget.x,
		posTarget.y + sizeMinTarget.y,
		posTarget.z + sizeMinTarget.z
	);

	{//********** X�� **********//

		bool bRightAndLeft = (ownMax.x > targetMin.x);
		bool bLeftAndRight = (ownMin.x < targetMax.x);

		if (bRightAndLeft || bLeftAndRight)
		{
			return true;
		}
	}

	{//********** Y�� **********//

		bool bTopAndBottom = (ownMax.y > targetMin.y);
		bool bBottomAndTop = (ownMin.y < targetMax.y);

		if (bTopAndBottom || bBottomAndTop)
		{
			return true;
		}
	}

	{//********** Z�� **********//

		bool bFrontAndBack = (ownMax.z > targetMin.z);
		bool bBackAndFront = (ownMin.z < targetMax.z);

		if (bFrontAndBack || bBackAndFront)
		{
			return true;
		}
	}

	return false;
}