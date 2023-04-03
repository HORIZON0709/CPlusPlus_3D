//================================================
//
//3D�Q�[��(��)[panel.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "panel.h"
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "input.h"

#include "debug_proc.h"
#include "utility.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPanel::PANEL_SIZE = 100.0f;	//�p�l���̃T�C�Y

//***************************
//�ÓI�����o�ϐ�
//***************************
CPanel::PANEL_INFO CPanel::m_aPanelInfo[MAX_PANEL] = {};	//�p�l�����

//================================================
//����
//================================================
CPanel* CPanel::Create()
{
	CPanel* pPanel = nullptr;	//�|�C���^

	if (pPanel != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pPanel = new CPanel;	//�������̓��I�m��

	pPanel->Init();	//������

	return pPanel;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CPanel::CPanel() :
	m_pBg(nullptr),
	m_pSelect(nullptr),
	m_nPosX(0),
	m_nPosY(0),
	m_bPanel(false)
{
	//�����o�ϐ��̃N���A
	memset(m_apPanel, 0, sizeof(m_apPanel));
}

//================================================
//�f�X�g���N�^
//================================================
CPanel::~CPanel()
{
}

//================================================
//������
//================================================
HRESULT CPanel::Init()
{
	//�����o�ϐ��̏�����
	m_nPosX = 0;
	m_nPosY = 0;
	m_bPanel = false;

	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//��ʂ̉���
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//��ʂ̏c��

	for (int i = 0; i < MAX_PANEL; i++)
	{//�p�l�����̏�����
		m_aPanelInfo[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aPanelInfo[i].stage = CStage::STAGE::NONE;
	}

	/* �w�i */

	//����
	m_pBg = CObject2D::Create();

	//�e���̐ݒ�
	m_pBg->SetPos(D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f));
	m_pBg->SetSize(D3DXVECTOR2(fWidth, fHeight));
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//�`�悵�Ȃ�
	m_pBg->SetIsDraw(false);

	D3DXVECTOR3 aPos[MAX_PANEL] =
	{//�p�l���̈ʒu
		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.3f, 0.0f),	//1
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.3f, 0.0f),	//2
		D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.3f, 0.0f),	//3

		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.5f, 0.0f),	//4
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f),	//5
		D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.5f, 0.0f),	//6

		D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.7f, 0.0f),	//7
		D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.7f, 0.0f)	//8
	};

	/* �I��p */

	//����
	m_pSelect = CObject2D::Create();

	//�e���̐ݒ�
	m_pSelect->SetPos(aPos[0]);
	m_pSelect->SetSize(D3DXVECTOR2(PANEL_SIZE + 20.0f, PANEL_SIZE + 20.0f));
	m_pSelect->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	//�`�悵�Ȃ�
	m_pSelect->SetIsDraw(false);

	/* �p�l�� */

	int nTex = CTexture::TEXTURE::Number_Single_1;	//�e�N�X�`���ݒ�p

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//����
		m_apPanel[i] = CObject2D::Create();

		//�ʒu�̐ݒ�
		m_apPanel[i]->SetPos(aPos[i]);

		//�T�C�Y�̐ݒ�
		m_apPanel[i]->SetSize(D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE));

		//�e�N�X�`���̐ݒ�
		m_apPanel[i]->SetTexture((CTexture::TEXTURE)nTex);

		//���̃e�N�X�`���ɂ���
		nTex++;

		//�`�悵�Ȃ�
		m_apPanel[i]->SetIsDraw(false);
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CPanel::Uninit()
{
	for (int i = 0; i < MAX_PANEL; i++)
	{
		if (m_apPanel[i] != nullptr)
		{//NULL�`�F�b�N
			m_apPanel[i] = nullptr;
		}
	}

	if (m_pSelect != nullptr)
	{//NULL�`�F�b�N
		m_pSelect = nullptr;
	}

	if (m_pBg != nullptr)
	{//NULL�`�F�b�N
		m_pBg = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CPanel::Update()
{
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_F3))
	{//F3�L�[
		//�\��:��\���̐؂�ւ�
		m_bPanel = m_bPanel ? false : true;
	}

	if (!m_bPanel)
	{//�p�l����������Ă��Ȃ��ꍇ
		return;
	}

	/* �p�l�����쒆�̏ꍇ */

	//�p�l���̑I��
	SelectPanel();

	/* �`�悷�� */

	//�w�i
	m_pBg->SetIsDraw(m_bPanel);

	//�I��p
	m_pSelect->SetIsDraw(m_bPanel);

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//�p�l��
		m_apPanel[i]->SetIsDraw(m_bPanel);
	}
}

//================================================
//�`��
//================================================
void CPanel::Draw()
{
}

//================================================
//�p�l�����쒆���ǂ������擾
//================================================
bool CPanel::GetIsPanel()
{
	return m_bPanel;
}

//================================================
//�p�l���̑I��
//================================================
void CPanel::SelectPanel()
{
	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//��ʂ̉���
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//��ʂ̏c��

	D3DXVECTOR3 aPos[GRID_Y][GRID_X] = {};	//�p�l���̈ʒu

	for (int Y = 0; Y < GRID_Y; Y++)
	{
		for (int X = 0; X < GRID_X; X++)
		{
			//�ʒu��ݒ�
			aPos[Y][X] = D3DXVECTOR3(fWidth * (0.3f + (0.1f * (X + 1))), fHeight * ((0.2f * (Y + 1)) + 0.1f), 0.0f);
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_W))
	{//W�L�[����
		m_nPosY--;	//-1����

		if (m_nPosY < 0)
		{//0����(-1�ȉ�)�ɂȂ����ꍇ
			m_nPosY = 0;	//0�ɌŒ�
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_S))
	{//S�L�[����
		m_nPosY++;	//+1����

		if (m_nPosY > 2)
		{//2���傫��(3�ȏ�)�ɂȂ����ꍇ
			m_nPosY = 2;	//2�ɌŒ�
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_A))
	{//A�L�[����
		m_nPosX--;	//-1����

		if (m_nPosX < 0)
		{//0����(-1�ȉ�)�ɂȂ����ꍇ
			m_nPosX = 0;	//0�ɌŒ�
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_D))
	{//D�L�[����
		m_nPosX++;	//+1����

		if (m_nPosX > 2)
		{//2���傫��(3�ȏ�)�ɂȂ����ꍇ
			m_nPosX = 2;	//2�ɌŒ�
		}
	}

	//�I��p�̈ʒu�̐ݒ�
	m_pSelect->SetPos(aPos[m_nPosY][m_nPosX]);
}