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

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPanel
{/* ��{�N���X */
private: /* �萔�̒�` */

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

private:

private: /* �����o�ϐ� */
	
};

#endif