//================================================
//
//������H��b[model.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CModel
{/* ��{�N���X */
private: /* �萔�̒�` */

public: /* �ÓI�����o�֐� */
	static CModel* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CModel();
	~CModel();

public: /* �����o�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
 
	/*
		�e�̐ݒ�
		CModel* pModel ---> ���f���̃|�C���^
	*/
	void SetParent(CModel* pModel);

private: /* �����o�ϐ� */
	CModel* m_pParent;	//�e���f���̃|�C���^
};

#endif