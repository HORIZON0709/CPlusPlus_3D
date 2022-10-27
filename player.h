//================================================
//
//������H��b[player.h]
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

public: /* �ÓI�����o�֐� */
	static CPlayer* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�֐� */
	void Move();	//�ړ���

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_rot;	//����
};

#endif