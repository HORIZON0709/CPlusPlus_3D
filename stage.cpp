//================================================
//
//3D�Q�[��(��)[stage.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "stage.h"
#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CStage::FLOAR_SIZE = 200.0f;				//���̃T�C�Y
const float CStage::WALL_WIDTH = FLOAR_SIZE;			//�ǂ̕�
const float CStage::WALL_HEIGHT = FLOAR_SIZE * 0.5f;	//�ǂ̍���

const int CStage::MAX_WORD = 256;	//�ő啶����

const char* CStage::FILE_NAME = "data/TEXT/model.txt";	//�t�@�C����

//================================================
//����
//================================================
CStage* CStage::Create(char* pFileName)
{
	CStage* pObjectX = nullptr;	//�|�C���^

	if (pObjectX != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObjectX = new CStage;	//�������̓��I�m��

	pObjectX->Init();	//������

	return pObjectX;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CStage::CStage() :
	m_pFloar(nullptr),
	m_nNumModel(0),
	m_nCntSet(0)
{
	//�����o�ϐ��̃N���A
	memset(m_apWall, 0, sizeof(m_apWall));
	memset(m_apModel, 0, sizeof(m_apModel));
}

//================================================
//�f�X�g���N�^
//================================================
CStage::~CStage()
{
}

//================================================
//������
//================================================
HRESULT CStage::Init()
{
	//���̐���
	m_pFloar = CObject3D::Create();

	D3DXVECTOR3 sizeFloar = D3DXVECTOR3(FLOAR_SIZE, 0.0f, FLOAR_SIZE);
	m_pFloar->SetSize(sizeFloar);
	m_pFloar->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));

	for (int i = 0; i < NUM_WALL; i++)
	{
		//�ǂ̐���
		m_apWall[i] = CObject3D::Create();
	}

	SetWall();

	/*posWall = D3DXVECTOR3(
		0.0f,
		m_pFloar->GetPos().y,
		m_pFloar->GetPos().z + (200.0f * 0.5f));

	m_apWall[1]->SetPos(posWall);
	m_apWall[1]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	posWall = D3DXVECTOR3(
		m_pFloar->GetPos().x + (200.0f * 0.5f),
		m_pFloar->GetPos().y,
		0.0f);

	m_apWall[2]->SetPos(posWall);
	m_apWall[2]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	posWall = D3DXVECTOR3(
		0.0f,
		m_pFloar->GetPos().y,
		m_pFloar->GetPos().z - (200.0f * 0.5f));

	m_apWall[3]->SetPos(posWall);
	m_apWall[3]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));*/

	//�ǂݍ���
	Load();

	return S_OK;
}

//================================================
//�I��
//================================================
void CStage::Uninit()
{
	if (m_pFloar != nullptr)
	{//NULL�`�F�b�N
		m_pFloar->Uninit();	//�I������
		delete m_pFloar;	//�������̉��
		m_pFloar = nullptr;	//nullptr�ɂ���
	}

	for (int i = 0; i < NUM_WALL; i++)
	{
		if (m_apWall[i] != nullptr)
		{//NULL�`�F�b�N
			m_apWall[i]->Uninit();	//�I������
			delete m_apWall[i];		//�������̉��
			m_apWall[i] = nullptr;	//nullptr�ɂ���
		}
	}

	for (int i = 0; i < m_nNumModel; i++)
	{
		if (m_apModel[i] != nullptr)
		{//NULL�`�F�b�N
			m_apModel[i]->Uninit();	//�I������
			delete m_apModel[i];	//�������̉��
			m_apModel[i] = nullptr;	//nullptr�ɂ���
		}
	}
}

//================================================
//�X�V
//================================================
void CStage::Update()
{
}

