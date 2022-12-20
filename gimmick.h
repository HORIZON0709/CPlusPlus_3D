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
#include "object.h"

//***************************
//�O���錾
//***************************
class CModel;
class CLine;

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CGimmick : public CObject
{/* CObjectX�̔h���N���X */
private: /* �萔�̒�` */
	static const float MOVE_SPEED;		//�ړ����x
	static const float ROT_SMOOTHNESS;	//��]�̊��炩��
	static const float ROTATION_SPEED;	//��]���x

	static const int MAX_LINE = 12;	//���C���̍ő吔

public: /* �ÓI�����o�֐� */
	static CGimmick* Create();	//����

public: /* �ÓI�����o�ϑ� */
	static CLine* m_apLine[MAX_LINE];	//���C���̃|�C���^

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
	void SetLines();			//���C���̐ݒ�܂Ƃ�

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

public: /* Pos */
	/*
		�ʒu��ݒ�
		const D3DXVECTOR3 &pos ---> �C�ӂ̈ʒu
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//�ʒu���擾
	D3DXVECTOR3 GetPos();

public: /* Rot */
	/*
		������ݒ�
		const D3DXVECTOR3 &rot ---> �C�ӂ̌���
	*/
	void SetRot(const D3DXVECTOR3 &rot);

	//�������擾
	D3DXVECTOR3 GetRot();

public: /* vtx */
	D3DXVECTOR3 GetVtxMax();	//���_�̍ő�l���擾
	D3DXVECTOR3 GetVtxMin();	//���_�̍ŏ��l���擾

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_vec;		//�����x�N�g��
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;	//���_�̍ő�l
	D3DXVECTOR3 m_vtxMin;	//���_�̍ŏ��l

	D3DXQUATERNION m_quaternion;	//�N�H�[�^�j�I��

	bool m_bPressKey;	//�L�[���������ǂ���
	bool m_bMove;		//�ړ����邩�ǂ���
	bool m_bRotation;	//��]���邩�ǂ���
};

#endif