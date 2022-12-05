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
//#include "objectMesh.h"
#include "objectX.h"

#include "camera.h"
#include "light.h"
#include "polygon3D.h"
#include "player.h"

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
CCamera* CGame::m_pCamera = nullptr;		//�J����
CLight* CGame::m_pLight = nullptr;			//���C�g
CPolygon3D* CGame::m_pPolygon3D = nullptr;	//3D�|���S��
CPlayer* CGame::m_pPlayer = nullptr;		//�v���C���[
CObjectMesh* CGame::m_pMesh = nullptr;		//���b�V��
CObjectX* CGame::m_pObjX = nullptr;			//X���f��

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
//3D�|���S�������擾
//================================================
CPolygon3D* CGame::GetPolygon3D()
{
	return m_pPolygon3D;
}

//================================================
//�v���C���[�����擾
//================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//���b�V�������擾
//================================================
CObjectMesh* CGame::GetMesh()
{
	return m_pMesh;
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

	/* 3D�|���S�� */

	if (m_pPolygon3D == nullptr)
	{//NULL�`�F�b�N
		m_pPolygon3D = CPolygon3D::Create();	//����
	}

	/* �v���C���[ */

	if (m_pPlayer == nullptr)
	{//NULL�`�F�b�N
		m_pPlayer = CPlayer::Create();	//����
	}

	/* ���b�V�� */

	/*if (m_pMesh == nullptr)
	{
		m_pMesh = CObjectMesh::Create();
	}*/

	/* X���f�� */

	//if (m_pObjX== nullptr)
	//{//NULL�`�F�b�N
	//	m_pObjX = CObjectX::Create();	//����
	//}

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
	CObjectX::ReleaseAll();		//�S�Ẳ��(X)
	//CObjectMesh::ReleaseAll();		//�S�Ẳ��(Mesh)

	/* �J���� */

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Uninit();	//�I��
		delete m_pCamera;		//�������̉��
		m_pCamera = nullptr;	//nullptr�ɂ���
	}

	/* ���C�g */

	if (m_pLight != nullptr)
	{//NULL�`�F�b�N
		m_pLight->Uninit();	//�I��
		delete m_pLight;	//�������̉��
		m_pLight = nullptr;	//nullptr�ɂ���
	}

	/* 3D�|���S�� */

	m_pPolygon3D = nullptr;	//nullptr�ɂ���

	/* �v���C���[ */

	m_pPlayer = nullptr;	//nullptr�ɂ���

	/* ���b�V�� */

	m_pMesh = nullptr;	//nullptr�ɂ���

	/* X���f�� */

	m_pObjX = nullptr;	//nullptr�ɂ���
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

	if (m_pLight != nullptr)
	{//NULL�`�F�b�N
		m_pLight->Update();	//���C�g
	}

	//���C���[�t���[���̐؂�ւ�
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

	//if (CApplication::GetInput()->GetKey()->Trigger(CInput::DECISION))
	//{//Enter�L�[����
	//	m_nCntIntervalFade++;	//�J�E���g�A�b�v

	//	if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMEOVER == 0))
	//	{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
	//		//�Ó]
	//		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

	//		//�Ó]����
	//		m_bFadeOut = true;
	//	}

	//	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	//	{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
	//		Change(MODE::RESULT);	//���[�h�̐ݒ�
	//	}
	//}
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