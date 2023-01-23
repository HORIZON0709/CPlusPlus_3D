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

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
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
	m_nNumModel(0)
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
	//�ǂݍ���
	Load();
	
	return S_OK;
}

//================================================
//�I��
//================================================
void CStage::Uninit()
{
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

	char aText[MAX_WORD];	//�e�L�X�g�i�[�p

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
		fgets(aText, MAX_WORD, pFile);	//1�s�ۂ��Ɠǂݍ���
	}

	int nNumModel = 0;	//���f����

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
			fscanf(pFile, "%d", m_nNumModel);
		}
		else if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
		{//�t�@�C����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//X�t�@�C���̃p�X��ǂݍ���
			fscanf(pFile, "%s", m_aModelSetInfo[nNumModel].pFileName);

			//���f�����J�E���g�𑝉�
			nNumModel++;
		}
		else if (strcmp(&aText[0], "MODELSET") == 0)
		{//���f���Z�b�g
			//���f���ݒ�
			Set_ModelSet(pFile, &aText[0]);
		}
	}

	//�t�@�C�������
	fclose(pFile);
}

//================================================
//���f���Z�b�g�ݒ�
//================================================
void CStage::Set_ModelSet(FILE* pFile, char aText[])
{
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

		if (strcmp(&aText[0], "POS") == 0)
		{//�ʒu
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//�ʒu��ǂݍ���
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].pos.x);
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].pos.y);
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].pos.z);
		}
		else if (strcmp(&aText[0], "ROT") == 0)
		{//����
			//�u���v��ǂݍ���
			fscanf(pFile, "%s", &aText[0]);

			//������ǂݍ���
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].rot.x);
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].rot.y);
			fscanf(pFile, "%f", &m_aModelSetInfo[nNumModel].rot.z);
		}
	}
}