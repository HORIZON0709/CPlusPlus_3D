//================================================
//
//������H��b[game.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

//***************************
//�C���N���[�h
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CCamera;
class CLight;
class CPolygon3D;
class CPlayer;
class CObjectMesh;

//***************************
//�Q�[���N���X�̒�`
//***************************
class CGame : public CMode
{/* CMode�̔h���N���X */
private: /* �萔�̒�` */
	static const int INTERVAL_STRAIGHT;			//�����G�̐����Ԋu
	static const int FADE_INTERVAL_GAMEOVER;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���I�[�o�[��)
	static const int FADE_INTERVAL_GAMECLEAR;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���N���A��)

public: /* �ÓI�����o�֐� */
	static CCamera* GetCamera();		//�J�����̏����擾
	static CLight* GetLight();			//���C�g�̏����擾
	static CPolygon3D* GetPolygon3D();	//3D�|���S���̏����擾
	static CPlayer* GetPlayer();		//�v���C���[�̏����擾
	static CObjectMesh* GetMesh();		//���b�V���̏����擾
	
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CGame();
	~CGame() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��

private: /* �ÓI�����o�ϐ� */
	static CCamera* m_pCamera;			//�J����
	static CLight* m_pLight;			//���C�g
	static CPolygon3D* m_pPolygon3D;	//3D�|���S��
	static CPlayer* m_pPlayer;			//�v���C���[
	static CObjectMesh* m_pMesh;		//���b�V��
	
private: /* �����o�ϐ� */
	int m_nCntIntervalFade;	//�t�F�[�h����܂ł̊Ԋu�J�E���g�p

	bool m_bFadeOut;	//�Ó]�������ǂ���
	bool m_bWireFrame;	//���C���[�t���[���\���؂�ւ�
};
#endif