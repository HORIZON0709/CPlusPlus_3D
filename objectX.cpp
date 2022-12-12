//================================================
//
//3D�Q�[��(��)[objectX.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "objectX.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//����
//================================================
CObjectX* CObjectX::Create()
{
	CObjectX* pObjectX = nullptr;	//�|�C���^

	if (pObjectX != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObjectX = new CObjectX;	//�������̓��I�m��

	pObjectX->Init();	//������

	return pObjectX;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CObjectX::CObjectX() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//�f�X�g���N�^
//================================================
CObjectX::~CObjectX()
{
}

//================================================
//������
//================================================
HRESULT CObjectX::Init()
{
	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}

//================================================
//�I��
//================================================
void CObjectX::Uninit()
{
}

//================================================
//�X�V
//================================================
void CObjectX::Update()
{
}

//================================================
//�`��
//================================================
void CObjectX::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//================================================
//�ʒu��ݒ�
//================================================
void CObjectX::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CObjectX::GetPos()
{
	return m_pos;
}

//================================================
//�ړ��ʂ�ݒ�
//================================================
void CObjectX::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//�ړ��ʂ��擾
//================================================
D3DXVECTOR3 CObjectX::GetMove()
{
	return m_move;
}

//================================================
//������ݒ�
//================================================
void CObjectX::Setrot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//================================================
//�������擾
//================================================
D3DXVECTOR3 CObjectX::GetRot()
{
	return m_rot;
}