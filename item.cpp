//================================================
//
//3D�Q�[��(��)[item.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "item.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "model.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CItem::ROTATION_SPEED = 0.05f;	//��]���x

//================================================
//����
//================================================
CItem* CItem::Create()
{
	CItem* pItem = nullptr;	//�|�C���^

	if (pItem != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pItem = new CItem;	//�������̓��I�m��

	pItem->Init();	//������

	return pItem;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CItem::CItem() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_bPressKey(false)
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));

	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::ITEM);
}

//================================================
//�f�X�g���N�^
//================================================
CItem::~CItem()
{
}

//================================================
//������
//================================================
HRESULT CItem::Init()
{
	//���f���̐���
	m_pModel = CModel::Create(CModel::XFILE::Coin01);

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bPressKey = false;

	return S_OK;
}

//================================================
//�I��
//================================================
void CItem::Uninit()
{
}

//================================================
//�X�V
//================================================
void CItem::Update()
{
	//��]
	m_rot.y += ROTATION_SPEED;

	//�p�x�̐��K��
	NormalizeAngle(&m_rot.y);

#ifdef _DEBUG
	//�e����\��
	CDebugProc::Print("\n�s Item �t\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);

#endif // _DEBUG
}

//================================================
//�`��
//================================================
void CItem::Draw()
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

	//���f���̕`��
	m_pModel->Draw();
}