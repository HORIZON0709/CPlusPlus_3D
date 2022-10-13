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
	//�擪�̃I�u�W�F�N�g��ۑ�
	CObject* pObject = m_pTop;

	while (pObject)
	{//pObj��nullptr�ɂȂ�܂�
		//�擪�̈��̃I�u�W�F�N�g��ۑ�
		CObject* pNext = pObject->m_pNext;

		//���
		pObject->Release();

		//�擪��ύX
		pObject = pNext;
	}

	//�擪�̃I�u�W�F�N�g��ۑ�
	pObject = m_pTop;

	while (pObject)
	{
		if (pObject->m_bDeath)
		{//���S�t���O�������Ă���ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�I��
			pObject->Uninit();

			//�擪��ύX
			pObject = pNext;
		}
		else
		{//���S�t���O�������Ă��Ȃ��ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�擪��ύX
			pObject = pNext;
		}
	}
}

//================================================
//�S�Ă̍X�V
//================================================
void CObject::UpdateAll()
{
	//�擪�̃I�u�W�F�N�g��ۑ�
	CObject* pObject = m_pTop;

	while (pObject)
	{//pObj��nullptr�ɂȂ�܂�
		//�擪�̈��̃I�u�W�F�N�g��ۑ�
		CObject* pNext = pObject->m_pNext;

		//�X�V
		pObject->Update();

		//�擪��ύX
		pObject = pNext;
	}

	//�擪�̃I�u�W�F�N�g��ۑ�
	pObject = m_pTop;

	while (pObject)
	{
		if (pObject->m_bDeath)
		{//���S�t���O�������Ă���ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�X�V
			pObject->Update();

			//�擪��ύX
			pObject = pNext;
		}
		else
		{//���S�t���O�������Ă��Ȃ��ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�擪��ύX
			pObject = pNext;
		}
	}
}

//================================================
//�S�Ă̕`��
//================================================
void CObject::DrawAll()
{
	//�擪�̃I�u�W�F�N�g��ۑ�
	CObject* pObject = m_pTop;

	while (pObject)
	{//pObj��nullptr�ɂȂ�܂�
		//�擪�̈��̃I�u�W�F�N�g��ۑ�
		CObject* pNext = pObject->m_pNext;

		//�`��
		pObject->Draw();

		//�擪��ύX
		pObject = pNext;
	}

	//�擪�̃I�u�W�F�N�g��ۑ�
	pObject = m_pTop;

	while (pObject)
	{
		if (pObject->m_bDeath)
		{//���S�t���O�������Ă���ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�`��
			pObject->Draw();

			//�擪��ύX
			pObject = pNext;
		}
		else
		{//���S�t���O�������Ă��Ȃ��ꍇ
			//�擪�̈��̃I�u�W�F�N�g��ۑ�
			CObject* pNext = pObject->m_pNext;

			//�擪��ύX
			pObject = pNext;
		}
	}
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