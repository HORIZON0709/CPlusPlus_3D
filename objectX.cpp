//================================================
//
//������H��b[objectX.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "objectX.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//����
//================================================
CObjectX* CObjectX::Create()
{
	CObjectX* pObjectX = nullptr;	//�|�C���^

	if (pObjectX != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObjectX = new CObjectX;	//�������̓��I�m��

	pObjectX->Init();	//������

	return pObjectX;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CObjectX::CObjectX() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_nIdxUse(0)
{
	//�����o�ϐ��̃N���A
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//�f�X�g���N�^
//================================================
CObjectX::~CObjectX()
{
}

//================================================
//������
//================================================
HRESULT CObjectX::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::NONE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I��
//================================================
void CObjectX::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CObjectX::Update()
{
}

//================================================
//�`��
//================================================
void CObjectX::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture* pTexture = CApplication::GetTexture();	//�e�N�X�`�����擾

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
							2);					//�`�悷��v���~�e�B�u��
}

//================================================
//�ʒu��ݒ�
//================================================
void CObjectX::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;	//�ʒu��ݒ�

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//�����̔���
	float fHeightHalf = (m_size.y * 0.5f);	//�c���̔���

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CObjectX::GetPos()
{
	return m_pos;
}

//================================================
//�T�C�Y�̐ݒ�
//================================================
void CObjectX::SetSize(const D3DXVECTOR2 &size)
{
	m_size = size;	//�T�C�Y�̐ݒ�

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//�����̔���
	float fHeightHalf = (m_size.y * 0.5f);	//�c���̔���

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�T�C�Y�̎擾
//================================================
D3DXVECTOR2 CObjectX::GetSize()
{
	return m_size;
}

//================================================
//�ړ��ʂ̐ݒ�
//================================================
void CObjectX::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//�ړ��ʂ̎擾
//================================================
D3DXVECTOR3 CObjectX::GetMove()
{
	return m_move;
}

//================================================
//�F�̐ݒ�
//================================================
void CObjectX::SetCol(const D3DXCOLOR &col)
{
	m_col = col;	//�F��ݒ�

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�F�̐ݒ�
//================================================
D3DXCOLOR CObjectX::GetCol()
{
	return m_col;
}

//================================================
//�e�N�X�`���̐ݒ�
//================================================
void CObjectX::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//================================================
//�e�N�X�`�����W�̐ݒ�(�A�j���[�V�����ɑΉ�)
//================================================
void CObjectX::SetTexUV(const int nDivNum, const int nPtnAnim)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

 	float fDivide = (1.0f / nDivNum);	//��Z�p��float�ɕϊ�

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fDivide * nPtnAnim,		0.0f);
	pVtx[1].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 0.0f);
 	pVtx[2].tex = D3DXVECTOR2(fDivide * nPtnAnim,		1.0f);
	pVtx[3].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
