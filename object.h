//================================================
//
//������H��b[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject
{/* ��{�N���X */
public: /* �񋓌^�̒�` */
	enum OBJ_TYPE
	{/* �I�u�W�F�N�g�̎�� */
		NONE = -1,
		PLAYER = 0,	//�v���C���[
		ENEMY,		//�G
		BULLET,		//�e
		EXPLOSION,	//����
		BG,			//�w�i
		ITEM,		//�A�C�e��
		SCORE,		//�X�R�A
		NUMBER,		//�i���o�[
		MAX
	};

public: /* �ÓI�����o�֐� */
	static void ReleaseAll();	//�S�Ẳ��
	static void UpdateAll();	//�S�Ă̍X�V
	static void DrawAll();		//�S�Ă̕`��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject();
	virtual ~CObject();

public: /* �������z�֐� */
	virtual HRESULT Init() = 0;	//������
	virtual void Uninit() = 0;	//�I��
	virtual void Update() = 0;	//�X�V
	virtual void Draw() = 0;	//�`��

public: /* �����o�֐� */
	void Release();	//���

public:	/* ObjType */
	/*
		�^�C�v�̐ݒ�
		const OBJ_TYPE &type ---> �C�ӂ̃^�C�v
	*/
	void SetObjType(const OBJ_TYPE &type);

	//�^�C�v�̎擾
	OBJ_TYPE GetObjType();

private: /* �ÓI�����o�ϐ� */
	static CObject* m_pTop;		//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCurrent;	//����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	
private: /* �����o�ϐ� */
	CObject* m_pPrev;	//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;	//���̃I�u�W�F�N�g�ւ̃|�C���^

	CObject::OBJ_TYPE objType;	//���

	bool m_bDeath;	//���S�t���O
};

#endif