//================================================
//
//������H��b[model.h]
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
	static const char* FILE_NAME;	//�ǂݍ��ރt�@�C����

public: /* �ÓI�����o�֐� */
	static CModel* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CModel();
	~CModel();

public: /* �����o�֐� */
	HRESULT Init(const char* aFileName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
 
	/*
		�e�̐ݒ�
		CModel* pModel ---> ���f���̃|�C���^
	*/
	void SetParent(CModel* pModel);

	D3DXMATRIX GetMtxWorld();	//���[���h�}�g���b�N�X�̎擾
public: /* Pos */
	/*
		�ʒu��ݒ�
		const D3DXVECTOR3 &pos ---> �C�ӂ̈ʒu
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//�ʒu���擾
	D3DXVECTOR3 GetPos();

private:
	void DrawShadow();	//�e�̕`��

	void Load(const char* aFileName);	//�ǂݍ���

	/*
		�ݒ�
		FILE *pFile ---> �t�@�C���|�C���^
		char aText[] ---> �e�L�X�g�i�[�p
	*/
	void Set(FILE *pFile, char aText[]);

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_vtxMax;	//�ő�l
	D3DXVECTOR3 m_vtxMin;	//�ŏ��l

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			//���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����̃|�C���^

	DWORD m_numMat;	//�}�e���A�����̐�

	char* m_pFileName;	//�t�@�C����

	int m_nIdx;	//�C���f�b�N�X��

	CModel* m_pParent;	//�e���f���ւ̃|�C���^
};

#endif