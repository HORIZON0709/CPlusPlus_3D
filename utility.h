//================================================
//
//3D�Q�[��(��)[utility.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�v���g�^�C�v�錾
//***************************
/*
	�p�x�̐��K��
	float *pAngle ---> �p�x
*/
void NormalizeAngle(float* pAngle); 

/*
	�����蔻��(���f�����m)
	D3DXVECTOR3* pPosOwn ---> ���g�̈ʒu
	D3DXVECTOR3* pPosTarget ---> �Ώۂ̈ʒu
	const D3DXVECTOR3 &sizeOwn ---> ���g�̃T�C�Y
	const D3DXVECTOR3 &sizeTarget ---> �Ώۂ̃T�C�Y
*/
bool CollisionModel(
	D3DXVECTOR3* pPosOwn,
	D3DXVECTOR3* pPosTarget,
	const D3DXVECTOR3 &sizeOwn,
	const D3DXVECTOR3 &sizeTarget);

#endif