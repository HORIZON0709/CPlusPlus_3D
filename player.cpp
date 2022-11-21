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
#include "model.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer::MOVE_SPEED = 3.0f;	//�ړ����x

//***************************
//�ÓI�����o�ϐ�
//***************************
//CPlayer::KEY_SET CPlayer::m_aKeySet[] =
//{
//	
//};

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
CPlayer::CPlayer() :CObject::CObject(CObject::PRIORITY::PRIO_MODEL),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	memset(m_apModel, 0, sizeof(m_apModel));

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
	/*for (int i = 0; i < MAX_PARTS; i++)
	{
		m_apModel[i] = CModel::Create();
	}*/

	m_apModel[0] = CModel::Create(CModel::XFILE::chair);
	m_apModel[1] = CModel::Create(CModel::XFILE::table);

	//�e���f���̐ݒ�
	m_apModel[1]->SetParent(m_apModel[0]);

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

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

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//���f���̕`��
		m_apModel[i]->Draw();
	}
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

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�0�ɂ���
}