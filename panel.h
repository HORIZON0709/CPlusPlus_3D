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
	static const int MAX_PANEL = 8;	//�p�l���̍ő吔
	static const int GRID_X = 3;	//�}�X�ڂ̐�(X��)
	static const int GRID_Y = 3;	//�}�X�ڂ̐�(Y��)

	static const float PANEL_SIZE;	//�p�l���̃T�C�Y

private: /* �\���̂̒�` */
	struct PANEL_INFO	//�p�l�����
	{
		D3DXVECTOR3 pos;		//�p�l���̈ʒu
		CStage::STAGE stage;	//�X�e�[�W
	};

public: /* �ÓI�����o�֐� */
	static CPanel* Create();	//����

public: /* �ÓI�����o�ϐ� */
	static PANEL_INFO m_aPanelInfo[MAX_PANEL];	//�p�l�����

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
	void SelectPanel();	//�p�l���̑I��

private: /* �����o�ϐ� */
	CObject2D* m_pBg;					//�w�i
	CObject2D* m_pSelect;				//�I��p
	CObject2D* m_apPanel[MAX_PANEL];	//�X�e�[�W�����̃|���S��

	int m_nPosX;	//�ʒu(X��)
	int m_nPosY;	//�ʒu(Y��)

	bool m_bPanel;	//�p�l�����쒆���ǂ���
};

#endif