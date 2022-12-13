//================================================
//
//3D�Q�[��(��)[player.cpp]
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
#include "utility.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer::MOVE_SPEED = 1.5f;		//�ړ����x
const float CPlayer::ROT_SMOOTHNESS = 0.5f;	//��]�̊��炩��

//***************************
//�ÓI�����o�ϐ�
//***************************
CPlayer::KEY_SET CPlayer::m_aKeySet[NUM_KEYSET] =
{
	/* KEY : 0 / 2 */
	{ 45,	//�t���[����
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,0.18f,0.0f),	//����(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,-1.82f,0.0f),	//����(ROT)
		}
	},
	
	/* KEY : 1 / 2 */
	{ 45,	//�t���[����
		{//[0]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,-0.18f,0.0f),	//����(ROT)

		//[1]
		D3DXVECTOR3(0.0f,0.0f,0.0f),	//�ʒu(POS)
		D3DXVECTOR3(0.0f,1.82f,0.0f),	//����(ROT)
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
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nNumKey(0),
	m_nCurrentKey(0),
	m_nCntMotion(0),
	m_bPressKey(false)
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

	//���_�̍ő�l�ƍŏ��l��ݒ�
	SetVtxMaxAndMin();

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;
	m_bPressKey = false;

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

	//CollisionModel(m_pos,m_pModelTarget->GetPos(),)

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

#ifdef _DEBUG
	//�e����\��
	CDebugProc::Print("\n�s Player �t\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("m_vec:[%f,%f,%f]\n", m_vec.x, m_vec.y, m_vec.z);

	CDebugProc::Print("m_vtxMax:[%f,%f,%f]\n", m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	CDebugProc::Print("m_vtxMin:[%f,%f,%f]\n", m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
#endif // _DEBUG
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
	{//D�L�[������
		if (pKeyboard->GetPress(DIK_W))
		{//�E�O
			m_vec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//�ړ�������ݒ�
		}
		else if (pKeyboard->GetPress(DIK_S))
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
	else if (pKeyboard->GetPress(DIK_A))
	{//A�L�[������
		if (pKeyboard->GetPress(DIK_W))
		{//���O
			m_vec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//�ړ�������ݒ�
		}
		else if (pKeyboard->GetPress(DIK_S))
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
	else if (pKeyboard->GetPress(DIK_W))
	{//W�L�[������
		m_vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//�ړ�������ݒ�

		//�L�[������
		m_bPressKey = true;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//S�L�[������
		m_vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//�ړ�������ݒ�

		//�L�[������
		m_bPressKey = true;
	}

	//********** �� �ړ����� �� **********//

	//�x�N�g���̑傫����1�ɂ���
	D3DXVec3Normalize(&m_vec, &m_vec);

	//2�����̒P�ʃx�N�g������p�x�����߂�
	m_rotDest.y = atan2f(-m_vec.x, -m_vec.z);

	//���݂̌����ƖړI�̌����̍������v�Z
	float fDif = m_rotDest.y - m_rot.y;

	//�p�x�̐��K��
	NormalizeAngle(&fDif);

	//���݂̌������X�V
	m_rot.y += fDif * ROT_SMOOTHNESS;

	//�p�x�̐��K��
	NormalizeAngle(&m_rot.y);

	//********** �� �ړ��� �� **********//

	if (!m_bPressKey)
	{//�ړ��L�[��������Ă��Ȃ��ꍇ
		return;
	}

	/* �ړ��L�[��������Ă���ꍇ */

	//�ړ��ʂɑ��(�ړ��x�N�g�� * �ړ����x)
	m_move = m_vec * MOVE_SPEED;

	//���݂̈ʒu���A�O��̈ʒu�Ƃ��ĕۑ�
	m_posOld = m_pos;

	//���݂̈ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;

	//�ړ��ʂ�0�ɂ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�u�L�[��������Ă��Ȃ��v�ɂ���
	m_bPressKey = false;
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
		float fRelativeValue = (float)m_nCntMotion / (float)m_aKeySet[m_nCurrentKey].nFrame;

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

		//���ݒl�ɑ��(�J�n�l + (���� * ���Βl))
		posPre = m_aKeySet[m_nCurrentKey].aKey[i].pos + pos;
		rotPre = m_aKeySet[m_nCurrentKey].aKey[i].rot + rot;

		//�p�x�̐��K��
		NormalizeAngle(&rotPre.x);	
		NormalizeAngle(&rotPre.y);
		NormalizeAngle(&rotPre.z);

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

//================================================
//���_�̍ő�l�ƍŏ��l��ݒ�
//================================================
void CPlayer::SetVtxMaxAndMin()
{
	//�e�p�[�c�̒��_�̍ő�l�ƍŏ��l���i�[����z��
	D3DXVECTOR3 aVtxMax[MAX_PARTS] = {};
	D3DXVECTOR3 aVtxMin[MAX_PARTS] = {};

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//�e�p�[�c����A���_�̍ő�l�ƍŏ��l���擾
		aVtxMax[i] = m_apModel[i]->GetVtxMax();
		aVtxMin[i] = m_apModel[i]->GetVtxMin();
	}

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if ((i + 1) >= MAX_PARTS)
		{//�p�[�c���̎��̃J�E���g���A�ő�p�[�c���𒴂���ꍇ
			break;
		}

		//********** �ő�l **********//

		if (aVtxMax[i] > aVtxMax[i + 1])
		{//[ ���݂̃p�[�c�̍ő�l > ���̃p�[�c�̍ő�l]
			m_vtxMax = aVtxMax[i];	//���݂̃p�[�c�̍ő�l��ݒ�
		}
		else if (aVtxMax[i] < aVtxMax[i + 1])
		{//[ ���݂̃p�[�c�̍ő�l < ���̃p�[�c�̍ő�l]
			m_vtxMax = aVtxMax[i + 1];	//���̃p�[�c�̍ő�l��ݒ�
		}

		//********** �ŏ��l **********//

		if (aVtxMin[i] < aVtxMin[i + 1])
		{//[ ���݂̃p�[�c�̍ŏ��l < ���̃p�[�c�̍ŏ��l]
			m_vtxMin = aVtxMin[i];	//���݂̃p�[�c�̍ŏ��l��ݒ�
		}
		else if (aVtxMin[i] > aVtxMin[i + 1])
		{//[ ���݂̃p�[�c�̍ŏ��l > ���̃p�[�c�̍ŏ��l]
			m_vtxMin = aVtxMin[i + 1];	//���݂̃p�[�c�̍ŏ��l��ݒ�
		}
	}
}