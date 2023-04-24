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

#include "stage.h"

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
	static const int MAX_PANEL = 9;	//�p�l���̍ő吔
	static const int GRID_X = 3;	//�}�X�ڂ̐�(X��)
	static const int GRID_Y = 3;	//�}�X�ڂ̐�(Y��)

	static const float PANEL_SIZE;	//�p�l���̃T�C�Y

private: /* �\���̂̒�` */
	struct PANEL_INFO	//�p�l�����
	{
		CObject2D* m_pPanel;	//�p�l���̃|�C���^
		CStage::STAGE stage;	//�X�e�[�W
	};

public: /* �ÓI�����o�֐� */
	static CPanel* Create();	//����

private: /* �ÓI�����o�ϐ� */
	static PANEL_INFO m_aPanelInfo[GRID_Y][GRID_X];	//�p�l�����

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
	void SelectPanel();		//�p�l���̑I��
	void MoveSelect();		//�I��p�p�l���̈ړ�
	void SetPanelSize();	//�p�l���̃T�C�Y�̐ݒ�
	void SetSelectColor();	//�I��p�p�l���̐F�̐ݒ�
	void MovePanel();		//�p�l���̈ړ�

private: /* �����o�ϐ� */
	CObject2D* m_pBg;		//�w�i
	CObject2D* m_pSelect;	//�I��p�p�l��

	D3DXVECTOR3 m_aPos[GRID_Y][GRID_X];	//�p�l���̈ʒu

	int m_nPosX;	//�ʒu(X��)
	int m_nPosY;	//�ʒu(Y��)

	bool m_bPanel;		//�p�l�����쒆���ǂ���
	bool m_bIsSelect;	//�I�𒆂��ǂ���
};

#endif