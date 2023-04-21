//================================================
//
//3D�Q�[��(��)[number.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "number.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CNumber::POS_X = 1000.0f;		//�ʒu( X )
const float CNumber::POS_Y = 100.0f;		//�ʒu( Y )
const float CNumber::NUMBER_WIDTH = 30.0f;	//����
const float CNumber::NUMBER_HEIGHT = 50.0f;	//�c��

//================================================
//����
//================================================
CNumber* CNumber::Create()
{
	CNumber* pNumber = nullptr;	//�|�C���^

	if (pNumber != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pNumber = new CNumber;	//�������̓��I�m��

	pNumber->Init();	//������

	return pNumber;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CNumber::CNumber()
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::NUMBER);
}

//================================================
//�f�X�g���N�^
//================================================
CNumber::~CNumber()
{
}

//================================================
//������
//================================================
HRESULT CNumber::Init()
{
	CObject2D::Init();	//�e�N���X
	
	return S_OK;
}

//================================================
//�I��
//================================================
void CNumber::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CNumber::Update()
{
	CObject2D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CNumber::Draw()
{
	CObject2D::Draw();	//�e�N���X
}