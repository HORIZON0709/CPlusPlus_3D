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
#include "objectX.h"

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CObjectX
{/* CObjectX�̔h���N���X */
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

private: /* �����o�ϐ� */
	
};

#endif