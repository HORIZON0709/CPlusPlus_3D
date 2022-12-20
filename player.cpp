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
#include "gimmick.h"
#include "line.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

namespace
{
bool bCollisionDebug = false;
}

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

CLine* CPlayer::m_apLine[MAX_LINE] = {};	//���C���̃|�C���^

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
	m_pTarget(nullptr),
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
	m_apModel[0] = CModel::Create(CModel::XFILE::Fish_Body);
	m_apModel[1] = CModel::Create(CModel::XFILE::Fish_Tail);

	//�e���f���̐ݒ�
	m_apModel[1]->SetParent(m_apModel[0]);

	//���_�̍ő�l�ƍŏ��l��ݒ�
	SetVtxMaxAndMin();

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = NUM_KEYSET;
	m_nCurrentKey = 0;
	m_nCntMotion = 0;
	m_bPressKey = false;

	for (int i = 0; i < MAX_LINE; i++)
	{
		m_apLine[i] = CLine::Create();
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_apLine[i] != nullptr)
		{
			m_apLine[i]->Uninit();
			delete m_apLine[i];
			m_apLine[i] = nullptr;
		}
	}
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	//�ړ�
	Move();

	//���[�V����
	//Motion();

	//�����蔻��
	Collision();

	m_apModel[1]->SetPos(D3DXVECTOR3(0.0f, 24.0f, 65.0f));

