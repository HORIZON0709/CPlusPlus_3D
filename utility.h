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
	const D3DXVECTOR3 &posOwn ---> ���g�̈ʒu
	const D3DXVECTOR3 &posTarget ---> �Ώۂ̈ʒu
	const D3DXVECTOR3 &sizeMaxOwn ---> ���g�̃T�C�Y�̍ő�l
	const D3DXVECTOR3 &sizeMinOwn ---> ���g�̃T�C�Y�̍ŏ��l
	const D3DXVECTOR3 &sizeMaxTarget ---> �Ώۂ̃T�C�Y�̍ő�l
	const D3DXVECTOR3 &sizeMinTarget ---> �Ώۂ̃T�C�Y�̍ŏ��l
*/
bool CollisionModel(
	const D3DXVECTOR3 &posOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget);

#endif