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
	const D3DXVECTOR3 &sizeOwn,
	const D3DXVECTOR3 &sizeTarget)
{
	

	return false;
}