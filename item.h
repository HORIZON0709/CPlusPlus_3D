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
class CLine;

//***************************
//�A�C�e���N���X�̒�`
//***************************
class CItem : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const float ROTATION_SPEED;	//��]���x

	static const int MAX_LINE = 12;	//���C���̍ő吔

public: /* �ÓI�����o�֐� */
	static CItem* Create();	//����

public: /* �ÓI�����o�ϑ� */
	static CLine* m_apLine[MAX_LINE];	//���C���̃|�C���^

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

	D3DXVECTOR3 GetPos();		//�ʒu���擾
	D3DXVECTOR3 GetVtxMax();	//���_�̍ő�l���擾
	D3DXVECTOR3 GetVtxMin();	//���_�̍ŏ��l���擾

private: /* �����o�ϐ� */
	CModel* m_pModel;	//���f���̃|�C���^

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_rotDest;	//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;	//���_�̍ő�l
	D3DXVECTOR3 m_vtxMin;	//���_�̍ŏ��l

	bool m_bPressKey;	//�L�[���������ǂ���
};

#endif