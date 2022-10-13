//================================================
//
//������H��b[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object.h"
#include "renderer.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CObject* CObject::m_pTop = nullptr;		//�擪�̃I�u�W�F�N�g�̃|�C���^
CObject* CObject::m_pCurrent = nullptr;	//���݂̃I�u�W�F�N�g�̃|�C���^

int CObject::m_nNumAll = 0;	//�ő吔

//================================================
//�S�Ẳ��
//================================================
void CObject::ReleaseAll()
{
	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULL�`�F�b�N
	//		continue;
	//	}

	//	/* nullptr�ł͂Ȃ��ꍇ */

	//	m_apObject[i]->Release();	//���
	//}
}

//================================================
//�S�Ă̍X�V
//================================================
void CObject::UpdateAll()
{

	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULL�`�F�b�N
	//		continue;
	//	}

	//	/* nullptr�ł͂Ȃ��ꍇ */

	//	m_apObject[i]->Update();	//�X�V
	//}
}

//================================================
//�S�Ă̕`��
//================================================
void CObject::DrawAll()
{
	//for (int i = 0; i < MAX_OBJECT; i++)
	//{
	//	if (m_apObject[i] == nullptr)
	//	{//NULL�`�F�b�N
	//		continue;
	//	}

	//	/* nullptr�ł͂Ȃ��ꍇ */

	//	m_apObject[i]->Draw();	//�`��
	//}
}

//================================================
//�I�u�W�F�N�g���̎擾
//================================================
CObject* CObject::GetObjects(int nIdx)
{
	//return m_apObject[nIdx];
}

//================================================
//�I�u�W�F�N�g���̐ݒ�
//================================================
void CObject::SetObject(int nIdx, void* pObject)
{
	//m_apObject[nIdx] = (CObject*)pObject;
}

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject()
{
	if (m_pTop == nullptr)
	{//�I�u�W�F�N�g����������ꍇ
		//���g��擪�Ƃ��ēo�^
		m_pTop = this;

		//�����Ɏ��g(�擪)������
		m_pCurrent = m_pTop;
		return;
	}

	/* �I�u�W�F�N�g��1�ȏ゠��ꍇ */

	//�����̎��Ɏ��g������
	m_pCurrent->m_pNext = this;

	//���g����Ԍ��ɂȂ�
	this->m_pPrev = m_pCurrent;

	//�����Ɏ��g(�擪)������
	m_pCurrent = m_pTop;

	//����������₷
	m_nNumAll++;
}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
}

//================================================
//���
//================================================
void CObject::Release()
{
	if (this == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	if (this->m_pPrev != nullptr)
	{//���g�̈�O�����݂��Ă���ꍇ
		//�u���g�̈�O�����A���̏��v�ɁA�u���g�̈��̏��v��ڑ�
		this->m_pPrev->m_pNext = this->m_pNext;
	}

	if (this->m_pNext != nullptr)
	{//���g�̈�オ���݂��Ă���ꍇ
		//�u���g�̈�オ���A��O�̏��v�ɁA�u���g�̈�O�̏��v��ڑ�
		this->m_pNext->m_pPrev = this->m_pPrev;
	}

	if (this->m_pPrev == nullptr)
	{//���g�̈�O�ɉ��������ꍇ(���g���擪)
		//�擪�ɁA���g�̈��̏���ݒ�
		m_pTop = this->m_pNext;
	}

	if (this->m_pNext == nullptr)
	{//���g�̈��ɉ��������ꍇ(���g������)
		//�����ɁA���g�̈�O�̏���ݒ�
		m_pCurrent = this->m_pPrev;  
	}

	//�I��
	this->Uninit();

	//�������̉��
	delete this;

	//����������炷
	m_nNumAll--;
}

//================================================
//�^�C�v�̐ݒ�
//================================================
void CObject::SetObjType(const CObject::OBJ_TYPE &type)
{
	objType = type;
}

//================================================
//�^�C�v�̎擾
//================================================
CObject::OBJ_TYPE CObject::GetObjType()
{
	return objType;
}