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
	m_bPanel = false;

	//�w�i�̐���
	m_pBg = CObject2D::Create();

	//�e���̐ݒ�
	m_pBg->SetPos(D3DXVECTOR3(CRenderer::SCREEN_WIDTH * 0.5f, CRenderer::SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pBg->SetSize(D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT));
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//�`�悵�Ȃ�
	m_pBg->SetIsDraw(false);

	float fWidth = CRenderer::SCREEN_WIDTH;		//��ʂ̉���
	float fHeight = CRenderer::SCREEN_HEIGHT;	//��ʂ̏c��

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

	int nTex = CTexture::TEXTURE::Number_Single_1;	//�e�N�X�`���ݒ�p

	for (int i = 0; i < MAX_PANEL; i++)
	{
		//�p�l���̐���
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

	/* �`�悷�� */

	//�w�i
	m_pBg->SetIsDraw(m_bPanel);

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