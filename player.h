//================================================
//
//3D�Q�[��(��)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"

//***************************
//�O���錾
//***************************
class CModel;
class CGimmick;

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const float MOVE_SPEED;		//�ړ����x
	static const float ROT_SMOOTHNESS;	//��]�̊��炩��
	
	static const int MAX_PARTS = 2;		//�ő�p�[�c��
	static const int NUM_KEYSET = 2;	//�L�[�Z�b�g��

private: /* �\���̂̒�` */
	struct KEY //�L�[�v�f
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

	struct KEY_SET //�L�[���
	{
		int nFrame;				//�t���[����
		KEY aKey[MAX_PARTS];	//�L�[�v�f
	};

public: /* �ÓI�����o�֐� */
	static CPlayer* Create();	//����

private: /* �ÓI�����o�ϐ� */
	static KEY_SET m_aKeySet[NUM_KEYSET];	//�L�[���

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	D3DXVECTOR3 GetPos();		//�ʒu���擾
	D3DXVECTOR3 GetVtxMax();	//���_�̍ő�l�̎擾
	D3DXVECTOR3 GetVtxMin();	//���_�̍ŏ��l�̎擾
private:
	void Move();		//�ړ�
	void Motion();		//���[�V����
	void Collision();	//�����蔻��

	void SetVtxMaxAndMin();	//���_�̍ő�l�ƍŏ��l�̐ݒ�

private: /* �����o�ϐ� */
	CModel* m_apModel[MAX_PARTS];	//���f���̃|�C���^
	CGimmick* m_pTarget;			//�����蔻��̑ΏۃI�u�W�F�N�g�̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//���݂̈ʒu
	D3DXVECTOR3 m_posOld;	//�O��̈ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_vec;		//�����x�N�g��
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;	//���_�̍ő�l
	D3DXVECTOR3 m_vtxMin;	//���_�̍ŏ��l

	int m_nNumKey;		//�L�[�̑���
	int m_nCurrentKey;	//���݂̃L�[�ԍ�
	int m_nCntMotion;	//���[�V�����J�E���^�[

	bool m_bPressKey;	//�L�[���������ǂ���
};

#endif