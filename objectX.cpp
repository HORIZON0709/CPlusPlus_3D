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

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CObjectX::MOVE_SPEED = 2.0f;	//�ړ����x

const int CObjectX::MAX_WORD = 256;		//�ő啶����

const char* CObjectX::FILE_NAME = "data/TEXT/model.txt";	//�ǂݍ��ރt�@�C����

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
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_pFileName("\0"),
	m_nIdx(0)
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
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_numMat = 0;
	m_pFileName = "\0";
	m_nIdx = 0;
	
	//�ǂݍ���
	Load();

	//���_���̎擾
	int nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	DWORD sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int j = 0; j < nNumVtx; j++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		/* ���_���W���r���A���f���̍ő�l�E�ŏ��l���擾 */

		//***** �ő� *****//

		if (vtx.x > m_vtxMax.x)
		{//X
			m_vtxMax.x = vtx.x;
		}

		if (vtx.y > m_vtxMax.y)
		{//Y
			m_vtxMax.y = vtx.y;
		}

		if (vtx.z > m_vtxMax.z)
		{//Z
			m_vtxMax.z = vtx.z;
		}

		//***** �ŏ� *****//

		if (vtx.x < m_vtxMin.x)
		{//X
			m_vtxMin.x = vtx.x;
		}

		if (vtx.y < m_vtxMin.y)
		{//Y
			m_vtxMin.y = vtx.y;
		}

		if (vtx.z < m_vtxMin.z)
		{//Z
			m_vtxMin.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//================================================
//�I��
//================================================
void CObjectX::Uninit()
{
	//���b�V���̉��
	if (m_pMesh != nullptr)
	{
		m_pMesh = nullptr;
	}

	//�}�e���A���̉��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CObjectX::Update()
{
	//�ړ�
	Move();

	D3DXVECTOR3 axis;					//��]��
	D3DXVECTOR3 inverseVec = -m_move;	//move�l�𔽑΂ɂ���

	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�O�ςŉ�]�����Z�o
	D3DXVec3Cross(&axis, &inverseVec, &vecY);
	
	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//�N�I�[�^�j�I���v�Z�p

	//��]���Ɖ�]�p�x���w��
	D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);
	
	// �N�I�[�^�j�I����K�p
	m_quaternion *= quaternion;
	
	// �N�I�[�^�j�I���̃m�[�}���C�Y
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�0�ɂ���
}

//================================================
//�`��
//================================================
void CObjectX::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

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

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^��ێ�
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int i = 0; i < (int)m_numMat; i++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(i);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
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
//�ړ�
//================================================
void CObjectX::Move()
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

//================================================
//�e�̕`��
//================================================
void CObjectX::DrawShadow()
{
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, nor;

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	//���C�g�̕�����ݒ�
	vecLight = D3DXVECTOR4(-1.0f, 0.8f, 0.0f, 0.0f);

	//�ʒu��ݒ�
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@����ݒ�
	nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���ƕ��ʂ�1�_���畽�ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &nor);

	//���C�g�ƕ��ʂ���e�s����쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X�ƃV���h�E�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^��ێ�
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	D3DMATERIAL9 mat = pMat->MatD3D;

	//�F�����ɐݒ�
	mat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	mat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&mat);

	for (int i = 0; i < (int)m_numMat; i++)
	{
		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(i);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//================================================
//�ǂݍ���
//================================================
void CObjectX::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�t�@�C�����J��
	FILE *pFile = fopen(FILE_NAME, "r");
	
	if (pFile == nullptr)
	{//�t�@�C�����J���Ȃ������ꍇ
		assert(false);
	}

	/* �t�@�C�����J�����ꍇ */

	char aText[MAX_WORD];	//�e�L�X�g�i�[�p

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
		fgets(aText, MAX_WORD, pFile);		//1�s�ۂ��Ɠǂݍ���
	}

	while (strcmp(&aText[0], "END_SCRIPT") != 0)
	{//�e�L�X�g�̍ŏI�s��ǂݍ��ނ܂ŌJ��Ԃ�
		//������ǂݍ���
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//�u���b�N�R�����g
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//�R�����g
			//1�s�S�ēǂݍ���
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
		{//�t�@�C����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			char aFileName[MAX_WORD];	//�t�@�C�����ǂݍ��ݗp

			//X�t�@�C���̃p�X��ǂݍ���
			fscanf(pFile, "%s", &aFileName[0]);

			//�ǂݍ��񂾃t�@�C��������
			m_pFileName = &aFileName[0];
		}
		else if (strcmp(&aText[0], "MODELSET") == 0)
		{//���f���̃Z�b�g
			//�ݒ�
			Set(pFile, &aText[0]);
		}
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		m_pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	//�t�@�C�������
	fclose(pFile);
}

//================================================
//�ݒ�
//================================================
void CObjectX::Set(FILE *pFile, char aText[])
{
	while (strcmp(&aText[0], "END_MODELSET") != 0)
	{//���f���̃Z�b�g���I���܂ŌJ��Ԃ�
		//������ǂݍ���
		fscanf(pFile, "%s", &aText[0]);

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//�u���b�N�R�����g
			continue;
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//�R�����g
			//1�s�S�ēǂݍ���
			fgets(aText, MAX_WORD, pFile);
			continue;
		}

		if (strcmp(&aText[0], "INDEX") == 0)
		{//�C���f�b�N�X��
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�C���f�b�N�X����ǂݍ���
			fscanf(pFile, "%d", &m_nIdx);
		}
		else if (strcmp(&aText[0], "POS") == 0)
		{//�ʒu
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�ʒu��ǂݍ���
			fscanf(pFile, "%f", &m_pos.x);	//X��
			fscanf(pFile, "%f", &m_pos.y);	//Y��
			fscanf(pFile, "%f", &m_pos.z);	//Z��
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//������ǂݍ���
			fscanf(pFile, "%f", &m_rot.x);	//X��
			fscanf(pFile, "%f", &m_rot.y);	//Y��
			fscanf(pFile, "%f", &m_rot.z);	//Z��
		}
	}
}