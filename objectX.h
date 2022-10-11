//================================================
//
//������H��b[objectX.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObjectX : public CObject
{/* CObject�̔h���N���X */
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

public: /* Collision */
	/*
		�����蔻��
		OBJ_TYPE myType ---> ���g�̃^�C�v
		OBJ_TYPE targetType ---> ��������Ώۂ̃^�C�v
	*/
	bool Collision(OBJ_TYPE myType, OBJ_TYPE targetType);

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;	//�ő�l
	D3DXVECTOR3 m_vtxMin;	//�ŏ��l

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			//���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����̃|�C���^

	DWORD m_numMat;	//�}�e���A�����̐�

	int m_nIdxUse;	//�g�p���郂�f���̃C���f�b�N�X��
};

#endif