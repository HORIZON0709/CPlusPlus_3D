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

#include "debug_proc.h"

#include <assert.h>

//***************************
//namespace�̒�`
//***************************
namespace Utility	//�֗��֐�
{
/*
	�p�x�̐��K��
	float *pAngle ---> �p�x
*/
void NormalizeAngle(float* pAngle);
} //namespace�͂����܂�

//***************************
//�萔�̒�`
//***************************
const float CPlayer::MOVE_SPEED = 1.5f;	//�ړ����x

//***************************
//�ÓI�����o�ϐ�
//***************************
CPlayer::KEY_SET CPlayer::m_aKeySet[NUM_KEYSET] =
{
	/* KEY : 0 / 2 */
	{ 45,	//�t���[����
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,0.09f,0.0f),	//����(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,-0.91f,0.0f),	//����(ROT)
		}
	},
	
	/* KEY : 1 / 2 */
	{ 45,	//�t���[����
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,-0.09f,0.0f),	//����(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,0.91f,0.0f),	//����(ROT)
		}
	},
};

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
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nNumKey(0),
	m_nCurrentKey(0),
	m_nCntMotion(0)
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

	m_apModel[0] = CModel::Create(CModel::XFILE::Fish_Body);
	m_apModel[1] = CModel::Create(CModel::XFILE::Fish_Tail);

	//�e���f���̐ݒ�
	m_apModel[1]->SetParent(m_apModel[0]);

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;

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

	//���[�V����
	Motion();

	CDebugProc::Print("\n");
	CDebugProc::Print("m_rot : [%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);

	D3DXVECTOR3 aRot[2] =
	{
		m_apModel[0]->GetRot(),
		m_apModel[1]->GetRot(),
	};

	CDebugProc::Print("m_apModel[0]->GetRot() : [%f,%f,%f]\n", aRot[0].x, aRot[0].y, aRot[0].z);
	CDebugProc::Print("m_apModel[1]->GetRot() : [%f,%f,%f]\n", aRot[1].x, aRot[1].y, aRot[1].z);
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

	//������ς���(�}�����炦)
	if (pKeyboard->GetPress(DIK_Q))
	{
		m_rot.y += 0.01f;
	}
	else if (pKeyboard->GetPress(DIK_E))
	{
		m_rot.y -= 0.01f;
	}

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

//================================================
//���[�V����
//================================================
void CPlayer::Motion()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_apModel[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//���Βl���v�Z(���[�V�����J�E���^�[ / �Đ��t���[����)
		float fRelativeValue = (float)(m_nCntMotion / m_aKeySet[i].nFrame);

		//���̃L�[�ԍ�(�v�Z�p)
		int nNextKey = (m_nCurrentKey + 1) % m_nNumKey;

		//����(�I���l - �J�n�l)
		D3DXVECTOR3 posDif = (m_aKeySet[nNextKey].aKey[i].pos - m_aKeySet[m_nCurrentKey].aKey[i].pos);
		D3DXVECTOR3 rotDif = (m_aKeySet[nNextKey].aKey[i].rot - m_aKeySet[m_nCurrentKey].aKey[i].rot);

		//���� * ���Βl
		D3DXVECTOR3 pos = D3DXVECTOR3(	//�ʒu
			posDif.x * fRelativeValue,
			posDif.y * fRelativeValue,
			posDif.z * fRelativeValue);

		D3DXVECTOR3 rot = D3DXVECTOR3(	//����
			rotDif.x * fRelativeValue,
			rotDif.y * fRelativeValue,
			rotDif.z * fRelativeValue);

		//�ʒu�E�����̌��ݒl���擾
		D3DXVECTOR3 posPre = m_apModel[i]->GetPos();
		D3DXVECTOR3 rotPre = m_apModel[i]->GetRot();

		//���ݒl�ɉ��Z(�J�n�l + (���� * ���Βl))
		if (m_nCurrentKey < nNextKey)
		{//�L�[���i�ގ�
			posPre += m_aKeySet[m_nCurrentKey].aKey[i].pos + pos;
			rotPre += m_aKeySet[m_nCurrentKey].aKey[i].rot + rot;
		}
		else if (m_nCurrentKey > nNextKey)
		{//���߂̃L�[�ԍ��ɖ߂鎞
			posPre += m_aKeySet[m_nCurrentKey].aKey[i].pos - pos;
			rotPre += m_aKeySet[m_nCurrentKey].aKey[i].rot - rot;
		}

		//�p�x�̐��K��
		Utility::NormalizeAngle(&rotPre.x);	
		Utility::NormalizeAngle(&rotPre.y);
		Utility::NormalizeAngle(&rotPre.z);

		//�ʒu�E�����𔽉f
		m_apModel[i]->SetPos(posPre);
		m_apModel[i]->SetRot(rotPre);
	}

	m_nCntMotion++;	//���[�V�����J�E���^�[��i�߂�

	if (m_nCntMotion < m_aKeySet[m_nCurrentKey].nFrame)
	{//���[�V�����J�E���^�[���Đ��t���[�����ɒB���Ă��Ȃ��ꍇ
		return;
	}

	/* �Đ��t���[�����ɒB�����ꍇ */

	m_nCurrentKey++;	//���݂̃L�[�ԍ�����i�߂�
	m_nCntMotion = 0;	//���[�V�����J�E���^�[��������

	if (m_nCurrentKey == m_nNumKey)
	{//���݂̃L�[�ԍ����A�L�[�̑����ɒB������
		m_nCurrentKey = 0;	//���݂̃L�[�ԍ���0�ɖ߂�
	}
}

namespace Utility
{
//------------------------------------------------
//�p�x�̐��K��
//------------------------------------------------
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
} //namespace�͂����܂