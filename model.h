//================================================
//
//3D�Q�[��(��)[model.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>
#include <stdio.h>

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CModel
{/* ��{�N���X */
public: /* �񋓌^�̒�` */
	enum XFILE //X�t�@�C���̃p�X
	{
		NONE = -1,

		/* �f�o�b�O */
		chair = 0,				//�֎q
		table,					//��
		Stage_Debug_Obstade,	//�X�e�[�W�f�o�b�O�p�̏�Q��(������)
		Coin01,					//�R�C��
		Fish_Body,				//���̓���
		Fish_Tail,				//���̔��Ђ�

		MAX
	};

public: /* �萔�̒�` */
	static const char* s_apFileName[];	//�t�@�C���p�X
private:
	static const int MAX_WORD;		//�ő啶����

public: /* �ÓI�����o�֐� */
	/*
		����
		XFILE xFile ---> �ǂݍ���X�t�@�C��
	*/
	static CModel* Create(XFILE xFile);

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CModel();
	~CModel();

public: /* �����o�֐� */
	HRESULT Init(XFILE xFile);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
 
	void LoadAll();			//�S�Ă̓ǂݍ���
	void Load(XFILE xFile);	//�w��̓ǂݍ���

	/*
		�e�̐ݒ�
		CModel* pModel ---> ���f���̃|�C���^
	*/
	void SetParent(CModel* pModel);

	D3DXMATRIX GetMtxWorld();	//���[���h�}�g���b�N�X�̎擾
public: /* Pos */
	/*
		�ʒu��ݒ�
		const D3DXVECTOR3 &pos ---> �C�ӂ̈ʒu
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	//�ʒu���擾
	D3DXVECTOR3 GetPos();

public: /* Rot */
	/*
		������ݒ�
		const D3DXVECTOR3 &rot ---> �C�ӂ̌���
	*/
	void SetRot(const D3DXVECTOR3 &rot);

	//�������擾
	D3DXVECTOR3 GetRot();

public: /* vtx */
	D3DXVECTOR3 GetVtxMax();	//���_�̍ő�l���擾
	D3DXVECTOR3 GetVtxMin();	//���_�̍ŏ��l���擾

private:
	void DrawShadow();	//�e�̕`��

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//���݂̌���
	D3DXVECTOR3 m_vtxMax;	//�ő�l
	D3DXVECTOR3 m_vtxMin;	//�ŏ��l

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			//���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����̃|�C���^

	DWORD m_numMat;	//�}�e���A�����̐�

	int m_nIdx;	//�C���f�b�N�X��

	CModel* m_pParent;	//�e���f���ւ̃|�C���^
};

#endif