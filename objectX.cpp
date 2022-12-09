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
#include "input.h"
#include "model.h"

#include "debug_proc.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CObjectX::ROTATION_SPEED = 0.25f;	//��]���x
const float CObjectX::MOVE_SPEED = 5.0f;		//�ړ����x

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
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_quaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),
	m_bPressKey(false),
	m_bMove(false),
	m_bRotation(false)
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
	//���f���̐���
	m_pModel = CModel::Create(CModel::XFILE::Stage_Debug_Obstade);

	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_bPressKey = false;
	m_bMove = false;
	m_bRotation = false;
	
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
#ifdef _DEBUG
	if (m_bMove)
	{//�ړ��A���̏ꍇ
		//�ړ�
		Move();

		if (m_bRotation)
		{//��]�A���̏ꍇ
			//�N�H�[�^�j�I���ɂ���]
			RotationQuaternion();
		}
	}

	//�ړ��ʂ�0�ɂ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e����\��
	CDebugProc::Print("\n�s ObjectX �t\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_quaternion:[%f,%f,%f,%f]\n", m_quaternion.x, m_quaternion.y, m_quaternion.z, m_quaternion.w);
#endif // _DEBUG
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
	/*D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);*/

	//�N�H�[�^�j�I�����g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);	//�N�I�[�^�j�I���ɂ��s���]
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);	//�s��|���Z�֐�(��2�����~��3�������1�����Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���f���̉e��`��
	//DrawShadow();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���̕`��
	m_pModel->Draw();
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
//�ړ��̗L����ݒ�
//================================================
void CObjectX::SetFlagOfMove(bool bMove)
{
	m_bMove = bMove;
}

//================================================
//��]�̗L����ݒ�
//================================================
void CObjectX::SetFlagOfRotation(bool bRotation)
{
	m_bRotation = bRotation;
}

//================================================
//�ړ�
//================================================
void CObjectX::Move()
{
	//�L�[�{�[�h�����擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_K))
	{//K�L�[������
		if (pKeyboard->GetPress(DIK_U))
		{//�E�O
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//�ړ�������ݒ�
		}
		else if (pKeyboard->GetPress(DIK_J))
		{//�E���
			m_vec = D3DXVECTOR3(1.0f, 0.0f, -1.0f);	//�ړ�������ݒ�
		}
		else
		{//�E
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	//�ړ�������ݒ�
		}

		//�L�[������
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_H))
	{//A�L�[������
		if (pKeyboard->GetPress(DIK_U))
		{//���O
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//�ړ�������ݒ�
		}
		else if (pKeyboard->GetPress(DIK_J))
		{//�����
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);	//�ړ�������ݒ�
		}
		else
		{//��
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);	//�ړ�������ݒ�
		}

		//�L�[������
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_U))
	{//W�L�[������
		m_vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//�ړ�������ݒ�

		//�L�[������
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_J))
	{//S�L�[������
		m_vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//�ړ�������ݒ�

		//�L�[������
		m_bPressKey = true;
	}

	if (!m_bPressKey)
	{//�ړ��L�[��������Ă��Ȃ��ꍇ
		return;
	}

	/* �ړ��L�[��������Ă���ꍇ */

	//�ړ��ʂɑ��(�ړ��x�N�g�� * �ړ����x)
	m_move = m_vec * MOVE_SPEED;

	//�ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;

	//�u�L�[��������Ă��Ȃ��v�ɂ���
	m_bPressKey = false;
}

//================================================
//�N�H�[�^�j�I���ɂ���]
//================================================
void CObjectX::RotationQuaternion()
{
	D3DXVECTOR3 axis;					//��]��
	D3DXVECTOR3 inverseVec = -m_move;	//move�l�𔽑΂ɂ���

	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�O�ςŉ�]�����Z�o
	D3DXVec3Cross(&axis, &inverseVec, &vecY);
	
	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//�N�I�[�^�j�I���v�Z�p

	//��]���Ɖ�]�p�x���w��
	D3DXQuaternionRotationAxis(&quaternion, &axis, ROTATION_SPEED);
	
	// �N�I�[�^�j�I����K�p
	m_quaternion *= quaternion;
	
	// �N�I�[�^�j�I���̃m�[�}���C�Y
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);
}