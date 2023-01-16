//================================================
//
//3D�Q�[��(��)[model.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "model.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const int CModel::MAX_WORD = 256;	//�ő啶����

const char* CModel::FILE_NAME = "data/TEXT/motion.txt";	//�t�@�C����

//***************************
//�ÓI�����o�ϐ�
//***************************
CModel::CHARACTER_SET CModel::m_characterSet = {};	//�L�����N�^�[���

//================================================
//����
//================================================
CModel* CModel::Create()
{
	CModel* pModel = nullptr;	//�|�C���^

	if (pModel != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pModel = new CModel;	//�������̓��I�m��

	pModel->Init();	//������

	return pModel;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CModel::CModel():
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_pParent(nullptr)
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//�f�X�g���N�^
//================================================
CModel::~CModel()
{
}

//================================================
//������
//================================================
HRESULT CModel::Init()
{
	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_numMat = 0;
	m_pParent = nullptr;

	//X�t�@�C���̓ǂݍ���
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
void CModel::Uninit()
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
void CModel::Update()
{
}

//================================================
//�`��
//================================================
void CModel::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;	//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

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

	//���f���̉e��`��
	//DrawShadow();

	if (m_pParent != nullptr)
	{//���g�ɐe���f�������݂���Ƃ�
		//�e���f���̃��[���h�}�g���b�N�X���擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//���g���e���f���̏ꍇ
		//���݂̃}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//���[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
//�e�̐ݒ�
//================================================
void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}

//================================================
//���[���h�}�g���b�N�X�̎擾
//================================================
D3DXMATRIX CModel::GetMtxWorld()
{
	return m_mtxWorld;
}

//================================================
//�ʒu��ݒ�
//================================================
void CModel::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CModel::GetPos()
{
	return m_pos;
}

//================================================
//������ݒ�
//================================================
void CModel::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//================================================
//�������擾
//================================================
D3DXVECTOR3 CModel::GetRot()
{
	return m_rot;
}

//================================================
//���_�̍ő�l���擾
//================================================
D3DXVECTOR3 CModel::GetVtxMax()
{
	return m_vtxMax;
}

//================================================
//���_�̍ŏ��l���擾
//================================================
D3DXVECTOR3 CModel::GetVtxMin()
{
	return m_vtxMin;
}

//================================================
//�e�̕`��
//================================================
void CModel::DrawShadow()
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
void CModel::Load()
{
	//�t�@�C�����J��
	FILE* pFile = fopen(FILE_NAME, "r");
	
	if (pFile == nullptr)
	{//�t�@�C�����J���Ȃ������ꍇ
		assert(false);
	}

	/* �t�@�C�����J�����ꍇ */

	char aText[MAX_WORD];	//�e�L�X�g�i�[�p

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
		fgets(aText, MAX_WORD, pFile);	//1�s�ۂ��Ɠǂݍ���
	}

	int nNumXFile = 0;	//X�t�@�C���̐�

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

			//X�t�@�C���̃p�X��ǂݍ���
			fscanf(pFile, "%s", &s_apFileName[nNumXFile]);

			//X�t�@�C���̐��𑝂₷
			nNumXFile++;
		}
		else if (strcmp(&aText[0], "CHARACTERSET") == 0)
		{//�L�����N�^�[�Z�b�g
			//�L�����N�^�[�ݒ�
			Set_CharacterSet(pFile, &aText[0]);
		}
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int i = 0; i < nNumXFile; i++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			s_apFileName[i],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_numMat,
			&m_pMesh);
	}

	//�t�@�C�������
	fclose(pFile);
}

//================================================
//�L�����N�^�[�ݒ�
//================================================
void CModel::Set_CharacterSet(FILE* pFile, char aText[])
{
	while (strcmp(&aText[0], "CHARACTERSET") != 0)
	{//�L�����N�^�[�Z�b�g���I���܂ŌJ��Ԃ�
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

		if (strcmp(&aText[0], "NUM_PARTS") == 0)
		{//�p�[�c��
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�L�[����ǂݍ���
			fscanf(pFile, "%d", &m_characterSet.nNumParts);
		}
		else if (strcmp(&aText[0], "PARTSSET") == 0)
		{//�p�[�c�Z�b�g
			//�p�[�c�Z�b�g�ݒ�
			Set_PartsSet(pFile, &aText[0]);
		}
	}
}

//================================================
//�p�[�c�ݒ�
//================================================
void CModel::Set_PartsSet(FILE* pFile, char aText[])
{
	while (strcmp(&aText[0], "PARTSSET") != 0)
	{//�L�����N�^�[�Z�b�g���I���܂ŌJ��Ԃ�
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
			fscanf(pFile, "%d", &m_characterSet.partsSet.nIndex);
		}
		else if (strcmp(&aText[0], "PARENT") == 0)
		{//�e�p�[�c�ԍ�
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�e�p�[�c�ԍ���ǂݍ���
			fscanf(pFile, "%d", &m_characterSet.partsSet.nParent);
		}
		else if (strcmp(&aText[0], "POS") == 0)
		{//�ʒu
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�ʒu��ǂݍ���
			fscanf(pFile, "%d", &m_characterSet.partsSet.pos.x);
			fscanf(pFile, "%d", &m_characterSet.partsSet.pos.y);
			fscanf(pFile, "%d", &m_characterSet.partsSet.pos.z);
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//������ǂݍ���
			fscanf(pFile, "%d", &m_characterSet.partsSet.rot.x);
			fscanf(pFile, "%d", &m_characterSet.partsSet.rot.y);
			fscanf(pFile, "%d", &m_characterSet.partsSet.rot.z);
		}
	}
}