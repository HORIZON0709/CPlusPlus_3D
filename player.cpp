//================================================
//
//������H��b[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "player.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
//#include "objectMesh.h"
#include "model.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer::MOVE_SPEED = 3.0f;	//�ړ����x

//================================================
//����
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//�|�C���^

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pPlayer = new CPlayer;	//�������̓��I�m��

	pPlayer->Init();	//������

	return pPlayer;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CPlayer::CPlayer() :
	m_pModel(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));

	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//������
//================================================
HRESULT CPlayer::Init()
{
	//���f���̐���
	m_pModel = CModel::Create();

	//�e���f���̐ݒ�
	//CModel::SetParent(m_pModel);

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	//�ړ�
	Move();

	//D3DXVECTOR3 pos = CObjectX::GetPos();	//�ʒu���擾

	////���b�V���Ƃ̓����蔻��
	//CGame::GetMesh()->Collision(&pos);

	//CObjectX::SetPos(pos);
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
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

//================================================
//�ړ�
//================================================
void CPlayer::Move()
{
	//�L�[�{�[�h�����擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_D))
	{//�E
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//�E�O
			m_move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			m_move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//�E���
			m_move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			m_move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z������
		}
		else
		{//�E
			m_move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//��
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//���O
			m_move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			m_move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//�����
			m_move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			m_move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z������
		}
		else
		{//��
			m_move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//�O
		m_move.z += cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Z������
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//���
		m_move.z += cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Z������
	}

	m_pos += m_move;	//�ʒu�Ɉړ��ʂ����Z
}