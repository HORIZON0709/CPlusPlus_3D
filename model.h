//================================================
//
//3D�Q�[��(��)[model.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CModel
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const int MAX_WORD;		//�ő啶����
	static const int NUM_PARTS = 2;	//�p�[�c��

	static const char* FILE_NAME;	//�t�@�C����

private: /* �\���̂̒�` */
	struct PARTS_SET	//�p�[�c���
	{
		int nIndex;			//�C���f�b�N�X��
		int nParent;		//�e�p�[�c�ԍ�
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

	struct CHARACTER_SET	//�L�����N�^�[���
	{
		int nNumParts;					//�p�[�c��
		PARTS_SET aPartsSet[NUM_PARTS];	//�p�[�c���
	};

public:
	struct MODEL_INFO	//���f���̊e���
	{
		LPD3DXMESH pMesh;		//���b�V�����̃|�C���^
		LPD3DXBUFFER pBuffMat;	//�}�e���A�����̃|�C���^
		DWORD numMat;			//�}�e���A�����̐�
		D3DXVECTOR3 pos;		//�ʒu
		D3DXVECTOR3 rot;		//����
		D3DXVECTOR3 vtxMax;		//�ő�l
		D3DXVECTOR3 vtxMin;		//�ŏ��l
	};

public: /* �ÓI�����o�֐� */
	static CModel* Create();	//����

	/*
		���f���̊e���̎擾
		int nNum ---> �ԍ�
	*/
	static MODEL_INFO GetModelInfo(int nNum);


public: /* �ÓI�����o�ϐ� */
	static CHARACTER_SET m_characterSet;	//�L�����N�^�[���

	static MODEL_INFO m_aModelInfo[NUM_PARTS];	//���f���̊e���

	static char* m_apFileName[];	//�t�@�C���p�X

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CModel();
	~CModel();

public: /* �����o�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	D3DXMATRIX GetMtxWorld();	//���[���h�}�g���b�N�X�̎擾

private:
	void DrawShadow();	//�e�̕`��
	void Load();		//�ǂݍ���

	/*
		�L�����N�^�[�ݒ�
		FILE* pFile ---> �t�@�C���|�C���^
		char aText[] ---> �e�L�X�g�i�[�p
	*/
	void Set_CharacterSet(FILE* pFile, char aText[]);

	/*
		�p�[�c�ݒ�
		FILE* pFile ---> �t�@�C���|�C���^
		char aText[] ---> �e�L�X�g�i�[�p
	*/
	void Set_PartsSet(FILE* pFile, char aText[]);

private: /* �����o�ϐ� */
	

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	
	int m_nNumModel;	//���f����
};

#endif