#ifdef _DEBUG
	//�e����\��
	CDebugProc::Print("\n�s Player �t\n");
	CDebugProc::Print("m_pos:[%f,%f,%f]\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("m_rot:[%f,%f,%f]\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("m_vec:[%f,%f,%f]\n", m_vec.x, m_vec.y, m_vec.z);

	if (bCollisionDebug)
	{//�Ώۂ̃I�u�W�F�N�g�ɓ������Ă���ꍇ
		CDebugProc::Print("bCollision:[true]\n", bCollisionDebug);
	}
	else
	{//�������Ă��Ȃ��ꍇ
		CDebugProc::Print("bCollision:[false]\n", bCollisionDebug);
	}

	//���C���̐ݒ�܂Ƃ�
	SetLines();

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

	for (int i = 0; i < MAX_LINE; i++)
	{
		//���C���̕`��
		m_apLine[i]->Draw();
	}
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CPlayer::GetPos()
{
	return m_pos;
}

//================================================
//���_�̍ő�l���擾
//================================================
D3DXVECTOR3 CPlayer::GetVtxMax()
{
	return m_vtxMax;
}

//================================================
//���_�̍ŏ��l���擾
//================================================
D3DXVECTOR3 CPlayer::GetVtxMin()
{
	return m_vtxMin;
}

//================================================
//�ړ�
//================================================
void CPlayer::Move()
{
	//�L�[�{�[�h�����擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_R))
	{
		m_pos.y += 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_F))
	{
		m_pos.y -= 0.5f;
	}

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
//�����蔻��
//================================================
void CPlayer::Collision()
{
	//�M�~�b�N�����擾
	m_pTarget = CGame::GetGimmick();

	D3DXMATRIX mtxRotOwn,mtxRotTarget;	//�v�Z�p�}�g���b�N�X

	//********** ���_�̍ő�l�E�ŏ��l���R�s�[ **********//

	//���g
	D3DXVECTOR3 vtxMaxOwn = m_vtxMax;	//�ő�l
	D3DXVECTOR3 vtxMinOwn = m_vtxMin;	//�ŏ��l

	//�Ώ�
	D3DXVECTOR3 vtxMaxTarget = m_pTarget->GetVtxMax();	//�ő�l
	D3DXVECTOR3 vtxMinTarget = m_pTarget->GetVtxMin();	//�ŏ��l

	//********** �������烈�[�E�s�b�`�E���[�����w�肵�A�}�g���b�N�X���쐬 **********//

	//���g
	D3DXMatrixRotationYawPitchRoll(&mtxRotOwn, m_rot.y, m_rot.x, m_rot.z);

	//�Ώ�
	D3DXMatrixRotationYawPitchRoll(
		&mtxRotTarget,
		m_pTarget->GetRot().y,
		m_pTarget->GetRot().x,
		m_pTarget->GetRot().z
	);

	//********** �}�g���b�N�X��ϊ����āA���_�̍ő�l�E�ŏ��l�ɐݒ肷�� **********//

	//���g
	D3DXVec3TransformCoord(&vtxMaxOwn, &vtxMaxOwn, &mtxRotOwn);	//�ő�l
	D3DXVec3TransformCoord(&vtxMinOwn, &vtxMinOwn, &mtxRotOwn);	//�ŏ��l

	//�Ώ�
	D3DXVec3TransformCoord(&vtxMaxTarget, &vtxMaxTarget, &mtxRotTarget);	//�ő�l
	D3DXVec3TransformCoord(&vtxMinTarget, &vtxMinTarget, &mtxRotTarget);	//�ŏ��l

	//���f�����m�̓����蔻��
	bCollisionDebug = CollisionModel(
		&m_pos,					//���g�̌��݂̈ʒu
		m_posOld,				//���g�̑O��̈ʒu
		m_pTarget->GetPos(),	//�Ώۂ̈ʒu
		vtxMaxOwn,				//���g�̃T�C�Y�̍ő�l
		vtxMinOwn,				//���g�̃T�C�Y�̍ŏ��l
		vtxMaxTarget,			//�Ώۂ̃T�C�Y�̍ő�l
		vtxMinTarget			//�Ώۂ̃T�C�Y�̍ŏ��l
	);
}

//================================================
//���_�̍ő�l�ƍŏ��l��ݒ�
//================================================
void CPlayer::SetVtxMaxAndMin()
{
	//���_�̍ő吔�E�ŏ��l��������
	m_vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	m_vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//�e�p�[�c�̒��_�̍ő�l�E�ŏ��l���i�[����z��
	D3DXVECTOR3 aVtxMax[MAX_PARTS] = {};
	D3DXVECTOR3 aVtxMin[MAX_PARTS] = {};

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//�e�p�[�c���璸�_�̍ő�l�E�ŏ��l���擾
		aVtxMax[i] = m_apModel[i]->GetVtxMax();
		aVtxMin[i] = m_apModel[i]->GetVtxMin();
	}

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (i >= MAX_PARTS)
		{//�p�[�c���̃J�E���g���A�ő�p�[�c���𒴂���ꍇ
			break;
		}

		//********** �ő�l **********//

		/* �e�p�[�c�̍ő�l���A���݂̍ő�l���傫���ꍇ�A�ő�l��ݒ肷�� */

		if (aVtxMax[i].x > m_vtxMax.x)
		{//X���W
			m_vtxMax.x = aVtxMax[i].x;	//�ő�l��ݒ�
		}

		if (aVtxMax[i].y > m_vtxMax.y)
		{//Y���W
			m_vtxMax.y = aVtxMax[i].y;	//�ő�l��ݒ�
		}

		if (aVtxMax[i].z> m_vtxMax.z)
		{//Z���W
			m_vtxMax.z = aVtxMax[i].z;	//�ő�l��ݒ�
		}
		
		//********** �ŏ��l **********//

		/* �e�p�[�c�̍ŏ��l���A���݂̍ŏ��l��菬�����ꍇ�A�ŏ��l��ݒ肷�� */

		if (aVtxMin[i].x < m_vtxMin.x)
		{//X���W
			m_vtxMin.x = aVtxMin[i].x;	//�ŏ��l��ݒ�
		}

		if (aVtxMin[i].y < m_vtxMin.y)
		{//Y���W
			m_vtxMin.y = aVtxMin[i].y;	//�ŏ��l��ݒ�
		}

		if (aVtxMin[i].z < m_vtxMin.z)
		{//Z���W
			m_vtxMin.z = aVtxMin[i].z;	//�ŏ��l��ݒ�
		}
	}
}

//================================================
//���C���̐ݒ�܂Ƃ�
//================================================
void CPlayer::SetLines()
{
	//�F(�S�Ă̐��œ����F)
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//���Ԗڂ�
	int nNum = 0;

	//********** �㕔���� **********//

	//�n�_�E�I�_
	D3DXVECTOR3 start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);
	D3DXVECTOR3 end = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �㕔��O�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �㕔�E�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �㕔���� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �������� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** ������O�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �����E�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** �������� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** ��O���� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** ��O�E�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** ������ **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�

	//********** ���E�� **********//

	//�n�_�E�I�_
	start = D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	end = D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z);

	//�ݒ�
	m_apLine[nNum]->Set(m_pos, m_rot, start, end, col);

	nNum++;	//���ɐi�߂�
}