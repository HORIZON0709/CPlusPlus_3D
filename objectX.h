//================================================
//
//3D�Q�[��(��)[objectX.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"

#include <stdio.h>

//***************************
//�O���錾
//***************************
class CModel;

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObjectX : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const float MOVE_SPEED;	//�ړ����x

	static const int MAX_WORD;		//�ő啶����

	static const char* FILE_NAME;	//�ǂݍ��ރt�@�C����

public: /* �ÓI�����o�֐� */
	static CObjectX* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObjectX();
	~CObjectX() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* Pos */
	/*
		�ʒu��ݒ�
		const D3DXVECTOR3 &pos ---> �C�ӂ̈ʒu
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//�ʒu���擾
	D3DXVECTOR3 GetPos();

public: /* Move */
	/*
		�ړ��ʂ�ݒ�
		const D3DXVECTOR3 &move ---> �C�ӂ̈ړ���
	*/
	void SetMove(const D3DXVECTOR3 &move);

	//�ړ��ʂ��擾
	D3DXVECTOR3 GetMove();

public: /* Collision */
	/*
		�����蔻��
		OBJ_TYPE myType ---> ���g�̃^�C�v
		OBJ_TYPE targetType ---> ��������Ώۂ̃^�C�v
	*/
	//bool Collision(OBJ_TYPE myType, OBJ_TYPE targetType);

private: /* �����o�֐� */
	void Move();		//�ړ�
	void DrawShadow();	//�e�̕`��
	void Load();		//�ǂݍ���

	/*
		�ݒ�
		FILE *pFile ---> �t�@�C���|�C���^
		char aText[] ---> �e�L�X�g�i�[�p
	*/
	void Set(FILE *pFile, char aText[]);

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;	//�ő�l
	D3DXVECTOR3 m_vtxMin;	//�ŏ��l

	D3DXQUATERNION m_quaternion;	//�N�H�[�^�j�I��

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			//���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����̃|�C���^

	DWORD m_numMat;	//�}�e���A�����̐�

	char* m_pFileName;	//�t�@�C����

	int m_nIdx;	//�C���f�b�N�X��
};

#endif