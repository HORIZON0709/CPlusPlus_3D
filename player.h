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

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const float MOVE_SPEED;	//�ړ����x
	
	static const int MAX_PARTS = 2;	//�ő�p�[�c��
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

private: /* �����o�֐� */
	void Move();	//�ړ�
	void Motion();	//���[�V����

private: /* �����o�ϐ� */
	CModel* m_apModel[MAX_PARTS];	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���

	int m_nNumKey;		//�L�[�̑���
	int m_nCurrentKey;	//���݂̃L�[�ԍ�
	int m_nCntMotion;	//���[�V�����J�E���^�[
};

#endif