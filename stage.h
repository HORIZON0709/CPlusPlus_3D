//================================================
//
//3D�Q�[��(��)[stage.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//�X�e�[�W�N���X�̒�`
//***************************
class CStage
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const int MAX_WORD;	//�ő啶����

	static const char* FILE_NAME;	//�t�@�C����

public: /* �ÓI�����o�֐� */
	static CStage* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CStage();
	~CStage();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private:
	void Load();	//�ǂݍ���

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif