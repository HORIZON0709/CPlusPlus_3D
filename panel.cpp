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

	return S_OK;
}

//================================================
//�I��
//================================================
void CPanel::Uninit()
{
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

	//�`�悷��
	m_pBg->SetIsDraw(m_bPanel);
}

//================================================
//�`��
//================================================
void CPanel::Draw()
{
}