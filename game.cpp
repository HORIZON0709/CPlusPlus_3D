//================================================
//
//3D�Q�[��(��)[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"

#include "object2D.h"

#include "camera.h"
#include "light.h"
#include "player.h"
#include "item.h"
#include "stage.h"
#include "panel.h"

#include <assert.h>
#include <time.h>

//***************************
//�萔�̒�`
//***************************
const int CGame::INTERVAL_STRAIGHT = 120;		//�����G�̐����Ԋu
const int CGame::FADE_INTERVAL_GAMEOVER = 60;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���I�[�o�[��)
const int CGame::FADE_INTERVAL_GAMECLEAR = 180;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���N���A��)

//***************************
//�ÓI�����o�ϐ�
//***************************
CCamera* CGame::m_pCamera = nullptr;	//�J����
CLight* CGame::m_pLight = nullptr;		//���C�g
CPlayer* CGame::m_pPlayer = nullptr;	//�v���C���[
CStage* CGame::m_pStage = nullptr;		//�X�e�[�W
CPanel* CGame::m_pPanel = nullptr;		//�p�l��

//================================================
//�J���������擾
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//���C�g�����擾
//================================================
CLight* CGame::GetLight()
{
	return m_pLight;
}

//================================================
//�v���C���[�����擾
//================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//�X�e�[�W�����擾
//================================================
CStage* CGame::GetStage()
{
	return m_pStage;
}

//================================================
//�p�l�������擾
//================================================
CPanel* CGame::GetPanel()
{
	return m_pPanel;
}

//================================================
//�R���X�g���N�^
//================================================
CGame::CGame() : 
	CMode(MODE::GAME),
	m_nCntIntervalFade(0),
	m_bFadeOut(false),
	m_bWireFrame(false)
{
}

//================================================
//�f�X�g���N�^
//================================================
CGame::~CGame()
{
}

//================================================
//������
//================================================
HRESULT CGame::Init()
{
	srand((unsigned)time(NULL));	//�����_����q�̏�����

	//�����o�ϐ��̏�����
	m_nCntIntervalFade = 0;
	m_bFadeOut = false;
	m_bWireFrame = false;

	//***** ���� *****//

	/* �J���� */

	if (m_pCamera == nullptr)
	{//NULL�`�F�b�N
		m_pCamera = new CCamera;	//���I�m��
		m_pCamera->Init();			//������
	}

	/* ���C�g */

	if (m_pLight == nullptr)
	{//NULL�`�F�b�N
		m_pLight = new CLight;	//���I�m��
		m_pLight->Init();		//������
	}

	/* �v���C���[ */

	if (m_pPlayer == nullptr)
	{//NULL�`�F�b�N
		m_pPlayer = CPlayer::Create();	//����
	}

	/* �X�e�[�W */

	if (m_pStage == nullptr)
	{//NULL�`�F�b�N
		m_pStage = CStage::Create(CStage::STAGE::Stage01);	//����
	}

	/* �p�l�� */

	if (m_pPanel == nullptr)
	{//NULL�`�F�b�N
		m_pPanel = CPanel::Create();	//����
	}

	//���]����
	m_bFadeOut = false;

	//���]
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================\
//�I��
//================================================
void CGame::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)
	CObjectX::ReleaseAll();		//�S�Ẳ��(X���f��)

	/* �p�l�� */

	if (m_pPanel == nullptr)
	{
		m_pPanel->Uninit();	//�I��
		delete m_pPanel;	//�������̉��
		m_pPanel = nullptr;	//nullptr�ɂ���
	}

	/* �X�e�[�W */

	if (m_pStage != nullptr)
	{//NULL�`�F�b�N
		m_pStage->UninitAll();	//�S�Ă̏I��
		delete m_pStage;		//�������̉��
		m_pStage = nullptr;		//nullptr�ɂ���
	}

	/* �v���C���[ */

	m_pPlayer = nullptr;	//nullptr�ɂ���

	/* ���C�g */

	if (m_pLight != nullptr)
	{//NULL�`�F�b�N
		m_pLight->Uninit();	//�I��
		delete m_pLight;	//�������̉��
		m_pLight = nullptr;	//nullptr�ɂ���
	}

	/* �J���� */

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Uninit();	//�I��
		delete m_pCamera;		//�������̉��
		m_pCamera = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CGame::Update()
{
	//���C���[�t���[���̐؂�ւ�
	SwitchWireFrame();

	CObject::UpdateAll();	//�I�u�W�F�N�g

	if (m_pPanel != nullptr)
	{//NULL�`�F�b�N
		m_pPanel->Update();	//�p�l��
	}

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Update();	//�J����
	}

	if (m_pLight != nullptr)
	{//NULL�`�F�b�N
		m_pLight->Update();	//���C�g
	}

	if (m_pStage != nullptr)
	{//NULL�`�F�b�N
		m_pStage = m_pStage->Set();	//�X�e�[�W
	}

	if (CApplication::GetInput()->GetKey()->Trigger(CInput::DECISION))
	{//Enter�L�[����
		m_nCntIntervalFade = FADE_INTERVAL_GAMEOVER + 1;	//�J�E���g�A�b�v
	}

	if (!m_bFadeOut && (m_nCntIntervalFade > FADE_INTERVAL_GAMEOVER))
	{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
		//�Ó]
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

		//�Ó]����
		m_bFadeOut = true;
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
		//Change(MODE::RESULT);	//���[�h�̐ݒ�

		//�X�e�[�W�؂�ւ�
		m_pStage->Change(CStage::STAGE::Stage02);

		//�J�E���g���Z�b�g
		m_nCntIntervalFade = 0;

		//���]����
		m_bFadeOut = false;

		//���]
		CApplication::GetFade()->Set(CFade::STATE::FADE_IN);
	}
}

//================================================
//�`��
//================================================
void CGame::Draw()
{
	//�J�����̐ݒ�
	m_pCamera->Set();

	CObject::DrawAll();	//�I�u�W�F�N�g
}

//================================================
//���C���[�t���[���̐؂�ւ�
//================================================
void CGame::SwitchWireFrame()
{
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_F2))
	{//F2�L�[
		//�\��:��\���̐؂�ւ�
		m_bWireFrame = m_bWireFrame ? false : true;

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		if (m_bWireFrame)
		{//�\����
			//���C���[�t���[�����[�h�̐ݒ�
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{//��\����
			//���ɖ߂�
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}
}