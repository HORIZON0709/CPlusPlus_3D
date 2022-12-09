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
	static const float ROTATION_SPEED;	//��]���x
	static const float MOVE_SPEED;		//�ړ����x

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

public: /* bool����n */
	/*
		�ړ��̗L����ݒ�
		bool bMove ---> �ړ����邩���Ȃ���
	*/
	void SetFlagOfMove(bool bMove);

	/*
		��]�̗L����ݒ�
		bool bRotation ---> ��]���邩�ǂ���
	*/
	void SetFlagOfRotation(bool bRotation);

private: /* �����o�֐� */
	void Move();				//�ړ�
	void RotationQuaternion();

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_vec;		//�����x�N�g��

	D3DXQUATERNION m_quaternion;	//�N�H�[�^�j�I��

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	bool m_bPressKey;	//�L�[���������ǂ���
	bool m_bMove;		//�ړ����邩�ǂ���
	bool m_bRotation;	//��]���邩�ǂ���
};

#endif