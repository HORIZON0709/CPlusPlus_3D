//================================================
//
//3D�Q�[��(��)[utility.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "utility.h"

//================================================
//�p�x�̐��K��
//================================================
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{//�p�x��[3.14]�ȏ�̏ꍇ
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{//�p�x��[-3.14]�ȉ��̏ꍇ
		*pAngle += D3DX_PI * 2.0f;
	}
}

//================================================
//�����蔻��(���f�����m)
//================================================
bool CollisionModel(
	D3DXVECTOR3* pPosOwn,
	const D3DXVECTOR3 &posOldOwn,
	const D3DXVECTOR3 &posTarget,
	const D3DXVECTOR3 &sizeMaxOwn,
	const D3DXVECTOR3 &sizeMinOwn,
	const D3DXVECTOR3 &sizeMaxTarget,
	const D3DXVECTOR3 &sizeMinTarget)
{
	//********** �����p�ϐ� **********//

	//���g�̔���̍ő�l�E�ŏ��l(���݂̈ʒu)
	D3DXVECTOR3 ownMax = (*pPosOwn + sizeMaxOwn);
	D3DXVECTOR3 ownMin = (*pPosOwn + sizeMinOwn);

	//���g�̔���̍ő�l�E�ŏ��l(�O��̈ʒu)
	D3DXVECTOR3 oldOwnMax = (posOldOwn + sizeMaxOwn);
	D3DXVECTOR3 oldOwnMin = (posOldOwn + sizeMinOwn);

	//�Ώۂ̔���̍ő�l�E�ŏ��l
	D3DXVECTOR3 targetMax = (posTarget + sizeMaxTarget);
	D3DXVECTOR3 targetMin = (posTarget + sizeMinTarget);

	//X���̔��莮
	bool bRightToLeft = (ownMin.x < targetMax.x);	//�E���獶��
	bool bLeftToRight = (ownMax.x > targetMin.x);	//������E��

	//Y���̔��莮
	bool bTopToBottom = (ownMin.y < targetMax.y);	//�ォ�牺��
	bool bBottomToTop = (ownMax.y > targetMin.y);	//��������

	//Z���̔��莮
	bool bFrontToBack = (ownMin.z < targetMax.z);	//��O���牜��
	bool bBackToFront = (ownMax.z > targetMin.z);	//�������O��

	//�����蔻��̌���
	bool bCollisionResult = false;

	//********** �����蔻�� **********//

	if (bTopToBottom && bBottomToTop)
	{//Y���œ������Ă���ꍇ
		if (bFrontToBack && bBackToFront)
		{//Z���œ������Ă���ꍇ
			if ((oldOwnMax.x <= targetMin.x) && (ownMax.x > targetMin.x))
			{//���g���ΏۂɁu������E�֌������ē��������v�ꍇ
				//�����o��
				pPosOwn->x = (targetMin.x - sizeMaxOwn.x);

				//�u���������v����ɂ���
				bCollisionResult = true;
			}
			else if ((oldOwnMin.x >= targetMax.x) && (ownMin.x < targetMax.x))
			{//���g���ΏۂɁu�E���獶�֌������ē��������v�ꍇ
				//�����o��
				pPosOwn->x = (targetMax.x + sizeMinOwn.x);

				//�u���������v����ɂ���
				bCollisionResult = true;
			}
		}
		
		if (bLeftToRight && bRightToLeft)
		{//X���œ������Ă���ꍇ
			if ((oldOwnMax.z <= targetMin.z) || (ownMax.z > targetMin.z))
			{//���g���ΏۂɁu��O���牜�֌������ē��������v�ꍇ
				//�����o��
				pPosOwn->z = (targetMin.z - sizeMaxOwn.z);

				//�u���������v����ɂ���
				bCollisionResult = true;
			}
			else if ((oldOwnMin.z >= targetMax.z) && (ownMin.z < targetMax.z))
			{//���g���ΏۂɁu�������O�֌������ē��������v�ꍇ
				//�����o��
				pPosOwn->z = (targetMax.z + sizeMinOwn.z);

				//�u���������v����ɂ���
				bCollisionResult = true;
			}
		}
	}

	if (bLeftToRight && bRightToLeft &&
		bFrontToBack && bBackToFront)
	{//X���AZ���œ������Ă���ꍇ
		if ((oldOwnMax.y <= targetMin.y) || (ownMax.y > targetMin.y))
		{//���g���ΏۂɁu�������֌������ē��������v�ꍇ
			//�����o��
			pPosOwn->y = (targetMin.y - sizeMaxOwn.y);

			//�u���������v����ɂ���
			bCollisionResult = true;
		}
		else if ((oldOwnMin.y >= targetMax.y) || (ownMin.y < targetMax.y))
		{//���g���ΏۂɁu�ォ�牺�֌������ē��������v�ꍇ
			//�����o��
			pPosOwn->y = (targetMax.y + sizeMinOwn.y);

			//�u���������v����ɂ���
			bCollisionResult = true;
		}
	}

	return bCollisionResult;	//�u�������Ă��Ȃ��v�����Ԃ�
}