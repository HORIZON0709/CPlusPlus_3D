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
#include "objectMesh.h"

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
CPlayer::CPlayer()
{
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
	CObjectX::Init();	//�e�N���X

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObjectX::SetPos(pos);

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	CObjectX::Update();	//�e�N���X

	//�ړ�
	Move();
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	CObjectX::Draw();	//�e�N���X
}

//================================================
//�ړ�
//================================================
void CPlayer::Move()
{
	//�L�[�{�[�h�����擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	D3DXVECTOR3 pos = CObjectX::GetPos();	//�ʒu���擾
	D3DXVECTOR3 move = CObjectX::GetMove();	//�ړ��ʂ��擾

	if (pKeyboard->GetPress(DIK_D))
	{//�E
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//�E�O
			move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//�E���
			move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z������
		}
		else
		{//�E
			move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//��
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//���O
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.z += cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Z������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//�����
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.z += cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Z������
		}
		else
		{//��
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//�O
		move.z += cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Z������
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//���
		move.z += cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Z������
	}

	pos += move;	//�ʒu�Ɉړ��ʂ����Z

	CObjectX::SetPos(pos);	//�ʒu���X�V
}