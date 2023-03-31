//================================================
//
//3D�Q�[��(��)[panel.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PANEL_H_
#define _PANEL_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CObject2D;

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPanel
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const int MAX_PANEL = 8;	//�p�l���̍ő吔

	static const float PANEL_SIZE;	//�p�l���̃T�C�Y

public: /* �ÓI�����o�֐� */
	static CPanel* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPanel();
	~CPanel();

public: /* �����o�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	bool GetIsPanel();	//�p�l�����쒆���ǂ������擾

private:

private: /* �����o�ϐ� */
	CObject2D* m_pBg;					//�w�i
	CObject2D* m_apPanel[MAX_PANEL];	//�X�e�[�W�����̃|���S��

	bool m_bPanel;	//�p�l�����쒆���ǂ���
};

#endif