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
#include "line.h"
#include "objectX.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CItem::ROTATION_SPEED = 0.05f;	//��]���x

//***************************
//�ÓI�����o�ϐ�
//***************************
CLine* CItem::m_apLine[MAX_LINE] = {};	//���C���̃|�C���^

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
	m_pModel = CObjectX::Create("data/MODEL/Coin01.x");

	//���_�̍ő�l�E�ŏ��l��ݒ�
	m_vtxMax = m_pModel->GetVtxMax();
	m_vtxMin = m_pModel->GetVtxMin();

	//�����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
void CItem::Uninit()
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

	//���C���̐ݒ�܂Ƃ�
	SetLines();

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

	for (int i = 0; i < MAX_LINE; i++)
	{
		//���C���̕`��
		m_apLine[i]->Draw();
	}
}

//================================================
//���C���̐ݒ�܂Ƃ�
//================================================
void CItem::SetLines()
{
	//�F(�S�Ă̐��œ����F)
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

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

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CItem::GetPos()
{
	return m_pos;
}

//================================================
//���_�̍ő�l���擾
//================================================
D3DXVECTOR3 CItem::GetVtxMax()
{
	return m_vtxMax;
}

//================================================
//���_�̍ŏ��l���擾
//================================================
D3DXVECTOR3 CItem::GetVtxMin()
{
	return m_vtxMin;
}