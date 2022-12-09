//================================================
//
//3D�Q�[��(��)[gimmick.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//***************************
//�C���N���[�h
//***************************
#include "objectX.h"

//***************************
//�O���錾
//***************************
class CModel;

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CGimmick : public CObjectX
{/* CObjectX�̔h���N���X */
private: /* �萔�̒�` */
	static const float MOVE_SPEED;		//�ړ����x
	static const float ROT_SMOOTHNESS;	//��]�̊��炩��
	static const float ROTATION_SPEED;	//��]���x

public: /* �ÓI�����o�֐� */
	static CGimmick* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CGimmick();
	~CGimmick() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�֐� */
	void Move();				//�ړ�
	void RotationQuaternion();	//�N�H�[�^�j�I���ɂ���]

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


private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_vec;		//�����x�N�g��
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���

	D3DXQUATERNION m_quaternion;	//�N�H�[�^�j�I��

	bool m_bPressKey;	//�L�[���������ǂ���
	bool m_bMove;		//�ړ����邩�ǂ���
	bool m_bRotation;	//��]���邩�ǂ���
};

#endif