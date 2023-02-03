//================================================
//
//3D�Q�[��(��)[stage.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//�O���錾
//***************************
class CObject3D;
class CObjectX;

//***************************
//�X�e�[�W�N���X�̒�`
//***************************
class CStage
{/* ��{�N���X */
private: /* �񋓌^�̒�` */
	enum DIRECTION	//����
	{
		LEFT = 0,	//��
		BACK,		//��
		RIGHT,		//�E
		FRONT,		//��O
		MAX
	};

private: /* �萔�̒�` */
	static const float FLOAR_SIZE;	//���̃T�C�Y
	static const float WALL_WIDTH;	//�ǂ̕�
	static const float WALL_HEIGHT;	//�ǂ̍���

	static const int NUM_WALL = 4;		//�ǂ̐�
	static const int MAX_MODEL = 16;	//���f���̍ő吔

	static const int MAX_WORD;	//�ő啶����

	static const char* FILE_NAME;	//�t�@�C����

private: /* �\���̂̒�` */
	struct MODELSET_INFO	//���f���z�u�ɕK�v�ȏ��
	{
		int nIndex;			//�C���f�b�N�X��
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

public: /* �ÓI�����o�֐� */
	/*
		����
		char* pFileName ---> �t�@�C����
	*/
	static CStage* Create(char* pFileName);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CStage();
	~CStage();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V

private:
	void Load();	//�ǂݍ���

	/*
		���f���Z�b�g�ݒ�
		FILE* pFile ---> �t�@�C���|�C���^
	*/
	void Set_ModelSet(FILE* pFile);

	void SetWall();

private: /* �����o�ϐ� */
	MODELSET_INFO m_aModelSetInfo[MAX_MODEL];	//���f���ݒu�ɕK�v�ȏ��

	CObject3D* m_pFloar;			//3D�|���S���̏��̃|�C���^
	CObject3D* m_apWall[NUM_WALL];	//3D�|���S���̕�(�l��)�̃|�C���^
	CObjectX* m_apModel[MAX_MODEL];	//���f���̃|�C���^

	int m_nNumModel;	//���f����
	int m_nCntSet;		//�Z�b�g�σ��f�����J�E���g�p
};

#endif