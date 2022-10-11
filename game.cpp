//================================================
//
//������H��b[game.cpp]
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
#include "object3D.h"

#include "camera.h"

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
CCamera* CGame::m_pCamera = nullptr;					//�J����

//================================================
//�J���������擾
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//�R���X�g���N�^
//================================================
CGame::CGame() : CMode(MODE::GAME),
m_nCntStraight(0),
m_nCntIntervalFade(0),
m_bFadeOut(false)
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
	m_nCntStraight = 0;
	m_nCntIntervalFade = 0;
	m_bFadeOut = false;

	/* ���� */

	if (m_pCamera == nullptr)
	{//NULL�`�F�b�N
		m_pCamera = new CCamera;	//�J����
		m_pCamera->Init();			//������
	}

	//���]
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================
//�I��
//================================================
void CGame::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)
	CObject3D::ReleaseAll();	//�S�Ẳ��(3D)

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
	CObject::UpdateAll();	//�I�u�W�F�N�g

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Update();	//�J����
	}

	if (CApplication::GetInput()->GetKey()->Trigger(CInput::DECISION))
	{//Enter�L�[����
		m_nCntIntervalFade++;	//�J�E���g�A�b�v

		if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMEOVER == 0))
		{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
			//�Ó]
			CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

			//�Ó]����
			m_bFadeOut = true;
		}

		if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
		{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
			Change(MODE::RESULT);	//���[�h�̐ݒ�
		}
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