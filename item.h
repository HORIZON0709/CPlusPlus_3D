//================================================
//
//3D�Q�[��(��)[item.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***************************
//�C���N���[�h
//***************************
#include "objectX.h"

//***************************
//�O���錾
//***************************
class CLine;

//***************************
//�A�C�e���N���X�̒�`
//***************************
class CItem : public CObjectX
{/* CObjectX�̔h���N���X */
private: /* �萔�̒�` */
	static const float ROTATION_SPEED;	//��]���x

	static const int MAX_LINE = 12;	//���C���̍ő吔

public: /* �ÓI�����o�֐� */
	/*
		����
		char* pFileName ---> �t�@�C����
	*/
	static CItem* Create(char* pFileName);

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CItem();
	~CItem() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	void SetLines();	//���C���̐ݒ�܂Ƃ�

private: /* �����o�ϐ� */
	CLine* m_apLine[MAX_LINE];	//���C���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
};

#endif