//================================================
//�ǂݍ���
//================================================
void CStage::Load()
{
	//�t�@�C�����J��
	FILE* pFile = fopen(FILE_NAME, "r");
	
	if (pFile == nullptr)
	{//�t�@�C�����J���Ȃ������ꍇ
		assert(false);
	}

	/* �t�@�C�����J�����ꍇ */

	char aText[MAX_WORD] = {};	//�e�L�X�g�i�[�p

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
		fgets(aText, MAX_WORD, pFile);	//1�s�ۂ��Ɠǂݍ���
	}

	char aFileName[MAX_MODEL][MAX_WORD] = {};	//�t�@�C���p�X�ǂݍ��ݗp

	int nCntFile = 0;	//�t�@�C�����J�E���g

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

		if (strcmp(&aText[0], "NUM_MODEL") == 0)
		{//���f����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//���f������ǂݍ���
			fscanf(pFile, "%d", &m_nNumModel);
		}
		else if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
		{//�t�@�C����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//X�t�@�C���̃p�X��ǂݍ���
			fscanf(pFile, "%s", &aFileName[nCntFile][0]);

			//�J�E���g�𑝉�
			nCntFile++;
		}
		else if (strcmp(&aText[0], "MODELSET") == 0)
		{//���f���Z�b�g
			//���f���ݒ�
			Set_ModelSet(pFile);

			//�J�E���g�A�b�v
			m_nCntSet++;
		}
	}

	//�t�@�C�������
	fclose(pFile);

	for (int i = 0; i < m_nNumModel; i++)
	{
		m_apModel[i] = CObjectX::Create(&aFileName[i][0]);

		int nIndex = m_aModelSetInfo[i].nIndex;

		m_apModel[i]->SetPos(m_aModelSetInfo[nIndex].pos);
		m_apModel[i]->SetRot(m_aModelSetInfo[nIndex].rot);
	}
}

//================================================
//���f���Z�b�g�ݒ�
//================================================
void CStage::Set_ModelSet(FILE* pFile)
{
	char aText[MAX_WORD] = {};	//�e�L�X�g�i�[�p

	//�|�C���^�ɑ��
	MODELSET_INFO* pInfo = &m_aModelSetInfo[m_nCntSet];

	while (strcmp(&aText[0], "END_MODELSET") != 0)
	{//���f���Z�b�g���I���܂ŌJ��Ԃ�
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
			fscanf(pFile, "%d", &pInfo->nIndex);
		}
		else if (strcmp(&aText[0], "POS") == 0)
		{//�ʒu
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�ʒu��ǂݍ���
			fscanf(pFile, "%f", &pInfo->pos.x);
			fscanf(pFile, "%f", &pInfo->pos.y);
			fscanf(pFile, "%f", &pInfo->pos.z);
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//������ǂݍ���
			fscanf(pFile, "%f", &pInfo->rot.x);
			fscanf(pFile, "%f", &pInfo->rot.y);
			fscanf(pFile, "%f", &pInfo->rot.z);
		}
	}
}

//================================================
//�ǂ̐ݒ�
//================================================
void CStage::SetWall()
{
	//�����p�ϐ�
	float fFloarSizeHalf = (FLOAR_SIZE * 0.5f);		//���T�C�Y�̔���
	float fWallHeightHalf = (WALL_HEIGHT * 0.5f);	//�ǂ̍����̔���

	//********** �� **********//

	DIRECTION dir = DIRECTION::LEFT;

	//�T�C�Y
	D3DXVECTOR3 size = D3DXVECTOR3(WALL_HEIGHT, 0.0f, WALL_WIDTH);
	m_apWall[dir]->SetSize(size);

	//�ʒu
	D3DXVECTOR3 pos = D3DXVECTOR3(
		m_pFloar->GetPos().x - fFloarSizeHalf,
		m_pFloar->GetPos().y + fWallHeightHalf,
		0.0f);
	m_apWall[dir]->SetPos(pos);

	//����
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f);
	m_apWall[dir]->SetRot(rot);

	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	m_apWall[dir]->SetCol(col);

	//********** �� **********//

	dir = DIRECTION::BACK;

	//�T�C�Y
	size = D3DXVECTOR3(WALL_WIDTH, 0.0f, WALL_HEIGHT);
	m_apWall[dir]->SetSize(size);

	//�ʒu
	pos = D3DXVECTOR3(
		0.0f,
		m_pFloar->GetPos().y + fWallHeightHalf,
		m_pFloar->GetPos().z + fFloarSizeHalf);
	m_apWall[dir]->SetPos(pos);

	//����
	rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);
	m_apWall[dir]->SetRot(rot);

	//�F
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	m_apWall[dir]->SetCol(col);

	//********** �E **********//

	dir = DIRECTION::RIGHT;

	//�T�C�Y
	size = D3DXVECTOR3(WALL_HEIGHT, 0.0f, WALL_WIDTH);
	m_apWall[dir]->SetSize(size);

	//�ʒu
	pos = D3DXVECTOR3(
		m_pFloar->GetPos().x + fFloarSizeHalf,
		m_pFloar->GetPos().y + fWallHeightHalf,
		0.0f);
	m_apWall[dir]->SetPos(pos);

	//����
	rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f);
	m_apWall[dir]->SetRot(rot);

	//�F
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	m_apWall[dir]->SetCol(col);
}