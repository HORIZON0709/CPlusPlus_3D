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
#include "game.h"

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
	m_bPanel(false),
	m_bIsSelect(false)
{
	//�����o�ϐ��̃N���A
	memset(&m_aPos, 0, sizeof(m_aPos));
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
	m_bIsSelect = false;

	float fWidth = (float)CRenderer::SCREEN_WIDTH;		//��ʂ̉���
	float fHeight = (float)CRenderer::SCREEN_HEIGHT;	//��ʂ̏c��

	{//�p�l���̈ʒu��ݒ肷��
		D3DXVECTOR3 aPos[MAX_PANEL] =
		{//�p�l���̈ʒu(�Œ�)
			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.3f, 0.0f),	//1
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.3f, 0.0f),	//2
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.3f, 0.0f),	//3

			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.5f, 0.0f),	//4
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.5f, 0.0f),	//5
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.5f, 0.0f),	//6

			D3DXVECTOR3(fWidth * 0.4f, fHeight * 0.7f, 0.0f),	//7
			D3DXVECTOR3(fWidth * 0.5f, fHeight * 0.7f, 0.0f),	//8
			D3DXVECTOR3(fWidth * 0.6f, fHeight * 0.7f, 0.0f)	//9
		};

		for (int Y = 0; Y < GRID_Y; Y++)
		{
			for (int X = 0; X < GRID_X; X++)
			{
				//3�~3�}�X�ł̈ʒu��ۑ�����
				m_aPos[Y][X] = aPos[X + (Y * 3)];
			}
		}
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

	/* �I��p�p�l�� */

	//����
	m_pSelect = CObject2D::Create();

	//�e���̐ݒ�
	m_pSelect->SetPos(m_aPos[0][0]);
	m_pSelect->SetSize(D3DXVECTOR2(PANEL_SIZE + 20.0f, PANEL_SIZE + 20.0f));
	m_pSelect->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	//�`�悵�Ȃ�
	m_pSelect->SetIsDraw(false);

	int nTex = CTexture::TEXTURE::Number_Single_1;	//�e�N�X�`���ݒ�p
	int nStage = CStage::STAGE::Stage01;			//�X�e�[�W�ݒ�p

	for (int i = 0; i < MAX_PANEL; i++)
	{//�p�l�����̏�����
		//����
		m_aPanelInfo[i].m_pPanel = CObject2D::Create();

		//�ʒu�̐ݒ�
		m_aPanelInfo[i].m_pPanel->SetPos(m_aPos[(i / GRID_Y)][(i % GRID_X)]);

		//�T�C�Y�̐ݒ�
		m_aPanelInfo[i].m_pPanel->SetSize(D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE));

		//�e�N�X�`���̐ݒ�
		m_aPanelInfo[i].m_pPanel->SetTexture((CTexture::TEXTURE)nTex);

		//���̃e�N�X�`���ɂ���
		nTex++;

		//�`�悵�Ȃ�
		m_aPanelInfo[i].m_pPanel->SetIsDraw(false);

		//�X�e�[�W��ݒ�
		m_aPanelInfo[i].stage = (CStage::STAGE)nStage;

		if (i == (MAX_PANEL - 1))
		{//�󔒕����̓X�e�[�W����
			m_aPanelInfo[i].stage = CStage::STAGE::NONE;
		}

		//���̃X�e�[�W�ɂ���
		nStage++;
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
		if (m_aPanelInfo[i].m_pPanel != nullptr)
		{//NULL�`�F�b�N
			m_aPanelInfo[i].m_pPanel = nullptr;
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

	/* �`�悷�� */

	//�w�i
	m_pBg->SetIsDraw(m_bPanel);

	//�I��p�p�l��
	m_pSelect->SetIsDraw(m_bPanel);

	for (int i = 0; i < MAX_PANEL; i++)
	{
		if (m_aPanelInfo[i].m_pPanel == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//�p�l��
		m_aPanelInfo[i].m_pPanel->SetIsDraw(m_bPanel);

		//���݂̃X�e�[�W���擾
		CStage::STAGE stage = CGame::GetStage()->Get();

		if (m_aPanelInfo[i].stage == stage)
		{//���݂̃X�e�[�W�ɊY������p�l����T��
			//�F���Â�����
			m_aPanelInfo[i].m_pPanel->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}

	if (!m_bPanel)
	{//�p�l����������Ă��Ȃ��ꍇ
		return;
	}

	/* �p�l�����쒆�̏ꍇ */

	//�p�l���̑I��
	SelectPanel();
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
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{//Enter�L�[
		//�I���F��I���̐؂�ւ�
		m_bIsSelect = m_bIsSelect ? false : true;
	}

	//�I��p�p�l���̈ړ�
	MoveSelect();

	//�p�l���̃T�C�Y�̐ݒ�
	SetPanelSize();

	//�I��p�p�l���̐F�̐ݒ�
	SetSelectColor();

	//�p�l���̈ړ�
	MovePanel();
}

//================================================
//�I��p�p�l���̈ړ�
//================================================
void CPanel::MoveSelect()
{
	if (m_bIsSelect)
	{//�I�𒆂̏ꍇ
		return;
	}

	/* �I�𒆂ł͂Ȃ��ꍇ */

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

		if (m_nPosY >= GRID_Y)
		{//2���傫��(3�ȏ�)�ɂȂ����ꍇ
			m_nPosY = GRID_Y - 1;	//2�ɌŒ�
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

		if (m_nPosX >= GRID_X)
		{//2���傫��(3�ȏ�)�ɂȂ����ꍇ
			m_nPosX = GRID_X - 1;	//2�ɌŒ�
		}
	}

	//�I��p�p�l���̈ʒu�̐ݒ�
	m_pSelect->SetPos(m_aPos[m_nPosY][m_nPosX]);
}

//================================================
//�p�l���̃T�C�Y�̐ݒ�
//================================================
void CPanel::SetPanelSize()
{
	for (int i = 0; i < MAX_PANEL; i++)
	{
		if (m_aPanelInfo[i].stage == CStage::STAGE::NONE)
		{//�X�e�[�W�������ꍇ
			continue;
		}

		/* �X�e�[�W������ꍇ */

		//�|�C���^���擾
		CObject2D* pPanel = m_aPanelInfo[i].m_pPanel;

		if (pPanel == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//�ʒu���擾
		D3DXVECTOR3 posPanel = pPanel->GetPos();		//�p�l��
		D3DXVECTOR3 posSelect = m_pSelect->GetPos();	//�I��p�p�l��

		if (posPanel != posSelect)
		{//�����ʒu�ɂ��Ȃ��ꍇ
			continue;
		}

		/* �����ʒu�ɂ���ꍇ */

		//�T�C�Y�ݒ�p
		D3DXVECTOR2 size = D3DXVECTOR2(PANEL_SIZE, PANEL_SIZE);

		if (m_bIsSelect)
		{//�I�𒆂̏ꍇ
			//�T�C�Y�������傫������
			size = D3DXVECTOR2(PANEL_SIZE + 10.0f, PANEL_SIZE + 10.0f);
		}

		//�T�C�Y�̐ݒ�
		pPanel->SetSize(size);
	}
}

//================================================
//�I��p�p�l���̐F�̐ݒ�
//================================================
void CPanel::SetSelectColor()
{
	if (m_pSelect == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	//�F�ݒ�p
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	if (m_bIsSelect)
	{//�I�𒆂̏ꍇ
		//�F��ς���
		col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	}

	//�F�̐ݒ�
	m_pSelect->SetCol(col);
}

//================================================
//�p�l���̈ړ�
//================================================
void CPanel::MovePanel()
{
	if (!m_bIsSelect)
	{//�I�𒆂ł͂Ȃ��ꍇ
		return;
	}

	/* �I�𒆂̏ꍇ */

	int nIdx = 0;	//�ԍ�

	for (int i = 0; i < MAX_PANEL; i++)
	{
		if (m_aPanelInfo[i].m_pPanel == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		if (m_aPanelInfo[i].m_pPanel->GetPos() == m_pSelect->GetPos())
		{//�I��p�p�l���Ɠ����ʒu�ɂ���p�l����T��
			//�ԍ���ۑ�
			nIdx = i;
		}
	}

	if (m_aPanelInfo[nIdx].stage == CStage::STAGE::NONE)
	{//�I�������p�l���ɁA�Y������X�e�[�W�������ꍇ
		return;
	}

	int nDest = 0;	//���݈ʒu����ړ������̔ԍ�

	bool bCanMove = false;	//�ړ��ł��邩�ǂ���

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_D))
	{//D�L�[
		if ((m_nPosX + 1) < GRID_X)
		{//�E���Ɉړ����āA�}�X�ڂ̐�(X��)�𒴂��Ȃ��ꍇ
			//�ʒu���E�ɂ��炷
			m_nPosX++;

			//�ړ���̔ԍ���ݒ�
			nDest = (nIdx + 1);
		}

		if (m_aPanelInfo[nDest].stage == CStage::STAGE::NONE)
		{//�ړ���ɃX�e�[�W�������ꍇ
			//�ړ��ł���
			bCanMove = true;
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_A))
	{//A�L�[
		if ((m_nPosX - 1) >= 0)
		{//�����Ɉړ����āA�}�X�ڂ̐�(X��)�𒴂��Ȃ��ꍇ
			//�ʒu�����ɂ��炷
			m_nPosX--;

			//�ړ���̔ԍ���ݒ�
			nDest = (nIdx - 1);
		}

		if (m_aPanelInfo[nDest].stage == CStage::STAGE::NONE)
		{//�ړ���ɃX�e�[�W�������ꍇ
			//�ړ��ł���
			bCanMove = true;
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_W))
	{//W�L�[
		if ((m_nPosY - 1) >= 0)
		{//�㑤�Ɉړ����āA�}�X�ڂ̐�(Y��)�𒴂��Ȃ��ꍇ
			//�ʒu����ɂ��炷
			m_nPosY--;

			//�ړ���̔ԍ���ݒ�
			nDest = (nIdx - 3);
		}

		if (m_aPanelInfo[nDest].stage == CStage::STAGE::NONE)
		{//�ړ���ɃX�e�[�W�������ꍇ
			//�ړ��ł���
			bCanMove = true;
		}
	}
	else if (CApplication::GetInputKeyboard()->GetTrigger(DIK_S))
	{//S�L�[
		if ((m_nPosY + 1) < GRID_Y)
		{//�E���Ɉړ����āA�}�X�ڂ̐�(Y��)�𒴂��Ȃ��ꍇ
			//�ʒu�����ɂ��炷
			m_nPosY++;

			//�ړ���̔ԍ���ݒ�
			nDest = (nIdx + 3);
		}

		if (m_aPanelInfo[nDest].stage == CStage::STAGE::NONE)
		{//�ړ���ɃX�e�[�W�������ꍇ
			//�ړ��ł���
			bCanMove = true;
		}
	}

	if (bCanMove)
	{//�ړ��ł���ꍇ
		//�ړ���̏���ۑ�
		CStage::STAGE stageDest = m_aPanelInfo[nDest].stage;
		D3DXVECTOR3 posDest = m_aPanelInfo[nDest].m_pPanel->GetPos();

		//�p�l���̊e�����ړ�������
		m_aPanelInfo[nDest].stage = m_aPanelInfo[nIdx].stage;
		m_aPanelInfo[nDest].m_pPanel->SetPos(m_aPanelInfo[nIdx].m_pPanel->GetPos());

		//�ړ����̏��Ɉړ���̕ۑ�������������
		m_aPanelInfo[nIdx].stage = stageDest;
		m_aPanelInfo[nIdx].m_pPanel->SetPos(posDest);

		//�I������Ă��Ȃ���Ԃɂ���
		m_bIsSelect = false;

		//�ړ�����
		bCanMove = false;
	}
}