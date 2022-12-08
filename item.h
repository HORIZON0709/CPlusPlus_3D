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
#include "object.h"

//***************************
//�O���錾
//***************************
class CModel;

//***************************
//�A�C�e���N���X�̒�`
//***************************
class CItem : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const float ROTATION_SPEED;	//��]���x

public: /* �ÓI�����o�֐� */
	static CItem* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CItem();
	~CItem() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���

	bool m_bPressKey;	//�L�[���������ǂ���
};

#endif